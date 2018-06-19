<?php

// COPIE DES ENIGMES DANS LE BON DOSSIER
$dir_dest = '../_enigmasNewForm/enigme/';

function RemoveAll ( $path ) {
    foreach ( new DirectoryIterator($path) as $item ):
        if ( $item->isFile() ) unlink($item->getRealPath());
        if ( !$item->isDot() && $item->isDir() ) RemoveAll($item->getRealPath());
    endforeach;
    rmdir($path);
}

if (!file_exists("../_enigmasNewForm")) {mkdir("../_enigmasNewForm/", 0777);}

if (file_exists($dir_dest)) {
  RemoveAll($dir_dest);
  mkdir($dir_dest, 0777);
}
else {
  mkdir($dir_dest, 0777);
}

try
{
  $bdd = new PDO('mysql:host=localhost;dbname=formulaire;charset=utf8', 'root', 'root');
}
catch (Exception $e)
{
  die('Erreur : ' . $e->getMessage());
}

$reponse = $bdd->query("SELECT * FROM enigme ORDER BY id");

while ($donnees = $reponse->fetch())
{

  switch (strlen($donnees['id'])) {
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

  if (!strcmp($donnees['actif'],"on")) {
    mkdir($dir_dest .  $StrNum . $donnees['id'], 0777);
    $dir_tmp = $dir_dest .  $StrNum . $donnees['id'] . "/";
    $dir_source = "enigme/" . $StrNum . $donnees['id'];

    $dir_iterator = new RecursiveDirectoryIterator($dir_source, RecursiveDirectoryIterator::SKIP_DOTS);
    $iterator = new RecursiveIteratorIterator($dir_iterator, RecursiveIteratorIterator::SELF_FIRST);

    foreach($iterator as $element){
       if($element->isDir()){
          @mkdir($dir_tmp . DIRECTORY_SEPARATOR . $iterator->getSubPathName());
       } else{
          copy($element, $dir_tmp . DIRECTORY_SEPARATOR . $iterator->getSubPathName());
       }
     }
}

}

$reponse->closeCursor();

?>
