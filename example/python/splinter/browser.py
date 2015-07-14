#!env python3
# -*- coding: utf-8 -*- 

from splinter import Browser

browser = Browser()
browser.visit('http://baidu.com')
browser.fill('wd', 'splinter')
browser.find_by_id('su').click()

if browser.is_text_present('splinter.cobrateam.info'):
	print("Yes, the official website was found!")
else:
	print("No, it wasn't found... We need to improve our SEO techniques")
		    
browser.quit()
