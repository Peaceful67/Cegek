<?php

opcache_reset(); 

define("INCLUDES", './includes/');
define("MODULES", './modules/');
define("DESIGN", './css/');
define("TEMPDIR", '/tmp');
define("FUNCTIONS", './functions/');
define("IMAGES", "./images/");
define("CLASSES", './vendor/');
define("HELPERS", './helpers/');

include_once FUNCTIONS.'database.inc';
include_once FUNCTIONS.'config.inc';
include_once FUNCTIONS.'functions.inc';
include_once FUNCTIONS.'ip.inc';
include_once INCLUDES. 'create_tables.inc';
include_once FUNCTIONS.'load_options.inc';
include_once FUNCTIONS.'email_functions.inc';

