news=$(grep -v "#" newsfeeds.bbs | awk -F' ' '{print $1}')

for i in $news
do
   file=/bbs/innd/active/$i.active
   if [ ! -f $file ]  
   then
      echo "$i 0000000000 0000000000 y"
      echo "$i 0000000000 0000000000 y" > $file
   fi
done
