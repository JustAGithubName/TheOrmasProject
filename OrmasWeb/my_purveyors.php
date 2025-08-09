<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
	$string_out = "<table id='my-purveyor'><caption>Поставщики</cation><thead><tr><th>Имя</th><th>Фамилия</th><th>Телефон</th><th>Город</th><th>Адрес</th><th>Фирма</th></tr></thead><tbody>";
	
	$query = "SELECT user_id, user_name, user_surname, user_phone, city_name, user_address, company_name FROM \"OrmasSchema\".purveyors_view";			
	$result = pg_query($query);
	while ($row = pg_fetch_array($result)) {
		$string_out =$string_out."<tr>";
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
				$('#my-purveyor').DataTable();
			});
	</script>";
	echo $string_out;
?>