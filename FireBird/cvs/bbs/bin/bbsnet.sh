stty pass8
stty -parenb cs8 -istrip
lcctype=iso_8859_1;
LC_CTYPE=$lcctype; export LC_CTYPE
exec /home/bbs/bin/bbsnet
