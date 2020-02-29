<?php

$logger_categories = array(
    LOGGER_CAT_LOGIN => 'Belépés',
    LOGGER_CAT_MODIFY_CEG=> 'Cég adatok módosítása',
    LOGGER_CAT_INACTIV_CEG => 'Cég inaktiválása',
    LOGGER_CAT_ACTIV_CEG => 'Cég vissza aktiválása',
    LOGGER_CAT_INSERT_CEG => 'Cég felvétele',
    LOGGER_CAT_INSERT_INTERNET => 'Internet felvétele',
    LOGGER_CAT_DELETE_INTERNET => 'Internet lezárása',
    LOGGER_CAT_MODIFY_INTERNET => 'Internet módosítása',
    LOGGER_CAT_PRINT_CEGEK => 'Cégek listájának nyomtatása',
    LOGGER_CAT_PRINT_IP => 'IP cím beállítások nyomtatása',
    LOGGER_CAT_PRINT_INVOICE => 'Számlázandók nyomtatása', 
    LOGGER_CAT_OPTIONS_CHANGED => 'Beállítások módosítása',
    LOGGER_CAT_EMAIL_SENT => 'Email küldés',
);

if (!isset($logger_from)) {
    $logger_from = date('Y-m-d', strtotime($today.' -1 month'));
}
if (!isset($logger_to)) {
    $logger_to = $today;
}
if (!isset($selected_act)) {
    $selected_act = -1;;
}
$output .= '<br><div class="keret">';
$output .= '<label >Művelet: </label><select id="selected_act" name="selected_act" onChange="submit();">';
$output .= '<option value="-1">Válassz műveletet !</option>';
foreach ($logger_categories as $cat_id => $cat_name) {
    $output .= '<option value="' . $cat_id . '" ' . (($selected_act == $cat_id) ? " selected " : "") . '>' . $cat_name . '</option>';
}
$output .= '</select><br><br>';
$output .= '<label >Időszak: </label>
            <input type="date" name="logger_from"  value="' . $logger_from . '" >
            <input type="date" name="logger_to"  value="' . $logger_to . '">'
        . '&nbsp;&nbsp;&nbsp;<input type="submit" name="submit" value="Keresés">';
$output .= '</div><br><table border="1"><caption>Aktivitás listázása</caption>';
$output .= '<tr><th>Elkövető</th><th>Mező</th><th>Művelet</th><th>Időpont</th></tr>';

$sql = 'SELECT * FROM `'.LOGGER_TABLE.'` WHERE '
        . '(`'.LOGGER_TIMESTAMP.'` BETWEEN "'.$logger_from.' 00:00:00" AND "'.$logger_to.' 23:59:59" ) '
        . 'AND `'.LOGGER_CATEGORY.'`="' . $selected_act . '"'
        . ' ORDER BY `'.LOGGER_TIMESTAMP.'` DESC ;';
            
$res = $mysqliLink->query($sql);
while ($res AND $row = $res->fetch_assoc()) {

    $output .= "<tr>";

    $output .= '<td>---</td>';
    $output .= '<td>'.$row[LOGGER_FIELD].'</td>';
    $output .= '<td><a title="'.$logger_categories[$row[LOGGER_CATEGORY]].'">'.$row[LOGGER_COMMENT] . '</a></td>';
    $output .= '<td><small>' . $row[LOGGER_TIMESTAMP] . '</small></td>';
    $output .= "</tr>";
}
$output .= "</table></div>";


