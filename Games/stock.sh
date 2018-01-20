#!/usr/bin/perl
open(BBSPOST, "> /home/bbs/etc/game/stock_now");
open(STOCK, "/usr/local/bin/lynx -source http://www.polaris.com.tw/polaris/www/price/c_et.htm |");

while (<STOCK>)
{
  print BBSPOST if($_ ne "\n") ;
}
close STOCK;

print BBSPOST "\n--\n";
print BBSPOST "◆ Origin: ^[[31;1m二^[[33;1m三^[[32;1m子^[[0m (140.113.124.116)※ 我來自:[兩參證券交易所]   ";

close BBSPOST;
