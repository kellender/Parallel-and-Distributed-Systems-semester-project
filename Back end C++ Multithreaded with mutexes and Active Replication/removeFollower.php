<!doctype html>
<html>
  <head>
    <title>Giraffer</title>
    <meta charset="UTF-8">
  </head>
  <body>
    



  <!--This is were i can remove followers from a specific user to a  Text file. meh comments-->
	<?php
	session_start();
	$username = $_COOKIE['Username'];
	$filename = "" . $username . "_followers.txt";
	$password = $_COOKIE['Password'];


	for($i = 13002; $i < 13005; ++$i){
		$fp = stream_socket_client("tcp://0.0.0.0:" . $i, $errno, $errstr, 5);
		if ($fp) {
			fwrite($fp, "rmFollo "  . $username . " " . $password . " " . $_POST["removalFollower"] . "\n" );
			header("location:response.php");
			break;
		}
	}
	echo $errstr;
	exit(1);
	?>
  





   </body>
</html>


