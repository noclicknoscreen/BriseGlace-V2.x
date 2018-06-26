//RECHERCHE D'IMAGE

function recupmot(valeurChamp, num) {
    $('#flickr0' + num).attr('href', "javascript:popup(\"https://www.flickr.com/search/?text=" + valeurChamp + "&license=4%2C5%2C9%2C10\")");
    $('#wikipedia0' + num).attr('href', "javascript:popup(\"https://fr.wikipedia.org/wiki/" + valeurChamp + "\")");
    $('#noun0' + num).attr('href', "javascript:popup(\"https://thenounproject.com/search/?q=" + valeurChamp + "\")");
}

function recupindice1(valeurChamp, num) {
    $('#flickr1' + num).attr('href', "javascript:popup(\"https://www.flickr.com/search/?text=" + valeurChamp + "&license=4%2C5%2C9%2C10\")");
    $('#wikipedia1' + num).attr('href', "javascript:popup(\"https://fr.wikipedia.org/wiki/" + valeurChamp + "\")");
    $('#noun1' + num).attr('href', "javascript:popup(\"https://thenounproject.com/search/?q=" + valeurChamp + "\")");
}

function recupindice2(valeurChamp, num) {
    $('#flickr2' + num).attr('href', "javascript:popup(\"https://www.flickr.com/search/?text=" + valeurChamp + "&license=4%2C5%2C9%2C10\")");
    $('#wikipedia2' + num).attr('href', "javascript:popup(\"https://fr.wikipedia.org/wiki/" + valeurChamp + "\")");
    $('#noun2' + num).attr('href', "javascript:popup(\"https://thenounproject.com/search/?q=" + valeurChamp + "\")");
}

function recupindice3(valeurChamp, num) {
    $('#flickr3' + num).attr('href', "javascript:popup(\"https://www.flickr.com/search/?text=" + valeurChamp + "&license=4%2C5%2C9%2C10\")");
    $('#wikipedia3' + num).attr('href', "javascript:popup(\"https://fr.wikipedia.org/wiki/" + valeurChamp + "\")");
    $('#noun3' + num).attr('href', "javascript:popup(\"https://thenounproject.com/search/?q=" + valeurChamp + "\")");
}

function recupindice4(valeurChamp, num) {
    $('#flickr4' + num).attr('href', "javascript:popup(\"https://www.flickr.com/search/?text=" + valeurChamp + "&license=4%2C5%2C9%2C10\")");
    $('#wikipedia4' + num).attr('href', "javascript:popup(\"https://fr.wikipedia.org/wiki/" + valeurChamp + "\")");
    $('#noun4' + num).attr('href', "javascript:popup(\"https://thenounproject.com/search/?q=" + valeurChamp + "\")");
}

// POPUP
function popup(page) {
   window.open(page,'popup','width=1500,height=900');
}
