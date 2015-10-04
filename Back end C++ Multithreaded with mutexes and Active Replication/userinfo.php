<!doctype html>
<html>
  <head>
    <title>Giraffer</title>
    <meta charset="UTF-8">
  </head>
  <body>
	<?php

		for($i = 13002; $i < 13005; ++$i){
		$fp = stream_socket_client("tcp://0.0.0.0:" . $i, $errno, $errstr, 5);
		if ($fp) {
			fwrite($fp, "newCred " . $_POST["email"] . ' ' . $_POST["newPassword"] . "\n");
			while($line = fgets($fp)) {
				if($line[0] != '1' and $line[0] != '2'){
					break;
				}
				else{
					header("location:index.php");
					break;
				}
			}
			break;
		}
	}
		
	echo $errstr;
	exit(1);
	?>

    User already Exists!!<br> 
    <form action="index.php" method="Post">
    <input type="submit" value="Click here to go back!"><br>
    </form>


     	
  </body>
</html>
