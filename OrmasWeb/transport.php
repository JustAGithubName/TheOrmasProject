<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
	
	$query_transport = "SELECT transport_id FROM \"OrmasSchema\".transports_view WHERE employee_id=".$_SESSION['id'];			
	$result_transport = pg_query($query_transport);
	$row_transport = pg_fetch_array($result_transport);
	$string_out = "<table id='transport-table'><caption>Товары в таранспорте</cation><thead><tr><th>Наименование продукта</th><th>Количество</th><th>Сумма</th><th>Валюта</th></tr></thead><tbody>";
	$totalSum=0;
	$curName="";
	if(!empty($row_transport))
	{
		$query = "SELECT product_name, count, sum, sum_currency_name, product_id, currency_name FROM \"OrmasSchema\".transport_list_view WHERE transport_id=".$row_transport[0];			
		$result = pg_query($query);
		$sum=0;
		$count=0;
		while ($row = pg_fetch_array($result)) {
			$sum=0;
			$count=0;
			$sum=$row[2]+0;
			$count=$row[1]+0;
			$calculatedSum=0;
			$string_out =$string_out."<tr>";
			$string_out =$string_out."<td>$row[0]</td>";
			$string_out =$string_out."<td>$count</td>";
			if($count  >0)
			{
				$query_product = "SELECT price FROM \"OrmasSchema\".products WHERE product_id=".$row[4];
				$result_product = pg_query($query_product);	
				$row_product = pg_fetch_array($result_product);
				if(!empty($row_product))
				{
					$price_extension_result=pg_query("SELECT * FROM \"OrmasSchema\".price_extension_view where product_id = ".$row[4]." and expeditor_id = ".$_SESSION['id']);
					$price_extension = pg_fetch_all($price_extension_result);
					if(empty($price_extension[0]))
					{
						$totalSum = $totalSum +  $count*$row_product[0];
						$calculatedSum = $count*$row_product[0];
						$string_out =$string_out."<td>$calculatedSum</td>";
					}
					else
					{
						$totalSum = $totalSum +  $count* ($row_product[0]+$price_extension[0]['value']);
						$calculatedSum = $count*($row_product[0]+$price_extension[0]['value']);
						$string_out =$string_out."<td>$calculatedSum</td>";
					}
				}
			}
			else
			{
				$string_out =$string_out."<td>0</td>";
			}
			$string_out =$string_out."<td>$row[3]</td>";
			$string_out =$string_out."</tr>";
			$curName = $row[5];			
		}
	}
	$string_out = $string_out."</tbody></table>";
	$string_out = $string_out."<div><b>Общая стоимость товаров в транспорте $totalSum $curName</b></div>";
	
	$string_out .= "<script>
			$(document).ready( function () {
				$('#transport-table').DataTable();
			});
	</script>";
	echo $string_out;
?>