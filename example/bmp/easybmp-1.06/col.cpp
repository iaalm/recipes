#include "EasyBMP.h"
using namespace std;
int main( int argc, char* argv[] )
{
	FILE *fp = fopen("/dev/fb0","w");
	if( argc != 2 )
	{
		cout << "Usage: ColorBMPtoGrayscale <input_filename> <output_filename>"
			<< endl << endl;
		return 1;
	}
	// declare and read the bitmap
	BMP Input;
	Input.ReadFromFile( argv[1] );
	// convert each pixel to grayscale using RGB->YUV
	for( int j=0 ; j < Input.TellHeight() ; j++)
	{
		for( int i=0 ; i < Input.TellWidth() ; i++)
		{
			fprintf(fp,"%c%c%c%c",Input(i,j)->Blue,Input(i,j)->Green,Input(i,j)->Red,0);
		}
		for(int i = 0;i < 1024 - Input.TellWidth() ; i++)
			fprintf(fp,"%c%c%c%c",0,0,0,0);
	}
	fclose(fp);
}

