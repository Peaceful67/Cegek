<?php

if (!isset($selectedUser)) {
    $selectedUser = -1;
}
if(isset($belep) AND $authUser->setUserId($selectedUser) AND $authUser->isPasswdOK($loginPassword)) {
    $authUser->logIn($loginPassword);
    $menuModules->goHome();
    return;
}
if ($selectedUser > 0 AND isset($sendEmail)) {
    $command = new Command();
    $code = $command->putCommand($authUser->getUserId(), COMMAND_PASSWORD, $selectedUser, '1');
    $email_addr = $authUser->getEmailOfUser($selectedUser);
    $subject = 'Új jelszó megadása';
    $body = 'Tisztelt '.$authUser->getNameOfUser($selectedUser).' !<br><br>';
    $body .= 'Az alábbi linkre kattintva új jelszót állíthatsz be magadnak:<br>';
    $body .= '<a target="_blank" href="'.$host_url.'?'.COMMAND_STRING.'='.$code.'">Jelszó megadás</a><br>';
    $body .= '<br>Üdvözlettel:<br>Adminisztrációs felület';
    send_mail_to($email_addr, $subject, $body);
    $output .= '<div class="keret">';
    $output .= '<br>A '.$email_addr.' email címre kiment a jelszó megadáshoz szükséges link.<br>';
    $output .= '<br>A link mostantól 24 óráig lesz felhasználható.<br><br>';
    $output .= '</div>';
    return;
}
$output .= '<div class="editor keret">';
$output .= '
                <label>Felhasználó :</label><select name="selectedUser" onchange="submit();">
                <option value="-1" ' . ($selectedUser == -1 ? "selected" : "") . '>Válassz !!!</option>';

foreach ($authUser->readTable() as $u) {
    $output .= '<option value="' . $u[DB_AUTH_USER_ID] . '" ' . ($u[DB_AUTH_USER_ID] == $selectedUser ? "selected" : "") . '>' . $u[DB_AUTH_USER_USERNAME] . '</option>';
}
$output .= '</select><br>
                <label>Jelszó: </label>
                <input type="password" name="loginPassword"><br>
                <input type="submit" name="belep" value="Belépés"> 
                <input type="submit" name="sendEmail" value="Új jelszó">
    ';
$output .= '</div>';
