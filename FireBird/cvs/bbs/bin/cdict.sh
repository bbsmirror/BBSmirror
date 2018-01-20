echo
echo "偵測到英文字, 翻查英漢字典..."
echo
echo "請稍候...."
exec /usr/local/bin/cdict $1 > /home/bbs/tmp/dict.$2_$3
