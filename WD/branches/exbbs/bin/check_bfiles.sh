board=Test
opt=nothing

if [ ! -z $1 ]; then board=$1; fi
if [ ! -z $2 ]; then opt=$2; fi

bpath=/bbs/boards/$board
dpath=$bpath/.DIR

echo $bpath
files=$(ls $bpath)

for i in $files
do
  result=$(/bbs/bin/check_bfile $dpath $i)
#  echo $result
  if [ -z $result ]
  then
    echo $i
    if [ $opt = del ]
    then
       rm -f $bpath/$i
    fi
  fi
done