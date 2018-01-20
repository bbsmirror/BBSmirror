node=/bbs/innd/nodelist.bbs

servers=$(grep -v "#" $node | awk -F' ' '{print $1}')

for i in $servers
do
  addr=$(grep -w "$i" $node | awk -F' ' '{print$2'})
  echo $i $addr
done

