<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
	$query_employee = "SELECT user_id_1 FROM \"OrmasSchema\".relations_view WHERE user_id_2=".$_SESSION['id'];			
	$result_employee = pg_query($query_employee);
	$string_out = "<table id='my-expeditor'><caption>Мой экпедитор</cation><thead><tr><th>Имя</th><th>Фамилия</th><th>Телефон</th><th>Должность</th></tr></thead><tbody>";
	while ($row_user = pg_fetch_array($result_employee)) {
		$query = "SELECT user_id, user_name, user_surname, user_phone, position_name FROM \"OrmasSchema\".employees_view WHERE user_id=".$row_user[0];			
		$result = pg_query($query);
		while ($row = pg_fetch_array($result)) {
			$string_out =$string_out."<tr>";
			$string_out =$string_out."<td>$row[1]</td>";
			$string_out =$string_out."<td>$row[2]</td>";
			$string_out =$string_out."<td>$row[3]</td>";
			$string_out =$string_out."<td>$row[4]</td>";
			$string_out =$string_out."</tr>";
		}
	}
	$string_out = $string_out."</tbody></table>";
	$string_out .= "<script>
			$(document).ready( function () {
				$('#my-expeditor').DataTable();
			});
	</script>";
	echo $string_out;
?>