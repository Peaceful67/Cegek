<?php

define("DB_RENT_REQUIRED_ID", 'id');
define("DB_RENT_REQUIRED_NAME", 'name');
define("DB_RENT_REQUIRED_TEL", 'telefon');
define("DB_RENT_REQUIRED_EMAIL", 'email');
define("DB_RENT_REQUIRED_SIZE", 'size');
define("DB_RENT_REQUIRED_DESCRIPT", 'descripion');
define("DB_RENT_REQUIRED_TIME", 'created');
define("DB_RENT_REQUIRED_FULFILLED", 'fulfill');

class RentRequired extends TableManager implements TableHelper {

    const TABLE_NAME = 'required';

    function __construct() {
        parent::__construct(self::TABLE_NAME);
        $this->createFields();
    }

    protected function createFields() {
        $this->addFieldType(DB_RENT_REQUIRED_ID, FIELD_TYPE_ID);
        $this->addFieldType(DB_RENT_REQUIRED_NAME, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_RENT_REQUIRED_TEL, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_RENT_REQUIRED_EMAIL, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_RENT_REQUIRED_DESCRIPT, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_RENT_REQUIRED_SIZE, FIELD_TYPE_NUMBER);
        $this->addFieldType(DB_RENT_REQUIRED_TIME, FIELD_TYPE_TIMESTAMP);
        $this->addFieldType(DB_RENT_REQUIRED_FULFILLED, FIELD_TYPE_BOOL);
        $this->addPrimaryKey(DB_RENT_REQUIRED_ID);
    }

    public function createIfNotExists() {
        $this->addFieldCreate(DB_RENT_REQUIRED_ID, DB_FIELD_CREATE_ID);
        $this->addFieldCreate(DB_RENT_REQUIRED_NAME, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_RENT_REQUIRED_TEL, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_RENT_REQUIRED_EMAIL, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_RENT_REQUIRED_DESCRIPT, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_RENT_REQUIRED_SIZE, DB_FIELD_CREATE_NUMBER);
        $this->addFieldCreate(DB_RENT_REQUIRED_TIME, DB_FIELD_CREATE_TIMESTAMP);
    }

    public function setEdit() {
        
    }

    public function setListView() {
        
    }

    public function setListEdit() {
        
    }

}
