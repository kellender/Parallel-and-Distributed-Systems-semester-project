<!doctype html>
<html>
  <head>
    <title>Giraffer</title>
    <meta charset="UTF-8">
  </head>
  <body>
	<?php
		$Follower = $_POST["followerMessage"];
		$username = $_COOKIE['Username'];
		$password = $_COOKIE['Password'];
		for($i = 13002; $i < 13005; ++$i){
			$fp = stream_socket_client("tcp://0.0.0.0:" . $i, $errno, $errstr, 5);
			if ($fp) {
				fwrite($fp, "viewFolloMsg " . " " . $username . " " . $password . " " . $Follower);
				while($line = fgets($fp)) {
					//echo $line;
					if($line[0] != '0'){
						echo $line;	
						echo "<br>";
						echo "<br>";
					}
				}
				break;
			}
		}
		echo $errstr;
		exit(1);
	?>
    <form action=response.php method="Post">
      <input type="submit" value="Go back">
    </form>
    
   </body>
</html>


