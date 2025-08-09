<?php
	session_start();
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<meta name="author" content="Main technology Comp." />
		<meta name="robots" content="none" />
		<LINK rel="stylesheet" media="screen" type="text/css" title="Style" href="css/mainstyle.css">
		<?php
		  session_unset();
		  session_destroy();
          if(empty($_SESSION['login'])) 
          {
				echo '<script type="text/javascript"> window.location = "index.php";</script>';
          }
          	unset($_SESSION['password']);
            unset($_SESSION['login']); 
			unset($_SESSION['role']); 
            unset($_SESSION['id']);
				exit("<meta    http-equiv='Refresh' content='0;    URL=index.php'></head></html>");
		?>
