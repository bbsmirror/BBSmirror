echo
echo "偵測到中文字, 作漢英查詢..."
echo
echo "請稍候...."
exec /usr/local/bin/cdict -c -m=100 $1 > /home/bbs/tmp/dict.$2_$3
