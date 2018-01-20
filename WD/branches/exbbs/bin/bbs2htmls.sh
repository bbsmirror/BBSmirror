if [ $# -lt 2 ]
then
  echo "error"
  exit -1
fi

source=$1
target=$2

files=$(ls $source)

for i in $files
do
  bbs2htmlcode $source/$i > $target/$i.html
done
