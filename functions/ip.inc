<?php

$dns1 = array(195, 70, 40, 114);
$dns2 = array(195, 56, 77, 76);

$ip_pools = array();

$ip_pools[] = getIpRange(array(195, 70, 40), 96, 224, 97);
$ip_pools[] = getIpRange(array(195, 70, 59), 0, 192, 62);
$ip_pools[] = getIpRange(array(195, 70, 59), 96, 224, 126);
$ip_pools[] = getIpRange(array(195, 70, 43), 224, 224, 254);
$ip_pools[] = getIpRange(array(195, 70, 60), 0, 0, 254);

$ipaddresses = array();
foreach ($ip_pools as $range) {
    foreach ($range as $value) {
        $ipaddresses[] = $value;
    }
}

function getIpRange($fixIp, $net, $mask, $gw) {
    $ret = array();
    $num = 255 - $mask;
    for ($ip = $net + 1; $ip < $net + $num; $ip++) {
        $ret[] = array($fixIp[0], $fixIp[1], $fixIp[2], $ip, $mask, $gw);
    }
    return $ret;
}


function getFreeIpAddr() {
    global $mysqliLink;
    $sql = 'SELECT * FROM `' . IP_ADDR_TABLE . '` WHERE `' . IP_ADDR_INTERNET_ID . '`=0;';
    $res = $mysqliLink->query($sql);
    $ret = array();
    while ($res AND $row = $res->fetch_assoc()) {
        $ret[] = $row;
    }
    return $ret;
}

function getIpAddresses() {
    global $mysqliLink;
    $sql = 'SELECT * FROM `' . IP_ADDR_TABLE . '` ;';
    $res = $mysqliLink->query($sql);
    $ret = array();
    while ($res AND $row = $res->fetch_assoc()) {
        $ret[] = $row;
    }
    return $ret;
}

function getIpAddrById($ip_addr_id) {
    global $mysqliLink;
    $sql = 'SELECT * FROM `' . IP_ADDR_TABLE . '` WHERE `' . IP_ADDR_ID . '`=' . $ip_addr_id . ' LIMIT 1;';
    $res = $mysqliLink->query($sql);    
    if ($res AND $row = $res->fetch_assoc()) {
        return $row;
    } else {
        return array();
    }
}


function isIpAddrFree($ip_addr_id) {
    global $mysqliLink;
    $sql = 'SELECT * FROM `' . IP_ADDR_TABLE . '` WHERE `' . IP_ADDR_ID . '`=' . $ip_addr_id . ' LIMIT 1;';
    $res = $mysqliLink->query($sql);
    $ret = array();
    if ($res AND $row = $res->fetch_assoc() AND 0 == $row[IP_ADDR_INTERNET_ID]) {
        return true;
    } else {
        return false;
    }
}

function getCegByInternetId($netId) {
    $internet = getInternetById($netId);
    if(empty($internet)) {
        return array();
    } else {
        return getCegById($internet[INTERNET_CEG_ID]);
    }
}

function getCegNameByInternetId($netId) {
    $ceg = getCegByInternetId($netId);
    if (empty($ceg)) {
        return '---';
    } else {
        return $ceg[RECORD_CEGNEV];
    }
}
function getInternetById($netId) {
    global $mysqliLink;
    $sql = 'SELECT * FROM `' . INTERNET_TABLE . '` WHERE `' . INTERNET_ID . '`=' . $netId . ' LIMIT 1;';
    $res = $mysqliLink->query($sql);
    if ($res AND $row = $res->fetch_assoc()) {
        return $row;
    } else {
        return array();
    }
}

function getIpAddrByInternetId($netId) {
    global $mysqliLink;
    $sql = 'SELECT * FROM `' . IP_ADDR_TABLE . '` WHERE `' . IP_ADDR_INTERNET_ID . '`=' . $netId . ' LIMIT 1;';
    $res = $mysqliLink->query($sql);
    if ($res AND $row = $res->fetch_assoc()) {
        return $row;
    } else {
        return array();
    }
}
