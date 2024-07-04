<?php 
require 'config.php';
if ($_SERVER["REQUEST_METHOD"] == "POST") {
		$temprature = $_POST["temprature"];
		$humidity = $_POST["humidity"];
		$rain = $_POST["rain"];
		$soil = $_POST["soil"];
		$light = $_POST["light"];
		$sql = "INSERT INTO sensor(temprature,humidity,rain,soil,light) 
			VALUES('".$temprature."','".$humidity."','".$rain."','".$soil."','".$light."')";
		if($db->query($sql) === FALSE)
			{ echo "Error: " . $sql . "<br>" . $db->error; }
		echo "OK. INSERT ID: ";
		echo $db->insert_id;	}?>
