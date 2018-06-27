<?php

try
{
  $bdd = new PDO('mysql:host=localhost;dbname=formulaire;charset=utf8', 'root', 'root');
}
catch (Exception $e)
{
  die('Erreur : ' . $e->getMessage());
}

// On récupère tout le contenu de la table enigme

$reponse = $bdd->query($_POST['good_requet']);

// On affiche chaque entrée une à une

$i = 0;
while ($donnees = $reponse->fetch())
{
  $id = $donnees['id'];
  $long = strlen($id);
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

  if (file_exists("enigme/" . $StrNum . $id) == false) {
      mkdir("./enigme/" . $StrNum . $id, 0777, true);
      mkdir("./enigme/" . $StrNum . $id . "/image", 0777, true);
  }

  if (file_exists("./enigme/" . $StrNum . $id . "/image") == false) {
      mkdir("./enigme/" . $StrNum . $id . "/image", 0777, true);
  }

  // Upload des images
  for ($j=0; $j <= 4; $j++) {

    $testImg = false;

    $url = $_POST['sqlimage' . $j . $i];
    $info = new SplFileInfo($url);
        if (file_exists("tmp/image" . $j . $i . "-crop.jpg"))
          {
            $datacrop = @file_get_contents("tmp/image" . $j . $i . "-crop.jpg");
            $newcrop ="enigme/" . $StrNum . $id . '/image/image' . $j . '-crop.jpg';
            file_put_contents($newcrop, $datacrop);
            unlink("tmp/image" . $j . $i . "-crop.jpg");
          }
          if ($donnees['image' . $j] != $_POST['sqlimage' . $j . $i] || file_exists("enigme/" . $StrNum . $id . '/image/image' . $j . '.' . $info->getExtension()) == false)
          {
            $data = @file_get_contents($url);
            $new = "enigme/" . $StrNum . $id . '/image/image' . $j . '.' . $info->getExtension();
            file_put_contents($new, $data);
          }

    $imgName[$j] = 'image' . $j . '.' . $info->getExtension();
  }

if (@$_POST['check' . $i]) { $actif = "on"; }
else { $actif = "off"; }

$imgcrop0 = "enigme/" . $StrNum . $id . '/image/image0-crop.jpg';
$imgcrop1 = "enigme/" . $StrNum . $id . '/image/image1-crop.jpg';
$imgcrop2 = "enigme/" . $StrNum . $id . '/image/image2-crop.jpg';
$imgcrop3 = "enigme/" . $StrNum . $id . '/image/image3-crop.jpg';
$imgcrop4 = "enigme/" . $StrNum . $id . '/image/image4-crop.jpg';

if (!strcmp($_POST['sqlcomplet' . $i], "vide"))
{
  clearFolder("./enigme/" . $StrNum . $id . "/image/");
  $_POST['sqlimage0'. $i] = "";
  $imgcrop0 = "";
  $imgcrop1 = "";
  $imgcrop2 = "";
  $imgcrop3 = "";
  $imgcrop4 = "";
}

  $req = $bdd->prepare('UPDATE enigme SET mot = :mot, theme = :theme, image0 = :image0, imgcrop0 = :imgcrop0, auteur0 = :auteur0, date0 = :date0,
                        indice1 = :indice1, image1 = :image1, imgcrop1 = :imgcrop1, auteur1 = :auteur1, date1 = :date1,
                        indice2 = :indice2, image2 = :image2, imgcrop2 = :imgcrop2, auteur2 = :auteur2, date2 = :date2,
                        indice3 = :indice3, image3 = :image3, imgcrop3 = :imgcrop3, auteur3 = :auteur3, date3 = :date3,
                        recompense = :recompense, image4 = :image4, imgcrop4 = :imgcrop4, auteur4 = :auteur4, date4 = :date4,
                        legende = :legende, complet = :complet, actif = :actif WHERE id = :id');
  $req->execute(array(
    'mot' =>$_POST['sqlmot' . $i],
    'theme' =>$_POST['sqltheme' . $i],

    'image0'=>$_POST['sqlimage0'. $i],
    'imgcrop0'=> $imgcrop0,
    'auteur0' => $_POST['sqlauteur0'. $i],
    'date0' => $_POST['sqldate0' . $i],

    'indice1'=>$_POST['sqlindice1' . $i],
    'image1'=>$_POST['sqlimage1' . $i],

    'imgcrop1'=> $imgcrop1,
    'auteur1' => $_POST['sqlauteur1'. $i],
    'date1' => $_POST['sqldate1'. $i],

    'indice2'=>$_POST['sqlindice2' . $i],
    'image2'=>$_POST['sqlimage2' . $i],

    'imgcrop2'=> $imgcrop2,
    'auteur2' => $_POST['sqlauteur2'. $i],
    'date2' => $_POST['sqldate2'. $i],

    'indice3'=>$_POST['sqlindice3' . $i],
    'image3'=>$_POST['sqlimage3' . $i],

    'imgcrop3'=> $imgcrop3,
    'auteur3' => $_POST['sqlauteur3'. $i],
    'date3' => $_POST['sqldate3'. $i],

    'recompense'=>$_POST['sqlrecompense' . $i],
    'image4'=>$_POST['sqlimage4' . $i],

    'imgcrop4'=> $imgcrop4,
    'auteur4' => $_POST['sqlauteur4'. $i],
    'date4' => $_POST['sqldate4'. $i],

    'legende'=>$_POST['sqllegende' . $i],
    'complet' => $_POST['sqlcomplet' . $i],
    'actif' => $actif,

  	'id' => $id,
  	));
    $req->closeCursor();

    $jsonFormat = array(
        "theme"=>$_POST['sqltheme' . $i],
        "mot" => array(
          "titre"=>$_POST['sqlmot' . $i],
          "image"=>$imgName[0],
          "image-crop"=> "image0-crop.jpg",
          "url"=>$_POST['sqlimage0' . $i],
          'auteur' => $_POST['sqlauteur0' . $i],
          'date' => $_POST['sqldate0' . $i],
        ),
        "indice"=>array(array(
            "titre"=>$_POST['sqlindice1' . $i],
            "image"=>$imgName[1],
            "image-crop"=> "image1-crop.jpg",
            "url"=>$_POST['sqlimage1' . $i],
            'auteur' => $_POST['sqlauteur1' . $i],
            'date' => $_POST['sqldate1' . $i],
          ),
          array(
            "titre"=>$_POST['sqlindice2' . $i],
            "image"=>$imgName[2],
            "image-crop"=> "image2-crop.jpg",
            "url"=>$_POST['sqlimage2' . $i],
            'auteur' => $_POST['sqlauteur2' . $i],
            'date' => $_POST['sqldate2' . $i],
          ),
          array(
            "titre"=>$_POST['sqlindice3' . $i],
            "image"=>$imgName[3],
            "image-crop"=> "image3-crop.jpg",
            "url"=>$_POST['sqlimage3' . $i],
            'auteur' => $_POST['sqlauteur3' . $i],
            'date' => $_POST['sqldate3' . $i],
        ),),
          "recompense"=>array(
            "indice"=>array(
              "titre"=>$_POST['sqlrecompense' . $i],
              "image"=>$imgName[4],
              "image-crop"=> "image4-crop.jpg",
              "url"=>$_POST['sqlimage4' . $i],
              'auteur' => $_POST['sqlauteur4' . $i],
              'date' => $_POST['sqldate4' . $i],
            ),
          "legende"=>$_POST['sqllegende' . $i],
          )
        );

        // Modifie le fichier JSON
        $fichier = fopen("enigme/" . $StrNum . $id . "/enigma.json", "w+");
        fputs($fichier, $json_string = json_encode($jsonFormat, JSON_UNESCAPED_UNICODE | JSON_PRETTY_PRINT));
        fclose($fichier);

$i++;
}
$reponse->closeCursor();

?>
