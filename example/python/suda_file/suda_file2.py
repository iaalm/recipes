#!env python3
# -*- coding: utf-8 -*-

__author__ = "iaalm <iaalmsimon@gmail.com>"
__license__ = "MIT"
__version__ = "2.0"

'''用来读取http://file.suda.edu.cn/,写入到sqlite数据库，用来进行搜索'''

import urllib.request
import re
import sqlite3

baseurl = "http://file.suda.edu.cn"
title_pattern = re.compile(r'<td[^>]*>([0-9-]*)</td><td><a href="([^"]*)" target="_blank">([^>]*)</a></td>')
count = 0

def get_title(postfix,cursor):
    global count
    fp = urllib.request.urlopen(baseurl+postfix)
    content = fp.read().decode("gb18030")       #原网页写的是gb2312,实际是gbk,下同
    for m in title_pattern.finditer(content):
        if not cursor.execute('SELECT * FROM file  WHERE url = ?',(m.group(2),)).fetchone() :
            cursor.execute('INSERT INTO file(day,url,title,content) VALUES (?,?,?,?)',(m.group(1),m.group(2),m.group(3),urllib.request.urlopen(baseurl+m.group(2)).read().decode("gb18030")))
            count = count + 1
        else :
            return False
    return True
        
if __name__ == "__main__" :
    conn = sqlite3.connect("file.db")
    c = conn.cursor();
    c.execute('CREATE TABLE IF NOT EXISTS file(url VARCHAR(100) NOT NULL UNIQUE,day date,title NTEXT,content NTEXT)')
    conn.commit()
    page_pattern = re.compile(r'<option value="(?P<pre>[^\d]*)(?P<id>\d*)"( selected)?>(?P=id)</option>')
    fp = urllib.request.urlopen(baseurl)
    content = fp.read().decode("gb18030")
    for m in page_pattern.finditer(content):
        if not get_title(m.group(1)+m.group(2),c) :
            break
    conn.commit()
    conn.close()
    print("done!\n%d new" % count)


