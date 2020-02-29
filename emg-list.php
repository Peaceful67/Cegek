<?php

include_once 'settings.inc';

$output = '<!doctype html>
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
	</head>
	<body>';

$eredm = $mysqliLink->query(SQL_QUERY_ACT_BY_CEGNEV) or die("Nem sikerült a lekérdezés, mysql hibaüzenet:");
$output .= '<link type="text/css" href="'.DESIGN.'emglista.css" rel="stylesheet">';
$output .= '<table width="100%" cellspacing="0" cellpadding="0" >';
$output .= '<tr><td><img src="images/t1tl.gif" class="cim" alt=""></td><td class="topic_t" ></td>';
$output .= '<td><img src="images/t1tr.gif" class="cim" alt=""></td></tr>';
while ($rekord = $eredm->fetch_assoc()) {
    $output .= '<tr><td class="topic_l"><img src="images/t1l.gif" class="clr" alt=""></td>';
    $output .= '<td height="80" valign="bottom" class="topic_bg"><b>' . $rekord[RECORD_CEGNEV] . '</b><br>';
    if ($rekord[RECORD_TEVEKENYSEG])
        $output .= $rekord[RECORD_TEVEKENYSEG] . '<br>';
    if ($rekord[RECORD_HONLAP])
        $output .= 'Honlap: <a target="_blank" href="http://' . $rekord[RECORD_HONLAP] . '">' . $rekord[RECORD_HONLAP] . ' </a>, ';
//   if ($rekord[RECORD_EMAIL])
//        $output .= 'Email: ' . str_replace("@", "(kukac)", $rekord[RECORD_EMAIL]) . ', ';
    if ($rekord[RECORD_BUILDINGID])
        $output .= 'Elhelyezkedés: ' . $buildings[$rekord[RECORD_BUILDINGID]] . ',  ';
    if ($rekord[RECORD_SZOBA])
        $output .= $rekord[RECORD_SZOBA];
    $output .= '</td>';
    $output .= '<td align="right" class="topic_r"><img src="images/t1r.gif" class="clr"  alt=""></td></tr>';
}
$output .= '<tr><td><img src="images/t1bl.gif" class="cim" alt=""></td><td class="topic_b"></td>';
$output .= '<td><img src="images/t1br.gif" class="cim" alt=""></td></tr></table>';
$output .= '    </body>
            </html>';
theEnd($output);
?>
