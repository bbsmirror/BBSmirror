
check=$(find /bbs/usboard -size +12000k -exec ls {} \;)

if [ ! -z $check ] && [ $check = /bbs/usboard ]
then

  echo "reset use board.."

  cp /bbs/.BOARDS /bbs/.BOARDS.OLD
  setboardtime /bbs/.BOARDS /bbs/.BOARDS.NEW
  cp /bbs/.BOARDS.NEW /bbs/.BOARDS
  rm /bbs/usboard

else
  echo "nothing to do.."
fi
