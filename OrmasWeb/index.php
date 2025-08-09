<?php
	session_start();
	$PageTitle="Ormas";
	function customPageHeader()
	{
		echo ("<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />");
		echo ("<meta name='keywords' content='Ormas, oreder mamagement system, order' />");
		echo ("<meta name='description' content='Oreder mamagement system' />");
		echo ("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
		echo ("<meta name='author' content='Main technology Comp.' />");
		echo ("<meta name='robots' content='all' />");
		echo ("<LINK rel='stylesheet' media='screen' type='text/css' href='css/bootstrap.css'/>");
		echo ("<LINK rel='stylesheet' media='screen' type='text/css' title='Style' href='css/mainstyle.css'>");
		echo ("<script type='text/javascript' src='js/bootstrap.js'></script>");
	}	
	require_once ('header.php');
	$query = "SELECT * FROM \"OrmasSchema\".roles_view";
	$result = pg_query($query);
	for($i = 0 ; $i < pg_num_rows($result); $i++)
	{
		$role_row = pg_fetch_array($result, null, PGSQL_BOTH);
		if($role_row['role_name'] == "CLIENT")
		{
			$_SESSION['role_id_client']=$role_row['role_id']; 
		}
		if($role_row['role_name'] == "EXPEDITOR")
		{
			$_SESSION['role_id_expeditor']=$role_row['role_id']; 
		}
		if($role_row['role_name'] == "STOCK INSPECTOR")
		{
			$_SESSION['role_id_stock_inspector']=$role_row['role_id']; 
		}
		if($role_row['role_name'] == "PURVEYOR MANEGER")
		{
			$_SESSION['role_id_purveyor_manager']=$role_row['role_id']; 
		}
		if($role_row['role_name'] == "PURVEYOR")
		{
			$_SESSION['role_id_purveyor']=$role_row['role_id']; 
		}
	}
?> 


<?php
if(!empty($_SESSION['name']) and !empty($_SESSION['surname']) and !empty($_SESSION['id']) and !empty($_SESSION['role']))
    {
        $name    = $_SESSION['name'];
		$surname    = $_SESSION['surname'];
		$role_id = $_SESSION['role_id'];
		$id = $_SESSION['id'];
		$phone    = $_SESSION['phone'];
	}
	 $message="";
?>

<?php
	if (isset($_GET['id']))
	{
		if($_GET['id'] != 0)
		{
			$user_result = pg_query("SELECT * FROM \"OrmasSchema\".users_view WHERE user_id=$_GET[id]");
			$user_row = pg_fetch_array($user_result, null, PGSQL_BOTH);
			if(!empty($user_row[0]))
			{
				$message = "Вы успешно зарегистрированы! Ваш ID: $_GET[id], ждите активации.";
			}
		}
	}
?>
<?php
unset($_SESSION['password']);
unset($_SESSION['login']); 
unset($_SESSION['role']); 
unset($_SESSION['id']);
unset($_SESSION['phone']);

if (isset($_POST['phone']) && isset($_POST['password'])) 
{ 
	$phone = $_POST['phone']; 
    $password=$_POST['password'];
   
	if ($phone == '' && $password =='')
	{unset($phone); unset($password); }
	if (empty($phone) or empty($password))
    {    
		$message="Вы ввели не всю информацию!";
    }
    else
	{
		$phone = stripslashes($phone);
		$phone = htmlspecialchars($phone);
		$password = stripslashes($password);
		$password = htmlspecialchars($password);
		//удаляем лишние пробелы
		$phone = trim($phone);
		$password = trim($password);
		$query = "SELECT * FROM \"OrmasSchema\".users_view WHERE user_phone='$phone'";
		$result = pg_query($query); //извлекаем из базы все данные о пользователе с введенным логином
	
		$user_row = pg_fetch_array($result, null, PGSQL_BOTH);
	
		if (!$result)
		{  
			$message="Введённый Вами номер телефона, e-mail или пароль неверный.";
		}
		else 
		{
			if ($user_row['password']==$password) 
			{
   		 		if($user_row['activated'] == 't')
				{
					$_SESSION['name']=$user_row['user_name']; 
					$_SESSION['surname']=$user_row['user_surname']; 
					$_SESSION['id']=$user_row['user_id'];
					$_SESSION['role_id']=$user_row['role_id'];
					$_SESSION['password']=$user_row['password'];
					$_SESSION['phone']=$user_row['user_phone'];
					echo '<script type="text/javascript"> window.location = "menu.php";</script>';
				}
				else
				{
					$message = "Ваш акаунт не активирован, ждите активации.";	
				}
			}
 			else {
   				$message = "Извините, введённый Вами номер телефона, e-mail или пароль неверный!";
			}
		}	
	}
}
?>

<div class = "row content">
	<div class = "container login">
		<div class = "login-logo">
		</div>
		<div class = "login-content">
			<form action="index.php" method="post">
				<p>
					<label>Номер телефона:<br></label>
					<input name="phone" type="text" placeholder="Например: 991010022"> 
				</p>
				<p>
					<label>Пароль:<br></label>
					<input name="password" type="password" >
				</p>
				<p>
				<input class = "submit" type="submit" name="submit" value="Войти"/>
				<br>
			</form>
		</div>
		<div class = "message">
			<span><?php echo $message?></span>
		</div>
	</div>
</div>
<?php
	require_once('footter.php')
?>