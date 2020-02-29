<?php

define("DB_AUTH_USER_ID", 'id');
define("DB_AUTH_USER_NAME", 'name');
define("DB_AUTH_USER_USERNAME", 'username');
define("DB_AUTH_USER_PASSWORD", 'passwd');
define("DB_AUTH_USER_EMAIL", 'email');
define("DB_AUTH_USER_PERMISSION", 'permission');
define("DB_AUTH_USER_OWNER_ID", 'owner_id');

class User extends TableManager implements TableHelper {

    const TABLE_NAME = 'users';

    protected $userId = -1;

    function __construct() {
        parent::__construct(self::TABLE_NAME);
        $this->createFields();
    }

    public function setEdit() {
        $this->modField(DB_AUTH_USER_NAME, [
            FIELD_NAME => 'Teljes név',
            FIELD_EDITSIZE => 20,
        ]);
        $this->modField(DB_AUTH_USER_USERNAME, [
            FIELD_NAME => 'Felhasználó',
            FIELD_EDITSIZE => 20,
        ]);
        $this->modField(DB_AUTH_USER_EMAIL, [
            FIELD_NAME => 'Email cím',
            FIELD_EDITSIZE => 20,
        ]);
        $this->modField(DB_AUTH_USER_PERMISSION, [
            FIELD_NAME => 'Jogosultságok',
            FIELD_EDITSIZE => 1,
            FIELD_EDITOR => 'permissionEditor',
            FIELD_SAVER => 'permissionSaver',
        ]);
        return $this->fields;
    }

    public function setListView() {
        $this->modField(DB_AUTH_USER_NAME, [
            FIELD_NAME => 'Teljes név',
            FIELD_LISTSIZE => 20
        ]);
        $this->modField(DB_AUTH_USER_USERNAME, [
            FIELD_NAME => 'Felhasználó',
            FIELD_LISTSIZE => 20,
        ]);
        $this->modField(DB_AUTH_USER_EMAIL, [
            FIELD_NAME => 'Email cím',
            FIELD_LISTSIZE => 20,
        ]);
        $this->modField(DB_AUTH_USER_PERMISSION, [
            FIELD_NAME => 'Jogosultságok',
            FIELD_LISTSIZE => 20,
            FIELD_VIEWER => 'permissionViewer',
        ]);
        return $this->fields;
    }

    public function setListEdit() {
        $this->setEdit();
        $this->setListView();
        return $this->fields;
    }

    public function permissionSaver() {
        global $chk_permission;
        $itemValue = 0;
        foreach (AuthAccess::$accessNames as $bit => $name) {
            if ($bit == AuthAccess::ACCESS_NOBODY OR $bit == AuthAccess::ACCESS_FULL) {
                continue;
            }
            if (isset($chk_permission[$bit])AND $chk_permission[$bit] == 'on') {
                $itemValue |= $bit;
            }
        }
        return $itemValue;
    }

    public function permissionEditor() {
        $ret = '';
        $first = true;
        $access = (int) $this->getFieldValue(DB_AUTH_USER_PERMISSION);
        foreach (AuthAccess::$accessNames as $bit => $name) {
            if ($bit == AuthAccess::ACCESS_NOBODY OR $bit == AuthAccess::ACCESS_FULL) {
                continue;
            }
            if ($first) {
                $first = false;
            } else {
                $ret .= '<label> </label>';
            }
            $ret .= '<input type="checkbox" name="chk_permission[' . $bit . ']"';
            if (($access & $bit) > 0) {
                $ret .= ' checked ';
            }
            $ret .= '><label>' . $name . '</label><br>';
        }

        return $ret;
    }

    public function permissionViewer() {
        $ret = '';
        $access = (int) $this->getFieldValue(DB_AUTH_USER_PERMISSION);
        foreach (AuthAccess::$accessNames as $bit => $name) {
            if ($bit == AuthAccess::ACCESS_NOBODY OR $bit == AuthAccess::ACCESS_FULL) {
                continue;
            }
            if (($access & $bit) > 0) {
                $ret .= $name . '<br>';
            }
        }
        return $ret;
    }

    public function getNameOfUser($user_id) {
        $user = $this->getItemById($user_id);
        return empty($user) ? '' : $user[DB_AUTH_USER_NAME];
    }

    public function getName() {
        return $this->getNameOfUser($this->userId);
    }

    public function getEmailOfUser($user_id) {
        $user = $this->getItemById($user_id);
        return empty($user) ? '' : $user[DB_AUTH_USER_EMAIL];
    }

    public function createIfNotExists() {
        $this->createFields();
        $this->addFieldCreate(DB_AUTH_USER_ID, DB_FIELD_CREATE_ID);
        $this->addFieldCreate(DB_AUTH_USER_NAME, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_AUTH_USER_USERNAME, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_AUTH_USER_PASSWORD, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_AUTH_USER_EMAIL, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_AUTH_USER_PERMISSION, DB_FIELD_CREATE_NUMBER);
        $this->addFieldCreate(DB_AUTH_USER_OWNER_ID, DB_FIELD_CREATE_RELATED_ID);

        parent::ifNotExists();
    }

    protected function createFields() {
        $this->addFieldType(DB_AUTH_USER_ID, FIELD_TYPE_ID);
        $this->addFieldType(DB_AUTH_USER_NAME, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_AUTH_USER_USERNAME, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_AUTH_USER_PASSWORD, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_AUTH_USER_EMAIL, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_AUTH_USER_PERMISSION, FIELD_TYPE_CHECKBOXES);
        $this->addFieldType(DB_AUTH_USER_OWNER_ID, FIELD_TYPE_RELATED_ID);
        $this->addPrimaryKey(DB_AUTH_USER_ID);
    }

    public function readTable() {
        return parent::readTableOrderBy(DB_AUTH_USER_USERNAME);
    }

}
