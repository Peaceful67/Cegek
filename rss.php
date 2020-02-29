<?php

include_once 'settings.inc';


$output = '<?xml version="1.0"?>';
$xml_cegek = new SimpleXMLElement("<?xml version=\"1.0\"?><companies></companies>");
$cegek_array = array();

$eredm = $mysqliLink->query(SQL_QUERY_ACT_BY_CEGNEV);
while ($eredm AND $rekord = $eredm->fetch_assoc()) {
    $id = $rekord['id'];
    $cegek_array[$id]['name'] = $rekord[RECORD_CEGNEV];
    $cegek_array[$id]['place'] = $buildings[$rekord[RECORD_BUILDINGID]];
    array_to_xml($cegek_array, $xml_cegek, 'company');
    $output = $xml_cegek->asXML();
}
theEnd($output);

function array_to_xml($array, &$xml_user_info, $item_name) {
    foreach ($array as $key => $value) {
        if (is_array($value)) {
            if (!is_numeric($key)) {
                $subnode = $xml_user_info->addChild("$key");
                array_to_xml($value, $subnode, $item_name0);
            } else {
                $subnode = $xml_user_info->addChild($item_name);
                array_to_xml($value, $subnode, $item_name);
            }
        } elseif (!empty($value)) {
            $xml_user_info->addChild("$key", htmlspecialchars(trim($value)));
        }
    }
}
