<?php

try
{
  $bdd = new PDO('mysql:host=localhost;dbname=formulaire;charset=utf8', 'root', 'root');
}
catch (Exception $e)
{
  die('Erreur : ' . $e->getMessage());
}

// On récupère tout le contenu de la table motus
$reponse = $bdd->query('SELECT * FROM ' . $_POST['jeux']);

// On affiche chaque entrée une à une

$i = 0;
while ($donnees = $reponse->fetch())
{

  $long = strlen($i);
  switch ($long) {
    case 1:
      $StrNum = "000";
      break;
    case 2:
      $StrNum = "00";
      break;
    case 3:
      $StrNum = "0";
      break;
    case 4:
      $StrNum = "";
      break;
  }

  // Upload des images
  for ($j=1; $j <= 4; $j++) {

    $testImg = false;
    $bdd = new PDO('mysql:host=localhost;dbname=formulaire;charset=utf8', 'root', 'root');
    $zone = $bdd->query("SELECT * FROM motus WHERE id='$i'");
    $donnee = $zone->fetch();
    if ($donnee['image' . $j] == $_POST['sqlimage' . $j . $i]) { $testImg = true; }

    $url = $_POST['sqlimage' . $j . $i];
    $info = new SplFileInfo($url);
    if ($testImg == false)
      {
        error_mess($url, $j);
        if (verif_image($url)) {
          $data = @file_get_contents($url);
          $new = $_POST['jeux'] . "/" . $StrNum . $i . '/image/image' . $j . '.' . $info->getExtension();
          file_put_contents($new, $data);
        }
        else { $_POST['sqlimage' . $j . $i] = $donnee['image' . $j]; }
      }
    $imgName[$j] = 'image' . $j . '.' . $info->getExtension();
    $zone->closeCursor();
  }

  $req = $bdd->prepare('UPDATE motus SET mot = :mot, indice1 = :indice1, image1 = :image1, indice2 = :indice2, image2 = :image2,
                        indice3 = :indice3, image3 = :image3, recompense = :recompense, image4 = :image4,
                        legende = :legende WHERE id = :id');
  $req->execute(array(
    'mot' =>$_POST['sqlmot' . $i],
    'indice1'=>$_POST['sqlindice1' . $i],
    'image1'=>$_POST['sqlimage1' . $i],
    'indice2'=>$_POST['sqlindice2' . $i],
    'image2'=>$_POST['sqlimage2' . $i],
    'indice3'=>$_POST['sqlindice3' . $i],
    'image3'=>$_POST['sqlimage3' . $i],
    'recompense'=>$_POST['sqlrecompense' . $i],
    'image4'=>$_POST['sqlimage4' . $i],
    'legende'=>$_POST['sqllegende' . $i],
  	'id' => $i,
  	));

    $jsonFormat = array(
        "jeux" => $_POST['jeux'],
        "mot" => $_POST['sqlmot' . $i],
        "indice"=>array(array(
            "titre"=>$_POST['sqlindice1' . $i],
            "image"=>$imgName[1],
            "url"=>$_POST['sqlimage1' . $i],
          ),
          array(
            "titre"=>$_POST['sqlindice2' . $i],
            "image"=>$imgName[2],
            "url"=>$_POST['sqlimage2' . $i],
          ),
          array(
            "titre"=>$_POST['sqlindice3' . $i],
            "image"=>$imgName[3],
            "url"=>$_POST['sqlimage3' . $i],
        ),),
          "recompense"=>array(
            "indice"=>array(
              "titre"=>$_POST['sqlrecompense' . $i],
              "image"=>$imgName[4],
              "url"=>$_POST['sqlimage4' . $i],
            ),
          "legende"=>$_POST['sqllegende' . $i],
          )
        );

        // Modifie le fichier JSON
        $fichier = fopen($_POST['jeux']. "/" . $StrNum . $i . "/enigma.json", "w+");
        fputs($fichier, $json_string = json_encode($jsonFormat, JSON_UNESCAPED_UNICODE | JSON_PRETTY_PRINT));
        fclose($fichier);

$i++;
}
?>
