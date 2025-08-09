<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
			$query_client = "SELECT user_id_2 FROM \"OrmasSchema\".relations_view WHERE user_id_1=".$_SESSION['id'];			
			$result_clinet = pg_query($query_client);
			$my_clients = "";
			$my_clients_array = array();
			while ($row_user = pg_fetch_array($result_clinet)) {
				$my_clients .= ",$row_user[0] ";
				array_push($my_clients_array,$row_user[0]);
			}
			$my_clients = substr($my_clients, 1);
			$query_order = "SELECT order_id, client_name, client_surname, clinet_address, count, sum, currency_name, status_name, user_id FROM \"OrmasSchema\".orders_view WHERE employee_id = ".$_SESSION['id']." and execution_date like '%".$_POST['datepicker']."%' AND user_id in (".$my_clients.") AND status_name = 'EXECUTED'";
			$query_product_cons = "SELECT consume_product_id, employee_name, employee_surname, employee_phone, count, sum, currency_name, status_name FROM \"OrmasSchema\".consume_products_view WHERE user_id = ".$_SESSION['id']." and execution_date like '%".$_POST['datepicker']."%' AND status_name = 'EXECUTED'";
			$query_return = "SELECT return_id, client_name, client_surname, clinet_address, count, sum, currency_name, status_name, user_id  FROM \"OrmasSchema\".returns_view WHERE  employee_id = ".$_SESSION['id']." and execution_date like '%".$_POST['datepicker']."%' AND user_id in (".$my_clients.") AND status_name = 'EXECUTED'";
			$query_payment_execute = "SELECT payment_id, user_name,user_surname, payment_value, currency_name, status_name, user_id, payment_date FROM \"OrmasSchema\".payments_view WHERE user_id in (".$my_clients.")  AND payment_date like '%".$_POST['datepicker']."%' AND
			status_name = 'EXECUTED'";	
			$query_payment_to_pay = "SELECT payment_id, user_name,user_surname, payment_value, currency_name,status_name, user_id
			, payment_date	FROM \"OrmasSchema\".payments_view WHERE user_id in (".$my_clients.")  AND payment_date like '%".$_POST['datepicker']."%' AND
			status_name = 'TO PAY'";
			$result_order = pg_query($query_order);
			$result_product_cons = pg_query($query_product_cons);
			$result_return = pg_query($query_return);
			$result_payment_execute = pg_query($query_payment_execute);
			$result_payment_to_pay = pg_query($query_payment_to_pay);
			/*$order_all=pg_fetch_all($result_order);
			$result_all=pg_fetch_all($result_return);
			$result_payment_all=pg_fetch_all($result_payment_execute);
			$result_payment_topay_all=pg_fetch_all($result_payment_to_pay);
			print_r($order_all);*/
			$order_sum=0;
			$product_cons_sum=0;
			$return_sum=0;
			$payment_sum=0;
			$to_payment_sum=0;
			
			$string_cons_out = "<table id='report-table'><capital>Отчет о получении товара за ".$_POST['datepicker']."<capital><thead><tr><th>ID прихода </th><th>Имя сотрудника</th><th>Фамили сотрудника</th><th>Телефон сотрудника</th><th>Количество</th><!--<th>Сумма заказа</th><th>Валюта</th>--><th>Обзор</th></tr>";
			while ($row = pg_fetch_array($result_product_cons)) 
			{
				$string_cons_out =$string_cons_out."<tr>";
				$string_cons_out =$string_cons_out."<td>$row[0]</td>";
				$string_cons_out =$string_cons_out."<td>$row[1]</td>";
				$string_cons_out =$string_cons_out."<td>$row[2]</td>";
				$string_cons_out =$string_cons_out."<td>$row[3]</td>";
				$string_cons_out =$string_cons_out."<td>$row[4]</td>";
				//$string_cons_out =$string_cons_out."<td>$row[5]</td>-->";
				//$string_cons_out =$string_cons_out."<td>TJS</td>";
				$string_cons_out =$string_cons_out."<td><div class='controls-container'><a href='#' class = 'consid' onclick='PrintProductCons($row[0])'><div class='form-contraols list-submit print-submit '></div></a></div></td>";
				$string_cons_out =$string_cons_out."</tr>";
				$product_cons_sum = $product_cons_sum + $row[5];
			}
			$string_cons_out = $string_cons_out."<tr><td></td><td></td><td></td><td></td><td>Суммарно отгружено</td><td>$product_cons_sum</td><td>TJS</td></tr></thead><tbody>";
			
			
			$string_order_out = "<table id='report-table'><capital>Отчет о продажах за ".$_POST['datepicker']."<capital><thead><tr><th>ID заказа </th><th>Имя клиента</th><th>Фамили клиента</th><th>Адрес клиента</th><th>Количество</th><th>Сумма заказа</th><th>Валюта</th><th>Обзор</th></tr>";
			while ($row = pg_fetch_array($result_order)) 
			{
				$string_order_out =$string_order_out."<tr>";
				$string_order_out =$string_order_out."<td>$row[0]</td>";
				$string_order_out =$string_order_out."<td>$row[1]</td>";
				$string_order_out =$string_order_out."<td>$row[2]</td>";
				$string_order_out =$string_order_out."<td>$row[3]</td>";
				$string_order_out =$string_order_out."<td>$row[4]</td>";
				$string_order_out =$string_order_out."<td>$row[5]</td>";
				$string_order_out =$string_order_out."<td>TJS</td>";
				$string_order_out =$string_order_out."<td><div class='controls-container'><a href='#' class = 'orderid' onclick='PrintOrder($row[0])'><div class='form-contraols list-submit print-submit '></div></a></div></td>";
				$string_order_out =$string_order_out."</tr>";
				$order_sum = $order_sum + $row[5];
			}
			$string_order_out = $string_order_out."<tr><td></td><td></td><td></td><td></td><td>Суммарно отгружено</td><td>$order_sum</td><td>TJS</td></tr></thead><tbody>";
			
			$string_return_out = "<table id='report-table'><capital>Отчет о возврате за ".$_POST['datepicker']."<capital><thead><tr><th>ID возврата </th><th>Имя клиента</th><th>Фамили клиента</th><th>Адрес клиента</th><th>Количество</th><th>Сумма возврата</th><th>Валюта</th><th>Обзор</th></tr>";
			while ($row_ret = pg_fetch_array($result_return)) 
			{
				$string_return_out =$string_return_out."<tr>";
				$string_return_out =$string_return_out."<td>$row_ret[0]</td>";
				$string_return_out =$string_return_out."<td>$row_ret[1]</td>";
				$string_return_out =$string_return_out."<td>$row_ret[2]</td>";
				$string_return_out =$string_return_out."<td>$row_ret[3]</td>";
				$string_return_out =$string_return_out."<td>$row_ret[4]</td>";
				$string_return_out =$string_return_out."<td>$row_ret[5]</td>";
				$string_return_out =$string_return_out."<td>TJS</td>";
				$string_return_out =$string_return_out."<td><div class='controls-container'><a href='#' class = 'orderid' onclick='PrintOrder($row[0])'><div class='form-contraols list-submit print-submit '></div></a></div></td>";
				$string_return_out =$string_return_out."</tr>";
				$return_sum = $return_sum + $row_ret[5];
			}
			$string_return_out = $string_return_out."<tr><td></td><td></td><td></td><td></td><td>Суммарно к возврату</td><td>$return_sum</td><td>TJS</td></tr></thead><tbody>";
			
			$string_payment = "<table id='report-table'><capital>Отчет об оплатах за ".$_POST['datepicker']."<capital><thead><tr><th>ID платежа </th><th>Имя клиента</th><th>Фамили клиента</th><th>Сумма оплаты</th><th>Валюта</th></tr>";
			while ($row_pay = pg_fetch_array($result_payment_execute)) 
			{
				$string_payment =$string_payment."<tr>";
				$string_payment =$string_payment."<td>$row_pay[0]</td>";
				$string_payment =$string_payment."<td>$row_pay[1]</td>";
				$string_payment =$string_payment."<td>$row_pay[2]</td>";
				$string_payment =$string_payment."<td>$row_pay[3]</td>";
				$string_payment =$string_payment."<td>TJS</td>";
				$string_payment =$string_payment."</tr>";
				$payment_sum = $payment_sum + $row_pay[3];
			}
			$string_payment = $string_payment."<tr><td></td><td></td><td>Суммарно оплаченно</td><td>$payment_sum</td><td>TJS</td></tr></thead><tbody>";
			
			$string_to_payment = "<table id='report-table'><capital>Отчет к оплатам за ".$_POST['datepicker']."<capital><thead><tr><th>ID платежа </th><th>Имя клиента</th><th>Фамили клиента</th><th>Сумма оплаты</th><th>Валюта</th></tr>";
			while ($row_to_pay = pg_fetch_array($result_payment_to_pay)) 
			{
				$string_to_payment =$string_to_payment."<tr>";
				$string_to_payment =$string_to_payment."<td>$row_to_pay[0]</td>";
				$string_to_payment =$string_to_payment."<td>$row_to_pay[1]</td>";
				$string_to_payment =$string_to_payment."<td>$row_to_pay[2]</td>";
				$string_to_payment =$string_to_payment."<td>$row_to_pay[3]</td>";
				$string_to_payment =$string_to_payment."<td>TJS</td>";
				$string_to_payment =$string_to_payment."</tr>";
				$to_payment_sum = $to_payment_sum + $row_to_pay[3];
			}
			$string_to_payment = $string_to_payment."<tr><td></td><td></td><td>Суммарно к оплате</td><td>$to_payment_sum</td><td>TJS</td></tr></thead><tbody>";
			$total_string=$string_cons_out.$string_order_out.$string_return_out.$string_payment.$string_to_payment;
			echo $total_string;
?>