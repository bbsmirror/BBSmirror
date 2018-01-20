/*---------------------------------------------------------------------------*/
/* ¯S®í¿ï³æ:¬Ý¯f ´îªÎ ¾Ô°« «ô³X ´Â¨£                                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/
#include <time.h>
#include "bbs.h"
#include "pip.h"
extern struct chicken d;
extern time_t start_time;
extern time_t lasttime;
#define getdata(a, b, c , d, e, f, g) getdata(a,b,c,d,e,f,NULL,g)

struct royalset royallist[] = {
"T",	"«ô³X¹ï¶H",	  0,	0,	 0,	  0,NULL,NULL,
"A",	"¬PªÅÃM§L³s",	  1,	10,	15,    	100,"§A¯u¦n¡A¨Ó³­§Ú²á¤Ñ..","¦u½Ã¬PªÅªº¦w¥þ¬O«Ü¨¯­Wªº..",
"B",	"¬PªÅ¢¯¢¯¢¶",	  1,   100,	25,	200,"¯u¬OÂ§»ªªº¤pÂû..§Ú³ßÅw...","¯S°È´N¬O¯µ±K«OÅ@¯¸ªø¦w¥þªº¤H..",
"C",	"Âí°ê¤j±N­x",	  1,   200,	30,	250,"§i¶D§A­ò¡I·í¦~¨º­Ó¾Ô§Ð«Üºë±m³á..","§A¯u¬O°ª¶QÀu¶®ªº¤pÂû...",
"D",	"°Ñ¿ÑÁ`°Èªø",	  1,   300,	35,	300,"§ÚÀ°¯¸ªøºÞ²z³o­Ó°ê®a­ò..","§AªºÁn­µ«Ü¦nÅ¥­C..§Ú«Ü³ßÅw³á...:)",
"E",	"¤p¤Ñ¨Ï¯¸ªø",	  1,   400,	35,	300,"§A«Ü¦³±Ð¾i­ò¡I«Ü°ª¿³»{ÃÑ§A...","Àu¶®ªº§A¡A½ÐÅý§ÚÀ°§A¬èºÖ....",
"F",	"­·ºå¤â¯¸ªø",	  1,   500,	40,	350,"§A¦n¥i·R³á..§Ú³ßÅw§A­ò....","¹ï°Õ..¥H«á­n¦h¦h¨Ó©M§Úª±³á...",
"G",	"¨Ä¤p«Ä¯¸ªø",	  1,   550,	40,	350,"¸ò§AÁ¿¸Ü«Ü§Ö¼Ö³á..¤£¹³¯¸ªø¤@¼ËµL²á..","¨Ó¡A§¤§Ú½¥»\\¤W¡AÅ¥§ÚÁ¿¬G¨Æ..",
"H",	"¤p¦Ì§J¯¸ªø",	  1,   600,	50,     400,"¤@¯¸¤§ªø³d¥ô­«¤j§r..:)..","ÁÂÁÂ§AÅ¥§ÚÁ¿¸Ü..¥H«á­n¦h¨Ó³á...",
"I",	"¬PªÅÄé¤ô¸s",	  2,    60,	 0,	  0,"¤£¿ù­ò..ÆZ¾÷ÆFªº³á..«Ü¥i·R....","¨Ó  §Ú­Ì¤@°_¨ÓÄé¤ô§a....",
"J",	"«C¦~«ÓªZ©x",	  0,	 0,	 0,	  0,"§A¦n¡A§Ú¬OªZ©x¡A­è±q»ÈªeÃä¹Ò¦^¨Ó¥ð®§..","§Æ±æ¤U¦¸ÁÙ¯à¨£¨ì§A...:)",
NULL,		NULL,NULL,    NULL,    NULL,NULL,NULL
};

int pip_see_doctor()	/*¬ÝÂå¥Í*/
{
    char buf[256];
    long savemoney;
    savemoney=d.sick*25;
    if(d.sick<=0)
    {
    pressanykey("«z­ù..¨S¯f¨ÓÂå°|·F¹À..³Q½|¤F..¶ã~~");
    d.character-=(rand()%3+1);
    if(d.character<0)
      d.character=0;
    d.happy-=(rand()%3+3);
    d.satisfy-=rand()%3+2;
    }    
    else if(d.money < savemoney)
    {
     sprintf(buf,"§Aªº¯f­nªá %d ¤¸³á....§A¤£°÷¿ú°Õ...",savemoney);    
     pressanykey(buf);
    }
    else if(d.sick>0 && d.money >=savemoney)
    {
    d.tired-=rand()%10+20;
    if(d.tired<0)
       d.tired=0;
    d.sick=0;
    d.money=d.money-savemoney;
    move(4,0);
    show_special_pic(1);
    pressanykey("ÃÄ¨ì¯f°£..¨S¦³°Æ§@¥Î!!");
    }
    return 0;
}

/*´îªÎ*/
int pip_change_weight()
{
    char genbuf[5];
    char inbuf[256];
    int weightmp;
    
    move(b_lines-1, 0);
    clrtoeol();
    show_special_pic(2);
#ifdef MAPLE
    getdata(b_lines-1,1, "§Aªº¿ï¾Ü¬O? [Q]Â÷¶}:", genbuf, 2, 1, 0);    
#else
    getdata(b_lines-1,1, "§Aªº¿ï¾Ü¬O? [Q]Â÷¶}:", genbuf, 2, DOECHO, YEA);
#endif  // END MAPLE
    if (genbuf[0]=='1'|| genbuf[0]=='2'|| genbuf[0]=='3'|| genbuf[0]=='4')
    { 
      switch(genbuf[0])
      {
        case '1':
          if(d.money<80)
          {
            pressanykey("¶Ç²Î¼W­D­n80¤¸³á....§A¤£°÷¿ú°Õ...");
          }
          else
          {
#ifdef MAPLE
            getdata(b_lines-1,1, "»Ýªá¶O80¤¸(3¡ã5¤½¤ç)¡A§A½T©w¶Ü? [y/N]", genbuf, 2, 1, 0);
#else
            getdata(b_lines-1,1, "»Ýªá¶O80¤¸(3¡ã5¤½¤ç)¡A§A½T©w¶Ü? [y/N]", genbuf, 2, DOECHO, YEA);
#endif  // END MAPLE
            if(genbuf[0]=='Y' || genbuf[0]=='y')
            {
              weightmp=3+rand()%3;
              d.weight+=weightmp;
              d.money-=80;
              d.maxhp-=rand()%2;
              d.hp-=rand()%2+3;
              show_special_pic(3);
              sprintf(inbuf, "Á`¦@¼W¥[¤F%d¤½¤ç",weightmp);
              pressanykey(inbuf);
            }
            else
            {
              pressanykey("¦^¤ßÂà·NÅo.....");
            }
          }
          break;
          
        case '2':
#ifdef MAPLE
          getdata(b_lines-1,1, "¼W¤@¤½¤ç­n30¤¸¡A§A­n¼W¦h¤Ö¤½¤ç©O? [½Ð¶ñ¼Æ¦r]:", genbuf, 4, 1, 0);
#else
          getdata(b_lines-1,1, "¼W¤@¤½¤ç­n30¤¸¡A§A­n¼W¦h¤Ö¤½¤ç©O? [½Ð¶ñ¼Æ¦r]:", genbuf, 4, DOECHO, YEA);
#endif  // END MAPLE
          weightmp=atoi(genbuf);
          if(weightmp<=0)
          {
            pressanykey("¿é¤J¦³»~..©ñ±óÅo...");          
          }
          else if(d.money>(weightmp*30))
          {
            sprintf(inbuf, "¼W¥[%d¤½¤ç¡AÁ`¦@»Ýªá¶O¤F%d¤¸¡A½T©w¶Ü? [y/N]",weightmp,weightmp*30);
#ifdef MAPLE
            getdata(b_lines-1,1,inbuf, genbuf, 2, 1, 0);
#else
            getdata(b_lines-1,1,inbuf, genbuf, 2, DOECHO, YEA);
#endif  // END MAPLE
            if(genbuf[0]=='Y' || genbuf[0]=='y')
            {
                d.money-=weightmp*30;
                d.weight+=weightmp;
                d.maxhp-=(rand()%2+2);
                count_tired(5,8,"N",100,1);
                d.hp-=(rand()%2+3);
                d.sick+=rand()%10+5;
                show_special_pic(3);
                sprintf(inbuf, "Á`¦@¼W¥[¤F%d¤½¤ç",weightmp);
                pressanykey(inbuf);
            }
            else
            {
              pressanykey("¦^¤ßÂà·NÅo.....");
            }
          }
          else
          {
            pressanykey("§A¿ú¨S¨º»ò¦h°Õ.......");            
          }
          break;        
          
        case '3':
          if(d.money<80)
          {
            pressanykey("¶Ç²Î´îªÎ­n80¤¸³á....§A¤£°÷¿ú°Õ...");
          }
          else
          {
#ifdef MAPLE
            getdata(b_lines-1,1, "»Ýªá¶O80¤¸(3¡ã5¤½¤ç)¡A§A½T©w¶Ü? [y/N]", genbuf, 2, 1, 0);
#else
            getdata(b_lines-1,1, "»Ýªá¶O80¤¸(3¡ã5¤½¤ç)¡A§A½T©w¶Ü? [y/N]", genbuf, 2, DOECHO, YEA);
#endif  // END MAPLE
            if(genbuf[0]=='Y' || genbuf[0]=='y')
            {
              weightmp=3+rand()%3;
              d.weight-=weightmp;
              if(d.weight<0)
                   d.weight=0;
              d.money-=100;
              d.maxhp+=rand()%2;
              d.hp-=rand()%2+3;
              show_special_pic(4);
              sprintf(inbuf, "Á`¦@´î¤Ö¤F%d¤½¤ç",weightmp);
              pressanykey(inbuf);
            }
            else
            {
              pressanykey("¦^¤ßÂà·NÅo.....");
            }
          }        
          break;
        case '4':
#ifdef MAPLE
          getdata(b_lines-1,1, "´î¤@¤½¤ç­n30¤¸¡A§A­n´î¦h¤Ö¤½¤ç©O? [½Ð¶ñ¼Æ¦r]:", genbuf, 4, 1, 0);
#else
          getdata(b_lines-1,1, "´î¤@¤½¤ç­n30¤¸¡A§A­n´î¦h¤Ö¤½¤ç©O? [½Ð¶ñ¼Æ¦r]:", genbuf, 4, DOECHO, YEA);
#endif  // END MAPLE
          weightmp=atoi(genbuf);
          if(weightmp<=0)
          {
            pressanykey("¿é¤J¦³»~..©ñ±óÅo...");
          }          
          else if(d.weight<=weightmp)
          {
            pressanykey("§A¨S¨º»ò­«³á.....");
          }
          else if(d.money>(weightmp*30))
          {
            sprintf(inbuf, "´î¤Ö%d¤½¤ç¡AÁ`¦@»Ýªá¶O¤F%d¤¸¡A½T©w¶Ü? [y/N]",weightmp,weightmp*30);
#ifdef MAPLE
            getdata(b_lines-1,1,inbuf, genbuf, 2, 1, 0);
#else
            getdata(b_lines-1,1,inbuf, genbuf, 2, DOECHO, YEA);
#endif  // END MAPLE
            if(genbuf[0]=='Y' || genbuf[0]=='y')
            {
                d.money-=weightmp*30;
                d.weight-=weightmp;
                d.maxhp-=(rand()%2+2);
                count_tired(5,8,"N",100,1);
                d.hp-=(rand()%2+3);
                d.sick+=rand()%10+5;
                show_special_pic(4);
                sprintf(inbuf, "Á`¦@´î¤Ö¤F%d¤½¤ç",weightmp);
                pressanykey(inbuf);
            }
            else
            {
              pressanykey("¦^¤ßÂà·NÅo.....");
            }
          }
          else
          {
            pressanykey("§A¿ú¨S¨º»ò¦h°Õ.......");            
          }
          break;
      }
    }
    return 0;
}


/*°Ñ¨£*/

int
pip_go_palace()
{
  pip_go_palace_screen(royallist);
  return 0;
}

int
pip_go_palace_screen(p) 
struct royalset *p;
{
  int n;
  int a;
  int b;
  int choice;
  int prince;  /*¤ý¤l·|¤£·|¥X²{*/
  int pipkey;
  int change;
  char buf[256];
  char inbuf1[20];
  char inbuf2[20];
  char ans[5];
  char *needmode[3]={"      ","Â§»öªí²{¡Ö","½Í¦R§Þ¥©¡Ö"};
  int save[11]={0,0,0,0,0,0,0,0,0,0,0};

  d.nodone=0; 
  do
  {
  clear();
  show_palace_pic(0);
  move(13,4);
  sprintf(buf,"[1;31m¢z¢w¢w¢w¢w¢w¢w¢t[37;41m ¨Ó¨ìÁ`¥q¥O³¡¤F  ½Ð¿ï¾Ü§A±ý«ô³Xªº¹ï¶H [0;1;31m¢u¢w¢w¢w¢w¢w¢w¢{[0m");
  prints(buf);
  move(14,4);
  sprintf(buf,"[1;31m¢x                                                                  ¢x[0m");
  prints(buf);

  for(n=0;n<5;n++)  
  {
    a=2*n+1;
    b=2*n+2;
    move(15+n,4);
    sprintf(inbuf1,"%-10s%3d",needmode[p[a].needmode],p[a].needvalue);
    if(n==4)
    { 
      sprintf(inbuf2,"%-10s",needmode[p[b].needmode]);
    }
    else
    {
      sprintf(inbuf2,"%-10s%3d",needmode[p[b].needmode],p[b].needvalue);
    }
    if((d.seeroyalJ==1 && n==4)||(n!=4))
      sprintf(buf,"[1;31m¢x [36m([37m%s[36m) [33m%-10s  [37m%-14s     [36m([37m%s[36m) [33m%-10s  [37m%-14s[31m¢x[0m",    
             p[a].num,p[a].name,inbuf1,p[b].num,p[b].name,inbuf2);
    else
      sprintf(buf,"[1;31m¢x [36m([37m%s[36m) [33m%-10s  [37m%-14s                                   [31m¢x[0m",    
             p[a].num,p[a].name,inbuf1);             
    prints(buf);
  }
  move(20,4);
  sprintf(buf,"[1;31m¢x                                                                  ¢x[0m");
  prints(buf);
  move(21,4);
  sprintf(buf,"[1;31m¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}[0m");
  prints(buf);
  

   if(d.death==1 || d.death==2 || d.death==3)
     return 0;    
  /*±N¦U¤H°È¤w¸gµ¹»Pªº¼Æ­È¥s¦^¨Ó*/
   save[1]=d.royalA;            /*from¦u½Ã*/
   save[2]=d.royalB;            /*fromªñ½Ã*/
   save[3]=d.royalC;		/*from±N­x*/
   save[4]=d.royalD;            /*from¤j¦Ú*/
   save[5]=d.royalE;            /*from²½¥q*/
   save[6]=d.royalF;            /*fromÃd¦m*/
   save[7]=d.royalG;            /*from¤ý¦m*/
   save[8]=d.royalH;            /*from°ê¤ý*/
   save[9]=d.royalI;            /*from¤p¤¡*/
   save[10]=d.royalJ;           /*from¤ý¤l*/

   move(b_lines-1, 0);
   clrtoeol();
   move(b_lines-1,0);
   prints("[1;33m [¥Í©R¤O] %d/%d  [¯h³Ò«×] %d [0m",d.hp,d.maxhp,d.tired);
             
   move(b_lines, 0);
   clrtoeol();
   move(b_lines,0);
   prints(
   "[1;37;46m  °Ñ¨£¿ï³æ  [44m [¦r¥À]¿ï¾Ü±ý«ô³Xªº¤Hª«  [Q]Â÷¶}¬PªÅÁ`¥q¥O³¡¡G                    [0m");
   pipkey=egetch();
   choice=pipkey-64;
   if(choice<1 || choice>10)
      choice=pipkey-96;

   if((choice>=1 && choice<=10 && d.seeroyalJ==1)||(choice>=1 && choice<=9 && d.seeroyalJ==0))
   {
    d.social+=rand()%3+3;
    d.hp-=rand()%5+6;
    d.tired+=rand()%5+8;
    if(d.tired>=100)
    {
       d.death=1;
       pipdie("[1;31m²Ö¦º¤F...[m  ",1);
    }
    if(d.hp<0)
    {
       d.death=1;
       pipdie("[1;31m¾j¦º¤F...[m  ",1);
    }
    if(d.death==1)
    {
      sprintf(buf,"ÙTÙT¤F...¯u¬O´d±¡..");
    }
    else
    {
    if((p[choice].needmode==0)||
       (p[choice].needmode==1 && d.manners>=p[choice].needvalue)||
       (p[choice].needmode==2 && d.speech>=p[choice].needvalue))    
    {
      if(choice>=1 && choice<=9 && save[choice] >= p[choice].maxtoman)
      {
        if(rand()%2>0)
            sprintf(buf,"¯à©M³o»ò°¶¤jªº§AÁ¿¸Ü¯u¬Oºa©¯£«...");
        else
            sprintf(buf,"«Ü°ª¿³§A¨Ó«ô³X§Ú¡A¦ý§Ú¤£¯àµ¹§A¤°»ò¤F..");
      }
      else
      {
        change=0;
        if(choice>=1 && choice <=8 )
        {
          switch(choice)
          {
            case 1:
              change=d.character/5;
              break;
            case 2:
              change=d.character/8;
              break;
            case 3:
              change=d.charm/5;
              break;              
            case 4:
              change=d.wisdom/10;
              break;
            case 5:
              change=d.belief/10;
              break;
            case 6:
              change=d.speech/10;
              break;
            case 7:
              change=d.social/10;
              break;
            case 8:
              change=d.hexp/10;
              break;            
          }
          /*¦pªG¤j©ó¨C¦¸ªº¼W¥[³Ì¤j¶q*/
          if(change > p[choice].addtoman)
             change=p[choice].addtoman;
          /*¦pªG¥[¤W­ì¥ýªº¤§«á¤j©ó©Ò¯àµ¹ªº©Ò¦³­È®É*/
          if((change+save[choice])>= p[choice].maxtoman)
             change=p[choice].maxtoman-save[choice];
          save[choice]+=change;
          d.toman+=change;
        }
        else if(choice==9)
        {
          save[9]=0;
          d.social-=13+rand()%4;
          d.affect+=13+rand()%4;
        }
        else if(choice==10 && d.seeroyalJ==1)
        {
            save[10]+=15+rand()%4;
            d.seeroyalJ=0;
        }
        if(rand()%2>0)
            sprintf(buf,"%s",p[choice].words1);
        else    
            sprintf(buf,"%s",p[choice].words2);
      }
    }
    else
    {
      if(rand()%2>0)
            sprintf(buf,"§Ú¤£©M©p³o¼ËªºÂû½Í¸Ü....");
      else
            sprintf(buf,"§A³o°¦¨S±Ð¾iªºÂû¡A¦A¥h¾Ç¾ÇÂ§»ö§a....");    
    
    }
    }    
    pressanykey(buf);
   }
   d.royalA=save[1];
   d.royalB=save[2];
   d.royalC=save[3];
   d.royalD=save[4];
   d.royalE=save[5];
   d.royalF=save[6];
   d.royalG=save[7];
   d.royalH=save[8];
   d.royalI=save[9];
   d.royalJ=save[10];
  }while((pipkey!='Q')&&(pipkey!='q')&&(pipkey!=KEY_LEFT));

  pressanykey("Â÷¶}¬PªÅÁ`¥q¥O³¡.....");  
  return 0;
}

int pip_query()  /*«ô³X¤pÂû*/
{

#ifdef MAPLE
  userec muser;
#endif  // END MAPLE
  int id;
  char genbuf[STRLEN];

#ifndef MAPLE
  char *msg_uid = MSG_UID;
  char *err_uid = ERR_UID;
#endif  // END MAPLE

  stand_title("«ô³X¦P¦ñ");
  usercomplete(msg_uid, genbuf);
  if (genbuf[0])
  {
    move(2, 0);
    if (id = getuser(genbuf))
    {
        pip_read(genbuf);
        pressanykey("Æ[¼¯¤@¤U§O¤Hªº¤pÂû...:p");
    }
    else
    {
      outs(err_uid);
      clrtoeol();
    }
  }
  return 0;
}

int
pip_read(genbuf)
char *genbuf;
{
  FILE *fs;
  char buf[200];
  /*char yo[14][5]={"½Ï¥Í","À¦¨à","¥®¨à","¨àµ£","«C¦~","¤Ö¦~","¦¨¦~",
                  "§§¦~","§§¦~","§§¦~","§ó¦~","¦Ñ¦~","¦Ñ¦~","¥jµ}"};*/
  char yo[12][5]={"½Ï¥Í","À¦¨à","¥®¨à","¨àµ£","¤Ö¦~","«C¦~",
                  "¦¨¦~","§§¦~","§ó¦~","¦Ñ¦~","¥jµ}","¯«¥P"};                  
  int pc1,age1,age=0;
  
  int year1,month1,day1,sex1,death1,nodone1,relation1,liveagain1,dataB1,dataC1,dataD1,dataE1;
  int hp1,maxhp1,weight1,tired1,sick1,shit1,wrist1,bodyA1,bodyB1,bodyC1,bodyD1,bodyE1;
  int social1,family1,hexp1,mexp1,tmpA1,tmpB1,tmpC1,tmpD1,tmpE1;
  int mp1,maxmp1,attack1,resist1,speed1,hskill1,mskill1,mresist1,magicmode1,fightB1,fightC1,fightD1,fightE1;
  int weaponhead1,weaponrhand1,weaponlhand1,weaponbody1,weaponfoot1,weaponA1,weaponB1,weaponC1,weaponD1,weaponE1;
  int toman1,character1,love1,wisdom1,art1,etchics1,brave1,homework1,charm1,manners1,speech1,cookskill1,learnA1,learnB1,learnC1,learnD1,learnE1;
  int happy1,satisfy1,fallinlove1,belief1,offense1,affect1,stateA1,stateB1,stateC1,stateD1,stateE1;
  int food1,medicine1,bighp1,cookie1,ginseng1,snowgrass1,eatC1,eatD1,eatE1;
  int book1,playtool1,money1,thingA1,thingB1,thingC1,thingD1,thingE1;
  int winn1,losee1;
  int royalA1,royalB1,royalC1,royalD1,royalE1,royalF1,royalG1,royalH1,royalI1,royalJ1,seeroyalJ1,seeA1,seeB1,seeC1,seeD1,seeE1;
  int wantend1,lover1;
  char name1[200];
  int classA1,classB1,classC1,classD1,classE1;
  int classF1,classG1,classH1,classI1,classJ1;
  int classK1,classL1,classM1,classN1,classO1;
  int workA1,workB1,workC1,workD1,workE1;
  int workF1,workG1,workH1,workI1,workJ1;
  int workK1,workL1,workM1,workN1,workO1;
  int workP1,workQ1,workR1,workS1,workT1;
  int workU1,workV1,workW1,workX1,workY1,workZ1;

#ifdef MAPLE
  sprintf(buf,"home/%s/new_chicken",genbuf);
  currutmp->destuid = genbuf;
#else
  sprintf(buf,"home/%c/%s/new_chicken",toupper(genbuf[0]),genbuf);
#endif  // END MAPLE

  if(fs=fopen(buf,"r"))
  {
    fgets(buf, 80, fs);
    age = ((time_t) atol(buf))/60/30;
  
    if(age==0) /*½Ï¥Í*/
       age1=0;
    else if( age==1) /*À¦¨à*/
       age1=1;
    else if( age>=2 && age<=5 ) /*¥®¨à*/
       age1=2;
    else if( age>=6 && age<=12 ) /*¨àµ£*/
       age1=3;
    else if( age>=13 && age<=15 ) /*¤Ö¦~*/
       age1=4;     
    else if( age>=16 && age<=18 ) /*«C¦~*/
       age1=5;     
    else if( age>=19 && age<=35 ) /*¦¨¦~*/
       age1=6;
    else if( age>=36 && age<=45 ) /*§§¦~*/
       age1=7;
    else if( age>=45 && age<=60 ) /*§ó¦~*/
       age1=8;
    else if( age>=60 && age<=70 ) /*¦Ñ¦~*/
       age1=9;
    else if( age>=70 && age<=100 ) /*¥jµ}*/
       age1=10;
    else if( age>100 ) /*¯«¥P*/
       age1=11;

    fscanf(fs,
    "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
    &(year1),&(month1),&(day1),&(sex1),&(death1),&(nodone1),&(relation1),&(liveagain1),&(dataB1),&(dataC1),&(dataD1),&(dataE1),
    &(hp1),&(maxhp1),&(weight1),&(tired1),&(sick1),&(shit1),&(wrist1),&(bodyA1),&(bodyB1),&(bodyC1),&(bodyD1),&(bodyE1),
    &(social1),&(family1),&(hexp1),&(mexp1),&(tmpA1),&(tmpB1),&(tmpC1),&(tmpD1),&(tmpE1),
    &(mp1),&(maxmp1),&(attack1),&(resist1),&(speed1),&(hskill1),&(mskill1),&(mresist1),&(magicmode1),&(fightB1),&(fightC1),&(fightD1),&(fightE1),
    &(weaponhead1),&(weaponrhand1),&(weaponlhand1),&(weaponbody1),&(weaponfoot1),&(weaponA1),&(weaponB1),&(weaponC1),&(weaponD1),&(weaponE1),
    &(toman1),&(character1),&(love1),&(wisdom1),&(art1),&(etchics1),&(brave1),&(homework1),&(charm1),&(manners1),&(speech1),&(cookskill1),&(learnA1),&(learnB1),&(learnC1),&(learnD1),&(learnE1),
    &(happy1),&(satisfy1),&(fallinlove1),&(belief1),&(offense1),&(affect1),&(stateA1),&(stateB1),&(stateC1),&(stateD1),&(stateE1),
    &(food1),&(medicine1),&(bighp1),&(cookie1),&(ginseng1),&(snowgrass1),&(eatC1),&(eatD1),&(eatE1),
    &(book1),&(playtool1),&(money1),&(thingA1),&(thingB1),&(thingC1),&(thingD1),&(thingE1),
    &(winn1),&(losee1),
    &(royalA1),&(royalB1),&(royalC1),&(royalD1),&(royalE1),&(royalF1),&(royalG1),&(royalH1),&(royalI1),&(royalJ1),&(seeroyalJ1),&(seeA1),&(seeB1),&(seeC1),&(seeD1),&(seeE1),
    &(wantend1),&(lover1),
    name1,
    &(classA1),&(classB1),&(classC1),&(classD1),&(classE1),
    &(classF1),&(classG1),&(classH1),&(classI1),&(classJ1),
    &(classK1),&(classL1),&(classM1),&(classN1),&(classO1),
    &(workA1),&(workB1),&(workC1),&(workD1),&(workE1),
    &(workF1),&(workG1),&(workH1),&(workI1),&(workJ1),
    &(workK1),&(workL1),&(workM1),&(workN1),&(workO1),
    &(workP1),&(workQ1),&(workR1),&(workS1),&(workT1),
    &(workU1),&(workV1),&(workW1),&(workX1),&(workY1),&(workZ1)
  );
  fclose(fs);

  move(1,0);
  clrtobot();
#ifdef MAPLE
  prints("³o¬O%s¾iªº¤pÂû¡G\n",xuser.userid);
#else
  prints("³o¬O%s¾iªº¤pÂû¡G\n",genbuf);
#endif  // END MAPLE

  if (death1==0)
  {
   prints("[1;32mName¡G%-10s[m  ¥Í¤é¡G%2d¦~%2d¤ë%2d¤é   ¦~ÄÖ¡G%2d·³  ª¬ºA¡G%s  ¿ú¿ú¡G%d\n"
          "¥Í©R¡G%3d/%-3d  §Ö¼Ö¡G%-4d  º¡·N¡G%-4d  ®ð½è¡G%-4d  ´¼¼z¡G%-4d  Åé­«¡G%-4d\n"
          "¤j¸É¤Y¡G%-4d   ­¹ª«¡G%-4d  ¹s­¹¡G%-4d  ¯h³Ò¡G%-4d  Å¼Å¼¡G%-4d  ¯f®ð¡G%-4d\n",
        name1,year1,month1,day1,age,yo[age1],money1,
        hp1,maxhp1,happy1,satisfy1,character1,wisdom1,weight1,
        bighp1,food1,cookie1,tired1,shit1,sick1);

    move(5,0);
    switch(age1)
    {
     case 0:       
     case 1:
     case 2:
       if(weight1<=(60+10*age-30))
          show_basic_pic(1);
       else if(weight1>(60+10*age-30) && weight1<(60+10*age+30))
          show_basic_pic(2);
       else if(weight1>=(60+10*age+30))
          show_basic_pic(3);
       break;
     case 3:
     case 4:
       if(weight1<=(60+10*age-30))
          show_basic_pic(4);
       else if(weight1>(60+10*age-30) && weight1<(60+10*age+30))
          show_basic_pic(5);
       else if(weight1>=(60+10*age+30))
          show_basic_pic(6);
       break;
     case 5:
     case 6:
       if(weight1<=(60+10*age-30))
          show_basic_pic(7);
       else if(weight1>(60+10*age-30) && weight1<(60+10*age+30))
          show_basic_pic(8);
       else if(weight1>=(60+10*age+30))
          show_basic_pic(9);
       break;     
     case 7:
     case 8:
       if(weight1<=(60+10*age-30))
          show_basic_pic(10);
       else if(weight1>(60+10*age-30) && weight1<(60+10*age+30))
          show_basic_pic(11);
       else if(weight1>=(60+10*age+30))
          show_basic_pic(12);
       break;     
     case 9:
       show_basic_pic(13);
       break;
     case 10:
     case 11:
       show_basic_pic(13);
       break;
    }
   move(18,0);
   if(shit1==0) prints("«Ü°®²b..");
   if(shit1>40&&shit1<60) prints("¯ä¯äªº..");
   if(shit1>=60&&shit1<80) prints("¦n¯ä³á..");
   if(shit1>=80&&shit1<100) prints("[1;34m§Ö¯ä¦º¤F..[m");
   if(shit1>=100) {prints("[1;31m¯ä¦º¤F..[m"); return -1;}

   pc1=hp1*100/maxhp1;
   if(pc1==0) {prints("¾j¦º¤F.."); return -1;}
   if(pc1<20) prints("[1;35m¥þ¨­µL¤O¤¤.§Ö¾j¦º¤F.[m");
   if(pc1<40&&pc1>=20) prints("Åé¤O¤£¤Ó°÷..·Q¦YÂIªF¦è..");
   if(pc1<100&&pc1>=80) prints("¶â¡ã¨{¤l¹¡¹¡¦³Åé¤O..");
   if(pc1>=100) prints("[1;34m§Ö¼µ¦º¤F..[m");

   pc1=tired1;
   if(pc1<20) prints("ºë¯«§Ý§Ý¤¤..");
   if(pc1<80&&pc1>=60) prints("[1;34m¦³ÂI¤p²Ö..[m");
   if(pc1<100&&pc1>=80) {prints("[1;31m¦n²Ö³á¡A§Ö¤£¦æ¤F..[m"); }
   if(pc1>=100) {prints("²Ö¦º¤F..."); return -1;}

   pc1=60+10*age;
   if(weight1<(pc1+30) && weight1>=(pc1+10)) prints("¦³ÂI¤p­D..");
   if(weight1<(pc1+50) && weight1>=(pc1+30)) prints("¤Ó­D¤F..");
   if(weight1>(pc1+50)) {prints("­D¦º¤F..."); return -1;}

   if(weight1<(pc1-50)) {prints("½G¦º¤F.."); return -1;}
   if(weight1>(pc1-30) && weight1<=(pc1-10)) prints("¦³ÂI¤p½G..");
   if(weight1>(pc1-50) && weight1<=(pc1-30)) prints("¤Ó½G¤F..");

   if(sick1<75&&sick1>=50) prints("[1;34m¥Í¯f¤F..[m");
   if(sick1<100&&sick1>=75) {prints("[1;31m¯f­«!!..[m"); }
   if(sick1>=100) {prints("¯f¦º¤F.!."); return -1;}

   pc1=happy1;
   if(pc1<20) prints("[1;31m«Ü¤£§Ö¼Ö..[m");
   if(pc1<40&&pc1>=20) prints("¤£§Ö¼Ö..");
   if(pc1<95&&pc1>=80) prints("§Ö¼Ö..");
   if(pc1<=100&&pc1>=95) prints("«Ü§Ö¼Ö..");

   pc1=satisfy1;
   if(pc1<40) prints("[31;1m¤£º¡¨¬..[m");
   if(pc1<95&&pc1>=80) prints("º¡¨¬..");
   if(pc1<=100&&pc1>=95) prints("«Üº¡¨¬..");
  }
  else if(death1==1)
  {
     show_die_pic(2);
     move(14,20);
     prints("¥i¼¦ªº¤pÂû¶ã©I«s«v¤F");
  } 
  else if(death1==2)
  {
     show_die_pic(3);
  }
  else if(death1==3)
  {
    move(5,0);
    outs("¹CÀ¸¤w¸gª±¨ìµ²§½Åo....");
  }
  else
  {
    pressanykey("ÀÉ®×·l·´¤F....");
  }
 }   /* ¦³¾i¤pÂû */
 else
 {
   move(1,0);
   clrtobot();
   pressanykey("³o¤@®aªº¤H¨S¦³¾i¤pÂû......");
 }
}
