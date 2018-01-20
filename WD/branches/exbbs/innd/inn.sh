# word1=$1
# word2=$1

word1=innbbsd
word2=/bbs/innd/innbbsd

if [ $# = 2 ]
then
   word2=$2
fi

inn=$(ps -ax | grep $word1 | awk -F' ' '{print $5}')
key=0
for i in $inn
do
  if [ $i = $word1 ] || [ $i = $word2 ]
  then
    echo -n "$i found, "
    key=1
  fi
done

if [ $key = 0 ]
then
  echo "recall this program..."
  $word1
else
  echo "nothing to do..."
fi
