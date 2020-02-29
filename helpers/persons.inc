<?php

define("DB_PERSONS_ID", 'id');
define("DB_PERSONS_NAME", 'name');
define("DB_PERSONS_ADDR", 'addr');
define("DB_PERSONS_TEL", 'telephone');
define("DB_PERSONS_EMAIL", 'email');
define("DB_PERSONS_CEGID", 'ceg_id');

class Persons extends TableManager implements TableHelper {

    const TABLE_NAME = 'persons';

    function __construct() {
        parent::__construct(self::TABLE_NAME);
        $this->createFields();
    }

    function createIfNotExists() {
        $this->addFieldCreate(DB_PERSONS_ID, DB_FIELD_CREATE_ID);
        $this->addFieldCreate(DB_PERSONS_CEGID, DB_FIELD_CREATE_RELATED_ID);
        $this->addFieldCreate(DB_PERSONS_NAME, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_PERSONS_ADDR, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_PERSONS_TEL, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_PERSONS_EMAIL, DB_FIELD_CREATE_VARCHAR);
        parent::ifNotExists();
    }

    protected function createFields() {
        $this->addFieldType(DB_PERSONS_ID, FIELD_TYPE_ID);
        $this->addFieldType(DB_PERSONS_CEGID, FIELD_TYPE_RELATED_ID);
        $this->addFieldType(DB_PERSONS_NAME, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_PERSONS_ADDR, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_PERSONS_TEL, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_PERSONS_EMAIL, FIELD_TYPE_VARCHAR);
        $this->addPrimaryKey(DB_PERSONS_ID);
    }

    public function setEdit() {
        $this->modField(DB_PERSONS_NAME, [
            FIELD_NAME => 'Teljes név',
            FIELD_EDITSIZE => 20]);
        $this->modField(DB_PERSONS_ADDR, [
            FIELD_NAME => 'Cím',
            FIELD_EDITSIZE => 30]);
        $this->modField(DB_PERSONS_TEL, [
            FIELD_NAME => 'Telefon',
            FIELD_EDITSIZE => 20]);
        $this->modField(DB_PERSONS_EMAIL, [
            FIELD_NAME => 'Email cím',
            FIELD_EDITSIZE => 20]);
    }

    public function setListView() {
        $this->modField(DB_PERSONS_NAME, [
            FIELD_NAME => 'Teljes név',
            FIELD_LISTSIZE => 20]);
        $this->modField(DB_PERSONS_ADDR, [
            FIELD_NAME => 'Cím',
            FIELD_LISTSIZE => 30]);
        $this->modField(DB_PERSONS_TEL, [
            FIELD_NAME => 'Telefon',
            FIELD_LISTSIZE => 20]);
        $this->modField(DB_PERSONS_EMAIL, [
            FIELD_NAME => 'Email cím',
            FIELD_LISTSIZE => 20]);
    }

    public function setListEdit() {
        $this->setEdit();
        $this->setListView();
        return $this->fields;
    }

}
