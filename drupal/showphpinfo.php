<html>
<body>
<?php

if (isset($_COOKIE["PHPSESSID"]))
echo "Welcome " . $_COOKIE["PHPSESSID"] . "!<br />";
else
echo "Welcome guest!<br />";
phpinfo(INFO_GENERAL);
phpinfo(INFO_MODULES);
?>
</body>
</html>
