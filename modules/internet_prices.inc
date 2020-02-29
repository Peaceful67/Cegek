<?php

if (!isset($price_first)) {
    $price_first = getOptionValue(OPTIONS_NAME_PRICE_FIRST);
}
if (!isset($price_more)) {
    $price_more = getOptionValue(OPTIONS_NAME_PRICE_MORE);
}
if (isset($submit_price)) {
    updateOption(OPTIONS_NAME_PRICE_FIRST, $price_first);
    updateOption(OPTIONS_NAME_PRICE_MORE, $price_more);
}
$output .= '<div class="keret">';
$output .= '<label style="width:200px;  display:inline-block;">Első csatlakozás:</label>';
$output .= '<input type="number" maxlength="5" name="price_first"  min="100" max="10000" step="100" value="'
        . $price_first . '"> Ft<br>';
$output .= '<label style="width:200px;  display:inline-block;">További csatlakozások :</label>';
$output .= '<input type="number" maxlength="5" name="price_more" min="100" max="10000" step="100" value="'
        . $price_more . '"> Ft<br>';
$output .= '<button name="submit_price" value="submiting" title="Mentés">Rögzít</button>';
$output .= '</div>';

