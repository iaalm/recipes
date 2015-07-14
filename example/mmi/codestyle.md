mmi项目代码规范及建议
==========

##内容

包括mmi项目开发中的python，html，css，js代码的命名及格式规范。

##python

###结构
* 代码按对象组成，每个对象应当在相应的APP目录下建立 <对象名>_urls.py <对象名>_views.py 模板和model可以共用，统一APP下，通过的工具统一放在utils.py下内。url应当由上级url通过include函数指向当前url。

###命名
* python全局使用一套名空间的情况比较普遍，所以，代码中应当以后缀表示不同的对象类型。

模型    _m
视图    _v
过滤器 _f

##模板
* 各页面一般都需要extend自head.html，将需要的js，css包括在head中，其他内容放置在bnody中。如果需要显示提示信息，应当尽量使用head提供的message。

##html
* css和js可以使用cdn的方式从外界加载，不过需要在static下留有副本，以便在cdn无法使用时可以切换到本地文件。


##css
* 推荐使用**bootstrip**来制作网页，统一界面风格。

##js
* 尽量使用现有的**jQuery**和**ko.js**来实现功能，使代码风格较为统一。


#changelog
时间 |版本 |内容
------|---|----
15. September 2014 |1.0 |草稿

