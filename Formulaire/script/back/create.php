
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
$query = $bdd->query('SELECT MAX(id) AS maxval FROM enigme');
$max_row = $query->fetch(PDO::FETCH_ASSOC);
$max = $max_row['maxval'];
$query->closeCursor();

if ($max == null)
{
  $num = 0;
}
else
{
  $num = $max + 1;
}

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
  if (file_exists("tmp/image" . $i . "-crop.jpg")) {unlink("tmp/image" . $i . "-crop.jpg");}
  $imgName[$i] = 'image' . $i . '.' . $info->getExtension();
}

if (@$_POST['check']) { $actif = "on"; }
else { $actif = "off"; }

date_default_timezone_set('UTC');
   $req = $bdd->prepare('INSERT INTO enigme(id, mot, theme, image0, imgcrop0, auteur0, date0, indice1, image1, imgcrop1, auteur1, date1, indice2, image2, imgcrop2, auteur2, date2, indice3, image3, imgcrop3, auteur3, date3, recompense, image4, imgcrop4, auteur4, date4, legende, actif)
      VALUES(:id, :mot, :theme, :image0, :imgcrop0, :auteur0, :date0, :indice1, :image1, :imgcrop1, :auteur1, :date1, :indice2, :image2, :imgcrop2, :auteur2, :date2, :indice3, :image3, :imgcrop3, :auteur3, :date3, :recompense, :image4, :imgcrop4, :auteur4, :date4, :legende, :actif)');
    $req->execute(array(
      'id' => $num,
      'mot' => $_POST['mot'],
      'theme' => $_POST['theme'],
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
      'actif'=>$actif,
      ));

    // Crée le tableau JSON
    $jsonFormat = array(
        "theme"=>$_POST['theme'],
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
?>
