<?php
	$db_hostname= '-';
	$db_database = '-';
	$db_username = '-';
	$db_password = '-';
	$db_port = '-';
	
	$connStr = "host=".$db_hostname." port=".$db_port." dbname=".$db_database." user=".$db_username." password=".$db_password." options='--client_encoding=UTF8'";
	$dbconn = pg_connect($connStr);
	if (!$dbconn) die ("Database error :".pg_last_error());
?>