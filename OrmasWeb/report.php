<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
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
	
	
	$form_string = " 
					<script>
							$('#datepicker').datepicker({
							format: 'dd.mm.yyyy',
							autoclose: true,
							todayHighlight: true,
							language: 'ru'
								});
							$('#datepicker').datepicker('setDate', new Date());
						</script>
					<div class='form-body'>
					<form method='post' id = 'report-form'>
						<div class='form-title'>
							<label>Отчеты</label>
						</div>
						<input type='hidden' name='employee' value='".$_SESSION['id']."'/>
						<input type='hidden' name='currency' value='".$currency_id."'/>
						<div class='form-content'>
							<div class='close-bar'>
								<!--<div class='close-img'>
								</div>-->
							</div>
							<div class='my-row'>
								<div>
									<input id='datepicker' width='276' name='datepicker'/>
								</div>
							</div>
							<div class='from-submit'>
								<input class='form-submit' type='button' onclick='Report()' id='sub-button' value='Показать' id='rep-button'/>
							<div>
						</form>
					</div>";
	echo ($form_string);
?>
