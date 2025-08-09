<?php
session_start();
require_once 'logsql.php';
	
    if(empty($product_list) or empty($productPrice))
	{
	$product_type_result = pg_query("SELECT product_type_id FROM \"OrmasSchema\".product_types_view where product_type_code = 'PRODUCT'");
    $product_type_row = pg_fetch_array($product_type_result);
	$product_employee_result = pg_query("SELECT product_id FROM \"OrmasSchema\".employee_product_view where employee_id =".$_SESSION['id']);
    $product_employee_row = pg_fetch_all($product_employee_result);
	$product_id_list ="";
	if(!empty($product_employee_row[0]))
	{
		$row_count = pg_num_rows($product_employee_result);
		for($i=0;$i<$row_count;$i++)
		{
			if($i == 0)
			{
				$product_id_list .= " ".$product_employee_row[$i]['product_id']." ";
			}
			else
			{
				$product_id_list .= ", ".$product_employee_row[$i]['product_id']." ";
			}
		}
	}
	
	if(empty($product_id_list))
	{
		$transport = pg_query("SELECT transport_id FROM \"OrmasSchema\".transports_view where employee_id =".$_SESSION['id']);
		$transport_row = pg_fetch_array($transport);
		//print_r($transport_row);
		$transport_list = pg_query("SELECT product_id FROM \"OrmasSchema\".transport_list_view where transport_id =".$transport_row[0]);
		$transport_list_row = pg_fetch_all($transport_list);
		$product_id_list ="";
		if(!empty($transport_list_row[0]))
		{
			$row_count = pg_num_rows($transport_list);
			for($i=0;$i<$row_count;$i++)
			{
				if($i == 0)
				{
					$product_id_list .= " ".$transport_list_row[$i]['product_id']." ";
				}
				else
				{
					$product_id_list .= ", ".$transport_list_row[$i]['product_id']." ";
				}
			}
		}
	}
	
	if(!empty($product_id_list))
	{
		$product_result = pg_query("SELECT * FROM \"OrmasSchema\".products_view where product_type_id = ".$product_type_row[0]." 
		and product_id IN(".$product_id_list.")");
	}
	else
	{
		$product_result = pg_query("SELECT * FROM \"OrmasSchema\".products_view where product_type_id = ".$product_type_row[0]);
	}
	$product_row = pg_fetch_all($product_result);
	
	
	if(!empty($product_row[0]))
	{
		$row_count = pg_num_rows($product_result);
		$product_list_all="";
		for($i=0;$i<$row_count;$i++)
		{
			$product_list_all .= "<option value='".$product_row[$i]['product_id']."'>".$product_row[$i]['product_name']."</option>";
			$temp= "<option value='".$product_row[$i]['product_id']."'>".$product_row[$i]['product_name']."</option>";
			$product_list[$i] .=$temp;
			if($_SESSION['role_id_client'] == $_SESSION['role_id'])
			{
				$productPrice[$i] = array("id" => $product_row[$i]['product_id'], "price" => $product_row[$i]['price']);
			}
			if($_SESSION['role_id_expeditor'] == $_SESSION['role_id'])
			{
				$price_extension_result=pg_query("SELECT * FROM \"OrmasSchema\".price_extension_view where product_id = ".$product_row[$i]['product_id']." and expeditor_id = ".$_SESSION['id']." ORDER BY price_extension_id DESC;");
				$price_extension = pg_fetch_all($price_extension_result);
				if(!empty($price_extension[0]))
				{
					$productPrice[$i] = array("id" => $product_row[$i]['product_id'], "price" => $product_row[$i]['price'] +$price_extension[0]['value']);
				}
				else
				{
					$productPrice[$i] = array("id" => $product_row[$i]['product_id'], "price" => $product_row[$i]['price']);
				}
			}
		}	
	}
}
	
$status_result= pg_query("SELECT status_id FROM \"OrmasSchema\".status_view where status_name = 'TO RETURN'");
$status_row = pg_fetch_all($status_result);
$status_id ="";
if(!empty($status_row[0]))
{
	$row_count = pg_num_rows($status_result);
	for($i=0;$i<$row_count;$i++)
	{
		$status_id = $status_row[$i]['status_id'];
	}
}

$currency_result= pg_query("SELECT currency_id FROM \"OrmasSchema\".currencies_view where currency_short_name = 'TJS'");
$currency_row = pg_fetch_all($currency_result);
$currency_id ="";
if(!empty($currency_row[0]))
{
	$row_count = pg_num_rows($currency_result);
	for($i=0;$i<$row_count;$i++)
	{
		$currency_id = $currency_row[$i]['currency_id'];
	}
}

$status_result= pg_query("SELECT \"OrmasSchema\".getcurrentdate()");
$status_row = pg_fetch_row($status_result);
$currentDate = $status_row[0];


if($_SESSION['role_id_client'] == $_SESSION['role_id'])
{
	$relation_query = "SELECT user_id_1 FROM \"OrmasSchema\".relations_view where user_id_2 =".$_SESSION['id'];
	$relation_result= pg_query($relation_query);
	$relation_row = pg_fetch_array($relation_result);
$form_string= "
<div class='form-body'>
	<form method='post' id = 'return-form'>
		<div class='form-title'>
			<label>Создать возврат</label>
		</div>
		<input type='hidden' name='form_type' value='return'/>
		<input type='hidden' name='client' value='".$_SESSION['id']."'/>
		<input type='hidden' name='date' value='".$currentDate."'/>
		<input type='hidden' name='employee' id ='employee' value='".$relation_row['user_id_1']."'/>
		<input type='hidden' name='status' value='".$status_id."'/>
		<input type='hidden' name='returncount' id ='returncount' value=''/>
		<input type='hidden' name='sum' id='sum' value=''/>
		<input type='hidden' name='currency' value='".$currency_id."'/>
		<input type='hidden' name='prices' value='".json_encode($productPrice)."'/>
		<div class='form-content'>
			<div class='addable'>
				<div class='close-bar'>
					<!--<div class='close-img'>
					</div>-->
				</div>
				<div class='my-row'>
					<div class='float-left'>
						<label class='float-left form-label'>Виберите продукт:</label>
						<select class='form-prod' name='product[]'>
						".$product_list_all."
						</select>
					</div>
					<div >
						<label class='float-left form-label'>Количество:</label>
						<input class ='form-count' type='number' name='count[]'/>
					</div>
				</div>
			</div>
		</div>
		<div class='form-button'>
			<div class='form-button-content'>
				<div class='form-button-img' class='float-left'>
				</div>
				<div class='form-buttom-text'>
					Добавить еще...
				</div>
			</div>
		</div>
		<div class='from-submit'>
			<input class='form-submit' type='button' value='Создать' onclick='SubmitReturnFormForClinet()' id='sub-button'/>
		<div>
	</form>
</div>";
echo ($form_string);
}
if($_SESSION['role_id_expeditor'] == $_SESSION['role_id'])
{	
$client_options = "";
if(empty($client_options))
{
$query_client = "SELECT user_id_2 FROM \"OrmasSchema\".relations_view WHERE user_id_1=".$_SESSION['id'];			
$result_clinet = pg_query($query_client);

while ($row_user = pg_fetch_array($result_clinet)) {
	$query = "SELECT user_id, user_name, user_surname, user_phone, city_name, user_address, firm	 FROM \"OrmasSchema\".clients_view WHERE user_id=".$row_user[0];			
	$result = pg_query($query);
	while ($row = pg_fetch_array($result)) {
		$client_options .= "<option value='".$row[0]."'>".$row[1].", ".$row[2].", ".$row[3].", ".$row[6]."</option>";
	}
}
}
$form_string= "
<script>
  $(document).ready(function() { 
            $('#selected-clinet').select2({
                    placeholder: '',
                    allowClear: false
             }); 
			$('.form-prod').select2({
                    placeholder: '',
                    allowClear: false
            }); 
        });
</script>
<div class='form-body'>
	<form method='post' id = 'return-form'>
		<div class='form-title'>
			<label>Создать возврат</label>
		</div>
		<input type='hidden' name='form_type' value='return'/>
		<input type='hidden' name='date' value='".$currentDate."'/>
		<input type='hidden' name='employee' value='".$_SESSION['id']."'/>
		<input type='hidden' name='status' value='".$status_id."'/>
		<input type='hidden' name='returncount' id ='returncount' value=''/>
		<input type='hidden' name='sum' id='sum' value=''/>
		<input type='hidden' name='currency' value='".$currency_id."'/>
		<input type='hidden' name='prices' value='".json_encode($productPrice)."'/>
		<div class='form-content'>
			<div class='my-row'>
					<div class='float-left'>
						<label class='float-left form-label'>Виберите клиента:</label>
						<select class='form-client' name='selected_clinet' id='selected-clinet'>
						".$client_options."
						</select>
					</div>
			</div>";
			for($i = 0; $i < count($product_list) ; $i++)
			{
			$form_string .= "<div class='addable'>
				<div class='close-bar'>
					<!--<div class='close-img'>
					</div>-->
				</div>
				
				<div class='my-row'>
					<div class='float-left'>
						<label class='float-left form-label'>Виберите продукт:</label>
						<select class='form-prod' name='product[]'>
						".$product_list[$i]."
						</select>
					</div>
					<div >
						<label class='float-left form-label'>Количество:</label>
						<input class ='form-count' type='number' name='count[]' value='0' min='0'/>
					</div>
				</div>
			</div>";
			}
		$form_string .= "</div>
		<!--<div class='form-button'>
			<div class='form-button-content'>
				<div class='form-button-img'>
				</div>
				<div class='form-buttom-text'>
					Добавить еще...
				</div>
			</div>
		</div>-->
		<div class='from-submit'>
			<input class='form-submit' type='button' value='Создать' onclick='SubmitReturnForm()' id='sub-button'/>
		<div>
	</form>
</div>";
echo ($form_string);
}
?>