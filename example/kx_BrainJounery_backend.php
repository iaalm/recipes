<?php

$tab = array(
    'index' => '9dd4e461268c8034f5c8564e155c67a6',
    '9dd4e461268c8034f5c8564e155c67a6' => '0cc175b9c0f1b6a831c399e269772661'
);

if (!array_key_exists("id", $_POST) || !array_key_exists($_POST['id'], $tab))
    echo '<html><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8"><Script Language="JavaScript">alert("答案不在这里！凡人！");window.location.href="./index.html"</Script></head></html>';
    //header("Location: ./index.html");
else if (!array_key_exists("ans", $_POST) || md5($_POST['ans']) != $tab[$_POST['id']])
    echo '<html><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8"><Script Language="JavaScript">alert("错了！亲！");window.location.href="./' . $_POST['id'] . '.html"</Script></head></html>';
//header("Location: ./" . $_POST['id'] . ".html");
else {
    if (file_exists('./result/' . $_POST['id'] . '.txt'))
        header("Location: ./" . md5($_POST['ans']) . ".html");
    else {
        if (isset($_POST['sid'])) {
            $fp = fopen('./result/' . $_POST['id'] . '.txt','w');
            fwrite($fp, $_POST['sid'] . ' ' . $_POST['name']);
            fclose($fp);
            header("Location: ./" . md5($_POST['ans']) . ".html");
        } else {
            echo '<html>
    <head>
        <title></title>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    </head>
    <body>
        <h1>哈哈!你是第一个打到这关的人，有奖品哦，留下你的名字和学号吧!</h1><br />
        <form method="post" action="backend.php">
            <input type="hidden" name ="id" value ="' . $_POST['id'] . '" /><br />
            <input type="hidden" name ="ans" value ="' . $_POST['ans'] . '" />
            学号:<input name ="sid" />
            姓名:<input name ="name" />
            <input type="submit" value="提交" />
        </form>
    </body>
</html>
';
        }
    }
}
?>
