
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
$reponse = $bdd->query('SELECT * FROM enigme ORDER BY id');
$query = $bdd->query('SELECT MAX(id) AS maxval FROM enigme');
$max_row = $query->fetch(PDO::FETCH_ASSOC);

$max = $max_row['maxval'];

if ($max == null)
{
  $num = 0;
}
else
{
  $num = $max + 1;
}

// Verifie si les images sont valable
error_mess($_POST['image0'], 0);
error_mess($_POST['image1'], 1);
error_mess($_POST['image2'], 2);
error_mess($_POST['image3'], 3);
error_mess($_POST['image4'], 4);
if (verif_image($_POST['image1']) && verif_image($_POST['image2']) && verif_image($_POST['image3']) && verif_image($_POST['image4']) && verif_image($_POST['image0'])) {
  // SI OUI Creation des dossiers et fichiers JSON + Upload les images
  $tmp = "enigme";
  if (file_exists($tmp) == false) {
      mkdir("./" . $tmp, 0777, true);
  }

  $long = strlen($num);
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

  if (file_exists($tmp . "/" . $StrNum . $num) == false) {
      mkdir("./" . $tmp . "/" . $StrNum . $num, 0777, true);
    }

    if (file_exists($tmp . "/". $StrNum . $num . "/image") == false) {
      mkdir("./" . $tmp . "/" . $StrNum . $num . "/image", 0777, true);
    }

    // Upload des images
    for ($i=0; $i <= 4; $i++) {
      $url=$_POST['image' . $i];
      $info = new SplFileInfo($url);
      $data = @file_get_contents($url);
      $datacrop = @file_get_contents("tmp/image" . $i . "-crop.jpg");
      $new = $tmp . "/" . $StrNum . $num . '/image/image' . $i . '.' . $info->getExtension();
      $newcrop = $tmp . "/" . $StrNum . $num . '/image/image' . $i . '-crop.jpg';
      file_put_contents($new, $data);
      file_put_contents($newcrop, $datacrop);
      unlink("tmp/image" . $i . "-crop.jpg");
      $imgName[$i] = 'image' . $i . '.' . $info->getExtension();
    }


    date_default_timezone_set('UTC');
    $req = $bdd->prepare('INSERT INTO enigme(id, mot, image0, imgcrop0, auteur0, date0, indice1, image1, imgcrop1, auteur1, date1, indice2, image2, imgcrop2, auteur2, date2, indice3, image3, imgcrop3, auteur3, date3, recompense, image4, imgcrop4, auteur4, date4, legende)
      VALUES(:id, :mot, :image0, :imgcrop0, :auteur0, :date0, :indice1, :image1, :imgcrop1, :auteur1, :date1, :indice2, :image2, :imgcrop2, :auteur2, :date2, :indice3, :image3, :imgcrop3, :auteur3, :date3, :recompense, :image4, :imgcrop4, :auteur4, :date4, :legende)');
    $req->execute(array(
      'id' => $num,
      'mot' => $_POST['mot'],
      'image0'=>$_POST['image0'],
      'imgcrop0'=> $tmp . "/" . $StrNum . $num . '/image/image0-crop.jpg',
      'auteur0' => $_POST['auteur0'],
      'date0' => $_POST['date0'],
      'indice1'=>$_POST['indice1'],
      'image1'=>$_POST['image1'],
      'imgcrop1'=> $tmp . "/" . $StrNum . $num . '/image/image1-crop.jpg',
      'auteur1' => $_POST['auteur1'],
      'date1' => $_POST['date1'],
      'indice2'=>$_POST['indice2'],
      'image2'=>$_POST['image2'],
      'imgcrop2'=> $tmp . "/" . $StrNum . $num . '/image/image2-crop.jpg',
      'auteur2' => $_POST['auteur2'],
      'date2' => $_POST['date2'],
      'indice3'=>$_POST['indice3'],
      'image3'=>$_POST['image3'],
      'imgcrop3'=> $tmp . "/" . $StrNum . $num . '/image/image3-crop.jpg',
      'auteur3' => $_POST['auteur3'],
      'date3' => $_POST['date3'],
      'recompense'=>$_POST['recompense'],
      'image4'=>$_POST['image4'],
      'imgcrop4'=> $tmp . "/" . $StrNum . $num . '/image/image4-crop.jpg',
      'auteur4' => $_POST['auteur4'],
      'date4' => $_POST['date4'],
      'legende'=>$_POST['legende'],
      ));

    // Crée le tableau JSON
    $jsonFormat = array(
        "mot" =>array(
          "titre"=>$_POST['mot'],
          "image"=>$imgName[0],
          "image-crop"=> "image0-crop.jpg",
          "url"=>$_POST['image0'],
          'auteur' => $_POST['auteur0'],
          'date' => $_POST['date0'],
        ),
        "indice"=>array(array(
            "titre"=>$_POST['indice1'],
            "image"=>$imgName[1],
            "image-crop"=> "image1-crop.jpg",
            "url"=>$_POST['image1'],
            'auteur' => $_POST['auteur1'],
            'date' => $_POST['date1'],
          ),
          array(
            "titre"=>$_POST['indice2'],
            "image"=>$imgName[2],
            "image-crop"=> "image2-crop.jpg",
            "url"=>$_POST['image2'],
            'auteur' => $_POST['auteur2'],
            'date' => $_POST['date2'],
          ),
          array(
            "titre"=>$_POST['indice3'],
            "image"=>$imgName[3],
            "image-crop"=> "image3-crop.jpg",
            "url"=>$_POST['image3'],
            'auteur' => $_POST['auteur3'],
            'date' => $_POST['date3'],
        ),),
          "recompense"=>array(
            "indice"=>array(
              "titre"=>$_POST['recompense'],
              "image"=>$imgName[4],
              "image-crop"=> "image4-crop.jpg",
              "url"=>$_POST['image4'],
              'auteur' => $_POST['auteur4'],
              'date' => $_POST['date4'],
            ),
          "legende"=>$_POST['legende'],
          )
        );

// Crée le fichier JSON
$fichier = fopen($tmp . "/" . $StrNum . $num . "/enigma.json", "w+");
fputs($fichier, $json_string = json_encode($jsonFormat, JSON_UNESCAPED_UNICODE | JSON_PRETTY_PRINT));
fclose($fichier);
}
else {
// SI NON Echec de l'enregistrement
echo "Echec de l'enregistrement.";
}

$reponse->closeCursor(); // Termine le traitement de la requête

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
