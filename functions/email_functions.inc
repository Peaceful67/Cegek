<?php



function send_mail_via_phpmailer($addr, $subject, $body, $filename = "") {
    require_once CLASSES . 'PHPMailer/PHPMailer.php';
    require_once CLASSES . 'PHPMailer/SMTP.php';
    require_once CLASSES . 'PHPMailer/Exception.php';

    $my_mail = new \PHPMailer\PHPMailer\PHPMailer(true);

    $my_mail->IsSMTP();
    $my_mail->SMTPOptions = array(
        'ssl' => array(
            'verify_peer' => false,
            'verify_peer_name' => false,
            'allow_self_signed' => true
        )
    );
    $my_mail->Host = "localhost";
    $my_mail->Port = 25;
    $my_mail->CharSet = 'utf-8';
    $my_mail->Username = SMTP_USER;
    $my_mail->Password = SMTP_PASSWD;
    if (empty($my_mail->Username)) {
        $my_mail->SMTPAuth = false;
    } else {
        $my_mail->SMTPAuth = true;
    }
    $my_mail->AddReplyTo('no-replay@emg.hu', 'Cégek EMG');
    $my_mail->SetFrom('cegek@emg.hu', 'Cégek EMG');
    $my_mail->Subject = $subject;
    $my_mail->AltBody = 'Az üzenet megtekintéséhez használj HTML kompatibilis email klienst !';
    $my_mail->MsgHTML($body);
    $my_mail->AddAddress($addr);
    $my_mail->Encoding = 'base64';
    if (!empty($filename)) {
        $my_mail->AddAttachment($filename);
    }    
    if (!$my_mail->Send()) {
        error_log('Error occurred during sending the email: ' . $my_mail->ErrorInfo);
    }
}

function send_mail_to($addr, $subject, $body, $filename = "") {
    global $member_id;
    $email_body = '<html><body style=\"font-family:Verdana, Verdana, Geneva, sans-serif; font-size:12px;\">';
    $email_body .= $body;
    $email_body .= "<br><br>Üdvözlettel:<br>Cégek EMG" ;
    $email_body .= "</body></html>\n";
    if (!isset($addr) OR empty($addr)) {
        mail_system_error('Nem létező emailcím !\r\nTárgy: ' . $subject . '\r\nTartalom: ' . $body);
        return;
    }
    $addr = trim($addr);
    send_mail_via_phpmailer($addr, $subject, $email_body, $filename);
    logger( -1, -1, LOGGER_CAT_EMAIL_SENT, $addr . ' címre, ' . $subject . ' tárgyú levél kiküldve');
}

function send_mail($subject, $body) {

    $addr = getOptionValue(OPTIONS_NAME_EMAIL_WARNING);
    if (!isset($addr) OR empty($addr)) {
        error_log("Missing email address (send_mail)");
        return;
    }
    send_mail_to($addr, $subject, $body);
}


