<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
	if($_SESSION['role_id_purveyor'] == $_SESSION['role_id'])
	{
		$query_status_1 = "SELECT status_id FROM \"OrmasSchema\".status_view where status_name='EXECUTED'";	
		$result_status_1  = pg_query($query_status_1);
		$row_status_1 = pg_fetch_row($result_status_1);
		$status_1_id=0;
		if($row_status_1)
		{
			$status_1_id=$row_status_1[0];
		}
		
		$query_status_2 = "SELECT status_id FROM \"OrmasSchema\".status_view where status_name='RETURN'";	
		$result_status_2  = pg_query($query_status_2);
		$row_status_2 = pg_fetch_row($result_status_2);
		$status_2_id=0;
		if($row_status_2)
		{
			$status_2_id=$row_status_2[0];
		}
		
		$query_order = "SELECT * FROM \"OrmasSchema\".order_raws_view where purveyor_id=".$_SESSION['id']." and status_id=".$status_1_id." ORDER BY order_raw_id DESC  LIMIT 10 ";	
		$result_order = pg_query($query_order);
		$string_out = "<table id='raw-table_1'><caption>10 последних поставок</caption><thead><tr><th>ID заказа</th><th>Дата заказа</th><th>Поставщик</th><th>Статус</th><th>Количество</th><th>Сумма</th><th>Валюта</th><th>Действие</th></tr></thead><tbody>";
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
		
			
		$query_order_2 = "SELECT * FROM \"OrmasSchema\".order_raws_view where purveyor_id=".$_SESSION['id']." and status_id=".$status_2_id." ORDER BY order_raw_id DESC  LIMIT 10 ";	
		$result_order_2 = pg_query($query_order_2);
		$string_out = $string_out."<table id='raw-table_2'><caption>10 возвратов</caption><thead><tr><th>ID заказа</th><th>Дата заказа</th><th>Поставщик</th><th>Статус</th><th>Количество</th><th>Сумма</th><th>Валюта</th><th>Действие</th></tr></thead><tbody>";
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