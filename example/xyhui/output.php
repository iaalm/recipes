<?php
$con = mysql_connect('192.168.135.113','fpp','fpp','fpp');
//var_dump($con);
mysql_select_db('test',$con);
#$res=mysql_query('select * from Test_List order by answer',$con);
$res=mysql_query('select * from Test_List',$con);
//var_dump($res);
echo '
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8;"  />
<title>苏州大学 智慧之星 题库</title></head>';
$count = 0;
while($i = mysql_fetch_array($res))
//	var_dump($i);
	echo ++$count . ':' . urldecode($i['question']) . '<br />' . urldecode($i['answer']) . '<br /><br />';
mysql_close($con);
?>
