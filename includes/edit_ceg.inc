<?php

if (isset($ceg_id) AND $ceg_id > 0) {
    $eredm = $mysqliLink->query(SQL_QUERY . $ceg_id);
    if ($eredm AND $rekord = $eredm->fetch_assoc()) {
        $ceg_cegnev = $rekord[RECORD_CEGNEV];
        $ceg_buildingId = $rekord[RECORD_BUILDINGID];
        $ceg_ownerId = $rekord[RECORD_OWNERID];
        $ceg_szoba = $rekord[RECORD_SZOBA];
        $ceg_tevekenyseg = $rekord[RECORD_TEVEKENYSEG];
        $ceg_vezeto = $rekord[RECORD_VEZETO];
        $ceg_telefon = $rekord[RECORD_TELEFON];
        $ceg_email = $rekord[RECORD_EMAIL];
        $ceg_honlap = $rekord[RECORD_HONLAP];
        $ceg_comment = $rekord[RECORD_COMMENT];
        $ceg_parkolo = $rekord[RECORD_PARKOLO];
        $ceg_start = $rekord[RECORD_START];
        $ceg_stop = $rekord[RECORD_STOP];
        $ceg_posta = $rekord[RECORD_POSTA];
    } else {
        $ceg_id = -1;
    }
} else {
    $ceg_id = -1;
}
if ($ceg_id < 0) {
    $ceg_cegnev = '';
    $ceg_buildingId = -1;
    $ceg_ownerId = -1;
    $ceg_szoba = '';
    $ceg_tevekenyseg = '';
    $ceg_vezeto = '';
    $ceg_telefon = '';
    $ceg_email = '';
    $ceg_honlap = '';
    $ceg_comment = '';
    $ceg_parkolo = '';
    $ceg_posta = '';
    $ceg_start = date('Y-m-d');
    $ceg_stop = date('Y-m-d', strtotime('+20 year'));
    $ceg_id = 0;
}
$output .= '<div class="keret editor">';
$output .= ' <form method="post">';
$output .= ' <table  width="100%" border="0" cellspacing="1" cellpadding="1">';
$output .= '     <tr>';
$output .= '         <td><div align="right">Cégnév: </div></td>';
$output .= '         <td><input type="text" size="30" maxlength="254" name="ceg_cegnev" id="ceg_cegnev" value="' . $ceg_cegnev . '" >' . (empty($hiba['cegnev']) ? "" : $hiba['cegnev']) . '</td>';
$output .= '     </tr>';
$output .= '     <tr>';
$output .= '         <td><div align="right">Bérbeadó: </div></td>';
$output .= '         <td width="100%"><select  name="ceg_ownerId" >';

foreach ($owners as $id => $tulaj) {
    $output .= '<option value="' . $id . '"';
    if ($id == $ceg_ownerId) {
        $output .= ' selected';
    }
    $output .= '>' . $tulaj . '</option>';
}

$output .= '             </select>' . (empty($hiba['tulajdonos']) ? "" : $hiba['tulajdonos']);
$output .= '         </td>';
$output .= '     </tr>';
$output .= '     <tr>';
$output .= '	       <td><div align="right">Épület: </div></td>';
$output .= '         <td width="100%"><select name="ceg_buildingId" >';

foreach ($buildings as $id => $hely) {
    $output .= '<option value="' . $id . '"';
    if ($ceg_buildingId == $id) {
        $output .= ' selected';
    }
    $output .= '>' . $hely . '</option>';
}

$output .= '             </select>' . (empty($hiba['epulet']) ? "" : $hiba['epulet']);
$output .= '         </td>';
$output .= '     </tr>';
$output .= '     <tr>';
$output .= '         <td><div align="right">Szoba: </div></td>';
$output .= '         <td><input type="text" size="30" maxlength="15" name="ceg_szoba" id="ceg_szoba" value="' . $ceg_szoba . '"></td>';
$output .= '     </tr>';
$output .= '     <tr>';
$output .= '         <td><div align="right">Tevékenység: </div></td>';
$output .= '         <td><input type="text" size="30" maxlength="126" name="ceg_tevekenyseg" id="ceg_tevekenyseg" value="' . $ceg_tevekenyseg . '"></td>';
$output .= '     </tr>';
$output .= '     <tr>';
$output .= '         <td><div align="right">Képviselő: </div></td>';
$output .= '         <td><input type="text" size="30" maxlength="254" name="ceg_vezeto" id="ceg_vezeto" value="' . $ceg_vezeto . '"></td>';
$output .= '     </tr>';
$output .= '     <tr>';
$output .= '         <td><div align="right">Telefonszám: </div></td>';
$output .= '         <td><input type="text" size="30" maxlength="254" name="ceg_telefon" id="ceg_telefon" value="' . $ceg_telefon . '"></td>';
$output .= '     </tr>';
$output .= '     <tr>';
$output .= '         <td><div align="right">Email: </div></td>';
$output .= '         <td><input type="email" size="30" maxlength="254" name="ceg_email" id="ceg_email" value="' . $ceg_email . '"></td>';
$output .= '     </tr>';
$output .= '     <tr>';
$output .= '         <td><div align="right">Honlap: </div></td>';
$output .= '         <td><input type="text" size="30" maxlength="30" name="ceg_honlap" id="ceg_honlap" value="' . $ceg_honlap . '"></td>';
$output .= '     </tr>';
$output .= '     <tr>';
$output .= '         <td><div align="right">Megjegyzés: </div></td>';
$output .= '         <td><input type="text" size="30" maxlength="254" name="ceg_comment" id="ceg_comment" value="' . $ceg_comment . '"></td>';
$output .= '     </tr>';
$output .= '     <tr>';
$output .= '         <td><div align="right">Parkoló: </div></td>';
$output .= '         <td><input type="text" size="30" maxlength="30" name="ceg_parkolo" id="ceg_parkolo" value="' . $ceg_parkolo . '"></td>';
$output .= '     </tr>';
$output .= '     <tr><td <div align="left">Bérlet</td><td></td></tr>';
$output .= '     <tr>';
$output .= '         <td><div align="right">Kezdete: </div></td>';
$output .= '         <td><label>' . $ceg_start . '</label></td>';
$output .= '     </tr>';
$output .= '     <tr>';
$output .= '         <td><div align="right">Vége: </div></td>';
$output .= '         <td><label>' . $ceg_stop . '</label></td>';
$output .= '     </tr>';
$output .= '     <tr>';
$output .= '         <td><div align="right">Posta: </div></td>';
$output .= '         <td><input type="checkbox" name="ceg_posta" id="ceg_posta"  value="POSTA"';
if ($ceg_posta == "POSTA") {
    $output .= ' checked';
}
$output .= '></td>';
$output .= '    </tr>';
$output .= '     <tr></tr><tr>';
$output .= '         <td></td><td align="left"></td>';
$output .= '     </tr>';
$output .= '  </table>';
$output .= '  <input type="hidden" name="ceg_id" value="' . $ceg_id . '">';
$output .= '  <input type="hidden" name="ceg_start" value="' . $ceg_start . '">';
$output .= '  <input type="hidden" name="ceg_stop" value="' . $ceg_stop . '">';
$output .= '<input type="submit" name="ceg_felvesz" 
                    value="' . ($ceg_id == 0 ? 'Cég felvitele' : 'Cég módosítása') . '" >&nbsp;&nbsp;&nbsp;&nbsp;'
        . '<input type="submit"  name="ceg_edit_return" value="Vissza">';
$output .= '  </form></div>';

