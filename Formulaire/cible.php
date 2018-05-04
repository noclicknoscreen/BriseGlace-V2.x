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
    "Jeux" => $_GET['jeux'],
    "mot" => $_GET['mot'],
    "indice1"=>array(
        "nom"=>$_GET['indice1'],
        "photo"=>$_GET['photo1'],
    ),
    "indice2"=>array(
        "nom"=>$_GET['indice2'],
        "photo"=>$_GET['photo1'],
    ),
    "indice3"=>array(
        "nom"=>$_GET['indice3'],
        "photo"=>$_GET['photo1'],
    ),
    "recompense"=>array(
        "description"=>$_GET['recompense'],
        "photo"=>$_GET['photoR'],
    )
);

// echo json_encode($jsonFormat, JSON_PRETTY_PRINT);

if (file_exists ("enigme1") == false) {
    mkdir("./enigme1", 0777, true);
}
$fichier = fopen("enigme1/test.json", "w+");

fputs($fichier, $json_string = json_encode($jsonFormat, JSON_PRETTY_PRINT));

fclose($fichier);

?>

<p>Enigme enregistrer !</p>

</body>
</html>
