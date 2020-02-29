<?php

require_once CLASSES . 'ArpStatus/ArpStatus.php';



$arpTable = getArpTable();
$arpStatus = new ArpStatus();
$sql = 'SELECT * FROM `' . IP_ADDR_TABLE . '`;';
$res = $mysqliLink->query($sql);
while ($res AND $ip_addr = $res->fetch_assoc()) {
    $ip_id = $ip_addr[IP_ADDR_ID];
    $ip = IP_ADDR_IP_A . '.' . IP_ADDR_IP_B . '.' . $ip_addr[IP_ADDR_IP_C] . '.' . $ip_addr[IP_ADDR_IP_D];
    $internet = getInternetById($ip_addr[IP_ADDR_INTERNET_ID]);
    $cegnev = $comment = '';
    if (!empty($internet)) {
        $ceg = getCegById($internet[INTERNET_CEG_ID]);
        $comment = $internet[INTERNET_COMMENT];
        if (!empty($ceg)) {
            $cegnev = $ceg[RECORD_CEGNEV];
        }
    }
    if (isset($arpTable[$ip]) AND ( 14 < strlen($arpTable[$ip]))) {
        $status = 1;
        $sql = 'INSERT INTO `' . ARP_CHECK_TABLE . '` '
                . '(`' . ARP_CHECK_IP_ADDR_ID . '`, `' . ARP_CHECK_MAC_ADDR . '`, `' . ARP_CHECK_VISIBLE . '`)'
                . ' VALUES '
                . '(' . $ip_id . ', "' . $arpTable[$ip] . '", 1);';
        if (!empty(getOptionValue(OPTIONS_NAME_EMAIL_WARNING)) AND !$arpStatus->isVisible($ip_id)) {
            $body = 'Megjelent egy hálózati elem ezekkel az adatokal: <br>';
            $body .= '<b>IP: </b>' . $ip . '<br>';
            $body .= '<b>Mac Addr: </b>' . $arpTable[$ip] . '<br>';
            $body .= '<b>Cégnév: </b>' . $cegnev . '<br>';
            $body .= '<b>Comment: </b>' . $comment . '<br>';
            $body .= '<br><hr>';
            send_mail('Felbukkanó IP cím', $body);
        }
    } else {
        $status = 0;
        $sql = 'INSERT INTO `' . ARP_CHECK_TABLE . '` '
                . '(`' . ARP_CHECK_IP_ADDR_ID . '`, `' . ARP_CHECK_MAC_ADDR . '`, `' . ARP_CHECK_VISIBLE . '`)'
                . ' VALUES '
                . '(' . $ip_id . ', "----", 0);';
        if (!empty(getOptionValue(OPTIONS_NAME_EMAIL_WARNING)) AND $arpStatus->isVisible($ip_id)) {
            $body = 'Eltűnt egy hálózati elem ezekkel az adatokal: <br>';
            $body .= '<b>IP: </b>' . $ip . '<br>';
            $body .= '<b>Mac Addr: </b>' . $arpTable[$ip] . '<br>';
            $body .= '<b>Cégnév: </b>' . $cegnev . '<br>';
            $body .= '<b>Comment: </b>' . $comment . '<br>';
            $body .= '<br><hr>';
            send_mail('Eltűnt IP cím', $body);
        }
    }
    $mysqliLink->query($sql);
    $ip_status = array(
        OPTIONS_ARP_STATUS => $status,
        OPTIONS_ARP_CEGNEV => $cegnev,
        OPTIONS_ARP_COMMENT => $comment,
    );
    $arpStatus->setStatus($ip_addr[IP_ADDR_ID], serialize($ip_status));
}
$sql = 'DELETE FROM `' . ARP_CHECK_TABLE . '` WHERE `' . ARP_CHECK_TIMESTAMP . '` < DATE_SUB(NOW(), INTERVAL 1 YEAR);';
$mysqliLink->query($sql);

checkHost(getOptionValue(OPTIONS_NAME_HOST_CHECK));
checkHost('195.70.32.131');

function getArpTable() {
//    exec('/sbin/ip -s -s neigh flush all', $devnull);
    exec('/usr/bin/nmap -n -sn -iL /web/www/cegek/arp-check.txt', $devnull);
    $ret = array();
    exec('/usr/bin/arp -n', $arpTable);
    foreach ($arpTable as $arpItem) {
        $valueSplitted = preg_split("/[\s ]+/", $arpItem);
        $ret[$valueSplitted[0]] = $valueSplitted[2];
    }
    return $ret;
}

function checkHost($host) {
    global $mysqliLink;
    $result = -1;
    $op = array();
    exec("ping -c 2 " . $host, $op[], $result);
    $sql = 'INSERT INTO `' . ARP_CHECK_TABLE . '` '
            . '(`' . ARP_CHECK_IP_ADDR_ID . '`, `' . ARP_CHECK_MAC_ADDR . '`, `' . ARP_CHECK_VISIBLE . '`)'
            . ' VALUES '
            . '(-1, "' . $host . '", ' . (($result == 0) ? '1' : '0') . ');';
    $mysqliLink->query($sql);
}
