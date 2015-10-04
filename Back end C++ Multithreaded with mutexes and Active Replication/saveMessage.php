<!doctype html>
<html>
  <head>
    <title>Giraffer</title>
    <meta charset="UTF-8">
  </head>
  <body>
    



  <!--This is were i can add followers to a specific user to a  Text file-->
	<?php
	session_start();
	$username = $_COOKIE['Username'];
	$filename = "" . $username . "_messages.txt";
	$password = $_COOKIE['Password'];

	session_start();
	$_SESSION["Username"] = $_POST["Username"];


	for($i = 13002; $i < 13005; ++$i){
		$fp = stream_socket_client("tcp://0.0.0.0:" . $i, $errno, $errstr, 5);
		if ($fp) {
			fwrite($fp, "addMsg "  . $username . " " . $password ." " . $_POST["reciever"] ." " . $username . ":" . $_POST["Message"] . "\n");
			header("location:response.php");
			break;
		}
	}
	echo $errstr;
	exit(1);
	?>
  





   </body>
</html>


