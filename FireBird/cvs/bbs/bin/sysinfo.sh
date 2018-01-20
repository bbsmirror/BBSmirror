#!/bin/sh
echo "查詢時間為:" > /home/bbs/tmp/sysinfo.$1
date >> /home/bbs/tmp/sysinfo.$1
/usr/bin/uptime >> /home/bbs/tmp/sysinfo.$1
echo "" >> /home/bbs/tmp/sysinfo.$1
echo "*****  記憶體使用狀況 (以 KB 為單位) *****" >> /home/bbs/tmp/sysinfo.$1
free -t >> /home/bbs/tmp/sysinfo.$1
/usr/bin/ipcs -mu >> /home/bbs/tmp/sysinfo.$1
/usr/bin/ipcs >> /home/bbs/tmp/sysinfo.$1
echo "" >> /home/bbs/tmp/sysinfo.$1
echo "*****  硬碟使用狀況 (以 KB 為單位)  *****" >> /home/bbs/tmp/sysinfo.$1
df   >> /home/bbs/tmp/sysinfo.$1
echo "" >> /home/bbs/tmp/sysinfo.$1
echo "" >> /home/bbs/tmp/sysinfo.$1
echo "*****  信件傳輸狀況  *****" >> /home/bbs/tmp/sysinfo.$1
/usr/sbin/mailstats >> /home/bbs/tmp/sysinfo.$1
echo "" >> /home/bbs/tmp/sysinfo.$1
echo "" >> /home/bbs/tmp/sysinfo.$1
echo "*****  Kernel Interface Statistics  *****" >> /home/bbs/tmp/sysinfo.$1
netstat -i >> /home/bbs/tmp/sysinfo.$1
echo "" >> /home/bbs/tmp/sysinfo.$1
echo "" >> /home/bbs/tmp/sysinfo.$1
echo "*****  Process 資訊一覽  *****" >> /home/bbs/tmp/sysinfo.$1
ps -aux >> /home/bbs/tmp/sysinfo.$1
echo "" >> /home/bbs/tmp/sysinfo.$1
