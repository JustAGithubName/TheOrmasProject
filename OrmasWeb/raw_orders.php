<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
	$query_order = "SELECT * FROM \"OrmasSchema\".order_raws_view ORDER BY order_raw_id DESC  LIMIT 50 ";	
	$result_order = pg_query($query_order);
	$string_out = "<table id='raw-table'><caption>Поставки</caption><thead><tr><th>ID заказа</th><th>Дата заказа</th><th>Клиент</th><th>Статус</th><th>Количество</th><th>Сумма</th><th>Валюта</th><th>Действие</th></tr></thead><tbody>";
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
	
	$string_out .= "<script>
			$(document).ready( function () {
				$('#raw-table').DataTable();
			});
		</script>";
	echo $string_out;
?>