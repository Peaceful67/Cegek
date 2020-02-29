<?php

if (isset($internet_edit_cancel)) {
    $internet_edit = -1;
    return;
}

if (isset($internet_add) OR ( !isset($internet_id))) {
    $internet_id = -1;
}
if ($internet_id > 0) {
    $internet = getInternetById($internet_id);
    if (!empty($internet)) {
        if (!isset($selected_ceg)) {
            $ceg = getCegByInternetId($internet_id);
            if (!empty($ceg)) {
                $selected_ceg = $ceg[RECORD_ID];
            } else {
                $selected_ceg = -1;
            }
        }
        if (!isset($selected_ip)) {
            $ip_addr = getIpAddrByInternetId($internet_id);
            $selected_ip = (!empty($ip_addr)) ? $ip_addr[IP_ADDR_ID] : -1;
        }
        if (!isset($date_from)) {
            $date_from = $internet[INTERNET_DATE_FROM];
        }
        if (!isset($date_to)) {
            $date_to = $internet[INTERNET_DATE_TO];
        }
        if (!isset($discount)) {
            $discount = $internet[INTERNET_DISCOUNT];
        }
        if (!isset($comment)) {
            $comment = $internet[INTERNET_COMMENT];
        }
    }
}

if (!isset($selected_ceg)) {
    $selected_ceg = -1;
}

if (!isset($selected_ip)) {
    $selected_ip = -1;
}
if (!isset($date_from)) {
    $date_from = $today;
}
if (!isset($date_to)) {
    $date_to = FOREVER;
}
if (!isset($discount)) {
    $discount = 0;
}
if (!isset($chk_eszamla)) {
    $chk_eszamla = 'off';
}
if (!isset($comment)) {
    $comment = '';
}


if (isset($internet_save)) {
    if ($internet_save < 0) {
        $sql = 'INSERT INTO `' . INTERNET_TABLE . '` '
                . '(`' . INTERNET_CEG_ID . '`, `' . INTERNET_DATE_FROM . '`,`' . INTERNET_DATE_TO . '`,`'
                . INTERNET_DISCOUNT . '`,`' . INTERNET_COMMENT . '`)'
                . ' VALUES '
                . '(' . $selected_ceg . ', "' . $date_from . '","' . $date_to . '",' . $discount . ',"' . $comment . '");';
        $mysqliLink->query($sql);
        $internet_id = $mysqliLink->insert_id;
        $sql = 'UPDATE `' . IP_ADDR_TABLE . '` SET '
                . '`' . IP_ADDR_INTERNET_ID . '`=' . $internet_id
                . ' WHERE `' . IP_ADDR_ID . '`=' . $selected_ip;
        $mysqliLink->query($sql);
    } else {
        $sql = 'UPDATE `' . INTERNET_TABLE . '` SET '
                . '`' . INTERNET_DATE_FROM . '`="' . $date_from . '", '
                . '`' . INTERNET_DATE_TO . '`="' . $date_to . '", '
                . '`' . INTERNET_CEG_ID . '`=' . $selected_ceg . ', '
                . '`' . INTERNET_DISCOUNT . '`=' . $discount . ', '
                . '`' . INTERNET_ESZAMLA . '`=' . (($chk_eszamla == 'on') ? 1 : 0) . ', '
                . '`' . INTERNET_COMMENT . '`="' . $comment . '"'
                . ' WHERE `' . INTERNET_ID . '`=' . $internet_save . ';';
        $mysqliLink->query($sql);
        $sql = 'UPDATE `' . IP_ADDR_TABLE . '` SET '
                . '`' . IP_ADDR_INTERNET_ID . '`=0'
                . ' WHERE `' . IP_ADDR_INTERNET_ID . '`=' . $internet_save;
        $mysqliLink->query($sql);
        $sql = 'UPDATE `' . IP_ADDR_TABLE . '` SET '
                . '`' . IP_ADDR_INTERNET_ID . '`=' . $internet_save
                . ' WHERE `' . IP_ADDR_ID . '`=' . $selected_ip;
        $mysqliLink->query($sql);
    }
    return;
} 

$output .= '<div class="keret editor">';
$output .= '<label>Cégnév:</label>';
$output .= '<select name="selected_ceg">';
$output .= '<option value=-1 ' . (($selected_ceg == -1) ? " selected" : "") . ' disabled>Válassz !</option>';
foreach (getActCegList() as $ceg) {
    $output .= '<option value=' . $ceg[RECORD_ID] . ' ' . (($selected_ceg == $ceg[RECORD_ID]) ? " selected" : "") . '>' . $ceg[RECORD_CEGNEV] . '</option>';
}
$output .= '</select>';

$output .= '<br>';
$output .= '<label>Megjegyzés: </label><input  type="text" name="comment" value="' . $comment . '"><br>';
$output .= '<label>IP cím:</label><select name="selected_ip" >';
$output .= '<option value="-1" ' . (($selected_ip == -1) ? " selected" : "") . ' disabled>Válassz !</option>';
foreach (getIpAddresses() as $ip_addr) {
    $ip_addr_id = $ip_addr[IP_ADDR_ID];
    $output .= '<option value="' . $ip_addr_id . '" ' . (($selected_ip == $ip_addr_id) ? " selected" : "")
            . (isIpAddrFree($ip_addr_id) ? '' : ' disabled ') . '>'
            . IP_ADDR_IP_A . '.' . IP_ADDR_IP_B . '.' . $ip_addr[IP_ADDR_IP_C] . '.' . $ip_addr[IP_ADDR_IP_D] . '</option>';
}
$output .= '</select>';
$output .= '<br>';
$output .= '<label>Kezdet: </label><input type="date" name="date_from" value="' . $date_from . '"><br>';
$output .= '<label>Zárás: </label><input type="date" name="date_to" value="' . $date_to . '"><br>';
$output .= '<label>Kedvezmény: </label><input maxlength="5" size="6" type="number" name="discount" value="' . $discount . '"> Ft<br>';
$output .= '<button type="submit" name="internet_save" value="' . $internet_id . '">' . ((-1 == $internet_id) ? 'Rögzítés' : 'Módosítás') . '</button>';
$output .= '&nbsp;&nbsp;&nbsp;&nbsp;<button name="internet_edit_cancel">Vissza</button>';
$output .= '<input type="hidden" name="internet_edit" value="' . $internet_edit . '">';
//$output .= '<input type="hidden" name="selected_ceg" value="' . $selected_ceg . '">';
$output .= '</div>';
