#!/bin/sh 
#
# Last updated: by netty, Apr.12,1995
#
PATH=/bin:/usr/ucb:/usr/etc:/usr/local/bin
stty pass8
stty -parenb cs8 -istrip
username=$1
IRCNICK=${username}; export IRCNICK
USER=${username}; export USER
IRCNAME=${username}; export IRCNAME
NAME=${username}; export NAME
HOME=home/$username; export HOME
IRCRC=$HOME/.ircrc; export IRCRC
TERM=vt100
export TERM
PAGER=/usr/bin/cless
export PAGER
LC_CTYPE=iso_8859_1
export LC_CTYPE
LOCALDOMAIN=.
export LOCALDOMAIN
IRCSERVER=irc.csie.ncu.edu.tw
export IRCSERVER
exec /usr/local/bin/irc
