<?php

require_once 'vendor/autoload.php';

$ip_addr = getIpAddrByInternetId($internet_print);
$ceg = getCegByInternetId($internet_print);
if (empty($ip_addr) OR empty($ceg)) {
    warning('Hibás tétel, nem nyomtatható !');
    theEnd($output);
}
$cegname = $ceg[RECORD_CEGNEV];
$stylesheet = file_get_contents(DESIGN . 'print.css');

$body = '<body>';
$body .= '<h1 align=center style="text-align:center"><b>IP
beállítási adatlap</b></h1>';
$body .= '<table class="keretes">';
$body .= '<tr><th>Cégnév: </th><th>' . $cegname . '</th>></tr>';
$body .= '<tr><td>IP cím:</td><td>' . IP_ADDR_IP_A . '.' . IP_ADDR_IP_B . '.' . $ip_addr[IP_ADDR_IP_C] . '.' . $ip_addr[IP_ADDR_IP_D] . '</td></tr>';
$body .= '<tr><td>Alhálózati maszk:</td><td>255.255.255.' . $ip_addr[IP_ADDR_NETMASK] . '</td></tr>';
$body .= '<tr><td>Átjáró:</td><td>' . IP_ADDR_IP_A . '.' . IP_ADDR_IP_B . '.' . $ip_addr[IP_ADDR_IP_C] . '.' . $ip_addr[IP_ADDR_GW] . '</td></tr>';
$body .= '<tr><td>DNS 1:</td><td>' . $dns1[0] . '.' . $dns1[1] . '.' . $dns1[2] . '.' . $dns1[3] . '</td></tr>';
$body .= '<tr><td>DNS 2:</td><td>' . $dns2[0] . '.' . $dns2[1] . '.' . $dns2[2] . '.' . $dns2[3] . '</td></tr>';
$body .= '<tr><td>SMTP, kimenő szerver</td><td>mail.emg.hu</td></tr>';
$body .= '</table>';
$body .= '<h2>Ügyintézés, hibabejelentés:</h2>';
$body .= '<ul style="list-style-type:square;">';
$body .= '<li>internet@emg.hu</li>';
$body .= '<li>Baksa Zsolt: 30-9507985</li>';
$body .= '<li>Iroda: 403-5094</li>';
$body .= '</ul>';
$body .= '<h2>Telekom adatok:</h2>';
$body .= '<ul style="list-style-type:square;">';
$body .= '<li>Vonali azonosító: GTSEMGT11AA</li>';
$body .= '<li>SAP végpont: 9000435405</li>';
$body .= '<li>MT ügyfél azonosító: 493393213</li>';
$body .= '</ul>';
$body .= '<h2>Telekom hibabejelentés:</h2>';
$body .= '<ul style="list-style-type:square;">';
$body .= '<li>80-466111</li>';
$body .= '<li>Áramköri azonosító: SG 160444</li>';
$body .= '<li>noc.kiemelt@telekom.hu</li>';
$body .= '</ul>';


$body .= '</body>';


$pdf = new \Mpdf\Mpdf(
        array(
    'tempDir' => TEMPDIR,
    'mode' => '+aCJK',
    'margin_left' => 10,
    'margin_right' => 10,
    'margin_top' => 10,
    'margin_bottom' => 10,
    'margin_header' => 10,
    'margin_footer' => 10
        )
);
$pdf->img_dpi = $pdf->dpi = 300;
$pdf->nonPrintMargin = '0';
$pdf->WriteHTML($stylesheet, 1);
$pdf->WriteHTML($body);
$pdf->Output('IP_' . $cegname . '_' . date("Y-m-d_H-i-s") . '.pdf', 'D');
