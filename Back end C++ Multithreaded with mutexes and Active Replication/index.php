<!doctype HTML>
<html>
<!-- This is where i shall code in CSS!!!! -->
	<style>
	.blueBackground{
		color:white;
		background-color: lightblue;
	}
	.login{
		
		width:  400px;
		color: black;
		padding: 5px;
		border: 5px lightblue;
		margin: 5px;

		background-color: rgba(255, 0, 0, 0.0);
		
		position: absolute;
	    left: 500px;
	    top: 600px;
	}
	.credientials{
		
		width:  400px;
		color: black;
		padding: 5px;
		border: 5px lightblue;
		margin: 5px;

		background-color: rgba(255, 255, 255, 0.0);
		
		border:black;
		
		position: absolute;
	    left: 500px;
	    top: 350px;
	}
	.img{
		background-color: rgba(255, 0, 0, 0.3);
	}
	input{
		border: 1px solid black;
	}
	input:hover{
		border: 1px solid blue;
	}
	</style>
	<!--expirmenting with a little java script.................-->

	
	<head>

		<title>Giraffer</title>
		<meta charset="UTF-8">
		<link rel="icon" href="bluegiraffe.ico" />
	</head>

	<body class = "blueBackground">
	<?php
		setcookie("Username"); //should destroy cookies on logout!!!
		setcookie("Password");
	?>

	
		<h1 class = "blueBackground">
			Welocme to Giraffer
			<br>
			<br>
		</h1>
			<h1>
	Reach out! Stand out! Be Heard!
	</h1>


	<img src= "bluegiraffe.png" alt="A giraffe..." width= "400" height ="800" href="img">

	<!--Users who log in. They will need passwords. They may want to cancel their accounts.-->
	<div class="login"color="black">
 <form action=checkLogin.php method="Post" name = "loginForm">
        Username:<br>
        <input type="text" name="Username"><br>
        Password:<br>
        <input type="password" name="Password"><br>
        <input type="submit" value="Login">
  </form>
	</div>

	<br>
	<br>
	
	<div class="credientials"color="black">
		<form action=userinfo.php method="Post">
        Full Name:<br>
        <input type="text" name="fullName"><br>
        Your Email:<br>
        <input type="text" name="email"><br>
        New Password:<br>
        <input type="password" name="newPassword"><br>
        Gender<br>
        <select>
        	<option value = "Select">Select</option>
          	<option value = "Male">Male</option>
        	<option value = "Female">Female</option>
        </select>
        <br>
        Date of Birth<br>
        <select>
        	<option value = "Jan">Jan</option>
          	<option value = "Feb">Feb</option>
        	<option value = "Mar">Mar</option>
        	<option value = "Apr">Apr</option>
        	<option value = "May">May</option>
        	<option value = "Jun">Jun</option>
        	<option value = "Jul">Jul</option>
        	<option value = "Aug">Aug</option>
        	<option value = "Sep">Sep</option>
        	<option value = "Oct">Oct</option>
        	<option value = "Nov">Nov</option>
        	<option value = "Dec">Dec</option>
        </select>

        <select>
        	<option value = "one">1</option>
          	<option value = "two">2</option>
        	<option value = "three">3</option>
        	<option value = "Four">4</option>
        	<option value = "five">5</option>
        	<option value = "six">6</option>
        	<option value = "seven">7</option>
        	<option value = "eight">8</option>
        	<option value = "nine">9</option>
        	<option value = "ten">10</option>
        	<option value = "eleven">11</option>
        	<option value = "twelve">12</option>
        	<option value = "thirteen">13</option>
        	<option value = "fourteen">14</option>
        	<option value = "fiften">15</option>
        	<option value = "sixteen">16</option>
        	<option value = "seventeen">17</option>
        	<option value = "eighteen">18</option>
        	<option value = "nighteen">19</option>
        	<option value = "twenty">20</option>
        	<option value = "twentyone">21</option>
        	<option value = "twentytwo">22</option>
        	<option value = "twentythree">23</option>
        	<option value = "twentyfour">24</option>
        	<option value = "twentyfive">25</option>
        	<option value = "twentysix">26</option>
        	<option value = "twentyseven">27</option>
        	<option value = "twentyeight">28</option>
        	<option value = "twentynine">29</option>
        	<option value = "thirty">30</option>
        	<option value = "thirtyone">31</option>
        </select>

        <!--Didnt feel like putting a select here after finishing the days.....-->
		<input type="text" name="year" >
		<br>
        

        <input type="submit" value="Sign up" color = "darkGreen">
      </form>
	</div>

	<div href="credientials" color="black">
		
	</div>
	<br>



	</body>

</html>

