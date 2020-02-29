<?php

require_once 'vendor/autoload.php';

$stylesheet = file_get_contents(DESIGN . 'print.css');

$sql = "SELECT * FROM `" . CEGEK_TABLE . "` WHERE `act`=1 ORDER BY `" . RECORD_CEGNEV . "`";
$res = $mysqliLink->query($sql);
$body = '<h3>Az EMG-ben talaláható cégek listája (' . $today . ')</h3>';
while ($res AND ( $rekord = $res->fetch_assoc())) {
    $body .= '(' . $rekord[RECORD_ID] . ') ';
    $body .= '<b>' . $rekord[RECORD_CEGNEV] . '</b>, ';
    $body .= $buildings[$rekord[RECORD_BUILDINGID]] . ' ' . $rekord[RECORD_SZOBA] . ', ';
    $body .= $owners[$rekord[RECORD_OWNERID]];
    if (isset($rekord[RECORD_TEVEKENYSEG]) AND ! empty($rekord[RECORD_TEVEKENYSEG])) {
        $body .= ', ' . $rekord[RECORD_TEVEKENYSEG];
    }
    if (isset($rekord[RECORD_VEZETO]) AND ! empty($rekord[RECORD_VEZETO])) {
        $body .= ', ' . $rekord[RECORD_VEZETO];
    }
    if (isset($rekord[RECORD_TELEFON]) AND ! empty($rekord[RECORD_TELEFON])) {
        $body .= ', ' . $rekord[RECORD_TELEFON];
    }
    if (isset($rekord[RECORD_EMAIL]) AND ! empty($rekord[RECORD_EMAIL])) {
        $body .= ', ' . $rekord[RECORD_EMAIL];
    }
    if (isset($rekord[RECORD_HONLAP]) AND ! empty($rekord[RECORD_HONLAP])) {
        $body .= ', ' . $rekord[RECORD_HONLAP];
    }
    if (isset($rekord[RECORD_COMMENT]) AND ! empty($rekord[RECORD_COMMENT])) {
        $body .= ', ' . $rekord[RECORD_COMMENT];
    }

    $body .= '<hr>';
}
$body .= '</body>';


$pdf = new \Mpdf\Mpdf(
        array(
    'tempDir' => TEMPDIR,
    'mode' => '+aCJK',
    'margin_left' => 20,
    'margin_right' => 20,
    'margin_top' => 20,
    'margin_bottom' => 20,
    'margin_header' => 20,
    'margin_footer' => 20
        )
);
$pdf->img_dpi = $pdf->dpi = 300;
$pdf->nonPrintMargin = '0';
$pdf->WriteHTML($stylesheet, 1);
$pdf->WriteHTML($body);
$pdf->Output('Céglista_' . date("Y-m-d_H-i-s") . '.pdf', 'D');



