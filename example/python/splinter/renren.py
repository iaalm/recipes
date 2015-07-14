#!env python3
# -*- coding: utf-8 -*- 

from splinter import Browser

browser = Browser()
browser.visit('http://www.renren.com/SysHome.do')
browser.fill('email', 'xxx_kkk_sss@yahoo.com.cn')
browser.fill('password', 'lighting')
browser.find_by_id('login').click()
browser.visit("http://www.renren.com/285677911#//status/status?id=272008801");
print(browser.html);
#browser.quit()
