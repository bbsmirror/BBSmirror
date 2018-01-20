
file_outgo=/bbs/innd/out.http
cancel_outgo=/bbs/innd/cancel.http

if [ $# -lt 2 ]
then
   echo "usage: cmd serv board"
   exit -1
fi

if [ ! -f $file_outgo ]; then echo "out.http" > $file_outgo; fi

serv=$1
board=$2

let "count = 0"
if [ -f $file_outgo ]
then
  files=$(grep -w $board $file_outgo | awk -F' ' '{print $2}')
  for i in $files
  do
    fpath=/bbs/boards/$board/$i
    cancel=
    if [ -f $cancel_outgo ] 
    then
      cancel=$(grep -w $i $cancel_outgo | awk -F' ' '{print $1}')
    fi

    if [ -f $fpath ] && [ -z $cancel ]
    then
      source=$serv"save_db_post.asp"
      result=$(/bbs/bin/bbsencode $fpath | lynx -post_data -source $source | grep OK)
      if [ ! -z $result ] && [ $result = OK ]
      then
        let "count = count + 1"
      fi
    fi
  done
  grep -w $board $file_outgo -v > $file_outgo.new
  mv $file_outgo $file_outgo.old
  mv $file_outgo.new $file_outgo
fi

echo $count
