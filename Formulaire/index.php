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
      <script type="text/javascript"  src="js/pastille.js"></script>
      <link rel="stylesheet" href="css/jquery.Jcrop.css" type="text/css" />
      <link href="http://fonts.googleapis.com/css?family=Oswald:400,400|Quattrocento+Sans:400,700|PT+Sans:400|Open+Sans Condensed:300" rel="stylesheet" type="text/css">
      <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
      <link rel="stylesheet" href="css/standardize.css">
      <link rel="stylesheet" href="css/index-grid.css">
      <link rel="stylesheet" href="css/index.css">
  </head>
  <body class="body page-index clearfix">


    <div class="element element-2"></div>
    <img class="image image-1" src="images/1.png">
    <p class="_input _input-1">ENIGME</p>
    <img class="image image-2" src="images/2.png">
    <div class="element element-3"></div>

  <?php
  require('script/utile/function.php');
  // NOUVELLE ENIGME
  if (isset($_POST['plus']))
  {
      require('script/front/new.php');
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



</body>
</html>
