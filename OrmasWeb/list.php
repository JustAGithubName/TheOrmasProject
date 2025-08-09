<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
	if($_SESSION['role_id_client'] == $_SESSION['role_id'])
	{
		$query_order = "SELECT order_id, order_date, client_name, client_surname, client_phone, status_name, count, sum, currency_name FROM \"OrmasSchema\".orders_view WHERE user_id=".$_SESSION['id']." AND status_name = 'ORDERED' LIMIT 15";	
		$query_return = "SELECT return_id, return_date, client_name, client_surname, client_phone, status_name, count, sum, currency_name FROM \"OrmasSchema\".returns_view WHERE user_id=".$_SESSION['id']." AND status_name = 'TO RETURN' LIMIT 15";			
		$result_order = pg_query($query_order);
		$string_out = "<table id='order-table'><h1>Мои заказы<h1><thead><tr><th>ID заказа</th><th>Дата заказа</th><th>Клиент</th><th>Статус</th><th>Количество</th><th>Сумма</th><th>Валюта</th><th>Действие</th></tr></thead><tbody>";
		$count=0;
		$sum=0;
		while ($row = pg_fetch_array($result_order)) {
			$count=$row[6]+0;
			$sum=$row[7]+0;		
			$string_out =$string_out."<tr>";
			$string_out =$string_out."<td>$row[0]</td>";
			$string_out =$string_out."<td>$row[1]</td>";
			$string_out =$string_out."<td>$row[2] $row[3] $row[4]</td>";
			$string_out =$string_out."<td>$row[5]</td>";
			$string_out =$string_out."<td>$count</td>";
			$string_out =$string_out."<td>$sum</td>";
			$string_out =$string_out."<td>$row[8]</td>";
			$string_out =$string_out."<td><div class='controls-container'><!--<div class='form-contraols'><form method='post' id='execute-order'><input type='hidden' id='execute' name='execute' value='' /><input type='hidden' id='execute_coun' name='execute_coun[]' value='$row[0]' /><button class='list-submit ok-submit' type='button' onclick='ExecuteOrder($row[0])'></button></form></div>--><a href='#' class = 'orderid' onclick='PrintOrder($row[0])'><div class='form-contraols list-submit print-submit '></div></a><!--<div class='form-contraols'><form method='post' id='cancel-order'><input type='hidden' id='order_error' name='order_error' value='' /><input type='hidden' id='order_error_count' name='order_error_count[]' value='$row[0]' /><button class='list-submit cancel-submit'  type='button' onclick='CancelOrder($row[0])'></button></form></div>--></div></td>";
			$string_out =$string_out."</tr>";
		}
		$string_out = $string_out."</tbody></table><br/><br/><br/>";
		$result_return = pg_query($query_return);
		$string_out = $string_out."<table id='return-table'><caption>Мои возвраты</caption><thead><tr><th>ID возврата</th><th>Дата возврата</th><th>Клиент</th><th>Статус</th><th>Количество</th><th>Сумма</th><th>Валюта</th><th>Действие</th></tr></thead><tbody>";
		while ($row = pg_fetch_array($result_return)) {
			$count=$row[6]+0;
			$sum=$row[7]+0;
			$string_out =$string_out."<tr>";
			$string_out =$string_out."<td>$row[0]</td>";
			$string_out =$string_out."<td>$row[1]</td>";
			$string_out =$string_out."<td>$row[2] $row[3] $row[4]</td>";
			$string_out =$string_out."<td>$row[5]</td>";
			$string_out =$string_out."<td>$count</td>";
			$string_out =$string_out."<td>$sum</td>";
			$string_out =$string_out."<td>$row[8]</td>";
			$string_out =$string_out."<td><div class='controls-container'><!--<div class='form-contraols'><form method='post'  id='execute-ret'><input type='hidden' id='execute_return' name='execute_return' value='' /><input type='hidden' id='execute_coun' name='execute_coun[]' value='$row[0]' /><button class='list-submit ok-submit' type='button' onclick='ExecuteReturn($row[0])'></button></form></div>--><a href='#' class = 'returnid' onclick='PrintReturn($row[0])'><div class='form-contraols list-submit print-submit' ></div></a><!--<div class='form-contraols'><form method='post' id='cancel-return'><input type='hidden' id='return-error' name='return-error' value='' /><input type='hidden' id='return-error_count' name='return-error_count[]' value='$row[0]' /><button class='list-submit cancel-submit'  type='button' onclick='CancelReturn($row[0])'></button></form></div>--></div></td>";
			$string_out =$string_out."</tr>";
		}
		$string_out = $string_out."</tbody></table>";
		$string_out .= "<script>
			$(document).ready( function () {
				$('#order-table').DataTable();
			});
			$(document).ready( function () {
				$('#return-table').DataTable();
			});
		</script>";
		echo $string_out;
	}
	if($_SESSION['role_id_expeditor'] == $_SESSION['role_id'])
	{
		$count=0;
		$sum=0;
		$query_order = "SELECT order_id, order_date, client_name, client_surname, client_phone, status_name, count, sum, currency_name FROM \"OrmasSchema\".orders_view WHERE employee_id=".$_SESSION['id']." AND status_name = 'ORDERED' ORDER BY order_id DESC";
		$query_return = "SELECT return_id, return_date, client_name, client_surname, client_phone, status_name, count, sum, currency_name FROM \"OrmasSchema\".returns_view WHERE employee_id=".$_SESSION['id']." AND status_name = 'TO RETURN' ORDER BY return_id DESC";			
		$query_consume = "SELECT consume_product_id, consume_product_date, stock_employee_name, stock_employee_surname, stock_employee_phone, status_name, count, sum, currency_name FROM \"OrmasSchema\".consume_products_view WHERE user_id=".$_SESSION['id']." AND status_name = 'CONSUMED' ORDER BY consume_product_id DESC";			
		$result_order = pg_query($query_order);
		$string_out = "<table id='order-table'><caption>Мои заказы</cation><thead><tr><th>ID заказа</th><th>Дата заказа</th><th>Клиент</th><th>Статус</th><th>Количество</th><th>Сумма</th><th>Валюта</th><th>Действие</th></tr></thead><tbody>";
		$order_count=0;
		while ($row = pg_fetch_array($result_order)) {
			$count=$row[6]+0;
			$sum=$row[7]+0;
			$string_out =$string_out."<tr>";
			$string_out =$string_out."<td>$row[0]</td>";
			$string_out =$string_out."<td>$row[1]</td>";
			$string_out =$string_out."<td>$row[2] $row[3] $row[4]</td>";
			$string_out =$string_out."<td>$row[5]</td>";
			$string_out =$string_out."<td>$count</td>";
			$string_out =$string_out."<td>$sum</td>";
			$string_out =$string_out."<td>$row[8]</td>";
			$string_out =$string_out."<td><div class='controls-container'><div class='form-contraols'><form method='post' id='execute-order'><input type='hidden' id='execute' name='execute' value='' /><input type='hidden' id='execute_coun' name='execute_coun[]' value='$row[0]' /><button class='list-submit ok-submit' type='button' onclick='ExecuteOrder($row[0])'></button></form></div><a href='#' class = 'orderid' onclick='PrintOrder($row[0])'><div class='form-contraols list-submit print-submit '></div></a><a href='#' class = 'orderid' onclick='TermoPrintOrder($row[0])'><div class='form-contraols list-submit termoprint-submit'></div></a><div class='form-contraols'><form method='post' id='cancel-order'><input type='hidden' id='order_error' name='order_error' value='' /><input type='hidden' id='order_error_count' name='order_error_count[]' value='$row[0]' /><button class='list-submit cancel-submit'  type='button' onclick='CancelOrder($row[0])'></button></form></div></div></td>";
			$string_out =$string_out."</tr>";
		}
		$string_out = $string_out."</tbody></table><br/><br/><br/>";
		$result_return = pg_query($query_return);
		$string_out = $string_out."<table id='return-table'><caption>Мои возвраты</cation><thead><tr><th>ID возврата</th><th>Дата возврата</th><th>Клиент</th><th>Статус</th><th>Количество</th><th>Сумма</th><th>Валюта</th><th>Действие</th></tr></thead><tbody>";
		$return_count=0;
		while ($row = pg_fetch_array($result_return)) {
			$count=$row[6]+0;
			$sum=$row[7]+0;
			$string_out =$string_out."<tr>";
			$string_out =$string_out."<td>$row[0]</td>";
			$string_out =$string_out."<td>$row[1]</td>";
			$string_out =$string_out."<td>$row[2] $row[3] $row[4]</td>";
			$string_out =$string_out."<td>$row[5]</td>";
			$string_out =$string_out."<td>$count</td>";
			$string_out =$string_out."<td>$sum</td>";
			$string_out =$string_out."<td>$row[8]</td>";
			
			$string_out =$string_out."<td><div class='controls-container'><!--<div class='form-contraols'><form method='post'  id='execute-ret'><input type='hidden' id='execute_return' name='execute_return' value='' /><input type='hidden' id='execute_coun' name='execute_coun[]' value='$row[0]' /><button class='list-submit ok-submit' type='button' onclick='ExecuteReturn($row[0])'></button></form></div>--><a href='#' class = 'returnid' onclick='PrintReturn($row[0])'><div class='form-contraols list-submit print-submit' ></div></a><a href='#' class = 'returnid' onclick='TermoPrintReturn($row[0])'><div class='form-contraols list-submit termoprint-submit' ></div></a><div class='form-contraols'><form method='post' id='cancel-return'><input type='hidden' id='return-error' name='return-error' value='' /><input type='hidden' id='return-error_count' name='return-error_count[]' value='$row[0]' /><button class='list-submit cancel-submit'  type='button' onclick='CancelReturn($row[0])'></button></form></div></div></td>";
			
			$string_out =$string_out."</tr>";
		}
		$string_out = $string_out."</tbody></table><br/><br/><br/>";
		$result_consume = pg_query($query_consume);
		$string_out = $string_out."<table id='consume-table'><caption>Мои заявки</cation><thead><tr><th>ID возврата</th><th>Дата возврата</th><th>Клиент</th><th>Статус</th><th>Количество</th><th>Сумма</th><th>Валюта</th><th>Действие</th></tr></thead><tbody>";
		$consume_count=0;
		while ($row = pg_fetch_array($result_consume)) {
			$count=$row[6]+0;
			$sum=$row[7]+0;
			$string_out =$string_out."<tr>";
			$string_out =$string_out."<td>$row[0]</td>";
			$string_out =$string_out."<td>$row[1]</td>";
			$string_out =$string_out."<td>$row[2] $row[3] $row[4]</td>";
			$string_out =$string_out."<td>$row[5]</td>";
			$string_out =$string_out."<td>$count</td>";
			$string_out =$string_out."<td>$sum</td>";
			$string_out =$string_out."<td>$row[8]</td>";
			
			$string_out =$string_out."<td><div class='controls-container'><a href='#' class = 'consumeid' onclick='PrintConsume($row[0])'><div class='form-contraols list-submit print-submit' ></div></a><div class='form-contraols'><form method='post' id='cancel-consume'><input type='hidden' id='consume-error' name='consume-error' value='' /><input type='hidden' id='consume-error_count' name='consume-error_count[]' value='$row[0]' /><button class='list-submit cancel-submit'  type='button' onclick='CancelConsume($row[0])'></button></form></div></div></td>";
			
			$string_out =$string_out."</tr>";
		}
		$string_out = $string_out."</tbody></table><br/><br/><br/>";
		$string_out .= "<script>
			$(document).ready( function () {
				$('#order-table').DataTable();
			});
			$(document).ready( function () {
				$('#return-table').DataTable();
			});
			$(document).ready( function () {
				$('#consume-table').DataTable();
			});
		</script>";
		echo $string_out;
	}
	if($_SESSION['role_id_stock_inspector'] == $_SESSION['role_id'])
	{
		$query_stock = "SELECT stock_id, product_name, count, sum, currency_name, warehouse_name FROM \"OrmasSchema\".stock_view ORDER BY product_name";	
		$result_stock = pg_query($query_stock);
		$string_out = "<table id='stock-table'><caption>Склад</cation><thead><tr><th>ID склада</th><th>Наименование продукта</th><th>Количество</th><th>Сумма</th><th>Валюта</th><th>Название склада</th></tr></thead><tbody>";
		$count=0;
		while ($row = pg_fetch_array($result_stock)) {
			$count=$row[2]+0;
			$string_out =$string_out."<tr>";
			$string_out =$string_out."<td>$row[0]</td>";
			$string_out =$string_out."<td>$row[1]</td>";
			$string_out =$string_out."<td>$count</td>";
			$string_out =$string_out."<td>$row[3]</td>";
			$string_out =$string_out."<td>$row[4]</td>";
			$string_out =$string_out."<td>$row[5]</td>";
			$string_out =$string_out."</tr>";
		}
		$string_out = $string_out."</tbody></table><br/><br/><br/>";
		$string_out .= "<script>
			$(document).ready( function () {
				$('#stock-table').DataTable();
			});
		</script>";
		echo $string_out;						
	}
	if($_SESSION['role_id_purveyor_manager'] == $_SESSION['role_id'])
	{
		$query_branch = "SELECT branch_id FROM \"OrmasSchema\".user_extended_view where user_id=".$_SESSION['id'];	
		$result_branch  = pg_query($query_branch);
		$row_branch = pg_fetch_row($result_branch);
		$branch_id="";
		if($row_branch)
		{
			$branch_id=$row_branch[0];
		}
		
		$query_role = "SELECT role_id FROM \"OrmasSchema\".roles_view where role_name='STOCK MANAGER'";	
		$result_role  = pg_query($query_role);
		$row_role = pg_fetch_row($result_role);
		$role_id=0;
		if($row_role)
		{
			$role_id=$row_role[0];
		}
		
		$query_employee = "SELECT user_id FROM \"OrmasSchema\".user_extended_view where branch_id=".$branch_id." and role_id=".$role_id;	
		$result_employee  = pg_query($query_employee);
		$stock_managers="";
		while ($row_employee = pg_fetch_array($result_employee)) {
			$stock_managers .= $row_employee[0].",";
		}
		$stock_managers_list = substr($stock_managers, 0, -1);
		
		$query_warehouse_type = "SELECT warehouse_type_id FROM \"OrmasSchema\".warehouse_type_view where warehouse_type_code='RAW'";	
		$result_wearehous_type = pg_query($query_warehouse_type);
		$row_wearehous_type = pg_fetch_row($result_wearehous_type);
		$type_id=0;
		if($row_wearehous_type)
		{
			$type_id=$row_wearehous_type[0];
		}
		
		$query_warehouse_employee = "SELECT warehouse_id FROM \"OrmasSchema\".warehouse_employee_view where employee_id IN(".$stock_managers_list.")";	
		$result_warehouse_employee = pg_query($query_warehouse_employee);
		$warehouses="";
		while ($row_warehouse_employee = pg_fetch_array($result_warehouse_employee)) {
			$warehouses .= $row_warehouse_employee[0].",";
		}
		$warehouses_list = substr($warehouses, 0, -1);
		
		$query_warehouse = "SELECT warehouse_id FROM \"OrmasSchema\".warehouse_view where warehouse_id IN(".$warehouses_list.") and warehouse_type_id = ".$type_id;	
		$result_warehouse = pg_query($query_warehouse);
		$warehouse_id="";
		while ($row_warehouse = pg_fetch_array($result_warehouse)) {
			$warehouse_id .= $row_warehouse[0].",";
		}
		$warehouses_list_id = substr($warehouse_id, 0, -1);

		$query_stock = "SELECT stock_id, product_name, count, sum, currency_name, warehouse_name FROM \"OrmasSchema\".stock_view where warehouse_id IN(".$warehouses_list_id.") ORDER BY product_name";	
		$result_stock = pg_query($query_stock);
		$string_out = "<table id='stock-table'><caption>Склад</cation><thead><tr><th>ID склада</th><th>Наименование продукта</th><th>Количество</th><th>Сумма</th><th>Валюта</th><th>Название склада</th></tr></thead><tbody>";
		$count=0;
		$sum=0;
		while ($row = pg_fetch_array($result_stock)) {
			$count=$row[2]+0;
			$sum=$row[3]+0;
			$string_out =$string_out."<tr>";
			$string_out =$string_out."<td>$row[0]</td>";
			$string_out =$string_out."<td>$row[1]</td>";
			$string_out =$string_out."<td>$count</td>";
			$string_out =$string_out."<td>$sum</td>";
			$string_out =$string_out."<td>$row[4]</td>";
			$string_out =$string_out."<td>$row[5]</td>";
			$string_out =$string_out."</tr>";
		}
		$string_out = $string_out."</tbody></table><br/><br/><br/>";
		$string_out .= "<script>
			$(document).ready( function () {
				$('#stock-table').DataTable();
			});
			
		</script>";
		echo $string_out;						
	}
	if($_SESSION['role_id_purveyor'] == $_SESSION['role_id'])
	{
		$query_status_1 = "SELECT status_id FROM \"OrmasSchema\".status_view where status_name='ORDERED'";	
		$result_status_1  = pg_query($query_status_1);
		$row_status_1 = pg_fetch_row($result_status_1);
		$status_1_id=0;
		if($row_status_1)
		{
			$status_1_id=$row_status_1[0];
		}
		
		$query_status_2 = "SELECT status_id FROM \"OrmasSchema\".status_view where status_name='TO RETURN'";	
		$result_status_2  = pg_query($query_status_2);
		$row_status_2 = pg_fetch_row($result_status_2);
		$status_2_id=0;
		if($row_status_2)
		{
			$status_2_id=$row_status_2[0];
		}
		
		$query_order = "SELECT * FROM \"OrmasSchema\".order_raws_view where purveyor_id=".$_SESSION['id']." and status_id=".$status_1_id." ORDER BY order_raw_id DESC  LIMIT 50 ";	
		$result_order = pg_query($query_order);
		$string_out = "<table id='raw-table_1'><caption>Поставки</caption><thead><tr><th>ID заказа</th><th>Дата заказа</th><th>Поставщик</th><th>Статус</th><th>Количество</th><th>Сумма</th><th>Валюта</th><th>Действие</th></tr></thead><tbody>";
		$count=0;
		$sum=0;
		while ($row = pg_fetch_array($result_order)) {
			$count=0;
			$sum=0;
			$count=$row[13]+0;
			$sum=$row[14]+0;
			$string_out =$string_out."<tr>";
			$string_out =$string_out."<td>$row[0]</td>";
			$string_out =$string_out."<td>$row[1]</td>";
			$string_out =$string_out."<td>$row[5] $row[6] $row[7] $row[8]</td>";
			$string_out =$string_out."<td>$row[4]</td>";
			$string_out =$string_out."<td>$count</td>";
			$string_out =$string_out."<td>$sum</td>";
			$string_out =$string_out."<td>$row[15]</td>";
			$string_out =$string_out."<td><div class='controls-container'><a href='#' class = 'orderrawid' onclick='PrintOrderRaw($row[0])'><div class='form-contraols list-submit print-submit '></div></a></div></td>";
			$string_out =$string_out."</tr>";
		}
		$string_out = $string_out."</tbody></table><br/><br/><br/>";
		
			
		$query_order_2 = "SELECT * FROM \"OrmasSchema\".order_raws_view where purveyor_id=".$_SESSION['id']." and status_id=".$status_2_id." ORDER BY order_raw_id DESC  LIMIT 50 ";	
		$result_order_2 = pg_query($query_order_2);
		$string_out = $string_out."<table id='raw-table_2'><caption>К возвтару</caption><thead><tr><th>ID заказа</th><th>Дата заказа</th><th>Поставщик</th><th>Статус</th><th>Количество</th><th>Сумма</th><th>Валюта</th><th>Действие</th></tr></thead><tbody>";
		$count=0;
		$sum=0;
		while ($row = pg_fetch_array($result_order_2)) {
			$count=0;
			$sum=0;
			$count=$row[13]+0;
			$sum=$row[14]+0;
			$string_out =$string_out."<tr>";
			$string_out =$string_out."<td>$row[0]</td>";
			$string_out =$string_out."<td>$row[1]</td>";
			$string_out =$string_out."<td>$row[5] $row[6] $row[7] $row[8]</td>";
			$string_out =$string_out."<td>$row[4]</td>";
			$string_out =$string_out."<td>$count</td>";
			$string_out =$string_out."<td>$sum</td>";
			$string_out =$string_out."<td>$row[15]</td>";
			$string_out =$string_out."<td><div class='controls-container'><a href='#' class = 'orderrawid' onclick='PrintOrderRaw($row[0])'><div class='form-contraols list-submit print-submit '></div></a></div></td>";
			$string_out =$string_out."</tr>";
		}
		$string_out = $string_out."</tbody></table><br/><br/><br/>";
		
		$string_out .= "<script>
				$(document).ready( function () {
					$('#raw-table_1').DataTable();
				});
			</script>
			<script>
				$(document).ready( function () {
					$('#raw-table_2').DataTable();
				});
			</script>";
			
		echo $string_out;					
	}
?>