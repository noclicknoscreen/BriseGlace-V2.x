<?php

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
