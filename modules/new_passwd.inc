<?php

if(isset($submitPasswd)) {
    if($passwd1 == $passwd2) {
        $authUser->setPasswd($passwd1);
        $authUser->logIn($passwd1);
        $menuModules->goHome();
        return;
    } else {
        warning('A két jelszó nem egyezik');
    }
}

$output .= '<div class="keret editor">';
$output .= '<label>Új jelszó:</label><input type="password" name="passwd1"><br>';
$output .= '<label>Ismét:</label><input type="password" name="passwd2"><br>';
$output .= '<input type="submit" name="submitPasswd" value="Rögzít">';
$output .= '</div>';
