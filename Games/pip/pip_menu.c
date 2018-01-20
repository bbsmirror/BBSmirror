/*---------------------------------------------------------------------------*/
/*�D�e���M���                                                               */
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

char *menuname[8][2]={
 {"             ",
  "[1;44;37m ��� [46m[1]�� [2]�}�� [3]�צ� [4]���� [5]���u [6]�S�� [7]�t�� [Q]���}          [0m"},
 
 {"             ",
  "[1;44;37m  �򥻿��  [46m[1]���� [2]�M�� [3]�� [4]�˿� [Q]���X�G                          [m"},

 {"[1;44;37m �}�� [46m�i��`�Ϋ~�j[1]�K�Q�ө� [2]�P���ľQ [3]�]�̮ѧ�                          [m",
  "[1;44;37m ��� [46m�i�Z���ʳf�j[A]�Y���Z�� [B]�k��Z�� [C]����Z�� [D]����Z�� [E]�}���Z��  [m"},
 
 {"[1;44;37m �צ� [46m[A]���(%d) [B]�ֵ�(%d) [C]����(%d) [D]�x��(%d) [E]�C�N(%d)                   [m",
  "[1;44;37m ��� [46m[F]�氫(%d) [G]�]�k(%d) [H]§��(%d) [I]ø�e(%d) [J]�R��(%d) [Q]���X�G         [m"},
  
 {"   ",
  "[1;44;37m  ���ֿ��  [46m[1]���B [2]�B�� [3]���| [4]�q�� [5]�ȹC [6]���~ [7]�ۺq [Q]���X�G  [m"},

 {"[1;44;37m ���u [46m[A]�a�� [B]�O�i [C]���] [D]�A�� [E]�\\�U [F]�а� [G]�a�u [H]���          [m",
  "[1;44;37m ��� [46m[I]���v [J]�y�H [K]�u�a [L]�u�� [M]�a�� [N]�s�a [O]�s�� [P]�]�`�| [Q]���X[m"},
 
 {"   ",
  "[1;44;37m  �S�����  [46m[1]�P����| [2]�A�n�p�� [3]�԰��צ� [4]���X�B�� [5]�`�q�O�� [Q]���X[m"},
  
 {"   ",
  "[1;44;37m  �t�ο��  [46m[1]�ԲӸ�� [2]�p���ۥ� [3]�S�O�A�� [4]�x�s�i�� [5]Ū���i�� [Q]���X[m"}
};

/*�D���*/
int pip_basic_menu(),pip_store_menu(),pip_practice_menu();
int pip_play_menu(),pip_job_menu(),pip_special_menu(),pip_system_menu();
static struct pipcommands pipmainlist[] =
{
pip_basic_menu,		'1',	'1',
pip_store_menu,		'2',	'2',
pip_practice_menu,	'3',	'3',
pip_play_menu,		'4',	'4',
pip_job_menu,		'5',	'5',
pip_special_menu,	'6',	'6',
pip_system_menu,	'7',	'7',
NULL,			'\0',	'\0'
};

/*�򥻿��*/
int pip_basic_feed(),pip_basic_takeshower(),pip_basic_takerest(),pip_basic_kiss();
static struct pipcommands pipbasiclist[] =
{
pip_basic_feed,		'1',	'1',
pip_basic_takeshower,	'2',	'2',
pip_basic_takerest,	'3',	'3',
pip_basic_kiss,		'4',	'4',
NULL,			'\0',	'\0'
};

/*�ө����*/
int pip_store_food(),pip_store_medicine(),pip_store_other();
int pip_store_weapon_head(),pip_store_weapon_rhand(),pip_store_weapon_lhand();
int pip_store_weapon_body(),pip_store_weapon_foot();
static struct pipcommands pipstorelist[] =
{
pip_store_food,		'1',	'1',
pip_store_medicine,	'2',	'2',
pip_store_other,	'3',	'3',
pip_store_weapon_head,	'a',	'A',
pip_store_weapon_rhand,	'b',	'B',
pip_store_weapon_lhand,	'c',	'C',
pip_store_weapon_body,	'd',	'D',
pip_store_weapon_foot,	'e',	'E',
NULL,			'\0',	'\0'
};
/*�צ���*/
int pip_practice_classA(),pip_practice_classB(),pip_practice_classC();
int pip_practice_classD(),pip_practice_classE(),pip_practice_classF();
int pip_practice_classG(),pip_practice_classH(),pip_practice_classI();
int pip_practice_classJ();
static struct pipcommands pippracticelist[] =
{
pip_practice_classA,	'a',	'A',
pip_practice_classB,	'b',	'B',
pip_practice_classC,	'c',	'C',
pip_practice_classD,	'd',	'D',
pip_practice_classE,	'e',	'E',
pip_practice_classF,	'f',	'F',
pip_practice_classG,	'g',	'G',
pip_practice_classH,	'h',	'H',
pip_practice_classI,	'i',	'I',
pip_practice_classJ,	'j',	'J',
NULL,			'\0',	'\0'
};

/*���ֿ��*/
int pip_play_stroll(),pip_play_sport(),pip_play_date(),pip_play_guess();
int pip_play_outing(),pip_play_kite(),pip_play_KTV();
static struct pipcommands pipplaylist[] =
{
pip_play_stroll,	'1',	'1',
pip_play_sport,		'2',	'2',
pip_play_date,		'3',	'3',
pip_play_guess,		'4',	'4',
pip_play_outing,	'5',	'5',
pip_play_kite,		'6',	'6',
pip_play_KTV,		'7',	'7',
NULL,			'\0',	'\0'
};
/*���u���*/
int pip_job_workA(),pip_job_workB(),pip_job_workC(),pip_job_workD();
int pip_job_workE(),pip_job_workF(),pip_job_workG(),pip_job_workH();
int pip_job_workI(),pip_job_workJ(),pip_job_workK(),pip_job_workL();
int pip_job_workM(),pip_job_workN(),pip_job_workO(),pip_job_workP();
static struct pipcommands pipjoblist[] =
{
pip_job_workA,		'a',	'A',
pip_job_workB,		'b',	'B',
pip_job_workC,		'c',	'C',
pip_job_workD,		'd',	'D',
pip_job_workE,		'e',	'E',
pip_job_workF,		'f',	'F',
pip_job_workG,		'g',	'G',
pip_job_workH,		'h',	'H',
pip_job_workI,		'i',	'I',
pip_job_workJ,		'j',	'J',
pip_job_workK,		'k',	'K',
pip_job_workL,		'l',	'L',
pip_job_workM,		'm',	'M',
pip_job_workN,		'n',	'N',
pip_job_workO,		'o',	'O',
pip_job_workP,		'p',	'P',
NULL,			'\0',	'\0'
};

/*�S�����*/
int pip_see_doctor(),pip_change_weight(),pip_meet_vs_man(),pip_query(),pip_go_palace();
static struct pipcommands pipspeciallist[] =
{
pip_see_doctor,		'1',	'1',
pip_change_weight,	'2',	'2',
pip_meet_vs_man,	'3',	'3',
pip_query,		'4',	'4',
pip_go_palace,		'5',	'5',
NULL,			'\0',	'\0'
};

/*�t�ο��*/
int pip_data_list(),pip_system_freepip(),pip_system_service();
int pip_write_backup(),pip_read_backup();
int pip_divine(),pip_results_show();
static struct pipcommands pipsystemlist[] =
{
pip_data_list,		'1',	'1',
pip_system_freepip,	'2',	'2',
pip_system_service,	'3',	'3',
pip_write_backup,	'4',	'4',
pip_read_backup,	'5',	'5',
pip_divine,		'o',	'O',
pip_results_show,	's',	'S',
NULL,			'\0',	'\0'
};



/*����menu.c���\��*/
int
pip_do_menu(menunum,menumode,cmdtable)
int menunum,menumode;
struct pipcommands cmdtable[];
{
	time_t now;
	int key1,key2;
	int pipkey;
	int goback=0,ok=0;
	int class1=0,class2=0,class3=0,class4=0,class5=0;
	int class6=0,class7=0,class8=0,class9=0,class10=0;
	struct pipcommands *cmd1;
	struct pipcommands *cmd2;

	do
	{
	   ok=0;
	   /*�P�_�O�_���`  �����Y���^�W�@�h*/
	   if(d.death==1 || d.death==2 || d.death==3)
	     return 0;
	   /*�gpip_mainmenu�P�w��O�_���`*/
	   if(pip_mainmenu(menumode)) 
	     return 0;

	   class1=d.wisdom/200+1;			/*���*/
	   if(class1>5)  class1=5;
	   class2=(d.affect*2+d.wisdom+d.art*2+d.character)/400+1; /*�ֵ�*/
	   if(class2>5)  class2=5;  
	   class3=(d.belief*2+d.wisdom)/400+1;		/*����*/
	   if(class3>5)  class3=5;   
	   class4=(d.hskill*2+d.wisdom)/400+1;		/*�x��*/
	   if(class4>5)  class4=5; 
	   class5=(d.hskill+d.attack)/400+1;		/*�C�N*/
	   if(class5>5)  class5=5; 
	   class6=(d.hskill+d.resist)/400+1;		/*�氫*/
	   if(class6>5)  class6=5; 
	   class7=(d.mskill+d.maxmp)/400+1;		/*�]�k*/
	   if(class7>5)  class7=5;    
	   class8=(d.manners*2+d.character)/400+1;	/*§��*/
	   if(class8>5)  class8=5; 
	   class9=(d.art*2+d.character)/400+1; 		/*ø�e*/
	   if(class9>5)  class9=5;      
	   class10=(d.art*2+d.charm)/400+1;		/*�R��*/
	   if(class10>5) class10=5; 
	   
	   clrchyiuan(22,24);
	   move(b_lines-1,0);
	   prints(menuname[menunum][0],class1,class2,class3,class4,class5);
	   move(b_lines,0);
	   prints(menuname[menunum][1],class6,class7,class8,class9,class10);
	   
	   now=time(0);   
	   pip_time_change(now);
	   pipkey=egetch();
	   now=time(0);
	   pip_time_change(now);
	
	   cmd1=cmdtable;
	   cmd2=cmdtable;
	   switch(pipkey)
	   {
#ifdef MAPLE
	     case Ctrl('R'):
		if (currutmp->msgs[0].last_pid) 
		{
		    show_last_call_in();
		    my_write(currutmp->msgs[0].last_pid,"�y�P��^�h�G",0);
		}
		break;
#endif  // END MAPLE

#ifdef MAPLE			
	     case KEY_ESC:
		if (KEY_ESC_arg == 'c')
		    capture_screen();
		else if (KEY_ESC_arg == 'n') 
		    edit_note();
		break;
#endif  // END MAPLE
			
	     case KEY_LEFT:
	     case 'q':
	     case 'Q':		
	        goback=1;
		break;
		
	     default:
		for(cmd1; key1 = cmd1->key1; cmd1++)
		/*if(key == tolower(pipkey))*/
		if(key1 == pipkey)
		{
		    cmd1->fptr();
		    ok=1;
		}
		for(cmd2; key2 = cmd2->key2; cmd2++)
		if(ok==0 && key2 == pipkey)
		{
		    cmd2->fptr();
		}
		break;
	   }  
	}while(goback==0);

	return 0;
}


/*---------------------------------------------------------------------------*/
/* �򥻿��:���� �M�� �˿� ��                                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
int pip_main_menu()
{
 pip_do_menu(0,0,pipmainlist);
 return 0;
}

/*---------------------------------------------------------------------------*/
/* �򥻿��:���� �M�� �˿� ��                                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
int pip_basic_menu()
{
 pip_do_menu(1,0,pipbasiclist);
 return 0;
}

/*---------------------------------------------------------------------------*/
/* �ө����:���� �s�� �j�ɤY ���� �ѥ�                                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
int pip_store_menu()
{
   pip_do_menu(2,1,pipstorelist);
   return 0;
}

/*---------------------------------------------------------------------------*/
/* �צ���:���� �m�Z �צ�                                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
int pip_practice_menu()
{
   pip_do_menu(3,3,pippracticelist);
   return 0;
}

     
/*---------------------------------------------------------------------------*/
/* ���ֿ��:���B �ȹC �B�� ���| �q��                                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/
int pip_play_menu()
{
  pip_do_menu(4,0,pipplaylist);
  return 0;
}

/*---------------------------------------------------------------------------*/
/* ���u���:�a�� �W�u �a�� �a�u                                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
int pip_job_menu()
{
   pip_do_menu(5,2,pipjoblist);
   return 0;
}

/*---------------------------------------------------------------------------*/
/* �S�����:�ݯf ��� �԰� ���X �¨�                                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/
int pip_special_menu()
{
  pip_do_menu(6,0,pipspeciallist);
  return 0;
}

/*---------------------------------------------------------------------------*/
/* �t�ο��:�ӤH���  �p�����  �S�O�A��                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/
int pip_system_menu()
{
  pip_do_menu(7,0,pipsystemlist);
  return;
}


int
pip_mainmenu(mode)
int mode;
{
 char genbuf[200];
 char inbuf1[20];
 char inbuf2[20];
 char buf[256];
 time_t now;

 int tm,m,color,tm1,m1;
 int age;
 int color1,color2,color3,color4;
 int anynum;
 float pc;
 char yo[12][5]={"�ϥ�","����","����","�ൣ","�֦~","�C�~",
                 "���~","���~","��~","�Ѧ~","�j�}","���P"};

 color1=color2=color3=color4=37;
 move(1,0);
 tm=(time(0)-start_time+d.bbtime)/60/30; /* �@�� */
 tm1=(time(0)-start_time+d.bbtime)/60;
 m=d.bbtime/60/30;
 m1==d.bbtime/60;
 /*���j�@���ɪ��W�[���ܭ�*/
 if(m!=tm)
 {
  d.wisdom+=10;
  d.happy+=rand()%5+5;
  if(d.happy>100)
     d.happy=100;
  d.satisfy+=rand()%5;
  if(d.satisfy>100)
     d.satisfy=100;
  if(tm<13) d.maxhp+=rand()%5+5; else d.maxhp-=rand()%15;
  d.character+=rand()%5;
  d.money+=500;
  d.seeroyalJ=1;
  count_tired(1,7,"N",100,0);
  d.bbtime+=time(0)-start_time;
  start_time=time(0);
  pip_write_file();

  /*�O���}�l*/
  now=time(0);
  sprintf(genbuf, "[1;37m%s %-11s���p�� [%s] �� %d ���F [0m\n", Cdate(&now), cuser.userid,d.name,m+1);
  pip_log_record(genbuf);
  /*�O���פ�*/
  clear();
  showtitle("�q�l�i�p��", BoardName);  
  show_basic_pic(20); /*�ͤ�ּ�*/
  pressanykey("�p�����j�@���F..");
  /*����*/
  if(tm%2==0)
     pip_results_show();
  if(tm>=21 && (d.wantend==4 || d.wantend==5 || d.wantend==6))
     pip_ending_screen(); 
  
  clrtobot();
  refresh();
 }
 color=37;
 m=tm;
 
 if((rand()%30==29) && tm>=15 && d.charm>=300 && d.character >=300)
    pip_marriage_offer();
    
 if(mode!=1 && rand()%71==69)
    pip_divine();

 /*�Z�x*/
 if((time(0)-start_time)>=900 )
 {
  d.seeroyalJ=0;
 }
 
 if(m==0) /*�ϥ�*/
     age=0;
 else if( m==1) /*����*/
     age=1;
 else if( m>=2 && m<=5 ) /*����*/
     age=2;
 else if( m>=6 && m<=12 ) /*�ൣ*/
     age=3;
 else if( m>=13 && m<=15 ) /*�֦~*/
     age=4;     
 else if( m>=16 && m<=18 ) /*�C�~*/
     age=5;     
 else if( m>=19 && m<=35 ) /*���~*/
     age=6;
 else if( m>=36 && m<=45 ) /*���~*/
     age=7;
 else if( m>=45 && m<=60 ) /*��~*/
     age=8;
 else if( m>=60 && m<=70 ) /*�Ѧ~*/
     age=9;
 else if( m>=70 && m<=100 ) /*�j�}*/
     age=10;
 else if( m>100 ) /*���P*/
     age=11;
 clear(); 
 /*showtitle("�q�l�i�p��", BoardName);*/
 move(0,0);
 if(d.sex==1)
   sprintf(buf,"[1;41m  �P�ž԰��� �� [32m�� [37m%-15s                                             [0m",d.name); 	 
 else if(d.sex==2)
   sprintf(buf,"[1;41m  �P�ž԰��� �� [33m�� [37m%-15s                                             [0m",d.name); 	 
 else 
   sprintf(buf,"[1;41m  �P�ž԰��� �� [34m�H [37m%-15s                                             [0m",d.name); 	 
 prints(buf); 
 
 move(1,0);
 if(d.money<=100)
     color1=31;
 else if(d.money>100 && d.money<=500)
     color1=33;
 else
     color1=37;
 sprintf(inbuf1,"%02d/%02d/%02d",d.year-11,d.month,d.day);
 sprintf(buf
 ," [1;32m[��  �A][37m %-5s     [32m[��  ��][37m %-9s [32m[�~  ��][37m %-5d     [32m[��  ��][%dm %-8d [m"
 ,yo[age],inbuf1,tm,color1,d.money);
 prints(buf);
   
 move(2,0);   
 
 if((d.hp*100/d.maxhp)<=20)
     color1=31;
 else if((d.hp*100/d.maxhp)<=40 && (d.hp*100/d.maxhp)>20)
     color1=33;
 else
     color1=37;   
 if(d.maxmp==0)
     color2=37;
 else if((d.mp*100/d.maxmp)<=20)
     color2=31;
 else if((d.mp*100/d.maxmp)<=40 && (d.mp*100/d.maxmp)>20)
     color2=33;
 else
     color2=37;   
   
 if(d.tired>=80)
     color3=31;
 else if(d.tired<80 && d.tired >=60)
     color3=33;
 else
     color3=37;      
     
 sprintf(inbuf1,"%d/%d",d.hp,d.maxhp);  
 sprintf(inbuf2,"%d/%d",d.mp,d.maxmp);       
 sprintf(buf
 ," [1;32m[��  �R][%dm %-10s[32m[�k  �O][%dm %-10s[32m[��  ��][37m %-5d     [32m[�h  ��][%dm %-4d[0m "
 ,color1,inbuf1,color2,inbuf2,d.weight,color3,d.tired);
 prints(buf);
   
 move(3,0);
 if(d.shit>=80)
     color1=31;
 else if(d.shit<80 && d.shit >=60)
     color1=33;
 else
     color1=37;         
 if(d.sick>=75)
     color2=31;
 else if(d.sick<75 && d.sick >=50)
     color2=33;
 else
     color2=37;           
 if(d.happy<=20)
     color3=31;
 else if(d.happy>20 && d.happy <=40)
     color3=33;
 else
     color3=37;           
 if(d.satisfy<=20)
     color4=31;
 else if(d.satisfy>20 && d.satisfy <=40)
     color4=33;
 else
     color4=37;           
 sprintf(buf
 ," [1;32m[ż  ż][%dm %-4d      [32m[�f  ��][%dm %-4d      [32m[�ּ֫�][%dm %-4d      [32m[���N��][%dm %-4d[0m"
 ,color1,d.shit,color2,d.sick,color3,d.happy,color4,d.satisfy);
 prints(buf);              
 if(mode==0)  /*�D�n�e��*/
 {
   anynum=0;
   anynum=rand()%4;
   move(4,0);
   if(anynum==0)
     sprintf(buf," [1;35m[������]:[31m����[36m���ܦM�I  [33m����[36m����ĵ�i  [37m�զ�[36m���ܦw��[0m");
   else if(anynum==1)
     sprintf(buf," [1;35m[������]:[37m�n�h�h�`�N�p�����h�ҫשM�f��  �H�K�֦��f��[0m");     
   else if(anynum==2)
     sprintf(buf," [1;35m[������]:[37m�H�ɪ`�N�p�����ͩR�ƭȭ�![0m");                  
   else if(anynum==3)
     sprintf(buf," [1;35m[������]:[37m�ּּ֧֪��p���~�O���֪��p��.....[0m");                       
   prints(buf);               
 }
 else if(mode==1)/*����*/
 {
   move(4,0);
   if(d.food==0)
     color1=31;
   else if(d.food<=5 && d.food>0)
     color1=33;
   else
     color1=37;         
   if(d.cookie==0)
     color2=31;
   else if(d.cookie<=5 && d.cookie>0)
     color2=33;
   else
     color2=37;           
   if(d.bighp==0)
     color3=31;
   else if(d.bighp<=2 && d.bighp >0)
     color3=33;
   else
     color3=37;           
   if(d.medicine==0)
     color4=31;
   else if(d.medicine<=5 && d.medicine>0)
     color4=33;
   else
     color4=37;           
   sprintf(buf
   ," [1;36m[����][%dm%-7d[36m[�s��][%dm%-7d[36m[�ɤY][%dm%-7d[36m[�F��][%dm%-7d[36m[�H��][37m%-7d[36m[����][37m%-7d[0m"
   ,color1,d.food,color2,d.cookie,color3,d.bighp,color4,d.medicine,d.ginseng,d.snowgrass);
   prints(buf);
   
 }  
 else if(mode==2)/*���u*/
 {
   move(4,0);
   sprintf(buf
   ," [1;36m[�R��][37m%-5d[36m[���z][37m%-5d[36m[���][37m%-5d[36m[���N][37m%-5d[36m[�D�w][37m%-5d[36m[�i��][37m%-5d[36m[�a��][37m%-5d[0m"   
   ,d.love,d.wisdom,d.character,d.art,d.etchics,d.brave,d.homework);
   prints(buf);
   
 }  
 else if(mode==3)/*�צ�*/
 {
   move(4,0);
   sprintf(buf
   ," [1;36m[���z][37m%-5d[36m[���][37m%-5d[36m[���N][37m%-5d[36m[�i��][37m%-5d[36m[����][37m%-5d[36m[���m][37m%-5d[36m[�t��][37m%-5d[0m"   
   ,d.wisdom,d.character,d.art,d.brave,d.attack,d.resist,d.speed);
   prints(buf);
   
 }  
  move(5,0);
  prints("[1;%dm�z�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�{[m",color);  
  move(6,0);
  switch(age)
  {
     case 0:       
     case 1:
     case 2:
       if(d.weight<=(60+10*tm-30))
          show_basic_pic(1);
       else if(d.weight>(60+10*tm-30) && d.weight<(60+10*tm+30))
          show_basic_pic(2);
       else if(d.weight>=(60+10*tm+30))
          show_basic_pic(3);
       break;
     case 3:
     case 4:
       if(d.weight<=(60+10*tm-30))
          show_basic_pic(4);
       else if(d.weight>(60+10*tm-30) && d.weight<(60+10*tm+30))
          show_basic_pic(5);
       else if(d.weight>=(60+10*tm+30))
          show_basic_pic(6);
       break;
     case 5:
     case 6:
       if(d.weight<=(60+10*tm-30))
          show_basic_pic(7);
       else if(d.weight>(60+10*tm-30) && d.weight<(60+10*tm+30))
          show_basic_pic(8);
       else if(d.weight>=(60+10*tm+30))
          show_basic_pic(9);
       break;     
     case 7:
     case 8:
       if(d.weight<=(60+10*tm-30))
          show_basic_pic(10);
       else if(d.weight>(60+10*tm-30) && d.weight<(60+10*tm+30))
          show_basic_pic(11);
       else if(d.weight>=(60+10*tm+30))
          show_basic_pic(12);
       break;     
     case 9:
       show_basic_pic(13);
       break;
     case 10:
     case 11:
       show_basic_pic(16);
       break;
  }
  

 move(18,0);
 prints("[1;%dm�|�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�}[m",color);
 move(19,0);
 prints(" [1;34m�w[37;44m  �� �A  [0;1;34m�w[0m");
 move(20,0);
 prints(" ");
 if(d.shit==0)
     prints("���b�p��  ");
 if(d.shit>40&&d.shit<60)
     prints("���I���  ");
 if(d.shit>=60&&d.shit<80)
     prints("[1;33m�ܯ�F��[m  ");
 if(d.shit>=80&&d.shit<100)
  {
     prints("[1;35m�֯䦺�F[m  ");
     d.sick+=4;
     d.character-=(rand()%3+3);
  }
 if(d.shit>=100)
  {
     d.death=1;
     pipdie("[1;31m�z��䦺�F[m  ",1);
     return -1;
  }

 if(d.hp<=0)
   pc=0;
 else
   pc=d.hp*100/d.maxhp;
 if(pc==0)
  {
     d.death=1;
     pipdie("[1;31m���j���F[m  ",1);
     return -1;
  }
 if(pc<20)
  {
     prints("[1;35m�־j���F[m  ");
     d.sick+=3;
     d.happy-=5;
     d.satisfy-=3;
  }
 if(pc<40&&pc>=20)
     prints("[1;33m�Q�Y�F��[m  ");
 if(pc<=100&&pc>=90)
     prints("�{�l����  ");
 if(pc<110&&pc>100)
     prints("[1;33m��������[m  ");

 pc=d.tired;
 if(pc<20)
     prints("�믫�ܦn  ");
 if(pc<80&&pc>=60)
     prints("[1;33m���I�p��[m  ");
 if(pc<100&&pc>=80)
  {
     prints("[1;35m�u���ܲ�[m  ");
     d.sick+=5;
  }
 if(pc>=100)
  {
     d.death=1;
     pipdie("[1;31m����֦��F[m  ",1);
     return -1;
  }

 pc=60+10*tm;
 if(d.weight<(pc+30) && d.weight>=(pc+10))
     prints("[1;33m���I�p�D[m  ");
 if(d.weight<(pc+50) && d.weight>=(pc+30))
  {
     prints("[1;35m�ӭD�F��[m  ");
     d.sick+=3;
     if(d.speed>=2)
        d.speed-=2;
     else
        d.speed=0;
     
  }
 if(d.weight>(pc+50))
  {
     d.death=1;
     pipdie("[1;31m���Φ��F[m  ",1);
     return -1;
  }

 if(d.weight<(pc-50))
  {
     d.death=1;
     pipdie("[1;31m:~~ �G���F[m  ",1);
     return -1;
  }
 if(d.weight>(pc-30) && d.weight<=(pc-10))
     prints("[1;33m���I�p�G[m  ");
 if(d.weight>(pc-50) && d.weight<=(pc-30))
     prints("[1;35m�ӽG�F��[m ");

 if(d.sick<75 &&d.sick>=50)
  {
     prints("[1;33m�ͯf�F��[m  ");
     count_tired(1,8,"Y",100,1);
  }
 if(d.sick<100&&d.sick>=75)
  {
     prints("[1;35m���f����[m  ");
     d.sick+=5;
     count_tired(1,15,"Y",100,1);
  }
 if(d.sick>=100)
  {
     d.death=1;
     pipdie("[1;31m�f���F�� :~~[m  ",1);
     return -1;
  }

 pc=d.happy;
 if(pc<20)
     prints("[1;35m�ܤ��ּ�[m  ");
 if(pc<40&&pc>=20)
     prints("[1;33m���ӧּ�[m  ");
 if(pc<95&&pc>=80)
     prints("�ְּ�..  ");
 if(pc<=100 &&pc>=95)
     prints("�ܧּ�..  ");

 pc=d.satisfy;
 if(pc<20) prints("[1;35m�ܤ�����..[m  ");
 if(pc<40&&pc>=20) prints("[1;33m���Ӻ���[m  ");
 if(pc<95&&pc>=80) prints("������..  ");
 if(pc<=100 && pc>=95) prints("�ܺ���..  ");

 prints("\n");

 pip_write_file();
 return 0;
}

/*�T�w�ɶ��@���� */
int
pip_time_change(cnow)
time_t cnow;
{
  int stime=60;
  int stired=2;
  while ((time(0)-lasttime)>=stime) /* �T�w�ɶ������� */
  {
   /*������  �٬O�|��ż��*/
   if((time(0)-cnow)>=stime)
      d.shit+=(rand()%3+3);
   /*������  �h�ҷ��M��C��*/
   if(d.tired>=stired) d.tired-=stired; else d.tired=0;
   /*������  �{�l�]�|�j�� */
   d.hp-=rand()%2+2;
   if(d.mexp<0)
      d.mexp=0;
   if(d.hexp<0)
      d.hexp=0;
   /*��O�|�]�ͯf���C�@�I*/
   d.hp-=d.sick/10;
   /*�f��|�H���v�W�[��ֳ֤\*/
   if(rand()%3>0)
    {
       d.sick-=rand()%2;
       if(d.sick<0)
         d.sick=0;
    }
   else
      d.sick+=rand()%2;
   /*�H����ּ֫�*/
   if(rand()%4>0)
    {
       d.happy-=rand()%2+2;
    }
   else
       d.happy+=2;
   if(rand()%4>0)
    {
       d.satisfy-=(rand()%4+5);
    }
   else
       d.satisfy+=2;
   lasttime+=stime;
  };
   /*�ּ֫׺��N�׳̤j�ȳ]�w*/
   if(d.happy>100)
     d.happy=100;
   else if(d.happy<0)
     d.happy=0;
   if(d.satisfy>100)
     d.satisfy=100;
   else if(d.satisfy<0)
     d.satisfy=0;  
   /*����*/
   if(d.social<0)
     d.social=0;
   if(d.tired<0)
     d.tired=0;
   if(d.hp>d.maxhp)
     d.hp=d.maxhp;
   if(d.mp>d.maxmp)
     d.mp=d.maxmp;
   if(d.money<0)
     d.money=0;
   if(d.charm<0)
     d.charm=0;
}