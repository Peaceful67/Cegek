<?php

$sql = 'CREATE TABLE IF NOT EXISTS `' . IP_ADDR_TABLE
        . '` (`' . IP_ADDR_ID . '` int(8) NOT NULL AUTO_INCREMENT,'
        . '`' . IP_ADDR_INTERNET_ID . '` int(16) NOT NULL,'
        . '`' . IP_ADDR_IP_C . '` int(3) NOT NULL,'
        . '`' . IP_ADDR_IP_D . '` int(3) NOT NULL,'
        . '`' . IP_ADDR_ACTIVE . '` tinyint(1) NOT NULL,'
        . '`' . IP_ADDR_NETMASK . '` int(3) NOT NULL,'
        . '`' . IP_ADDR_GW . '` int(3) NOT NULL,'
        . 'PRIMARY KEY (`id`), UNIQUE KEY `id` (`id`)'
        . ') ENGINE=InnoDB DEFAULT CHARSET=latin1; COMMIT;';

$res = $mysqliLink->query($sql);

$sql = 'SELECT * FROM `' . IP_ADDR_TABLE . '`;';

$res = $mysqliLink->query($sql);
if ($res and $res->num_rows == 0) {

    foreach ($ipaddresses as $ip) {
        $sql = 'INSERT INTO `' . IP_ADDR_TABLE . '`'
                . '(`' . IP_ADDR_INTERNET_ID . '`,`' . IP_ADDR_IP_C . '`,`'
                . IP_ADDR_IP_D . '`,`' . IP_ADDR_ACTIVE . '`,`' . IP_ADDR_NETMASK . '`,`' . IP_ADDR_GW
                . '`)'
                . ' VALUES (0, ' . $ip[2] . ', ' . $ip[3] . ', 0, '
                . $ip[4] . ', ' . $ip[5] . ');';

        $mysqliLink->query($sql);

    }
    $mysqliLink->query('COMMIT;');
}