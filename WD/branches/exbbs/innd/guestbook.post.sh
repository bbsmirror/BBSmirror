prog_1=/bbs/innd/guestbook.sh
prog_2=/bbs/bin/bbspost
board=BBSnnrp

log_1=/bbs/log/guestbook.log

$prog_1 > $log_1
$prog_2 $board < $log_1
mv $log_1 $log_1.OLD

