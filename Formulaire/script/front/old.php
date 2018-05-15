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
$reponse = $bdd->query('SELECT * FROM motus');
// On affiche chaque entrée une à une

while ($donnees = $reponse->fetch())
{
?>
      <!-- Input MOT -->
      <p>
          <label for="mot">Mot à trouver</label> : <br>
          <input type="text" name="sqlmot" id="sqlmot" value="<?php echo $donnees['mot']; ?>">
      </p>
      <details>
      <summary>ÉDITER</summary>
      <!-- Input INDICE 1 -->
      <p>
          <label for="indice1">Indice 1</label> : <br>
          <input type="text" name="sqlindice1" id="sqlindice1" value="<?php echo $donnees['indice1']; ?>">
      </p>
      <!-- Input IMAGE INDICE 1 -->
      <p>
          <label for="image1">image indice 1</label> : <br>
          <input type="url" name="sqlimage1" id="sqlimage1" class="url_input" value="<?php echo $donnees['image1']; ?>">
      </p>
      <!-- Input INDICE 2 -->
      <p>
          <label for="indice2">Indice 2</label> : <br>
          <input type="text" name="sqlindice2" id="sqlindice2" value="<?php echo $donnees['indice2']; ?>">
      </p>
      <!-- Input IMAGE INDICE 2 -->
      <p>
          <label for="image2">image indice 2</label> : <br>
          <input type="url" name="sqlimage2" id="sqlimage2" class="url_input" value="<?php echo $donnees['image2']; ?>">
      </p>
      <!-- Input INDICE 3 -->
      <p>
          <label for="indice3">Indice 3</label> : <br>
          <input type="text" name="sqlindice3" id="sqlindice3" value="<?php echo $donnees['indice3']; ?>">
      </p>
      <!-- Input IMAGE INDICE 3 -->
      <p>
          <label for="image3">image indice 3</label> : <br>
          <input type="url" name="sqlimage3" id="sqlimage3" class="url_input" value="<?php echo $donnees['image3']; ?>">
      </p>
      <!-- Input RECOMPENSE -->
      <p>
          <label for="recompense">Recompense</label> : <br>
          <input type="text" name="sqlrecompense" id="sqlrecompense" value="<?php echo $donnees['recompense']; ?>">
      </p>
      <!-- Input image RECOMPENSE -->
      <p>
          <label for="image4">image Recompense</label> : <br>
          <input type="url" name="sqlimage4" id="sqlimage4" class="url_input" value="<?php echo $donnees['image4']; ?>">
      </p>
      <!-- Input legende RECOMPENSE -->
      <p>
          <label for="legende">Légende</label> : <br>
          <input type="text" name="sqllegende" id="sqllegende" class="legende_input" value="<?php echo $donnees['legende']; ?>">
      </p>
      </details>
      <p> --------------------------------------------------------------------------------------------------------------------</p>
  <?php
}
$reponse->closeCursor(); // Termine le traitement de la requête
?>
