<!doctype html>

<html>
<head>
    <meta charset="utf-8">
    <title>Manipulation des formulaires</title>
</head>

<body>
<?php
$tmp = $_POST['jeux'];
if (file_exists ($tmp) == false) {
    mkdir("./" . $tmp, 0777, true);
}

$num = file_get_contents($tmp . "/info.txt");


if (file_exists ($tmp . "/" . $num) == false) {
    mkdir("./" . $tmp . "/" . $num, 0777, true);
}

if (file_exists ($tmp . "/" . $num . "/image") == false) {
    mkdir("./" . $tmp . "/" . $num . "/image", 0777, true);
}

// Photo
for ($i=1; $i <= 4; $i++) {
  $url=$_POST['photo' . $i];

  $info = new SplFileInfo($url);

  if (urlExist($url)) {
    $data = @file_get_contents($url);

    if ($info->getExtension() == "jpg" || $info->getExtension() == "jpeg" || $info->getExtension() == "png"|| $info->getExtension() == "gif") {
        $new = $tmp . "/" . $num . '/image/image' . $i . '.' . $info->getExtension();
        file_put_contents($new, $data);
        $imgName[$i] = 'image' . $i . '.' . $info->getExtension();
      }
      else {
        echo "Echec du Chargement de la photo " . $i . " : ce n'est pas une image !<br>";
        $imgName[$i] = '';
      }
    }
    else {
      echo "Echec du Chargement de la photo " . $i . " : le lien n'existe pas !<br>";
      $imgName[$i] = '';
    }
}

$jsonFormat = array(
    "Jeux" => $_POST['jeux'],
    "mot" => $_POST['mot'],
    "indice1"=>array(
        "nom"=>$_POST['indice1'],
        "photo"=>$imgName[1],
    ),
    "indice2"=>array(
        "nom"=>$_POST['indice2'],
        "photo"=>$imgName[2],
    ),
    "indice3"=>array(
        "nom"=>$_POST['indice3'],
        "photo"=>$imgName[3],
    ),
    "recompense"=>array(
        "description"=>$_POST['recompense'],
        "photo"=>$imgName[4],
    )
);

$fichier = fopen($tmp . "/" . $num . "/enigme.json", "w+");
fputs($fichier, $json_string = json_encode($jsonFormat, JSON_PRETTY_PRINT));
fclose($fichier);


$num = $num + 1;
$text = fopen($tmp . "/info.txt", "w+");
fputs($text, $num);
fclose($text);

echo "<p>Enigme enregistrer !</p>";

// Fonction
function urlExist($url) {
    $file_headers = @get_headers($url);
    if($file_headers[0] == 'HTTP/1.1 404 Not Found')
       return false;

    return true;
}
?>
</body>
</html>
