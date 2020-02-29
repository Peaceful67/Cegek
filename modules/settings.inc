<?php

if (!isset($email_warning)) {
    $email_warning = getOptionValue(OPTIONS_NAME_EMAIL_WARNING);
}
if (!isset($host_check)) {
    $host_check = getOptionValue(OPTIONS_NAME_HOST_CHECK);
}
if (isset($submit_email)) {
    updateOption(OPTIONS_NAME_EMAIL_WARNING, $email_warning);
    updateOption(OPTIONS_NAME_HOST_CHECK, $host_check);
}
if(isset($submit_restore_menus)) {
    $menuModules->setDefaultValues();
}

if(isset($add_menu)) {
    $menuModules->addNewMenuItem($add_menu);
}

$output .= '<div class="keret">';
$output .= '<label style="width:200px;  display:inline-block;">Figyelmeztető email:</label>';
$output .= '<input type="text" maxlength="32" name="email_warning" value="'
        . $email_warning . '"><br>';
$output .= '<label style="width:200px;  display:inline-block;">Külső szerver :</label>';
$output .= '<input type="text" maxlength="32" name="host_check" value="'
        . $host_check . '"><br>';
$output .= '<button name="submit_email" value="submiting" title="Mentés">Rögzít</button>';
$output .= '</div>';
$output .= '<div class="keret">';
$output .= '<button name="submit_restore_menus" value="submiting" title="Menü alaphelyzetbe állítása">Visszaállítás</button><br><br>';
$output .= '<label style="width:200px;  display:inline-block;">Kikapcsolt menük :</label>';
$newMenus = $menuModules->getNewMenus();
foreach ($newMenus as $key => $value) {
    $output .= '<button name="add_menu" value="'.$key.'" title="Menü bekapcsolása">'.$value[DB_MENU_MODULES_MENU].'</button>&nbsp;&nbsp;&nbsp;';
}
$output .= '</div>';
