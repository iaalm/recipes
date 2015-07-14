<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title></title>
    </head>
    <body>
        <?php
        include_once '/usr/local/lib/Smarty-3.1.12/libs/Smarty.class.php';
        $smarty = new Smarty();
        $smarty->assign("name","a");
        $smarty->display("t.tpl");        
        ?>
    </body>
</html>
