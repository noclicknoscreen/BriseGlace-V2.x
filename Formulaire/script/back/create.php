
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
$reponse = $bdd->query('SELECT * FROM motus ORDER BY id');
// Verifie si les images sont valable
error_mess($_POST['image1'], 1);
error_mess($_POST['image2'], 2);
error_mess($_POST['image3'], 3);
error_mess($_POST['image4'], 4);
if (verif_image($_POST['image1']) && verif_image($_POST['image2']) && verif_image($_POST['image3']) && verif_image($_POST['image4'])) {
  // SI OUI Creation des dossiers et fichiers JSON + Upload les images
  $tmp = $_POST['jeux'];
  if (file_exists ($tmp) == false) {
      mkdir("./" . $tmp, 0777, true);
  }

  // Crée numbering.txt
  if (file_exists ($tmp . "/numbering.txt") == false)
  {
    $numbering = fopen($tmp . "/numbering.txt", "w+");
    fputs($numbering, "0");
    fclose($numbering);
  }

  $num = file_get_contents($tmp . "/numbering.txt");

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

  if (file_exists ($tmp . "/" . $StrNum . $num) == false) {
      mkdir("./" . $tmp . "/" . $StrNum . $num, 0777, true);
    }

    if (file_exists ($tmp . "/". $StrNum . $num . "/image") == false) {
      mkdir("./" . $tmp . "/" . $StrNum . $num . "/image", 0777, true);
    }

    // Upload des images
    for ($i=1; $i <= 4; $i++) {
      $url=$_POST['image' . $i];
      $info = new SplFileInfo($url);
      $data = @file_get_contents($url);
      $new = $tmp . "/" . $StrNum . $num . '/image/image' . $i . '.' . $info->getExtension();
      file_put_contents($new, $data);
      $imgName[$i] = 'image' . $i . '.' . $info->getExtension();
    }

    date_default_timezone_set('UTC');
    $req = $bdd->prepare('INSERT INTO motus(id, mot, indice1, image1, auteur1, indice2, image2, auteur2, indice3, image3, auteur3, recompense, image4, auteur4, legende)
                          VALUES(:id, :mot, :indice1, :image1, :auteur1, :indice2, :image2, :auteur2, :indice3, :image3, :auteur3, :recompense, :image4, :auteur4, :legende)');
    $req->execute(array(
      'id' => $num,
      'mot' => $_POST['mot'],
      'indice1'=>$_POST['indice1'],
      'image1'=>$_POST['image1'],
      'auteur1' => 'auteur',
      'indice2'=>$_POST['indice2'],
      'image2'=>$_POST['image2'],
      'auteur2' => 'auteur',
      'indice3'=>$_POST['indice3'],
      'image3'=>$_POST['image3'],
      'auteur3' => 'auteur',
      'recompense'=>$_POST['recompense'],
      'image4'=>$_POST['image4'],
      'auteur4' => 'auteur',
      'legende'=>$_POST['legende'],
      ));

    // Crée le tableau JSON
    $jsonFormat = array(
        "jeux" => $_POST['jeux'],
        "mot" => $_POST['mot'],
        "indice"=>array(array(
            "titre"=>$_POST['indice1'],
            "image"=>$imgName[1],
            "url"=>$_POST['image1'],
          ),
          array(
            "titre"=>$_POST['indice2'],
            "image"=>$imgName[2],
            "url"=>$_POST['image2'],
          ),
          array(
            "titre"=>$_POST['indice3'],
            "image"=>$imgName[3],
            "url"=>$_POST['image3'],
        ),),
          "recompense"=>array(
            "indice"=>array(
              "titre"=>$_POST['recompense'],
              "image"=>$imgName[4],
              "url"=>$_POST['image4'],
            ),
          "legende"=>$_POST['legende'],
          )
        );

// Crée le fichier JSON
$fichier = fopen($tmp . "/" . $StrNum . $num . "/enigma.json", "w+");
fputs($fichier, $json_string = json_encode($jsonFormat, JSON_UNESCAPED_UNICODE | JSON_PRETTY_PRINT));
fclose($fichier);

// Numerotation des enigmes
$num = $num + 1;
$text = fopen($tmp . "/numbering.txt", "w+");
fputs($text, $num);
fclose($text);

echo "<p>Enigme enregistrer !</p>";
}
else {
// SI NON Echec de l'enregistrement
echo "Echec de l'enregistrement.";
}

$reponse->closeCursor(); // Termine le traitement de la requête

?>
