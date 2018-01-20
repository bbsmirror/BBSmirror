#!/bin/sh
cp -af /home/bbs/0Announce/bbslist/countusr /home/bbs/0Announce/bbslist/countusr.last
cp -af /home/bbs/0Announce/bbslist/newacct.today /home/bbs/0Announce/bbslist/newacct.last
cp -af /home/bbs/etc/posts/day /home/bbs/etc/posts/day.last
/home/bbs/bin/usage 0
/home/bbs/bin/usage 1
rm -f /home/bbs/use_board
cp /dev/null /home/bbs/0Announce/bbslist/toplogin
bin/bbstop /home/bbs 100 1 > /home/bbs/0Announce/bbslist/toplogin
cp /dev/null /home/bbs/0Announce/bbslist/toppost
bin/bbstop /home/bbs 100 2 > /home/bbs/0Announce/bbslist/toppost
cp /dev/null /home/bbs/0Announce/bbslist/topstay
bin/bbstop /home/bbs 100 3 > /home/bbs/0Announce/bbslist/topstay
cp /dev/null /home/bbs/0Announce/bbslist/topall
bin/bbstop /home/bbs 100 4 > /home/bbs/0Announce/bbslist/topall
