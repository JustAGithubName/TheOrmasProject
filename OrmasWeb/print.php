<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
	$string_out = $string_out."<div class='modal' id='modal'><div class='modal-header'><a fref='#' onclick='CloseModal()'><div class='colse-modal'></div></a></div><div class='modal-content' id='modal-content'>";
	$query_company = "SELECT * FROM \"OrmasSchema\".companies_view";
	$result_company = pg_query($query_company);
	$company_row = pg_fetch_array($result_company);
	if(!$company_row)
	{
		$string_out = $string_out."Ошибка! Оюратитесь к администратору.";
	}
	if(isset($_POST['consume-id']))
	{	
		$query_prod_cons = "SELECT * FROM \"OrmasSchema\".consume_products_view WHERE consume_product_id=".$_POST['consume-id'];
		$result_prod_cons = pg_query($query_prod_cons);
		if(!$result_prod_cons)
		{
			$string_out = $string_out."Ошибка! Оюратитесь к администратору.";
		}
		else
		{
			$cons_row = pg_fetch_array($result_prod_cons);
			$query_cons_list = "SELECT * FROM \"OrmasSchema\".consume_product_list_view WHERE consume_product_id=".$_POST['consume-id'];
			$result_cons_list = pg_query($query_cons_list);
			if(!$result_cons_list)
			{
				$string_out = $string_out."Ошибка! Оюратитесь к администратору.";
			}
			else
			{
				$count=0;
				$false_sum=0;
				$string_out = $string_out."<div id='report-header' >
					<div id='report-name'>
						<b>Накладная</b><b> №</b><b>".$_POST['consume-id']."</b>
					</div>
					<div id='report-period' ><b>
						на ".$cons_row['consume_product_date']
					."</b></div>
				</div>
				<div id = 'row'>
					Предприятие получатель: ".$company_row['company_name']."
				</div>
				</br>
				<div id = 'row'>
					Представитель получателя: ".$cons_row['employee_name']." ".$cons_row['employee_surname']."
				</div>
				</br>
				<div id = 'row'>
					Предприятие отправитель: ".$company_row['company_name']."
				</div>
				</br>
				<div id = 'row'>
					Представитель отправителя: ".$cons_row['stock_employee_name']." ".$cons_row['stock_employee_name']."
				</div>
				</br></br>
				<div id='content'>
					<table width='100%' border = 1px  cellpadding=5 style='border-spacing:0px;'>
						<th><b>№ п/п</b></th>
						<th><b>Наименование</b></th>
						<th><b>Ед. изм.</b></th>
						<th><b>Количество</b></th>
						<th><b>Цена</b></th>
						<th><b>Сумма</b></th>
						<th><b>Валюта</b></th>";
				while ($row = pg_fetch_array($result_cons_list)) {
					$price_result=pg_query("SELECT * FROM \"OrmasSchema\".products_view where product_id = ".$row['product_id']." ORDER BY product_id DESC;");
					$price_row = pg_fetch_array($price_result);
					$counter++;
					$count=$row['count']+0;
					$sum=($price_row['price']+0)*($row['count']+0);
					$price=$price_row['price']+0;
					$false_sum = $false_sum +$sum;
					$string_out = $string_out."<tr><td>".$counter."</td>
						<td>".$row['product_name']."</td>
						<td>".$row['measure_name']."</td>
						<td>".$count."</td>
						<td>".$sum/$count."</td>
						<td>".$sum."</td>
						<td>".$row['sum_currency_name']."</td><tr>";
					$count=0;
					$sum=0;
					$price=0;
				}
				$total_sum=$false_sum+0;
					$string_out = $string_out."</table>
				</div>
				</br></br>
				<div id = 'row'>
					На сумму: <b>".$total_sum."  ".$cons_row['currency_name']."</b> 
				</div>
				</br>
				<div id = 'row'>
					Получатель: _________________ (подпись)                  Отправитель: ______________________(подпись)
				</div>
				</br>
				<div id = 'row'>
					Главный бухгалтер: ____________________________ (подпись)
				</div>
				</br>
				<div id = 'row'>
					Руководитель: __________________________ (подпись)
				</div>";
			}
		}
	}
	if(isset($_POST['order-id']))
	{	
		$query_order = "SELECT * FROM \"OrmasSchema\".orders_view WHERE order_id=".$_POST['order-id'];
		$result_order = pg_query($query_order);
		if(!$result_order)
		{
			$string_out = $string_out."Ошибка! Оюратитесь к администратору.";
		}
		else
		{
			$order_row = pg_fetch_array($result_order);
			$query_order_list = "SELECT * FROM \"OrmasSchema\".order_list_view WHERE order_id=".$_POST['order-id'];
			$result_order_list = pg_query($query_order_list);
			if(!$result_order_list)
			{
				$string_out = $string_out."Ошибка! Оюратитесь к администратору.";
			}
			else
			{
				$count=0;
				$string_out = $string_out."<div id='report-header' >
					<div id='report-name'>
						<b>Накладная</b><b> №</b><b>".$_POST['order-id']."</b>
					</div>
					<div id='report-period' ><b>
						на ".$order_row['order_date']
					."</b></div>
				</div>
				<div id = 'row'>
					Предприятие получатель: ".$order_row['client_firm']."
				</div>
				</br>
				<div id = 'row'>
					Представитель получателя: ".$order_row['client_name']." ".$order_row['client_surname']."
				</div>
				</br>
				<div id = 'row'>
					Предприятие отправитель: ".$company_row['company_name']."
				</div>
				</br>
				<div id = 'row'>
					Представитель отправителя: ".$order_row['employee_name']." ".$order_row['employee_surname']."
				</div>
				</br></br>
				<div id='content'>
					<table width='100%' border = 1px  cellpadding=5 style='border-spacing:0px;'>
						<th><b>№ п/п</b></th>
						<th><b>Наименование</b></th>
						<th><b>Ед. изм.</b></th>
						<th><b>Количество</b></th>
						<th><b>Цена</b></th>
						<th><b>Сумма</b></th>
						<th><b>Валюта</b></th>";
				while ($row = pg_fetch_array($result_order_list)) {
					$counter++;
					$count=$row['count']+0;
					$sum=$row['sum']+0;
					$price=$row['price']+0;
					$string_out = $string_out."<tr><td>".$counter."</td>
						<td>".$row['product_name']."</td>
						<td>".$row['measure_name']."</td>
						<td>".$count."</td>
						<td>".$sum/$count."</td>
						<td>".$sum."</td>
						<td>".$row['sum_currency_name']."</td><tr>";
					$count=0;
					$sum=0;
					$price=0;
				}
				$total_sum=$order_row['sum']+0;
					$string_out = $string_out."</table>
				</div>
				</br></br>
				<div id = 'row'>
					На сумму: <b>".$total_sum."  ".$order_row['currency_name']."</b> 
				</div>
				</br>
				<div id = 'row'>
					Получатель: _________________ (подпись)                  Отправитель: ______________________(подпись)
				</div>
				</br>
				<div id = 'row'>
					Главный бухгалтер: ____________________________ (подпись)
				</div>
				</br>
				<div id = 'row'>
					Руководитель: __________________________ (подпись)
				</div>";
			}
		}
	}
	if(isset($_POST['return-id']))
	{
		$query_return = "SELECT * FROM \"OrmasSchema\".returns_view WHERE return_id=".$_POST['return-id'];
		$result_return = pg_query($query_return);
		if(!$result_return)
		{
			$string_out = $string_out."Ошибка! Оюратитесь к администратору.";
		}
		else
		{
			$return_row = pg_fetch_array($result_return);
			$query_return_list = "SELECT * FROM \"OrmasSchema\".return_list_view WHERE return_id=".$_POST['return-id'];
			$result_return_list = pg_query($query_return_list);
			if(!$result_return_list)
			{
				$string_out = $string_out."Ошибка! Оюратитесь к администратору.";
			}
			else
			{
				$count=0;
				$string_out = $string_out."<div id='report-header' >
					<div id='report-name'>
						<b>Накладная</b><b> №</b><b>".$_POST['return-id']."</b>
					</div>
					<div id='report-period' ><b>
						на ".$return_row['order_date']
					."</b></div>
				</div>
				<div id = 'row'>
					Предприятие получатель: ".$company_row['company_name']."
				</div>
				</br>
				<div id = 'row'>
					Представитель получателя: ".$return_row['employee_name']." ".$return_row['employee_surname']."
				</div>
				</br>
				<div id = 'row'>
					Предприятие отправитель: ".$return_row['client_firm']."
				</div>
				</br>
				<div id = 'row'>
					Представитель отправителя: ".$return_row['client_name']." ".$return_row['client_surname']."
				</div>
				</br></br>
				<div id='content'>
					<table width='100%' border = 1px  cellpadding=5 style='border-spacing:0px;'>
						<th><b>№ п/п</b></th>
						<th><b>Наименование</b></th>
						<th><b>Ед. изм.</b></th>
						<th><b>Количество</b></th>
						<th><b>Цена</b></th>
						<th><b>Сумма</b></th>
						<th><b>Валюта</b></th>";
				while ($row = pg_fetch_array($result_return_list)) {
					$counter++;
					$count=$row['count']+0;
					$sum=$row['sum']+0;
					$price=$row['price']+0;
					$string_out = $string_out."<tr><td>".$counter."</td>
						<td>".$row['product_name']."</td>
						<td>".$row['measure_name']."</td>
						<td>".$count."</td>
						<td>".$sum/$count."</td>
						<td>".$sum."</td>
						<td>".$row['sum_currency_name']."</td><tr>";
					$count=0;
					$sum=0;
					$price=0;
				}
				$total_sum=$return_row['sum']+0;
					$string_out = $string_out."</table>
				</div>
				</br></br>
				<div id = 'row'>
					На сумму: <b>".$total_sum."  ".$return_row['currency_name']."</b>
				</div>
				</br>
				<div id = 'row'>
					Получатель: _________________ (подпись)                  Отправитель: ______________________(подпись)
				</div>
				</br>
				<div id = 'row'>
					Главный бухгалтер: ____________________________ (подпись)
				</div>
				</br>
				<div id = 'row'>
					Руководитель: __________________________ (подпись)
				</div>";
			}
		}
	}
	if(isset($_POST['order-raw-id']))
	{
		$query_order_raw = "SELECT * FROM \"OrmasSchema\".order_raws_view WHERE order_raw_id=".$_POST['order-raw-id'];
		$result_order_raw = pg_query($query_order_raw);
		if(!$result_order_raw)
		{
			$string_out = $string_out."Ошибка! Оюратитесь к администратору.";
		}
		else
		{
			$order_raw_row = pg_fetch_array($result_order_raw);
			$query_order_raw_list = "SELECT * FROM \"OrmasSchema\".order_raw_list_view WHERE order_raw_id=".$_POST['order-raw-id'];
			$result_order_raw_list = pg_query($query_order_raw_list);
			if(!$result_order_raw_list)
			{
				$string_out = $string_out."Ошибка! Оюратитесь к администратору.";
			}
			else
			{
				$count=0;
				$string_out = $string_out."<div id='report-header' >
					<div id='report-name'>
						<b>Накладная</b><b> №</b><b>".$_POST['order-raw-id']."</b>
					</div>
					<div id='report-period' ><b>
						на ".$order_raw_row['order_raw_date']
					."</b></div>
				</div>
				<div id = 'row'>
					Предприятие получатель: ".$company_row['company_name']."
				</div>
				</br>
				<div id = 'row'>
					Представитель получателя: ".$order_raw_row['employee_name']." ".$order_raw_row['employee_surname']."
				</div>
				</br>
				<div id = 'row'>
					Предприятие отправитель: ".$order_raw_row['purveyor_company_name']."
				</div>
				</br>
				<div id = 'row'>
					Представитель отправителя: ".$order_raw_row['purveyor_name']." ".$order_raw_row['purveyor_surname']."
				</div>
				</br></br>
				<div id='content'>
					<table width='100%' border = 1px  cellpadding=5 style='border-spacing:0px;'>
						<th><b>№ п/п</b></th>
						<th><b>Наименование</b></th>
						<th><b>Ед. изм.</b></th>
						<th><b>Количество</b></th>
						<th><b>Цена</b></th>
						<th><b>Сумма</b></th>
						<th><b>Валюта</b></th>";
				while ($row = pg_fetch_array($result_order_raw_list)) {
					$counter++;
					$count=$row['count']+0;
					$sum=$row['sum']+0;
					$price=$row['price']+0;
					$string_out = $string_out."<tr><td>".$counter."</td>
						<td>".$row['product_name']."</td>
						<td>".$row['measure_name']."</td>
						<td>".$count."</td>
						<td>".$sum/$count."</td>
						<td>".$sum."</td>
						<td>".$row['sum_currency_name']."</td><tr>";
					$count=0;
					$sum=0;
					$price=0;
				}
				$total_sum=$order_raw_row['sum']+0;
					$string_out = $string_out."</table>
				</div>
				</br></br>
				<div id = 'row'>
					На сумму: <b>".$total_sum."  ".$order_raw_row['currency_name']."</b>
				</div>
				</br>
				<div id = 'row'>
					Получатель: _________________ (подпись)                  Отправитель: ______________________(подпись)
				</div>
				</br>
				<div id = 'row'>
					Главный бухгалтер: ____________________________ (подпись)
				</div>
				</br>
				<div id = 'row'>
					Руководитель: __________________________ (подпись)
				</div>";
			}
		}
	}
	$string_out = $string_out."</div><div class='modal-footter'><button class='modal-button' onclick='SentToPrinter()'>Печать</button><button class='modal-button' onclick='CloseModal()'>Закрыть</button></div></div>";
	echo $string_out;
?>