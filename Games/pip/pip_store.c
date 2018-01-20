/*---------------------------------------------------------------------------*/
/* °Ó©±¿ï³æ:­¹ª« ¹s­¹ ¤j¸É¤Y ª±¨ã ®Ñ¥»                                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
#include <time.h>
#include "bbs.h"
#include "pip.h"
extern struct chicken d;
extern time_t start_time;
extern time_t lasttime;

#ifndef MAPLE
extern char BoardName[];
#endif  // END MAPLE
#define getdata(a, b, c , d, e, f, g) getdata(a,b,c,d,e,f,NULL,g)

/*---------------------------------------------------------------------------*/
/* °Ó©±¿ï³æ:­¹ª« ¹s­¹ ¤j¸É¤Y ª±¨ã ®Ñ¥»                                       */
/* ¸ê®Æ®w                                                                    */
/*---------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*  ª««~°Ñ¼Æ³]©w                                                            */
/*--------------------------------------------------------------------------*/
struct goodsofpip
{
   int num;		/*½s¸¹*/
   char *name;		/*¦W¦r*/
   char *msgbuy;	/*¥\¥Î*/
   char *msguse;	/*»¡©ú*/
   int money;		/*ª÷¿ú*/
   int change;		/*§ïÅÜ¶q*/
   int pic1;
   int pic2;
};
typedef struct goodsofpip goodsofpip;

struct goodsofpip pipfoodlist[] = {
0,"ª««~¦W",	"»¡©úbuy",	"»¡©úfeed",			0,	0,	0,0,
1,"¦n¦Yªº­¹ª«",	"Åé¤O«ì´_50",	"¨C¦Y¤@¦¸­¹ª«·|«ì´_Åé¤O50³á!",	50,	50,	1,1,
2,"¬ü¨ýªº¹s­¹",	"Åé¤O«ì´_100",	"°£¤F«ì´_Åé¤O¡A¤pÂû¤]·|§ó§Ö¼Ö",	120,	100,	2,3,
0,NULL,NULL,NULL,0,0,0,0
};

struct goodsofpip pipmedicinelist[] = {
0,"ª««~¦W",	"»¡©úbuy",	"»¡©úfeed",			0,	0,	0,0,
1,"¦n¥Î¤j¸É¤Y",	"Åé¤O«ì´_600",	"«ì´_¤j¶q¬y¥¢Åé¤Oªº¨}¤è",	500,	600,	4,4,
2,"¬Ã¶QªºÆFªÛ",	"ªk¤O«ì´_50",	"¨C¦Y¤@¦¸ÆFªÛ·|«ì´_ªk¤O50³á!",	100,	50,	7,7,
3,"¤d¦~¤H°Ñ¤ý",	"ªk¤O«ì´_500",	"«ì´_¤j¶q¬y¥¢ªk¤Oªº¨}¤è",	800,	500,	7,7,
4,"¤Ñ¤s³·½¬",	"ªk¤OÅé¤O³Ì¤j",	"³o­Ó  ¦n¶Q......",		10000,	0,	7,7,
0,NULL,NULL,NULL,0,0,0,0
};

struct goodsofpip pipotherlist[] = {
0,"ª««~¦W",	"»¡©úbuy",	"»¡©úfeed",			0,	0,	0,0,
1,"¼Ö°ªª±¨ã²Õ",	"§Ö¼Öº¡·N«×",	"ª±¨ãÅý¤pÂû§ó§Ö¼Ö°Õ...",	50,	0,	5,5,
2,"¦Ê¬ì¥þ®Ñ",	"ª¾ÃÑªº¨Ó·½",	"®Ñ¥»Åý¤pÂû§óÁo©ú§ó¦³®ð½è°Õ...",100,	0,	6,6,
0,NULL,NULL,NULL,0,0,0,0
};

/*--------------------------------------------------------------------------*/
/*  ªZ¾¹°Ñ¼Æ³]©w                                                            */
/*--------------------------------------------------------------------------*/
struct weapon
{
  char *name;           /*¦W¦r*/  
  int needmaxhp;	/*»Ý­nhp*/
  int needmaxmp;	/*»Ý­nmp*/
  int needspeed;	/*»Ý­nªºspeed*/
  int attack;		/*§ðÀ»*/
  int resist;		/*¨¾Å@*/
  int speed;		/*³t«×*/
  int cost;		/*¶R»ù*/
  int sell;		/*½æ»ù*/
  int special;		/*¯S§O*/
  int map;		/*¹ÏÀÉ*/

};
typedef struct weapon weapon;

/*¦W¦r,»Ýhp,»Ýmp,»Ýspeed,§ðÀ»,¨¾Å@,³t«×,¶R»ù,½æ»ù,¯S§O,¹ÏÀÉ*/
struct weapon headlist[] = {
"¤£¶R¸Ë³Æ",  0,  0,  0,  0,  0,  0,     0,     0,0,0,
"¶ì½¦´U¤l",  0,  0,  0,  0,  5,  0,   500,   300,0,0,	
"¤û¥Ö¤p´U",  0,  0,  0,  0, 10,  0,  3500,  1000,0,0,
"¡À¦w¥þ´U", 60,  0,  0,  0, 20,  0,  5000,  3500,0,0,
"¿ûÅKÀY²¯",150, 50,  0,  0, 30,  0, 10000,  6000,0,0,
"Å]ªk¾vãT",100,150,  0,  0, 25,  0, 50000, 10000,0,0, 
"¶Àª÷¸t²¯",300,300,300,  0,100,  0,300000,100000,0,0,
NULL,        0,  0,  0,  0,  0,  0,   0,   0,0,0
};

/*¦W¦r,»Ýhp,»Ýmp,»Ýspeed,§ðÀ»,¨¾Å@,³t«×,¶R»ù,½æ»ù,¯S§O,¹ÏÀÉ*/
struct weapon rhandlist[] = {
"¤£¶R¸Ë³Æ",  0,  0,  0,  0,  0,  0,     0,     0,0,0,
"¤j¤ì´Î",    0,  0,  0,  5,  0,  0,  1000,   700,0,0,	
"ª÷ÄÝ§æ¤â",  0,  0,  0, 10,  0,  0,  2500,  1000,0,0,
"«C»É¼C",   50,  0,  0, 20,  0,  0,  6000,  4000,0,0,
"´¸¹p¼C",   80,  0,  0, 30,  0,  0, 10000,  8000,0,0,
"ÂÍÁl¤M",  100, 20,  0, 40,  0,  0, 15000, 10000,0,0, 
"§Ñ±¡¼C",  100, 40,  0, 35, 20,  0, 15000, 10000,0,0,
"·àÀYÄ_¤M",150,  0,  0, 60,  0,  0, 35000, 20000,0,0,
"±OÀs¤M",  200,  0,  0,100,  0,  0, 50000, 25000,0,0,
"¶Àª÷¸t§ú",300,300,300,100, 20,  0,150000,100000,0,0,
NULL,        0,  0,  0,  0,  0,  0,    0,   0,0,0
};

/*¦W¦r,»Ýhp,»Ýmp,»Ýspeed,§ðÀ»,¨¾Å@,³t«×,¶R»ù,½æ»ù,¯S§O,¹ÏÀÉ*/
struct weapon lhandlist[] = {
"¤£¶R¸Ë³Æ",  0,  0,  0,  0,  0,  0,     0,     0,0,0,
"¤j¤ì´Î",    0,  0,  0,  5,  0,  0,  1000,   700,0,0,	
"ª÷ÄÝ§æ¤â",  0,  0,  0, 10,  0,  0,  1500,  1000,0,0,
"¤ì¬Þ",	     0,  0,  0,  0, 10,  0,  2000,  1500,0,0,
"¤£ÄÃ¿û¬Þ", 60,  0,  0,  0, 25,  0,  5000,  3000,0,0,
"¥Õª÷¤§¬Þ", 80,  0,  0, 10, 40,  0, 15000, 10000,0,0,
"Å]ªk¬Þ",   80,100,  0, 20, 60,  0, 80000, 50000,0,0,
"¶Àª÷¸t¬Þ",300,300,300, 30,100,  0,150000,100000,0,0,
NULL,        0,  0,  0,  0,  0,  0,    0,   0,0,0
};

/*¦W¦r,»Ýhp,»Ýmp,»Ýspeed,§ðÀ»,¨¾Å@,³t«×,¶R»ù,½æ»ù,¯S§O,¹ÏÀÉ*/
struct weapon bodylist[] = {
"¤£¶R¸Ë³Æ",  0,  0,  0,  0,  0,  0,     0,     0,0,0,
"¶ì½¦«`¥Ò", 40,  0,  0,  0,  5,  0,  1000,   700,0,0,	
"¯S¯Å¥Ö¥Ò", 50,  0,  0,  0, 10,  0,  2500,  1000,0,0,
"¿ûÅK²¯¥Ò", 80,  0,  0,  0, 25,  0,  5000,  3500,0,0,
"Å]ªk©Ü­·", 80, 40,  0,  0, 20, 20, 15500, 10000,0,0,
"¥Õª÷²¯¥Ò",100, 30,  0,  0, 40, 20, 30000, 20000,0,0, 
"¶Àª÷¸t¦ç",300,300,300, 30,100,  0,150000,100000,0,0,
NULL,        0,  0,  0,  0,  0,  0,     0,   0,0,0
};

/*¦W¦r,»Ýhp,»Ýmp,»Ýspeed,§ðÀ»,¨¾Å@,³t«×,¶R»ù,½æ»ù,¯S§O,¹ÏÀÉ*/
struct weapon footlist[] = {
"¤£¶R¸Ë³Æ",  0,  0,  0,  0,  0,  0,     0,     0,0,0,
"¶ì½¦©ì¾c",  0,  0,  0,  0,  0, 10,   800,   500,0,0,
"ªF¬v¤ì®j",  0,  0,  0, 15,  0, 10,  1000,   700,0,0, 	
"¯S¯Å«B¾c",  0,  0,  0,  0, 10, 10,  1500,  1000,0,0,
"NIKE¹B°Ê¾c",70, 0,  0,  0, 10, 40,  8000,  5000,0,0,
"Æs³½¥Ö¹u", 80, 20,  0, 10, 25, 20, 12000,  8000,0,0,
"­¸¤ÑÅ]¹u",100,100,  0, 30, 50, 60, 25000, 10000,0,0,
"¶Àª÷¸t¹u",300,300,300, 50,100,100,150000,100000,0,0,
NULL,        0,  0,  0,  0,  0,  0,    0,   0,0,0
};

/*---------------------------------------------------------------------------*/
/* °Ó©±¿ï³æ:­¹ª« ¹s­¹ ¤j¸É¤Y ª±¨ã ®Ñ¥»                                       */
/* ¨ç¦¡®w                                                                    */
/*---------------------------------------------------------------------------*/

int pip_store_food()
{
    int num[3];
    num[0]=2;
    num[1]=d.food;
    num[2]=d.cookie;
    pip_buy_goods_new(1,pipfoodlist,num);
    d.food=num[1];
    d.cookie=num[2];
    return 0;
}

int pip_store_medicine()
{
    int num[5];
    num[0]=4;
    num[1]=d.bighp;
    num[2]=d.medicine;
    num[3]=d.ginseng;
    num[4]=d.snowgrass;
    pip_buy_goods_new(2,pipmedicinelist,num);
    d.bighp=num[1];
    d.medicine=num[2];
    d.ginseng=num[3];
    d.snowgrass=num[4];
    return 0;
}

int pip_store_other()
{
    int num[3];
    num[0]=2;
    num[1]=d.playtool;
    num[2]=d.book;
    pip_buy_goods_new(3,pipotherlist,num);
    d.playtool=num[1];
    d.book=num[2];
    return 0;
}

int pip_store_weapon_head()	/*ÀY³¡ªZ¾¹*/
{
     d.weaponhead=pip_weapon_doing_menu(d.weaponhead,0,headlist);
     return 0; 
}
int pip_store_weapon_rhand()	/*¥k¤âªZ¾¹*/
{
     d.weaponrhand=pip_weapon_doing_menu(d.weaponrhand,1,rhandlist);
     return 0;
}
int pip_store_weapon_lhand()    /*¥ª¤âªZ¾¹*/
{
     d.weaponlhand=pip_weapon_doing_menu(d.weaponlhand,2,lhandlist);
     return 0;
}
int pip_store_weapon_body()	/*¨­ÅéªZ¾¹*/
{
     d.weaponbody=pip_weapon_doing_menu(d.weaponbody,3,bodylist);
     return 0;
}
int pip_store_weapon_foot()     /*¨¬³¡ªZ¾¹*/
{
     d.weaponfoot=pip_weapon_doing_menu(d.weaponfoot,4,footlist);
     return 0;
}


int 
pip_buy_goods_new(mode,p,oldnum)
int mode;
int oldnum[];
struct goodsofpip *p;
{
    char *shopname[4]={"©±¦W","«K§Q°Ó©±","¬PªÅÃÄ¾Q","©]¸Ì®Ñ§½"};
    char inbuf[256];
    char genbuf[20];
    long smoney;
    int oldmoney;
    int i,pipkey,choice;
    oldmoney=d.money;
    do
    {
	    clrchyiuan(6,18);
	    move(6,0);
	    sprintf(inbuf,"[1;31m  ¢w[41;37m ½s¸¹ [0;1;31m¢w[41;37m °Ó      «~ [0;1;31m¢w¢w[41;37m ®Ä            ¯à [0;1;31m¢w¢w[41;37m »ù     ®æ [0;1;31m¢w[37;41m ¾Ö¦³¼Æ¶q [0;1;31m¢w[0m  ");
	    prints(inbuf);
	    for(i=1;i<=oldnum[0];i++)
	    {
		    move(7+i,0);
		    sprintf(inbuf,"     [1;35m[[37m%2d[35m]     [36m%-10s      [37m%-14s        [1;33m%-10d   [1;32m%-9d    [0m",
		    p[i].num,p[i].name,p[i].msgbuy,p[i].money,oldnum[i]);
		    prints(inbuf);
	    }
	    clrchyiuan(19,24);
	    move(b_lines,0); 
	    sprintf(inbuf,"[1;44;37m  %8s¿ï³æ  [46m  [B]¶R¤Jª««~  [S]½æ¥Xª««~  [Q]¸õ¥X¡G                         [m",shopname[mode]);
	    prints(inbuf);
	    pipkey=egetch(); 
	    switch(pipkey)  
	    {
		case 'B':
		case 'b':      
			move(b_lines-1,1);
			sprintf(inbuf,"·Q­n¶R¤JÔ£©O? [0]©ñ±ó¶R¤J [1¡ã%d]ª««~°Ó¸¹",oldnum[0]);
#ifdef MAPLE
			getdata(b_lines-1,1,inbuf,genbuf, 3, LCECHO,"0");
#else
                        getdata(b_lines-1,1,inbuf,genbuf, 3, DOECHO,YEA);
                        if ((genbuf[0] >= 'A') && (genbuf[0] <= 'Z'))
                                genbuf[0] = genbuf[0] | 32;
#endif  // END MAPLE

     			choice=atoi(genbuf);
			if(choice>=1 && choice<=oldnum[0])
			{
				clrchyiuan(6,18);
				if(rand()%2>0)
					show_buy_pic(p[choice].pic1);
				else
					show_buy_pic(p[choice].pic2);
				move(b_lines-1,0);
				clrtoeol();  
				move(b_lines-1,1);       
				smoney=0;
				if(mode==3)
					smoney=1;
				else
				{
					sprintf(inbuf,"§A­n¶R¤Jª««~ [%s] ¦h¤Ö­Ó©O?(¤W­­ %d)",p[choice].name,d.money/p[choice].money);
#ifdef MAPLE
					getdata(b_lines-1,1,inbuf,genbuf,6, 1, 0);
#else
                                        getdata(b_lines-1,1,inbuf,genbuf,6, DOECHO, YEA);
#endif  // END MAPLE
					smoney=atoi(genbuf);
				}
				if(smoney<0)
				{
					pressanykey("©ñ±ó¶R¤J...");
				}
				else if(d.money<smoney*p[choice].money)
				{
					pressanykey("§Aªº¿ú¨S¦³¨º»ò¦h³á..");
				}
				else
				{
					sprintf(inbuf,"½T©w¶R¤Jª««~ [%s] ¼Æ¶q %d ­Ó¶Ü?(©±®a½æ»ù %d) [y/N]:",p[choice].name,smoney,smoney*p[choice].money);
#ifdef MAPLE
					getdata(b_lines-1,1,inbuf,genbuf, 2, 1, 0); 
#else
                                        getdata(b_lines-1,1,inbuf,genbuf, 2, DOECHO, YEA);
#endif  // END MAPLE
					if(genbuf[0]=='y' || genbuf[0]=='Y')
					{
						oldnum[choice]+=smoney;
						d.money-=smoney*p[choice].money;
						sprintf(inbuf,"¦ÑÁóµ¹¤F§A%d­Ó%s",smoney,p[choice].name);
						pressanykey(inbuf);
						pressanykey(p[choice].msguse);
						if(mode==3 && choice==1)
						{
							d.happy+=rand()%10+20*smoney;
							d.satisfy+=rand()%10+20*smoney;
						}
						if(mode==3 && choice==2)
						{
							d.happy+=(rand()%2+2)*smoney;
							d.wisdom+=(2+10/(d.wisdom/100+1))*smoney;
							d.character+=(rand()%4+2)*smoney;
							d.art+=(rand()%2+1)*smoney;
						}
					}
					else
					{
						pressanykey("©ñ±ó¶R¤J...");
					}
				}
			}
			else
			{
				sprintf(inbuf,"©ñ±ó¶R¤J.....");
				pressanykey(inbuf);            
			}
			break;     
     
 		case 'S':
 		case 's':
 			if(mode==3)
 			{
 				pressanykey("³o¨ÇªF¦è¤£¯à½æ³á....");
 				break;
 			}
			move(b_lines-1,1);
			sprintf(inbuf,"·Q­n½æ¥XÔ£©O? [0]©ñ±ó½æ¥X [1¡ã%d]ª««~°Ó¸¹",oldnum[0]);
#ifdef MAPLE
			getdata(b_lines-1,1,inbuf,genbuf, 3, LCECHO,"0");
#else
                        getdata(b_lines-1,1,inbuf,genbuf, 3, DOECHO,YEA);
                        if ((genbuf[0] >= 'A') && (genbuf[0] <= 'Z'))
                                genbuf[0] = genbuf[0] | 32;
#endif  // END MAPLE
     			choice=atoi(genbuf);
			if(choice>=1 && choice<=oldnum[0])
			{
				clrchyiuan(6,18);
				if(rand()%2>0)
					show_buy_pic(p[choice].pic1);
				else
					show_buy_pic(p[choice].pic2);
				move(b_lines-1,0);
				clrtoeol();  
				move(b_lines-1,1);       
				smoney=0;
				sprintf(inbuf,"§A­n½æ¥Xª««~ [%s] ¦h¤Ö­Ó©O?(¤W­­ %d)",p[choice].name,oldnum[choice]);
#ifdef MAPLE
				getdata(b_lines-1,1,inbuf,genbuf,6, 1, 0); 
#else
                                getdata(b_lines-1,1,inbuf,genbuf,6, DOECHO, YEA);
#endif  // END MAPLE
				smoney=atoi(genbuf);
				if(smoney<0)
				{
					pressanykey("©ñ±ó½æ¥X...");
				}
				else if(smoney>oldnum[choice])
				{
					sprintf(inbuf,"§Aªº [%s] ¨S¦³¨º»ò¦h­Ó³á",p[choice].name);
					pressanykey(inbuf);
				}
				else
				{
					sprintf(inbuf,"½T©w½æ¥Xª««~ [%s] ¼Æ¶q %d ­Ó¶Ü?(©±®a¶R»ù %d) [y/N]:",p[choice].name,smoney,smoney*p[choice].money*8/10);
#ifdef MAPLE
					getdata(b_lines-1,1,inbuf,genbuf, 2, 1, 0);
#else
                                        getdata(b_lines-1,1,inbuf,genbuf, 2, DOECHO, YEA);
#endif  // END MAPLE
					if(genbuf[0]=='y' || genbuf[0]=='Y')
					{
						oldnum[choice]-=smoney;
						d.money+=smoney*p[choice].money*8/10;
						sprintf(inbuf,"¦ÑÁó®³¨«¤F§Aªº%d­Ó%s",smoney,p[choice].name);
						pressanykey(inbuf);
					}
					else
					{
						pressanykey("©ñ±ó½æ¥X...");
					}
				}
			}
			else
			{
				sprintf(inbuf,"©ñ±ó½æ¥X.....");
				pressanykey(inbuf);            
			}
			break;
		case 'Q':
		case 'q':
			sprintf(inbuf,"ª÷¿ú¥æ©ö¦@ %d ¤¸,Â÷¶} %s ",d.money-oldmoney,shopname[mode]);
			pressanykey(inbuf);
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
  }while((pipkey!='Q')&&(pipkey!='q')&&(pipkey!=KEY_LEFT));    
  return 0;
}

int
pip_weapon_doing_menu(variance,type,p)               /* ªZ¾¹ÁÊ¶Rµe­± */
int variance;
int type;
struct weapon *p;
{
  time_t now;
  register int n=0;
  register char *s;
  char buf[256];
  char ans[5];
  char shortbuf[100];
  char menutitle[5][11]={"ÀY³¡¸Ë³Æ°Ï","¥k¤â¸Ë³Æ°Ï","¥ª¤â¸Ë³Æ°Ï","¨­Åé¸Ë³Æ°Ï","¨¬³¡¸Ë³Æ°Ï"};  
  int pipkey;
  char choicekey[5];
  int choice;
  
  do{
   clear();
   showtitle(menutitle[type], BoardName);
   show_weapon_pic(0);
/*   move(10,2); 
   sprintf(buf,"[1;37m²{¤µ¯à¤O:Åé¤OMax:[36m%-5d[37m  ªk¤OMax:[36m%-5d[37m  §ðÀ»:[36m%-5d[37m  ¨¾¿m:[36m%-5d[37m  ³t«×:[36m%-5d [m",
           d.maxhp,d.maxmp,d.attack,d.resist,d.speed);
   prints(buf);*/
   move(11,2);
   sprintf(buf,"[1;37;41m [NO]  [¾¹¨ã¦W]  [Åé¤O]  [ªk¤O]  [³t«×]  [§ðÀ»]  [¨¾¿m]  [³t«×]  [°â  »ù] [m");
   prints(buf);
   move(12,2);
   sprintf(buf," [1;31m¢w¢w[37m¥Õ¦â ¥i¥HÁÊ¶R[31m¢w¢w[32mºñ¦â ¾Ö¦³¸Ë³Æ[31m¢w¢w[33m¶À¦â ¿ú¿ú¤£°÷[31m¢w¢w[35mµµ¦â ¯à¤O¤£¨¬[31m¢w¢w[m");
   prints(buf); 

   n=0;
   while (s = p[n].name)
   {   
     move(13+n,2);
     if(variance!=0 && variance==(n))/*¥»¨­¦³ªº*/
     {
      sprintf(buf, 
      "[1;32m (%2d)  %-10s %4d    %4d    %4d    %4d    %4d    %4d    %6d[m",     
      n,p[n].name,p[n].needmaxhp,p[n].needmaxmp,p[n].needspeed,
      p[n].attack,p[n].resist,p[n].speed,p[n].cost);        
     }
     else if(d.maxhp < p[n].needmaxhp || d.maxmp < p[n].needmaxmp || d.speed < p[n].needspeed )/*¯à¤O¤£¨¬*/
     {
      sprintf(buf, 
      "[1;35m (%2d)  %-10s %4d    %4d    %4d    %4d    %4d    %4d    %6d[m",
      n,p[n].name,p[n].needmaxhp,p[n].needmaxmp,p[n].needspeed,
      p[n].attack,p[n].resist,p[n].speed,p[n].cost);
     }

     else if(d.money < p[n].cost)  /*¿ú¤£°÷ªº*/
     {
      sprintf(buf, 
      "[1;33m (%2d)  %-10s %4d    %4d    %4d    %4d    %4d    %4d    %6d[m",     
      n,p[n].name,p[n].needmaxhp,p[n].needmaxmp,p[n].needspeed,
      p[n].attack,p[n].resist,p[n].speed,p[n].cost);    
     }    
     else
     {
      sprintf(buf, 
      "[1;37m (%2d)  %-10s %4d    %4d    %4d    %4d    %4d    %4d    %6d[m",     
      n,p[n].name,p[n].needmaxhp,p[n].needmaxmp,p[n].needspeed,
      p[n].attack,p[n].resist,p[n].speed,p[n].cost);        
     } 
     prints(buf);
     n++;
   }
   move(b_lines,0); 
   sprintf(buf,"[1;44;37m  ªZ¾¹ÁÊ¶R¿ï³æ  [46m  [B]ÁÊ¶RªZ¾¹  [S]½æ±¼¸Ë³Æ  [W]­Ó¤H¸ê®Æ  [Q]¸õ¥X¡G            [m");
   prints(buf);   
   now=time(0);
   pip_time_change(now);
   pipkey=egetch();
   pip_time_change(now);

   switch(pipkey)  
   {
    case 'B':      
    case 'b':
     move(b_lines-1,1);
     sprintf(shortbuf,"·Q­nÁÊ¶RÔ£©O? §Aªº¿ú¿ú[%d]¤¸:[¼Æ¦r]",d.money);
     prints(shortbuf);
#ifdef MAPLE
     getdata(b_lines-1,1,shortbuf,choicekey, 4, LCECHO,"0");
#else
     getdata(b_lines-1,1,shortbuf,choicekey, 4, DOECHO,YEA);
     if ((choicekey[0] >= 'A') && (choicekey[0] <= 'Z'))
             choicekey[0] = choicekey[0] | 32;
#endif  // END MAPLE
     choice=atoi(choicekey);
     if(choice>=0 && choice<=n)
     {
       move(b_lines-1,0);
       clrtoeol();  
       move(b_lines-1,1);       
       if(choice==0)     /*¸Ñ°£*/
       { 
          sprintf(shortbuf,"©ñ±óÁÊ¶R...");
          pressanykey(shortbuf);
       }
      
       else if(variance==choice)  /*¦­¤w¸g¦³°Õ*/
       {
          sprintf(shortbuf,"§A¦­¤w¸g¦³ %s Åo",p[variance].name);
          pressanykey(shortbuf);      
       }
      
       else if(p[choice].cost >= (d.money+p[variance].sell))  /*¿ú¤£°÷*/
       {
          sprintf(shortbuf,"³o­Ó­n %d ¤¸¡A§Aªº¿ú¤£°÷°Õ!",p[choice].cost);
          pressanykey(shortbuf);      
       }      
     
       else if(d.maxhp < p[choice].needmaxhp || d.maxmp < p[choice].needmaxmp 
               || d.speed < p[choice].needspeed ) /*¯à¤O¤£¨¬*/
       {
          sprintf(shortbuf,"»Ý­nHP %d MP %d SPEED %d ³á",
                p[choice].needmaxhp,p[choice].needmaxmp,p[choice].needspeed);
          pressanykey(shortbuf);            
       }
       else  /*¶¶§QÁÊ¶R*/
       {
          sprintf(shortbuf,"§A½T©w­nÁÊ¶R %s ¶Ü?($%d) [y/N]",p[choice].name,p[choice].cost);
#ifdef MAPLE
          getdata(b_lines-1,1,shortbuf, ans, 2, 1, 0); 
#else
          getdata(b_lines-1,1,shortbuf, ans, 2, DOECHO, YEA);
#endif  // END MAPLE
          if(ans[0]=='y' || ans[0]=='Y')
          {
              sprintf(shortbuf,"¤pÂû¤w¸g¸Ë°t¤W %s ¤F",p[choice].name);
              pressanykey(shortbuf);
              d.attack+=(p[choice].attack-p[variance].attack);
              d.resist+=(p[choice].resist-p[variance].resist);
              d.speed+=(p[choice].speed-p[variance].speed);
              d.money-=(p[choice].cost-p[variance].sell);
              variance=choice;
          }
          else
          {
              sprintf(shortbuf,"©ñ±óÁÊ¶R.....");
              pressanykey(shortbuf);            
          }
       }
     }       
     break;     
     
   case 'S':
   case 's':
     if(variance!=0)
     { 
        sprintf(shortbuf,"§A½T©w­n½æ±¼%s¶Ü? ½æ»ù:%d [y/N]",p[variance].name,p[variance].sell);
#ifdef MAPLE
        getdata(b_lines-1,1,shortbuf, ans, 2, 1, 0); 
#else
        getdata(b_lines-1,1,shortbuf, ans, 2, DOECHO, YEA);
#endif  // END MAPLE
        if(ans[0]=='y' || ans[0]=='Y')
        {
           sprintf(shortbuf,"¸Ë³Æ %s ½æ¤F %d",p[variance].name,p[variance].sell);
           d.attack-=p[variance].attack;
           d.resist-=p[variance].resist;
           d.speed-=p[variance].speed;
           d.money+=p[variance].sell;
           pressanykey(shortbuf);
           variance=0;
        }
        else
        {
           sprintf(shortbuf,"ccc..§Ú¦^¤ßÂà·N¤F...");
           pressanykey(shortbuf);         
        }
     }
     else if(variance==0)
     {
        sprintf(shortbuf,"§A¥»¨Ó´N¨S¦³¸Ë³Æ¤F...");
        pressanykey(shortbuf);
        variance=0;
     }
     break;
                      
   case 'W':
   case 'w':
     pip_data_list();   
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
  }while((pipkey!='Q')&&(pipkey!='q')&&(pipkey!=KEY_LEFT));
    
  return variance;
}
