
file_book=/bbs/innd/guestbook.bbs
file_outgo=/bbs/innd/out.http
file_cancel=/bbs/innd/cancel.http

now=$(date +%m%d-%H)

source="source"
board="board"

echo "From: 系統日誌"
echo "Subject: HTTP 轉信檢查 $now"
echo

if [ ! -f $file_book ]
then
  echo "$file_book error"
  exit -1
fi

printf "%-30s --> %-13s\n" $source $board
echo "-----------------------------------------------------------------"

servs=$(grep -v "#" $file_book | awk -F' ' '{print $1}')

for i in $servs
do
  board=$(grep -w "$i" $file_book | awk -F' ' '{print $2}')
  ssn=$(grep -w "$i" $file_book | awk -F' ' '{print $3}')
  lastssn=$(grep -w "$i" $file_book | awk -F' ' '{print $4}')
  let "ssn = $ssn"
  let "lastssn = $lastssn"

  if [ ! -z $board ]
  then
     source=$i"get_db_ssn.asp?ssn="$ssn
     ssns=$(lynx -source $source)
     let "count = 0"
       for j in $ssns
       do
          source=$i"check_db_post.asp?ssn="$j
          result=$(lynx -source $source | grep OK)
          if [ $result = OK ]
          then
            source=$i"get_db_post.asp?ssn="$j
            result=$(lynx -source $source | /bbs/bin/bbspost $board | grep OK)
            if [ $result = OK ]
            then
              let "count = count + 1"
            fi
          fi
       done

     outgo=$(/bbs/innd/guestbook.outgo.sh $i $board)
     let "outgo = $outgo"

     if [ $outgo -gt 0 ] || [ $count -gt 0 ]
     then
       let "lastssn = $ssn"
       source=$i"get_db_ssn.asp"
       result=$(lynx -source $source)
       let "ssn = $result"
     fi

     printf "%-30s --> %-13s %d %d %d %d\n" $i $board $ssn $lastssn $count $outgo
     echo "$i $board $ssn $lastssn $count" >> $file_book.new
  fi
done

if [ -f $file_outgo ]; then rm $file_outgo; fi
if [ -f $file_cancel ]; then rm $file_cancel; fi

mv $file_book $file_book.old
mv $file_book.new $file_book
