<?php

include_once 'settings.inc';


$header = '<?xml version="1.0" encoding="utf-8"?>';
$start_tag = '<cegek>';
$end_tag = '</cegek>';
$data_tag = "";
$error = '0';
$ceg_counter = 0;
$body = '';
if(isset($_GET['code'])) {
    $code = $_GET['code'];
} else {
    $code = '';
}
if(isset($_GET['download'])) {
    $download = $_GET['download'];
} else {
    $download = 0;
}
$download = 1;
$code = $current_code;

$eredm=$mysqliLink->query("SELECT * FROM `".CEGEK_TABLE."` WHERE 1") ;
while ($rekord  = $eredm->fetch_assoc()) {
    $ceg_counter++;
    $body .= "<ceg ";
    $body .= RECORD_ID.'="'.$rekord[RECORD_ID].'" ';        
    $body .= RECORD_CEGNEV.'="'.$rekord[RECORD_CEGNEV].'" ';        
    $body .= RECORD_OWNER.'="'.$owners[$rekord[RECORD_OWNERID]].'" ';        
    $body .= RECORD_BUILDING.'="'.$buildings[$rekord[RECORD_BUILDINGID]].'" ';        
    $body .= RECORD_AKTIV.'="'.$rekord[RECORD_AKTIV].'" ';        
    if ($rekord[RECORD_SZOBA])    $body .= RECORD_SZOBA.'="'.$rekord[RECORD_SZOBA].'" ';        
    if ($rekord[RECORD_TEVEKENYSEG])    $body .= RECORD_TEVEKENYSEG.'="'.$rekord[RECORD_TEVEKENYSEG].'" ';        
    if ($rekord[RECORD_EMAIL])    $body .= RECORD_EMAIL.'="'.$rekord[RECORD_EMAIL].'" ';        
    if ($rekord[RECORD_HONLAP])    $body .= RECORD_HONLAP.'="'.$rekord[RECORD_HONLAP].'" ';        
    if(isset($code) && ($code == $current_code)) {
        if ($rekord[RECORD_VEZETO])    $body .= RECORD_VEZETO.'="'.$rekord[RECORD_VEZETO].'" ';        
        if ($rekord[RECORD_TELEFON])    $body .= RECORD_TELEFON.'="'.$rekord[RECORD_TELEFON].'" ';        
        if ($rekord[RECORD_PARKOLO])    $body .= RECORD_PARKOLO.'="'.$rekord[RECORD_PARKOLO].'" ';        
    } else {
        $error ='2';
    }
    $body .= " />\n";   
}
$mysqliLink->close();


    

$data_tag= '<data lenght= "'.  strlen($body).'" error="'.$error.'" ceg_counter="'.$ceg_counter.'" building_counter="'
        .$building_counter.'" owner_counter="'.$owner_counter.'" code="'.$code.'"/>';
echo $header.$start_tag.$data_tag.$body.$end_tag;
/*
if(isset($download) && $download==1) {
    echo $body;

}
echo $end_tag;   
*/

?>