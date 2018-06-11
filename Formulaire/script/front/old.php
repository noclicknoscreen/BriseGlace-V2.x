<script type="text/javascript">

function sqlcropimg(valeurChamp, num) {
  $('#testimg' + num).attr('src', valeurChamp);
  if (document.getElementById('testimg' + num).height == 430 || document.getElementById('testimg' + num).height == 374 || document.getElementById('testimg' + num).height <= 0)
    {
      document.getElementById('result' + num).style.display = 'none';
    }
    else
    {
      document.getElementById('result' + num).style.display = 'inline';
      sqlpopupResize("resize.php?src=" + valeurChamp + "&num=" + num, num);
      sqltest(id);
    }
}

// POPUP
function sqlpopupResize(page, id) {
  window.open(page, 'popup','width=900,height=900');
  sqltest(id);
}

function sqltest(i)
{
  setTimeout(sqltest, 10, i);
  sessionStorage.clear();
  $('#result' + i).attr('src', "tmp/image" + i + "-crop.jpg");
}
</script>

<form  action="?" method="POST">

<?php
try
{
  $bdd = new PDO('mysql:host=localhost;dbname=formulaire;charset=utf8', 'root', 'root');
}
catch (Exception $e)
{
  die('Erreur : ' . $e->getMessage());
}

$reponse = $bdd->query("SELECT * FROM enigme ORDER BY id");
$result = $bdd->query("SELECT id FROM enigme");


// On récupère tout le contenu de la table enigme
// $reponse = $bdd->query('SELECT * FROM enigme ORDER BY id');
$bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);;

// On affiche chaque entrée une à une

if (empty($result->fetch()))
{
  ?>
  <input type="submit" class="_button _button-1" name="plus" id="plus" value="+"/>
  <?php
}
else
{
$i = 0;
while ($donnees = $reponse->fetch())
{
?>
<!-- Input MOT -->

          <p class="text text-1"><strong>LE MOT &nbsp;À TROUVER</strong></p>
          <p class="text text-2"></p>
          <input class="_input _input-2" type="text" name="sqlmot<?php echo $i?>" id="sqlmot<?php echo $i?>" value="<?php if (isset($_POST['sqlmot' . $i])){echo $_POST['sqlmot' . $i];} else {echo $donnees['mot'];} ?>">
          <input type="submit" class="_button _button-1" name="plus" id="plus" value="+"/>
          <div class="element element-4"></div>
          <p class="text text-3"><strong>DATE</strong></p>

          <i class="_button _button-2 first-arrow fa fa-caret-up" style="font-size:24px;color:white"></i>
          <div class="element element-5" ></div>

          <!-- DIV mot DEBUT -->
          <div hidden>

            <!-- Input IMAGE MOT -->
            <p class="text text-5"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ AU MOT</strong></font></p>
            <div class="element element-8"></div>
            <p class="text text-6"><strong>1-&nbsp;Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
            <img class="image image-3" src="images/flickr.png">
            <img class="image image-4" src="images/wikipedia.jpg">
            <img class="image image-5" src="images/noun.png">
            <p class="text text-7"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
            <p class="text text-8"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
            <input class="_input _input-4" type="url" name="sqlimage0<?php echo $i?>" id="sqlimage0<?php echo $i?>" onkeyup="sqlcropimg(this.value, '0<?php echo $i?>');" value="<?php if (isset($_POST['sqlimage0' . $i])){echo $_POST['sqlimage0' . $i];} else {echo $donnees['image0'];} ?>">
            <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
            <input class="_input _input-5" name="sqlauteur0<?php echo $i?>" id="sqlauteur0<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqlauteur0' . $i])){echo $_POST['sqlauteur0' . $i];} else {echo $donnees['auteur0'];} ?>" >
            <p class="text text-10"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
            <input class="_input _input-5" name="sqldate0<?php echo $i?>" id="sqldate0<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqldate0' . $i])){echo $_POST['sqldate0' . $i];} else {echo $donnees['date0'];} ?>" >

            <div class="element element-9">
              <a href='javascript:sqlpopupResize("resize.php?src=" + sqlimage0<?php echo $i?>.value + "&num=0<?php echo $i?>", "0<?php echo $i?>")'><img src="<?php echo $donnees['imgcrop0']; ?>" id="result0<?php echo $i?>"/></a>
            </div>

            <img src="<?php echo $donnees['imgcrop0']; ?>" id="testimg0<?php echo $i?>" hidden/>

            <div class="element element-10"></div>


            <!-- Input INDICE 1 -->
            <p class="text text-4"><font color="#b2b2b2" face="Quattrocento Sans"><strong>INDICE 1</strong></font></p>
            <input class="_input _input-3" type="text" name="sqlindice1<?php echo $i?>" id="sqlindice1<?php echo $i?>" value="<?php if (isset($_POST['sqlindice1' . $i])){echo $_POST['sqlindice1' . $i];} else {echo $donnees['indice1'];} ?>">
            <div class="element element-6"></div>
            <p class="_button _button-3 second-arrow">&nbsp;ÉDITER&nbsp;&nbsp;<i class="fa fa-caret-up" style="color:white"></i></p>

            <div class="element element-7"></div>
            <!-- DIV INDICE 1 -->
            <div hidden>

              <!-- Input IMAGE INDICE 1 -->
              <p class="text text-5"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ AU MOT INDICE 1</strong></font></p>
              <div class="element element-8"></div>
              <p class="text text-6"><strong>1-&nbsp;Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
              <img class="image image-3" src="images/flickr.png">
              <img class="image image-4" src="images/wikipedia.jpg">
              <img class="image image-5" src="images/noun.png">
              <p class="text text-7"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
              <p class="text text-8"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
              <input class="_input _input-4" type="url" name="sqlimage1<?php echo $i?>" id="sqlimage1<?php echo $i?>" onkeyup="sqlcropimg(this.value, '1<?php echo $i?>');" value="<?php if (isset($_POST['sqlimage1' . $i])){echo $_POST['sqlimage1' . $i];} else {echo $donnees['image1'];} ?>">
              <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
              <input class="_input _input-5" name="sqlauteur1<?php echo $i?>" id="sqlauteur1<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqlauteur1' . $i])){echo $_POST['sqlauteur1' . $i];} else {echo $donnees['auteur1'];} ?>" >
              <p class="text text-10"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
              <input class="_input _input-5" name="sqldate1<?php echo $i?>" id="sqldate1<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqldate1' . $i])){echo $_POST['sqldate1' . $i];} else {echo $donnees['date1'];} ?>" >

              <div class="element element-9">
                <a href='javascript:sqlpopupResize("resize.php?src=" + sqlimage1<?php echo $i?>.value + "&num=1<?php echo $i?>", "1<?php echo $i?>")'><img src="<?php echo $donnees['imgcrop1']; ?>" id="result1<?php echo $i?>"/></a>
              </div>

              <img src="<?php echo $donnees['imgcrop1']; ?>" id="testimg1<?php echo $i?>" hidden/>

              <div class="element element-10"></div>

            </div>

            <!-- Input INDICE 2 -->
            <p class="text text-4"><font color="#b2b2b2" face="Quattrocento Sans"><strong>INDICE 2</strong></font></p>
            <input class="_input _input-3" type="text" name="sqlindice2<?php echo $i?>" id="sqlindice2<?php echo $i?>" value="<?php if (isset($_POST['sqlindice2' . $i])){echo $_POST['sqlindice2' . $i];} else {echo $donnees['indice2'];} ?>">
            <div class="element element-6"></div>
            <p class="_button _button-3 third-arrow">&nbsp;ÉDITER&nbsp;&nbsp;<i class="fa fa-caret-up" style="color:white"></i></p>

            <div class="element element-7"></div>

            <div hidden>

              <!-- Input IMAGE INDICE 2 -->
              <p class="text text-5"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ AU MOT INDICE 2</strong></font></p>
              <div class="element element-8"></div>
              <p class="text text-6"><strong>1 &nbsp; Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
              <img class="image image-3" src="images/flickr.png">
              <img class="image image-4" src="images/wikipedia.jpg">
              <img class="image image-5" src="images/noun.png">
              <p class="text text-7"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
              <p class="text text-8"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
              <input class="_input _input-4" type="url" name="sqlimage2<?php echo $i?>" id="sqlimage2<?php echo $i?>" onkeyup="sqlcropimg(this.value, '2<?php echo $i?>');" value="<?php if (isset($_POST['sqlimage2' . $i])){echo $_POST['sqlimage2' . $i];} else {echo $donnees['image2'];} ?>">
              <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
              <input class="_input _input-5" name="sqlauteur2<?php echo $i?>" id="sqlauteur2<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqlauteur2' . $i])){echo $_POST['sqlauteur2' . $i];} else {echo $donnees['auteur2'];} ?>" >
              <p class="text text-10"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
              <input class="_input _input-5" name="sqldate2<?php echo $i?>" id="sqldate2<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqldate2' . $i])){echo $_POST['sqldate2' . $i];} else {echo $donnees['date2'];} ?>" >

              <div class="element element-9">
                <a href='javascript:sqlpopupResize("resize.php?src=" + sqlimage2<?php echo $i?>.value + "&num=2<?php echo $i?>", "2<?php echo $i?>")'><img src="<?php echo $donnees['imgcrop2']; ?>" id="result2<?php echo $i?>"/></a>
              </div>

              <img src="<?php echo $donnees['imgcrop2']; ?>" id="testimg2<?php echo $i?>" hidden/>

              <div class="element element-10"></div>
            </div>



            <!-- Input INDICE 3 -->
            <p class="text text-4"><font color="#b2b2b2" face="Quattrocento Sans"><strong>INDICE 3</strong></font></p>
            <input class="_input _input-3" type="text" name="sqlindice3<?php echo $i?>" id="sqlindice3<?php echo $i?>" value="<?php if (isset($_POST['sqlindice3' . $i])){echo $_POST['sqlindice3' . $i];} else {echo $donnees['indice3'];} ?>">
            <div class="element element-6"></div>
            <p class="_button _button-3 fourth-arrow">&nbsp;ÉDITER&nbsp;&nbsp;<i class="fa fa-caret-up" style="color:white"></i></p>

            <div class="element element-7"></div>

            <div hidden>

              <!-- Input IMAGE INDICE 3 -->
              <p class="text text-5"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ AU MOT INDICE 3</strong></font></p>
              <div class="element element-8"></div>
              <p class="text text-6"><strong>1 &nbsp; Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
              <img class="image image-3" src="images/flickr.png">
              <img class="image image-4" src="images/wikipedia.jpg">
              <img class="image image-5" src="images/noun.png">
              <p class="text text-7"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
              <p class="text text-8"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
              <input class="_input _input-4" type="url" name="sqlimage3<?php echo $i?>" id="sqlimage3<?php echo $i?>" onkeyup="sqlcropimg(this.value, '3<?php echo $i?>');" value="<?php if (isset($_POST['sqlimage3' . $i])){echo $_POST['sqlimage3' . $i];} else {echo $donnees['image3'];} ?>">
              <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
              <input class="_input _input-5" name="sqlauteur3<?php echo $i?>" id="sqlauteur3<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqlauteur3' . $i])){echo $_POST['sqlauteur3' . $i];} else {echo $donnees['auteur3'];} ?>" >
              <p class="text text-10"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
              <input class="_input _input-5" name="sqldate3<?php echo $i?>" id="sqldate3<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqldate3' . $i])){echo $_POST['sqldate3' . $i];} else {echo $donnees['date3'];} ?>" >

              <div class="element element-9">
                <a href='javascript:sqlpopupResize("resize.php?src=" + sqlimage3<?php echo $i?>.value + "&num=3<?php echo $i?>", "3<?php echo $i?>")'><img src="<?php echo $donnees['imgcrop3']; ?>" id="result3<?php echo $i?>"/></a>
              </div>

              <img src="<?php echo $donnees['imgcrop3']; ?>" id="testimg3<?php echo $i?>" hidden/>

              <div class="element element-10"></div>

            </div>

            <!-- Input RECOMPENSE -->
            <p class="text text-4"><font color="#b2b2b2" face="Quattrocento Sans"><strong>GAGNÉ !</strong></font></p>
            <input class="_input _input-3" type="text" name="sqlrecompense<?php echo $i?>" id="sqlrecompense<?php echo $i?>" value="<?php if (isset($_POST['sqlrecompense' . $i])){echo $_POST['sqlrecompense' . $i];} else {echo $donnees['recompense'];} ?>">
            <div class="element element-6"></div>
            <p class="_button _button-3 fifth-arrow">&nbsp;ÉDITER&nbsp;&nbsp;<i class="fa fa-caret-up" style="color:white"></i></p>

            <div class="element element-7"></div>

            <div hidden>

              <!-- Input image RECOMPENSE -->
              <p class="text text-5"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ LA DÉFINITION</strong></font></p>
              <div class="element element-8"></div>
              <p class="text text-6"><strong>1 &nbsp; Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
              <img class="image image-3" src="images/flickr.png">
              <img class="image image-4" src="images/wikipedia.jpg">
              <img class="image image-5" src="images/noun.png">
              <p class="text text-7"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
              <p class="text text-8"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
              <input class="_input _input-4"  type="url" name="sqlimage4<?php echo $i?>" id="sqlimage4<?php echo $i?>" onkeyup="sqlcropimg(this.value, '4<?php echo $i?>');" value="<?php if (isset($_POST['sqlimage4' . $i])){echo $_POST['sqlimage4' . $i];} else {echo $donnees['image4'];} ?>">
              <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
              <input class="_input _input-5" name="sqlauteur4<?php echo $i?>" id="sqlauteur4<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqlauteur4' . $i])){echo $_POST['sqlauteur4' . $i];} else {echo $donnees['auteur4'];} ?>" >
              <p class="text text-10"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
              <input class="_input _input-5" name="sqldate4<?php echo $i?>" id="sqldate4<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqldate4' . $i])){echo $_POST['sqldate4' . $i];} else {echo $donnees['date4'];} ?>" >

              <div class="element element-9">
                <a href='javascript:sqlpopupResize("resize.php?src=" + sqlimage4<?php echo $i?>.value + "&num=4<?php echo $i?>", "4<?php echo $i?>")'><img src="<?php echo $donnees['imgcrop4']; ?>" id="result4<?php echo $i?>"/></a>
              </div>

              <img src="<?php echo $donnees['imgcrop4']; ?>" id="testimg4<?php echo $i?>" hidden/>

              <div class="element element-10"></div>

              <!-- Input legende RECOMPENSE -->
              <p class="text text-11"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA LÉGENDE (144 caractère max.)</strong></font></p>
              <textarea class="_input _input-7" name="sqllegende<?php echo $i?>" id="sqllegende<?php echo $i?>" class="legende_input"><?php if (isset($_POST['sqllegende' . $i])){echo $_POST['sqllegende' . $i];} else {echo $donnees['legende'];} ?></textarea>
              <div class="element element-11"></div>
          </div>
          <!-- /DIV mot FIN -->
          </div>

  <?php
  $i++;
  }
  ?>
<input class="_button _button-4" type="submit"name="update" id="update" value="update"/>
<?php
}
$reponse->closeCursor(); // Termine le traitement de la requête
?>

<script type="text/javascript" src="js/toggle.js"></script>

</form>
