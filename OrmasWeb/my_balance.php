<?php
	session_start();
	require_once 'logsql.php';
?>
<?php
	if($_SESSION['role_id_purveyor_manager'] == $_SESSION['role_id'])
	{
		$query_group_id = "SELECT * FROM \"OrmasSchema\".user_group_view where user_id = ".$_SESSION['id'];	
		$result_group_id = pg_query($query_group_id);
		$row_group_id = pg_fetch_array($result_group_id);
		$group_id=0;
		if($row_group_id)
		{
			$group_id = $row_group_id['group_id'];
		}
		
		$query_user_id = "SELECT * FROM \"OrmasSchema\".user_group_view where group_id = ".$group_id;	
		$result_user_id = pg_query($query_user_id);
		$user_id="";
		while ($row_user_id = pg_fetch_array($result_user_id)) {
		   $user_list .= $row_user_id['user_id'].",";
		}
		$user_id_list = substr($user_list, 0, -1);
		
		$query = "SELECT balance_id, user_name, user_surname, subaccount_number, current_balance, currency_name FROM \"OrmasSchema\".balances_view WHERE user_id IN (".$user_id_list.");";			
		$result = pg_query($query);
		$string_out = "<table id='my-balance-table'><caption>Мой баланс</cation><thead><tr><th>ID счета</th><th>Имя</th><th>Фамилия</th><th>Номер счета</th><th>Сумма счета</th><th>Валюта</th></tr></thead><tbody>";
		$totalSum=0;
		$curName="";
		$sum=0;
		while ($row = pg_fetch_array($result)) {
			$subacc_parent_number = substr($row[3],0,5);
			$sum=0;
			$sum=$row[4]+0;
			if($subacc_parent_number == "10520" or $subacc_parent_number == "11620" or $subacc_parent_number == "22010" or $subacc_parent_number == "10410")
			{
				$string_out =$string_out."<tr>";
				$string_out =$string_out."<td>$row[0]</td>";
				$string_out =$string_out."<td>$row[1]</td>";
				$string_out =$string_out."<td>$row[2]</td>";
				$string_out =$string_out."<td>$row[3]</td>";
				$string_out =$string_out."<td>$sum</td>";
				$string_out =$string_out."<td>$row[5]</td>";
				$string_out =$string_out."</tr>";
				$totalSum = $totalSum + $row[4];
				$curName = $row[5];
			}
		}
		$string_out = $string_out."</tbody></table>";
		
		$string_out = $string_out."<div><b>Всего у вас $totalSum $curName</b></div>";
		
		$string_out .= "<script>
				$(document).ready( function () {
					$('#my-balance-table').DataTable();
				});
		</script>";
		
		echo $string_out;
	}
	if($_SESSION['role_id_client'] == $_SESSION['role_id'])
	{
		$query = "SELECT balance_id, user_name, user_surname, subaccount_number, current_balance, currency_name FROM \"OrmasSchema\".balances_view WHERE user_id = ".$_SESSION['id'].";";			
		$result = pg_query($query);
		$string_out = "<table id='my-balance-table'><caption>Мой баланс</cation><thead><tr><th>ID счета</th><th>Имя</th><th>Фамилия</th><th>Номер счета</th><th>Сумма счета</th><th>Валюта</th></tr></thead><tbody>";
		$sum=0;
		while ($row = pg_fetch_array($result)) {
			$sum=0;
			$sum=$row[4]+0;
			$string_out =$string_out."<tr>";
			$string_out =$string_out."<td>$row[0]</td>";
			$string_out =$string_out."<td>$row[1]</td>";
			$string_out =$string_out."<td>$row[2]</td>";
			$string_out =$string_out."<td>$row[3]</td>";
			$string_out =$string_out."<td>$sum</td>";
			$string_out =$string_out."<td>$row[5]</td>";
			$string_out =$string_out."</tr>";
		}
		$string_out = $string_out."</tbody></table>";
		
		$string_out .= "<script>
				$(document).ready( function () {
					$('#my-balance-table').DataTable();
				});
		</script>";
		
		echo $string_out;
	}
	if($_SESSION['role_id_purveyor'] == $_SESSION['role_id'])
	{
		$query = "SELECT balance_id, user_name, user_surname, subaccount_number, current_balance, currency_name FROM \"OrmasSchema\".balances_view WHERE user_id = ".$_SESSION['id'].";";			
		$result = pg_query($query);
		$string_out = "<table id='my-balance-table'><caption>Мой баланс</cation><thead><tr><th>ID счета</th><th>Имя</th><th>Фамилия</th><th>Номер счета</th><th>Сумма счета</th><th>Валюта</th></tr></thead><tbody>";
		$sum=0;
		while ($row = pg_fetch_array($result)) {
			$sum=0;
			$sum=$row[4]+0;
			$sum=$sum*(-1);
			$string_out =$string_out."<tr>";
			$string_out =$string_out."<td>$row[0]</td>";
			$string_out =$string_out."<td>$row[1]</td>";
			$string_out =$string_out."<td>$row[2]</td>";
			$string_out =$string_out."<td>$row[3]</td>";
			$string_out =$string_out."<td>$sum</td>";
			$string_out =$string_out."<td>$row[5]</td>";
			$string_out =$string_out."</tr>";
		}
		$string_out = $string_out."</tbody></table>";
		
		$string_out .= "<script>
				$(document).ready( function () {
					$('#my-balance-table').DataTable();
				});
		</script>";
		
		echo $string_out;
	}
?>