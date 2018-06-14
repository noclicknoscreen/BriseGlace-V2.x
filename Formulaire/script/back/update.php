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
$reponse = $bdd->query("SELECT * FROM enigme");


// On affiche chaque entrée une à une
echo 'console.log("debug1");';
$id = 0;
while ($donnees = $reponse->fetch())
{
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
  // Upload des images
  for ($j=0; $j <= 4; $j++) {

    $testImg = false;
    $zone = $bdd->query("SELECT * FROM enigme WHERE id='$id'");
    $donnees = $zone->fetch();
    $zone->closeCursor();
    $url = $_POST['sqlimage' . $j . $id];
    $info = new SplFileInfo($url);
        if (file_exists("tmp/image" . $j . $id . "-crop.jpg"))
          {
            $datacrop = @file_get_contents("tmp/image" . $j . $id . "-crop.jpg");
            $newcrop ="enigme/" . $StrNum . $id . '/image/image' . $j . '-crop.jpg';
            file_put_contents($newcrop, $datacrop);
            unlink("tmp/image" . $j . $id . "-crop.jpg");
          }
          if ($donnees['image' . $j] != $_POST['sqlimage' . $j . $id])
          {
            $data = @file_get_contents($url);
            $new = "enigme/" . $StrNum . $id . '/image/image' . $j . '.' . $info->getExtension();
            file_put_contents($new, $data);
          }

    $imgName[$j] = 'image' . $j . '.' . $info->getExtension();
  }

  $req = $bdd->prepare('UPDATE enigme SET mot = :mot, image0 = :image0, imgcrop0 = :imgcrop0, auteur0 = :auteur0, date0 = :date0,
                        indice1 = :indice1, image1 = :image1, imgcrop1 = :imgcrop1, auteur1 = :auteur1, date1 = :date1,
                        indice2 = :indice2, image2 = :image2, imgcrop2 = :imgcrop2, auteur2 = :auteur2, date2 = :date2,
                        indice3 = :indice3, image3 = :image3, imgcrop3 = :imgcrop3, auteur3 = :auteur3, date3 = :date3,
                        recompense = :recompense, image4 = :image4, imgcrop4 = :imgcrop4, auteur4 = :auteur4, date4 = :date4,
                        legende = :legende WHERE id = :id');
  $req->execute(array(
    'mot' =>$_POST['sqlmot' . $id],

    'image0'=>$_POST['sqlimage0'. $id],
    'imgcrop0'=> "enigme/" . $StrNum . $id . '/image/image0-crop.jpg',
    'auteur0' => $_POST['sqlauteur0'. $id],
    'date0' => $_POST['sqldate0' . $id],

    'indice1'=>$_POST['sqlindice1' . $id],
    'image1'=>$_POST['sqlimage1' . $id],

    'imgcrop1'=> "enigme/" . $StrNum . $id . '/image/image1-crop.jpg',
    'auteur1' => $_POST['sqlauteur1'. $id],
    'date1' => $_POST['sqldate1'. $id],

    'indice2'=>$_POST['sqlindice2' . $id],
    'image2'=>$_POST['sqlimage2' . $id],

    'imgcrop2'=> "enigme/" . $StrNum . $id . '/image/image2-crop.jpg',
    'auteur2' => $_POST['sqlauteur2'. $id],
    'date2' => $_POST['sqldate2'. $id],

    'indice3'=>$_POST['sqlindice3' . $id],
    'image3'=>$_POST['sqlimage3' . $id],

    'imgcrop3'=> "enigme/" . $StrNum . $id . '/image/image3-crop.jpg',
    'auteur3' => $_POST['sqlauteur3'. $id],
    'date3' => $_POST['sqldate3'. $id],

    'recompense'=>$_POST['sqlrecompense' . $id],
    'image4'=>$_POST['sqlimage4' . $id],

    'imgcrop4'=> "enigme/" . $StrNum . $id . '/image/image4-crop.jpg',
    'auteur4' => $_POST['sqlauteur4'. $id],
    'date4' => $_POST['sqldate4'. $id],

    'legende'=>$_POST['sqllegende' . $id],
  	'id' => $id,
  	));
    $req->closeCursor();

    $jsonFormat = array(
        "mot" => array(
          "titre"=>$_POST['sqlmot' . $id],
          "image"=>$imgName[0],
          "image-crop"=> "image0-crop.jpg",
          "url"=>$_POST['sqlimage0' . $id],
          'auteur' => $_POST['sqlauteur0' . $id],
          'date' => $_POST['sqldate0' . $id],
        ),
        "indice"=>array(array(
            "titre"=>$_POST['sqlindice1' . $id],
            "image"=>$imgName[1],
            "image-crop"=> "image1-crop.jpg",
            "url"=>$_POST['sqlimage1' . $id],
            'auteur' => $_POST['sqlauteur1' . $id],
            'date' => $_POST['sqldate1' . $id],
          ),
          array(
            "titre"=>$_POST['sqlindice2' . $id],
            "image"=>$imgName[2],
            "image-crop"=> "image2-crop.jpg",
            "url"=>$_POST['sqlimage2' . $id],
            'auteur' => $_POST['sqlauteur2' . $id],
            'date' => $_POST['sqldate2' . $id],
          ),
          array(
            "titre"=>$_POST['sqlindice3' . $id],
            "image"=>$imgName[3],
            "image-crop"=> "image3-crop.jpg",
            "url"=>$_POST['sqlimage3' . $id],
            'auteur' => $_POST['sqlauteur3' . $id],
            'date' => $_POST['sqldate3' . $id],
        ),),
          "recompense"=>array(
            "indice"=>array(
              "titre"=>$_POST['sqlrecompense' . $id],
              "image"=>$imgName[4],
              "image-crop"=> "image4-crop.jpg",
              "url"=>$_POST['sqlimage4' . $id],
              'auteur' => $_POST['sqlauteur4' . $id],
              'date' => $_POST['sqldate4' . $id],
            ),
          "legende"=>$_POST['sqllegende' . $id],
          )
        );

        // Modifie le fichier JSON
        $fichier = fopen("enigme/" . $StrNum . $id . "/enigma.json", "w+");
        fputs($fichier, $json_string = json_encode($jsonFormat, JSON_UNESCAPED_UNICODE | JSON_PRETTY_PRINT));
        fclose($fichier);

$id++;
}
$reponse->closeCursor();
?>
