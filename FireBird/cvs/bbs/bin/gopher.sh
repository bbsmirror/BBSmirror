#!/bin/sh 
TERM=vt100
export TERM
LC_CTYPE=iso_8859_1
export LC_CTYPE
LOCALDOMAIN=pine.ncu.edu.tw
export LOCALDOMAIN
stty pass8 -istrip
exec /usr/local/bin/gopher.bin -s %1
