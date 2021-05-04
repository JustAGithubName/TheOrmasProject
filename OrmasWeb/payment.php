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

	
	$form_string = "<script>
						$(document).ready(function() { 
							$('#selected-clinet').select2({
								placeholder: '',
								allowClear: false
							}); 
						});
					</script>
					<div id='form-body'>
					<form method='post' id = 'payment-form'>
						<div id='form-title'>
							<label>Платежы</label>
						</div>
						<input type='hidden' name='date' value='".$currentDate."'/>
						<input type='hidden' name='employee' value='".$_SESSION['id']."'/>
						<input type='hidden' name='status' value='".$status_id."'/>
						<input type='hidden' name='currency' value='".$currency_id."'/>
						<div id='form-content'>
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
							<div id='from-submit'>
								<input class='form-submit' type='submit' value='Оплатить' id='sub-button'/>
							<div>
						</form>
					</div>";
	echo ($form_string);
?>