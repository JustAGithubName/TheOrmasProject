<?php
	require_once 'logsql.php';
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title><?php echo($PageTitle)?></title>
		<?php 
			if (function_exists('customPageHeader'))
			{
				customPageHeader();
			}
		?>
	</head>
	<body>
		<nav class="nav navbar navbar-expand-lg  bg-light">
			<div class="action-bar container-fluid">
				<div class="logo">
					<a class="" href="exit.php">
						ORMAS
					</a>
					
				</div>
				<div class="collapse navbar-collapse" id="navbarNav">
					<ul class="navbar-nav ml-auto">
						<?php 
							/*if(!empty($_SESSION['name']) and !empty($_SESSION['surname']) and !empty($_SESSION['password']) and !empty($_SESSION['role_id']))
							{
								echo"<div class'user-img-div'></div>";
							}*/
						?>
						<div class="action-bar-content">
							<?php
								if(!empty($_SESSION['name']) and !empty($_SESSION['surname']) and !empty($_SESSION['password']) and !empty($_SESSION['role_id']))
								{	
									echo("<li class='nav-item'><a class='nav-link'  href='exit.php'>".$_SESSION['name']." ".$_SESSION['surname']."</a></li>");
								}
								else
								{
									//if($PageTitle != "Регистрация")
									//echo("<li class='nav-item'><span class='glyphicon glyphicon-envelope'></span><a class='nav-link' href='registration.php'>Регистрация</a></li>");
								}
							?>
						</div>
					</ul>
				</div>
			</div>
			
		</nav>