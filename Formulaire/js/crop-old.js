function sqlcropimg(valeurChamp, num) {
  $('#testimg' + num).attr('src', valeurChamp);
  if (document.getElementById('testimg' + num).height == 430 || document.getElementById('testimg' + num).height == 374 || document.getElementById('testimg' + num).height <= 0)
    {
      document.getElementById('result' + num).style.display = 'none';
    }
    else
    {
      document.getElementById('result' + num).style.display = 'inline';
      sqlpopupResize("resize.php?src=" + valeurChamp + "&num=" + num, num);
      sqltest(id);
    }
}

// POPUP
function sqlpopupResize(page, id) {
  document.getElementById('result' + id).style.display = 'inline';
  window.open(page, 'popup','width=900,height=900');
  sqltest(id);
}

function sqltest(i)
{
  setTimeout(sqltest, 10, i);
  sessionStorage.clear();
  $('#result' + i).attr('src', "tmp/image" + i + "-crop.jpg");
}
