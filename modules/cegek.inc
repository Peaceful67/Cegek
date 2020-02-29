<?php

if (!isset($cegek_mod)) {
    $cegek_mod = "list";
}
if (!isset($detailed)) {
    $detailed = "-1";
}
if (!isset($aktiv)) {
    $aktiv = "aktiv";
}
if (isset($aktiv_all)) {
    $aktiv = "minden";
}
if (isset($aktiv_act)) {
    $aktiv = "aktiv";
}

if (!isset($sort)) {
    $sort = "cegnev";
}
if (isset($sort_id)) {
    $sort = 'id';
}
if (isset($sort_name)) {
    $sort = 'cegnev';
}
if (isset($sort_build)) {
    $sort = 'epulet';
}
if (isset($sort_owner)) {
    $sort = 'tulaj';
}

if (!isset($search_ceg)) {
    $search_ceg = '';
}

if (isset($ceg_edit)) {
    $ceg_id = $ceg_edit;
    $cegek_mod = 'edit';
    include_once INCLUDES . 'edit_ceg.inc';
    return;
}




switch ($sort) {
    case "tulaj":
        $sql = "SELECT `" . CEGEK_TABLE . "`.*, 
            (SELECT name FROM owners WHERE cegek.ownerId=owners.id) AS ownerName 
            FROM `" . CEGEK_TABLE . "` WHERE"
                . (($aktiv == 'aktiv') ? ' `act`=1' : '`act`!=2')
                . ' AND ' . ((strlen($search_ceg) > 2) ?
                ('( CONCAT (`' . CEGEK_TABLE . '`.`' . RECORD_CEGNEV . '`, " ", `'
                . CEGEK_TABLE . '`.`' . RECORD_VEZETO . '`)' . ' LIKE "%' . $search_ceg . '%" )') : '1')
                . " ORDER BY ownerName";
        break;
    case "epulet":
        $sql = "SELECT `" . CEGEK_TABLE . "`.*, 
            (SELECT name FROM buildings WHERE cegek.buildingId=buildings.id) AS buildingName 
            FROM `" . CEGEK_TABLE . "` WHERE "
                . (($aktiv == 'aktiv') ? '`act`=1' : '`act`!=2')
                . ' AND ' . ((strlen($search_ceg) > 2) ?
                ('( CONCAT (`' . CEGEK_TABLE . '`.`' . RECORD_CEGNEV . '`, " ", `'
                . CEGEK_TABLE . '`.`' . RECORD_VEZETO . '`)' . ' LIKE "%' . $search_ceg . '%" )') : '1')
                . " ORDER BY buildingName";
        break;
    case "id":
        $sql = "SELECT * "
                . "FROM `" . CEGEK_TABLE . "` WHERE "
                . (($aktiv == 'aktiv') ? ' `act`=1' : '`act`!=2') . " "
                . ' AND ' . ((strlen($search_ceg) > 2) ?
                ('( CONCAT (`' . CEGEK_TABLE . '`.`' . RECORD_CEGNEV . '`, " ", `'
                . CEGEK_TABLE . '`.`' . RECORD_VEZETO . '`)' . ' LIKE "%' . $search_ceg . '%" )') : '1')
                . " ORDER BY `id`";
        break;
    case "cegnev":
    default:
        $sql = "SELECT * "
                . "FROM `" . CEGEK_TABLE . "` WHERE "
                . (($aktiv == 'aktiv') ? ' `act`=1' : '`act`!=2 ')
                . ' AND ' . ((strlen($search_ceg) > 2) ?
                '( CONCAT (`' . CEGEK_TABLE . '`.`' . RECORD_CEGNEV . '`, " ", `'
                . CEGEK_TABLE . '`.`' . RECORD_VEZETO . '`)' . ' LIKE "%' . $search_ceg . '%" )' : '1')
                . " ORDER BY `cegnev`";
        break;
}


switch ($cegek_mod) {
    case 'print':
        include_once INCLUDES . 'print_cegek.inc';
        exit(0);
    case 'delete':
        $sql = "SELECT  * FROM `cegek` ORDER BY id DESC";
        break;
    case 'add':
        $ceg_id = 0;
    case 'edit':
        include_once INCLUDES . 'edit_ceg.inc';
        return;
    case 'list':
    default:
        break;
}


$output .= '<button name="cegek_mod" value="add" title="új tétel felvétele"><img  src="' . IMAGES . 'add.jpg"></button>
    <button name="cegek_mod" value="delete" title="Egy tétel törlése" onClick="alert(\'Tudd mit csinálsz, mert innen nincs visszaút !\')">
    <img  src="' . IMAGES . 'delete.jpg"></button>&nbsp;&nbsp;&nbsp;';
$output .= '<button name="cegek_mod" value="print"><img src="' . IMAGES . 'print.jpg"></button>&nbsp;&nbsp;&nbsp;';
$output .= 'Szűrés: <input  onChange="submit();" type="text" name="search_ceg" value="' . $search_ceg . '">';
$output .= '<br><br>';
$output .= 'Rendezés: <button ' . (($sort == "id") ? ' class="selected_button" ' : '') . 'name="sort_id" value="id" >Sorszám</button>&nbsp;&nbsp;&nbsp;';
$output .= '<button ' . (($sort == "epulet") ? ' class="selected_button" ' : '') . ' name="sort_build" value="epulet" >Épület</button>&nbsp;&nbsp;&nbsp;';
$output .= '<button ' . (($sort == "cegnev") ? ' class="selected_button" ' : '') . ' name="sort_name" value="cegnev" >Cégnév</button>&nbsp;&nbsp;&nbsp;';
$output .= '<button ' . (($sort == "tulaj") ? ' class="selected_button" ' : '') . ' name="sort_owner" value="tulaj" >Tulajdonos</button>';
$output .= '<input type="hidden" name="sort" value="' . $sort . '">';
$output .= '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Listázás :';
$output .= '<button ' . (($aktiv == "minden") ? ' class="selected_button" ' : '') . ' name="aktiv_all" value="minden">Mindegyik</button>&nbsp;&nbsp;&nbsp;';
$output .= '<button ' . (($aktiv == "aktiv") ? ' class="selected_button" ' : '') . ' name="aktiv_act" value="aktiv">Aktívak</button>';
$output .= '<input type="hidden" name="aktiv" value="' . $aktiv . '">';



/*
  if (isset($tetel_torol) AND isLogedIn()) { // Megszünt, csak inaktiválni lehet
  echo $del_string = 'DELETE FROM cegek WHERE id=' . $tetel_torol . ' LIMIT 1';

  if ($mysqliLink->query($del_string)) {
  header("Location:" . PROGI);
  exit();
  } else {
  $output .= '<br><a  title="A tételt nem sikerült törölni, vissza !" href="' . PROGI . '?mod=l"><img width="48" weight="48"src="' . IMAGES . 'plus.jpg"></a>';
  }
  }
 */
if (isset($ceg_inaktiv)) {
    $mod_string = 'UPDATE cegek SET act=0, `' . RECORD_STOP . '`="' . $today . '" WHERE id=' . $ceg_inaktiv;
    if ($mysqliLink->query($mod_string)) {
        logger($mem_id, $ceg_inaktiv, LOGGER_CAT_INACTIV_CEG, '');
//        header("Location:" . PROGI);
    } else {
        $output .= '<br><a  title="A tételt nem sikerült inaktíválni, vissza !" href="' . PROGI . '?mod=l"><img width="48" weight="48"src="' . IMAGES . 'plus.jpg"></a>';
    }
}
if (isset($ceg_aktiv)) {
    $mod_string = 'UPDATE cegek SET act=1, `' . RECORD_STOP . '`="' . FOREVER . '" WHERE id=' . $ceg_aktiv;
    if ($mysqliLink->query($mod_string)) {
        logger($mem_id, $ceg_aktiv, LOGGER_CAT_ACTIV_CEG, '');
//        header("Location:" . PROGI);
    } else {
        $output .= '<br><a  title="A tételt nem sikerült inaktíválni, vissza !" href="' . PROGI . '?mod=l"><img width="48" weight="48"src="' . IMAGES . 'plus.jpg"></a>';
    }
}


if (isset($ceg_felvesz)) {
    // Rogzitjuk a bevitt adatokat, ha rendben van
    $hiba = array();
    if (!isset($ceg_cegnev) OR strlen($ceg_cegnev) < 3) {
        $hiba['cegnev'] = 'Túl rövid cégnév';
    }
    if (!isset($ceg_ownerId)) {
        $hiba['tulajdonos'] = 'Hiba a bérbeadónál';
    }
    if (!isset($ceg_buildingId)) {
        $hiba['epulet'] = 'Hiba a helyiség megadásnál !';
    }
    if (($buildingOwner[$ceg_buildingId] != $ceg_ownerId) AND ( $buildingOwner[$ceg_buildingId] != 0)) {
        $hiba['epulet'] = 'Ennek az epületnek a tulajdonosa: ' . $owners[$buildingOwner[$ceg_buildingId]];
    }
    if (empty($hiba)) {

        if ($ceg_id == 0) { // Ujat veszunk fel
            $sql_str = 'INSERT INTO cegek (cegnev, ownerId, buildingId, szoba, tevekenyseg, vezeto, telefon, email, honlap, comment, parkolo, start, posta, act) VALUES 
                                 ("' . $ceg_cegnev . '","' . $ceg_ownerId . '","' . $ceg_buildingId . '","' . $ceg_szoba . '","' . $ceg_tevekenyseg . '","' . $ceg_vezeto . '", "' . $ceg_telefon . '","' . $ceg_email . '","' . $ceg_honlap . '","'. $ceg_comment . '","' . $ceg_parkolo . '","' . $ceg_start . '","' . $ceg_posta . '", 1)';
        } else {  // Modositjuk a ceg_id elemet
            $sql_str = 'UPDATE cegek SET
                                   cegnev = "' . $ceg_cegnev . '", 
                                   ownerId = "' . $ceg_ownerId . '",
                                   buildingId = "' . $ceg_buildingId . '", 
                                   szoba = "' . $ceg_szoba . '",
                                   tevekenyseg = "' . $ceg_tevekenyseg . '", 
                                   vezeto = "' . $ceg_vezeto . '",
                                   telefon = "' . $ceg_telefon . '",
                                   email = "' . $ceg_email . '",
                                   honlap = "' . $ceg_honlap . '",
                                   comment = "' . $ceg_comment . '",
                                   parkolo = "' . $ceg_parkolo . '",
                                   posta = "' . $ceg_posta . '"
                        WHERE id = "' . $ceg_id . '"';
        }
        if ($mysqliLink->query($sql_str)) {
            logger($mem_id, $ceg_id, ($ceg_id == 0) ? LOGGER_CAT_INSERT_CEG : LOGGER_CAT_MODIFY_CEG, $ceg_cegnev);
            $output .= 'A rögzítés sikeres';
//            $output .= '<br><a  title="új tétel felvétele !" href="' . PROGI . '?mod=a"><img src="plus.jpg"></a>';
//            $output .= '<br><a  title="Köszönöm, ennyi volt !" href="' . PROGI . '?mod=l"><img width="48" weight="48"src="' . IMAGES . 'ready.jpg"></a>';
        } else {
            $output .= '<br><a  title="Ez nem sikerült, vissza !" href="' . PROGI . '?mod=l"><img width="48" weight="48"src="' . IMAGES . 'ready.jpg"></a>';
        }
    } else {
        foreach ($hiba as $h) {
            warning('Hiba :' . $h);
        }
    }
}

// Itt kezdodik a listazas
$output .= '<div class="lists">';

$output .= '<table><thead>';
$output .= '<tr id="teteje"><th style="width:32px;">No.</th>';
$output .= '<th style="width:156px;">Cégnév</th>';
$output .= '<th style="width:156px;">Elhelyezkedés</th>';
$output .= '<th style="width:156px;">Tulajdonos</th>';
$output .= '<th style="width:20px;"></th>';
$output .= '</tr></thead><tbody>';
/*
 *         }
 */
$eredm = $mysqliLink->query($sql);
while ($rekord = $eredm->fetch_assoc()) {
    $output .= '<tr id="ceg_id_' . $rekord[RECORD_ID] . '"><td>' . $rekord[RECORD_ID] . '</td>';
    $output .= '<td>';
    $output .= '<div class="tooltip">' . $rekord[RECORD_CEGNEV]
            . '<span class="tooltiptext">'
            . $rekord[RECORD_VEZETO]
            . '<br>' . $rekord[RECORD_TELEFON]
            . '<br>' . $rekord[RECORD_EMAIL]
            . '<br>' . $rekord[RECORD_TEVEKENYSEG]
            . '<br>' . $rekord[RECORD_HONLAP]
            . '<br>' . $rekord[RECORD_COMMENT]
            . '<br>' . $rekord[RECORD_PARKOLO]
            . '</span></div></td>';
    $output .= '<td>' . $buildings[$rekord[RECORD_BUILDINGID]] . ' '
            . $rekord[RECORD_SZOBA] . '</td><td>'
            . $owners[$rekord[RECORD_OWNERID]] . '</td>';
    $output .= $cegek_mod == "delete" ? (
            '<td><a title="A tétel végleges törlése" href="' . PROGI . '?tetel_torol=' . $rekord[RECORD_ID] . '"
                            onClick="return confirm(\'Biztosan törölni akarod a ' . $rekord[RECORD_CEGNEV] . ' céget?\')">
                            <img src="' . IMAGES . 'delete.jpg">
                            </a></td>'
            ) :
            ('<td>' . ($rekord[RECORD_AKTIV] == 1 ?
            ('<button name="ceg_inaktiv" value="' . $rekord[RECORD_ID] . '" title="Cég inaktiválása" onClick="return confirm(\'Biztosan inakítválni akarod a ' . $rekord[RECORD_CEGNEV] . ' céget?\')"><img src="' . IMAGES . 'ok.jpg"></button>' ) :
            ('<button name="ceg_aktiv" value="' . $rekord[RECORD_ID] . '" title="Cég aktiválása"><img src="' . IMAGES . 'inaktiv.jpg" onClick="return confirm(\'Biztosan aktíválni akarod a ' . $rekord[RECORD_CEGNEV] . ' céget?\')"></button>' ))
            . '<button name="ceg_edit" value="' . $rekord[RECORD_ID] . '" title="Cég adatainak szerkesztése"><img src="' . IMAGES . 'edit.jpg"></button>' .
            '</td>');
    $output .= '</tr>';
}
$output .= '</tbody></table>';
$output .= '</form></div>';



