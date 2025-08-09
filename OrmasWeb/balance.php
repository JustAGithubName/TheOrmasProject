<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
	$query = "SELECT balance_id, user_name, user_surname,user_phone, balance_value, currency_name FROM \"OrmasSchema\".balances_view WHERE user_id=".$_SESSION['id'];			
	$result = pg_query($query);
	$string_out = "<table class='balance-table'><caption>Мой баланс</cation><thead><tr><th>Номер счета</th><th>Имя</th><th>Фамилия</th><th>Номер телефона</th><th>Сумма счета</th><th>Валюта</th></tr></thead><tbody>";
	while ($row = pg_fetch_array($result)) {
        $string_out =$string_out."<tr>";
		$string_out =$string_out."<td>$row[0]</td>";
		$string_out =$string_out."<td>$row[1]</td>";
		$string_out =$string_out."<td>$row[2]</td>";
		$string_out =$string_out."<td>$row[3]</td>";
		$string_out =$string_out."<td>$row[4]</td>";
		$string_out =$string_out."<td>$row[5]</td>";
		$string_out =$string_out."</tr>";
    }
	$string_out = $string_out."</tbody></table>";
	
	$string_out .= "<script>
			$(document).ready( function () {
				$('#balance-table').DataTable();
			});
	</script>";
	
	echo $string_out;
?>