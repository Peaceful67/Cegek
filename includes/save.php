<?php
    $backup_filename = '/web/www/cegek_'.date('Y-m-d_H_i_s', time()).'.sql';
    exec("/usr/bin/mysqldump -umysql -pCsaCsi dokumentaciok doksik kepek > ".$backup_filename);
    error_log('Az adatbázis mentése '.$backup_filename.' fájlba megtörtént.');
?>