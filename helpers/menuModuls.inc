<?php

define("DB_MENU_MODULES_ID", 'id');
define("DB_MENU_MODULES_TITLE", 'title');
define("DB_MENU_MODULES_MENU", 'menu');
define("DB_MENU_MODULES_MODULE", 'modul');
define("DB_MENU_MODULES_DEPENDENCY", 'dependency');
define("DB_MENU_MODULES_GROUP", 'group');
define("DB_MENU_MODULES_WEIGHT", 'weight');
define("DB_MENU_MODULES_ACCESS", 'access');
define("DB_MENU_MODULES_ENABLED", 'ena');

define("DB_MENU_MODULES_MAINGROUP", -1);
define("DB_MENU_MODULES_INVISIBLE", -2);

class MenuModuls extends TableManager {

    const TABLE_NAME = 'menu_moduls';

    static $default_menu = [
        "cegek" => [
            DB_MENU_MODULES_TITLE => 'Cégek karbantartása',
            DB_MENU_MODULES_MENU => 'Cégek',
            DB_MENU_MODULES_MODULE => 'cegek.inc',
            DB_MENU_MODULES_DEPENDENCY => '',
            DB_MENU_MODULES_GROUP => 1,
            DB_MENU_MODULES_WEIGHT => 1,
            DB_MENU_MODULES_ACCESS => AuthAccess::ACCESS_ASSISTANT,
            DB_MENU_MODULES_ENABLED => 1,
        ],
        "users" => [
            DB_MENU_MODULES_TITLE => 'Felhasználók karbantartása',
            DB_MENU_MODULES_MENU => 'Felhaszn',
            DB_MENU_MODULES_MODULE => 'edit_users.inc',
            DB_MENU_MODULES_DEPENDENCY => '',
            DB_MENU_MODULES_GROUP => 1,
            DB_MENU_MODULES_WEIGHT => 2,
            DB_MENU_MODULES_ACCESS => AuthAccess::ACCESS_ADMIN,
            DB_MENU_MODULES_ENABLED => 1,
        ],
        "persons" => [
            DB_MENU_MODULES_TITLE => 'Személyek karbantartása',
            DB_MENU_MODULES_MENU => 'Személyek',
            DB_MENU_MODULES_MODULE => 'edit_persons.inc',
            DB_MENU_MODULES_DEPENDENCY => '',
            DB_MENU_MODULES_GROUP => 1,
            DB_MENU_MODULES_WEIGHT => 3,
            DB_MENU_MODULES_ACCESS => AuthAccess::ACCESS_ASSISTANT,
            DB_MENU_MODULES_ENABLED => 1,
        ],
        "internet" => [
            DB_MENU_MODULES_TITLE => 'Internet szolgáltatás beállításai',
            DB_MENU_MODULES_MENU => 'Szolgáltatás',
            DB_MENU_MODULES_MODULE => 'internet_services.inc',
            DB_MENU_MODULES_DEPENDENCY => '',
            DB_MENU_MODULES_GROUP => 3,
            DB_MENU_MODULES_WEIGHT => 1,
            DB_MENU_MODULES_ACCESS => AuthAccess::ACCESS_ASSISTANT,
            DB_MENU_MODULES_ENABLED => 1,
        ],
        "ip_addr" => [
            DB_MENU_MODULES_TITLE => 'IP cím kezelés',
            DB_MENU_MODULES_MENU => 'IP címek',
            DB_MENU_MODULES_MODULE => 'ip_addr.inc',
            DB_MENU_MODULES_DEPENDENCY => '',
            DB_MENU_MODULES_GROUP => 3,
            DB_MENU_MODULES_WEIGHT => 2,
            DB_MENU_MODULES_ACCESS => AuthAccess::ACCESS_USER,
            DB_MENU_MODULES_ENABLED => 1,
        ],
        "internet_prices" => [
            DB_MENU_MODULES_TITLE => 'Internet árak beállításai',
            DB_MENU_MODULES_MENU => 'Árak',
            DB_MENU_MODULES_MODULE => 'internet_prices.inc',
            DB_MENU_MODULES_DEPENDENCY => '',
            DB_MENU_MODULES_GROUP => 3,
            DB_MENU_MODULES_WEIGHT => 3,
            DB_MENU_MODULES_ACCESS => AuthAccess::ACCESS_ASSISTANT,
            DB_MENU_MODULES_ENABLED => 1,
        ],
        "settings" => [
            DB_MENU_MODULES_TITLE => 'Adminisztráció',
            DB_MENU_MODULES_MENU => 'Admin',
            DB_MENU_MODULES_MODULE => 'settings.inc',
            DB_MENU_MODULES_DEPENDENCY => '',
            DB_MENU_MODULES_GROUP => DB_MENU_MODULES_MAINGROUP,
            DB_MENU_MODULES_WEIGHT => 5,
            DB_MENU_MODULES_ACCESS => AuthAccess::ACCESS_ADMIN,
            DB_MENU_MODULES_ENABLED => 1,
        ],
        "logger" => [
            DB_MENU_MODULES_TITLE => 'Események listája',
            DB_MENU_MODULES_MENU => 'Logger',
            DB_MENU_MODULES_MODULE => 'logger.inc',
            DB_MENU_MODULES_DEPENDENCY => '',
            DB_MENU_MODULES_GROUP => DB_MENU_MODULES_MAINGROUP,
            DB_MENU_MODULES_WEIGHT => 5,
            DB_MENU_MODULES_ACCESS => AuthAccess::ACCESS_ADMIN,
            DB_MENU_MODULES_ENABLED => 1,
        ],
        "required" => [
            DB_MENU_MODULES_TITLE => 'Keresett helyiségek',
            DB_MENU_MODULES_MENU => 'Igények',
            DB_MENU_MODULES_MODULE => 'required.inc',
            DB_MENU_MODULES_DEPENDENCY => '',
            DB_MENU_MODULES_GROUP => 2,
            DB_MENU_MODULES_WEIGHT => 3,
            DB_MENU_MODULES_ACCESS => AuthAccess::ACCESS_ASSISTANT,
            DB_MENU_MODULES_ENABLED => 1,
        ],
        "login" => [
            DB_MENU_MODULES_TITLE => 'Belépés',
            DB_MENU_MODULES_MENU => 'Belépés',
            DB_MENU_MODULES_MODULE => 'login.inc',
            DB_MENU_MODULES_DEPENDENCY => '',
            DB_MENU_MODULES_GROUP => DB_MENU_MODULES_INVISIBLE,
            DB_MENU_MODULES_WEIGHT => 0,
            DB_MENU_MODULES_ACCESS => AuthAccess::ACCESS_NOBODY,
            DB_MENU_MODULES_ENABLED => 1,
        ],
        "logout" => [
            DB_MENU_MODULES_TITLE => 'Kilépés',
            DB_MENU_MODULES_MENU => 'Kilépés',
            DB_MENU_MODULES_MODULE => 'logout.inc',
            DB_MENU_MODULES_DEPENDENCY => '',
            DB_MENU_MODULES_GROUP => DB_MENU_MODULES_MAINGROUP,
            DB_MENU_MODULES_WEIGHT => 0,
            DB_MENU_MODULES_ACCESS => AuthAccess::ACCESS_USER,
            DB_MENU_MODULES_ENABLED => 1,
        ],
        "passwd" => [
            DB_MENU_MODULES_TITLE => 'Jelszó módosítás',
            DB_MENU_MODULES_MENU => 'Jelszó',
            DB_MENU_MODULES_MODULE => 'new_passwd.inc',
            DB_MENU_MODULES_DEPENDENCY => '',
            DB_MENU_MODULES_GROUP => DB_MENU_MODULES_MAINGROUP,
            DB_MENU_MODULES_WEIGHT => 0,
            DB_MENU_MODULES_ACCESS => AuthAccess::ACCESS_NOBODY,
            DB_MENU_MODULES_ENABLED => 1,
        ],
    ];

    public function goHome() {
        global $host_url;
        resetVariable('selectedMenu');
        resetVariable('selectedGroup');
        header("Location: " . $host_url);
    }

    public function getMenuById($id) {
        $items = parent::getItemsBy(DB_MENU_MODULES_ID, $id);
        return empty($items) ? array() : $items[0];
    }

    public function isMenuUnGrouped($id) {
        $menu = $this->getMenuById($id);
        return (!isset($menu[DB_MENU_MODULES_GROUP]) OR $menu[DB_MENU_MODULES_GROUP] <= 0) ? true : false;
    }

    public function getPermitedMenus($perm) {
        $menus = parent::readTableOrderBy(DB_MENU_MODULES_WEIGHT);
        if (empty($menus)) {
            $this->setDefaultValues();
            $menus = parent::readTableOrderBy(DB_MENU_MODULES_WEIGHT);
        }
        $ret = array();
        foreach ($menus as $menu) {
            if($perm & $menu[DB_MENU_MODULES_ACCESS]) {
                $ret[] = $menu;
            }
        }
        return $ret;
    }

    function __construct() {
        parent::__construct(self::TABLE_NAME);
        $this->createFields();
    }

    protected function createFields() {
        $this->addFieldType(DB_MENU_MODULES_ID, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_MENU_MODULES_TITLE, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_MENU_MODULES_MENU, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_MENU_MODULES_MODULE, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_MENU_MODULES_DEPENDENCY, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_MENU_MODULES_GROUP, FIELD_TYPE_RELATED_ID);
        $this->addFieldType(DB_MENU_MODULES_WEIGHT, FIELD_TYPE_NUMBER);
        $this->addFieldType(DB_MENU_MODULES_ACCESS, FIELD_TYPE_NUMBER);
        $this->addFieldType(DB_MENU_MODULES_ENABLED, FIELD_TYPE_BOOL);
        $this->addPrimaryKey(DB_MENU_MODULES_ID);
    }

    public function setEdit() {
        
    }

    public function setDefaultValues() {
        $this->truncateTable();
        foreach ($this->default_menu as $id => $item) {
            $this->addMenuItem($id, $item);
        }
    }

    public function addNewMenuItem($id) {
        $item = self::$default_menu[$id];
        $this->addMenuItem($id, $item);
    }

    protected function addMenuItem($id, $item) {
        $this->addItem([
            DB_MENU_MODULES_ID => $id,
            DB_MENU_MODULES_TITLE => $item[DB_MENU_MODULES_TITLE],
            DB_MENU_MODULES_MENU => $item[DB_MENU_MODULES_MENU],
            DB_MENU_MODULES_MODULE => $item[DB_MENU_MODULES_MODULE],
            DB_MENU_MODULES_DEPENDENCY => $item[DB_MENU_MODULES_DEPENDENCY],
            DB_MENU_MODULES_GROUP => $item[DB_MENU_MODULES_GROUP],
            DB_MENU_MODULES_WEIGHT => $item[DB_MENU_MODULES_WEIGHT],
            DB_MENU_MODULES_ACCESS => $item[DB_MENU_MODULES_ACCESS],
            DB_MENU_MODULES_ENABLED => $item[DB_MENU_MODULES_ENABLED],
        ]);
    }

    public function createIfNotExists() {
        $this->createFields();
        $this->addFieldCreate(DB_MENU_MODULES_ID, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_MENU_MODULES_TITLE, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_MENU_MODULES_MENU, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_MENU_MODULES_MODULE, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_MENU_MODULES_DEPENDENCY, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_MENU_MODULES_GROUP, DB_FIELD_CREATE_RELATED_ID);
        $this->addFieldCreate(DB_MENU_MODULES_WEIGHT, DB_FIELD_CREATE_NUMBER);
        $this->addFieldCreate(DB_MENU_MODULES_ACCESS, DB_FIELD_CREATE_NUMBER);
        $this->addFieldCreate(DB_MENU_MODULES_ENABLED, DB_FIELD_CREATE_BOOL);
        parent::ifNotExists();
    }

    public function getNewMenus() {
        $menus = parent::readTableOrderBy(DB_MENU_MODULES_MENU);
        $new = unserialize(serialize(self::$default_menu));
        foreach ($menus as $menu) {
            $id = $menu[$this->key];
            if (array_key_exists($id, $new)) {
                unset($new[$id]);
            }
        }
        return $new;
    }

    public function getMenus() {
        return parent::readTableOrderBy(DB_MENU_MODULES_MENU);
    }

}
