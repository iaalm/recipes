import os
import sys
from PIL import Image, ImageFilter
import numpy as np

def resize_image_with_blur_background(image_path, output_folder, target_width=1920, target_height=1080):
    """
    Resize an image to 1920x1080.
    If the aspect ratio is not 16:10, maintain the original aspect ratio
    and fill the remaining space with a blurred version of the original image.
    
    Args:
        image_path: Path to the input image
        output_folder: Folder to save the output image
        target_width: Target width (default 1920)
        target_height: Target height (default 1080)
    """
    
    try:
        # Open the image
        img = Image.open(image_path)
        original_width, original_height = img.size
        
        # Calculate target aspect ratio (16:10 = 1.6)
        target_ratio = target_width / target_height
        current_ratio = original_width / original_height
        
        # Create a blurred background by cropping the center of the original image
        # Crop to fill the target dimensions while maintaining original aspect ratio
        crop_width = original_width
        crop_height = original_height
        
        if current_ratio > target_ratio:
            # Image is wider than target - crop width
            crop_width = int(original_height * target_ratio)
        else:
            # Image is taller than target - crop height
            crop_height = int(original_width / target_ratio)
        
        # Calculate crop position (center crop)
        left = (original_width - crop_width) // 2
        top = (original_height - crop_height) // 2
        right = left + crop_width
        bottom = top + crop_height
        
        # Crop the center part of the original image
        bg_img = img.crop((left, top, right, bottom))
        
        # Resize the cropped image to fill the target dimensions
        bg_img = bg_img.resize((target_width, target_height), Image.Resampling.LANCZOS)
        
        # Apply blur to the background
        bg_img = bg_img.filter(ImageFilter.GaussianBlur(radius=30))
        
        # Create the final canvas with the blurred background
        final_img = Image.new('RGB', (target_width, target_height))
        final_img.paste(bg_img)
        
        # Calculate the size for the main image (maintaining aspect ratio)
        if current_ratio < target_ratio:
            # Fit by height
            new_height = target_height
            new_width = int(target_height * current_ratio)
        else:
            # Fit by width
            new_width = target_width
            new_height = int(target_width / current_ratio)
        
        # Resize the original image
        resized_img = img.resize((new_width, new_height), Image.Resampling.LANCZOS)
        
        # Calculate position to center the image
        x_offset = (target_width - new_width) // 2
        y_offset = (target_height - new_height) // 2
        
        # Paste the resized image on top of the blurred background
        final_img.paste(resized_img, (x_offset, y_offset))
        
        # Save the output image
        os.makedirs(output_folder, exist_ok=True)
        filename = os.path.basename(image_path)
        output_path = os.path.join(output_folder, f"resized_{filename}")
        final_img.save(output_path, quality=95)
        
        print(f"✓ Processed: {filename} -> {output_path}")
        print(f"  Original size: {original_width}x{original_height}")
        print(f"  Effective size: {new_width}x{new_height}")
        print(f"  Output size: {target_width}x{target_height}\n")
        
        return output_path
    
    except Exception as e:
        print(f"✗ Error processing {image_path}: {str(e)}\n")
        return None


def process_folder(folder_path, output_folder="output"):
    """
    Process all JPG images in a folder.
    
    Args:
        folder_path: Path to the folder containing images
        output_folder: Folder to save output images
    """
    
    # Check if folder exists
    if not os.path.isdir(folder_path):
        print(f"Error: Folder '{folder_path}' not found!")
        return
    
    # Get all jpg files
    jpg_files = [f for f in os.listdir(folder_path) 
                 if f.lower().endswith(('.jpg', '.jpeg'))]
    
    if not jpg_files:
        print(f"No JPG files found in '{folder_path}'")
        return
    
    print(f"Found {len(jpg_files)} JPG file(s)\n")
    print("Processing images...")
    print("-" * 50)
    
    # Process each image
    for jpg_file in jpg_files:
        image_path = os.path.join(folder_path, jpg_file)
        resize_image_with_blur_background(image_path, output_folder)
    
    print("-" * 50)
    print(f"All images processed! Output folder: '{output_folder}'")


if __name__ == "__main__":
    # Specify your folder path here
    output_folder = "output"  # Output folder name
    
    process_folder(sys.argv[1], output_folder)
