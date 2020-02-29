<?php

define("OPTIONS_NAME_PRICE_FIRST", 'price_first');
define("OPTIONS_NAME_PRICE_MORE", 'price_more');
define("OPTIONS_NAME_EMAIL_WARNING", 'email_warning');
define("OPTIONS_NAME_HOST_CHECK", 'host_check');
define("OPTIONS_NAME_ARP_STATUS_", 'arp_status_');

define("OPTIONS_NAME_ARP_CHECK_", 'arp_check_');
define("OPTIONS_NAME_LAST_CRON_DAILY", 'cron_daily');




$options = array (
    OPTIONS_NAME_PRICE_FIRST=> 7500,
    OPTIONS_NAME_PRICE_MORE=>1000,
    OPTIONS_NAME_EMAIL_WARNING=>'',
    OPTIONS_NAME_HOST_CHECK=>'index.hu',
);


$db_options = array();
$sql = 'SELECT * FROM `' . OPTIONS_TABLE . '` ';
$res = $mysqliLink->query($sql);
while ($res AND $row = $res->fetch_assoc()) {
    $db_options[$row[OPTIONS_NAME]] = $row[OPTIONS_VALUE];
}
foreach ($options as $name => $value) {
    if (isset($db_options[$name])) {
        $options[$name] = $db_options[$name];
    } else {
        updateOption($name, $value);
    }
}

function updateOption($name, $value) {
    global $mysqliLink, $options, $db_options, $mem_id;
    if (isset($db_options[$name])) {
        $sql = 'UPDATE `' . OPTIONS_TABLE . '` SET `' . OPTIONS_VALUE . '`="' . $value . '" '
                . 'WHERE `' . OPTIONS_NAME . '`="' . $name . '" ;';
    } else {
        $sql = 'INSERT INTO `' . OPTIONS_TABLE . '` '
                . '(`' . OPTIONS_NAME . '`, `' . OPTIONS_VALUE . '`)'
                . 'VALUES ("' . $name . '", "' . $value . '");';
    }
    $mysqliLink->query($sql);
    $options[$name] = $value;
    logger($mem_id, 0, LOGGER_CAT_OPTIONS_CHANGED, $name.' új értéke: '.$value);
    return $value;
}

function getOptionValue($key) {
    global $options;
    return isset($options[$key]) ? $options[$key] : '';
}

function retrieveOptionValue($key) {
    global $mysqliLink;
    $sql = 'SELECT * FROM `' . OPTIONS_TABLE . '` WHERE `' . OPTIONS_NAME . '`="' . $key . '" LIMIT 1; ';
    $res = $mysqliLink->query($sql);
    if ($res AND $res->num_rows > 0) {
        $row = $res->fetch_assoc();
        return $row[OPTIONS_NAME];
    } else {
        return '';
    }
}


