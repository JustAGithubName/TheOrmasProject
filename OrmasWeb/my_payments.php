<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
	if($_SESSION['role_id_client'] == $_SESSION['role_id'])
	{
		$query_client = "SELECT payment_date, user_name, user_surname, payment_value, currency_name, payment_target, status_name FROM \"OrmasSchema\".payments_view WHERE user_id=".$_SESSION['id']." LIMIT 5";			
		$result_clinet = pg_query($query_client);
		$string_out = "<table id='my-payments'><caption>5 последних оплат</cation><thead><tr><th>Дата</th><th>Имя</th><th>Фамилия</th><th>Сумма</th><th>Валюта</th><th>Назначение</th><th>Статус</th></tr></thead><tbody>";
		while ($row = pg_fetch_array($result_clinet)) {
			
				$string_out =$string_out."<tr>";
				$string_out =$string_out."<td>$row[0]</td>";
				$string_out =$string_out."<td>$row[1]</td>";
				$string_out =$string_out."<td>$row[2]</td>";
				$string_out =$string_out."<td>$row[3]</td>";
				$string_out =$string_out."<td>$row[4]</td>";
				$string_out =$string_out."<td>$row[5]</td>";
				$string_out =$string_out."<td>$row[6]</td>";
				$string_out =$string_out."</tr>";
		}
		$string_out = $string_out."</tbody></table>";
		$string_out .= "<script>
				$(document).ready( function () {
					$('#my-payments').DataTable();
				});
		</script>";
		echo $string_out;
	}
	
	if($_SESSION['role_id_purveyor'] == $_SESSION['role_id'])
	{
		$query_client = "SELECT withdrawal_date, user_name, user_surname, withdrawal_value, currency_name, withdrawal_target, status_name FROM \"OrmasSchema\".withdrawals_view WHERE user_id=".$_SESSION['id']." ORDER BY withdrawal_id DESC LIMIT 5";			
		
		$result_clinet = pg_query($query_client);
		$string_out = "<table id='my-withdrawals'><caption>5 последних выплат</cation><thead><tr><th>Дата</th><th>Имя</th><th>Фамилия</th><th>Сумма</th><th>Валюта</th><th>Назначение</th><th>Статус</th></tr></thead><tbody>";
		while ($row = pg_fetch_array($result_clinet)) {
			
				$string_out =$string_out."<tr>";
				$string_out =$string_out."<td>$row[0]</td>";
				$string_out =$string_out."<td>$row[1]</td>";
				$string_out =$string_out."<td>$row[2]</td>";
				$string_out =$string_out."<td>$row[3]</td>";
				$string_out =$string_out."<td>$row[4]</td>";
				$string_out =$string_out."<td>$row[5]</td>";
				$string_out =$string_out."<td>$row[6]</td>";
				$string_out =$string_out."</tr>";
		}
		$string_out = $string_out."</tbody></table>";
		$string_out .= "<script>
				$(document).ready( function () {
					$('#my-withdrawals').DataTable();
				});
		</script>";
		echo $string_out;
	}
?>