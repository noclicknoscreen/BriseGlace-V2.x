function cropimg(valeurChamp, num) {
    $('#testimg' + num).attr('src', valeurChamp);
    if (document.getElementById('testimg' + num).height == 430 || document.getElementById('testimg' + num).height == 374 || document.getElementById('testimg' + num).height <= 0)
    {
      document.getElementById('result' + num).style.display = 'none';
    }
    else
    {
      document.getElementById('result' + num).style.display = 'inline';
      popupResize("resize.php?src=" + valeurChamp + "&num=" + num, num);
    }
}

// POPUP
function popupResize(page, id) {
  if (document.getElementById('testimg' + id).height == 430 || document.getElementById('testimg' + id).height == 374 || document.getElementById('testimg' + id).height <= 0)
  {
    document.getElementById('result' + id).style.display = 'none';
    $('#result' + id).attr('src', "");
  }
  else {
    window.open(page, 'popup','width=900,height=900');
    test(id);
  }
}

function test(i)
{
  setTimeout(test, 10, i);
  sessionStorage.clear();
  $('#result' + i).attr('src', "tmp/image" + i + "-crop.jpg");
}
