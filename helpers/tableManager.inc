<?php

define("DB_FIELD_CREATE_ID", 'int(11) NOT NULL AUTO_INCREMENT');
define("DB_FIELD_CREATE_RELATED_ID", 'int(11) NOT NULL DEFAULT "-1"');
define("DB_FIELD_CREATE_NUMBER", 'int(8) NOT NULL DEFAULT "0"');
define("DB_FIELD_CREATE_CHECKBOXES", 'int(16) NOT NULL DEFAULT "0"');
define("DB_FIELD_CREATE_VARCHAR", 'varchar(255) NOT NULL');
define("DB_FIELD_CREATE_BOOL", 'int(1) NOT NULL DEFAULT "0"');
define("DB_FIELD_CREATE_TIMESTAMP", 'timestamp(1) NOT NULL DEFAULT CURRENT_TIMESTAMP(1)');

define("FIELD_TYPE_ID", 'type_id');
define("FIELD_TYPE_RELATED_ID", 'related');
define("FIELD_TYPE_NUMBER", 'number');
define("FIELD_TYPE_CHECKBOXES", 'checkboxes');
define("FIELD_TYPE_VARCHAR", 'varchar');
define("FIELD_TYPE_BOOL", 'bool');
define("FIELD_TYPE_TIMESTAMP", 'timestamp');


define("FIELD_TYPE", 'type');
define("FIELD_NAME", 'name');
define("FIELD_VALUE", 'value');
define("FIELD_CREATE", 'create');
define("FIELD_EDITSIZE", 'edit');
define("FIELD_LISTSIZE", 'list');
define("FIELD_EDITOR", 'editor');
define("FIELD_VIEWER", 'viewer');
define("FIELD_SAVER", 'saver');

abstract class TableManager {

    abstract protected function createFields();

    abstract protected function createIfNotExists();

    public $fields = array();
    protected $tableName;
    protected $my;
    public $key = '';
    protected $table = array();

    function __construct($tn) {
        global $mysqliLink;
        $this->my = $mysqliLink;
        $this->tableName = $tn;
    }

    protected function addFieldType($name, $type) {
        $this->fields[$name] = array(
            FIELD_TYPE => $type,
            FIELD_NAME => '',
            FIELD_VALUE => '',
            FIELD_EDITSIZE => -1,
            FIELD_LISTSIZE => -1,
            FIELD_CREATE => '',
            FIELD_EDITOR => '',
            FIELD_VIEWER => '',
            FIELD_SAVER => '',
        );
    }

    protected function addFieldCreate($name, $create) {
        if (isset($this->fields[$name])) {
            $this->fields[$name][FIELD_CREATE] = $create;
        }
    }

    public function getFieldEditor($name) {
        return $this->fields[$name][FIELD_EDITOR];
    }

    public function getFieldViewer($name) {
        return $this->fields[$name][FIELD_VIEWER];
    }

    public function getFieldSaver($name) {
        return $this->fields[$name][FIELD_SAVER];
    }

    public function modField($name, $data) {
        if (isset($this->fields[$name])) {
            foreach ($data as $key => $value) {
                $this->fields[$name][$key] = $value;
            }
        }
    }

    public function modFieldValue($name, $value) {
        if (isset($this->fields[$name])) {
            $this->fields[$name][FIELD_VALUE] = $value;
        }
    }

    public function resetFieldValue($name) {
        if (isset($this->fields[$name])) {
            $this->modFieldValue($name, '');
        }
    }

    public function getField($name) {
        if (isset($this->fields[$name]) AND ! empty($this->fields[$name])) {
            return $this->fields[$name];
        } else {
            return array();
        }
    }
    protected function getFieldType($name) {
        if (isset($this->fields[$name])) {
            return $this->fields[$name][FIELD_TYPE];
        } else {
            return '';
        }
    }
    public function getFieldValue($name) {
        if (isset($this->fields[$name])) {
            return $this->fields[$name][FIELD_VALUE];
        } else {
            return '';
        }
    }

    protected function addPrimaryKey($key) {
        $this->key = $key;
    }

    public function getPrimaryKey() {
        return $this->key;
    }

    protected function truncateTable() {
        $sql = 'TRUNCATE `' . $this->tableName . '`;';
        $this->my->query($sql);
    }

    public function addItem($fields) {
        if (empty($fields)) {
            return;
        }
        $sql = 'INSERT INTO `' . $this->tableName . '` (';
        foreach ($fields as $name => $value) {
            $sql .= '`' . $name . '`,';
        }
        $sql = substr($sql, 0, -1); //levagjuk az utolso vesszot
        $sql .= ') VALUES (';
        foreach ($fields as $name => $value) {
            $sql .= $this->getFieldType($name) == FIELD_TYPE_VARCHAR ? '"' : '';
            $sql .= $value;
            $sql .= $this->getFieldType($name) == FIELD_TYPE_VARCHAR ? '",' : ',';
        }
        $sql = substr($sql, 0, -1); //levagjuk az utolso vesszot
        $sql .= ');';
        if ($this->my->query($sql) === TRUE) {
            return $this->my->insert_id;
        } else {
            return -1;
        }
    }

    public function modifyItem($where, $values) {
        $sql = 'UPDATE `' . $this->tableName . '` SET ';
        foreach ($values as $key => $value) {
            $sql .= '`' . $key . '`="' . $value . '",';
        }
        $sql = substr($sql, 0, -1); //levagjuk az utolso vesszot
        $sql .= ' WHERE';
        foreach ($where as $name => $value) {
            $sql .= ' `' . $name . '`=';
            $sql .= $this->getFieldType($name) == FIELD_TYPE_VARCHAR ? '"' : '';
            $sql .= $value;
            $sql .= $this->getFieldType($name) == FIELD_TYPE_VARCHAR ? '" AND' : ' AND';
        }
        $sql = substr($sql, 0, -3); //levagjuk az utolso 3 karaktert
        $sql .= ';';
        $this->my->query($sql);
    }

    protected function modifyItemById($id, $values) {
        if (empty($this->key)) {
            return;
        }
        $this->modifyItem([$this->key => $id], $values);
    }

    public function deleteItem($where) {
        $sql = 'DELETE FROM `' . $this->tableName . '` WHERE  ';
        foreach ($where as $key => $value) {
            $sql .= ' `' . $key . '`="' . $value . '" AND';
        }
        $sql = substr($sql, 0, -3); //levagjuk az utolso 3 karaktert
        $sql .= ';';
        $this->my->query($sql);
    }

    public function deleteItemById($id) {
        $this->deleteItem([$this->key => $id]);
    }

    protected function ifNotExists() {
        if (empty($this->tableName) OR count($this->fields) == 0) {
            return;
        }
        $sql = 'CREATE TABLE IF NOT EXISTS `' . $this->tableName . '` (';
        foreach ($this->fields as $name => $data) {
            $sql .= '`' . $name . '` ' . $data[FIELD_CREATE] . ' ,';
        }
        if (!empty($this->key)) {
            $sql .= ' PRIMARY KEY (`' . $this->key . '`) ';
        } else {
            $sql = substr($sql, 0, -1); //levagjuk az utolso vesszot
        }
        $sql .= ') ENGINE=InnoDB DEFAULT CHARSET=utf8; ';
        $this->my->query($sql);
    }

    public function readTable() {
        $sql = 'SELECT * FROM `' . $this->tableName . '` ';
        $res = $this->my->query($sql);
        $this->table = array();
        while ($res AND $row = $res->fetch_assoc()) {
            $this->table[] = $row;
        }
        return $this->table;
    }

    protected function getItemsBy($fieldName, $fieldValue) {
        $sql = 'SELECT * FROM `' . $this->tableName . '` WHERE `' . $fieldName . '`="' . $fieldValue . '";';
        $res = $this->my->query($sql);
        $ret = array();
        while ($res AND $row = $res->fetch_assoc()) {
            $ret[] = $row;
        }
        return $ret;
    }

    public function getItemById($id) {
        $item = $this->getItemsBy($this->key, $id);
        if (empty($item)) {
            return $item;
        } else {
            return $item[0];
        }
    }

    protected function readTableOrderBy($order) {
        if (!isset($order) OR empty($order)) {
            return;
        }
        $sql = 'SELECT * FROM `' . $this->tableName . '` ORDER BY `' . $order . '` ASC;';
        $res = $this->my->query($sql);
        $this->table = array();
        while ($res AND $row = $res->fetch_assoc()) {
            $this->table[] = $row;
        }
        return $this->table;
    }

}
