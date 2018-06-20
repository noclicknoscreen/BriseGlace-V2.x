  <!doctype html>

  <html>
  <head>
      <meta charset="utf-8">
      <title>Formulaire</title>
      <meta name="viewport" content="initial-scale=1.0">
      <meta http-equiv="Pragma" content="no-cache" />
      <meta http-equiv="Cache-Control" content="no-cache, must-revalidate" />
      <meta http-equiv="Expires" content="0" />
      <script type="text/javascript" src="js/jquery.min.js"></script>
      <script type="text/javascript" src="js/jquery.Jcrop.js"></script>
      <script type="text/javascript" src="js/option-image.js"></script>
      <script type="text/javascript" src="js/crop-new.js"></script>
      <script type="text/javascript" src="js/crop-old.js"></script>
      <script type="text/javascript"  src="js/pastille_new.js"></script>
      <script type="text/javascript"  src="js/pastille_old.js"></script>
      <link rel="stylesheet" href="css/jquery.Jcrop.css" type="text/css" />
      <link href="http://fonts.googleapis.com/css?family=Oswald:400,400|Quattrocento+Sans:400,700|PT+Sans:400|Open+Sans Condensed:300" rel="stylesheet" type="text/css">
      <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
      <link rel="stylesheet" href="css/standardize.css">
      <link rel="stylesheet" href="css/index-grid.css">
      <link rel="stylesheet" href="css/index.css">
  </head>
  <body class="body page-index clearfix">

<script type="text/javascript">

$('#copie').on('click', function() {
    location.reload();
});
</script>

<?php
try
{
  $bdd = new PDO('mysql:host=localhost;dbname=formulaire;charset=utf8', 'root', 'root');
}
catch (Exception $e)
{
  die('Erreur : ' . $e->getMessage());
}
$query = $bdd->query('SELECT MAX(id) AS maxval FROM enigme');
$max_row = $query->fetch(PDO::FETCH_ASSOC);
$max = $max_row['maxval'] + 1;
$query->closeCursor(); // Termine le traitement de la requête
?>

    <div class="element element-2"></div>
    <img class="image image-1" src="images/1.png">
    <p class="_input _input-1"><?php echo $max ?> énigmes</p>
    <div class="element element-3"></div>
    <input class="checkbox checkbox-1" id="first_check" name="first_check" onclick="cocher(<?php echo $max ?>)" type="checkbox">
    <p class="text text-1"><strong><strong>LE MOT À TROUVER</strong></strong></p>
    <span class="_text-2"><font color="#fff9f9"><span>Tout cocher</span></font></span>

    <script type="text/javascript">
    function cocher(id)
      {
        if (document.getElementById('first_check').checked == true)
          {
            for (var i = 0; i < id; i++)
              {
                if (document.getElementById('check')) {document.getElementById('check').checked = true;}
                document.getElementById('check' + i).checked = true;
              }
          }
        else
          {
          for (var i = 0; i < id; i++)
            {
              if (document.getElementById('check')) {document.getElementById('check').checked = false;}
              document.getElementById('check' + i).checked = false;
            }
          }
      }

    </script>

<?php

  function clearFolder($folder)
  {
      // 1 ouvrir le dossier
      $dossier = opendir($folder);
      //2)Tant que le dossier est aps vide
      while ($fichier = readdir($dossier))
        {
          //3) Sans compter . et ..
          if ($fichier != "." && $fichier != "..")
          {
            //On selectionne le fichier et on le supprime
            $Vidage = $folder.$fichier;
            unlink($Vidage);
          }
        }
        //Fermer le dossier vide
        closedir($dossier);
  }

  require('script/utile/function.php');
  // NOUVELLE ENIGME
  if (isset($_POST['plus']))
  {
      require('script/front/new.php');
      clearFolder("tmp/");
  }
  else if (isset($_POST['submit']))
  {
    require('script/back/create.php');
    echo "<form method=\"post\" action=\"?\"><button class=\"_button _button-1\" name=\"copie\" id=\"copie\"/>METTRE À JOUR</button></form>";
    clearFolder("tmp/");

  }
  else if (isset($_POST['update']))
  {
    require('script/back/update.php');
    echo "<form method=\"post\" action=\"?\"><button class=\"_button _button-1\" name=\"copie\" id=\"copie\"/>Mettre à jour le jeu</button></form>";
    clearFolder("tmp/");
  }
  else if (isset($_POST['copie']))
  {
    require('script/back/copie.php');
    clearFolder("tmp/");
  }
  require('script/front/old.php');
  ?>



</body>
</html>
