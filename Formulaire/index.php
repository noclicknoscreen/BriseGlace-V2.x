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

      <?php
          $selected = isset( $_POST['jeux'] ) ? $_POST['jeux'] : "" ;
          $selectedValue = 'selected="selected"';
      ?>

        <label for="jeux">Jeux :</label>
        <select name="jeux" id="jeux" value="boggle">
            <!-- choix du jeux  -->
            <option value = "motus" <?php if( $selected == "motus" ) echo $selectedValue ?>>Motus</option>
            <option value = "boggle" <?php if( $selected == "boggle" ) echo $selectedValue ?>>Boggle</option>
            <option value = "memory" <?php if( $selected == "memory" ) echo $selectedValue ?>>Memory</option>
        </select>
        <input type="submit" name="select" id="selects" value="Select" />
    </p>

  <?php
  require('script/utile/function.php');
  if (isset($_POST['jeux']))
  {
      ?>

      <!-- BOUTTON -->
      <div class="button">
      </br>
        <input type="submit" name="plus" id="plus" value="+"/>
      </div>

      <?php

      // NOUVELLE ENIGME
      if (isset($_POST['plus']))
      {
        require('script/front/new.php');
        // SI BOUTTON ENVOYER
        ?>
        <input type="submit" name="submit" value="Envoyer" />
        <?php
      }
      else if (isset($_POST['submit']))
      {
        require('script/back/create.php');
      }
      else if (isset($_POST['update']))
      {
        require('script/back/update.php');
      }
      require('script/front/old.php');
      ?>
      <p> --------------------------------------------------------------------------------------------------------------------</p>
      <input type="submit" name="update" id="update" value="update" />
      <p> --------------------------------------------------------------------------------------------------------------------</p>
      <?php
    } ?>

</form>
</body>
</html>
