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

// On affiche chaque entrée une à une

$i = 0;
while ($donnees = $reponse->fetch())
{
?>
      <p> --------------------------------------------------------------------------------------------------------------------</p>
      <!-- Input MOT -->
      <p>
          <label for="mot">Mot à trouver</label> : <br>
          <input type="text" name="sqlmot<?php echo $i?>" id="sqlmot<?php echo $i?>" value="<?php if (isset($_POST['sqlmot' . $i])){echo $_POST['sqlmot' . $i];} else {echo $donnees['mot'];} ?>">
      </p>
      <details>
      <summary>ÉDITER</summary>
      <!-- Input INDICE 1 -->
      <p>
          <label for="indice1">Indice 1</label> : <br>
          <input type="text" name="sqlindice1<?php echo $i?>" id="sqlindice1<?php echo $i?>" value="<?php if (isset($_POST['sqlindice1' . $i])){echo $_POST['sqlindice1' . $i];} else {echo $donnees['indice1'];} ?>">
      </p>
      <!-- Input IMAGE INDICE 1 -->
      <p>
          <label for="image1">image indice 1</label> : <br>
          <input type="url" name="sqlimage1<?php echo $i?>" id="sqlimage1<?php echo $i?>" class="url_input" value="<?php if (isset($_POST['sqlimage1' . $i])){echo $_POST['sqlimage1' . $i];} else {echo $donnees['image1'];} ?>">
      </p>
      <!-- Input INDICE 2 -->
      <p>
          <label for="indice2">Indice 2</label> : <br>
          <input type="text" name="sqlindice2<?php echo $i?>" id="sqlindice2<?php echo $i?>" value="<?php if (isset($_POST['sqlindice2' . $i])){echo $_POST['sqlindice2' . $i];} else {echo $donnees['indice2'];} ?>">
      </p>
      <!-- Input IMAGE INDICE 2 -->
      <p>
          <label for="image2">image indice 2</label> : <br>
          <input type="url" name="sqlimage2<?php echo $i?>" id="sqlimage2<?php echo $i?>" class="url_input" value="<?php if (isset($_POST['sqlimage2' . $i])){echo $_POST['sqlimage2' . $i];} else {echo $donnees['image2'];} ?>">
      </p>
      <!-- Input INDICE 3 -->
      <p>
          <label for="indice3">Indice 3</label> : <br>
          <input type="text" name="sqlindice3<?php echo $i?>" id="sqlindice3<?php echo $i?>" value="<?php if (isset($_POST['sqlindice3' . $i])){echo $_POST['sqlindice3' . $i];} else {echo $donnees['indice3'];} ?>">
      </p>
      <!-- Input IMAGE INDICE 3 -->
      <p>
          <label for="image3">image indice 3</label> : <br>
          <input type="url" name="sqlimage3<?php echo $i?>" id="sqlimage3<?php echo $i?>" class="url_input" value="<?php if (isset($_POST['sqlimage3' . $i])){echo $_POST['sqlimage3' . $i];} else {echo $donnees['image3'];} ?>">
      </p>
      <!-- Input RECOMPENSE -->
      <p>
          <label for="recompense">Recompense</label> : <br>
          <input type="text" name="sqlrecompense<?php echo $i?>" id="sqlrecompense<?php echo $i?>" value="<?php if (isset($_POST['sqlrecompense' . $i])){echo $_POST['sqlrecompense' . $i];} else {echo $donnees['recompense'];} ?>">
      </p>
      <!-- Input image RECOMPENSE -->
      <p>
          <label for="image4">image Recompense</label> : <br>
          <input type="url" name="sqlimage4<?php echo $i?>" id="sqlimage4<?php echo $i?>" class="url_input" value="<?php if (isset($_POST['sqlimage4' . $i])){echo $_POST['sqlimage4' . $i];} else {echo $donnees['image4'];} ?>">
      </p>
      <!-- Input legende RECOMPENSE -->
      <p>
          <label for="legende">Légende</label> : <br>
          <textarea name="sqllegende<?php echo $i?>" id="sqllegende<?php echo $i?>" class="legende_input"><?php if (isset($_POST['sqllegende' . $i])){echo $_POST['sqllegende' . $i];} else {echo $donnees['legende'];} ?></textarea>      </p>
      </details>
  <?php
$i++;
}
$reponse->closeCursor(); // Termine le traitement de la requête
?>
