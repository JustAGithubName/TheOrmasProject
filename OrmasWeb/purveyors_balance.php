<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
	$string_out = "<table id='purveyor-balance'><caption>Баланс поставщиков</cation><thead><tr><th>Номер счета</th><th>Имя</th><th>Фамилия</th><th>Сумма счета</th><th>Валюта</th></tr></thead><tbody>";
	
		$query = "SELECT balance_id, user_name, user_surname, current_balance, currency_name, subaccount_id FROM \"OrmasSchema\".balances_view WHERE subaccount_number like '22010%'";			
		$result = pg_query($query);
		$sum=0;
			while ($row = pg_fetch_array($result)) {
			$sum=0;
			$sum=$row[3]+0;
			$query_subaac = "SELECT subaccount_number FROM \"OrmasSchema\".subaccounts_view WHERE subaccount_id=".$row[5];			
			$result_subaac = pg_query($query_subaac);
			$row_subaac = pg_fetch_array($result_subaac);
			$string_out =$string_out."<tr>";
			$string_out =$string_out."<td>$row_subaac[0]</td>";
			$string_out =$string_out."<td>$row[1]</td>";
			$string_out =$string_out."<td>$row[2]</td>";
			$string_out =$string_out."<td>$sum</td>";
			$string_out =$string_out."<td>$row[4]</td>";
			$string_out =$string_out."</tr>";
		}
	
	$string_out = $string_out."</tbody></table>";
	$string_out .= "<script>
			$(document).ready( function () {
				$('#purveyor-balance').DataTable();
			});
	</script>";
	echo $string_out;
?>