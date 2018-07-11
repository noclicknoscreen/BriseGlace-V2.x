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
            if ($data != NULL)
            {
              if ($info->getExtension() == NULL)
              {
                $new = "enigme/" . $StrNum . $id . '/image/image' . $j . '.jpg';
              }
              else {
                $new = "enigme/" . $StrNum . $id . '/image/image' . $j . '.' . $info->getExtension();
              }
              file_put_contents($new, $data);
            }
          }
    if (file_exists("enigme/" . $StrNum . $id . '/image/image' . $j))
      {
        unlink("enigme/" . $StrNum . $id . '/image/image' . $j);
      }
    $imgName[$j] = 'image' . $j . '.' . $info->getExtension();
  }

$actif = "off";
if (isset($_POST['check' . $i]))
{
  $actif = "on";
}
 else
{
  $actif = "off";
}

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

// UPDATE ENIGME DANS LA BASE DE DONNEE
if ($donnees['mot'] !=  $_POST['sqlmot' . $i])
{
  $req = $bdd->query('UPDATE enigme SET mot = "'.$_POST['sqlmot' . $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['theme'] != $_POST['sqltheme' . $i])
{
  $req = $bdd->query('UPDATE enigme SET theme = "'.$_POST['sqltheme' . $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['image0'] != $_POST['sqlimage0'. $i])
{
  $req = $bdd->query('UPDATE enigme SET image0 = "'.$_POST['sqlimage0'. $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['imgcrop0'] != $imgcrop0)
{
  $req = $bdd->query('UPDATE enigme SET imgcrop0 = "'.$imgcrop0.'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['auteur0'] != $_POST['sqlauteur0'. $i])
{
  $req = $bdd->query('UPDATE enigme SET auteur0 = "'.$_POST['sqlauteur0'. $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['date0'] != $_POST['sqldate0' . $i])
{
  $req = $bdd->query('UPDATE enigme SET date0 = "'.$_POST['sqldate0' . $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}

// UPDATE INDICE 2

if ($donnees['indice1'] != $_POST['sqlindice1' . $i])
{
  $req = $bdd->query('UPDATE enigme SET indice1 = "'.$_POST['sqlindice1' . $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['image1'] != $_POST['sqlimage1' . $i])
{
  $req = $bdd->query('UPDATE enigme SET image1 = "'.$_POST['sqlimage1' . $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['imgcrop1'] != $imgcrop1)
{
  $req = $bdd->query('UPDATE enigme SET imgcrop1 = "'.$imgcrop1.'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['auteur1'] != $_POST['sqlauteur1'. $i])
{
  $req = $bdd->query('UPDATE enigme SET auteur1 = "'.$_POST['sqlauteur1'. $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['date1'] != $_POST['sqldate1'. $i])
{
  $req = $bdd->query('UPDATE enigme SET date1 = "'.$_POST['sqldate1'. $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}

// UPDATE INDICE 2

if ($donnees['indice2'] != $_POST['sqlindice2' . $i])
{
  $req = $bdd->query('UPDATE enigme SET indice2 = "'.$_POST['sqlindice2' . $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['image2'] != $_POST['sqlimage2' . $i])
{
  $req = $bdd->query('UPDATE enigme SET image2 = "'.$_POST['sqlimage2' . $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['imgcrop2'] != $imgcrop2)
{
  $req = $bdd->query('UPDATE enigme SET imgcrop2 = "'.$imgcrop2.'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['auteur2'] != $_POST['sqlauteur2'. $i])
{
  $req = $bdd->query('UPDATE enigme SET auteur2 = "'.$_POST['sqlauteur2'. $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['date2'] != $_POST['sqldate2'. $i])
{
  $req = $bdd->query('UPDATE enigme SET date2 = "'.$_POST['sqldate2'. $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}

// UPDATE INDICE 3

if ($donnees['indice3'] != $_POST['sqlindice3' . $i])
{
  $req = $bdd->query('UPDATE enigme SET indice3 = "'.$_POST['sqlindice3' . $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['image3'] != $_POST['sqlimage3' . $i])
{
  $req = $bdd->query('UPDATE enigme SET image3 = "'.$_POST['sqlimage3' . $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['imgcrop3'] != $imgcrop3)
{
  $req = $bdd->query('UPDATE enigme SET imgcrop3 = "'.$imgcrop3.'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['auteur3'] != $_POST['sqlauteur3'. $i])
{
  $req = $bdd->query('UPDATE enigme SET auteur3 = "'.$_POST['sqlauteur3'. $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['date3'] != $_POST['sqldate3'. $i])
{
  $req = $bdd->query('UPDATE enigme SET date3 = "'.$_POST['sqldate3'. $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}

// UPDATE RECOMPENSE

if ($donnees['recompense'] != $_POST['sqlrecompense' . $i])
{
  $req = $bdd->query('UPDATE enigme SET recompense = "'.$_POST['sqlrecompense' . $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['image4'] != $_POST['sqlimage4' . $i])
{
  $req = $bdd->query('UPDATE enigme SET image4 = "'.$_POST['sqlimage4' . $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['imgcrop4'] != $imgcrop4)
{
  $req = $bdd->query('UPDATE enigme SET imgcrop4 = "'.$imgcrop4.'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['auteur4'] != $_POST['sqlauteur4'. $i])
{
  $req = $bdd->query('UPDATE enigme SET auteur4 = "'.$_POST['sqlauteur4'. $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['date4'] != $_POST['sqldate4'. $i])
{
  $req = $bdd->query('UPDATE enigme SET date4 = "'.$_POST['sqldate4'. $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}
if ($donnees['legende'] != $_POST['sqllegende' . $i])
{
  $legende = str_replace('"', '\"', $_POST['sqllegende' . $i] );
  $req = $bdd->query('UPDATE enigme SET legende = "'.$legende.'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}

// UPDATE STATUT

if ($donnees['complet'] != $_POST['sqlcomplet' . $i])
{
  $req = $bdd->query('UPDATE enigme SET complet = "'.$_POST['sqlcomplet' . $i].'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}

if ($donnees['actif'] != $actif)
{
  $req = $bdd->query('UPDATE enigme SET actif = "'.$actif.'" WHERE id = "' . $id . '"');
  $req->closeCursor();
}


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
