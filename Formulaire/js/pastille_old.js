function pastille_old(maxidi)
{
  setTimeout(pastille_old, 10, maxidi);
  // INDICE
  for (var j = 0; j < maxidi; j++) {

  // On ne peux pas cocher la case si l'énigme n'est pas compléte
  if (document.getElementById('sqldivmot' + j).style.backgroundColor == "rgb(228, 38, 19)" || document.getElementById('sqldivmot' + j).style.backgroundColor == "rgb(247, 147, 30)")
  {
    document.getElementById('check' + j).checked = false;
  }

    // MOT A TROUVER PASTILLE
    if (document.getElementById('sqlmot' + j).value &&
        document.getElementById('sqltheme' + j).value &&
        document.getElementById('result0' + j).style.display == 'inline' &&
        document.getElementById('sqlauteur0' + j).value &&
        document.getElementById('sqldate0' + j).value &&
        document.getElementById('sqldivindice1' + j).style.backgroundColor == "rgb(102, 171, 82)" &&
        document.getElementById('sqldivindice2' + j).style.backgroundColor == "rgb(102, 171, 82)" &&
        document.getElementById('sqldivindice3' + j).style.backgroundColor == "rgb(102, 171, 82)" &&
        document.getElementById('sqldivindice4' + j).style.backgroundColor == "rgb(102, 171, 82)")
    {
      document.getElementById('sqldivmot' + j).style.background ="rgb(102, 171, 82)";
    }
    else if(document.getElementById('sqlmot' + j).value ||
            document.getElementById('sqltheme' + j).value ||
            document.getElementById('result0' + j).style.display == 'inline' ||
            document.getElementById('sqlauteur0' + j).value ||
            document.getElementById('sqldate0' + j).value ||
            document.getElementById('sqldivindice1' + j).style.backgroundColor == "rgb(102, 171, 82)" ||
            document.getElementById('sqldivindice2' + j).style.backgroundColor == "rgb(102, 171, 82)" ||
            document.getElementById('sqldivindice3' + j).style.backgroundColor == "rgb(102, 171, 82)" ||
            document.getElementById('sqldivindice4' + j).style.backgroundColor == "rgb(102, 171, 82)")
    {
      document.getElementById('sqldivmot' + j).style.background="rgb(247, 147, 30)";
    }
    else
    {
      document.getElementById('sqldivmot' + j).style.background="rgb(228, 38, 19)";
    }

    // INDICE PASTILLE
    for (var i = 1; i <= 3; i++) {
      if (document.getElementById('sqlindice' + i + j).value &&
          document.getElementById('sqlauteur' + i + j).value &&
          document.getElementById('sqldate' + i + j).value &&
          document.getElementById('result' + i + j).style.display == 'inline')
        {
           document.getElementById('sqldivindice' + i + j).style.background="rgb(102, 171, 82)";
        }
      else if (document.getElementById('sqlindice' + i + j).value ||
               document.getElementById('sqlauteur' + i + j).value ||
               document.getElementById('sqldate' + i + j).value ||
               document.getElementById('result' + i + j).style.display == 'inline')
      {
        document.getElementById('sqldivindice' + i + j).style.background="rgb(247, 147, 30)";
      }
      else
      {
        document.getElementById('sqldivindice' + i + j).style.background="rgb(228, 38, 19)";
      }
    }

    // RECOMPENSE PASTILLE
      if (document.getElementById('sqlrecompense' + j).value &&
          document.getElementById('sqllegende' + j).value &&
          document.getElementById('sqlauteur4' + j).value &&
          document.getElementById('sqldate4' + j).value &&
          document.getElementById('result4' + j).style.display == 'inline')
       {
         document.getElementById('sqldivindice4' + j).style.background="rgb(102, 171, 82)";
       }
      else if (document.getElementById('sqlrecompense' + j).value ||
              document.getElementById('sqllegende' + j).value ||
              document.getElementById('sqlauteur4' + j).value ||
              document.getElementById('sqldate4' + j).value ||
              document.getElementById('result4' + j).style.display == 'inline')
      {
         document.getElementById('sqldivindice4' + j).style.background="rgb(247, 147, 30)";
      }
      else
      {
        document.getElementById('sqldivindice4' + j).style.background="rgb(228, 38, 19)";
      }

  }
}
