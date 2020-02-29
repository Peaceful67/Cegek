<?php

include_once HELPERS . 'authAccess.inc';

class AuthUser extends User {

    const PASSWD_SECRET = '?787yYR$';
    const TIME_REMEMBER_ME = 7 * 24 * 60 * 60;
    const COOKIE_PASS = 'cegek_pass';
    const COOKIE_USER = 'cegek_user';

    public function isLoggedIn() {
        if (isset($_COOKIE[self::COOKIE_USER]) AND isset($_COOKIE[self::COOKIE_PASS])) {
            $this->userId = $_COOKIE[self::COOKIE_USER];
            $item = $this->getItemById($this->userId);
            $crypted = $_COOKIE[self::COOKIE_USER];
            if ($item[DB_AUTH_USER_PASSWORD] == $crypted) {
                setcookie(self::COOKIE_PASS, $crypted, $now + self::TIME_REMEMBER_ME);
                setcookie(self::COOKIE_USER, $this->userId, $now + self::TIME_REMEMBER_ME);
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public function logOut() {
        global $now;
        setcookie(self::COOKIE_PASS, '', $now - 3600);
        setcookie(self::COOKIE_USER, '', $now - 3600);
    }

    public function logIn($passwd) {
        global $now;
        $crypted = $this->cryptPasswd($passwd);
        setcookie(self::COOKIE_PASS, $crypted, $now + self::TIME_REMEMBER_ME);
        setcookie(self::COOKIE_USER, $this->userId, $now + self::TIME_REMEMBER_ME);
    }

    public function setPasswd($passwd) {
        $id = $this->userId;
        $crypted = $this->cryptPasswd($passwd);
        $this->modifyItemById($id, [DB_AUTH_USER_PASSWORD => $crypted]);
    }

    public function isPasswdOK($passwd) {
        $crypted = $this->cryptPasswd($passwd);
        $item = $this->getItemById($this->userId);
        if (isset($item[DB_AUTH_USER_PASSWORD]) AND $item[DB_AUTH_USER_PASSWORD] == $crypted) {
            return true;
        } else {
            return false;
        }
    }

    function cryptPasswd($passwd) {
        return md5($passwd . self::PASSWD_SECRET);
    }

    public function setUserId($mem_id) {
        $this->userId = $mem_id;
        return true;
    }

    public function getUserId() {
        return $this->userId;
    }

    protected function getPermissionOfUser($mem_id) {
//        return AuthAccess::ACCESS_FULL;
        $users = parent::readTable();
        if (empty($users)) {
            return AuthAccess::ACCESS_FULL;
        }
        $user = $this->getItemById($mem_id);
        if ($mem_id < 0 OR empty($user)) {
            return AuthAccess::ACCESS_NOBODY;
        }
        return $user[DB_AUTH_USER_PERMISSION];
    }

    public function getPermission() {
        return $this->getPermissionOfUser($this->userId);
    }

}
