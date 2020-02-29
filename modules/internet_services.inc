<?php

if (!isset($sort)) {
    $sort = 'ip';
}
if (!isset($search_internet)) {
    $search_internet = '';
}
if (isset($internet_print)) {
    include_once INCLUDES . 'print_ip.inc';
    exit(0);
}
if (isset($internet_save)) {
    $internet_id = $internet_save;
    include_once INCLUDES . 'edit_internet.inc';
}
if (isset($internet_add)) {
    $internet_id = -1;
    include_once INCLUDES . 'edit_internet.inc';
    return;
}
if (isset($internet_lock)) {
    $sql = 'UPDATE `' . INTERNET_TABLE . '` SET '
            . '`' . INTERNET_DATE_TO . '`=DATE(DATE_ADD(CURRENT_DATE, INTERVAL -1 DAY)) '
            . ' WHERE `' . INTERNET_ID . '`=' . $internet_lock . ';';

    $mysqliLink->query($sql);
    $sql = 'UPDATE `' . IP_ADDR_TABLE . '` SET '
            . '`' . IP_ADDR_INTERNET_ID . '`=0 '
            . ' WHERE `' . IP_ADDR_INTERNET_ID . '`=' . $internet_lock . ';';
    $mysqliLink->query($sql);
}
if (isset($print_invoice)) {
    include_once INCLUDES . 'print_invoices.inc';
    exit(0);
}
if (isset($internet_edit) AND $internet_edit > 0
        AND ! isset($internet_edit_cancel) AND ! isset($internet_save)) {
    $internet_id = $internet_edit;
    include_once INCLUDES . 'edit_internet.inc';
    return;
}
$sql = 'SELECT `' . INTERNET_TABLE . '`.* FROM `' . INTERNET_TABLE . '`, `' . CEGEK_TABLE . '` WHERE '
        . 'CURRENT_DATE BETWEEN `' . INTERNET_DATE_FROM . '` AND `' . INTERNET_DATE_TO . '` '
        . ' AND (`' . CEGEK_TABLE . '`.`' . RECORD_ID . '`=`' . INTERNET_TABLE . '`.`' . INTERNET_CEG_ID . '`'
        . ((strlen($search_internet) > 2) ?
        (' AND ( CONCAT (`' 
        . CEGEK_TABLE . '`.`' . RECORD_CEGNEV . '`, " ", `'
        . CEGEK_TABLE . '`.`' . RECORD_VEZETO . '`)' . ' LIKE "%' . $search_internet . '%" ))') :
        ' OR -1=`' . INTERNET_TABLE . '`.`' . INTERNET_CEG_ID . '`)')
        . ' GROUP BY `' . INTERNET_TABLE . '`.`' . INTERNET_ID . '` '
        . ' ORDER BY `' . CEGEK_TABLE . '`.`' . RECORD_CEGNEV . '` ';



$res = $mysqliLink->query($sql);
$output .= '<button name="internet_add" value="add" title="új tétel felvétele"><img  src="' . IMAGES . 'add.jpg"></button>';
$output .= '<button name="print_invoice"  title="Számlázandók nyomtatása"><img  src="' . IMAGES . 'print.jpg"></button>';
$output .= '&nbsp;&nbsp;&nbsp;Szűrés: <input  onChange="submit();" type="text" name="search_internet" value="' . $search_internet . '">';
$output .= '&nbsp;&nbsp;&nbsp;<input  type="submit"  value="Keres">';
$output .= '<br>';
$output .= '<div class="lists">';
$output .= '<table>';
$output .= '<tr><th>IP cím</th><th>Cégnév</th><th>Kezdet</th><th>Művelet</th></tr>';
while ($res AND $net = $res->fetch_assoc()) {
    $ip_addr = getIpAddrByInternetId($net[INTERNET_ID]);
    $output .= '<tr><td>';
    $output .= (empty($ip_addr)) ? '---' : (IP_ADDR_IP_A . '.' . IP_ADDR_IP_B . '.' . $ip_addr[IP_ADDR_IP_C] . '.' . $ip_addr[IP_ADDR_IP_D] . '</td>');
    $output .= '<td>';
    $output .= getCegNameById($net[INTERNET_CEG_ID]);
    $output .= (empty($net[INTERNET_COMMENT])) ? '' : (' (' . $net[INTERNET_COMMENT] . ')');
    $output .= '</td>';
    $output .= '<td>' . $net[INTERNET_DATE_FROM] . '</td>';
    $output .= '<td>';
    $output .= '<button title="IP cím beállítások nyomtatása" name="internet_print" value="' . $net[INTERNET_ID] . '"><img src="' . IMAGES . 'print.jpg"></button>';
    $output .= '<button name="internet_edit" value="' . $net[INTERNET_ID] . '"><img src="' . IMAGES . 'edit.jpg"></button>';
    $output .= '<button onClick="alert(\'Biztosan ki akarod venni a szolgáltatásból ?\')"title="Tegnapi nappal lezárás" name="internet_lock" value="' . $net[INTERNET_ID] . '"><img src="' . IMAGES . 'lock.jpg"></button>';
    $output .= '</td>';
    $output .= '</tr>';
}

$output .= '</table>';
$output .= '</div>';

