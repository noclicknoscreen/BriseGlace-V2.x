<!doctype html>

<html>
<head>
    <meta charset="utf-8">
    <title>Manipulation des formulaires</title>
</head>

<body>
<?php
// header('Content-type: text/javascript');

$jsonFormat = array(
    "Jeux" => $_POST['jeux'],
    "mot" => $_POST['mot'],
    "indice1"=>array(
        "nom"=>$_POST['indice1'],
        "photo"=>$_POST['photo1'],
    ),
    "indice2"=>array(
        "nom"=>$_POST['indice2'],
        "photo"=>$_POST['photo1'],
    ),
    "indice3"=>array(
        "nom"=>$_POST['indice3'],
        "photo"=>$_POST['photo1'],
    ),
    "recompense"=>array(
        "description"=>$_POST['recompense'],
        "photo"=>$_POST['photoR'],
    )
);

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

$fichier = fopen($tmp . "/" . $num . "/enigme.json", "w+");
fputs($fichier, $json_string = json_encode($jsonFormat, JSON_PRETTY_PRINT));
fclose($fichier);


$num = $num + 1;
$text = fopen($tmp . "/info.txt", "w+");
fputs($text, $num);
fclose($text);

echo $num;

?>

<p>Enigme enregistrer !</p>

</body>
</html>
