<?php

class AuthAccess {

    const ACCESS_NOBODY = 0;
    const ACCESS_USER = 1;
    const ACCESS_ASSISTANT = 2;
    const ACCESS_MAINTAINER = 4;
    const ACCESS_CUSTOMER = 8;
    const ACCESS_ADMIN = 16;
    const ACCESS_FULL = 255;

    static $accessNames = [
        self::ACCESS_NOBODY => 'Bárki',
        self::ACCESS_USER => 'Regisztrált',
        self::ACCESS_ASSISTANT => 'Ügyintéző',
        self::ACCESS_MAINTAINER => 'Karbantartó',
        self::ACCESS_CUSTOMER => 'Ügyfél',
        self::ACCESS_ADMIN => 'Adminisztrátor',
        self::ACCESS_FULL => 'Teljes',
    ];

    public function getName($access) {
        return $this->accessName[$access];
    }

}
