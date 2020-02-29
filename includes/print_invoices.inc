<?php

require_once 'vendor/autoload.php';

$stylesheet = file_get_contents(DESIGN.'print.css');
$body = '<body>';
$sql = 'SELECT `' . INTERNET_TABLE . '`.* FROM `' . INTERNET_TABLE . '`, `' . CEGEK_TABLE . '` WHERE '
        . 'CURRENT_DATE BETWEEN `' . INTERNET_DATE_FROM . '` AND `' . INTERNET_DATE_TO . '` '
        . ' AND (`' . CEGEK_TABLE . '`.`' . RECORD_ID . '`=`' . INTERNET_TABLE . '`.`' . INTERNET_CEG_ID . '`'
        . ' OR -1=`' . INTERNET_TABLE . '`.`' . INTERNET_CEG_ID . '`)'
        . ' GROUP BY `' . INTERNET_TABLE . '`.`' . INTERNET_ID . '` '
        . ' ORDER BY `' . CEGEK_TABLE . '`.`' . RECORD_CEGNEV . '` ';


$szamlazando = array();
$total_num = $total_sum = 0;
$res = $mysqliLink->query($sql);
while ($res AND ( $row = $res->fetch_assoc())) {
    $ceg_id = $row[INTERNET_CEG_ID];
    if(-1==$ceg_id) {
        continue;
    }
    if (isset($szamlazando[$ceg_id])) {
        $szamlazando[$ceg_id] += getOptionValue(OPTIONS_NAME_PRICE_MORE);
    } else {
        $szamlazando[$ceg_id] = getOptionValue(OPTIONS_NAME_PRICE_FIRST);
    }
    $szamlazando[$ceg_id] -= $row[INTERNET_DISCOUNT];
}

$body .= '<h2>Számlázandó tételek:</h2>';
$body .= '<table class="keretes">';
$body .='<tr><th>Cégnév</th><th>Összeg</th></tr>';
foreach ($szamlazando as $ceg_id => $sum) {
    $total_num++;
    $total_sum += $sum;
    $body .= '<tr><td>'.getCegNameById($ceg_id).':</td><td>'.$sum.' Ft</td></tr>';    
}
$body.='</table>';
$body .= '</body>';


$pdf = new \Mpdf\Mpdf(
        array(
    'tempDir' => TEMPDIR,
    'mode' => '+aCJK',
    'margin_left' => 20,
    'margin_right' => 20,
    'margin_top' => 20,
    'margin_bottom' => 1,
    'margin_header' => 20,
    'margin_footer' => 1
        )
);
$pdf->img_dpi = $pdf->dpi = 300;
$pdf->nonPrintMargin = '0';
$pdf->WriteHTML($stylesheet, 1);
$pdf->WriteHTML($body);
$pdf->Output('Számlázandó_' . date("Y-m-d_H-i-s") . '.pdf', 'D');

logger($mem_id, 0, LOGGER_CAT_PRINT_INVOICE, $total_num.' db cégnek összesen '.$total_sum.' Ft összeg számlázandó');