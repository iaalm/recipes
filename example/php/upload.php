<?php
var_dump($_FILES);
?><form action="upload.php" enctype="multipart/form-data" method="POST">
	<br><b>Submit a solution:</b> <input type="file" NAME="filename">
	<input type="submit" VALUE="Send it in!">
</FORM>
