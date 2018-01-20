file_news=/bbs/innd/newsfeeds.bbs
file_node=/bbs/innd/nodelist.bbs
file_stop=/bbs/innd/stop.bbs
path_act=/bbs/innd/active
path_log=/bbs/innd/log

news=$1
opt=$2

now=$(date +%m%d-%H)

group="新聞群組"
board="站內看板"

echo "From: 系統日誌"
echo "Subject: NEWS 轉信檢查 $now"
echo

printf "%-30s --> %-20s 2 N 0\n" $group $board
echo "-----------------------------------------------------------------"


i=$news

  serv=$(grep -w "$i " $file_news | awk -F' ' '{print $3}')
  board=$(grep -w "$i " $file_news | awk -F' ' '{print $2}')
  addr=$(grep -w "$serv" $file_node | awk -F' ' '{print $2}')
  stop=$(grep -w "$serv" $file_stop)

  file_log=$path_log/$i.log

  if [ -z $stop] && [ ! -z $addr ]
  then
    /bbs/innd/bbsnnrp $opt $addr $path_act/$i.active > $file_log
  fi
  if [ ! -f $file_log ]
  then
     echo "$i" > $file_log
  fi

    c1=$(grep -w $i $file_log | wc -l)
    let "c1 = $c1"

    c2=$(grep -v $i $file_log | wc -l)
    let "c2 = $c2"

    c3=$(grep "terminated." $file_log | wc -l)
    let "c3 = $c3"
 
    msg=""

    if [ $c1 -lt 2 ]; then msg="err"; fi

    printf "%-30s --> %-20s %d %d %d %s\n" $i $board $c1 $c2 $c3 $msg
    mv $file_log $file_log.OLD

