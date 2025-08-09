<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
	$status_result= pg_query("SELECT status_id FROM \"OrmasSchema\".status_view where status_name = 'TO PAY'");
	$status_row = pg_fetch_row($status_result);
	$status_id ="";
	if(!empty($status_row[0]))
	{
		$status_id = $status_row[0];
	}

	$currency_result= pg_query("SELECT currency_id FROM \"OrmasSchema\".currencies_view where currency_short_name = 'TJS'");
	$currency_row = pg_fetch_all($currency_result);
	$currency_id ="";
	if(!empty($currency_row[0]))
	{
		
		$row_count = pg_num_rows($currency_result);
		for($i=0;$i<$row_count;$i++)
		{
			$currency_id = $currency_row[$i]['currency_id'];
		}
	}
	
	$status_result= pg_query("SELECT \"OrmasSchema\".getcurrentdate()");
	$status_row = pg_fetch_row($status_result);
	$currentDate = $status_row[0];
	
	$query_client = "SELECT user_id_2 FROM \"OrmasSchema\".relations_view WHERE user_id_1=".$_SESSION['id'];			
	$result_clinet = pg_query($query_client);
	$client_options = "";
	while ($row_user = pg_fetch_array($result_clinet)) {
		$query = "SELECT user_id, user_name, user_surname, user_phone, city_name, user_address, firm	 FROM \"OrmasSchema\".clients_view WHERE user_id=".$row_user[0];			
		$result = pg_query($query);
		while ($row = pg_fetch_array($result)) {
			$client_options .= "<option value='".$row[0]."'>".$row[1].", ".$row[2].", ".$row[3].", ".$row[6]."</option>";
		}
	}

	$query_current_branch = "SELECT * FROM \"OrmasSchema\".company_employee_view WHERE employee_id=".$_SESSION['id'];			
	$result_cahsier_branch = pg_query($query_current_branch);
	$result_br = pg_fetch_array($result_cahsier_branch);
	$current_branch = $result_br['branch_id'];
	
	$query_cashier_role = "SELECT * FROM \"OrmasSchema\".roles WHERE role_name='CASHIER'";			
	$result_cahsier_role = pg_query($query_cashier_role);
	$cashier_id=0;
	$chashbox_id=0;
	$chashbox_account_id=0;
	if($current_cashier_role > 0 && $current_branch > 0)
	{
		$query_cashier = "SELECT * FROM \"OrmasSchema\".user_branch_view WHERE role_id=".$current_cashier_role;			
		$result_cahsier = pg_query($query_cashier);
		while ($row_cashier = pg_fetch_array($result_cahsier)) {
			if(!empty($row_cashier['branch_id']))
			{
				if($row_cashier['branch_id'] == $current_branch)
				{				
					$cashier_id = $row_cashier['user_id'];
					break;
				}
			}
		}
		
		$chashbox_id=0;
		$query_cashier_id = "SELECT * FROM \"OrmasSchema\".cashbox_employee WHERE employee_id=".$cashier_id;
		$result_cahsier_id = pg_query($query_cashier_id);
		$result_cash_id  = pg_fetch_row($result_cahsier_id);
		$chashbox_id = $result_cash_id[1];
				
		if($chashbox_id > 0)
		{
			$query_cashier_acc_id = "SELECT * FROM \"OrmasSchema\".cashbox_view WHERE cashbox_id=".$chashbox_id;
			$result_cahsier_acc_id = pg_query($query_cashier_acc_id);
			$result_cash_account_id  = pg_fetch_row($result_cahsier_acc_id);
			$chashbox_account_id = $result_cash_account_id[4];
			if($chashbox_account_id > 0)
			{
				
			}
		}
		else
		{
			
		}
	}
	else
	{
		
	}
	
	
	$form_string = "<script>
						$(document).ready(function() { 
							$('#selected-clinet').select2({
								placeholder: '',
								allowClear: false
							}); 
						});
					</script>
					<div class='form-body'>
					<form method='post' class = 'payment-form' id='payment-form'>
						<div class='form-title'>
							<label>Платежы</label>
						</div>
						<input type='hidden' name='date' value='".$currentDate."'/>
						<input type='hidden' name='employee' value='".$_SESSION['id']."'/>
						<input type='hidden' name='status' value='".$status_id."'/>
						<input type='hidden' name='currency' value='".$currency_id."'/>
						<input type='hidden' name='cash_subaccount' value='".$chashbox_account_id."'/>
						<input type='hidden' name='target' value='Приход от продажи товаров или услуг'/>
						<input type='hidden' name='who' value='".$_SESSION['surname']." ".$_SESSION['name']."'/>
						<div class='form-content'>
							<div class='my-row'>
								<div class='float-left'>
									<label class='float-left form-label'>Виберите клиента:</label>
									<select class='form-client' name='selected_clinet' id='selected-clinet'>
									".$client_options."
									</select>
								</div>
							</div>
							<div class='close-bar'>
								<!--<div class='close-img'>
								</div>-->
							</div>
							<div class='my-row'>
								<div>
									<label class='float-left form-label'>Сумма к оплате:</label>
									<input class ='form-count' type='number' min='0' name='value' id='value' step='.01'/>
								</div>
							</div>
							<div class='from-submit'>
								<input class='form-submit' type='submit' value='Оплатить' id='sub-button'/>
							<div>
						</form>
					</div>
					<script>
						$('form').submit(function(){
							$('input[type=submit]', this).attr('disabled', 'disabled');
						});
					</script>";
	echo ($form_string);
?>