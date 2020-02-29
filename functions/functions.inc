<?php

function isLogedIn() {
    global $_COOKIE;
    global $secret;
    global $passwd;
    global $now;

    if (isset($_COOKIE[COOKIE_PASS]) AND ( $_COOKIE[COOKIE_PASS] == md5($passwd . $secret))) {
        $pass = $_COOKIE[COOKIE_PASS];
//        error_log('Pass: ' . $pass);
        setcookie(COOKIE_PASS, $pass, $now + TIME_REMEMBER_ME);
        return true;
    } else {
//        error_log('Cookie: ' . $_COOKIE[COOKIE_PASS]);
        return false;
    }
}

function getVariable($var_name, $default_value='') {
    global $$var_name;
    if (isset($$var_name)) {
        $_SESSION[$var_name] = $$var_name;
    } elseif (isset($_SESSION[$var_name])) {
        $$var_name = $_SESSION[$var_name];
    } else {
        $$var_name = $default_value;
    }
    return $$var_name;
}

function resetVariable($var_name) {
    global $$var_name;
    unset($$var_name);
    unset($_SESSION[$var_name]);
}

function theEnd($output) {
    global $mysqliLink;
    header("Content-type:text/html; charset=UTF-8;");
    echo $output;
    $mysqliLink->close();
    exit(0);
}

function getCegById($ceg_id) {
    global $mysqliLink;
    $sql = 'SELECT * FROM `' . CEGEK_TABLE . '` WHERE `' . RECORD_ID . '`=' . $ceg_id . ' LIMIT 1;';
    $res = $mysqliLink->query($sql);
    if ($res AND $row = $res->fetch_assoc()) {
        return $row;
    } else {
        return array();
    }
}

function getCegNameById($ceg_id) {
    $ceg = getCegById($ceg_id);
    if (empty($ceg)) {
        return '---';
    } else {
        return $ceg[RECORD_CEGNEV];
    }
}

function getActCegList() {
    global $mysqliLink;
    $ret = array();
    $sql = 'SELECT * FROM `' . CEGEK_TABLE . '` WHERE `' . RECORD_AKTIV . '`=1 ORDER BY `' . RECORD_CEGNEV . '`;';
    $res = $mysqliLink->query($sql);
    while ($res AND $row = $res->fetch_assoc()) {
        $ret[] = $row;
    }
    return $ret;
}

function warning($msg) {
    global $output;
    $output .= '<div class="warning">  ' . $msg . '</div><br><br>';
}

function logger($mem_id, $field, $category, $comment) {
    global $mysqliLink;
    $sql = 'INSERT INTO `' . LOGGER_TABLE . '` ('
            . '`' . LOGGER_OPERATOR . '`, `' . LOGGER_FIELD . '`, `' . LOGGER_CATEGORY . '`, `' . LOGGER_COMMENT . '`) '
            . ' VALUES '
            . '(' . $mem_id . ', ' . $field . ', ' . $category . ', "' . $comment . '");';
    $mysqliLink->query($sql);
    $sql = 'DELETE FROM `' . LOGGER_TABLE . '` WHERE `' . LOGGER_TIMESTAMP . '` < DATE_SUB(NOW(), INTERVAL 2 YEAR);';
    $mysqliLink->query($sql);
}
