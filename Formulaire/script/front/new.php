<!-- Input MOT -->
<p> --------------------------------------------------------------------------------------------------------------------</p>
<p>
    <label for="mot">Mot à trouver</label> : <br>
    <input type="text" name="mot" id="mot" value="<?php if (isset($_POST['mot'])){echo $_POST['mot'];} ?>">
</p>

<details open>
<summary>ÉDITER</summary>
<?php
if ($_POST['jeux'] == "motus")
{
?>
<!-- Input INDICE 1 -->
<p>
    <label for="indice1">Indice 1</label> : <br>
    <input type="text" name="indice1" id="indice1" value="<?php if (isset($_POST['indice1'])){echo $_POST['indice1'];} ?>">
</p>
<!-- Input IMAGE INDICE 1 -->
<p>
    <label for="image1">image indice 1</label> : <br>
    <input type="url" name="image1" id="image1" class="url_input" value="<?php if (isset($_POST['image1'])){echo $_POST['image1'];} ?>">
</p>
<!-- Input INDICE 2 -->
<p>
    <label for="indice2">Indice 2</label> : <br>
    <input type="text" name="indice2" id="indice2" value="<?php if (isset($_POST['indice2'])){echo $_POST['indice2'];} ?>">
</p>
<!-- Input IMAGE INDICE 2 -->
<p>
    <label for="image2">image indice 2</label> : <br>
    <input type="url" name="image2" id="image2" class="url_input" value="<?php if (isset($_POST['image2'])){echo $_POST['image2'];} ?>">
</p>
<!-- Input INDICE 3 -->
<p>
    <label for="indice3">Indice 3</label> : <br>
    <input type="text" name="indice3" id="indice3" value="<?php if (isset($_POST['indice3'])){echo $_POST['indice3'];} ?>">
</p>
<!-- Input IMAGE INDICE 3 -->
<p>
    <label for="image3">image indice 3</label> : <br>
    <input type="url" name="image3" id="image3" class="url_input" value="<?php if (isset($_POST['image3'])){echo $_POST['image3'];} ?>">
</p>
<?php
}
?>
<!-- Input RECOMPENSE -->
<p>
    <label for="recompense">Recompense</label> : <br>
    <input type="text" name="recompense" id="recompense" value="<?php if (isset($_POST['recompense'])){echo $_POST['recompense'];} ?>">
</p>
<!-- Input image RECOMPENSE -->
<p>
    <label for="image4">image Recompense</label> : <br>
    <input type="url" name="image4" id="image4" class="url_input" value="<?php if (isset($_POST['image4'])){echo $_POST['image4'];} ?>">
</p>
<!-- Input legende RECOMPENSE -->
<p>
    <label for="legende">Légende</label> : <br>
    <input type="text" name="legende" id="legende" class="legende_input" value="<?php if (isset($_POST['legende'])){echo $_POST['legende'];} ?>">
</p>
</details>
