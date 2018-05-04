<!doctype html>

<html>
<head>
    <meta charset="utf-8">
    <title>Manipulation des formulaires</title>
</head>

<body>
    <form action="cible.php">
        <h1>Enigme</h1>
        <p>
            <label for="jeux">Jeux :</label>
            <select name="jeux" id="jeux">
                <option selected>Motus</option>
                <option>Labyrinthe</option>
                <option>Rebu</option>
            </select>
        </p>
        <p>
            <label for="mot">Mot à trouver</label> :
            <input type="text" name="mot" id="mot" required>
        </p>
        <p>
            <label for="indice1">Indice 1</label> :
            <input type="text" name="indice1" id="indice1" required >
        </p>
        <p>
            <label for="photo1">Photo indice 1</label> :
            <input type="text" name="photo1" id="photo1" required>
        </p>
        <p>
        <p>
            <label for="indice2">Indice 2</label> :
            <input type="text" name="indice2" id="indice2" required >
        </p>
        <p>
            <label for="photo2">Photo indice 2</label> :
            <input type="text" name="photo2" id="photo2" required>
        </p>
        <p>
            <label for="indice3">Indice 3</label> :
            <input type="text" name="indice3" id="indice3" required >
        </p>
        <p>
            <label for="photo3">Photo indice 3</label> :
            <input type="text" name="photo3" id="photo3" required>
        </p>
        <p>
            <label for="recompense">Recompense</label> :
            <input type="text" name="recompense" id="recompense" required >
        </p>
        <p>
            <label for="photoR">Photo Recompense</label> :
            <input type="text" name="photoR" id="photoR" required>
        </p>
        <div class="button">
        <button type="submit">Envoyer le message</button>
        </div>
    </form>

</body>
</html>
