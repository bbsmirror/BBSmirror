/*---------------------------------------------------------------------------*/
/* ¾Ô°«¯S°Ï                                                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
#include <time.h>
#include "bbs.h"
#include "pip.h"
extern struct chicken d;
extern time_t start_time;
extern time_t lasttime;
#define getdata(a, b, c , d, e, f, g) getdata(a,b,c,d,e,f,NULL,g)

#ifndef MAPLE
extern char BoardName[];
#endif  // END MAPLE

struct playrule badmanlist[] = {
"º_¾ð©Ç",	 60,0,	20,0,	20,	20,	 20,	150, "11101",	0,0,
"ºô¸ôÅ]",	 60,0,	20,0,	30,	30,	 30,	200, "01111",	0,0,
"Ä¨Û£¤p©Ç",	 80,0,	40,0,	50,	35,	 60,	250, "11110",	0,0,
"¬rÃÈ",		 85,0,	30,0,	80,	90,	 80,	500, "10111",	0,0,
"´cª¯",		 90,0,  50,0,   75,	70,	 60,	550, "11010",	0,0,
"¬õ²´°­¿ß",	130,0,	50,0,	75,	90,	 70,	500, "11011",	0,0,
"µµ¦âÅ]ÃT",	140,0,	60,0,	80,	80,	 80,	550, "10101",	0,0,
"©Çª«Á­½¸",	150,0,	70,0,	85,	70,	 67,	500, "11110",	0,0,
"»jµïºë",	180,0,	50,0,   90,	90,	 80,	850, "00111",	0,0,
"­¹¤H§Å®v",	175,0, 100,0,  100,	80,	 60,    800, "11010",	0,0,
"¤jºl©Ç",	240,0,  80,0,  110,    100,	 70,    800, "00111",	0,0,
"¥Õ¦â´cÅ]",	250,0,  60,0,  120,    110,	 80,    900, "01011",	0,0,
"¦º¯«Å]",	280,0,  80,0,  150,    120,	 90,   1200, "00011",   0,0,
"¤j®£Às",	300,0,	50,0,  160,    120,	 90,   1500, "11001",	0,0,
"¶W¯Å¼Q¤õÀs",	500,0, 100,0,  250,    250,	150,   1500, "11000",	0,0,
"¾uÅ\\ÀY©Ç",	600,0, 400,0,  350,    400,	250,   2000, "00110",	0,0,
"ªü±j¤@¸¹",	700,0, 500,0,  600,    900,     500,   2000, "10011",	0,0,
"­±¨ã©Ç¤H",	700,0, 500,0,  800,    850,	300,   2000, "11100",	0,0,
"U2¥~¬P¤H",	800,0, 600,0,  800,    800,	600,   2000, "11010",	0,0,
"¤¤°êÃ¦«Í",	800,0, 600,0, 1000,   1000,     500,   2000, "10100",	0,0,
"±m¦â­©ªø",     900,0, 800,0, 1200,   1200,     600,   3000, "11100",   0,0,
"Å]­µ¦N¥L¤â",  1000,0, 850,0, 1400,   1000,     650,   3000, "11001",   0,0,
"¸U¦~¦ÑÀt",    1200,0,1000,0, 1300,   1500,     500,   3000, "01011",   0,0,
"¤K¯«",	       1200,0, 900,0, 1500,   1300,     800,   3000, "10101",   0,0,
"ÅK­±¤H",      1500,0,1200,0, 1800,   1800,    1200,   4000, "00011",   0,0,
"¤j¼L",        1600,0,1000,0, 1700,   1800,    1100,   4000, "00110",   0,0,
"¾uÅ\\§L",      1700,0,1500,0, 1800,   1800,    1250,  4000, "10110",   0,0,
"º²¤Æ§¯",      1750,0,1300,0, 1800,   2000,    1000,   4000, "01011",	0,0,
"¨Ï®{",	       2500,0,2500,0, 2500,   2500,    2500,   5000, "10001",   0,0,
"®J¤Î¤ì¤D¥ì",  3500,0,3000,0, 3500,   3500,    2000,   5000, "10110",	0,0,
"¥j¤p¨ß",      5000,0,4500,0, 5000,   6000,    4000,   5000, "11100",   0,0,
"¤Q¦r¾÷¾¹¤H",  6000,0,5000,0, 5500,   6500,    5000,   5000, "01001",	0,0,
"­¸¤Ñ¤p§Å®v",  6500,0,5500,0, 6500,   6000,    6000,   6000, "01101",	0,0,
"¬µ³J¶W¤H",    7000,0,6000,0, 8000,   7000,    6000,   6500, "00001",	0,0,
"Akira",      13500,0,6000,0,15000,  12000,   13000,   8000, "00100",	0,0, 
"Sarah",      15000,0,6000,0,14000,  13000,   12000,   8000, "10000",	0,0, 
"Jacky",      13000,0,6000,0,15000,  12000,   13000,   8000, "01000",	0,0, 
"Wolf",       16000,0,6000,0,13000,  15000,   10000,   8000, "00010",	0,0, 
"Jeffery",    15000,0,6000,0,12000,  14000,   13000,   8000, "00001",	0,0, 
"Kage",       12000,0,6000,0,11000,  11000,   15000,   8000, "10000",	0,0, 
"Lau",        14000,0,6000,0,14000,  13000,   14000,   8000, "01000",	0,0, 
"Lion",       16000,0,6000,0,12000,  15000,   11000,   8000, "00100",	0,0, 
"Shun",       11000,0,6000,0,13000,  12000,   11000,   8000, "00010",	0,0, 
"Aoi",        14000,0,6000,0,13000,  14000,   13000,   8000, "00001",	0,0, 
"Taka",       15000,0,6000,0,11000,  15000,   11000,   8000, "10000",	0,0, 
"Pai",        11000,0,6000,0,11000,  11000,   16000,   8000, "01000",	0,0, 
NULL,		  0,0,	 0,0,	 0,	 0,	  0,	  0,	NULL,	0,0
};


struct magicset treatmagiclist[] = {
"ªvÀøªk³N",	0,	0,	0,	0,	0,	0,
"®ðÀø³N",	5,	1,	20,	0,	10,	0,
"¾®¯«Âk¤¸",     20,     1,	100,    0,	40,	0,
"¤¸ÆFÂk¤ß",     50,     1,	400,    0,	60,	0,
"¤­®ð´Â¤¸",     100,    2,	0,	2,	0,	0,
NULL,		NULL,	NULL,	NULL,	NULL,	NULL,	NULL
};                            
     
struct magicset thundermagiclist[] = {
"¹p¨tªk³N",	0,	0,	0,	0,	0,	0,
"¹p©G",		10,	0,	20,	1,	5,	0,
"¤­¹p©G",	20,	0,	50,	1,	5,	0,
"¤Ñ¹p©G",	40,	0,	100,	1,	5,	0,
"¹p¤§ºô",	100,	0,	250,	1,	10,	0,
"ºÆ¨g¤§¹p",	200,	0,	500,	1,	10,	0,
"¹p¯«¤§»R",	600,	0,	1500,	1,	10,	0,
NULL,		NULL,	NULL,	NULL,	NULL,	NULL,	NULL
};

struct magicset icemagiclist[] = {
"¦B¨tªk³N",	0,	0,	0,	0,	0,	0,
"¦B©G",		10,	0,	20,	1,	5,	0,
"´H¦B©G",	20,	0,	50,	1,	5,	0,
"¥È¦B©G",	40,	0,	100,	1,	5,	0,
"­·¹p¦B¤Ñ",	100,	0,	250,	1,	10,	0,
"µ´¹ï¹s«×¤§¦B",	200,	0,	500,	1,	10,	0,
"¦B¯«¤§»R",	500,	0,	1400,	1,	10,	0,
NULL,		NULL,	NULL,	NULL,	NULL,	NULL,	NULL
};

struct magicset firemagiclist[] = {
"ª¢¨tªk³N",	0,	0,	0,	0,	0,	0,
"¤õ³N",		5,	0,	10,	1,	5,	0,
"ª¢©G",		10,	0,	20,	1,	5,	0,
"ª¢±þ©G",	20,	0,	50,	1,	5,	0,
"·Òº»¯u¤õ",	40,	0,	100,	1,	5,	0,
"¤õÀs´x",	100,	0,	250,	1,	10,	0,
"¤õÀs©Û³ê",	200,	0,	500,	1,	10,	0,
"¤õ¯«¤§»R",	600,	0,	1600,	1,	10,	0,
NULL,		NULL,	NULL,	NULL,	NULL,	NULL,	NULL
};

struct magicset earthmagiclist[] = {
"¤g¨tªk³N",	0,	0,	0,	0,	0,	0,
"¤g©G",		10,	0,	20,	1,	5,	0,
"­¸©¥³N",	20,	0,	50,	1,	5,	0,
"¦aµõ¤Ñ±Y",	40,	0,	100,	1,	5,	0,
"®õ¤sÀ£³»",	100,	0,	250,	1,	10,	0,
"¤gÀs¥l³ê",	200,	0,	500,	1,	10,	0,
"¤s¯«¤§»R",	450,	0,	1300,	1,	10,	0,
NULL,		NULL,	NULL,	NULL,	NULL,	NULL,	NULL
};

struct magicset windmagiclist[] = {
"­·¨tªk³N",	0,	0,	0,	0,	0,	0,
"­·©G",		10,	0,	20,	1,	5,	0,
"±Û­·©G",	20,	0,	50,	1,	5,	0,
"¨g­·³N",	40,	0,	100,	1,	5,	0,
"Às±²­·",	100,	0,	250,	1,	10,	0,
"­·±²´Ý¶³",	200,	0,	500,	1,	10,	0,
"­·¯«¤§»R",	400,	0,	1200,	1,	10,	0,
NULL,		NULL,	NULL,	NULL,	NULL,	NULL,	NULL
};
/*---------------------------------------------------------------------------*/
/* ¾Ô°«¤Hª«¨M©w¨ç¦¡                                                          */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*0~1:2
  2~4:3
  5~9:5
  10~12:3
  13~14:1
  15~19:5
  20~23:4
  24~27:4
  28~33:6
  34~45:12
*/
int
pip_meet_vs_man()
{
  int class;
  int man;
  int lucky;
  class=(d.maxhp*30+d.maxmp*20+d.attack*20+d.resist*15+d.mexp*5+d.hexp*5+d.speed*10)/8500+1;

  if(class==1)
  {
    man=rand()%2;
  }
  else if(class==2)
  { 
    if(rand()%4>0)
    {
      man=rand()%3+2;
    }
    else
    {
      man=rand()%2;
    }
  }
  else if(class==3)
  {
    lucky=rand()%9;
    if(lucky>3)
    {
      man=rand()%5+5;
    }
    else if(lucky<=3 && lucky>0)
    {
      man=rand()%3+2;
    }
    else
    {
      man=rand()%2;
    }
  }  
  else if(class==4)
  {
    lucky=rand()%15;
    if(lucky>5)
    {
      man=rand()%3+10;
    }
    else if(lucky<=5 && lucky>3)
    {
      man=rand()%5+5;
    }
    else 
    {
      man=rand()%5;
    }
  }
  else if(class==5)
  {
    lucky=rand()%20;
    if(lucky>6)
    {
      man=13+rand()%2;
    }
    else if(lucky<=6 && lucky>3)
    {
      man=rand()%3+10;
    }
    else
    {
      man=rand()%10;
    }
  }
  else if(class==6)
  {
    lucky=rand()%25;
    if(lucky>8)
    {
      man=15+rand()%6;
    }
    else if(lucky<=8 &&lucky>4)
    {
      man=13+rand()%2;
    }
    else
    {
      man=rand()%13;
    }
  }  
  else if(class==7)
  {
    lucky=rand()%40;
    if(lucky>12)
    {
      man=21+rand()%3;    
    }
    else if(lucky<=12 &&lucky>4)
    {
      man=15+rand()%6;
    }
    else
    {
      man=rand()%15;
    }
  }  
  else if(class==8)
  {
    lucky=rand()%50;
    if(lucky>25)
    {
      man=24+rand()%4;
    }
    else if(lucky<=25 && lucky>20)
    {
      man=21+rand()%3;    
    }
    else 
    {
      man=rand()%21;
    }
  }        
  else if(class==9)
  {
    lucky=rand()%75;
    if(lucky>20)
    {
      man=28+rand()%6;
    }
    else if(lucky<=20 && lucky>10)    
    {
      man=24+rand()%4;
    }
    else if(lucky<=10 && lucky>5)
    {
      man=21+rand()%3;    
    }
    else
    {
      man=rand()%21;
    }
  }          
  else if(class>=9)
  {
    lucky=rand()%100;
    if(lucky>20)
    {
      man=34+rand()%12;
    }
    else if(lucky<=20 && lucky>10)
    {
      man=28+rand()%6;
    }
    else if(lucky<=10 && lucky>5)    
    {
      man=24+rand()%4;
    }
    else
    {
      man=rand()%24;    
    }
  }            
  pip_fight_bad(man);
  return;
}

int 
pip_fight_bad(n)
int n;
{
  pip_fight_main(n,badmanlist,1);
  return;
}


int
pip_fight_main(n,list,mode)
int n;
struct playrule list[];   
int mode;
{
  pip_vs_man(n,list,mode);
  return 0;
}

/*---------------------------------------------------------------------------*/
/* ¾Ô°«¾Ô°«¨ç¦¡                                                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
int 
pip_vs_man(n,p,mode)
int n;
struct playrule *p;  
int mode;
{
 /* p[n].name hp mp speed attack resist money special map */ 
 struct playrule m; 
 char buf[256];
 char inbuf1[20];
 char inbuf2[20]; 
 int pipkey; 
 int mankey;
 int lucky;
 int dinjure=0;		/*¤pÂû¶Ë®`¤O*/
 int minjure=0;		/*¹ï¤è¶Ë®`¤O*/
 int dresistmore=0;	/*¤pÂû¥[±j¨¾¿m*/
 int mresistmore=0;	/*¹ï¤è¥[±j¨¾¿m*/
 int oldhexp;		/*¥¼¾Ô°««e®æ°«¸gÅç*/
 int oldmexp;		/*¥¼¾Ô°««eÅ]ªk¸gÅç*/
 int oldbrave;		/*¥¼¾Ô°««e«i´±*/
 int oldhskill;		/*¥¼¾Ô°««e¾Ô°«§Þ³N*/
 int oldmskill;		/*¥¼¾Ô°««eÅ]ªk§Þ³N*/
 int oldetchics;	/*¥¼¾Ô°««e¹D¼w*/
 int oldmoney;		/*¥¼¾Ô°««eª÷¿ú*/
 int oldtired;
 int oldhp;
 int winorlose=0;		/*1:you win 0:you loss*/
  
 /*ÀH¾÷²£¥Í¤Hª« ¨Ã¥B¦s¦n¾Ô°««eªº¤@¨Ç¼Æ­È*/
 oldhexp=d.hexp;
 oldmexp=d.mexp;
 oldbrave=d.brave;
 oldhskill=d.hskill;
 oldmskill=d.mskill;
 oldetchics=d.etchics;
 oldmoney=d.money;
 if(mode==1)
 {
	 m.hp=p[n].hp-rand()%10;
	 m.maxhp=(m.hp+p[n].hp)/2;
	 m.mp=p[n].mp-rand()%10;
	 m.maxmp=(m.mp+p[n].mp)/2;
	 m.speed=p[n].speed-rand()%4-1;
	 m.attack=p[n].attack-rand()%10;
	 m.resist=p[n].resist-rand()%10;
	 m.money=p[n].money-rand()%50;
	 m.death=p[n].death;
 }
 else
 {
 	 m.maxhp=d.maxhp*(80+rand()%50)/100+20;;
 	 m.hp=m.maxhp-rand()%10+20;
 	 m.maxmp=d.maxmp*(80+rand()%50)/100+10;
 	 m.mp= m.maxmp-rand()%20+10;
 	 m.speed=d.speed*(80+rand()%50)/100+10;
 	 m.attack=d.attack*(80+rand()%50)/100+10;
 	 m.resist=d.resist*(80+rand()%50)/100+10;
 	 m.money=0;
 	 m.death=0;
 }
 /*d.tired+=rand()%(n+1)/4+2;*/
 /*d.shit+=rand()%(n+1)/4+2;*/
 do
 { 
   if(m.hp<=0) /*¼Ä¤H¦º±¼¤F*/
   {
     m.hp=0;
     d.money+=m.money;
     m.death=1;
     d.brave+=rand()%4+3;
   }
   if(d.hp<=0 || d.tired>=100)  /*¤pÂû°}¤`*/
   {
     if(mode==1)
     {
       d.hp=0;
       d.tired=0;
       d.death=1;
     }
     else
     {
       d.hp=d.maxhp/3+10;
       d.hexp-=rand()%3+2;
       d.mexp-=rand()%3+2;
       d.tired=50;
       d.death=1;
     }
   }        
   clear(); 
   /*showtitle("¹q¤l¾i¤pÂû", BoardName);*/
   move(0,0);
   if(d.sex==1)
     sprintf(buf,"[1;41m  ¬PªÅ¾Ô°«Âû ¡ã [32m¡ñ [37m%-10s                                                  [0m",d.name); 	 
   else if(d.sex==2)
     sprintf(buf,"[1;41m  ¬PªÅ¾Ô°«Âû ¡ã [33m¡ð [37m%-10s                                                  [0m",d.name); 	 
   else 
     sprintf(buf,"[1;41m  ¬PªÅ¾Ô°«Âû ¡ã [34m¡H [37m%-10s                                                  [0m",d.name); 	 
   prints(buf);    
   move(6,0);
   if(mode==1)
	   show_badman_pic(n);
   move(1,0);
   sprintf(buf,"[1;31m¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{[m");
   prints(buf);
   move(2,0);
   /* lucky®³¨Ó·ícolor¥Î*/
   if(d.tired>=80)
      lucky=31;
   else if(d.tired>=60 && d.tired< 80)
      lucky=33;
   else
      lucky=37;
   sprintf(inbuf1,"%d/%d",d.hp,d.maxhp);  
   sprintf(inbuf2,"%d/%d",d.mp,d.maxmp);    
   sprintf(buf,"[1;31m¢x[33m¥Í  ©R:[37m%-12s[33mªk  ¤O:[37m%-12s[33m¯h  ³Ò:[%dm%-12d[33mª÷  ¿ú:[37m%-10d[31m¢x[m",
  	 inbuf1,inbuf2,lucky,d.tired,d.money);
   prints(buf);
   move(3,0);
   sprintf(inbuf1,"%d/%d",d.hexp,d.mexp);  
   sprintf(buf,"[1;31m¢x[33m§ð  À»:[37m%-10d  [33m¨¾  ¿m:[37m%-10d  [33m³t  «×:[37m%-5d       [33m¸g  Åç:[37m%-10s[31m¢x[m",
 	 d.attack,d.resist,d.speed,inbuf1);
   prints(buf);
   move(4,0);
   sprintf(buf,"[1;31m¢x[33m­¹  ª«:[37m%-5d       [33m¤j¸É¤Y:[37m%-5d       [33m¹s  ­¹:[37m%-5d       [33mÃÄ  ¯ó:[37m%-5d     [31m¢x[m",
 	 d.food,d.bighp,d.cookie,d.medicine);
   prints(buf);	 
   move(5,0);
   sprintf(buf,"[1;31m¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}[m");
   prints(buf); 
   move(19,0);
   sprintf(buf,"[1;34m¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{[m");
   prints(buf);
   move(20,0);
   sprintf(inbuf1,"%d/%d",m.hp,m.maxhp);  
   sprintf(inbuf2,"%d/%d",m.mp,m.maxmp);     
   sprintf(buf,"[1;34m¢x[32m©m  ¦W:[37m%-10s  [32m¥Í  ©R:[37m%-11s [32mªk  ¤O:[37m%-11s                  [34m¢x[m",
 	 p[n].name,inbuf1,inbuf2);
   prints(buf);
   move(21,0);
   sprintf(buf,"[1;34m¢x[32m§ð  À»:[37m%-6d      [32m¨¾  ¿m:[37m%-6d      [32m³t  «×:[37m%-6d      [32mª÷  ¿ú:[37m%-6d    [34m¢x[m",
 	 m.attack,m.resist,m.speed,m.money);
   prints(buf);
   move(22,0);
   sprintf(buf,"[1;34m¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}[m");
   prints(buf);
   move(b_lines,0);   
   sprintf(buf,"[1;44;37m  ¾Ô°«©R¥O  [46m  [1]´¶³q  [2]¥þ¤O  [3]Å]ªk  [4]¨¾¿m  [5]¸É¥R  [6]°k©R         [m");
   prints(buf);    
   
   if(m.death==0 && d.death==0)
   {
    dresistmore=0;
    d.nodone=0;
    pipkey=egetch(); 
    switch(pipkey)
    {
     case '1': 
      if(rand()%9==0)
      {
        pressanykey("³ºµM¨S¥´¤¤..:~~~"); 
      }
      else
      { 
      	if(mresistmore==0)
          dinjure=(d.hskill/100+d.hexp/100+d.attack/9-m.resist/12+rand()%12+2-m.speed/30+d.speed/30);
        else
	  dinjure=(d.hskill/100+d.hexp/100+d.attack/9-m.resist/8+rand()%12+2-m.speed/30+d.speed/30);            
	if(dinjure<=0)
	  dinjure=9;
        m.hp-=dinjure;
        d.hexp+=rand()%2+2;
        d.hskill+=rand()%2+1;  
        sprintf(buf,"´¶³q§ðÀ»,¹ï¤è¥Í©R¤O´î§C%d",dinjure);
        pressanykey(buf);
      }
      d.tired+=rand()%(n+1)/15+2;
      break;
     
     case '2':
      show_fight_pic(2);
      if(rand()%11==0)
      { 
        pressanykey("³ºµM¨S¥´¤¤..:~~~");
      }     
      else 
      { 
        if(mresistmore==0)      
          dinjure=(d.hskill/100+d.hexp/100+d.attack/5-m.resist/12+rand()%12+6-m.speed/50+d.speed/30);
        else
          dinjure=(d.hskill/100+d.hexp/100+d.attack/5-m.resist/8+rand()%12+6-m.speed/40+d.speed/30);                  
        if(dinjure<=15)
          dinjure=20;  
        if(d.hp>5)
        { 
          m.hp-=dinjure;
          d.hp-=5;
          d.hexp+=rand()%3+3;
          d.hskill+=rand()%2+2; 
          d.tired+=rand()%(n+1)/10+3; 
          sprintf(buf,"¥þ¤O§ðÀ»,¹ï¤è¥Í©R¤O´î§C%d",dinjure);
          pressanykey(buf);
        }
        else
        { 
          d.nodone=1;
          pressanykey("§AªºHP¤p©ó5°Õ..¤£¦æ°Õ...");
        }
      }
      break;
     
     case '3':
      oldtired=d.tired;
      oldhp=d.hp;     
      d.magicmode=0;
      dinjure=pip_magic_menu(); 
      if(dinjure<0)
        dinjure=5;
      if(d.nodone==0)
      {
        if(d.magicmode==1)
        {
          oldtired=oldtired-d.tired;
          oldhp=d.hp-oldhp;
          sprintf(buf,"ªvÀø«á,¥Í©R¤O´£°ª%d ¯h³Ò­°§C%d",oldhp,oldtired);
          pressanykey(buf);
        }
        else
        {
          if(rand()%15==0)
             pressanykey("³ºµM¨S¥´¤¤..:~~~");  
          else
          {  
             if(d.mexp<=100)
             {
                if(rand()%4>0)
                    dinjure=dinjure*60/100;
                else
                    dinjure=dinjure*80/100;
             }
             else if(d.mexp<=250 && d.mexp>100)
             {
                if(rand()%4>0)
                    dinjure=dinjure*70/100;
                else
                    dinjure=dinjure*85/100;           
             }
             else if(d.mexp<=500 && d.mexp>250)
             {
                if(rand()%4>0)
                    dinjure=dinjure*85/100;
                else
                    dinjure=dinjure*95/100;           
             }
             else if(d.mexp>500)
             {
                if(rand()%10>0)
                    dinjure=dinjure*90/100;
                else
                    dinjure=dinjure*99/100;           
             }
             if((p[n].special[d.magicmode-2]-48)==1)
             {
                if(rand()%2>0)
                {
                  dinjure=dinjure*125/100;
                }
                else
                {
                  dinjure=dinjure*110/100;
                }
             }
             else
             {
                if(rand()%2>0)
                {
                  dinjure=dinjure*60/100;
                }
                else
                {  
                  dinjure=dinjure*75/100;           
                }
             }
             d.tired+=rand()%(n+1)/12+2;
             m.hp-=dinjure; 
             /*d.mexp+=rand()%2+2;*/
             d.mskill+=rand()%2+2;  
             sprintf(buf,"Å]ªk§ðÀ»,¹ï¤è¥Í©R¤O´î§C%d",dinjure);
             pressanykey(buf);           
          }
        }
      }
      break;    
     case '4':
      dresistmore=1;
      d.tired+=rand()%(n+1)/20+1;
      pressanykey("¤pÂû¥[±j¨¾¿m°Õ....");
      break;

     case '5':
      
      pip_basic_feed();
      break;
      
     case '6':
      d.money-=(rand()%100+30);
      d.brave-=(rand()%3+2);      
      if(d.money<0)
      	d.money=0;
      if(d.hskill<0)
      	d.hskill=0;
      if(d.brave<0)
        d.brave=0;
      clear(); 
      showtitle("¹q¤l¾i¤pÂû", BoardName); 
      move(10,0);
      prints("            [1;31m¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{[m");
      move(11,0);
      prints("            [1;31m¢x  [37m¹ê¤O¤£±jªº¤pÂû [33m%-10s                 [31m¢x[m",d.name);
      move(12,0);
      prints("            [1;31m¢x  [37m¦b»P¹ï¤â [32m%-10s [37m¾Ô°««á¸¨¶]°Õ          [31m¢x[m",p[n].name);
      move(13,0);
      sprintf(inbuf1,"%d/%d",d.hexp-oldhexp,d.mexp-oldmexp);  
      prints("            [1;31m¢x  [37mµû»ù¼W¥[¤F [36m%-5s [37mÂI  §Þ³N¼W¥[¤F [36m%-2d/%-2d [37mÂI  [31m¢x[m",inbuf1,d.hskill-oldhskill,d.mskill-oldmskill);
      move(14,0);
      sprintf(inbuf1,"%d [37m¤¸",oldmoney-d.money);
      prints("            [1;31m¢x  [37m«i´±­°§C¤F [36m%-5d [37mÂI  ª÷¿ú´î¤Ö¤F [36m%-13s  [31m¢x[m",oldbrave-d.brave,inbuf1);
      move(15,0);
      prints("            [1;31m¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}[m");             
      pressanykey("¤T¤Q¤»­p ¨«¬°¤Wµ¦...");
      winorlose=0;
      break;

#ifdef MAPLE     
     case Ctrl('R'):
      if (currutmp->msgs[0].last_pid)
      {
      show_last_call_in();
      my_write(currutmp->msgs[0].last_pid, "¤ô²y¥á¦^¥h¡G");
      }
      break;
#endif  // END MAPLE
    }   
   }
   clear(); 
   move(0,0);
   if(d.sex==1)
     sprintf(buf,"[1;41m  ¬PªÅ¾Ô°«Âû ¡ã [32m¡ñ [37m%-10s                                                  [0m",d.name); 	 
   else if(d.sex==2)
     sprintf(buf,"[1;41m  ¬PªÅ¾Ô°«Âû ¡ã [33m¡ð [37m%-10s                                                  [0m",d.name); 	 
   else 
     sprintf(buf,"[1;41m  ¬PªÅ¾Ô°«Âû ¡ã [34m¡H [37m%-10s                                                  [0m",d.name); 	 
   prints(buf);    
   move(1,0);
   sprintf(buf,"[1;31m¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{[m");
   prints(buf);
   move(2,0);
   /* lucky®³¨Ó·ícolor¥Î*/
   if(d.tired>=80)
      lucky=31;
   else if(d.tired>=60 && d.tired< 80)
      lucky=33;
   else
      lucky=37;
   sprintf(inbuf1,"%d/%d",d.hp,d.maxhp);  
   sprintf(inbuf2,"%d/%d",d.mp,d.maxmp);    
   sprintf(buf,"[1;31m¢x[33m¥Í  ©R:[37m%-12s[33mªk  ¤O:[37m%-12s[33m¯h  ³Ò:[%dm%-12d[33mª÷  ¿ú:[37m%-10d[31m¢x[m",
  	 inbuf1,inbuf2,lucky,d.tired,d.money);
   prints(buf);
   
   move(3,0);
   sprintf(inbuf1,"%d/%d",d.hexp,d.mexp);     
   sprintf(buf,"[1;31m¢x[33m§ð  À»:[37m%-6d      [33m¨¾  ¿m:[37m%-6d      [33m³t  «×:[37m%-5d       [33m¸g  Åç:[37m%-10s[31m¢x[m",
 	 d.attack,d.resist,d.speed,inbuf1);
   prints(buf);
   move(4,0);
   sprintf(buf,"[1;31m¢x[33m­¹  ª«:[37m%-5d       [33m¤j¸É¤Y:[37m%-5d       [33m¹s  ­¹:[37m%-5d       [33mÃÄ  ¯ó:[37m%-5d     [31m¢x[m",
 	 d.food,d.bighp,d.cookie,d.medicine);
   prints(buf);	 
   move(5,0);
   sprintf(buf,"[1;31m¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}[m");
   prints(buf);    
   move(6,0);
   if(mode==1)
	   show_badman_pic(n);
   move(19,0);
   sprintf(buf,"[1;34m¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{[m");
   prints(buf);
   move(20,0);
   sprintf(inbuf1,"%d/%d",m.hp,m.maxhp);  
   sprintf(inbuf2,"%d/%d",m.mp,m.maxmp);     
   sprintf(buf,"[1;34m¢x[32m©m  ¦W:[37m%-10s  [32m¥Í  ©R:[37m%-11s [32mªk  ¤O:[37m%-11s                  [34m¢x[m",
 	 p[n].name,inbuf1,inbuf2);
   prints(buf);
   move(21,0);
   sprintf(buf,"[1;34m¢x[32m§ð  À»:[37m%-6d      [32m¨¾  ¿m:[37m%-6d      [32m³t  «×:[37m%-6d      [32mª÷  ¿ú:[37m%-6d    [34m¢x[m",
 	 m.attack,m.resist,m.speed,m.money);
   prints(buf);
   move(22,0);
   sprintf(buf,"[1;34m¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}[m");
   prints(buf);
   move(b_lines,0);   
   sprintf(buf,"[1;41;37m  [37m§ðÀ»©R¥O  [47m  [31m[1][30m´¶³q  [31m[2][30m¥þ¤O  [31m[3][30mÅ]ªk  [31m[4][30m¨¾¿m  [31m[5][30m°k©R                     [m");
   prints(buf);       
   
   if((m.hp>0)&&(pipkey!='6')&& (pipkey=='1'||pipkey=='2'||pipkey=='3'||pipkey=='4'||pipkey=='5')&&(d.death==0)&&(d.nodone==0))
   {
     mresistmore=0;
     lucky=rand()%100;
     if(lucky>=0 && lucky<=50)
        mankey=1;
     else if(lucky>=51 && lucky<=84)
        mankey=2;  
     else if(lucky>=85 && lucky<=97)
        mankey=3;
     else if(lucky>=98)
        mankey=4;   
     switch(mankey)
     {    
      case 1:
       if(rand()%6==5)
       { 
         pressanykey("¹ï¤è¨S¥´¤¤..:~~~");
       }     
       else
       {
        if(dresistmore==0)      
          minjure=(m.attack/9-d.resist/12+rand()%15+4-d.speed/30+m.speed/30-d.hskill/200-d.hexp/200);
        else
          minjure=(m.attack/9-d.resist/8+rand()%12+4-d.speed/50+m.speed/20-d.hskill/200-d.hexp/200);
        if(minjure<=0)
          minjure=8;  
        d.hp-=minjure;
        d.tired+=rand()%3+2;
        sprintf(buf,"¹ï¤è´¶³q§ðÀ»,¥Í©R¤O´î§C%d",minjure);
        pressanykey(buf);
       }             
       break;
       
      case 2:       
       if(rand()%11==10)
       { 
         pressanykey("¹ï¤è¨S¥´¤¤..:~~~");
       }     
       else
       {
        if(m.hp>5)
        {
          if(dresistmore==0)      
            minjure=(m.attack/5-d.resist/12+rand()%12+6-d.speed/30+m.speed/30-d.hskill/200-d.hexp/200);
          else
            minjure=(m.attack/5-d.resist/8+rand()%12+6-d.speed/30+m.speed/30-d.hskill/200-d.hexp/200);                  
	  if(minjure<=15)
	    minjure=20;
          d.hp-=minjure;
          m.hp-=5;
          sprintf(buf,"¹ï¤è¥þ¤O§ðÀ», ¥Í©R¤O´î§C%d",minjure);
          d.tired+=rand()%4+4;
          pressanykey(buf);
        }
        else
        {
          if(dresistmore==0)      
            minjure=(m.attack/9-d.resist/12+rand()%12+4-d.speed/30+m.speed/25-d.hexp/200-d.hskill/200);
          else
            minjure=(m.attack/9-d.resist/8+rand()%12+3-d.speed/30+m.speed/25-d.hexp/200-d.hskill/200);        
          if(minjure<=0)
            minjure=4;
          d.hp-=minjure;
          d.tired+=rand()%3+2;
          sprintf(buf,"¹ï¤è´¶³q§ðÀ»,¥Í©R¤O´î§C%d",minjure);
          pressanykey(buf);        
        }
       }             
       break;             
       
      case 3:
       if(rand()%5>0 && m.mp>20)
       {
        if(rand()%6>0 && m.mp>=50)
        {
         if(m.mp>=1000)
         {
           minjure=500;
           m.mp-=(500+rand()%300);
           if(rand()%2)
	      sprintf(inbuf1,"¼ö¤õÅ]");
	   else
	      sprintf(inbuf1,"´H®ð°­");
         }
         else if(m.mp<1000 && m.mp>=500)
         {
           minjure=300;
           m.mp-=(300+rand()%200);
           if(rand()%2)
	      sprintf(inbuf1,"¨g¤ô©Ç");
	   else
	      sprintf(inbuf1,"«ã¤g¦ä");
         }
         else if(m.mp<500 && m.mp>=200)
         {
           minjure=100;
           m.mp-=(100+rand()%100);
           if(rand()%2)
	      sprintf(inbuf1,"°g»î°­®t");
	   else
	      sprintf(inbuf1,"¥Û©Ç");
         }
         else if(m.mp<200 && m.mp>=50)
         {
           minjure=50;
           m.mp-=50;
           if(rand()%2)
	      sprintf(inbuf1,"°­¤ì»î");
	   else
	      sprintf(inbuf1,"­·§¯");
         }
         minjure=minjure-d.resist/50-d.mresist/10-d.mskill/200-d.mexp/200+rand()%10;
         if(minjure<0)
         	minjure=15;
         d.hp-=minjure;
         d.mresist+=rand()%2+1;
         sprintf(buf,"¹ï¤è©Û´«¤F%s,§A¨ü¶Ë¤F%dÂI",inbuf1,minjure);
         pressanykey(buf);
        }
        else
        {
         m.mp-=20;
         m.hp+=130+rand()%20;
         if(m.hp>m.maxhp)
            m.hp=m.maxhp;
         pressanykey("¹ï¤è¨Ï¥ÎÅ]ªkªvÀø¤F¦Û¤v...");
        }
       }
       else
       {
         mresistmore=1;
         pressanykey("¹ï¤è¥[±j¨¾¿m....");
       }
       break;
      
      case 4:
       d.money+=(m.money+m.money/2)/3+rand()%10;
       d.hskill+=rand()%4+3;
       d.brave+=rand()%3+2;
       m.death=1;
       sprintf(buf,"¹ï¤è¥ý°{¤F..¦ý±¼¤F¤@¨Ç¿úµ¹§A...");
       pressanykey(buf);       
       break;      
     }
   }
   
   if(m.death==1)
   {
     clear();
     showtitle("¹q¤l¾i¤pÂû", BoardName);
     if(mode==1)
     { 
       move(10,0);
       prints("            [1;31m¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{[m");
       move(11,0);
       prints("            [1;31m¢x  [37m­^«iªº¤pÂû [33m%-10s                     [31m¢x[m",d.name);
       move(12,0);
       prints("            [1;31m¢x  [37m¥´±Ñ¤F¨¸´cªº©Çª« [32m%-10s               [31m¢x[m",p[n].name);
     }  
     else
     {
       move(10,0);
       prints("            [1;31m¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{[m");
       move(11,0);
       prints("            [1;31m¢x  [37mªZ³N¤j·|ªº¤pÂû [33m%-10s                 [31m¢x[m",d.name);
       move(12,0);
       prints("            [1;31m¢x  [37m¥´±Ñ¤F±j«lªº¹ï¤â [32m%-10s               [31m¢x[m",p[n].name);
     }
     move(13,0);
     sprintf(inbuf1,"%d/%d",d.hexp-oldhexp,d.mexp-oldmexp);  
     prints("            [1;31m¢x  [37mµû»ù´£¤É¤F %-5s ÂI  §Þ³N¼W¥[¤F %-2d/%-2d ÂI  [31m¢x[m",inbuf1,d.hskill-oldhskill,d.mskill-oldmskill);
     move(14,0);
     sprintf(inbuf1,"%d ¤¸",d.money-oldmoney);
     prints("            [1;31m¢x  [37m«i´±´£¤É¤F %-5d ÂI  ª÷¿ú¼W¥[¤F %-9s [31m¢x[m",d.brave-oldbrave,inbuf1);
     move(15,0);
     prints("            [1;31m¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}[m");     
     
     if(m.hp<=0)     
        pressanykey("¹ï¤è¦º±¼Åo..©Ò¥H§AÄ¹Åo..");   
     else if(m.hp>0)
        pressanykey("¹ï¤è¸¨¶]Åo..©Ò¥Hºâ§AÄ¹Åo.....");   
     winorlose=1;
   }
   if(d.death==1 && mode==1)
   {   
       clear();
       showtitle("¹q¤l¾i¤pÂû", BoardName);       
       move(10,0);
       prints("            [1;31m¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{[m");
       move(11,0);
       prints("            [1;31m¢x  [37m¥i¼¦ªº¤pÂû [33m%-10s                     [31m¢x[m",d.name);
       move(12,0);
       prints("            [1;31m¢x  [37m¦b»P [32m%-10s [37mªº¾Ô°«¤¤¡A                [31m¢x[m",p[n].name);
       move(13,0);
       prints("            [1;31m¢x  [37m¤£©¯¦a°}¤`¤F¡A¦b¦¹¯S§OÀq«s..........      [31m¢x[m");
       move(14,0);
       prints("            [1;31m¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}[m");        
       pressanykey("¤pÂû°}¤`¤F....");      
       pipdie("[1;31m¾Ô°«¤¤³Q¥´¦º¤F...[m  ",1);       
   }
   else if(d.death==1 && mode==2)
   {
       clear();
       showtitle("¹q¤l¾i¤pÂû", BoardName);       
       move(10,0);
       prints("            [1;31m¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{[m");
       move(11,0);
       prints("            [1;31m¢x  [37m¥i¼¦ªº¤pÂû [33m%-10s                     [31m¢x[m",d.name);
       move(12,0);
       prints("            [1;31m¢x  [37m¦b»P [32m%-10s [37mªº¾Ô°«¤¤¡A                [31m¢x[m",p[n].name);
       move(13,0);
       prints("            [1;31m¢x  [37m¤£©¯¦a¥´¿é¤F¡A°OªÌ²{³õ¯S§O³ø¾É.........   [31m¢x[m");
       move(14,0);
       prints("            [1;31m¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}[m");        
       pressanykey("¤pÂû¥´¿é¤F....");     
   }
 }while((pipkey!='6')&&(d.death!=1)&&(m.death!=1)&&(mankey!=8)); 
 return winorlose;    
}                 


/*---------------------------------------------------------------------------*/
/* ¾Ô°«Å]ªk¨ç¦¡                                                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/

/*¶i¤J¨Ï¥ÎÅ]ªk¿ï³æ*/
int
pip_magic_menu()   /*¾Ô°«¤¤ªk³NªºÀ³¥Î*/
{
  char buf[256];
  int magicnum=0;
  int injure;		/*¶Ë®`¤O*/
  int pipkey;
  
  do
  {
   move(b_lines, 0);
   clrtoeol();
   move(b_lines,0);
   sprintf(buf,
   "[1;44;37m  Å]ªk¿ï³æ  [46m  [1]ªvÀø [2]¹p¨t [3]¦B¨t [4]¤õ¨t [5]¤g¨t [6]­·¨t [Q]©ñ±ó: [m");
   move(b_lines,0);
   prints(buf);   
   pipkey=egetch();
   switch(pipkey)
   {
    case '1':  /*ªvÀøªk³N*/
     d.magicmode=1;
     injure=pip_magic_doing_menu(treatmagiclist);
     break;

    case '2':  /*¹p¨tªk³N*/
     d.magicmode=2;
     injure=pip_magic_doing_menu(thundermagiclist);
     break;

    case '3': /*¦B¨tªk³N*/
     d.magicmode=3;
     injure=pip_magic_doing_menu(icemagiclist);
     break;

    case '4': /*ª¢¨tªk³N*/
     d.magicmode=4;
     injure=pip_magic_doing_menu(firemagiclist);
     show_fight_pic(341);
     pressanykey("¤pÂû¨Ï¥Î¤Fª¢¨tªk³N");
     break;

    case '5': /*¤g¨tªk³N*/
     d.magicmode=5;
     injure=pip_magic_doing_menu(earthmagiclist);
     break;

    case '6': /*­·¨tªk³N*/
     d.magicmode=6;
     injure=pip_magic_doing_menu(windmagiclist);
     break;

#ifdef MAPLE     
    case Ctrl('R'):
     if (currutmp->msgs[0].last_pid)
     {
     extern screenline* big_picture;
     screenline* screen0 = calloc(t_lines, sizeof(screenline));
     memcpy(screen0, big_picture, t_lines * sizeof(screenline));

     show_last_call_in();
     my_write(currutmp->msgs[0].last_pid, "¤ô²y¥á¦^¥h¡G");

     memcpy(big_picture, screen0, t_lines * sizeof(screenline));
     free(screen0);
     redoscr();
     }
     break;
#endif  // END MAPLE
   }
  }while((pipkey!='1')&&(pipkey!='2')&&(pipkey!='3')&&(pipkey!='4')&&(pipkey!='5')&&(pipkey!='6')&&(pipkey!='Q')&&(pipkey!='q')&&(d.nodone==0));

  if((pipkey=='Q')||(pipkey=='q'))
  {
   d.nodone=1;
  }
  return injure;    
}

/*Å]ªkµøµ¡*/
int
pip_magic_doing_menu(p)   /*Å]ªkµe­±*/
struct magicset *p;
{
 register int n=1;
 register char *s;
 char buf[256];
 char ans[5];
 int pipkey;
 int injure=0;

 d.nodone=0; 

 clrchyiuan(6,18);
 move(7,0);
 sprintf(buf,"[1;31m¢t[37;41m   ¥i¥Î[%s]¤@Äýªí   [0;1;31m¢u¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w[m",p[0].name);
 prints(buf);
 while ((s = p[n].name)&& (p[n].needmp<=d.mp))
 {
  move(7+n,4);
  if(p[n].hpmode==1)
  {   
      sprintf(buf,
      "[1;37m[[36m%d[37m] [33m%-10s  [37m»Ý­nªk¤O: [32m%-6d  [37m«ì´_Åé¤O: [32m%-6d [37m«ì´_¯h³Ò: [32m%-6d[m   ",n,p[n].name,p[n].needmp,p[n].hp,p[n].tired);
      prints(buf);
  }
  else if(p[n].hpmode==2)
  {
      sprintf(buf,
      "[1;37m[[36m%d[37m] [33m%-10s  [37m»Ý­nªk¤O: [32m%-6d  [37m«ì´_Åé¤O¨ì[35m³Ì¤j­È[37m «ì´_¯h³Ò¨ì[35m³Ì¤p­È[m  ",n,p[n].name,p[n].needmp);
      prints(buf);
  }  
  else if(p[n].hpmode==0)
  {
      sprintf(buf,
      "[1;37m[[36m%d[37m] [33m%-10s  [37m»Ý­nªk¤O: [32m%-6d [m             ",n,p[n].name,p[n].needmp);
      prints(buf);
  }
  n++;
 }  
 n-=1;
 
 do{
   move(16,4);
   sprintf(buf,"§A·Q¨Ï¥Î¨º¤@­Ó%8s©O?  [Q]©ñ±ó:",p[0].name);
#ifdef MAPLE
   getdata(16,4,buf, ans, 2, 1, 0);
#else
   getdata(16,4,buf, ans, 2, DOECHO, YEA);
#endif  // END MAPLE
   if( ans[0]!='q' && ans[0]!='Q')
   {
     pipkey=atoi(ans);
   }
 }while( ans[0]!='q' && ans[0]!='Q' && (pipkey>n || pipkey <=0));
 
 if(ans[0]!='q' && ans[0]!='Q')
 {
#ifdef MAPLE
   getdata(17,4,"½T©w¨Ï¥Î¶Ü? [Y/n]", ans, 2, 1, 0);
#else
   getdata(17,4,"½T©w¨Ï¥Î¶Ü? [Y/n]", ans, 2, DOECHO, YEA);
#endif  // END MAPLE
   if(ans[0]!='n' && ans[0]!='N')
   {
     if(p[pipkey].hpmode==1)
     {
      d.hp+=p[pipkey].hp;
      d.tired-=p[pipkey].tired;      
      d.mp-=p[pipkey].needmp;
      if(d.hp>d.maxhp)
        d.hp=d.maxhp;
      if(d.tired<0)
        d.tired=0;
      injure=0;
     }
     else if(p[pipkey].hpmode==2)
     {
      d.hp=d.maxhp;
      d.mp-=p[pipkey].needmp;
      d.tired=0;
      injure=0;
     } 
     else
     {
      injure=(p[pipkey].hp-rand()%5);               
      d.mp-=p[pipkey].needmp;
     }
     d.mexp+=rand()%3+pipkey;
   }
   else
   {
     d.nodone=1;
     injure=0;
   }
 }
 else
 {
   d.nodone=1;
   injure=0; 
 }
 return injure;
}
