
<?php
require 'config.php';
$sql = "SELECT * FROM sensor WHERE 1 ORDER BY id DESC";
$result = $db->query($sql);
if (!$result) {
  { echo "Error: " . $sql . "<br>" . $db->error; }}
$row = $result->fetch_assoc();
header('Content-Type: application/json');
echo json_encode($row);
?>
