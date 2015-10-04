<!doctype html>
<html>
  <head>

		<title>Giraffer</title>
		<meta charset="UTF-8">
		<link rel="icon" href="bluegiraffe.ico" />
	</head>
  <body>
  <!--This is where i expect my message thing to be-->




	<style>
	.logout{
		
		width:  400px;
		color: black;
		padding: 5px;
		border: 5px lightblue;
		margin: 5px;

		background-color: rgba(255, 0, 0, 0.0);
		
		position: absolute;
	    left: 800px;
	}
	.send{
		
		width:  400px;
		color: black;
		padding: 5px;
		border: 5px lightblue;
		margin: 5px;

		background-color: rgba(255, 0, 0, 0.0);

	}	

	.followers{
		width:  400px;
		left: 800px;
		color: black;
		padding: 5px;
		border: 5px lightblue;
		margin: 5px;

		background-color: rgba(255, 0, 0, 0.0);
	}
	.Messages{
		width:  400px;
		left: 800px;
		color: black;
		padding: 5px;
		border: 5px lightblue;
		margin: 5px;

		background-color: rgba(255, 0, 0, 0.0);
	}
	</style>



	<!-- the ability to log output of the system............... need to put it in the top right-->
	<div class="logout"color="black">
		<form action=index.php method="Post">
        	<input type="submit" value="Logout">
      	</form>
	</div>




	<!--The ability to write / send the messages that the system is built for........ like email...... sigh-->
	<div class="send"color="black">
		<form action=saveMessage.php method="Post">
			Message to:
		    <input type="text" name="reciever" size = 32>
			<br>
			<br>
			<br>
			Message body:
		    <input type="text" name="Message" style="height:50px;font-size:14pt;width:200px" >
        	<input type="submit" value="send">
      	</form>
	</div>

	<div class="followers"color="black">
		<form action=addFollower.php method="Post">
			Follow:
		    <input type="text" name="additionFollower">
			<input type="submit" value="send">
      	</form>

      	<form action=removeFollower.php method="Post">
			Remove follower:
		    <input type="text" name="removalFollower">
			<input type="submit" value="send">
      	</form>
	</div>

	<div class="Messages"color="black">
		<form action=followerMessages.php method="Post">
			<input type="text" name="followerMessage">
			<input type="submit" value="View Messages of thoes I follow">
      	</form>
      	<br>
	</div>









	<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>
        <a href = cancelation.php id ="cancelation">cancel account</a>	
    
  </body>
</html>
