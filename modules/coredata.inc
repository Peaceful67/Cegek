<?php

$selectedCore = getVariable('selectedCore');
$editableCores = [
    'Személyek' => 'edit_persons.inc',
];
$output .= '<div class="keret">';
$output .= '<label>Törzsadat: </label>';
$output .= '<select name="selectedCore" onChange="submit();">';
$output .= '<option value="" ' . (empty($selectedCore) ? "selected" : "") . '>Válassz!</option>';
foreach ($editableCores as $title => $func) {
    $output .= '<option value="' . $title . '" ' . ($selectedCore == $title ? "selected" : "") . '>' . $title . '</option>';
}
$output .= '</div>';
if (empty($selectedCore)) {
    return;
}


include_once INCLUDES . $editableCores[$selectedCore];

