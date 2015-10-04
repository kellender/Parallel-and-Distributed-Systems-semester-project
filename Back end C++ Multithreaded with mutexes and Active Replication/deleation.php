<!doctype html>
<html>
  <head>
    <title>Giraffer</title>
    <meta charset="UTF-8">
  </head>
  <body>
    



  <!--This is were i can remove user who cancled their account -->
	<?php
		session_start();
		$username = $_COOKIE['Username'];
		$password = $_COOKIE['Password'];

		for($i = 13002; $i < 13005; ++$i){
			$fp = stream_socket_client("tcp://0.0.0.0:" . $i, $errno, $errstr, 5);
			if ($fp) {
				fwrite($fp, "delUser ". $username . " " . $password. "\n" );
				header("location:index.php");
				break;
			}
		}
		echo $errstr;
		exit(1);
	?>






   </body>
</html>


