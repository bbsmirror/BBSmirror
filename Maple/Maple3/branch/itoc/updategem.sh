#!/bin/bash
#本程式用來自動更新itoc-Maple版內的精華區。
#請不要移除下載下來的原始檔，因為要作為版本判斷之用。
#參數請加上itoc版的版名。
#用法: updategem.sh itoc
dir=~/tmp
if [ ! -d $dir ]; then
	mkdir $dir
fi
if [ -z "$1" ]; then
	echo "參數請加上itoc版的版名。"
	echo '用法: ./updategem.sh itoc(這是itoc版的版名)'
	echo "usage: ./updategem.sh itoc"
	exit
else
	brd=`ls ~/gem/brd|grep "\<$1\>"`
	if [ -z "$brd" ]; then
		echo "$1這個版不存在"
		echo "$1 doesn't exist"
		exit
	fi
fi
oldfile=`ls $dir|grep itoc_gem`
newfile=`lynx -dump http://processor.tfcis.org | grep http | grep itoc_gem|awk '{print $2}'`
if [ -f $dir/$oldfile ]; then
	oldfiledate=`echo "$oldfile"| sed -e 's/itoc_gem_//' -e 's/.tgz//'`
	newfiledate=`echo "$newfile"| sed -e 's/^.*itoc_gem_//' -e 's/.tgz//'`
	if [ "$oldfiledate" == "$newfiledate" ]; then
		echo "精華區已經是最新版，目前不需更新。"
		echo "It's already up to date."
		exit
	else
		rm $dir/$oldfile
	fi
fi
filename=${newfile##*/}
lynx --dump "$newfile" > "$dir"/"$filename"
tar zxf $dir/$filename -C $dir
cp -rf $dir/gem/* ~/gem/brd/$1/
rm -rf $dir/gem
echo "$1版精華區更新完成"
echo "$1 gem update successful"
