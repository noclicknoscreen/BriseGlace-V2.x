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
            <option value = "boggle">Boggle</option>
            <option value = "memory">Memory</option>
        </select>
    </p>

<p> --------------------------------------------------------------------------------------------------------------------</p>

  <?php
    require('script/front/old.php');
    // NOUVELLE ENIGME
    if (isset($_POST['plus']))
    {
      require('script/front/new.php');
    }
    // SI BOUTTON ENVOYER
    else if (isset($_POST['submit']))
    {
      require('script/back/create.php');
    }
     ?>

      <!-- BOUTTON -->
      <div class="button">
      <input type="submit" name="submit" value="Envoyer" />
      <input type="submit" name="plus" id="plus" value="+" />
      </div>
      </form>
</body>
</html>
