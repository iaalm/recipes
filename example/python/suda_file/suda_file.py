#!env python3
# -*- coding: utf-8 -*-
import urllib.request
import re

baseurl = "http://file.suda.edu.cn"
title_pattern = re.compile(r'<td><a href="([^"]*)" target="_blank">([^>]*)</a></td>')
count = 0

def get_title(postfix,file):
    global count
    fp = urllib.request.urlopen(baseurl+postfix)
    content = fp.read().decode("gbk")       #原网页写的是gb2312,实际是gbk
    for m in title_pattern.finditer(content):
        print(m.group(1) + ' ' + m.group(2),file=file)
        count = count + 1
        
if __name__ == "__main__" :
    f = open("suda_file.txt", "w")
    page_pattern = re.compile(r'<option value="(?P<pre>[^\d]*)(?P<id>\d*)"( selected)?>(?P=id)</option>')
    fp = urllib.request.urlopen(baseurl)
    content = fp.read().decode("gb2312")
    for m in page_pattern.finditer(content):
        get_title(m.group(1)+m.group(2),f)
    f.close()
    print("done!\n%d total" % count)


