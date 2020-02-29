<?php

$sql = 'SELECT * FROM `' . ARP_CHECK_TABLE . '` WHERE `' . ARP_CHECK_IP_ADDR_ID . '`=' . $ip_history . ' ORDER BY `' . ARP_CHECK_TIMESTAMP . '`;';
$res = $mysqliLink->query($sql);
$status = false;
$mac_addr = '';
$ever = false;
$ip_addr = getIpAddrById($ip_history);
$ip = IP_ADDR_IP_A . '.' . IP_ADDR_IP_B . '.' . $ip_addr[IP_ADDR_IP_C] . '.' . $ip_addr[IP_ADDR_IP_D];
$output .= '<h2>' . $ip . '</h2><div class="lists keret">';
while ($res AND ( $row = $res->fetch_assoc())) {
    $last_check = $row[ARP_CHECK_TIMESTAMP];
    if ($mac_addr != $row[ARP_CHECK_MAC_ADDR]) {
        $mac_addr = $row[ARP_CHECK_MAC_ADDR];
        $output .= '<label>' . $row[ARP_CHECK_TIMESTAMP] . '</label>';
        $output .= '<label>' . $mac_addr . '</label>';
        if ($status) {
            if ($row[ARP_CHECK_VISIBLE] == 0) {
                $status = false;
                $output .= 'Megszünt<br>';
            } else {
                $output .= 'Más használja<br>';
            }
        } else {
            if ($row[ARP_CHECK_VISIBLE] == 1) {
                $status = true;
                $ever = true;
                $output .= 'Használatba került<br>';
            } else {
                $output .= '<br>';
            }
        }
    }
}
if ($status) {
    $output .= '<br>És még most is használatban van.<br>';
}
if (!$ever) {
    $output .= '<b>Az IP még sosem volt használatban !</b>';
}
$output .= '<br>Utolsó ellenőrzés: ' . $last_check;
$output .= '<br><br><button type="submit" >Vissza</button>';
$output .= '</div>';
