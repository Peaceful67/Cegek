<?php

$editItemList->setListEdit();

if (isset($delete)) {
    $editItemList->deleteItemById($delete);
}
if (isset($edit)) {
    $item = $editItemList->getItemById($edit);
    foreach ($item as $key => $value) {
        $editItemList->modFieldValue($key, $value);
    }
} else {
    $edit = -1;
}

if (isset($new)) {
    $edit = -1;
    foreach ($editItemList->fields as $key => $field) {
        $var_name = "edit_' . $key . '";
        resetVariable($var_name);
        $editItemList->resetFieldValue($key);
    }
}
if (isset($save)) {
    $error = false;
    $item = array();
    foreach ($editItemList->fields as $key => $field) {
        if ($field[FIELD_EDITSIZE] <= 0) {
            continue;
        }
        $saverFunction = $editItemList->getFieldSaver($key);
        if (!empty($saverFunction)) {
            $item[$key] = $editItemList->$saverFunction();
        } else {
            switch ($field[FIELD_TYPE]) {
                case FIELD_TYPE_VARCHAR:
                    $var_name = 'edit_' . $key;
                    if (strlen($$var_name) < 3) {
                        warning('Túl rövid ' . $field[FIELD_NAME]);
                        $error = true;
                    } else {
                        $item[$key] = $$var_name;
                    }
                    break;
                case FIELD_TYPE_CHECKBOXES:
                    break;
                case FIELD_TYPE_BOOL:
                    break;
                case FIELD_TYPE_RELATED_ID:
                    break;
                default:
                    break;
            }
        }
    }
    if (!$error) {
        if ($save < 0) {
            $editItemList->addItem($item);
        } else {
            $editItemList->modifyItem([$editItemList->getPrimaryKey() => $save], $item);
        }
    }
}
$output .= '<div class="editor keret">';
foreach ($editItemList->fields as $key => $field) {
    if ($field[FIELD_EDITSIZE] < 0) {
        continue;
    }
    $output .= '<label>' . $field[FIELD_NAME] . ': </label>';
    $editorFunction = $editItemList->getFieldEditor($key);
    if (!empty($editorFunction)) {
        $output .= $editItemList->$editorFunction();
    } else {
        switch ($field[FIELD_TYPE]) {
            case FIELD_TYPE_VARCHAR:
                $output .= '<input type="text" '
                        . 'name="edit_' . $key . '" '
                        . 'maxlength="' . $field[FIELD_EDITSIZE] . '" '
                        . 'value="' . $field[FIELD_VALUE] . '">';
                break;
            default:
                break;
        }
    }
    $output .= '<br>';
}
$output .= '<button type="submit" name="new" value="-1" title="Új felhasználó"><img src="' . IMAGES . 'add.jpg"></button>&nbsp;&nbsp;&nbsp;';

$output .= '<button type="submit" name="save" value="' . $edit . '" title="'
        . ($edit < 0 ? 'Új felhasználó rögzítése' : 'Felhasználó módosítása')
        . '"><img src="' . IMAGES . 'save.jpg"></button>';
$output .= '</div>';
$output .= '<div class="lists keret">';
$output .= '<table><tr>';
foreach ($editItemList->fields as $key => $field) {
    if ($field[FIELD_LISTSIZE] < 0) {
        continue;
    }
    $output .= '<th>' . $field[FIELD_NAME] . '</th>';
}
$output .= '<th>Művelet</th>';
$output .= '</tr>';
foreach ($editItemList->readTable() as $item) {
    $output .= '<tr>';
    foreach ($editItemList->fields as $key => $field) {
        if ($field[FIELD_LISTSIZE] < 0) {
            continue;
        }
        $editItemList->modFieldValue($key, $item[$key]);
        $viewerFunction = $editItemList->getFieldViewer($key);
        $output .= '<td>';
        $output .= empty($viewerFunction) ? $item[$key] : $editItemList->$viewerFunction();
        $output .= '</td>';
    }
    $output .= '<td>';
    $output .= '<button type="submit" name="edit" value="' . $item[$editItemList->key] . '" title="Szerkesztés"><img src="' . IMAGES . 'edit.jpg"></button>';
    $output .= '<button type="submit" name="delete" value="' . $item[$editItemList->key] . '" title="Törlés"><img src="' . IMAGES . 'delete.jpg"></button>';
    $output .= '</td>';
    $output .= '</tr>';
}
$output .= '</table>';
$output .= '</div>';
