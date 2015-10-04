
<!doctype html>
<html>
  <head>
    <title>Giraffer</title>
    <meta charset="UTF-8">
  </head>
  <body>

	<?php
		$Username = $_POST["Username"];

		session_start();
		//      $_SESSION["Username"] = $_POST["Username"];//apperentely sessions dont work anymore...
		$cookie_name = "Username";
		$cookie_value = $_POST["Username"];
		setcookie($cookie_name, $cookie_value, time() + (86400 * 30), "/"); // 86400 = 1 day
		$cookie_name = "Password";
		$cookie_value = $_POST["Password"];
		setcookie($cookie_name, $cookie_value, time() + (86400 * 30), "/"); // 86400 = 1 day

		//echo $_SESSION["Username"];

		for($i = 13002; $i < 13005; ++$i){

			$fp = stream_socket_client("tcp://0.0.0.0:" . $i, $errno, $errstr, 5);
			if ($fp) {
				fwrite($fp, "Cred " . $Username . ' ' . $_POST["Password"]);



				while($line = fgets($fp)) {
					//echo $line;
					if($line[0] == '1'){
					header("location:response.php");	
					break;
					}
				}
			break;
			}					
		}
	?>

    login incorrect!<br> 
    <form action="index.php" method="Post">
    <input type="submit" value="Click here to go back!"><br>
    </form>




   </body>
</html>
