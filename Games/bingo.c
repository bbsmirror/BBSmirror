#include "bbs.h"

int 
bingo()
{

 int place[5][5][3]={{{2,2,0},{2,6,0},{2,10,0},{2,14,0},{2,18,0}},
       		     {{4,2,0},{4,6,0},{4,10,0},{4,14,0},{4,18,0}},
  		     {{6,2,0},{6,6,0},{6,10,0},{6,14,0},{6,18,0}},
  		     {{8,2,0},{8,6,0},{8,10,0},{8,14,0},{8,18,0}},
  		     {{10,2,0},{10,6,0},{10,10,0},{10,14,0},{10,18,0}}};

 int bet,i=0,j=0,k=0,used[25]={0},account=16,ranrow,rancol,line=0,pp=0;
 char co[2];
 int save_pager;
 char m1[8];
 int money;
 save_pager=currutmp->pager;
 currutmp->pager =2;
 setutmpmode(BINGO);
 
while(-1)
{
account=14;
for(i=0;i<25;i++)
used[i]=0;
for(i=0;i<5;i++)
for(j=0;j<5;j++)
place[i][j][2]=0;
i=0;j=0;k=0;
line=0;pp=0; 

 clear();
  do
    {
       getdata(21, 0,"­n¤U¦h¤Ö©O(¤W­­10000)? «ö Enter Â÷¶}>", m1, 6, 1, 0);
          money=atoi(m1);
             if(money<0) money=0;
               } while(money>10000);
                 if(!money) 
                 {
                 currutmp->pager = save_pager;
                 return 0;
                 }
                   if(money>cuser.money)
                     {
                        pressanykey("§Aªº²{ª÷¤£°÷³á.. :)");
                           return 0;
                             }
 demoney(money);                            
 clear();
 move(1,0);
 for(i=0;i<=10;i++)
 {
 if(i%2==0)
 outs("[1;34;40m¡½¡½¡½¡½¡½¡½¡½¡½¡½¡½¡½[0m\n"); 
 else
 outs("[1;33;40m¡½  ¡½  ¡½  ¡½  ¡½  ¡½[0m\n");
 }
 for(i=1;i<=25;i++)
 {
 move(22,pp+3);
 pp+=3;
 prints("%2d",i);
 }
 while(account>0)
 {
 move(21,0);
 prints("±z©|¦³ %d ¦¸¾÷·|",account);
 getdata(20,0,"½Ð¿é¤J±zªº¸¹½X : ",co,3,DOECHO,0);
 bet=atoi(co);
 if(bet<=0 ||bet > 25 || used[bet-1]==1) continue;
  used[bet-1]=1;
  ranrow=random();
  ranrow=ranrow%5;
  rancol=random();
  rancol=rancol%5;

  while(place[ranrow][rancol][2]==1)
  {
     ranrow=random();
      ranrow=ranrow%5;
        rancol=random();
        rancol=rancol%5;
  }
  place[ranrow][rancol][2]=1;  
  move((place[ranrow][rancol][0]),(place[ranrow][rancol][1]));
  prints("%2s",co);
  account--;
  pp=0;
  for(k=0;k<bet;k++)
  pp+=3;
   move(22,pp);
   prints("  ");
   
 }
  
 for(i=0;i<5;i++)
   {
    if (place[i][0][2]==1 && place[i][1][2]==1 && place[i][2][2]==1 && place[i][3][2]==1 &&place[i][4][2]==1 )
      line++;
   }   
 for(i=0;i<5;i++)
  {
   if(place[0][i][2]==1 &&place[1][i][2]==1 &&place[2][i][2]==1 &&place[3][i][2]==1 &&place[4][i][2]==1 )
   line++;
  }

if(place[0][0][2]==1 && place[1][1][2]==1 && place[3][3][2]==1 && place[4][4][2]==1 && place[2][2][2]==1)
line++;
if(place[0][4][2]==1 && place[1][3][2]==1 && place[2][2][2]==1 && place[3][2][2]==1 && place[0][4][2]==1)
line++;
 
move(18,0);
prints("®¥³ß§A...³s¦³ %d ±ø½u ",line); 
prints("²bÁÈ¼úª÷ %d ¤¸",line*(money/2));
if(line>0) 
{
inmoney(money+(line*(money/2)));
}
game_log(BINGO," ³s¤F %d ±ø½u ÁÈ¤F %d ¤¸ ",line,(line*(money/2)));
 pressanykey(NULL);
} 
 currutmp->pager=save_pager;
 return 0;
}       
  
