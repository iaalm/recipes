<?php
$conn = mysql_connect("127.0.0.1","usr_php","php");
if(!$conn)
{
	die("connect error" . mysql_error());
}
mysql_select_db("db_php",$conn);
$result = mysql_query("select * from topic where id = " .$_GET["id"]);
$row = mysql_fetch_array($result);
$reply = mysql_query("select * from reply where tid = " .$_GET["id"]);
echo "<table border='1'>";
echo "<tr>";
echo "<td>" . $row["creater"] . "</td>";
echo "<td>" . $row["title"] . "</td>";
echo "</tr>";
echo "<tr>";
echo "<td> </td>" . "<td>". $row["article"]."</td>";
echo "</tr>";
while($row = mysql_fetch_array($reply))
{
	echo "<tr>";
	echo "<td>" . $row["creater"] . "</td>";
	echo "<td>" . $row["title"] . "</td>";
	echo "</tr>";
	echo "<tr>";
	echo "<td> </td>" . "<td>". $row["article"]."</td>";
	echo "</tr>";
}
echo "</table>";
mysql_close($conn);
?>
