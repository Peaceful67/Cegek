<?php

include_once 'settings.inc';

$output = '
<!DOCTYPE  html>
<head>
		<title>Telephelyi cégek adminisztrációja</title>
                <link type="text/css" rel="stylesheet" media="screen" href="' . DESIGN . 'layout.css">
 		<link type="text/css" rel="stylesheet" media="screen" href="' . DESIGN . 'main.css">
                <link type="text/css" rel="stylesheet" media="screen" href="' . DESIGN . 'ip_addr.css">                
</head>';
if (isset($selectedGroup)) {
    resetVariable('selectedMenu');
}
$selectedGroup = getVariable('selectedGroup');
$selectedMenu = getVariable('selectedMenu');
$authUser = new AuthUser();
if (isset($_GET[COMMAND_STRING])) {
    $command = new Command();
    $task = $command->getCommandOnce($_GET[COMMAND_STRING]);
    reset($task);
    $key = key($task);
    switch ($key) {
        case COMMAND_PASSWORD:
            $authUser->setUserId($task[$key]);
            $selectedMenu = 'passwd';
            break;
    }
} else {
    $authUser->isLoggedIn();
}
$permission = $authUser->getPermission();
$menuModules = new MenuModuls();
$menu_items = $menuModules->getPermitedMenus($permission);
$menuGroups = new MenuGroups();
if ($menuModules->isMenuUnGrouped($selectedMenu)) {
    resetVariable('selectedGroup');
} else {
    $selectedGroup = $menuModules->getMenuById($selectedMenu)[DB_MENU_MODULES_GROUP];
}

$output .= '<body>';
$output .= '<form method="post">';

$output .= '<div class="page_title" id="page_title">';
$menuItem = $menuModules->getMenuById($selectedMenu);

$output .= '<h2>' . (empty($selectedMenu) ? "Ügyfél kezelő felület" : $menuItem[DB_MENU_MODULES_TITLE] ) . '</h2>';
foreach ($menuGroups->readTable() as $group) { // Menucsoport megjelenitese
    foreach ($menu_items as $item) {
        if ($group[DB_MENU_GROUPS_ID] == $item[DB_MENU_MODULES_GROUP]) {
            $output .= '<button ' . ($selectedGroup == $group[DB_MENU_GROUPS_ID] ? 'style="background-color: #32b3bd;"' : '') . ' type="submit" name="selectedGroup" value="' . $group[DB_MENU_GROUPS_ID] . '" >'
                    . $group[DB_MENU_GROUPS_NAME] . '</button>&nbsp;&nbsp;&nbsp;&nbsp;';
            break;
        }
    }
}
foreach ($menu_items as $item) { // A menucsoport mellett megjeleno menuk
    if ($item[DB_MENU_MODULES_GROUP] == DB_MENU_MODULES_MAINGROUP) {
        $output .= '<button ' . ($selectedMenu == $item[DB_MENU_MODULES_ID] ? 'style="background-color: #32b3bd;"' : '') . ' type="submit" name="selectedMenu" value="' . $item[DB_MENU_MODULES_ID] . '">' . $item[DB_MENU_MODULES_MENU] . '</button>&nbsp;&nbsp;&nbsp;&nbsp;';
    }
}
if (!empty($selectedGroup)) {
    $output .= '<br>';
    foreach ($menu_items as $item) { // Ha van kiválasztott menucsoport, annka a menujeinek a megjelenitese
        if ($item[DB_MENU_MODULES_GROUP] == $selectedGroup) {
            $output .= '<button ' . ($selectedMenu == $item[DB_MENU_MODULES_ID] ? 'style="background-color: #32b3bd;"' : '') . 'type="submit" name="selectedMenu" value="' . $item[DB_MENU_MODULES_ID] . '">' . $item[DB_MENU_MODULES_MENU] . '</button>&nbsp;&nbsp;&nbsp;&nbsp;';
        }
    }
}
if($authUser->getUserId() >= 0) {
    $output .= '<br><div class="user_name">Felhasználó :'.$authUser->getName().'</div>';            
}
$output .= '</div>';
$output .= '<div class="torzs">';

if ($permission == AuthAccess::ACCESS_NOBODY) {
    include_once MODULES . $menuModules->getMenuById('login')[DB_MENU_MODULES_MODULE];
} elseif (!empty($selectedMenu)) {
    include_once MODULES . $menuModules->getMenuById($selectedMenu)[DB_MENU_MODULES_MODULE];
}
$output .= '</div>';
$output .= '</form>';
$output .= '</body></html>';

theEnd($output);
