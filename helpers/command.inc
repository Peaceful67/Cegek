<?php

define("DB_COMMAND_MEM_ID", 'mem_id');
define("DB_COMMAND_CODE", 'code');
define("DB_COMMAND_EXPIRE", 'expire');
define("DB_COMMAND_NAME", 'name');
define("DB_COMMAND_VALUE", 'value');

class Command extends TableManager {

    const TABLE_NAME = 'command';

    function __construct() {
        parent::__construct(self::TABLE_NAME);
        $this->createFields();
    }

    public function getCommandOnce($code) {
        $sql = 'DELETE FROM `' . $this->tableName . '` WHERE `' . DB_COMMAND_EXPIRE . '` < CURRENT_TIMESTAMP();';
        $this->my->query($sql);
        $item = $this->getItemById($code);
        $this->deleteItemById($code);
        return [$item[DB_COMMAND_NAME] => $item[DB_COMMAND_VALUE]];
    }

    public function putCommand($mem_id, $name, $value, $exp_day) {
        $code = $this->randomCode();
        $this->addItem([
            DB_COMMAND_MEM_ID => $mem_id,
            DB_COMMAND_NAME => $name,
            DB_COMMAND_VALUE => $value,
            DB_COMMAND_CODE => $code,
            DB_COMMAND_EXPIRE => 'TIMESTAMPADD(DAY,' . $exp_day . ',CURRENT_TIMESTAMP())',
        ]);
        return $code;
    }

    public function createIfNotExists() {
        $this->createFields();
        $this->addFieldCreate(DB_COMMAND_MEM_ID, DB_FIELD_CREATE_RELATED_ID);
        $this->addFieldCreate(DB_COMMAND_CODE, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_COMMAND_EXPIRE, DB_FIELD_CREATE_TIMESTAMP);
        $this->addFieldCreate(DB_COMMAND_NAME, DB_FIELD_CREATE_VARCHAR);
        $this->addFieldCreate(DB_COMMAND_VALUE, DB_FIELD_CREATE_VARCHAR);

        parent::ifNotExists();
    }

    private function randomCode() {
        $alphabet = "abcdefghijklmnopqrstuwxyzABCDEFGHIJKLMNOPQRSTUWXYZ0123456789";
        $len = mb_strlen($alphabet) - 1;
        $code = '';
        for ($i = 0; $i < 8; $i++) {
            $n = rand(0, $len);
            $code .= $alphabet[$n];
        }
        return $code;
    }

    protected function createFields() {
        $this->addFieldType(DB_COMMAND_MEM_ID, FIELD_TYPE_RELATED_ID);
        $this->addFieldType(DB_COMMAND_CODE, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_COMMAND_EXPIRE, FIELD_TYPE_TIMESTAMP);
        $this->addFieldType(DB_COMMAND_NAME, FIELD_TYPE_VARCHAR);
        $this->addFieldType(DB_COMMAND_VALUE, FIELD_TYPE_VARCHAR);
        $this->addPrimaryKey(DB_COMMAND_CODE);
    }

}
