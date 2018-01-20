/* ----------------------------------- */
/* pip.c  �i�p���{��                   */
/* ��@��: dsyan   ��g��: fennet      */
/* �Ϲ� by tiball.bbs@bbs.nhctc.edu.tw */
/* ----------------------------------- */

#define getdata(a, b, c , d, e, f, g) getdata(a,b,c,d,e,f,NULL,1)

#include "bbs.h"
#include <time.h>
#include "pip.h"
struct chicken d;
time_t start_time;
time_t lasttime;

#ifndef MAPLE
extern char BoardName[];
#endif  // END MAPLE

/*�C���D�{��*/
int dl_default()
{
 FILE *fs;
 time_t now;
 long smoney;
 int pipkey;
 int ok;
 char genbuf[200];

 modify_user_mode( FIGHT );
 ansimore("etc/games/pip/pip.welcome",YEA);
 showtitle("�P�ž԰���", BoardName);
 srandom(time(0));
#ifdef MAPLE
 sprintf(genbuf,"home/%s/new_chicken",cuser.userid);
#else
 sprintf(genbuf,"home/%c/%s/new_chicken",toupper(cuser.userid[0]),cuser.userid);
#endif  // END MAPLE
 
 pip_read_file();
 if((fs=fopen(genbuf, "r")) == NULL)
 {
   show_system_pic(11);
   move(b_lines,0);
   pipkey=egetch();   
   if(pipkey=='Q' || pipkey=='q')
     return 0;
   if(d.death!=0 || !d.name[0])
   {
       if(!pip_new_game()) return 0;
   }      
 }
 else
 {
   show_system_pic(12);
   move(b_lines,0);
   pipkey=egetch();   
   if(pipkey=='R' || pipkey=='r')
     pip_read_backup();
   else if(pipkey=='Q' || pipkey=='q')
     return 0;
   if(d.death!=0 || !d.name[0])
     {
       if(!pip_new_game()) return 0;
     }
 }
 
 lasttime=time(0);
 start_time=time(0);
 /*pip_do_menu(0,0,pipmainlist);*/
 pip_main_menu();
 d.bbtime+=time(0)-start_time;
 pip_write_file();
 return 0;
}

/*�ɶ����ܪk*/
char*
dsyan_time(const time_t *t)
{
  struct tm *tp;
  static char ans[9];

  tp = localtime(t);
  sprintf(ans, "%02d/%02d/%02d", tp->tm_year, tp->tm_mon + 1,tp->tm_mday);
  return ans;
}

/*�s�C�����]�w*/
int
pip_new_game()
{
  char buf[256];
  time_t now;
  char *pipsex[3]={"�H","��","��"};
  struct tm *ptime;
  ptime = localtime(&now);
  
  if(d.death==1 && !(!d.name[0]))
  {
     clear();
     showtitle("�~�P�԰���", BoardName); 
     move(4,6);
     prints("�w��Ө� [1;5;33m�P�ťͪ���ެ�s�|[0m");
     move(6,6);
     prints("�g�ڭ̽լd���  ���e�A���i�L�p����  �i�O�Q�A�i���F...");
     move(8,6);
     if(d.liveagain<4)
     {
       prints("�ڭ̥i�H���A���p���_��  ���O�ݭn�I�X�@�I�N��");
#ifdef MAPLE
       getdata(10, 6, "�A�n�ڭ����L���Ͷ�? [y/N]:", buf, 2, 1, 0);
#else
       getdata(10, 6, "�A�n�ڭ����L���Ͷ�? [y/N]:", buf, 2, DOECHO, YEA);
#endif  // END MAPLE
       if(buf[0]=='y' || buf[0]=='Y')
       {
         pip_live_again();
       }
     }
     else if(d.liveagain>=4)
     {
       prints("�i�O�A�_����N�Ӧh���F  �p�����W���O�}�M����");     
       move(10,6);
       prints("�ڭ̧䤣��i�H��N���a��F  �ҥH....");
       pressanykey("���s�A�ӧa....��....");    
     }
  }
  if(d.death!=0 || !d.name[0])
  {
    clear();
    showtitle("�~�P�԰���", BoardName);   
    /*�p���R�W*/
    strcpy(buf,"�Q�}");
#ifdef MAPLE
    getdata(2, 3, "���p�����Ӧnť���W�r�a(�Ф��n���Ů�):", buf, 11, 1, 0);
#else
    getdata(2, 3, "���p�����Ӧnť���W�r�a(�Ф��n���Ů�):", buf, 11, DOECHO, YEA);
#endif  // END MAPLE
    if(!buf[0]) return 0;
    strcpy(d.name,buf);
    /*1:�� 2:�� */
#ifdef MAPLE
    getdata(4, 3, "[Boy]�p������ or [Girl]�p������ [b/G]", buf, 2, 1, 0);
#else
    getdata(4, 3, "[Boy]�p������ or [Girl]�p������ [b/G]", buf, 2, DOECHO, YEA);
#endif  // END MAPLE
    if(buf[0]=='b' || buf[0]=='B')
    {
      d.sex=1;
    }  
    else
    {
      d.sex=2; 
    }        
    move(6,3);
    prints("�P�ž԰������C���{��������ت��k");
    move(7,3);
    prints("�靈�����|�b�p��20���ɵ����C���A�çi���p�����򪺵o�i");
    move(8,3);
    prints("��S�������h�@���i��p�����`�~�����C��....");
    /*1:���n�B���B 4:�n�B���B */
#ifdef MAPLE
    getdata(9, 3, "�A�Ʊ�p���C���O�_�n��20������? [Y/n]", buf, 2, 1, 0);
#else
    getdata(9, 3, "�A�Ʊ�p���C���O�_�n��20������? [Y/n]", buf, 2, DOECHO, YEA);
#endif  // END MAPLE
    if(buf[0]=='n' || buf[0]=='N')
    {
      d.wantend=1;
    }  
    else
    {
      d.wantend=4; 
    }        
    /*�}�Y�e��*/
    show_basic_pic(0);
    pressanykey("�p���ש�ϥͤF�A�Цn�n�R�L....");

    /*�}�Y�]�w*/
    now=time(0);
    strcpy(d.birth,dsyan_time(&now));
    d.bbtime=0;

    /*�򥻸��*/
    d.year=ptime->tm_year;
    d.month=ptime->tm_mon + 1;
    d.day=ptime->tm_mday;
    d.death=d.nodone=d.relation=0;
    d.liveagain=d.dataB=d.dataC=d.dataD=d.dataE=0;
          
    /*����Ѽ�*/
    d.hp=rand()%15+20;
    d.maxhp=rand()%20+20;
    if(d.hp>d.maxhp) d.hp=d.maxhp;
    d.weight=rand()%10+50;
    d.tired=d.sick=d.shit=d.wrist=0;
    d.bodyA=d.bodyB=d.bodyC=d.bodyD=d.bodyE=0;
  
    /*�����Ѽ�*/
    d.social=d.family=d.hexp=d.mexp=0;
    d.tmpA=d.tmpB=d.tmpC=d.tmpD=d.tmpE=0;
         
    /*�԰��Ѽ�*/
    d.mp=d.maxmp=d.attack=d.resist=d.speed=d.hskill=d.mskill=d.mresist=0;
    d.magicmode=d.fightB=d.fightC=d.fightD=d.fightE=0;
  
    /*�Z���Ѽ�*/
    d.weaponhead=d.weaponrhand=d.weaponlhand=d.weaponbody=d.weaponfoot=0;
    d.weaponA=d.weaponB=d.weaponC=d.weaponD=d.weaponE=0;
    
    /*��O�Ѽ�*/
    d.toman=d.character=d.love=d.wisdom=d.art=d.etchics=0;
    d.brave=d.homework=d.charm=d.manners=d.speech=d.cookskill=0;
    d.learnA=d.learnB=d.learnC=d.learnD=d.learnE=0;
  
    /*���A�ƭ�*/
    d.happy=rand()%10+20;
    d.satisfy=rand()%10+20;
    d.fallinlove=d.belief=d.offense=d.affect=0;
    d.stateA=d.stateB=d.stateC=d.stateD=d.stateE=0;

    /*�����Ѽ�:���� �s�� �ī~ �j�ɤY*/
    d.food=10;
    d.medicine=d.cookie=d.bighp=2;
    d.ginseng=d.snowgrass=d.eatC=d.eatD=d.eatE=0;

    /*���~�Ѽ�:�� ����*/
    d.book=d.playtool=0;
    d.money=1500;
    d.thingA=d.thingB=d.thingC=d.thingD=d.thingE=0;

    /*�q���Ѽ�:Ĺ �t*/
    d.winn=d.losee=0;

    /*�Ѩ�����*/
    d.royalA=d.royalB=d.royalC=d.royalD=d.royalE=0;
    d.royalF=d.royalG=d.royalH=d.royalI=d.royalJ=0;
    d.seeroyalJ=1;
    d.seeA=d.seeB=d.seeC=d.seeD=d.seeE;
    /*�����D�B�R�H*/        
    d.lover=0;
    /*0:�S�� 1:�]�� 2:�s�� 3:A 4:B 5:C 6:D 7:E */
    d.classA=d.classB=d.classC=d.classD=d.classE=0;
    d.classF=d.classG=d.classH=d.classI=d.classJ=0;
    d.classK=d.classL=d.classM=d.classN=d.classO=0;

    d.workA=d.workB=d.workC=d.workD=d.workE=0;
    d.workF=d.workG=d.workH=d.workI=d.workJ=0;
    d.workK=d.workL=d.workM=d.workN=d.workO=0;
    d.workP=d.workQ=d.workR=d.workS=d.workT=0;
    d.workU=d.workV=d.workW=d.workX=d.workY=d.workZ=0;
    /*�i���O��*/
    now=time(0);
    sprintf(buf, "[1;36m%s %-11s�i�F�@���s [%s] �� %s �p�� [0m\n", Cdate(&now), cuser.userid,d.name,pipsex[d.sex]);
    pip_log_record(buf);
  }  
  pip_write_file();
  return 1;
}

/*�p�����`�禡*/
pipdie(msg,mode)
char *msg;
int mode;
{
 char buf[100];
 char genbuf[200];
 time_t now;
 clear();
 showtitle("�q�l�i�p��", BoardName); 
 if(mode==1)
 {
   show_die_pic(1);
   pressanykey("�����ӱa���p���F");
   clear();
   showtitle("�q�l�i�p��", BoardName); 
   show_die_pic(2);
   move(14,20);
   prints("�i�����p��[1;31m%s[m",msg);
   pressanykey("�P�ūs����....");
 }
 else if(mode==2)
 {
   show_die_pic(3);
   pressanykey("����..�ڳQ���F.....");
 } 
 else if(mode==3)
 {
   show_die_pic(0);
   pressanykey("�C�������o.."); 
 }
 
 now=time(0);
 sprintf(genbuf, "[1;31m%s %-11s���p�� [%s] %s[m\n", Cdate(&now), cuser.userid,d.name, msg);
 pip_log_record(genbuf);
 pip_write_file();
}


/*pro:���v base:���� mode:���� mul:�[�v100=1 cal:�[��*/
int
count_tired(prob,base,mode,mul,cal)
int prob,base;
char *mode;
int mul;
int cal;
{
 int tiredvary=0;
 int tm;
 /*time_t now;*/
 tm=(time(0)-start_time+d.bbtime)/60/30;
 if(mode=="Y")
 {
  if(tm>=0 && tm <=3)
  {
     if(cal==1)
        tiredvary=(rand()%prob+base)*d.maxhp/(d.hp+0.8*d.hp)*120/100;
     else if(cal==0)
        tiredvary=(rand()%prob+base)*4/3;
  }
  else if(tm >=4 && tm <=7)
  {
     if(cal==1)
        tiredvary=(rand()%prob+base)*d.maxhp/(d.hp+0.8*d.hp);
     else if(cal==0)
        tiredvary=(rand()%prob+base)*3/2;
  }
  else if(tm >=8 && tm <=10)
  {
     if(cal==1)
        tiredvary=(rand()%prob+base)*d.maxhp/(d.hp+0.8*d.hp)*110/100;
     else if(cal==0)
        tiredvary=(rand()%prob+base)*5/4;
  }
  else if(tm >=11)
  {
     if(cal==1)
        tiredvary=(rand()%prob+base)*d.maxhp/(d.hp+0.8*d.hp)*150/100;
     else if(cal==0)
        tiredvary=(rand()%prob+base)*1;
  }
 }
 else if(mode=="N")
 {
  tiredvary=rand()%prob+base;
 }

 if(cal==1)
 {
   d.tired+=(tiredvary*mul/100);
   if(d.tired>100)
     d.tired=100;
 }
 else if(cal==0)
 {
   d.tired-=(tiredvary*mul/100);
   if(d.tired<=0)
     {d.tired=0;}
 }
 tiredvary=0;
 return;
}


