<script type="text/javascript">
pastille_new();
</script>

<form  action="?" method="POST">
<!-- Input MOT -->

<input class="_input _input-2" type="text" name="mot" id="mot" onkeyup='recupmot(this.value, "");' value="<?php if (isset($_POST['mot'])){echo $_POST['mot'];} ?>" spellcheck="true">
<input class="_input _input-3" type="text" id="theme" name="theme" placeholder="mot clé" value="<?php if (isset($_POST['mot'])){echo $_POST['mot'];} ?>" spellcheck="true">
<div class="element element-4" id="divmot" onchange="" ></div>
<p class="text text-2"><strong><?php echo $max + 1?></strong></p>
<input class="checkbox checkbox-2" onclick='alert_message_new()' type="checkbox" name="check" id="check" value="on">
<i class="_button _button-3 first-arrow fa fa-caret-down" id="arrow1" style="font-size:24px;color:white"></i>
<div class="element element-5" ></div>


<div >

  <!-- Input IMAGE MOT -->
  <p class="text text-4"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ AU MOT</strong></font></p>
  <div class="element element-8"></div>
  <p class="text text-5"><strong>1-&nbsp;Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
  <a id="flickr0" href='javascript:popup("https://www.flickr.com")'><img class="image image-2" src="images/flickr.png"></a>
  <a id="wikipedia0" href='javascript:popup("https://fr.wikipedia.org/wiki/Wikip%C3%A9dia:Accueil_principal")'><img class="image image-3" src="images/wikipedia.jpg" ></a>
  <a id="noun0" href='javascript:popup("https://thenounproject.com/")'><img class="image image-4" src="images/noun.png"></a>
  <p class="text text-6"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
  <p class="text text-7"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
  <input type="url" name="image0" id="image0" class="_input _input-5" onkeyup="cropimg(this.value, 0);" value="<?php if (isset($_POST['image0'])){echo $_POST['image0'];} ?>" spellcheck="true">
  <p class="text text-8"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
  <input class="_input _input-6" name="auteur0" id="auteur0" type="text"  value="<?php if (isset($_POST['auteur0'])){echo $_POST['auteur0'];} ?>" spellcheck="true">
  <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
  <input class="_input _input-7" name="date0" id="date0" type="text" value="<?php if (isset($_POST['date0'])){echo $_POST['date0'];} ?>" spellcheck="true">

<a href='javascript:popupResize("resize.php?src=" + image0.value + "&num=0", 0)'>
  <div class="element element-9">
     <img src="" id="result0"/>
  </div>
</a>

  <img src="" id="testimg0" hidden/>

  <div class="element element-10"></div>


  <!-- Input INDICE 1 -->

  <p class="text text-3"><font color="#b2b2b2" face="Quattrocento Sans"><strong>INDICE 1</strong></font></p>
  <input class="_input _input-4" type="text" name="indice1" id="indice1" onkeyup="recupindice1(this.value);" value="<?php if (isset($_POST['indice1'])){echo $_POST['indice1'];} ?>" spellcheck="true">
  <div class="element element-6" id="divindice1"></div>
  <p class="_button _button-4 second-arrow">ÉDITER</p>
  <div class="element element-7"></div>

  <!-- DIV INDICE 1 -->
  <div hidden>
    <!-- Input IMAGE INDICE 1 -->
    <p class="text text-4"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ AU MOT INDICE 1</strong></font></p>
    <div class="element element-8"></div>
    <p class="text text-5"><strong>1-&nbsp;Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
    <a id="flickr1" href='javascript:popup("https://www.flickr.com")'><img class="image image-2" src="images/flickr.png"></a>
    <a id="wikipedia1" href='javascript:popup("https://fr.wikipedia.org/wiki/Wikip%C3%A9dia:Accueil_principal")'><img class="image image-3" src="images/wikipedia.jpg" ></a>
    <a id="noun1" href='javascript:popup("https://thenounproject.com/")'><img class="image image-4" src="images/noun.png"></a>
    <p class="text text-6"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
    <p class="text text-7"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
    <input type="url" name="image1" id="image1" class="_input _input-5" onkeyup="cropimg(this.value, 1);" value="<?php if (isset($_POST['image1'])){echo $_POST['image1'];} ?>" spellcheck="true">
    <p class="text text-8"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
    <input class="_input _input-6" name="auteur1" id="auteur1" type="text" value="<?php if (isset($_POST['auteur1'])){echo $_POST['auteur1'];} ?>" spellcheck="true">
    <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
    <input class="_input _input-7" name="date1" id="date1" type="text" value="<?php if (isset($_POST['date1'])){echo $_POST['date1'];} ?>" spellcheck="true">

    <a href='javascript:popupResize("resize.php?src=" + image1.value + "&num=1", 1)'>
    <div class="element element-9">
       <img src="" id="result1"/>
    </div>
    </a>

    <img src="" id="testimg1" hidden/>

    <div class="element element-10"></div>

  </div>

  <!-- Input INDICE 2 -->

  <p class="text text-3"><font color="#b2b2b2" face="Quattrocento Sans"><strong>INDICE 2</strong></font></p>
  <input class="_input _input-4" type="text" name="indice2" id="indice2" onkeyup="recupindice2(this.value);" value="<?php if (isset($_POST['indice2'])){echo $_POST['indice2'];} ?>" spellcheck="true">
  <div class="element element-6" id="divindice2"></div>
  <p class="_button _button-4 third-arrow">ÉDITER</p>

  <div class="element element-7"></div>

  <div hidden>
    <!-- Input IMAGE INDICE 2 -->
    <p class="text text-4"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ AU MOT INDICE 2</strong></font></p>
    <div class="element element-8"></div>
    <p class="text text-5"><strong>1 &nbsp; Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
    <a id="flickr2" href='javascript:popup("https://www.flickr.com")'><img class="image image-2" src="images/flickr.png"></a>
    <a id="wikipedia2" href='javascript:popup("https://fr.wikipedia.org/wiki/Wikip%C3%A9dia:Accueil_principal")'><img class="image image-3" src="images/wikipedia.jpg" ></a>
    <a id="noun2" href='javascript:popup("https://thenounproject.com/")'><img class="image image-4" src="images/noun.png"></a>
    <p class="text text-6"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
    <p class="text text-7"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
    <input type="url" name="image2" id="image2" class="_input _input-5" onkeyup="cropimg(this.value, 2);" value="<?php if (isset($_POST['image2'])){echo $_POST['image2'];} ?>" spellcheck="true">
    <p class="text text-8"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
    <input class="_input _input-6" name="auteur2" id="auteur2" type="text" value="<?php if (isset($_POST['auteur2'])){echo $_POST['auteur2'];} ?>" spellcheck="true">
    <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
    <input class="_input _input-7" name="date2" id="date2" type="text" value="<?php if (isset($_POST['date2'])){echo $_POST['date2'];} ?>" spellcheck="true">

    <a href='javascript:popupResize("resize.php?src=" + image2.value + "&num=2", 2)'>
    <div class="element element-9">
      <img src="" id="result2" class="the_img"/>
    </div>
  </a>

    <img src="" id="testimg2" hidden/>
    <div class="element element-10"></div>
  </div>

  <!-- Input INDICE 3 -->

  <p class="text text-3"><font color="#b2b2b2" face="Quattrocento Sans"><strong>INDICE 3</strong></font></p>
  <input class="_input _input-4" type="text" name="indice3" id="indice3" onkeyup="recupindice3(this.value);" value="<?php if (isset($_POST['indice3'])){echo $_POST['indice3'];} ?>" spellcheck="true">
  <div class="element element-6" id="divindice3"></div>
  <p class="_button _button-4 fourth-arrow">ÉDITER</p>

  <div class="element element-7"></div>

  <div hidden>
    <!-- Input IMAGE INDICE 3 -->
    <p class="text text-4"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ AU MOT INDICE 3</strong></font></p>
    <div class="element element-8"></div>
    <p class="text text-5"><strong>1 &nbsp; Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
    <a id="flickr3" href='javascript:popup("https://www.flickr.com")'><img class="image image-2" src="images/flickr.png"></a>
    <a id="wikipedia3" href='javascript:popup("https://fr.wikipedia.org/wiki/Wikip%C3%A9dia:Accueil_principal")'><img class="image image-3" src="images/wikipedia.jpg" ></a>
    <a id="noun3" href='javascript:popup("https://thenounproject.com/")'><img class="image image-4" src="images/noun.png"></a>
    <p class="text text-6"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
    <p class="text text-7"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
    <input type="url" name="image3" id="image3" class="_input _input-5" onkeyup="cropimg(this.value, 3);" value="<?php if (isset($_POST['image3'])){echo $_POST['image3'];} ?>" spellcheck="true">
    <p class="text text-8"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
    <input class="_input _input-6" name="auteur3" id="auteur3" type="text" value="<?php if (isset($_POST['auteur3'])){echo $_POST['auteur3'];} ?>" spellcheck="true">
    <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
    <input class="_input _input-7" name="date3" id="date3" type="text" value="<?php if (isset($_POST['date3'])){echo $_POST['date3'];} ?>" spellcheck="true">

    <a href='javascript:popupResize("resize.php?src=" + image3.value + "&num=3", 3)'>
      <div class="element element-9">
        <img src="" id="result3" class="the_img"/>
      </div>
    </a>

      <img src="" id="testimg3" hidden/>
    <div class="element element-10"></div>

  </div>

  <!-- Input RECOMPENSE -->
  <p class="text text-3"><font color="#b2b2b2" face="Quattrocento Sans"><strong>GAGNÉ !</strong></font></p>
  <input class="_input _input-4" name="recompense" id="recompense" onkeyup="recupindice4(this.value);" value="<?php if (isset($_POST['recompense'])){echo $_POST['recompense'];} ?>" spellcheck="true">
  <div class="element element-6" id="divindice4"></div>
  <p class="_button _button-4 fifth-arrow">ÉDITER</p>

  <div class="element element-7"></div>

  <div hidden>

    <!-- Input image RECOMPENSE -->
    <p class="text text-4"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE VISUEL ASSOCIÉ LA DÉFINITION</strong></font></p>
    <div class="element element-8"></div>
    <p class="text text-5"><strong>1 &nbsp; Je choisi une banque d'image libres de droits</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;parmi les proposition ci-dessous :</strong></p>
    <a id="flickr4" href='javascript:popup("https://www.flickr.com")'><img class="image image-2" src="images/flickr.png"></a>
    <a id="wikipedia4" href='javascript:popup("https://fr.wikipedia.org/wiki/Wikip%C3%A9dia:Accueil_principal")'><img class="image image-3" src="images/wikipedia.jpg" ></a>
    <a id="noun4" href='javascript:popup("https://thenounproject.com/")'><img class="image image-4" src="images/noun.png"></a>
    <p class="text text-6"><strong>2- Je sélectionne une image puis je copie&nbsp;</strong><strong></br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l'URL de l'image (adresse dans le navigateur).&nbsp;</strong></p>
    <p class="text text-7"><strong>3- Je colle lURL dans le champs ci-dessous</strong></p>
    <input class="_input _input-5" type="url" name="image4" id="image4" onkeyup="cropimg(this.value, 4);" value="<?php if (isset($_POST['image4'])){echo $_POST['image4'];} ?>" spellcheck="true">
    <p class="text text-8"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LE NOM DE L'AUTEUR DE L'IMAGE</strong></font></p>
    <input class="_input _input-6" name="auteur4" id="auteur4" type="text" value="<?php if (isset($_POST['auteur4'])){echo $_POST['auteur4'];} ?>" spellcheck="true">
    <p class="text text-9"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA DATE DE MISE EN LIGNE DE L'IMAGE</strong></font></p>
    <input class="_input _input-7" name="date4" id="date4" type="text" value="<?php if (isset($_POST['date4'])){echo $_POST['date4'];} ?>" spellcheck="true">

    <a href='javascript:popupResize("resize.php?src=" + image4.value + "&num=4", 4)'>
    <div class="element element-9">
      <img src="" id="result4" class="the_img"/>
    </div>
  </a>

    <img src="" id="testimg4" hidden/>
    <div class="element element-10"></div>

    <!-- Input legende RECOMPENSE -->
    <p class="text text-10"><font color="#b2b2b2" face="Quattrocento Sans"><strong>LA LÉGENDE (144 caractère max.)</strong></font></p>
    <textarea name="legende" id="legende" class="_input _input-8"rows="4" cols="50" spellcheck="true"><?php if (isset($_POST['image4'])){echo $_POST['image4'];}?></textarea>
    <div class="element element-11"></div>
  </div>
  <input class="_button _button-5" type="submit" name="submit" value="Enregistrer la nouvelle enigme"/>
  <div class="element element-12"></div>
</div>
</form>                                                                                                                                                                                                        
