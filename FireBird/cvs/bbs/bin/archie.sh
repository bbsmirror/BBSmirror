#!/bin/sh
# $Id: archie.sh,v 1.1 2000/01/15 01:50:28 edwardc Exp $
echo
echo "·j´M¤¤, ½Ðµy­Ô....."
echo "Firebird BBS ARCHIE Service." `date` > /home/bbs/tmp/archie.$2.$3
echo "Search for: $1" >> /home/bbs/tmp/archie.$2.$3
exec /usr/local/bin/archie $1 >> /home/bbs/tmp/archie.$2.$3
