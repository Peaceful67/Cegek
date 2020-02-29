<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of ArpStatus
 *
 * @author Peaceful
 */
class ArpStatus {

    protected $ipStatusArray;

    function __construct() {
        global $mysqliLink;
        $this->ipStatusArray = array();
        $sql = 'SELECT * FROM `' . OPTIONS_TABLE . '` WHERE `' . OPTIONS_NAME . '` '
                . 'LIKE "' . OPTIONS_NAME_ARP_STATUS_ . '%" ;';
        $res = $mysqliLink->query($sql);
        while ($res AND $row = $res->fetch_assoc()) {
            $this->ipStatusArray[$row[OPTIONS_NAME]] = $row[OPTIONS_VALUE];
        }
    }

    function setStatus($ip, $status) {
        global $mysqliLink;
        $optionName = OPTIONS_NAME_ARP_STATUS_ . $ip;
        $statusEsc = $mysqliLink->real_escape_string($status);
        if (isset($this->ipStatusArray[$optionName])) {
            $sql = 'UPDATE `' . OPTIONS_TABLE . '` SET `' . OPTIONS_VALUE . '`="' . $statusEsc . '" '
                    . 'WHERE `' . OPTIONS_NAME . '`="' . $optionName . '" ;';
        } else {
            $sql = 'INSERT INTO `' . OPTIONS_TABLE . '` '
                    . '(`' . OPTIONS_NAME . '`, `' . OPTIONS_VALUE . '`)'
                    . ' VALUES ("' . $optionName . '", "' . $statusEsc . '");';
        }
        $this->ipStatusArray[$optionName] = $status;
        $mysqliLink->query($sql);
    }

    function getStatus($ip) {
        $optionName = OPTIONS_NAME_ARP_STATUS_ . $ip;
        if (isset($this->ipStatusArray[$optionName])) {
            return $this->ipStatusArray[$optionName];
        } else {
            serialize(array());
        }
    }

    function getVisible($ip) {
        $stat = unserialize($this->getStatus($ip));
        return isset($stat[OPTIONS_ARP_STATUS]) ? $stat[OPTIONS_ARP_STATUS]: 0;
    }
    function getCegnev($ip) {
        $stat = unserialize($this->getStatus($ip));
        return isset($stat[OPTIONS_ARP_CEGNEV]) ? $stat[OPTIONS_ARP_CEGNEV]: '';
    }

    function getComment($ip) {
        $stat = unserialize($this->getStatus($ip));
        return isset($stat[OPTIONS_ARP_COMMENT]) ? $stat[OPTIONS_ARP_COMMENT]:'';
    }

    function isVisible($ip) {
        return $this->getVisible($ip) == 1 ? true : false;
    }

    function getUser($ip) {
        $stat = unserialize($this->getStatus($ip));
        $ret = '';
        if (!empty($stat[OPTIONS_ARP_CEGNEV])) {
            $ret .= $stat[OPTIONS_ARP_CEGNEV];
        }
        if (!empty($stat[OPTIONS_ARP_COMMENT])) {
            $ret .= '&nbsp;&nbsp;(' . $stat[OPTIONS_ARP_COMMENT] . ')';
        }
        return $ret;
    }

}
