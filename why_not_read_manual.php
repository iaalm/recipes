<?php
 function bindAllColumn(&$stmt,&$set)
    {
           $count = $stmt->columnCount();
           for($i = 0;$i < $count;$i+=1)
           {
               $name = $stmt->getColumnMeta($i)["name"];
               $set[$name] = 0;
               $stmt->bindColumn($name,$set[$name]);
           }
    }
?>
