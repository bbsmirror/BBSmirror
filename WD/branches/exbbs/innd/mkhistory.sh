/bbs/innd/ctlinnbbsd shutdown
rm -f /bbs/innd/history*
/bbs/innd/mkhistory /bbs/innd/history
/bbs/innd/innbbsd
usleep 20000000
/bbs/innd/ctlinnbbsd hismaint
/bbs/innd/ctlinnbbsd hismaint
/bbs/innd/ctlinnbbsd hismaint
