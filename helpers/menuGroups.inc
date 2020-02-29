<?php

define("DB_MENU_GROUPS_ID", 'id');
define("DB_MENU_GROUPS_NAME", 'name');
define("DB_MENU_GROUPS_WEIGHT", 'weight');

class MenuGroups extends TableManager {

    const TABLE_NAME = 'menu_groups';

    private $default_group = array(
        1 => [DB_MENU_GROUPS_NAME => 'Törzsadatok', DB_MENU_GROUPS_WEIGHT => 1],
        2 => [DB_MENU_GROUPS_NAME => 'Beállítások', DB_MENU_GROUPS_WEIGHT => 5],
        3 => [DB_MENU_GROUPS_NAME => 'Internet', DB_MENU_GROUPS_WEIGHT => 3],
        2 => [DB_MENU_GROUPS_NAME => 'Bérbeadás', DB_MENU_GROUPS_WEIGHT => 2],
    );

    function __construct() {
        parent::__construct(self::TABLE_NAME);
        $this->createFields();
    }

    protected function createFields() {
        $this->addFieldType(DB_MENU_GROUPS_ID, FIELD_TYPE_ID);
        $this->addFieldType(DB_MENU_GROUPS_NAME, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_MENU_GROUPS_WEIGHT, FIELD_TYPE_NUMBER);
        $this->addPrimaryKey(DB_MENU_GROUPS_ID);
    }

    public function createIfNotExists() {
        $this->addFieldCreate(DB_MENU_GROUPS_ID, DB_FIELD_CREATE_ID);
        $this->addFieldCreate(DB_MENU_GROUPS_NAME, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_MENU_GROUPS_WEIGHT, DB_FIELD_CREATE_NUMBER);
        parent::ifNotExists();
    }

    public function getGroupById($id) {
        $items = parent::getItemsBy(DB_MENU_GROUPS_ID, $id);
        return empty($items) ? array() : $items[0];
    }

    public function readTable() {
        $groups = parent::readTableOrderBy(DB_MENU_GROUPS_WEIGHT);
        if (empty($groups)) {
            $this->setDefaultValues();
            $groups = parent::readTableOrderBy(DB_MENU_GROUPS_WEIGHT);
        }
        return $groups;
    }

    public function setDefaultValues() {
        $this->truncateTable();
        foreach ($this->default_group as $id => $item) {
            $this->addItem([
                DB_MENU_GROUPS_ID => $id,
                DB_MENU_GROUPS_NAME => $item[DB_MENU_GROUPS_NAME],
                DB_MENU_GROUPS_WEIGHT => $item[DB_MENU_GROUPS_WEIGHT],
            ]);
        }
    }

}
