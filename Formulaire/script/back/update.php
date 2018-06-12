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
  for ($j=0; $j <= 4; $j++) {

    $testImg = false;
    $bdd = new PDO('mysql:host=localhost;dbname=formulaire;charset=utf8', 'root', 'root');
    $zone = $bdd->query("SELECT * FROM enigme WHERE id='$i'");
    $donnees = $zone->fetch();
    $url = $_POST['sqlimage' . $j . $i];
    $info = new SplFileInfo($url);
    error_mess($url, $j);
    if (verif_image($url)) {
        if (file_exists("tmp/image" . $j . $i . "-crop.jpg"))
          {
            $datacrop = @file_get_contents("tmp/image" . $j . $i . "-crop.jpg");
            $newcrop ="enigme/" . $StrNum . $i . '/image/image' . $j . '-crop.jpg';
            file_put_contents($newcrop, $datacrop);
            unlink("tmp/image" . $j . $i . "-crop.jpg");
          }
          if ($donnees['image' . $j] != $_POST['sqlimage' . $j . $i])
          {
            $data = @file_get_contents($url);
            $new = "enigme/" . $StrNum . $i . '/image/image' . $j . '.' . $info->getExtension();
            file_put_contents($new, $data);
          }
      }
    else { $_POST['sqlimage' . $j . $i] = $donnee['image' . $j]; }
    $imgName[$j] = 'image' . $j . '.' . $info->getExtension();
    $zone->closeCursor();
  }

  $req = $bdd->prepare('UPDATE enigme SET mot = :mot, image0 = :image0, imgcrop0 = :imgcrop0, auteur0 = :auteur0, date0 = :date0,
                        indice1 = :indice1, image1 = :image1, imgcrop1 = :imgcrop1, auteur1 = :auteur1, date1 = :date1,
                        indice2 = :indice2, image2 = :image2, imgcrop2 = :imgcrop2, auteur2 = :auteur2, date2 = :date2,
                        indice3 = :indice3, image3 = :image3, imgcrop3 = :imgcrop3, auteur3 = :auteur3, date3 = :date3,
                        recompense = :recompense, image4 = :image4, imgcrop4 = :imgcrop4, auteur4 = :auteur4, date4 = :date4,
                        legende = :legende WHERE id = :id');
  $req->execute(array(
    'mot' =>$_POST['sqlmot' . $i],

    'image0'=>$_POST['sqlimage0'. $i],
    'imgcrop0'=> "enigme/" . $StrNum . $i . '/image/image0-crop.jpg',
    'auteur0' => $_POST['sqlauteur0'. $i],
    'date0' => $_POST['sqldate0' . $i],

    'indice1'=>$_POST['sqlindice1' . $i],
    'image1'=>$_POST['sqlimage1' . $i],

    'imgcrop1'=> "enigme/" . $StrNum . $i . '/image/image1-crop.jpg',
    'auteur1' => $_POST['sqlauteur1'. $i],
    'date1' => $_POST['sqldate1'. $i],

    'indice2'=>$_POST['sqlindice2' . $i],
    'image2'=>$_POST['sqlimage2' . $i],

    'imgcrop2'=> "enigme/" . $StrNum . $i . '/image/image2-crop.jpg',
    'auteur2' => $_POST['sqlauteur2'. $i],
    'date2' => $_POST['sqldate2'. $i],

    'indice3'=>$_POST['sqlindice3' . $i],
    'image3'=>$_POST['sqlimage3' . $i],

    'imgcrop3'=> "enigme/" . $StrNum . $i . '/image/image3-crop.jpg',
    'auteur3' => $_POST['sqlauteur3'. $i],
    'date3' => $_POST['sqldate3'. $i],

    'recompense'=>$_POST['sqlrecompense' . $i],
    'image4'=>$_POST['sqlimage4' . $i],

    'imgcrop4'=> "enigme/" . $StrNum . $i . '/image/image4-crop.jpg',
    'auteur4' => $_POST['sqlauteur4'. $i],
    'date4' => $_POST['sqldate4'. $i],

    'legende'=>$_POST['sqllegende' . $i],
  	'id' => $i,
  	));

    $jsonFormat = array(
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
        $fichier = fopen("enigme/" . $StrNum . $i . "/enigma.json", "w+");
        fputs($fichier, $json_string = json_encode($jsonFormat, JSON_UNESCAPED_UNICODE | JSON_PRETTY_PRINT));
        fclose($fichier);

$i++;
}

// COPIE DES ENIGMES DANS LE BON DOSSIER
$dir_source = 'enigme';
$dir_dest = '../_enigmasNewForm/enigme';

if (!file_exists($dir_dest)) {mkdir($dir_dest, 0755);}

$dir_iterator = new RecursiveDirectoryIterator($dir_source, RecursiveDirectoryIterator::SKIP_DOTS);

$iterator = new RecursiveIteratorIterator($dir_iterator, RecursiveIteratorIterator::SELF_FIRST);

foreach($iterator as $element){

   if($element->isDir()){
      mkdir($dir_dest . DIRECTORY_SEPARATOR . $iterator->getSubPathName());
   } else{
      copy($element, $dir_dest . DIRECTORY_SEPARATOR . $iterator->getSubPathName());
   }
}
?>
