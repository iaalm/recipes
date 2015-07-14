<?php
$conn = mysql_connect("127.0.0.1","usr_php","php");
if(!$conn)
{
	die("connect error" . mysql_error());
}
mysql_select_db("db_php",$conn);
$result = mysql_query("select * from topic");
echo "<table border='1'>";
while($row = mysql_fetch_array($result))
{
	echo "<tr>";
	echo "<td>" . $row["creater"] . "</td>";
	echo "<td><a href=showReply.php?id=".$row["id"] . ">" . $row["title"] . "</a></td>";
	echo "</tr>";
}
echo "</table>";
mysql_close($conn);
?>
