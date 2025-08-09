<?php
	session_start();
	if(empty($_SESSION['name']) or empty($_SESSION['surname']) or empty($_SESSION['id']) or empty($_SESSION['role_id']))
	{
		header("location:error.php");
	}
	else
	{
		$PageTitle="Ormas";
		function customPageHeader()
		{
			echo ("<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />");
			echo ("<meta name='keywords' content='Ormas, oreder mamagement system, order' />");
			echo ("<meta name='description' content='Oreder mamagement system' />");
			echo ("<meta name='author' content='Main technology Comp.' />");
			echo ("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
			echo ("<meta name='robots' content='all' />");
			echo ("<LINK rel='stylesheet' media='screen' type='text/css' title='Style' href='css/select2.min.css'>");
			echo ("<LINK rel='stylesheet' media='screen' type='text/css' href='css/datatables.min.css'/>");
			echo ("<LINK rel='stylesheet' media='screen' type='text/css' href='css/bootstrap.css'/>");
			echo ("<LINK rel='stylesheet' media='screen' type='text/css' href='css/datepicker.css'/>");
			echo ("<LINK rel='stylesheet' media='screen' type='text/css' title='Style' href='css/registration.css'>");
			echo ("<LINK rel='stylesheet' media='screen' type='text/css' title='Style' href='css/menu.css'>");
			echo ("<script type='text/javascript' src='js/jquery-3.2.1.min.js'></script>");
			echo ("<script type='text/javascript' src='js/select2.min.js'></script>");
			echo ("<script type='text/javascript' src='js/datepicker.js'></script>");
			echo ("<script type='text/javascript' src='js/bootstrap.js'></script>");
			echo ("<script type='text/javascript' src='js/datatables.min.js'></script>");
			echo ("<script type='text/javascript' src='js/main-1.1.js'></script>");
			
		
		}	
		require_once ('header.php');	
	}
?>
<?php
	$status_result= pg_query("SELECT status_id FROM \"OrmasSchema\".status_view where status_name = 'EXECUTED'");
	$status_row = pg_fetch_row($status_result);
	$status_execute_id ="";
	if(!empty($status_row[0]))
	{
		$status_execute_id = $status_row[0];
	}
	
	function GetParentHeadAccID($accID)
	{
		$acc_result = pg_query("SELECT * FROM \"OrmasSchema\".accounts_view WHERE account_id = ".$accID);
		$acc_array = pg_fetch_array($acc_result, null, PGSQL_BOTH);
		if(empty($acc_array))
		{
			return 0;
		}
		$number = 0;
		$headtreechar =0;
		$number = $acc_array['account_number'];
		$headtreechar= substr($number,0,3);
		$headtreechar .= "00";
		$headacc_result = pg_query("SELECT * FROM \"OrmasSchema\".accounts_view WHERE account_number = '".$headtreechar."';");
		$headacc_array = pg_fetch_array($headacc_result, null, PGSQL_BOTH);
		if(empty($headacc_array))
		{
			return 0;
		}
		return $headacc_array['account_id'];
	}
	/*function CreateStockChangeLog($operID)
	{
		$datetime_result = pg_query("SELECT to_char(now()::timestamp(0), 'dd.MM.yyyy hh24:mm')");
		$datetime_array = pg_fetch_array($datetime_result, null, PGSQL_BOTH);
		if(empty($datetime_array))
		{
			return false;
		}
		$log_id ="";
		$id_result = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
		$id_row = pg_fetch_array($id_result, null, PGSQL_BOTH);
		if(empty($id_row))
		{
			return false;
		}
		$log_id = $id_row[0];
		$datetime = $datetime_array[0];
		$user_class =  $_SESSION['id'];
		$operation_id = $operID;
	}*/
	function CreateUnitedSale($orderID, $returnID, $paymentID, $userID, $subaccountID,$currentValue)
	{
		$id_result2 = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
		$id_row2 = pg_fetch_array($id_result2, null, PGSQL_BOTH);
		if(empty($id_row2[0]))
		{
			return false;
		}
		$united_sale_id = $id_row2[0];
		$insert_united_sale_result = pg_query("INSERT INTO \"OrmasSchema\".united_sale(united_sale_id, order_id, return_id, payment_id,
								user_id, subaccount_id, current_value) VALUES($united_sale_id, $orderID, 
								$returnID, $paymentID , $userID, $subaccountID,$currentValue)
								");
		if(!$insert_united_sale_result)
		{
			return false;
		}
		return true;
	}
	
	function UpdateUnitedSale($unitedSaleID, $orderID, $returnID, $paymentID, $userID, $subaccountID)
	{
		if(!empty($orderID) and $orderID>0)
		{
			$update_united_sale_result = pg_query("UPDATE \"OrmasSchema\".united_sale set order_id = $orderID where united_sale_id = $unitedSaleID");
			if(!$update_united_sale_result)
			{
				return false;
			}
		}
		if(!empty($returnID) and $returnID>0)
		{
			
			$update_united_sale_result = pg_query("UPDATE \"OrmasSchema\".united_sale set return_id = $returnID where united_sale_id = $unitedSaleID");
			if(!$update_united_sale_result)
			{
				return false;
			}
		}
		if(!empty($paymentID) and $paymentID>0)
		{
			$update_united_sale_result = pg_query("UPDATE \"OrmasSchema\".united_sale set payment_id = $paymentID where united_sale_id = $unitedSaleID");
			if(!$update_united_sale_result)
			{
				return false;
			}
		}
		return true;
	}
	
	function CheckExsistensUnatedSaleForOrder($orderID)
	{
		$order_result = pg_query("SELECT * from \"OrmasSchema\".orders_view where order_id=$orderID;");
		$order_row = pg_fetch_row($order_result, null, PGSQL_BOTH);
		if(!empty($order_row))
		{
			$united_sale_result = pg_query("SELECT * from \"OrmasSchema\".united_sale_view where user_id = ".$order_row['user_id']." ORDER BY united_sale_id DESC;");
			$united_sale_row = pg_fetch_row($united_sale_result, null, PGSQL_BOTH);
			if(!empty($united_sale_row))
			{
				if($united_sale_row['order_id']  >0)
				{
					return 0;
				}
				else
				{
					if(SearchUnitedByReturn($order_row['order_date'], $united_sale_row['return_id']))
					{
						return $united_sale_row['united_sale_id'];
					}
					if(SearchUnitedByPaymant($order_row['order_date'], $united_sale_row['payment_id']))
					{
						return $united_sale_row['united_sale_id'];
					}
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
		return -1;
	}
	
	function CheckExsistensUnatedSaleForReturn($returnID)
	{
		$return_result = pg_query("SELECT * from \"OrmasSchema\".returns_view where return_id=$returnID;");
		$return_row = pg_fetch_row($return_result, null, PGSQL_BOTH);
		if(!empty($return_row))
		{
			$united_sale_result = pg_query("SELECT * from \"OrmasSchema\".united_sale_view where user_id=".$return_row['user_id']." ORDER BY united_sale_id DESC;");
			$united_sale_row = pg_fetch_row($united_sale_result, null, PGSQL_BOTH);
			if(!empty($united_sale_row))
			{
				if($united_sale_row['return_id'] > 0)
				{
					return 0;
				}
				else
				{
					if(SearchUnitedByOrder($return_row['return_date'], $united_sale_row['order_id']))
					{
						return $united_sale_row['united_sale_id'];
					}
					if(SearchUnitedByPaymant($order_row['return_date'], $united_sale_row['payment_id']))
					{
						return $united_sale_row['united_sale_id'];
					}
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
		return -1;
	}
	
	function CheckExsistensUnatedSaleForPayment($paymentID)
	{
		$payment_result = pg_query("SELECT * from \"OrmasSchema\".payments_view where payment_id=$paymentID;");
		$payment_row = pg_fetch_row($payment_result, null, PGSQL_BOTH);
		if(!empty($payment_row))
		{
			$united_sale_result = pg_query("SELECT * from \"OrmasSchema\".united_sale_view where user_id=".$payment_row['user_id']." ORDER BY united_sale_id DESC;");
			$united_sale_row = pg_fetch_row($united_sale_result, null, PGSQL_BOTH);
			if(!empty($united_sale_row))
			{
				if($united_sale_row['payment_id'] > 0)
				{
					return 0;
				}
				else
				{
					if(SearchUnitedByOrder($return_row['payment_date'], $united_sale_row['order_id']))
					{
						return $united_sale_row['united_sale_id'];
					}
					if(SearchUnitedByReturn($order_row['payment_date'], $united_sale_row['return_id']))
					{
						return $united_sale_row['united_sale_id'];
					}
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
		return -1;
	}
	
	function SearchUnitedByReturn($search_date, $return_id)
	{
		$date = substr($search_date, 0, strpos($search_date, ' '));
		$return_result = pg_query("SELECT * from \"OrmasSchema\".returns_view where return_date like '$date%' and return_id=$return_id ;");
		$return_row = pg_fetch_row($return_result, null, PGSQL_BOTH);
		if(!empty($return_row))
		{
				return true;
		}
		else
		{
			return false;
		}
	}
	
	
	
	function SearchUnitedByPaymant($search_date, $payment_id)
	{
		$date = substr($search_date, 0, strpos($search_date, ' '));
		$payment_result = pg_query("SELECT * from \"OrmasSchema\".payments_view where payment_date like '$date%' and payment_id=$payment_id;");
		$payment_row = pg_fetch_row($payment_result, null, PGSQL_BOTH);
		if(!empty($payment_row))
		{
				return true;
		}
		else
		{
			return false;
		}
	}
	
	function SearchUnitedByOrder($search_date, $order_id)
	{
		$date = substr($search_date, 0, strpos($search_date, ' '));
		$order_result = pg_query("SELECT * from \"OrmasSchema\".orders_view where order_date like '$date%' and order_id=$order_id;");
		$order_row = pg_fetch_row($order_result, null, PGSQL_BOTH);
		if(!empty($order_row))
		{
				return true;
		}
		else
		{
			return false;
		}
	}
	
	function CreateOrderUnited($orderID)
	{
		$unitedID = CheckExsistensUnatedSaleForOrder($orderID);
		if((int)$unitedID == 0)
		{
			$order_result = pg_query("SELECT * from \"OrmasSchema\".orders_view where order_id=$orderID;");
			$order_row = pg_fetch_row($order_result, null, PGSQL_BOTH);
			if(empty($order_row))
			{
				return false;
			}
			$userID=$order_row['user_id'];
			$balance_result = pg_query("SELECT * from \"OrmasSchema\".balances_view where user_id=".$order_row['user_id'].";");
			$balance_row = pg_fetch_row($balance_result, null, PGSQL_BOTH);
			if(empty($balance_row))
			{
				return false;
			}
			$subaccountID=$balance_row['subaccount_id'];
			$subaccount_result = pg_query("SELECT * from \"OrmasSchema\".subaccounts_view where subaccount_id=".$subaccountID.";");
			$subaccount_row = pg_fetch_row($subaccount_result, null, PGSQL_BOTH);
			if(empty($subaccount_row))
			{
				return false;
			}
			$currentValue = $subaccount_row['current_balance'];
			if(CreateUnitedSale($orderID, "0", "0", $userID, $subaccountID,$currentValue))
			{
				return true;
			}
		}
		if((int)$unitedID > 0)
		{
			if(UpdateUnitedSale($unitedID,$orderID, "0", "0", "0", "0"))
			{
				return true;
			}
		}
		return false;
	}
	
	function CreateReturnUnited($returnID)
	{
		$unitedID = CheckExsistensUnatedSaleForReturn($returnID);
		if((int)$unitedID == 0)
		{
			$return_result = pg_query("SELECT * from \"OrmasSchema\".returns_view where return_id=$returnID;");
			$return_row = pg_fetch_row($return_result, null, PGSQL_BOTH);
			if(empty($return_row))
			{
				return false;
			}
			$userID=$return_row['user_id'];
			$balance_result = pg_query("SELECT * from \"OrmasSchema\".balances_view where user_id=".$return_row['user_id'].";");
			$balance_row = pg_fetch_row($balance_result, null, PGSQL_BOTH);
			if(empty($balance_row))
			{
				return false;
			}
			$subaccountID=$balance_row['subaccount_id'];
			$subaccount_result = pg_query("SELECT * from \"OrmasSchema\".subaccounts_view where subaccount_id=".$subaccountID.";");
			$subaccount_row = pg_fetch_row($subaccount_result, null, PGSQL_BOTH);
			if(empty($subaccount_row))
			{
				return false;
			}
			$currentValue = $subaccount_row['current_balance'];
			if(CreateUnitedSale("0", $returnID, "0", $userID, $subaccountID,$currentValue))
			{
				return true;
			}
		}
		if((int)$unitedID > 0)
		{
			if(UpdateUnitedSale($unitedID,"0", $returnID, "0", "0", "0"))
			{
				return true;
			}
		}
		return false;
	}
	
	function CreatePaymentUnited($paymentID)
	{
		$unitedID = CheckExsistensUnatedSaleForPayment($paymentID);
		if((int)$unitedID == 0)
		{
			$payment_result = pg_query("SELECT * from \"OrmasSchema\".payments_view where payment_id=$paymentID;");
			$payment_row = pg_fetch_row($payment_result, null, PGSQL_BOTH);
			if(empty($payment_row))
			{
				return false;
			}
			$userID=$payment_row['user_id'];
			$subaccountID=$payment_row['subaccount_id'];
			$subaccount_result = pg_query("SELECT * from \"OrmasSchema\".subaccounts_view where subaccount_id=".$subaccountID.";");
			$subaccount_row = pg_fetch_row($subaccount_result, null, PGSQL_BOTH);
			if(empty($subaccount_row))
			{
				return false;
			}
			$currentValue = $subaccount_row['current_balance'];
			if(CreateUnitedSale("0", "0", $paymentID, $userID, $subaccountID,$currentValue))
			{
				return true;
			}
		}
		if((int)$unitedID > 0)
		{
			if(UpdateUnitedSale($unitedID,"0", "0", $paymentID, "0", "0"))
			{
				return true;
			}
		}
		return false;
	}
	
	function CreateAccountChangeLog($accountID, $operID)
	{
		$datetime_result = pg_query("SELECT to_char(now()::timestamp(0), 'dd.MM.yyyy hh24:mm');");
		$datetime_array = pg_fetch_array($datetime_result, null, PGSQL_BOTH);
		if(empty($datetime_array))
		{
			return false;
		}
		$log_id ="";
		$id_result = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
		$id_row = pg_fetch_array($id_result, null, PGSQL_BOTH);
		if(empty($id_row))
		{
			return false;
		}
		$log_id = $id_row[0];
		$datetime = $datetime_array[0];
		$user_id= $_SESSION['id'];
		$operation_id = $operID;
		
		$acc_result = pg_query("SELECT * FROM \"OrmasSchema\".accounts_view WHERE account_id = ".$accountID);
		$acc_array = pg_fetch_array($acc_result, null, PGSQL_BOTH);
		if(empty($acc_array))
		{
			return false;
		}
		$accountnumber= $acc_array['account_number'];
		$startBalance= $acc_array['start_balance'];
		$currentBalance= $acc_array['current_balance'];
		$create_account_change_log = pg_query("INSERT INTO \"OrmasSchema\".account_change_log(account_change_log_id, account_id, account_number, start_balance, current_balance,
		log_date, user_id, operation_id) VALUES ($log_id, $accountID, $accountnumber, $startBalance, $currentBalance, '".$datetime."' ,$user_id, $operation_id);");
		if(!$create_account_change_log)
			return false;
		return true;
	}
	function CreateSubaccountChangeLog($accountID,  $operID)
	{
		$datetime_result = pg_query("SELECT to_char(now()::timestamp(0), 'dd.MM.yyyy hh24:mm')");
		$datetime_array = pg_fetch_array($datetime_result, null, PGSQL_BOTH);
		if(empty($datetime_array))
		{
			return false;
		}
		$log_id ="";
		$id_result = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
		$id_row = pg_fetch_array($id_result, null, PGSQL_BOTH);
		if(empty($id_row))
		{
			return false;
		}
		$log_id = $id_row[0];
		$datetime = $datetime_array[0];
		$user_id= $_SESSION['id'];
		$operation_id = $operID;
		
		$acc_result = pg_query("SELECT * FROM \"OrmasSchema\".subaccounts_view WHERE subaccount_id = ".$accountID);
		$acc_array = pg_fetch_array($acc_result, null, PGSQL_BOTH);
		if(empty($acc_array))
		{
			return false;
		}
		
		
		$startBalance= $acc_array['start_balance'];
		$currentBalance= $acc_array['current_balance'];
		
		$create_subaccount_change_log = pg_query("INSERT INTO \"OrmasSchema\".subaccount_change_log(subaccount_change_log_id, subaccount_id, start_balance, current_balance,
		log_date, user_id, operation_id) VALUES ($log_id, $accountID, $startBalance, $currentBalance , '".$datetime."',$user_id, $operation_id);");
		if(!$create_subaccount_change_log)
			return false;
		return true;
	}
	
	function CreateTransportChangeLog($transportID, $productID, $count,$sum, 
				$statusID, $currencyID, $orderID)
	{
		$datetime_result = pg_query("SELECT to_char(now()::timestamp(0), 'dd.MM.yyyy hh24:mm')");
		$datetime_array = pg_fetch_array($datetime_result, null, PGSQL_BOTH);
		if(empty($datetime_array))
		{
			return false;
		}
		$log_id ="";
		$id_result = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
		$id_row = pg_fetch_array($id_result, null, PGSQL_BOTH);
		if(empty($id_row))
		{
			return false;
		}
		$log_id = $id_row[0];
		$datetime = $datetime_array[0];
		$user_id= $_SESSION['id'];
		$operation_id = $orderID;
		$create_transport_change_log = pg_query("INSERT INTO \"OrmasSchema\".transport_change_log(transport_change_log_id, transport_id, product_id, count, sum, status_id,currency_id, log_date, user_id, operation_id)
				VALUES ($log_id, $transportID, $productID, $count,$sum,  $statusID, $currencyID,  '".$datetime."' ,$user_id, $operation_id);");
		echo("<script>alert(".$create_transport_change_log.")</script>");
		if(!$create_transport_change_log)
			return false;
		return true;
	}
	
	function IsOperEntryUnique($entryID, $operationID)
	{
		$ord_result = pg_query("SELECT * FROM \"OrmasSchema\".entry_operation_view WHERE entry_id = $entryID and operation_id = $operationID");
		if(pg_num_rows($ord_result) == 0)
		{
			return true;
		}
		return false;
	}
	function GetParentAccID($accID)
	{
		$subacc_result = pg_query("SELECT * FROM \"OrmasSchema\".subaccounts_view WHERE subaccount_id = ".$accID);
		$subacc_array = pg_fetch_array($subacc_result, null, PGSQL_BOTH);
		if(empty($subacc_array))
		{
			return 0;
		}
		return $subacc_array['account_id'];
	}
	function DebitAccount($accID, $value, $operID)
	{
		$acc_result = pg_query("SELECT * FROM \"OrmasSchema\".accounts_view WHERE account_id = ".$accID);
		$acc_array = pg_fetch_array($acc_result, null, PGSQL_BOTH);
		if(empty($acc_array))
		{
			return false;
		}
		$sum = $acc_array['current_balance'] + $value;
		$update_acc =  pg_query("UPDATE \"OrmasSchema\".accounts SET current_balance = $sum  WHERE account_id = ".$accID);
		if(!$update_acc)
			return false;
		if (!CreateAccountChangeLog($acc_array['account_id'],  $operID))
			return false;
		return true;
	}
	function CreditAccount($accID, $value, $operID)
	{
		$acc_result = pg_query("SELECT * FROM \"OrmasSchema\".accounts_view WHERE account_id = ".$accID);
		$acc_array = pg_fetch_array($acc_result, null, PGSQL_BOTH);
		if(empty($acc_array))
		{
			return false;
		}
		$sum = $acc_array['current_balance'] - $value;
		$update_acc =  pg_query("UPDATE \"OrmasSchema\".accounts SET current_balance = $sum  WHERE account_id = ".$accID);
		if(!$update_acc)
			return false;
		if (!CreateAccountChangeLog($acc_array['account_id'],  $operID))
			return false;
		return true;
	}
	function DebitSubaccount($accID, $value, $operID)
	{
		$acc_result = pg_query("SELECT * FROM \"OrmasSchema\".subaccounts_view WHERE subaccount_id = ".$accID);
		$acc_array = pg_fetch_array($acc_result, null, PGSQL_BOTH);
		if(empty($acc_array))
		{
			return false;
		}
		$sum = $acc_array['current_balance'] + $value;
		$update_acc =  pg_query("UPDATE \"OrmasSchema\".subaccounts SET current_balance = $sum  WHERE subaccount_id = ".$accID);
		if(!$update_acc)
			return false;
		if (!CreateSubaccountChangeLog($acc_array['subaccount_id'],  $operID))
			return false;
		return true;
	}
	function CreditSubaccount($accID, $value, $operID)
	{
		$acc_result = pg_query("SELECT * FROM \"OrmasSchema\".subaccounts_view WHERE subaccount_id = ".$accID);
		$acc_array = pg_fetch_array($acc_result, null, PGSQL_BOTH);
		if(empty($acc_array))
		{
			return false;
		}
		$sum = $acc_array['current_balance'] - $value;
		$update_acc =  pg_query("UPDATE \"OrmasSchema\".subaccounts SET current_balance = $sum  WHERE subaccount_id = ".$accID);
		if(!$update_acc)
			return false;
		if (!CreateSubaccountChangeLog($acc_array['subaccount_id'], $operID))
			return false;
		return true;
	}
	function RecalculateParentDebAcc($debAccID, $value, $operID)
	{
		$parentAcc = GetParentHeadAccID($debAccID);
		if ($parentAcc ==0)
			return false;
		$acc_result = pg_query("SELECT * FROM \"OrmasSchema\".accounts_view WHERE account_id = ".$parentAcc);
		$acc_array = pg_fetch_array($acc_result, null, PGSQL_BOTH);
		if(empty($acc_array))
		{
			return false;
		}
		$sum = $acc_array['current_balance'] + $value;
		$row = "UPDATE \"OrmasSchema\".accounts SET current_balance = $sum  WHERE account_id = ".$parentAcc;
		$update_acc =  pg_query("UPDATE \"OrmasSchema\".accounts SET current_balance = $sum  WHERE account_id = ".$parentAcc);
		if(!$update_acc)
			return false;
		if (!CreateAccountChangeLog($acc_array['account_id'],   $operID))
			return false;
		return true;
	}
	function RecalculateParentCredAcc($credAccID, $value, $operID)
	{
		$parentAcc = GetParentHeadAccID($credAccID);
		if ($parentAcc ==0)
			return false;
		$acc_result = pg_query("SELECT * FROM \"OrmasSchema\".accounts_view WHERE account_id = ".$parentAcc);
		$acc_array = pg_fetch_array($acc_result, null, PGSQL_BOTH);
		if(empty($acc_array))
		{
			return false;
		}
		$sum = $acc_array['current_balance'] - $value;
		$update_acc =  pg_query("UPDATE \"OrmasSchema\".accounts SET current_balance = $sum  WHERE account_id = ".$parentAcc);
		if(!$update_acc)
			return false;
		if (!CreateAccountChangeLog($acc_array['account_id'],   $operID))
			return false;
		return true;
	}
	function CreateEntryAccountRelationForOrder($entryID,$debAccID)
	{
		$entry_acc_id ="";
		$id_result = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
		$id_row = pg_fetch_array($id_result, null, PGSQL_BOTH);
		if(empty($id_row))
		{
			return false;
		}
		$entry_acc_id = $id_row[0];
		$create_entry = pg_query("INSERT INTO \"OrmasSchema\".entry_subaccount(entry_subaccount_id, entry_id, subaccount_id)
				VALUES ($entry_acc_id, $entryID, $debAccID);");
		if(!$create_entry)
			return false;
		return true;
	}
	function CreateEntryAccountRelationForReturn($entryID,$credAccID)
	{
		$entry_acc_id ="";
		$id_result = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
		$id_row = pg_fetch_array($id_result, null, PGSQL_BOTH);
		if(empty($id_row))
		{
			return false;
		}
		$entry_acc_id = $id_row[0];
		$create_entry = pg_query("INSERT INTO \"OrmasSchema\".entry_subaccount(entry_subaccount_id, entry_id, subaccount_id)
				VALUES ($entry_acc_id, $entryID, $credAccID);");
		if(!$create_entry)
			return false;
		return true;
	}
	
	function UpdateTransport($orderID)
	{
		$netcost_sum = 0.0;
		$transport_result =  pg_query("SELECT * FROM \"OrmasSchema\".transports_view where employee_id =".$_SESSION['id']);
		$transport_row = pg_fetch_all($transport_result);
		if(empty($transport_row))
		{
			return false;
		}
		$order_list_result = pg_query("SELECT * FROM \"OrmasSchema\".order_list_view where order_id = ".$orderID);
		while ($order_list_row = pg_fetch_array($order_list_result)) {
			if(empty($order_list_row))
			{
				return false;
			}
			$transport_list_result = pg_query("SELECT * FROM \"OrmasSchema\".transport_list_view where transport_id = ".$transport_row[0]['transport_id']." AND product_id=".$order_list_row['product_id']);
			while ($transport_list_row = pg_fetch_array($transport_list_result)) {
				if(empty($transport_list_row))
				{
					return false;
				}
				$net_cost_result = pg_query("SELECT * FROM \"OrmasSchema\".net_cost_view where product_id = ".$order_list_row['product_id']);
				$net_cost_row = pg_fetch_array($net_cost_result);
				if(empty($net_cost_row))
				{
					return false;
				}
				$netcost_sum += $order_list_row['count'] * $net_cost_row['net_cost_value'];
				if(($transport_list_row['count'] - $order_list_row['count']) < 0)
				{
					
					$product_result = pg_query("SELECT * FROM \"OrmasSchema\".products_view where product_id = ".$order_list_row['product_id']);
					$product_row = pg_fetch_array($product_result);
					if(empty($product_row))
					{
						return false;
					}					
					echo "<script>alert('У Вас мало товара\(ов\) в транспорте! В транспорте продукта \'".$product_row['product_name']."\' в количестве ".$transport_list_row['count'] ." штук\(и\). Не возможно отгрузить ".$order_list_row['count']." штук\(и\) из этого товара')</script>";
					return false;
				}
				$update_list_order =  pg_query("UPDATE \"OrmasSchema\".transport_list SET count = ($transport_list_row[count] - $order_list_row[count]), sum = ($transport_list_row[sum] - ($order_list_row[count] * $net_cost_row[net_cost_value]))  WHERE transport_list_id = ".$transport_list_row['transport_list_id']);
				if(!$update_list_order)
				{
					return false;
				}
				
				$transport_list_result2 = pg_query("SELECT * FROM \"OrmasSchema\".transport_list_view where transport_list_id = ".$transport_list_row['transport_list_id']);
				$transport_list_row2 = pg_fetch_array($transport_list_result2);
				
				if(!empty($transport_list_row2['count']))
				{
					if(!CreateTransportChangeLog($transport_row[0]['transport_id'], $transport_list_row2['product_id'], $transport_list_row2['count'], $transport_list_row2['sum'], 
					$transport_list_row2['status_id'], $transport_list_row2['currency_id'], $orderID))
					{
						return false;
					}
				}
			}
		}
		if($netcost_sum == 0)
			return false;
		$order_result = pg_query("SELECT * FROM \"OrmasSchema\".orders_view where order_id = ".$orderID);
		$order_row = pg_fetch_all($order_result);
		if(!empty($order_row))
		{
				$acc_10742 = 0;
				$acc_55010 =0;
				//print_r($order_row);
				$acc_result_10742 = pg_query("SELECT * FROM \"OrmasSchema\".accounts_view where account_number = '10742'");
				$acc_row_10742 = pg_fetch_all($acc_result_10742);
				if($acc_row_10742[0]['account_id'])
				{
					$acc_10742 = $acc_row_10742[0]['account_id'];
				}
				$acc_result_55010 = pg_query("SELECT * FROM \"OrmasSchema\".accounts_view where account_number = '55010'");
				$acc_row_55010 = pg_fetch_all($acc_result_55010);
				if($acc_row_55010[0]['account_id'])
				{
					$acc_55010 = $acc_row_55010[0]['account_id'];
				}
				if($acc_10742 != 0 && $acc_55010 != 0)
				{	
					$entry_id =CreateEntry($acc_55010, $netcost_sum, $acc_10742, 0, $orderID);
					if($entry_id != 0)
					{
						if(!IsOperEntryUnique($entry_id, $orderID))
							return false;
						$ransport_string = "INSERT INTO \"OrmasSchema\".entry_operation(entry_operation_id,
								entry_id, operation_id) VALUES((SELECT nextval('\"OrmasSchema\".id_seq')), $entry_id,
								$orderID)";
						$insert_entry_operation_result = pg_query($ransport_string);
						if($insert_entry_operation_result)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
				}
		}
		return false;
	}
	
	function UpdateOrder($orderID)
	{
		$order_result = pg_query("SELECT * FROM \"OrmasSchema\".orders_view where order_id = ".$orderID);
		$order_row = pg_fetch_all($order_result);
		if(empty($order_row))
		{
			return false;
		}
		$status_result =  pg_query("SELECT * FROM \"OrmasSchema\".status_view where status_name = 'EXECUTED'");
		$status_row = pg_fetch_all($status_result);
		if(empty($status_row))
		{
			return false;
		}
		
		// check correction
		$order_list_result=pg_query("SELECT count,sum FROM \"OrmasSchema\".order_list_view where order_id = ".$orderID);
		$order_list_all = pg_fetch_all($order_list_result);
		if(empty($order_list_all))
		{
			return false;
		}
		else{
			$count=0;
			$sum=0;
			foreach($order_list_all as $row) {
				$count =$count+ $row['count'];
				$sum = $sum+ $row['sum'];
			}
			if (abs((floatval($count)-floatval($order_row[0]['count']))) > 0.0001 or
				abs((floatval($sum)-floatval($order_row[0]['sum']))) > 0.0001) {
					return false;
				}
		}
		
		$current_date_result = pg_query("SELECT \"OrmasSchema\".getcurrentdate()");
		$current_date = pg_fetch_array($current_date_result, null, PGSQL_BOTH);
		if(empty($current_date))
		{
			return false;
		}
		
		$status_id = $status_row[0]['status_id'];
		$date = $current_date[0];
			
		$update_order =  pg_query("UPDATE \"OrmasSchema\".orders SET status_id = $status_id, execution_date = '$date'  WHERE order_id = ".$orderID);
		if(!$update_order)
			return false;
		return true;
	}
	
	function CreateOrderPriceCorrection($orderListID, $orderID, $productID, $count, $sum, $employee, $client)
	{
		
		$product_result=pg_query("SELECT * FROM \"OrmasSchema\".products_view where product_id = ".$productID);
		$product = pg_fetch_all($product_result);
		if(empty($product))
		{
			return false;
		}
		$price_extension_result=pg_query("SELECT * FROM \"OrmasSchema\".price_extension_view where product_id = ".$productID." and expeditor_id = ".$employee."ORDER BY price_extension_id DESC;");
		$price_extension = pg_fetch_all($price_extension_result);
		if(!empty($price_extension))
		{
			$id_result = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
			$id_row = pg_fetch_array($id_result, null, PGSQL_BOTH);
			if(empty($id_row[0]))
			{
				return false;
			}
			$standart_value= $count * $product[0]['price'];
			$price_extension_id=$price_extension[0]['price_extension_id'];
			$create_extenstion = pg_query("INSERT INTO \"OrmasSchema\".order_price_correction(order_price_correction_id, order_id, price_extension_id, order_list_id, srandart_value, new_value)
			VALUES ($id_row[0], $orderID, $price_extension_id, $orderListID, $standart_value , $sum);");
			
			if(!$create_extenstion)
			{
				
				return false;
			}
			
			
			return true;
		}
		else
		{
			return true;
		}
	}
	
	function CreateReturnPriceCorrection($returnListID, $returnID, $productID, $count, $sum, $employee, $client)
	{
		
		$product_result=pg_query("SELECT * FROM \"OrmasSchema\".products_view where product_id = ".$productID);
		$product = pg_fetch_all($product_result);
		if(empty($product))
		{
			return false;
		}
		$price_extension_result=pg_query("SELECT * FROM \"OrmasSchema\".price_extension_view where product_id = ".$productID." and expeditor_id = ".$employee."ORDER BY price_extension_id DESC;");
		$price_extension = pg_fetch_all($price_extension_result);
		if(!empty($price_extension))
		{
			$id_result = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
			$id_row = pg_fetch_array($id_result, null, PGSQL_BOTH);
			if(empty($id_row[0]))
			{
				return false;
			}
			$standart_value= $count * $product[0]['price'];
			$price_extension_id=$price_extension[0]['price_extension_id'];
			$create_extenstion = pg_query("INSERT INTO \"OrmasSchema\".return_price_correction(return_price_correction_id, return_id, price_extension_id, return_list_id, srandart_value, new_value)
			VALUES ($id_row[0], $returnID, $price_extension_id, $returnListID, $standart_value , $sum);");
			
			if(!$create_extenstion)
			{
				
				return false;
			}
			
			
			return true;
		}
		else
		{
			return true;
		}
	}
	
	function UpdateOrderToError($orderID)
	{
		$order_result = pg_query("SELECT * FROM \"OrmasSchema\".orders_view where order_id = ".$orderID);
		$order_row = pg_fetch_all($order_result);
		if(empty($order_row))
		{
			return false;
		}
		$status_result =  pg_query("SELECT * FROM \"OrmasSchema\".status_view where status_name = 'ERROR'");
		$status_row = pg_fetch_all($status_result);
		if(empty($status_row))
		{
			return false;
		}
		
		$current_date_result = pg_query("SELECT \"OrmasSchema\".getcurrentdate()");
		$current_date = pg_fetch_array($current_date_result, null, PGSQL_BOTH);
		if(empty($current_date))
		{
			return false;
		}
		
		$status_id = $status_row[0]['status_id'];
		$date = $current_date[0];
			
		$update_order =  pg_query("UPDATE \"OrmasSchema\".orders SET status_id = $status_id, execution_date = '$date'  WHERE order_id = ".$orderID);
		if(!$update_order)
			return false;
		return true;
	}
	
	
	
	function UpdateReturn($returnID)
	{
		$return_result = pg_query("SELECT * FROM \"OrmasSchema\".returns_view where return_id = ".$returnID);
		$return_row = pg_fetch_all($return_result);
		if(empty($return_row))
		{
			return false;
		}
		$status_result =  pg_query("SELECT * FROM \"OrmasSchema\".status_view where status_name = 'EXECUTED'");
		$status_row = pg_fetch_all($status_result);
		if(empty($status_row))
		{
			return false;
		}
		
		// check correction
		$retrun_list_result=pg_query("SELECT count,sum FROM \"OrmasSchema\".return_list_view where return_id = ".$returnID);
		$retrun_list_all = pg_fetch_all($retrun_list_result);
		if(empty($retrun_list_all))
		{
			return false;
		}
		else{
			$count=0;
			$sum=0;
			foreach($order_list_all as $row) {
				$count =$count+ $row['count'];
				$sum = $sum+ $row['sum'];
			}
			if (abs((floatval($count)-floatval($order_row[0]['count']))) > 0.0001 or
				abs((floatval($sum)-floatval($order_row[0]['sum']))) > 0.0001) {
					return false;
				}
		}
		
		$current_date_result = pg_query("SELECT \"OrmasSchema\".getcurrentdate()");
		$current_date = pg_fetch_array($current_date_result, null, PGSQL_BOTH);
		if(empty($current_date))
		{
			return false;
		}
		
		$status_id = $status_row[0]['status_id'];
		$date = $current_date[0];
			
		$update_return =  pg_query("UPDATE \"OrmasSchema\".returns SET status_id = $status_id, execution_date = '$date'  WHERE return_id = ".$returnID);
		if(!$update_return)
		{
			return false;
		}
		return true;
	}
	
	function UpdateReturnToError($returnID)
	{
		$return_result = pg_query("SELECT * FROM \"OrmasSchema\".returns_view where return_id = ".$returnID);
		$return_row = pg_fetch_all($return_result);
		if(empty($return_row))
		{
			return false;
		}
		$status_result =  pg_query("SELECT * FROM \"OrmasSchema\".status_view where status_name = 'ERROR'");
		$status_row = pg_fetch_all($status_result);
		if(empty($status_row))
		{
			return false;
		}
		
		$current_date_result = pg_query("SELECT \"OrmasSchema\".getcurrentdate()");
		$current_date = pg_fetch_array($current_date_result, null, PGSQL_BOTH);
		if(empty($current_date))
		{
			return false;
		}
		
		$status_id = $status_row[0]['status_id'];
		$date = $current_date[0];
			
		$update_return =  pg_query("UPDATE \"OrmasSchema\".returns SET status_id = $status_id, execution_date = '$date'  WHERE return_id = ".$returnID);
		if(!$update_return)
		{
			return false;
		}
		return true;
	}
	
	function UpdateConsumeToError($consumeID)
	{
		$consume_result = pg_query("SELECT * FROM \"OrmasSchema\".consume_products_view where consume_product_id = ".$consumeID);
		$consume_row = pg_fetch_all($consume_result);
		if(empty($consume_row))
		{
			return false;
		}
		$status_result =  pg_query("SELECT * FROM \"OrmasSchema\".status_view where status_name = 'ERROR'");
		$status_row = pg_fetch_all($status_result);
		if(empty($status_row))
		{
			return false;
		}
		
		$current_date_result = pg_query("SELECT \"OrmasSchema\".getcurrentdate()");
		$current_date = pg_fetch_array($current_date_result, null, PGSQL_BOTH);
		if(empty($current_date))
		{
			return false;
		}
		
		$status_id = $status_row[0]['status_id'];
		$date = $current_date[0];
			
		$update_consume =  pg_query("UPDATE \"OrmasSchema\".consume_products SET status_id = $status_id, execution_date = '$date'  WHERE consume_product_id = ".$consumeID);
		if(!$update_consume)
		{
			return false;
		}
		return true;
	}
	
	function CreateEntry($debAccID, $sum, $credAccID, $userID, $operID)
	{
		$current_date_result = pg_query("SELECT \"OrmasSchema\".getcurrentdate()");
		$current_date = pg_fetch_array($current_date_result, null, PGSQL_BOTH);
		if(empty($current_date))
		{
			return 0;
		}
		$date ="";
		$entry_id ="";
		$parentDebAccID =0;
		$parentCredAccID=0;
		if($userID > 0)
		{
			if(GetParentAccID($debAccID) != 0)
			{
				$description= "Товар продан и отгружен клиенту с ID = ".$userID;
			}
			if(GetParentAccID($credAccID) != 0)
			{
				$description= "Возврат товара от клиента с ID = ".$userID;
			}
		}
		else
		{
			$description= "Списание товаров по себестоимости";
		}
		$date = $current_date[0];
		$id_result = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
		$id_row = pg_fetch_array($id_result, null, PGSQL_BOTH);
		if(empty($id_row))
		{
			return 0;
		}
		$entry_id = $id_row[0];
		$parentDebAccID = GetParentAccID($debAccID);
		$parentCredAccID = GetParentAccID($credAccID);
		if($parentDebAccID == 0)
			$parentDebAccID=$debAccID;
		if($parentCredAccID == 0)
			$parentCredAccID=$credAccID;
		
		if($parentDebAccID == 0 || $parentCredAccID == 0)
			return 0;
		
		$create_entry = pg_query("INSERT INTO \"OrmasSchema\".entries(entry_id, entry_date, debiting_account_id, value, crediting_account_id, description)
				VALUES ($entry_id, '$date', $parentDebAccID, $sum, $parentCredAccID, '$description');");
		if(!$create_entry)
			return 0;
		
		if(!DebitAccount($parentDebAccID, $sum, $operID) || !CreditAccount($parentCredAccID, $sum, $operID))
			return 0;
		
		if(!RecalculateParentDebAcc($parentDebAccID, $sum, $operID) || !RecalculateParentCredAcc($parentCredAccID, $sum, $operID))
			return 0;
		
		if(GetParentAccID($debAccID) != 0)
		{
			if(!DebitSubaccount($debAccID, $sum, $operID))
				return 0;
			if(!CreateEntryAccountRelationForOrder($entry_id, $debAccID))
				return 0;
		}
		if(GetParentAccID($credAccID) != 0)
		{
			if(!CreditSubaccount($credAccID, $sum, $operID))
				return 0;
			if(!CreateEntryAccountRelationForReturn($entry_id, $credAccID))
				return 0;
		}
		return $entry_id;
		
	}

	$productPrice = Array();
	$productNetCost = Array();
	$product_type_result = pg_query("SELECT product_type_id FROM \"OrmasSchema\".product_types_view where product_type_code = 'PRODUCT'");
    $product_type_row = pg_fetch_array($product_type_result);
	$product_result = pg_query("SELECT * FROM \"OrmasSchema\".products_view where product_type_id = ".$product_type_row[0]);
	$product_row = pg_fetch_all($product_result);
	$product_list ="";
	if(!empty($product_row[0]))
	{
		$row_count = pg_num_rows($product_result);
		for($i=0;$i<$row_count;$i++)
		{
			if($_SESSION['role_id_client'] == $_SESSION['role_id'])
			{
				$productPrice[$i] = array("id" => $product_row[$i]['product_id'], "price" => $product_row[$i]['price']);
			}
			if($_SESSION['role_id_expeditor'] == $_SESSION['role_id'])
			{
				$price_extension_result=pg_query("SELECT * FROM \"OrmasSchema\".price_extension_view where product_id = ".$product_row[$i]['product_id']." and expeditor_id = ".$_SESSION['id']."ORDER BY price_extension_id DESC;");
				$price_extension = pg_fetch_all($price_extension_result);
				if(!empty($price_extension[0]))
				{
					$productPrice[$i] = array("id" => $product_row[$i]['product_id'], "price" => $product_row[$i]['price'] +$price_extension[0]['value']);
				}
				else
				{
					$productPrice[$i] = array("id" => $product_row[$i]['product_id'], "price" => $product_row[$i]['price']);
				}
				
				$net_cost_result=pg_query("SELECT * FROM \"OrmasSchema\".net_cost_view where product_id = ".$product_row[$i]['product_id']." ORDER BY net_cost_id DESC;");
				$net_cost = pg_fetch_all($net_cost_result);
				if(!empty($net_cost[0]))
				{
					$productNetCost[$i] = array("id" => $product_row[$i]['product_id'], "price" => $net_cost[0]['net_cost_value']);
				}
				else
				{
					$productNetCost[$i] = array("id" => $product_row[$i]['product_id'], "price" => $net_cost[0]['net_cost_value']);
				}
			}
			$product_list .= "<option value='".$product_row[$i]['product_id']."'>".$product_row[$i]['product_name']."</option>";
			
		}
	}
// Logic section
	if(isset($_POST['execute']))
	{
		$clear_transaction = pg_query("ROLLBACK");
		$start_transaction = pg_query("BEGIN ISOLATION LEVEL SERIALIZABLE;");
		if($start_transaction)
		{
			$order_result = pg_query("SELECT * FROM \"OrmasSchema\".orders_view where order_id = ".$_POST['execute']);
			$order_row = pg_fetch_all($order_result);
			if(!empty($order_row))
			{
				if($order_row[0]['status_id'] == $status_execute_id)
				{
					echo "<script>alert('Повторная отправка формы!')</script>";
				}
				else
				{
					$clinet_acc_id = 0;
					$acc_44010 =0;
					//print_r($order_row);
					
					$balance_result = pg_query("SELECT * FROM \"OrmasSchema\".balances_view where user_id = ".$order_row[0]['user_id']);
					$balance_row = pg_fetch_all($balance_result);
					if($balance_row[0]['subaccount_id'])
					{
						$clinet_acc_id = $balance_row[0]['subaccount_id'];
					}
					$acc_result = pg_query("SELECT * FROM \"OrmasSchema\".accounts_view where account_number = '44010'");
					$acc_row = pg_fetch_all($acc_result);
					if($acc_row[0]['account_id'])
					{
						$acc_44010 = $acc_row[0]['account_id'];
					}
					if($clinet_acc_id != 0 && $acc_44010 != 0)
					{
						$order_entry_id = CreateEntry($clinet_acc_id, $order_row[0]['sum'], $acc_44010, $order_row[0]['user_id'], $order_row[0]['order_id']);
						if($order_entry_id != 0)
						{
							if(UpdateOrder($order_row[0]['order_id']))
							{
								if(UpdateTransport($order_row[0]['order_id']))
								{
									if(IsOperEntryUnique($order_entry_id, $order_row[0]['order_id']))
									{
										$orderID= $order_row[0]['order_id'];
										$insert_entry_operation_result = pg_query("INSERT INTO \"OrmasSchema\".entry_operation(entry_operation_id,
										entry_id, operation_id) VALUES((SELECT nextval('\"OrmasSchema\".id_seq')), $order_entry_id,	$orderID)");
										if($insert_entry_operation_result)
										{
											$commit_transaction = pg_query("COMMIT;");
											if(!$commit_transaction)
											{
												$rollback_transaction = pg_query("ROLLBACK;");
												echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
											}
											echo ("<script>
												window.location = 'menu.php';
											</script>");
										}
										else
										{
											echo "<script>alert('У Вас нет некоторых товаров в транспорте или их мало.')</script>";
										}
									}
								}
								else
								{
									echo "<script>alert('У Вас нет некоторых товаров в транспорте или их мало.')</script>";
								}
							}
							else
							{
								echo "<script>alert('Не возможно изменить статус заказа.')</script>";
							}
						}
						else
						{
							echo "<script>alert('Ошибка при создании проводки.')</script>";
						}
					}
					else
					{
						echo "<script>alert('Ошибка счета не найдены.')</script>";
					}
				}
			}
		}
		$rollback_transaction = pg_query("ROLLBACK;");
	}
	if(isset($_POST['order_error']))
	{
		$clear_transaction = pg_query("ROLLBACK");
		$start_transaction = pg_query("BEGIN ISOLATION LEVEL SERIALIZABLE;");
		if($start_transaction)
		{
			$order_result = pg_query("SELECT * FROM \"OrmasSchema\".orders_view where order_id = ".$_POST['order_error']);
			$order_row = pg_fetch_all($order_result);
			if(!empty($order_row))
			{
				if($order_row[0]['status_id'] == $status_execute_id)
				{
					echo "<script>alert('Не возможно удалить этот документ!')</script>";
				}
				else
				{
					if(UpdateOrderToError($order_row[0]['order_id']))
					{
						$commit_transaction = pg_query("COMMIT;");
						if(!$commit_transaction)
						{
							$rollback_transaction = pg_query("ROLLBACK;");
							echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
						}
						echo ("<script>
							window.location = 'menu.php';
						</script>");
					}
					else
					{
						echo "<script>alert('Не возможно изменить статус заказа.')</script>";
					}
				}
			}
		}
		$rollback_transaction = pg_query("ROLLBACK;");
	}
	if(isset($_POST['execute_return'])) // IMPORTANT THIS METHOD IS WRONG, DONT USE IT! Before, using rework
	{
		$clear_transaction = pg_query("ROLLBACK");
		$start_transaction = pg_query("BEGIN ISOLATION LEVEL SERIALIZABLE;");
		if($start_transaction)
		{
			$return_result = pg_query("SELECT * FROM \"OrmasSchema\".returns_view where return_id = ".$_POST['execute_return']);
			$return_row = pg_fetch_all($return_result);
			if(!empty($return_row))
			{
				if($return_row[0]['status_id'] == $status_execute_id)
				{
					echo "<script>alert('Повторная отправка формы!')</script>";
				}
				else
				{
					$clinet_acc_id = 0;
					$acc_10740 =0;
					$balance_result = pg_query("SELECT * FROM \"OrmasSchema\".balances_view where user_id = ".$return_row[0]['user_id']);
					$balance_row = pg_fetch_all($balance_result);
					if($balance_row[0]['subaccount_id'])
					{
						$clinet_acc_id = $balance_row[0]['subaccount_id'];
					}
					$acc_result = pg_query("SELECT * FROM \"OrmasSchema\".accounts_view where account_number = '10740'");
					$acc_row = pg_fetch_all($acc_result);
					if($acc_row[0]['account_id'])
					{
						$acc_10740 = $acc_row[0]['account_id'];
					}
					if($clinet_acc_id != 0 && $acc_10740 != 0)
					{
						$return_entry_id = CreateEntry($acc_10740, $return_row[0]['sum'], $clinet_acc_id, $return_row[0]['user_id']);
						if($return_entry_id !=0)
						{
							if(UpdateReturn($return_row[0]['return_id']))
							{
								if(IsOperEntryUnique($return_entry_id, $orderID))
								{
									$returnID= $order_row[0]['return_id'];
									$insert_entry_operation_result = pg_query("INSERT INTO \"OrmasSchema\".entry_operation(entry_operation_id,
									entry_id, operation_id) VALUES((SELECT nextval('\"OrmasSchema\".id_seq')), $return_entry_id,	$returnID)");
									if($insert_payment_employee_result)
									{
										$commit_transaction = pg_query("COMMIT;");
											if(!$commit_transaction)
											{
												$rollback_transaction = pg_query("ROLLBACK;");
												echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
											}
											echo ("<script>
											window.location = 'menu.php';
											</script>");
									}
									else
									{
										echo "<script>alert('Не возможно изменить статус возврата.')</script>";
									}
								}
							}
							else
							{
								echo "<script>alert('Не возможно изменить статус возврата.')</script>";
							}
						}
						else
						{
							echo "<script>alert('Ошибка при создании проводки.')</script>";
						}
					}
					else
					{
						echo "<script>alert('Ошибка счета не найдены.')</script>";
					}
				}
			}
		}
		$rollback_transaction = pg_query("ROLLBACK;");
	}
	if(isset($_POST['return-error']))
	{
		$clear_transaction = pg_query("ROLLBACK");
		$start_transaction = pg_query("BEGIN ISOLATION LEVEL SERIALIZABLE;");
		if($start_transaction)
		{
			$return_result = pg_query("SELECT * FROM \"OrmasSchema\".returns_view where return_id = ".$_POST['return-error']);
			$return_row = pg_fetch_all($return_result);
			if(!empty($return_row))
			{
				if($return_row[0]['status_id'] == $status_execute_id)
				{
					echo "<script>alert('Не возможно удалить этот документ!')</script>";
				}
				else
				{
					if(UpdateReturnToError($return_row[0]['return_id']))
					{
						$commit_transaction = pg_query("COMMIT;");
						if(!$commit_transaction)
						{
							$rollback_transaction = pg_query("ROLLBACK;");
							echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
						}
						echo ("<script>
						window.location = 'menu.php';
						</script>");
					}											
					else
					{
						echo "<script>alert('Не возможно изменить статус возврата.')</script>";
					}
				}
			}
		}
		$rollback_transaction = pg_query("ROLLBACK;");
	}
	if(isset($_POST['consume-error']))
	{
		$clear_transaction = pg_query("ROLLBACK");
		$start_transaction = pg_query("BEGIN ISOLATION LEVEL SERIALIZABLE;");
		if($start_transaction)
		{
			$consume_result = pg_query("SELECT * FROM \"OrmasSchema\".consume_products_view where consume_product_id = ".$_POST['consume-error']);
			$consume_row = pg_fetch_all($consume_result);
			if(!empty($consume_row))
			{
				if($consume_row[0]['status_id'] == $status_execute_id)
				{
					echo "<script>alert('Не возможно удалить этот документ!')</script>";
				}
				else
				{
					if(UpdateConsumeToError($consume_row[0]['consume_product_id']))
					{
						$commit_transaction = pg_query("COMMIT;");
						if(!$commit_transaction)
						{
							$rollback_transaction = pg_query("ROLLBACK;");
							echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
						}
						echo ("<script>
						window.location = 'menu.php';
						</script>");
					}											
					else
					{
						echo "<script>alert('Не возможно изменить статус заявки.')</script>";
					}
				}
			}
		}
		$rollback_transaction = pg_query("ROLLBACK;");
	}
	if($_SESSION['role_id_client'] == $_SESSION['role_id'])
	{
		if(isset($_POST['product']) && isset($_POST['count']) && isset($_POST['employee']) )
		{
			$id_result = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
			$id_row = pg_fetch_array($id_result, null, PGSQL_BOTH);
			if(!empty($id_row[0]))
			{
				$clear_transaction = pg_query("ROLLBACK");
				$start_transaction = pg_query("BEGIN ISOLATION LEVEL SERIALIZABLE;");
				if($start_transaction)
				{
					if($_POST['form_type'] == "order")
					{
						$order_id = $id_row[0];
						if(count($_POST['product']) == count($_POST['count']))
						{
							$error=false;
							for($i =0; $i<count($_POST['product']); $i++)
							{
								if($_POST['count'][$i]==0)
									continue;
								$id_result2 = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
								$id_row2 = pg_fetch_array($id_result2, null, PGSQL_BOTH);
								if(empty($id_row2[0]))
								{
									return false;
								}
								$order_list_id = $id_row2[0];
								$key = array_search($_POST['product'][$i], array_column($productPrice, 'id'));
								$needed_array = $productPrice[$key];
								$sum = $needed_array['price'] * $_POST['count'][$i];
								$product_current_id = $_POST['product'][$i];
								$count_current = $_POST['count'][$i];
								$insert_order_list_result = pg_query("INSERT INTO \"OrmasSchema\".order_list(order_list_id, order_id, product_id, count,
								sum, status_id, currency_id) VALUES($order_list_id, $order_id, 
								$product_current_id, $count_current , $sum, $_POST[status], $_POST[currency])
								");
								if(!$insert_order_list_result)
								{
									$error=true;
									$rollback_transaction = pg_query("ROLLBACK;");
									break;
								}
								if(!CreateOrderPriceCorrection($order_list_id, $order_id, $product_current_id, $count_current , $sum, $_POST[employee], $_POST[client]))
								{
									$error=true;
									$rollback_transaction = pg_query("ROLLBACK;");
									break;
								}
							}
							if($error!=true)
							{
								$current_date_result = pg_query("SELECT \"OrmasSchema\".getcurrentdate()");
								$current_date = pg_fetch_array($current_date_result, null, PGSQL_BOTH);
								$insert_order_result = pg_query("INSERT INTO \"OrmasSchema\".orders(order_id,user_id, order_date, execution_date, employee_id,
										 count, sum, status_id, currency_id) VALUES($order_id, $_POST[client],'$current_date[0]',
										 NULL, $_POST[employee], $_POST[ordercount], $_POST[sum] ,$_POST[status], $_POST[currency])");
								if(!$insert_order_result)
								{
									$rollback_transaction = pg_query("ROLLBACK;");
								}
								if(!CreateOrderUnited($order_id))
								{
									$rollback_transaction = pg_query("ROLLBACK;");
								}
								$commit_transaction = pg_query("COMMIT;");
												if(!$commit_transaction)
												{
													$rollback_transaction = pg_query("ROLLBACK;");
													echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
												}
							}
							else{
								echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
							}
							echo ("<script>
											window.location = 'menu.php';
											</script>");
						}
					}
					else if($_POST['form_type'] == "return")
					{
						$return_id = $id_row[0];
						if(count($_POST['product']) == count($_POST['count']))
						{
							$error=false;
							for($i =0; $i<count($_POST['product']); $i++)
							{
								if($_POST['count'][$i]==0)
									continue;
								$id_result2 = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
								$id_row2 = pg_fetch_array($id_result2, null, PGSQL_BOTH);
								if(empty($id_row2[0]))
								{
									return false;
								}
								$return_list_id = $id_row2[0];
								$key = array_search($_POST['product'][$i], array_column($productPrice, 'id'));
								$needed_array = $productPrice[$key];
								$sum = $needed_array['price'] * $_POST['count'][$i];
								$product_current_id = $_POST['product'][$i];
								$count_current = $_POST['count'][$i];
								$insert_return_list_result = pg_query("INSERT INTO \"OrmasSchema\".return_list(return_list_id, return_id, product_id, count,
								sum, status_id, currency_id) VALUES($return_list_id, $return_id, 
								$product_current_id, $count_current , $sum, $_POST[status], $_POST[currency])
								");
								if(!$insert_return_list_result)
								{
									$error=true;
									$rollback_transaction = pg_query("ROLLBACK;");
									break;
								}
								if(!CreateReturnPriceCorrection($return_list_id, $return_id, $product_current_id, $count_current , $sum, $_POST[employee], $_POST[client]))
								{
									$error=true;
									$rollback_transaction2 = pg_query("ROLLBACK;");
									break;
								}
							}
							if($error!=true)
							{
								$current_date_result = pg_query("SELECT \"OrmasSchema\".getcurrentdate()");
								$current_date = pg_fetch_array($current_date_result, null, PGSQL_BOTH);
								$insert_return_result = pg_query("INSERT INTO \"OrmasSchema\".returns(return_id,user_id, return_date, execution_date, employee_id,
										 count, sum, status_id, currency_id) VALUES($return_id, $_POST[client],'$current_date[0]',
										 NULL, $_POST[employee], $_POST[returncount], $_POST[sum] ,$_POST[status], $_POST[currency])");
								if(!$insert_return_result)
								{
									$rollback_transaction = pg_query("ROLLBACK;");
								}
								if(!CreateReturnUnited($return_id))
								{
									$rollback_transaction = pg_query("ROLLBACK;");
								}
								$commit_transaction = pg_query("COMMIT;");
												if(!$commit_transaction)
												{
													echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
													$rollback_transaction = pg_query("ROLLBACK;");
												}
							}
							else{
								echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
							}
							echo ("<script>
											window.location = 'menu.php';
											</script>");
						}
					}
				}
			}
		}
	}
	if($_SESSION['role_id_expeditor'] == $_SESSION['role_id'])
	{
		if(isset($_POST['value']) && $_POST['value'] > 0 && isset($_POST['status']) && isset($_POST['selected_clinet']) &&
		isset($_POST['currency']) && isset($_POST['cash_subaccount']) && isset($_POST['who']))
		{
			$id_result = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
			$id_row = pg_fetch_array($id_result, null, PGSQL_BOTH);
			if(!empty($id_row[0]))
			{
				$payment_id = $id_row[0];
				$current_date_result = pg_query("SELECT \"OrmasSchema\".getcurrentdate()");
				$current_date = pg_fetch_array($current_date_result, null, PGSQL_BOTH);
				$clear_transaction = pg_query("ROLLBACK");
				$start_transaction = pg_query("BEGIN ISOLATION LEVEL SERIALIZABLE;");
				if($start_transaction)
				{
					$client_subacc_id=0;
					$parent_acc_id=0;
					$query_acc_id = "SELECT * FROM \"OrmasSchema\".balances WHERE user_id=".$_POST['selected_clinet'].";";			
					$result_acc_id = pg_query($query_acc_id);
					$result_account_id  = pg_fetch_row($result_acc_id);
					$client_subacc_id = $result_account_id[2];
					$parent_acc_id = GetParentAccID($client_subacc_id);
					$payment_query = "INSERT INTO \"OrmasSchema\".payments(payment_id, payment_date, payment_value,
								payment_target, user_id, currency_id, status_id, account_id, subaccount_id, who, cashbox_account_id) 
								VALUES($payment_id, '$current_date[0]', $_POST[value] ,'$_POST[target]',
								$_POST[selected_clinet], $_POST[currency], $_POST[status], $parent_acc_id, $client_subacc_id, 
								'$_POST[who]', $_POST[cash_subaccount])";
					$insert_payment_result =  pg_query($payment_query);
					if($insert_payment_result)
					{
						
						$insert_payment_employee_result = pg_query("INSERT INTO \"OrmasSchema\".payment_employee(payment_employee_id,
								payment_id, employee_id) VALUES((SELECT nextval('\"OrmasSchema\".id_seq')), $payment_id,
								$_SESSION[id])");
						if($insert_payment_employee_result)
						{
							if(!CreatePaymentUnited($payment_id))
							{
								$rollback_transaction = pg_query("ROLLBACK;");
							}
							echo ("<script>alert(\"Оплата прошла успешно!\")</script>");
							$commit_transaction = pg_query("COMMIT;");
											if(!$commit_transaction)
											{
												$rollback_transaction = pg_query("ROLLBACK;");
												echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
											}
							echo ("<script>
								window.location = 'menu.php';
							</script>");
						}
						else
						{
							echo ("<script>alert(\"Ошибка оплаты!\")</script>");
							$rollback_transaction = pg_query("ROLLBACK;");
						}
					}
					else
					{
						echo ("<script>alert(\"Оплата прошла успешно!\")</script>");
						$rollback_transaction = pg_query("ROLLBACK;");
					}						
				}
			}
		}
		
				
		if(isset($_POST['product']) && isset($_POST['count']) && isset($_POST['selected_clinet']))
		{
			$id_result = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
			$id_row = pg_fetch_array($id_result, null, PGSQL_BOTH);
			if(!empty($id_row[0]))
			{
				$clear_transaction = pg_query("ROLLBACK");
				$start_transaction = pg_query("BEGIN ISOLATION LEVEL SERIALIZABLE;");
				if($start_transaction)
				{
					if($_POST['form_type'] == "order")
					{
						$order_id = $id_row[0];
						if(count($_POST['product']) == count($_POST['count']))
						{
							$error=false;
							for($i =0; $i<count($_POST['product']); $i++)
							{
								if($_POST['count'][$i]==0)
									continue;
								$id_result2 = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
								$id_row2 = pg_fetch_array($id_result2, null, PGSQL_BOTH);
								if(empty($id_row2[0]))
								{
									return false;
								}
								$order_list_id = $id_row2[0];
								$key = array_search($_POST['product'][$i], array_column($productPrice, 'id'));
								$needed_array = $productPrice[$key];
								$sum = $needed_array['price'] * $_POST['count'][$i];
								$product_current_id = $_POST['product'][$i];
								$count_current = $_POST['count'][$i];
								$insert_order_list_result = pg_query("INSERT INTO \"OrmasSchema\".order_list(order_list_id, order_id, product_id, count,
								sum, status_id, currency_id) VALUES($order_list_id, $order_id, 
								$product_current_id, $count_current , $sum, $_POST[status], $_POST[currency])
								");
								if(!$insert_order_list_result)
								{
									$rollback_transaction = pg_query("ROLLBACK;");
									$error=true;
									break;
								}

								
								if(!CreateOrderPriceCorrection($order_list_id, $order_id, $product_current_id, $count_current , $sum, $_POST[employee], $_POST[client]))
								{
									$error=true;
									$rollback_transaction2 = pg_query("ROLLBACK;");
									break;
								}
							}
							if($error!=true)
							{
								$current_date_result = pg_query("SELECT \"OrmasSchema\".getcurrentdate()");
								$current_date = pg_fetch_array($current_date_result, null, PGSQL_BOTH);
								$insert_order_result = pg_query("INSERT INTO \"OrmasSchema\".orders(order_id,user_id, order_date, execution_date, employee_id,
										 count, sum, status_id, currency_id) VALUES($order_id, $_POST[selected_clinet],'$current_date[0]',
										 NULL, $_POST[employee], $_POST[ordercount], $_POST[sum] ,$_POST[status], $_POST[currency])");
								if(!$insert_order_result)
								{
									$rollback_transaction = pg_query("ROLLBACK;");
								}
								if(!CreateOrderUnited($order_id))
								{
									$rollback_transaction = pg_query("ROLLBACK;");
								}
								$commit_transaction = pg_query("COMMIT;");
												if(!$commit_transaction)
												{
													$rollback_transaction = pg_query("ROLLBACK;");
													echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
												}
							}
							else{
								echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
							}
							echo ("<script>
											window.location = 'menu.php';
											</script>");
						}
					}
					else if($_POST['form_type'] == "return")
					{
						$return_id = $id_row[0];
						if(count($_POST['product']) == count($_POST['count']))
						{
							$error=false;
							for($i =0; $i<count($_POST['product']); $i++)
							{
								if($_POST['count'][$i]==0)
									continue;
								$id_result2 = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
								$id_row2 = pg_fetch_array($id_result2, null, PGSQL_BOTH);
								if(empty($id_row2[0]))
								{
									return false;
								}
								$return_list_id = $id_row2[0];
								$key = array_search($_POST['product'][$i], array_column($productPrice, 'id'));
								$needed_array = $productPrice[$key];
								$sum = $needed_array['price'] * $_POST['count'][$i];
								$product_current_id = $_POST['product'][$i];
								$count_current = $_POST['count'][$i];
								$insert_return_list_result = pg_query("INSERT INTO \"OrmasSchema\".return_list(return_list_id, return_id, product_id, count,
								sum, status_id, currency_id) VALUES($return_list_id, $return_id, 
								$product_current_id, $count_current , $sum, $_POST[status], $_POST[currency])
								");
								if(!$insert_return_list_result)
								{
									$error=true;
									$rollback_transaction = pg_query("ROLLBACK;");
									break;
								}
								if(!CreateReturnPriceCorrection($return_list_id, $return_id, $product_current_id, $count_current , $sum, $_POST[employee], $_POST[client]))
								{
									$error=true;
									$rollback_transaction2 = pg_query("ROLLBACK;");
									break;
								}
							}
							if($error!=true)
							{
								$current_date_result = pg_query("SELECT \"OrmasSchema\".getcurrentdate()");
								$current_date = pg_fetch_array($current_date_result, null, PGSQL_BOTH);
								$insert_return_result = pg_query("INSERT INTO \"OrmasSchema\".returns(return_id,user_id, return_date, execution_date, employee_id,
										 count, sum, status_id, currency_id) VALUES($return_id, $_POST[selected_clinet],'$current_date[0]',
										 NULL, $_POST[employee], $_POST[returncount], $_POST[sum] ,$_POST[status], $_POST[currency])");
								if(!$insert_return_result)
								{
									$rollback_transaction = pg_query("ROLLBACK;");
								}
								if(!CreateReturnUnited($return_id))
								{
									$rollback_transaction = pg_query("ROLLBACK;");
								}
								$commit_transaction = pg_query("COMMIT;");
												if(!$commit_transaction)
												{
													echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
													$rollback_transaction = pg_query("ROLLBACK;");
												}
							}
							else{
								echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
							}
							echo ("<script>
											window.location = 'menu.php';
											</script>");
						}
					}
				}
			}
		}
		else if(isset($_POST['product']) && isset($_POST['count']))
		{
			$id_result = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
			$id_row = pg_fetch_array($id_result, null, PGSQL_BOTH);
			if(!empty($id_row[0]))
			{
				$clear_transaction = pg_query("ROLLBACK");
				$start_transaction = pg_query("BEGIN ISOLATION LEVEL SERIALIZABLE;");
				if($start_transaction)
				{
					if($_POST['form_type'] == "consume")
					{
						
						$consume_id = $id_row[0];
						if(count($_POST['product']) == count($_POST['count']))
						{
							
							$error=false;
							for($i =0; $i<count($_POST['product']); $i++)
							{
								if($_POST['count'][$i]==0)
									continue;
								$id_result2 = pg_query("SELECT nextval('\"OrmasSchema\".id_seq')");
								$id_row2 = pg_fetch_array($id_result2, null, PGSQL_BOTH);
								if(empty($id_row2[0]))
								{
									return false;
								}
								$consume_list_id = $id_row2[0];
								$key = array_search($_POST['product'][$i], array_column($productNetCost, 'id'));
								$needed_array = $productNetCost[$key];
								$sum = $needed_array['price'] * $_POST['count'][$i];
								$product_current_id = $_POST['product'][$i];
								$count_current = $_POST['count'][$i];
								$insert_consume_product_list_result = pg_query("INSERT INTO \"OrmasSchema\".consume_product_list(consume_product_list_id, consume_product_id, product_id, count,
								sum, status_id, currency_id) VALUES($consume_list_id, $consume_id, 
								$product_current_id, $count_current , $sum, $_POST[status], $_POST[currency])
								");
								if(!$insert_consume_product_list_result)
								{
									$error=true;
									$rollback_transaction = pg_query("ROLLBACK;");
									break;
								}
							}
							if($error!=true)
							{
								$current_date_result = pg_query("SELECT \"OrmasSchema\".getcurrentdate()");
								$current_date = pg_fetch_array($current_date_result, null, PGSQL_BOTH);
								$insert_consume_product_result = pg_query("INSERT INTO \"OrmasSchema\".consume_products(consume_product_id,user_id, consume_product_date, execution_date, employee_id,
										 count, sum, status_id, currency_id) VALUES($consume_id, $_POST[employee],'$current_date[0]',
										 NULL, $_POST[stock_employee], $_POST[consumecount], $_POST[sum] ,$_POST[status], $_POST[currency])");
								if(!$insert_consume_product_result)
								{
									$rollback_transaction = pg_query("ROLLBACK;");
								}
								$commit_transaction = pg_query("COMMIT;");
												if(!$commit_transaction)
												{
													echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
													$rollback_transaction = pg_query("ROLLBACK;");
												}
							}
							else{
								echo "<script>alert('Ошибка, повторите попытку поже.')</script>";
							}
							echo ("<script>
											window.location = 'menu.php';
											</script>");
						}
					}
				}
			}
		}
	}
	// role seperated section
	if($_SESSION['role_id_stock_inspector'] == $_SESSION['role_id'])
	{
		
	}
?>
<div class="main-content">
		<div class = "menu">
		<?php
			$product_list= Array();
			$productPrice= Array();
			$client_options = '';
			$product_list_all ='';
			if($_SESSION['role_id'] == $_SESSION['role_id_client'])
			{
				require_once ('client.php');
			}
			if($_SESSION['role_id'] == $_SESSION['role_id_expeditor'])
			{
				require_once ('expeditor.php');
			}
			if($_SESSION['role_id'] == $_SESSION['role_id_stock_inspector'])
			{
				require_once ('stock.php');
			}
			if($_SESSION['role_id'] == $_SESSION['role_id_purveyor'])
			{
				require_once ('purveyor.php');
			}
			if($_SESSION['role_id'] == $_SESSION['role_id_purveyor_manager'])
			{
				require_once ('manager.php');
			}
		?>
		</div>
		<div class = "content-body">
			<div class = "ajax-content">
			</div>
		</div>
	</div>

<?php
	require_once('footter.php')
?>