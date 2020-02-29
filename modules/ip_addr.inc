<?php

if (isset($ip_history)) {
    include_once INCLUDES . 'list_ip_history.inc';
    return;
}
require_once CLASSES . 'ArpStatus/ArpStatus.php';
if (isset($arp_check)) {
    include_once INCLUDES . 'arp_check.inc';
}

$arpStatus = new ArpStatus();

$output .= '<button type="submit" name="arp_check" title="Azonnal indított ellenőrzés">Ellenőrzés</button><br>';
$sql = 'SELECT * FROM `' . IP_ADDR_TABLE . '` ORDER BY `' . IP_ADDR_IP_C . '`, `' . IP_ADDR_IP_D . '`;';
$res = $mysqliLink->query($sql);
$ip_addresses = array();
while ($res AND $row = $res->fetch_assoc()) {
    $ip_addresses[] = $row;
}
$output .= '<div class="lists">';
$output .= '<div class="ip_list_row">';
$ip_c = 0;

foreach ($ip_addresses as $ip_addr) {
    $ip_id = $ip_addr[IP_ADDR_ID];
    if ($ip_c != $ip_addr[IP_ADDR_IP_C]) {
        if ($ip_c != 0) {
            $output .= '</tbody></table>';
            $output .= '</div>';
        }
        $output .= '<div class="ip_list_column">';
        $output .= '<table><thead>';
        $output .= '<tr><th>IP cím</th><th>Cég</th><th>Áll.</th></tr></thead><tbody>';
        $ip_c = $ip_addr[IP_ADDR_IP_C];
    }
    $output .= '<tr><td>';
    $output .= IP_ADDR_IP_A . '.' . IP_ADDR_IP_B . '.' . $ip_addr[IP_ADDR_IP_C] . '.' . $ip_addr[IP_ADDR_IP_D] . '</td>';
    $output .= '<td>';
    $ip_status = unserialize($arpStatus->getStatus($ip_id));
    $output .= $arpStatus->getUser($ip_id);
    $output .= '</td><td>';
    if ($arpStatus->isVisible($ip_id)) {
        if ($ip_addr[IP_ADDR_INTERNET_ID] > 0) {
            $output .= '<button name="ip_history" value="' . $ip_id . '"><img src="' . IMAGES . 'visible.png"></button>';
        } else {
            $output .= '<button name="ip_history" value="' . $ip_id . '"><img src="' . IMAGES . 'exclamation.jpg"></button>';
        }
    } else {
        $output .= '<button name="ip_history" value="' . $ip_id . '"><img src="' . IMAGES . 'invisible.png"></button>';
    }
    $output .= '</td>';
    $output .= '</tr>';
}

$output .= '</tbody></table>';
$output .= '</div>';
$output .= '</div>';


