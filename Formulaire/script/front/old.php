<form  action="?" method="POST" onsubmit="return old_submit()">

<?php
try
{
  $bdd = new PDO('mysql:host=localhost;dbname=formulaire;charset=utf8', 'root', 'root');
}
catch (Exception $e)
{
  die('Erreur : ' . $e->getMessage());
}

if (!isset($_POST['trier'])) {
  $trier = "id";
}
else {
  $trier = $_POST['trier'];
}

if (isset($_POST['chercher']))
{
  if (strlen($_POST['chercher']) > 0)
  {
    if (!strcmp($_POST['selectTable'], "indice")) {
      $chercherand = " AND indice1 LIKE '%" . $_POST['chercher'] ."%' OR indice2 LIKE '%" . $_POST['chercher'] ."%' OR indice3 LIKE '%" . $_POST['chercher'] . "%' ";
      $chercherwhere = " WHERE indice1 LIKE '%" . $_POST['chercher'] ."%' OR indice2 LIKE '%" . $_POST['chercher'] ."%' OR indice3 LIKE '%" . $_POST['chercher'] . "%' ";
    }
    elseif (!strcmp($_POST['selectTable'], "image")) {
      $chercherand = " AND image0 LIKE '%" . $_POST['chercher'] ."%' OR image1 LIKE '%" . $_POST['chercher'] ."%' OR image2 LIKE '%" . $_POST['chercher'] ."%' OR image3 LIKE '%" . $_POST['chercher'] ."%' OR image4 LIKE '%" . $_POST['chercher'] ."%' ";
      $chercherwhere = " WHERE image0 LIKE '%" . $_POST['chercher'] ."%' OR image1 LIKE '%" . $_POST['chercher'] ."%' OR image2 LIKE '%" . $_POST['chercher'] ."%' OR image3 LIKE '%" . $_POST['chercher'] ."%' OR image4 LIKE '%" . $_POST['chercher'] ."%' ";
    }
    elseif (!strcmp($_POST['selectTable'], "auteur")) {
      $chercherand = " AND auteur0 LIKE '%" . $_POST['chercher'] ."%' OR auteur1 LIKE '%" . $_POST['chercher'] ."%' OR auteur2 LIKE '%" . $_POST['chercher'] ."%' OR auteur3 LIKE '%" . $_POST['chercher'] ."%' OR auteur4 LIKE '%" . $_POST['chercher'] ."%' ";
      $chercherwhere = " WHERE auteur0 LIKE '%" . $_POST['chercher'] ."%' OR auteur1 LIKE '%" . $_POST['chercher'] ."%' OR auteur2 LIKE '%" . $_POST['chercher'] ."%' OR auteur3 LIKE '%" . $_POST['chercher'] ."%' OR auteur4 LIKE '%" . $_POST['chercher'] ."%' ";
    }
    elseif (!strcmp($_POST['selectTable'], "date")) {
      $chercherand = " AND date LIKE '%" . $_POST['chercher'] ."%' OR date0 LIKE '%" . $_POST['chercher'] ."%' OR date1 LIKE '%" . $_POST['chercher'] ."%' OR date2 LIKE '%" . $_POST['chercher'] ."%' OR date3 LIKE '%" . $_POST['chercher'] ."%' OR date4 LIKE '%" . $_POST['chercher'] ."%' ";
      $chercherwhere = " WHERE date LIKE '%" . $_POST['chercher'] ."%' OR date0 LIKE '%" . $_POST['chercher'] ."%' OR date1 LIKE '%" . $_POST['chercher'] ."%' OR date2 LIKE '%" . $_POST['chercher'] ."%' OR date3 LIKE '%" . $_POST['chercher'] ."%' OR date4 LIKE '%" . $_POST['chercher'] ."%' ";
    }
    else {
      $chercherand = " AND " . $_POST['selectTable'] ." LIKE '%" . $_POST['chercher'] ."%' ";
      $chercherwhere = " WHERE " . $_POST['selectTable'] ." LIKE '%" . $_POST['chercher'] ."%' ";
    }
  }
  else {
    $chercherand = " ";
    $chercherwhere = " ";
  }
}
else {
  $chercherand = " ";
  $chercherwhere = " ";
}

if (isset($_POST['filtrer']) || isset($_POST['trier']))
{
  if (!strcmp($_POST['filtrer'], "on"))
  {
    $reponse = $bdd->query("SELECT * FROM enigme WHERE actif = 'on'" . $chercherand . "ORDER BY " . $trier);
    $good_requet = "SELECT * FROM enigme WHERE actif = 'on'" . $chercherand . "ORDER BY " . $trier;
    $control_check = 1;
  }
  elseif (!strcmp($_POST['filtrer'], "off")) {
    $reponse = $bdd->query("SELECT * FROM enigme WHERE actif = 'off'" . $chercherand . "ORDER BY " . $trier);
    $good_requet = "SELECT * FROM enigme WHERE actif = 'off'" . $chercherand . "ORDER BY " . $trier;
    $control_check = 0;
  }
  elseif (!strcmp($_POST['filtrer'], "complet")) {
    $reponse = $bdd->query("SELECT * FROM enigme WHERE complet = 'complet'" . $chercherand . "ORDER BY " . $trier);
    $good_requet = "SELECT * FROM enigme WHERE complet = 'complet'" . $chercherand . "ORDER BY " . $trier;
    $control_check = 1;
  }
  elseif (!strcmp($_POST['filtrer'], "incomplet")) {
    $reponse = $bdd->query("SELECT * FROM enigme WHERE complet = 'incomplet'" . $chercherand . "ORDER BY " . $trier);
    $good_requet = "SELECT * FROM enigme WHERE complet = 'incomplet'" . $chercherand . "ORDER BY " . $trier;
    $control_check = 0;
  }
  else
  {
    $reponse = $bdd->query('SELECT * FROM enigme' . $chercherwhere . 'ORDER BY ' . $trier);
    $good_requet = 'SELECT * FROM enigme' . $chercherwhere . 'ORDER BY ' . $trier;
    $control_check = 1;
  }
}
else
  {
    $reponse = $bdd->query('SELECT * FROM enigme' . $chercherwhere . 'ORDER BY id');
    $good_requet = 'SELECT * FROM enigme' . $chercherwhere . 'ORDER BY id';
    $control_check = 1;
  }


// On récupère tout le contenu de la table enigme
// $reponse = $bdd->query('SELECT * FROM enigme ORDER BY id');
$bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);;

// On affiche chaque entrée une à une

?>
  <input type="text" name="good_requet" id="good_requet" value="<?php echo $good_requet?>" hidden/>
<?php
$i = 0;
while ($donnees = $reponse->fetch())
{
?>
<!-- Input MOT -->
<!-- Mot clé -->
          <input type="text" name="sqlcomplet<?php echo $i?>" id="sqlcomplet<?php echo $i?>" value="incomplet" hidden/>
          <input type="submit" class="_button _button-2" name="plus" id="plus" value="+"/>
          <input class="_input _input-2" type="text" name="sqlmot<?php echo $i?>" id="sqlmot<?php echo $i?>" value="<?php if (isset($_POST['sqlmot' . $i])){echo $_POST['sqlmot' . $i];} else {echo $donnees['mot'];} ?>" spellcheck="true">
          <input class="_input _input-3" type="text" id="sqltheme<?php echo $i?>" name="sqltheme<?php echo $i?>" placeholder="mot clé" value="<?php if (isset($_POST['sqltheme' . $i])){echo $_POST['sqltheme' . $i];} else {echo $donnees['theme'];} ?>" spellcheck="true">
          <div class="element element-4" id="sqldivmot<?php echo $i?>"></div>
          <?php
          $year = substr($donnees['date'], 0, 10);
          $hour= substr($donnees['date'], 10, 6);
          ?>
          <p class="text text-2"><strong><?php echo $year?>&nbsp;&nbsp;&nbsp;&nbsp;<?php echo $hour?></strong></p>


          <input class="checkbox checkbox-2" onclick='alert_message_old("<?php echo $i?>")' type="checkbox" name="check<?php echo $i?>" id="check<?php echo $i?>" value="on" <?php if (!strcmp($donnees['actif'],"on")) {echo "checked";}?>>


          <i class="container first-arrow fa fa-caret-up" style="font-size:24px;color:white"></i>

          <div class="element element-5" ></div>

          <!-- DIV mot DEBUT -->
          <div hidden>

            <!-- Input IMAGE MOT -->
            <p class="text text-4"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ AU MOT</strong></font></p>
            <div class="element element-8"></div>
            <p class="text text-5"><strong>1-&nbsp;Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
            <a id="flickr0<?php echo $i?>" href='javascript:popup("https://www.flickr.com/search/?text=<?php echo $donnees['mot'];?>&license=4%2C5%2C9%2C10")'><img class="image image-2" src="images/flickr.png"></a>
            <a id="wikipedia0<?php echo $i?>" href='javascript:popup("https://fr.wikipedia.org/wiki/<?php echo $donnees['mot'];?>")'><img class="image image-3" src="images/wikipedia.jpg" ></a>
            <a id="noun0<?php echo $i?>" href='javascript:popup("https://thenounproject.com/search/?q=<?php echo $donnees['mot'];?>")'><img class="image image-4" src="images/noun.png"></a>
            <p class="text text-6"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
            <p class="text text-7"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
            <input class="_input _input-5" type="url" name="sqlimage0<?php echo $i?>" id="sqlimage0<?php echo $i?>" onkeyup="sqlcropimg(this.value, '0<?php echo $i?>');" value="<?php if (isset($_POST['sqlimage0' . $i])){echo $_POST['sqlimage0' . $i];} else {echo $donnees['image0'];} ?>" spellcheck="true">
            <p class="text text-8"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
            <input class="_input _input-6" name="sqlauteur0<?php echo $i?>" id="sqlauteur0<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqlauteur0' . $i])){echo $_POST['sqlauteur0' . $i];} else {echo $donnees['auteur0'];} ?>" spellcheck="true">
            <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
            <input class="_input _input-7" name="sqldate0<?php echo $i?>" id="sqldate0<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqldate0' . $i])){echo $_POST['sqldate0' . $i];} else {echo $donnees['date0'];} ?>" spellcheck="true">

            <a href='javascript:sqlpopupResize("resize.php?src=" + sqlimage0<?php echo $i?>.value + "&num=0<?php echo $i?>", "0<?php echo $i?>")'>
            <div class="element element-9">
              <img src="<?php echo $donnees['imgcrop0']; ?>" id="result0<?php echo $i?>" display="inline"/>
            </div>
            </a>

            <img src="<?php echo $donnees['imgcrop0']; ?>" id="testimg0<?php echo $i?>" hidden/>

            <div class="element element-10"></div>


            <!-- Input INDICE 1 -->
            <p class="text text-3"><font color="#b2b2b2" face="Quattrocento Sans"><strong>INDICE 1</strong></font></p>
            <input class="_input _input-4" type="text" name="sqlindice1<?php echo $i?>" id="sqlindice1<?php echo $i?>" value="<?php if (isset($_POST['sqlindice1' . $i])){echo $_POST['sqlindice1' . $i];} else {echo $donnees['indice1'];} ?>" spellcheck="true">
            <div class="element element-6" id="sqldivindice1<?php echo $i?>" spellcheck="true"></div>
            <p class="_button _button-3 second-arrow">ÉDITER</p>

            <div class="element element-7"></div>
            <!-- DIV INDICE 1 -->
            <div hidden>

              <!-- Input IMAGE INDICE 1 -->
              <p class="text text-4"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ AU MOT INDICE 1</strong></font></p>
              <div class="element element-8"></div>
              <p class="text text-5"><strong>1-&nbsp;Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
              <a id="flickr1<?php echo $i?>" href='javascript:popup("https://www.flickr.com/search/?text=<?php echo $donnees['indice1'];?>&license=4%2C5%2C9%2C10")'><img class="image image-2" src="images/flickr.png"></a>
              <a id="wikipedia1<?php echo $i?>" href='javascript:popup("https://fr.wikipedia.org/wiki/<?php echo $donnees['indice1'];?>")'><img class="image image-3" src="images/wikipedia.jpg" ></a>
              <a id="noun1<?php echo $i?>" href='javascript:popup("https://thenounproject.com/search/?q=<?php echo $donnees['indice1'];?>")'><img class="image image-4" src="images/noun.png"></a>
              <p class="text text-6"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
              <p class="text text-7"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
              <input class="_input _input-5" type="url" name="sqlimage1<?php echo $i?>" id="sqlimage1<?php echo $i?>" onkeyup="sqlcropimg(this.value, '1<?php echo $i?>');" value="<?php if (isset($_POST['sqlimage1' . $i])){echo $_POST['sqlimage1' . $i];} else {echo $donnees['image1'];} ?>" spellcheck="true">
              <p class="text text-8"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
              <input class="_input _input-6" name="sqlauteur1<?php echo $i?>" id="sqlauteur1<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqlauteur1' . $i])){echo $_POST['sqlauteur1' . $i];} else {echo $donnees['auteur1'];} ?>" spellcheck="true">
              <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
              <input class="_input _input-7" name="sqldate1<?php echo $i?>" id="sqldate1<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqldate1' . $i])){echo $_POST['sqldate1' . $i];} else {echo $donnees['date1'];} ?>" spellcheck="true">

              <a href='javascript:sqlpopupResize("resize.php?src=" + sqlimage1<?php echo $i?>.value + "&num=1<?php echo $i?>", "1<?php echo $i?>")'>
              <div class="element element-9">
                <img src="<?php echo $donnees['imgcrop1']; ?>" id="result1<?php echo $i?>" display="inline"/>
              </div>
              </a>

              <img src="<?php echo $donnees['imgcrop1']; ?>" id="testimg1<?php echo $i?>" hidden/>

              <div class="element element-10"></div>

            </div>

            <!-- Input INDICE 2 -->
            <p class="text text-3"><font color="#b2b2b2" face="Quattrocento Sans"><strong>INDICE 2</strong></font></p>
            <input class="_input _input-4" type="text" name="sqlindice2<?php echo $i?>" id="sqlindice2<?php echo $i?>" value="<?php if (isset($_POST['sqlindice2' . $i])){echo $_POST['sqlindice2' . $i];} else {echo $donnees['indice2'];} ?>" spellcheck="true">
            <div class="element element-6" id="sqldivindice2<?php echo $i?>" spellcheck="true"></div>
            <p class="_button _button-3 third-arrow">ÉDITER</p>

            <div class="element element-7"></div>

            <div hidden>

              <!-- Input IMAGE INDICE 2 -->
              <p class="text text-4"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ AU MOT INDICE 2</strong></font></p>
              <div class="element element-8"></div>
              <p class="text text-5"><strong>1 &nbsp; Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
              <a id="flickr2<?php echo $i?>" href='javascript:popup("https://www.flickr.com/search/?text=<?php echo $donnees['indice2'];?>&license=4%2C5%2C9%2C10")'><img class="image image-2" src="images/flickr.png"></a>
              <a id="wikipedia2<?php echo $i?>" href='javascript:popup("https://fr.wikipedia.org/wiki/<?php echo $donnees['indice2'];?>")'><img class="image image-3" src="images/wikipedia.jpg" ></a>
              <a id="noun2<?php echo $i?>" href='javascript:popup("https://thenounproject.com/search/?q=<?php echo $donnees['indice2'];?>")'><img class="image image-4" src="images/noun.png"></a>
              <p class="text text-6"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
              <p class="text text-7"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
              <input class="_input _input-5" type="url" name="sqlimage2<?php echo $i?>" id="sqlimage2<?php echo $i?>" onkeyup="sqlcropimg(this.value, '2<?php echo $i?>');" value="<?php if (isset($_POST['sqlimage2' . $i])){echo $_POST['sqlimage2' . $i];} else {echo $donnees['image2'];} ?>" spellcheck="true">
              <p class="text text-8"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
              <input class="_input _input-6" name="sqlauteur2<?php echo $i?>" id="sqlauteur2<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqlauteur2' . $i])){echo $_POST['sqlauteur2' . $i];} else {echo $donnees['auteur2'];} ?>" spellcheck="true">
              <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
              <input class="_input _input-7" name="sqldate2<?php echo $i?>" id="sqldate2<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqldate2' . $i])){echo $_POST['sqldate2' . $i];} else {echo $donnees['date2'];} ?>" spellcheck="true">

              <a href='javascript:sqlpopupResize("resize.php?src=" + sqlimage2<?php echo $i?>.value + "&num=2<?php echo $i?>", "2<?php echo $i?>")'>
              <div class="element element-9">
                <img src="<?php echo $donnees['imgcrop2']; ?>" id="result2<?php echo $i?>" display="inline"/>
              </div>
              </a>

              <img src="<?php echo $donnees['imgcrop2']; ?>" id="testimg2<?php echo $i?>" hidden/>

              <div class="element element-10"></div>
            </div>



            <!-- Input INDICE 3 -->
            <p class="text text-3"><font color="#b2b2b2" face="Quattrocento Sans"><strong>INDICE 3</strong></font></p>
            <input class="_input _input-4" type="text" name="sqlindice3<?php echo $i?>" id="sqlindice3<?php echo $i?>" value="<?php if (isset($_POST['sqlindice3' . $i])){echo $_POST['sqlindice3' . $i];} else {echo $donnees['indice3'];} ?>" spellcheck="true">
            <div class="element element-6" id="sqldivindice3<?php echo $i?>" spellcheck="true"></div>
            <p class="_button _button-3 fourth-arrow">ÉDITER</p>

            <div class="element element-7"></div>

            <div hidden>

              <!-- Input IMAGE INDICE 3 -->
              <p class="text text-4"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ AU MOT INDICE 3</strong></font></p>
              <div class="element element-8"></div>
              <p class="text text-5"><strong>1 &nbsp; Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
              <a id="flickr3<?php echo $i?>" href='javascript:popup("https://www.flickr.com/search/?text=<?php echo $donnees['indice3'];?>&license=4%2C5%2C9%2C10")'><img class="image image-2" src="images/flickr.png"></a>
              <a id="wikipedia3<?php echo $i?>" href='javascript:popup("https://fr.wikipedia.org/wiki/<?php echo $donnees['indice3'];?>")'><img class="image image-3" src="images/wikipedia.jpg" ></a>
              <a id="noun3<?php echo $i?>" href='javascript:popup("https://thenounproject.com/search/?q=<?php echo $donnees['indice3'];?>")'><img class="image image-4" src="images/noun.png"></a>
              <p class="text text-6"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
              <p class="text text-7"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
              <input class="_input _input-5" type="url" name="sqlimage3<?php echo $i?>" id="sqlimage3<?php echo $i?>" onkeyup="sqlcropimg(this.value, '3<?php echo $i?>');" value="<?php if (isset($_POST['sqlimage3' . $i])){echo $_POST['sqlimage3' . $i];} else {echo $donnees['image3'];} ?>" spellcheck="true">
              <p class="text text-8"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
              <input class="_input _input-6" name="sqlauteur3<?php echo $i?>" id="sqlauteur3<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqlauteur3' . $i])){echo $_POST['sqlauteur3' . $i];} else {echo $donnees['auteur3'];} ?>" spellcheck="true">
              <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
              <input class="_input _input-7" name="sqldate3<?php echo $i?>" id="sqldate3<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqldate3' . $i])){echo $_POST['sqldate3' . $i];} else {echo $donnees['date3'];} ?>" spellcheck="true">

              <a href='javascript:sqlpopupResize("resize.php?src=" + sqlimage3<?php echo $i?>.value + "&num=3<?php echo $i?>", "3<?php echo $i?>")'>
              <div class="element element-9">
                <img src="<?php echo $donnees['imgcrop3']; ?>" id="result3<?php echo $i?>" display="inline"/>
              </div>
              </a>

              <img src="<?php echo $donnees['imgcrop3']; ?>" id="testimg3<?php echo $i?>" hidden/>

              <div class="element element-10"></div>

            </div>

            <!-- Input RECOMPENSE -->
            <p class="text text-3"><font color="#b2b2b2" face="Quattrocento Sans"><strong>GAGNÉ !</strong></font></p>
            <input class="_input _input-4" type="text" name="sqlrecompense<?php echo $i?>" id="sqlrecompense<?php echo $i?>" value="<?php if (isset($_POST['sqlrecompense' . $i])){echo $_POST['sqlrecompense' . $i];} else {echo $donnees['recompense'];} ?>" spellcheck="true">
            <div class="element element-6" id="sqldivindice4<?php echo $i?>" spellcheck="true"></div>
            <p class="_button _button-3 fifth-arrow">ÉDITER</p>

            <div class="element element-5"></div>

            <div hidden>

              <!-- Input image RECOMPENSE -->
              <p class="text text-4"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ LA DÉFINITION</strong></font></p>
              <div class="element element-8"></div>
              <p class="text text-5"><strong>1 &nbsp; Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
              <a id="flickr4<?php echo $i?>" href='javascript:popup("https://www.flickr.com/search/?text=<?php echo $donnees['recompense'];?>&license=4%2C5%2C9%2C10")'><img class="image image-2" src="images/flickr.png"></a>
              <a id="wikipedia4<?php echo $i?>" href='javascript:popup("https://fr.wikipedia.org/wiki/<?php echo $donnees['recompense'];?>")'><img class="image image-3" src="images/wikipedia.jpg" ></a>
              <a id="noun4<?php echo $i?>" href='javascript:popup("https://thenounproject.com/search/?q=<?php echo $donnees['recompense'];?>")'><img class="image image-4" src="images/noun.png"></a>
              <p class="text text-6"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
              <p class="text text-7"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
              <input class="_input _input-5"  type="url" name="sqlimage4<?php echo $i?>" id="sqlimage4<?php echo $i?>" onkeyup="sqlcropimg(this.value, '4<?php echo $i?>');" value="<?php if (isset($_POST['sqlimage4' . $i])){echo $_POST['sqlimage4' . $i];} else {echo $donnees['image4'];} ?>" spellcheck="true">
              <p class="text text-8"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
              <input class="_input _input-6" name="sqlauteur4<?php echo $i?>" id="sqlauteur4<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqlauteur4' . $i])){echo $_POST['sqlauteur4' . $i];} else {echo $donnees['auteur4'];} ?>" spellcheck="true">
              <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
              <input class="_input _input-7" name="sqldate4<?php echo $i?>" id="sqldate4<?php echo $i?>" type="text"  value="<?php if (isset($_POST['sqldate4' . $i])){echo $_POST['sqldate4' . $i];} else {echo $donnees['date4'];} ?>" spellcheck="true">

              <a href='javascript:sqlpopupResize("resize.php?src=" + sqlimage4<?php echo $i?>.value + "&num=4<?php echo $i?>", "4<?php echo $i?>")'>
              <div class="element element-9">
                <img src="<?php echo $donnees['imgcrop4']; ?>" id="result4<?php echo $i?>" display="inline"/>
              </div>
              </a>

              <img src="<?php echo $donnees['imgcrop4']; ?>" id="testimg4<?php echo $i?>" hidden/>

              <div class="element element-10"></div>

              <!-- Input legende RECOMPENSE -->
              <p class="text text-10"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA LÉGENDE (144 caractère max.)</strong></font></p>
              <textarea class="_input _input-8" name="sqllegende<?php echo $i?>" id="sqllegende<?php echo $i?>" class="legende_input"><?php if (isset($_POST['sqllegende' . $i])){echo $_POST['sqllegende' . $i];} else {echo $donnees['legende'];} ?></textarea>
              <div class="element element-5"></div>
          </div>
          <!-- /DIV mot FIN -->
          </div>

  <?php
  $i++;
  }
  ?>
<input class="_button _button-4" type="submit"name="update" id="update" value="Enregistrer les modifications"/>
<?php
$reponse->closeCursor(); // Termine le traitement de la requête
$maxidi = $i;
?>
<input type="number" id="numMax" name="numMax" value=<?php echo $maxidi?> hidden>
<script type="text/javascript" src="js/toggle.js"></script>

</form>


<script type="text/javascript">

function alert_message_old(id)
{
  if (document.getElementById('sqldivmot' + id).style.backgroundColor == "rgb(228, 38, 19)" || document.getElementById('sqldivmot' + id).style.backgroundColor == "rgb(247, 147, 30)")
  {
    document.getElementById('check' + id).checked = false;
    alert("Enigme incomplète !");
  }
}

// Autorisation à cocher "check" ou non
function old_submit()
{
  var nb = <?php echo $control_check;?>;
  if (nb == 1)
  {
    var testcheck = false;
    for (var id = 0; id < <?php echo $maxidi?>; id++)
    {
       if (document.getElementById('check' + id).checked == true) {testcheck = true;}
    }
    if (testcheck != true) {
      window.alert("Vous devez avoir activé au moins une enigme !");
      return false;
    }
  }
}

// PASTILLE POUR OLD.PHP
// INDICE
for (var j = 0; j < <?php echo $maxidi?>; j++) {
  for (var i = 0; i <= 4; i++) {
      if (!document.getElementById('result' + i + j).height <= 0)
        {
          document.getElementById('result' + i + j).style.display = 'inline';
        }
    }
}

for (var j = 0; j < <?php echo $maxidi?>; j++) {
  for (var i = 1; i <= 4; i++) {
      document.getElementById('sqldivindice' + i + j).style.backgroundColor = "rgb(102, 171, 82)";
    }
}

pastille_old(<?php echo $maxidi?>);

</script>
