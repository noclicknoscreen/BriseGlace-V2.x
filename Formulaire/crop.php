<?php

$targ_w = $targ_h = 400;
$jpeg_quality = 90;
$new_filename = "tmp/image" . $_POST['num'] . "-crop.jpg";

$src = $_POST['src'];

$info = new SplFileInfo($src);
if ($info->getExtension() == "jpg" || $info->getExtension() == "jpeg" || $info->getExtension() == "JPG" || $info->getExtension() == "svg")
{
  $img_r = imagecreatefromjpeg($src);
  $dst_r = ImageCreateTrueColor( $targ_w, $targ_h);
  imagecopyresampled($dst_r,$img_r,0,0,$_POST['x'],$_POST['y'],$targ_w,$targ_h,$_POST['w'],$_POST['h']);
  imagejpeg($dst_r, $new_filename, $jpeg_quality);
}
else if($info->getExtension() == "png")
{
  $img_r = imagecreatefrompng($src);
  $dst_r = ImageCreateTrueColor( $targ_w, $targ_h );
  $nouvelleImage = imagecreatetruecolor($width, $height);
  $bg = imagecolorallocate($dst_r, 255, 255, 255);
  imagefill($dst_r, 0, 0, $bg);
  imagecopyresampled($dst_r,$img_r,0,0,$_POST['x'],$_POST['y'],$targ_w,$targ_h,$_POST['w'],$_POST['h']);
  imagejpeg($dst_r, $new_filename);
}


echo "<img src='" . $new_filename . "' />"

?>

<script type="text/javascript">
this.window.close();
</script>
