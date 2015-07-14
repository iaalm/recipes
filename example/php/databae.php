<?php
$conn = mysql_connect("127.0.0.1","usr_php","php");
if(!$conn)
{
	die("connect error" . mysql_error());
}
mysql_select_db("db_php",$conn);
$result = mysql_query("select * from test");
while($row = mysql_fetch_array($result))
{
	echo $row["id"] . " " . $row["name"] . "<br/>";
}
mysql_close($conn);
?>
