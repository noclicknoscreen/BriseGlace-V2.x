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
function handleSubmit(){
    document.getElementById("form1").submit();
}

function delaySubmit(){
    window.setTimeout(handleSubmit, 2000); // change this to whatever delay you need
};

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

  <form  action="?" method="POST" id="form1" name="form1">

  <div class="element element-2"></div>

  <button class="_button _button-1" name="copie" id="copie"/>Mettre à jour le jeu</button>

  <img class="image image-1" src="images/1.png">
  <p class="_input _input-1"><?php echo $max ?> énigmes</p>
  <div class="element element-3"></div>



  <input id="chercher" name="chercher" class="-select -select-1 js-chercher" onkeyup="delaySubmit()" placeholder="mot clé" type="text" value="<?php if(isset($_POST['chercher'])) {echo $_POST['chercher'];}?>">

  <select id="selectTable" name="selectTable" class="-select -select-2 js-select-table" type="text" onChange="submit()">
    <option value="mot" <?php if(!isset($_POST['selectTable'])) {echo "selected";}?>>mot</option>
    <option value="theme" <?php if(isset($_POST['selectTable']) && !strcmp($_POST['selectTable'], "theme")) {echo "selected";}?>>theme</option>
    <option value="indice" <?php if(isset($_POST['selectTable']) && !strcmp($_POST['selectTable'], "indice")) {echo "selected";}?>>indice</option>
    <option value="image" <?php if(isset($_POST['selectTable']) && !strcmp($_POST['selectTable'], "image")) {echo "selected";}?>>image</option>
    <option value="auteur" <?php if(isset($_POST['selectTable']) && !strcmp($_POST['selectTable'], "auteur")) {echo "selected";}?>>auteur</option>
    <option value="date" <?php if(isset($_POST['selectTable']) && !strcmp($_POST['selectTable'], "date")) {echo "selected";}?>>date</option>
    <option value="recompense" <?php if(isset($_POST['selectTable']) && !strcmp($_POST['selectTable'], "recompense")) {echo "selected";}?>>gagné</option>
    <option value="legende" <?php if(isset($_POST['selectTable']) && !strcmp($_POST['selectTable'], "legende")) {echo "selected";}?>>legende</option>
  <select>


  <select id="trier" name="trier" class="-select -select-3 js-trier" onChange="submit()">
    <option value="id" <?php if(!isset($_POST['trier'])) {echo "selected";}?>>Trier par</option>
    <option value="mot" <?php if(isset($_POST['trier']) && !strcmp($_POST['trier'], "mot")) {echo "selected";}?>>Mot: par ordre croissant</option>
    <option value="mot DESC" <?php if(isset($_POST['trier']) && !strcmp($_POST['trier'], "mot DESC")) {echo "selected";}?>>Mot: par ordre décroissant</option>
    <option value="id" <?php if(isset($_POST['trier']) && !strcmp($_POST['trier'], "id")) {echo "selected";}?>>id: par ordre croissant</option>
    <option value="id DESC" <?php if(isset($_POST['trier']) && !strcmp($_POST['trier'], "id DESC")) {echo "selected";}?>>id: par ordre décroissant</option>
    <option value="date" <?php if(isset($_POST['trier']) && !strcmp($_POST['trier'], "date")) {echo "selected";}?>>date/heure: par ordre croissant</option>
    <option value="date DESC" <?php if(isset($_POST['trier']) && !strcmp($_POST['trier'], "date DESC")) {echo "selected";}?>>date/heure: par ordre décroissant</option>
    <option value="complet" <?php if(isset($_POST['trier']) && !strcmp($_POST['trier'], "complet")) {echo "selected";}?>>Enigme complete</option>
    <option value="complet DESC" <?php if(isset($_POST['trier']) && !strcmp($_POST['trier'], "complet DESC")) {echo "selected";}?>>Enigme incomplete</option>
  <select>

    <select type="submit" id="filtrer" name="filtrer" class="-select -select-4 js-filtrer" onChange="submit()">
      <option value="" <?php if(!isset($_POST['filtrer'])) {echo "selected";}?>>Filtrer par</option>
      <option value="on" <?php if(isset($_POST['filtrer']) && !strcmp($_POST['filtrer'], "on")) {echo "selected";}?>>actif</option>
      <option value="off" <?php if(isset($_POST['filtrer']) && !strcmp($_POST['filtrer'], "off")) {echo "selected";}?>>inactif</option>
      <option value="complet" <?php if(isset($_POST['filtrer']) && !strcmp($_POST['filtrer'], "complet")) {echo "selected";}?>>complet</option>
      <option value="incomplet" <?php if(isset($_POST['filtrer']) && !strcmp($_POST['filtrer'], "incomplet")) {echo "selected";}?>>incomplet</option>
    <select>

  <span class="_text-1"><font color="#fff9f9"><span>Tout cocher</span></font></span>

  <input class="checkbox checkbox-1" id="first_check" name="first_check" onclick="cocher(<?php echo $max ?>)" type="checkbox">

  <input type="submit" class="_button _button-2" name="plus" id="plus" value="+"/>
  
  <p class="text text-1"><strong><strong>LE MOT À TROUVER</strong></strong></p>

</form>


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
    ?>
    <script type="text/javascript">
    document.getElementById('filtrer').style.display='none';
    document.getElementById('trier').style.display='none';
    document.getElementById('selectTable').style.display='none';
    document.getElementById('chercher').style.display='none';
    </script>
    <?php
    require('script/front/new.php');
    clearFolder("tmp/");
}
else if (isset($_POST['submit']))
{
  require('script/back/create.php');
  // echo "<form method=\"post\" action=\"?\"><button class=\"_button _button-1\" name=\"copie\" id=\"copie\"/>METTRE À JOUR</button></form>";
  clearFolder("tmp/");
  echo "<meta http-equiv=\"refresh\" content=\"0\">";
}
else if (isset($_POST['update']))
{
  require('script/back/update.php');
  clearFolder("tmp/");
  // echo "<form method=\"post\" action=\"?\"><button class=\"_button _button-1\" name=\"copie\" id=\"copie\"/>Mettre à jour le jeu</button></form>";
  echo "<meta http-equiv=\"refresh\" content=\"0\">";
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
