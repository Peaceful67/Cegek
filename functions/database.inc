<?php
// Itt hozzuk letre az adatbazis kapcsolatot es ha valamelyik tabla nem letezik, azt is letrehozzuk

include_once HELPERS.'tableManager.inc';
include_once HELPERS.'tableHelper.inc';
include_once HELPERS.'persons.inc';
include_once HELPERS.'user.inc';
include_once HELPERS.'authUser.inc';
include_once HELPERS.'menuGroups.inc';
include_once HELPERS.'menuModuls.inc';
include_once HELPERS.'rentRequired.inc';
include_once HELPERS.'command.inc';

$db_tables = array ( // classNames
    'Persons',
    'MenuGroups',
    'MenuModuls',
    'User',
    'RentRequired',
    'Command',
);

$mysqliLink = new MYSQLi(DATABASE_ADDR, DB_USER, DB_PASSWD,DATABASE_NAME) or die(mysqli_error());
if ($mysqliLink->connect_errno) {
    error_log("MySQL hiba:" . $mysqliLink->connect_error);
    die(-1);
}
$mysqliLink->set_charset("utf8");
$existingTables = array();
$sql = 'SELECT * FROM information_schema.TABLES WHERE TABLE_SCHEMA = "'.DATABASE_NAME.'";';
$res = $mysqliLink->query($sql);
while($res AND $row = $res->fetch_assoc()) {
    $existingTables[] = $row['TABLE_NAME'];
}

foreach ($db_tables as $tableName => $className) {
    $tableName = $className::TABLE_NAME;
    if(!in_array($tableName, $existingTables)) {
        $createClass = new $className;
        $createClass->createIfNotExists();
    }
}

