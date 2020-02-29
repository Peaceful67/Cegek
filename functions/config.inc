<?php

session_start();

foreach ($_POST as $key => $value) {
    if (is_array($value)) {
        error_log($key . '->' . print_r($value, true));
    } else {
        error_log($key . '->' . $value);
    }
    $$key = $value;
}

$host_url = 'http://'.$_SERVER['HTTP_HOST'].'/';

date_default_timezone_set('Europe/Budapest');

if (isset($logout)) {
    unset($_SESSION);
}
$now = time();
$today = date('Y-m-d');
define("FOREVER", '2099-12-31');

define("MENU_ID", 'menu_id');
define("MENU_NAME", "menu_name");
define("MENU_TITLE", "title");
define("MENU_MODULE", "module");

define("COMMAND_STRING", 'c');
DEFINE("COMMAND_PASSWORD", 'password');

define("SMTP_USER", '');
define("SMTP_PASSWD", '');





define("CEGEK_TABLE", 'cegek');
define("RECORD_ID", "id");
define("RECORD_CEGNEV", "cegnev");
define("RECORD_OWNER", "owner");
define("RECORD_OWNERID", "ownerId");
define("RECORD_BUILDING", "building");
define("RECORD_BUILDINGID", "buildingId");
define("RECORD_SZOBA", "szoba");
define("RECORD_TEVEKENYSEG", "tevekenyseg");
define("RECORD_VEZETO", "vezeto");
define("RECORD_TELEFON", "telefon");
define("RECORD_EMAIL", "email");
define("RECORD_HONLAP", "honlap");
define("RECORD_COMMENT", "comment");
define("RECORD_PARKOLO", "parkolo");
define("RECORD_POSTA", "posta");
define("RECORD_AKTIV", "act");
define("RECORD_START", "start");
define("RECORD_STOP", "stop");

define("BUILDING_ID", "id");
define("BUILDING_NAME", "name");
define("BUILDING_OWNERID", "ownerId");

define("OWNER_ID", "id");
define("OWNER_NAME", "name");

define("IP_ADDR_IP_A", 195);
define("IP_ADDR_IP_B", 70);

define("IP_ADDR_TABLE", 'ip_addr');
define("IP_ADDR_ID", 'id');
define("IP_ADDR_INTERNET_ID", 'internet_id');
define("IP_ADDR_IP_C", 'ip_c');
define("IP_ADDR_IP_D", 'ip_d');
define("IP_ADDR_NETMASK", 'netmask');
define("IP_ADDR_GW", 'gateway');
define("IP_ADDR_ACTIVE", 'active');

define("INTERNET_TABLE", 'internet');
define("INTERNET_ID", 'id');
define("INTERNET_CEG_ID", 'ceg_id');
define("INTERNET_DATE_FROM", 'date_from');
define("INTERNET_DATE_TO", 'date_to');
define("INTERNET_DISCOUNT", 'discount');
define("INTERNET_ESZAMLA", 'eszamla');
define("INTERNET_COMMENT", 'comment');

define("OPTIONS_TABLE", 'options');
define("OPTIONS_ID", 'id');
define("OPTIONS_NAME", 'name');
define("OPTIONS_VALUE", 'value');
define("OPTIONS_ARP_CEGNEV", 'cegnev');
define("OPTIONS_ARP_COMMENT", 'comment');
define("OPTIONS_ARP_STATUS", 'status');


define("ARP_CHECK_TABLE", 'arp_check');
define("ARP_CHECK_ID", 'id');
define("ARP_CHECK_TIMESTAMP", 'time_stamp');
define("ARP_CHECK_MAC_ADDR", 'mac_addr');
define("ARP_CHECK_IP_ADDR_ID", 'ip_addr_id');
define("ARP_CHECK_VISIBLE", 'visible');

define("LOGGER_TABLE", 'logger');
define("LOGGER_ID", 'id');
define("LOGGER_TIMESTAMP", 'time');
define("LOGGER_OPERATOR", 'operator');
define("LOGGER_CATEGORY", 'category');
define("LOGGER_FIELD", 'field');
define("LOGGER_COMMENT", 'comment');


define("LOGGER_CAT_LOGIN", 1);
define("LOGGER_CAT_MODIFY_CEG", 2);
define("LOGGER_CAT_ACTIV_CEG", 3);
define("LOGGER_CAT_INACTIV_CEG", 4);
define("LOGGER_CAT_INSERT_CEG", 5);
define("LOGGER_CAT_MODIFY_INTERNET", 6);
define("LOGGER_CAT_DELETE_INTERNET", 7);
define("LOGGER_CAT_INSERT_INTERNET", 8);
define("LOGGER_CAT_PRINT_CEGEK", 9);
define("LOGGER_CAT_PRINT_IP", 10);
define("LOGGER_CAT_PRINT_INVOICE", 11);
define("LOGGER_CAT_OPTIONS_CHANGED", 12);
define("LOGGER_CAT_EMAIL_SENT", 13);





define("SQL_QUERY", "SELECT * FROM `cegek` WHERE id=");
define("SQL_QUERY_BY_ID", "SELECT * FROM `cegek` WHERE act=1 ORDER BY `id`");
define("SQL_QUERY_BY_CEGNEV", "SELECT * FROM `cegek` ORDER BY `cegnev`");
define("SQL_QUERY_ACT_BY_CEGNEV", "SELECT * FROM `cegek` WHERE act=1 ORDER BY `cegnev`");
define("SQL_QUERY_BY_TULAJDONOS", "SELECT * FROM `cegek` ORDER BY `ownerId`");
define("SQL_QUERY_BY_EPULET", "SELECT * FROM `cegek` ORDER BY `buildingId`");

$secret = '%/{)9A!#@';
$passwd = 'Marika';
$current_code = "5094";




$owners = array();
$owner_counter = 0;
$res = $mysqliLink->query("SELECT * FROM `owners` WHERE 1");
while ($row = $res->fetch_assoc()) {
    $id = $row["id"];
    $owner_counter++;
    $name = $row["name"];
    $owners[$id] = $name;
}
asort($owners);
$buildings = array();
$buildingOwner = array();
$building_counter = 0;
$res = $mysqliLink->query("SELECT * FROM `buildings` WHERE 1");
while ($row = $res->fetch_assoc()) {
    $id = $row["id"];
    $building_counter++;
    $name = $row["name"];
    $buildings[$id] = $name;
    $buildingOwner[$id] = $row["ownerId"];
}
asort($buildings);
?>
