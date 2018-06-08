//RECHERCHE D'IMAGE

function recupmot(valeurChamp) {
    $('#flickr0').attr('href', "javascript:popup(\"https://www.flickr.com/search/?text=" + valeurChamp + "&license=4%2C5%2C9%2C10\")");
    $('#wikipedia0').attr('href', "javascript:popup(\"https://fr.wikipedia.org/wiki/" + valeurChamp + "\")");
    $('#noun0').attr('href', "javascript:popup(\"https://thenounproject.com/search/?q=" + valeurChamp + "\")");
}

function recupindice1(valeurChamp) {
    $('#flickr1').attr('href', "javascript:popup(\"https://www.flickr.com/search/?text=" + valeurChamp + "&license=4%2C5%2C9%2C10\")");
    $('#wikipedia1').attr('href', "javascript:popup(\"https://fr.wikipedia.org/wiki/" + valeurChamp + "\")");
    $('#noun1').attr('href', "javascript:popup(\"https://thenounproject.com/search/?q=" + valeurChamp + "\")");
}

function recupindice2(valeurChamp) {
    $('#flickr2').attr('href', "javascript:popup(\"https://www.flickr.com/search/?text=" + valeurChamp + "&license=4%2C5%2C9%2C10\")");
    $('#wikipedia2').attr('href', "javascript:popup(\"https://fr.wikipedia.org/wiki/" + valeurChamp + "\")");
    $('#noun2').attr('href', "javascript:popup(\"https://thenounproject.com/search/?q=" + valeurChamp + "\")");
}

function recupindice3(valeurChamp) {
    $('#flickr3').attr('href', "javascript:popup(\"https://www.flickr.com/search/?text=" + valeurChamp + "&license=4%2C5%2C9%2C10\")");
    $('#wikipedia3').attr('href', "javascript:popup(\"https://fr.wikipedia.org/wiki/" + valeurChamp + "\")");
    $('#noun3').attr('href', "javascript:popup(\"https://thenounproject.com/search/?q=" + valeurChamp + "\")");
}

function recupindice4(valeurChamp) {
    $('#flickr4').attr('href', "javascript:popup(\"https://www.flickr.com/search/?text=" + valeurChamp + "&license=4%2C5%2C9%2C10\")");
    $('#wikipedia4').attr('href', "javascript:popup(\"https://fr.wikipedia.org/wiki/" + valeurChamp + "\")");
    $('#noun4').attr('href', "javascript:popup(\"https://thenounproject.com/search/?q=" + valeurChamp + "\")");
}

// POPUP
function popup(page) {
   window.open(page,'popup','width=1500,height=900');
}
