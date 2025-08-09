<?php
	session_start();
?> 

<?php
	$message_user="";
	$message_phone="";
	$message_address="";
	$message_firm="";
	$message_location="";
	$message_password="";
	
	if(isset($_POST['name']) && isset($_POST['surname']) && isset($_POST['email']) && isset($_POST['phone']) && isset($_POST['address']) && isset($_POST['firm']) && isset($_POST['password']))
	{
		if(($_POST['name'] == '') || ($_POST['surname'] == '') || ($_POST['phone'] == '') || ($_POST['address']  == '') || ($_POST['firm'] == '') || ($_POST['password'] == ''))
		{
			unset($_POST['name']);
			unset($_POST['surname']);
			unset($_POST['email']);
			unset($_POST['phone']);
			unset($_POST['address']);
			unset($_POST['firm']);
			unset($_POST['number']);
			unset($_POST['password']);
		}
		else
		{
			//get id
			$id_result = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
			$id_row = pg_fetch_array($id_result, null, PGSQL_BOTH);
			if(!empty($id_row[0]))
			{
				$start_transaction = pg_query("BEGIN ISOLATION LEVEL SERIALIZABLE;");
				if($start_transaction)
				{
					$generated_id = $id_row[0];
					$insert_user_result = pg_query("INSERT INTO \"OrmasSchema\".users(user_id, user_email, user_name, user_surname, user_phone, user_address,
					role_id, password, activated) VALUES($generated_id,'$_POST[email]', '$_POST[name]', '$_POST[surname]','$_POST[phone]','$_POST[address]', 
					$_SESSION[role_id_client], '$_POST[password]', 'f')");
					if($insert_user_result)
					{
						$insert_client_result = pg_query("INSERT INTO \"OrmasSchema\".clients(user_id, firm, firm_number, location_id) 
						VALUES($generated_id,'$_POST[firm]', '$_POST[number]', '$_POST[location]')");
						if($insert_client_result)
						{
							$id_for_balance = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
							$id_balance = pg_fetch_array($id_for_balance, null, PGSQL_BOTH);
							$currency_result = pg_query("SELECT * FROM \"OrmasSchema\".currencies_view WHERE currency_main_trade='t'");
							$currency_row = pg_fetch_array($currency_result, null, PGSQL_BOTH);
							if(!empty($id_balance[0]) && $currency_row)
							{
								$insert_balance_result = pg_query("INSERT INTO \"OrmasSchema\".balances(balance_id, user_id, balance_value, currency_id) 
								VALUES($id_balance[0], $generated_id, 0, $currency_row[0])");
								if($insert_balance_result)
								{
									pg_query("COMMIT;");
									header("location:index.php?id=$generated_id");
								}
								else
								{
									pg_query("ROLLBACK;");
								}
							}
							else
							{
								pg_query("ROLLBACK;");
							}
						}
						else
						{
							echo "cannot insert user!";
							pg_query("ROLLBACK;");
						}
						
					}
					else
					{
						echo "cannot insert user!";
					}
				}
			}
			else
			{
				//show error
			}
		}
	}
?>

<div id = "content">
	<div class="regis-content">
		<form action="menu.php" method="post">
				<div class="for_error_messages">
					
				</div>
				<div class='close-bar'>
				</div>
				<div class="regis-main-label">Регистрация</div>
				<div class="regis-row">
					<label id="regis-label">Имя:</label>
					<input name="name" type="text" required/>
					<div class="message"><label ></label></div>
				</div>
				<div class="regis-row">
					<label id="regis-label">Фамилия:</label>
					<input name="surname" type="text" required/>
					<div class="message"><label ></label></div>
				</div>
				<div class="regis-row">
					<label id="regis-label">E-mail:</label>
					<input name="email" type="email"/>
					<div class="message"><label ></label></div>
				</div>
				<div class="regis-row">
					<label id="regis-label">Номер телефона:</label>
					<input name="phone" type="text" required/>
					<div class="message"><label ></label></div>
				</div>
				<div class="regis-row">
					<label id="regis-label">Адрес:</label>
					<input name="address"  type="text" required/>
					<div class="message"><label ></label></div>
				</div>
				
				<div class="regis-row">
					<label id="regis-label">Название фирмы(магазина):</label>
					<input name="firm" id="firm" type="text" required/>
					<div class="message"><label ></label></div>
				</div>
				
				<div class="regis-row">
					<label id="regis-label">Номер фирмы(магазина):</label>
					<input name="number"  type="text"/>
					<div class="message"><label ></label></div>
				</div>
				
				<div class="regis-row">
					<label id="regis-label">Регион:</label>
					<select name="location" id="location">
					<?php
						$location_result = pg_query("SELECT * FROM \"OrmasSchema\".locations_view");
						$location_row = pg_fetch_all($location_result);
						if(!empty($location_row[0]))
						{
							$row_count = pg_num_rows($location_result);
							for($i=0;$i<$row_count;$i++)
							{
								echo("<option value='".$location_row[$i]['location_id']."'>".$location_row[$i]['country_name'].", ".$location_row[$i]['region_name'].", ".$location_row[$i]['city_name']."</option>");
							}
						}
					?>
					</select>
					<div class="message"><label ></label></div>
				</div>
				<div class="regis-row">
					<label id="regis-label">Пароль:</label>
					<input name="password" type="password" required/>
					<div class="message"><label ></label></div>
				</div>
				<div class="regis-row">
					<div class="button-position">
						<input id="regis-button" type="submit" name="submit" value="Зарегистрироватся"/>
					</div>
				</div>
		</form>
	</div>
</div>
