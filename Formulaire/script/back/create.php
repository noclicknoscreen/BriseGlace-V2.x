
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



date_default_timezone_set('UTC');
   $req = $bdd->prepare('INSERT INTO enigme(id, mot, theme, image0, imgcrop0, auteur0, date0, indice1, image1, imgcrop1, auteur1, date1, indice2, image2, imgcrop2, auteur2, date2, indice3, image3, imgcrop3, auteur3, date3, recompense, image4, imgcrop4, auteur4, date4, legende, complet, actif)
      VALUES(:id, :mot, :theme, :image0, :imgcrop0, :auteur0, :date0, :indice1, :image1, :imgcrop1, :auteur1, :date1, :indice2, :image2, :imgcrop2, :auteur2, :date2, :indice3, :image3, :imgcrop3, :auteur3, :date3, :recompense, :image4, :imgcrop4, :auteur4, :date4, :legende, :complet, :actif)');
    $req->execute(array(
      'id' => $num,
      'mot' => "",
      'theme' => "",
      'image0'=> "",
      'imgcrop0'=> "",
      'auteur0' => "",
      'date0' => "",
      'indice1'=> "",
      'image1'=> "",
      'imgcrop1'=> "",
      'auteur1' => "",
      'date1' => "",
      'indice2'=> "",
      'image2'=> "",
      'imgcrop2'=> "",
      'auteur2' => "",
      'date2' => "",
      'indice3'=> "",
      'image3'=> "",
      'imgcrop3'=> "",
      'auteur3' => "",
      'date3' => "",
      'recompense'=> "",
      'image4'=> "",
      'imgcrop4'=> "",
      'auteur4' => "",
      'date4' => "",
      'legende'=> "",
      'complet'=> "vide",
      'actif'=> "off",
      ));

    // Crée le tableau JSON
    $jsonFormat = array(
        "theme"=>"",
        "mot" =>array(
          "titre"=> "",
          "image"=> "",
          "image-crop"=> "",
          "url"=> "",
          'auteur' => "",
          'date' => "",
        ),
        "indice"=>array(array(
            "titre"=> "",
            "image"=> "",
            "image-crop"=> "",
            "url"=> "",
            'auteur' => "",
            'date' => "",
          ),
          array(
            "titre"=> "",
            "image"=> "",
            "image-crop"=> "",
            "url"=> "",
            'auteur' => "",
            'date' => "",
          ),
          array(
            "titre"=> "",
            "image"=> "",
            "image-crop"=> "",
            "url"=> "",
            'auteur' => "",
            'date' => "",
        ),),
          "recompense"=>array(
            "indice"=>array(
              "titre"=> "",
              "image"=> "",
              "image-crop"=> "",
              "url"=> "",
              'auteur' => "",
              'date' => "",
            ),
          "legende"=> "",
          )
        );

// Crée le fichier JSON
$fichier = fopen($tmp . "/" . $StrNum . $num . "/enigma.json", "w+");
fputs($fichier, $json_string = json_encode($jsonFormat, JSON_UNESCAPED_UNICODE | JSON_PRETTY_PRINT));
fclose($fichier);

?>
