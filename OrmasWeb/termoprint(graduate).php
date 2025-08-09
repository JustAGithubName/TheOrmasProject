<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
	$string_out = $string_out."<div class='modal-auto modal-text' id='modal-auto' ><div class='modal-header'><a fref='#' onclick='CloseModalAuto()'><div class='colse-modal'></div></a></div><div class='modal-content' id='modal-content'>";
	$query_company = "SELECT * FROM \"OrmasSchema\".companies_view";
	$result_company = pg_query($query_company);
	$company_row = pg_fetch_array($result_company);
	if(!$company_row)
	{
		$string_out = $string_out."Ошибка! Оюратитесь к администратору.";
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
			$query_order_list = "SELECT order_list_id, order_id, order_list_view.product_name, order_list_view.price, currency_name, order_list_view.volume, ( SELECT measures.measure_short_name FROM \"OrmasSchema\".measures WHERE measures.measure_id = p.measure_id) AS measure_short_name,count,sum, sum_currency_name, status_name, order_list_view.product_id, status_id, order_list_view.currency_id FROM \"OrmasSchema\".order_list_view LEFT JOIN \"OrmasSchema\".products p ON p.product_id = order_list_view.product_id WHERE order_id=".$_POST['order-id'];
			$result_order_list = pg_query($query_order_list);
			if(!$result_order_list)
			{
				$string_out = $string_out."Ошибка! Оюратитесь к администратору.";
			}
			else
			{
				$count=0;
				$string_out = $string_out."<div id='report-header' >
					<div id='report-name' style='font-family:\" Graduate\", Graduate, monospace; font-size:200%'>
						<b>Накладная</b><b> №</b><b>".$_POST['order-id']."</b>
					</div>
					<div id='report-period' style='font-family:\" Graduate\", Graduate, monospace; font-size:150%'><b>
						на ".$order_row['order_date']
					."</b></div>
				</div>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:120%'>
					Предприятие получатель: ".$order_row['client_firm']."
				</div>
				</br>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:120%'>
					Представитель получателя: ".$order_row['client_name']." ".$order_row['client_surname']."
				</div>
				</br>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:120%'>
					Предприятие отправитель: ".$company_row['company_name']."
				</div>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:120%'>
					Контактный телефон: ".$company_row['company_phone']."
				</div>
				</br>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:120%'>
					Представитель отправителя: ".$order_row['employee_name']." ".$order_row['employee_surname']."
				</div>
				</br></br>
				<div id='content'>
					<table style='font-family:\" Graduate\", Graduate, monospace; font-size:170%' class='reset-style simple'  border = 0px  cellpadding=5 style='border-spacing:0px;'>
						<th class='simple-data-print'><b>Наименование</b></th>
						<th class='simple-data-print'><b>Цена</b></th>
						<th class='simple-data-print'><b>Кол.</b></th>
						";
				while ($row = pg_fetch_array($result_order_list)) {
					$counter++;
					$count=$row['count']+0;
					$sum=$row['sum']+0;
					$price=$row['price']+0;
					$string_out = $string_out."<tr class='simple-data-print'><td class='simple-data-print'><b>".$row['product_name']."</b></td>
						<td class='simple-data-print'><b>".$sum/$count."</b></td>
						<td class='simple-data-print'><b>".$count." ".$row['measure_short_name']."</b></td>
						";
					$count=0;
					$sum=0;
					$price=0;
				}
				$total_sum=$order_row['sum']+0;
					$string_out = $string_out."</table>
				</div>
				</br></br>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:200%'>
					На сумму: <b>".$total_sum."  ".$order_row['currency_name']."</b> 
				</div>
				</br>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:130%'>
					Получатель: _________________ (подпись)
				</div>
				</br>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:130%'>
					Отправитель: ______________________(подпись)
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
			$query_return_list = "SELECT return_list_id, return_id, return_list_view.product_name, return_list_view.price, currency_name, return_list_view.volume, ( SELECT measures.measure_short_name FROM \"OrmasSchema\".measures WHERE measures.measure_id = p.measure_id) AS measure_short_name,count,sum, sum_currency_name, status_name, return_list_view.product_id, status_id, return_list_view.currency_id FROM \"OrmasSchema\".return_list_view LEFT JOIN \"OrmasSchema\".products p ON p.product_id = return_list_view.product_id WHERE return_id=".$_POST['return-id'];
			$result_return_list = pg_query($query_return_list);
			if(!$result_return_list)
			{
				$string_out = $string_out."Ошибка! Оюратитесь к администратору.";
			}
			else
			{
				$count=0;
				$string_out = $string_out."<div id='report-header' >
					<div id='report-name' style='font-family:\" Graduate\", Graduate, monospace; font-size:200%'>
						<b>Накладная</b><b> №</b><b>".$_POST['return-id']."</b>
					</div>
					<div id='report-period' style='font-family:\" Graduate\", Graduate, monospace; font-size:150%'><b>
						на ".$return_row['return_date']
					."</b></div>
				</div>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:120%'>
					Предприятие получатель: ".$company_row['company_name']."
				</div>
				</br>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:120%'>
					Представитель получателя: ".$return_row['employee_name']." ".$return_row['employee_surname']."
				</div>
				</br>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:120%'>
					Предприятие отправитель: ".$return_row['client_firm']."
				</div>
				</br>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:120%'>
					Представитель отправителя: ".$return_row['client_name']." ".$return_row['client_surname']."
				</div>
				</br></br>
				<div id='content'>
					<table style='font-family:\" Graduate\", Graduate, monospace; font-size:170%' class='reset-style simple'  border = 0px  cellpadding=5 style='border-spacing:0px;'>
						<th class='simple-data-print'><b>Наименование</b></th>
						<th class='simple-data-print'><b>Цена</b></th>
						<th class='simple-data-print'><b>Кол.</b></th>
						";
				while ($row = pg_fetch_array($result_return_list)) {
					$counter++;
					$count=$row['count']+0;
					$sum=$row['sum']+0;
					$price=$row['price']+0;
					$string_out = $string_out."<tr class='simple-data-print'><td class='simple-data-print'>".$row['product_name']."</td>
						<td class='simple-data-print'>".$sum/$count."</td>
						<td class='simple-data-print'>".$count." ".$row['measure_short_name']."</td>
						";
					$count=0;
					$sum=0;
					$price=0;
				}
				$total_sum=$return_row['sum']+0;
					$string_out = $string_out."</table>
				</div>
				</br></br>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:200%'>
					На сумму: <b>".$total_sum."  ".$return_row['currency_name']."</b>
				</div>
				</br>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:130%'>
					Получатель: _________________ (подпись)
				</div>
				</br>
				<div id = 'row' width='50%' style='font-family:\" Graduate\", Graduate, monospace; font-size:130%'>
					Отправитель: ______________________(подпись)
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
				<div id = 'row' width='50%'>
					Предприятие получатель: ".$company_row['company_name']."
				</div>
				</br>
				<div id = 'row' width='50%'>
					Представитель получателя: ".$order_raw_row['employee_name']." ".$order_raw_row['employee_surname']."
				</div>
				</br>
				<div id = 'row' width='50%'>
					Предприятие отправитель: ".$order_raw_row['purveyor_company_name']."
				</div>
				</br>
				<div id = 'row' width='50%'>
					Представитель отправителя: ".$order_raw_row['purveyor_name']." ".$order_raw_row['purveyor_surname']."
				</div>
				</br></br>
				<div id='content'>
					<table style='font-family:\" Graduate\", Graduate, monospace; font-size:140%' class='reset-style simple'  border = 0px  cellpadding=5 style='border-spacing:0px;'>
						<th class='simple-data-print'><b>Наименование</b></th>
						<th class='simple-data-print'><b>Цена</b></th>
						<th class='simple-data-print' ><b>Кол.</b></th>
						";
				while ($row = pg_fetch_array($result_order_raw_list)) {
					$counter++;
					$count=$row['count']+0;
					$sum=$row['sum']+0;
					$price=$row['price']+0;
					$string_out = $string_out."<tr class='simple-data-print'><td class='simple-data-print'>".$row['product_name']."</td>
						<td class='simple-data-print'>".$sum/$count."</td>
						<td class='simple-data-print'>".$count." ".$row['measure_short_name']."</td>
						";
					$count=0;
					$sum=0;
					$price=0;
				}
				$total_sum=$order_raw_row['sum']+0;
					$string_out = $string_out."</table>
				</div>
				</br></br>
				<div id = 'row' width='50%'>
					На сумму: <b>".$total_sum."  ".$order_raw_row['currency_name']."</b>
				</div>
				</br>
				<div id = 'row' width='50%'>
					Получатель: _________________ (подпись)
				</div>
				</br>
				<div id = 'row' width='50%'>
					Отправитель: ______________________(подпись)
				</div>";
			}
		}
	}
	$string_out = $string_out."</div><div class='modal-footter'><button class='modal-button' onclick='SentToPrinter()'>Печать</button><button class='modal-button' onclick='CloseModalAuto()'>Закрыть</button></div></div>";
	echo $string_out;
?>