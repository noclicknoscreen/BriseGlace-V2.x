<?php

// NON UTILISE

// Fonction

//Verification des IMAGES

//Renvoie "True" ou "False"
function verif_image($image)
{
  $url=$image;
  $info = new SplFileInfo($url);
  if (urlExist($url)) {
      $data = @file_get_contents($url);
      if ($data != NULL) {
          if ($info->getExtension() == "jpg" || $info->getExtension() == "jpeg" || $info->getExtension() == "png"|| $info->getExtension() == "gif" || $info->getExtension() == "JPG")
          {
            return true;
          }
            else { return false; }
        }
        else {return false; }
      }
    else { return false; }
}

// Affiche les messages d'erreur concernant les images
function error_mess($image, $nbimage)
{
  $url=$image;
  $info = new SplFileInfo($url);
  if (urlExist($url)) {
      $data = @file_get_contents($url);
      if ($data != NULL)
        {
          if ($info->getExtension() == "jpg" || $info->getExtension() == "jpeg" || $info->getExtension() == "png"|| $info->getExtension() == "gif" || $info->getExtension() == "JPG") {
            return true;
          }
          else { echo "Echec du Chargement de la image " . $nbimage . " : ce n'est pas une image !<br>"; }
        }
      else { echo "Echec du Chargement de la image " . $nbimage . " : image vide !<br>"; }
    }
   else { echo "Echec du Chargement de la image " . $nbimage . " : le lien n'existe pas !<br>"; }
}

// Verifie si le lien existe
function urlExist($url) {
    $file_headers = @get_headers($url);
    if($file_headers[0] == 'HTTP/1.1 404 Not Found')
    {
       return false;
     }
    return true;
}

?>
