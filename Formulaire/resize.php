<!doctype html>

<html>
<head>
    <meta charset="utf-8">
    <title>resize</title>
    <meta name="viewport" content="initial-scale=1.0">
    <script type="text/javascript" src="js/jquery.min.js"></script>
    <script type="text/javascript" src="js/jquery.Jcrop.js"></script>
    <link rel="stylesheet" href="css/jquery.Jcrop.css" type="text/css" />
</head>

<body>

<script type="text/javascript">

var file =
</script>

<img src="<?php echo $_GET['src']?>" id="jcrop_target" />

<form action="crop.php" class="coords" method="post">
    <input type="text" id="x" name="x" hidden/>
    <input type="text" id="y" name="y" hidden/>
    <input type="text" id="w" name="w" hidden/>
    <input type="text" id="h" name="h" hidden/>
    <input type="text" value="<?php echo $_GET['src']?>" id="src" name="src" hidden/>
    <input type="text" value="<?php echo $_GET['num']?>" id="num" name="num" hidden/>
    <input type="submit" value="Crop"/>
  </form>


<script type="text/javascript">

$(function(){
  $('#jcrop_target').Jcrop({
  onSelect: updateCoords,
  onChange: updateCoords,
  bgColor: 'transparent',
  boxWidth: 700,
  boxHeight: 770,
  bgOpacity:  .2,
  setSelect:   [0, 0, 3000, 0],
  allowSelect : false,
  aspectRatio: 1,
 });
});

function updateCoords(c)
{
 $('#x').val(c.x);
 $('#y').val(c.y);
 $('#w').val(c.w);
 $('#h').val(c.h);
};

function png2jpg($originalFile, $outputFile, $quality) {
    $image = imagecreatefrompng($originalFile);
    imagejpeg($image, $outputFile, $quality);
    imagedestroy($image);
}

</script>

</body>

</html>
