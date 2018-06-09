

function prog_submit()
{
   if (divmot.style.backgroundColor != "rgb(102, 171, 82)")
   {
      window.alert("Tous les champs ne sont pas renseignés correctement !";
      return false;
   }
    else
   {
     window.close();
    }
}

function tafonction()
{
  // traitement
  setTimeout(tafonction,10); /* rappel après 2 secondes = 2000 millisecondes */
  if (document.getElementById('mot').value &&
      document.getElementById('result0').style.display == 'inline' &&
      document.getElementById('auteur0').value &&
      document.getElementById('date0').value &&
      divindice1.style.backgroundColor == "rgb(102, 171, 82)" &&
      divindice2.style.backgroundColor == "rgb(102, 171, 82)" &&
      divindice3.style.backgroundColor == "rgb(102, 171, 82)" &&
      divindice4.style.backgroundColor == "rgb(102, 171, 82)")
  {
    document.getElementById('divmot').style.background="rgb(102, 171, 82)";
  }
  else if(document.getElementById('mot').value ||
          document.getElementById('result0').style.display == 'inline' ||
          document.getElementById('auteur0').value ||
          document.getElementById('date0').value ||
          divindice1.style.backgroundColor == "rgb(102, 171, 82)" ||
          divindice2.style.backgroundColor == "rgb(102, 171, 82)" ||
          divindice3.style.backgroundColor == "rgb(102, 171, 82)" ||
          divindice4.style.backgroundColor  == "rgb(102, 171, 82)")
  {
    document.getElementById('divmot').style.background="rgb(247, 147, 30)";
  }
  else
  {
    document.getElementById('divmot').style.background="rgb(228, 38, 19)";
  }


  // INDICE
  for (var i = 1; i <= 3; i++) {
    if (document.getElementById('indice' + i).value &&
        document.getElementById('auteur' + i).value &&
        document.getElementById('date' + i).value &&
        document.getElementById('result' + i).style.display == 'inline')
      {
         document.getElementById('divindice' + i).style.background="rgb(102, 171, 82)";
      }
    else if (document.getElementById('indice' + i).value ||
             document.getElementById('auteur' + i).value ||
             document.getElementById('date' + i).value ||
             document.getElementById('result' + i).style.display == 'inline')
    {
      document.getElementById('divindice' + i).style.background="rgb(247, 147, 30)";
    }
    else
    {
      document.getElementById('divindice' + i).style.background="rgb(228, 38, 19)";
    }
  }


// RECOMPENSE
  if (recompense.value &&
      legende.value &&
      auteur4.value &&
      date4.value &&
      document.getElementById('result' + 4).style.display == 'inline')
   {
     document.getElementById('divindice4').style.background="rgb(102, 171, 82)";
   }
  else if (recompense.value ||
           legende.value ||
           auteur4.value ||
           date4.value ||
           document.getElementById('result' + 4).style.display == 'inline')
  {
     document.getElementById('divindice4').style.background="rgb(247, 147, 30)";
  }
  else
  {
    document.getElementById('divindice4').style.background="rgb(228, 38, 19)";
  }

}
