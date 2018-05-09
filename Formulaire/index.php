  <!doctype html>

  <html>
  <head>
      <meta charset="utf-8">
      <link rel="stylesheet" href="css/IndexStyle.css" />
      <title>Formulaire</title>
  </head>

  <body>
      <form action="?" method="POST">
          <h1>Enigme</h1>
          <!-- Input JEUX  -->
          <p>
              <label for="jeux">Jeux :</label>
              <select name="jeux" id="jeux" value="<?php if (isset($_POST['jeux'])){echo $_POST['jeux'];} ?>">
                  <!-- choix du jeux  -->
                  <option value = "motus">Motus</option>
                  <option value = "labyrinthe">Labyrinthe</option>
                  <option value = "rebu">Rebu</option>
              </select>
          </p>
          <!-- Input MOT -->
          <p>
              <label for="mot">Mot à trouver</label> :
              <input type="text" name="mot" id="mot" value="<?php if (isset($_POST['mot'])){echo $_POST['mot'];} ?>" required>
          </p>
          <!-- Input INDICE 1 -->
          <p>
              <label for="indice1">Indice 1</label> :
              <input type="text" name="indice1" id="indice1" value="<?php if (isset($_POST['indice1'])){echo $_POST['indice1'];} ?>" required>
          </p>
          <!-- Input IMAGE INDICE 1 -->
          <p>
              <label for="photo1">Photo indice 1</label> :
              <input type="url" name="photo1" id="photo1" class="url_input" value="<?php if (isset($_POST['photo1'])){echo $_POST['photo1'];} ?>" required>
              <input type="submit" name="p1" id="p1" value="Afficher" />

              <!-- Quand on clique sur "Afficher" verifie si la photo existe si oui l'affiche -->
              <?php
              if (isset($_POST['p1']))
              {
                error_mess($_POST['photo1'], 1);
                if (verif_photo($_POST['photo1'])) {
                  ?>
                  <details open="true">
                    <summary></summary>
                    <img src=<?php if (isset($_POST['photo1'])){echo $_POST['photo1'];} ?> width="400" height="300"/></br>
                  </details>
                  <?php
                }
              }
              ?>
          </p>
          <!-- Input INDICE 2 -->
          <p>
              <label for="indice2">Indice 2</label> :
              <input type="text" name="indice2" id="indice2" value="<?php if (isset($_POST['indice2'])){echo $_POST['indice2'];} ?>" required>
          </p>
          <!-- Input IMAGE INDICE 2 -->
          <p>
              <label for="photo2">Photo indice 2</label> :
              <input type="url" name="photo2" id="photo2" class="url_input" value="<?php if (isset($_POST['photo2'])){echo $_POST['photo2'];} ?>" required>
              <input type="submit" name="p2" id="p2" value="Afficher" />

              <!-- Quand on clique sur "Afficher" verifie si la photo existe si oui l'affiche -->
              <?php
              if (isset($_POST['p2']))
              {
                error_mess($_POST['photo2'], 2);
                if (verif_photo($_POST['photo2'])) {
                  ?>
                  <details open="true">
                    <summary></summary>
                    <img src=<?php if (isset($_POST['photo2'])){echo $_POST['photo2'];} ?> width="400" height="300"/></br>
                  </details>
                  <?php
                }
              }
              ?>
          </p>
          <!-- Input INDICE 3 -->
          <p>
              <label for="indice3">Indice 3</label> :
              <input type="text" name="indice3" id="indice3" value="<?php if (isset($_POST['indice3'])){echo $_POST['indice3'];} ?>" required>
          </p>
          <!-- Input IMAGE INDICE 3 -->
          <p>
              <label for="photo3">Photo indice 3</label> :
              <input type="url" name="photo3" id="photo3" class="url_input" value="<?php if (isset($_POST['photo3'])){echo $_POST['photo3'];} ?>" required>
              <input type="submit" name="p3" id="p3" value="Afficher" />

              <!-- Quand on clique sur "Afficher" verifie si la photo existe si oui l'affiche -->
              <?php
              if (isset($_POST['p3']))
              {
                error_mess($_POST['photo3'], 3);
                if (verif_photo($_POST['photo3'])) {
                  ?>
                  <details open="true">
                    <summary></summary>
                    <img src=<?php if (isset($_POST['photo3'])){echo $_POST['photo3'];} ?> width="400" height="300"/></br>
                  </details>
                  <?php
                }
              }
              ?>
          </p>
          <!-- Input RECOMPENSE -->
          <p>
              <label for="recompense">Recompense</label> :
              <input type="text" name="recompense" id="recompense" value="<?php if (isset($_POST['recompense'])){echo $_POST['recompense'];} ?>" required>
          </p>
          <!-- Input PHOTO RECOMPENSE -->
          <p>
              <label for="photo4">Photo Recompense</label> :
              <input type="url" name="photo4" id="photo4" class="url_input" value="<?php if (isset($_POST['photo4'])){echo $_POST['photo4'];} ?>" required>
              <input type="submit" name="p4" id="p4" value="Afficher" />

              <!-- Quand on clique sur "Afficher" verifie si la photo existe si oui l'affiche -->
              <?php
              if (isset($_POST['p4']))
              {
                error_mess($_POST['photo4'], 4);
                if (verif_photo($_POST['photo4'])) {
                  ?>
                  <details open="true">
                    <summary></summary>
                    <img src=<?php if (isset($_POST['photo4'])){echo $_POST['photo4'];} ?> width="400" height="300"/></br>
                  </details>
                  <?php
                  }
                }
              ?>
          </p>
          <!-- BOUTTON -->
          <div class="button">
          <input type="submit" name="preview" value="Previsualiser" />
          <input type="submit" name="submit" value="Envoyer" />
          </div>
      </form>

  <!-- PHP -> conversion en JSON si tout les elements sont OK ! -->

  <?php
  // SI BOUTTON PREVIEW
  if (isset($_POST['preview']))
  {
    echo $_POST['jeux'] . "<br/>";
    echo $_POST['mot'] . "<br/>";
    echo $_POST['indice1'] . "<br/>";
    echo '<img src="' . $_POST['photo1'] . '" width="500" height="300" /><br/>';
    echo $_POST['indice2'] . "<br/>";
    echo '<img src="'. $_POST['photo2'] . '" width="500" height="300" /><br/>';
    echo $_POST['indice3'] . "<br/>";
    echo '<img src="'. $_POST['photo3'] . '" width="500" height="300" /><br/>';
    echo $_POST['recompense'] . "<br/>";
    echo '<img src="'. $_POST['photo4'] . '" width="500" height="300" /><br/>';
  }
  // SI BOUTTON ENVOYER
  if (isset($_POST['submit']))
  {
    // Verifie si les photos sont valable
    error_mess($_POST['photo1'], 1);
    error_mess($_POST['photo2'], 2);
    error_mess($_POST['photo3'], 3);
    error_mess($_POST['photo4'], 4);
    if (verif_photo($_POST['photo1']) && verif_photo($_POST['photo2']) && verif_photo($_POST['photo3']) && verif_photo($_POST['photo4'])) {
      // SI OUI Creation des dossiers et fichiers JSON + Upload les images
      $tmp = $_POST['jeux'];
      if (file_exists ($tmp) == false) {
          mkdir("./" . $tmp, 0777, true);
      }
      $num = file_get_contents($tmp . "/info.txt");

      if (file_exists ($tmp . "/" . $num) == false) {
          mkdir("./" . $tmp . "/" . $num, 0777, true);
        }

        if (file_exists ($tmp . "/" . $num . "/image") == false) {
          mkdir("./" . $tmp . "/" . $num . "/image", 0777, true);
        }

        // Upload des images
        for ($i=1; $i <= 4; $i++) {
          $url=$_POST['photo' . $i];
          $info = new SplFileInfo($url);
          $data = @file_get_contents($url);
          $new = $tmp . "/" . $num . '/image/image' . $i . '.' . $info->getExtension();
          file_put_contents($new, $data);
          $imgName[$i] = 'image' . $i . '.' . $info->getExtension();
        }

        // Crée le tableau JSON
        $jsonFormat = array(
          "Jeux" => $_POST['jeux'],
          "mot" => $_POST['mot'],
          "indice1"=>array(
              "nom"=>$_POST['indice1'],
              "photo"=>$imgName[1],
            ),
            "indice2"=>array(
              "nom"=>$_POST['indice2'],
              "photo"=>$imgName[2],
            ),
            "indice3"=>array(
              "nom"=>$_POST['indice3'],
              "photo"=>$imgName[3],
            ),
            "recompense"=>array(
              "description"=>$_POST['recompense'],
              "photo"=>$imgName[4],
            )
            );

  // Crée le fichier JSON
    $fichier = fopen($tmp . "/" . $num . "/enigme.json", "w+");
    fputs($fichier, $json_string = json_encode($jsonFormat, JSON_PRETTY_PRINT));
    fclose($fichier);

  // Numerotation des enigmes
    $num = $num + 1;
    $text = fopen($tmp . "/info.txt", "w+");
    fputs($text, $num);
    fclose($text);

    echo "<p>Enigme enregistrer !</p>";
  }
  else {
    // SI NON Echec de l'enregistrement
    echo "Echec de l'enregistrement. Verifier vos images avec les boutons \"Afficher\" !";
  }
  }

  // Fonction

  //Verification des IMAGES

  //Renvoie "True" ou "False"
  function verif_photo($photo)
  {
    $url=$photo;
    $info = new SplFileInfo($url);
    if (urlExist($url)) {
      $data = @file_get_contents($url);
      if ($info->getExtension() == "jpg" || $info->getExtension() == "jpeg" || $info->getExtension() == "png"|| $info->getExtension() == "gif") { return true; }
        else { return false; }
      }
      else { return false; }
  }

  // Affiche les messages d'erreur concernant les images
  function error_mess($photo, $nbPhoto)
  {
    $url=$photo;
    $info = new SplFileInfo($url);
    if (urlExist($url)) {
      $data = @file_get_contents($url);
      if ($info->getExtension() == "jpg" || $info->getExtension() == "jpeg" || $info->getExtension() == "png"|| $info->getExtension() == "gif") {
          return true;
        }
        else { echo "Echec du Chargement de la photo " . $nbPhoto . " : ce n'est pas une image !<br>"; }
      }
      else { echo "Echec du Chargement de la photo " . $nbPhoto . " : le lien n'existe pas !<br>"; }
  }

// Verifie si le lien existe
  function urlExist($url) {
      $file_headers = @get_headers($url);
      if($file_headers[0] == 'HTTP/1.1 404 Not Found')
         return false;

      return true;
  }
   ?>

<!-- JS Gestion des required -->
     <script type="text/javascript">
       for (var i = 1; i <= 4; i++) {
         document.getElementById( "p" + i ).addEventListener( "click" , function() {
           document.getElementById( "mot" ).removeAttribute( "required" );
           document.getElementById( "indice1" ).removeAttribute( "required" );
           document.getElementById( "indice2" ).removeAttribute( "required" );
           document.getElementById( "indice3" ).removeAttribute( "required" );
           document.getElementById( "recompense" ).removeAttribute( "required" );
           document.getElementById( "photo1").removeAttribute( "required" );
           document.getElementById( "photo2").removeAttribute( "required" );
           document.getElementById( "photo3").removeAttribute( "required" );
           document.getElementById( "photo4").removeAttribute( "required" );
           }
         );
       }
        document.getElementById("submit", "preview").addEventListener( "click" , function() {
          document.getElementById( "mot" ).setAttribute( "required" );
          document.getElementById( "indice1" ).setAttribute( "required" );
          document.getElementById( "indice2" ).setAttribute( "required" );
          document.getElementById( "indice3" ).setAttribute( "required" );
          document.getElementById( "recompense" ).setAttribute( "required" );
          document.getElementById( "photo1").setAttribute( "required" );
          document.getElementById( "photo2").setAttribute( "required" );
          document.getElementById( "photo3").setAttribute( "required" );
          document.getElementById( "photo4").setAttribute( "required" );
        } );
     </script>

  </body>
  </html>
