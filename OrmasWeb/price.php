<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
	$query_type = "SELECT * FROM \"OrmasSchema\".product_types_view WHERE product_type_code='PRODUCT'";			
	$result_type = pg_query($query_type);
	$row_type = pg_fetch_array($result_type);
	$query = "SELECT * FROM \"OrmasSchema\".products_view WHERE product_type_id=".$row_type['product_type_id'];			
	$result = pg_query($query);
	$string_out = "<table id='product-table'><caption>Прайс-лист</cation><thead><tr><th>ID продукта</th><th>Наименование</th><th>Цена</th><th>Валюта</th><th>Срок годгости в днях</th><th>Производитель</th></tr></thead><tbody>";
	$price=0;
	while ($row = pg_fetch_array($result)) {
		$price=0;
		$price=$row[2]+0;
        $string_out =$string_out."<tr>";
		$string_out =$string_out."<td>$row[0]</td>";
		$string_out =$string_out."<td>$row[1]</td>";
		$string_out =$string_out."<td>$price</td>";
		$string_out =$string_out."<td>$row[3]</td>";
		$string_out =$string_out."<td>$row[7]</td>";
		$string_out =$string_out."<td>$row[8]</td>";
		$string_out =$string_out."</tr>";
    }
	$string_out = $string_out."</tbody></table>";
	
	$string_out .= "<script>
			$(document).ready( function () {
				$('#product-table').DataTable();
			});
	</script>";
	
	echo $string_out;
?>