/*---------------------------------------------------------------------------*/
/* ª±¼Ö¿ï³æ:´²¨B ®È¹C ¹B°Ê ¬ù·| ²q®±                                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/
#include <time.h>
#include "bbs.h"
#include "pip.h"
extern struct chicken d;
extern time_t start_time;
extern time_t lasttime;
#define getdata(a, b, c , d, e, f, g) getdata(a,b,c,d,e,f,NULL,g)

int pip_play_stroll()	/*´²¨B*/
{
    int lucky;
    count_tired(3,3,"Y",100,0);
    lucky=rand()%7;
    if(lucky==2)
     {
      d.happy+=rand()%3+rand()%3+9;
      d.satisfy+=rand()%3+rand()%3+3;
      d.shit+=rand()%3+3;
      d.hp-=(rand()%3+5);
      move(4,0);
      if(rand()%2>0)
        show_play_pic(1);
      else
        show_play_pic(2);
      pressanykey("¹J¨ìªB¤ÍÅo  ¯u¦n.... ^_^");
     }
    else if(lucky==3)
     {
      d.money+=100;
      d.happy+=rand()%3+6;
      d.satisfy+=rand()%3+4;
      d.shit+=rand()%3+3;
      d.hp-=(rand()%3+4);
      move(4,0);
      show_play_pic(3);
      pressanykey("¾ß¨ì¤F100¤¸¤F..­C­C­C....");
     }

    else if(lucky==4)
     {
      if(rand()%2>0)
      {
       d.happy-=(rand()%2+5);
       move(4,0);
       d.hp-=(rand()%3+3);
       show_play_pic(4);
       if(d.money>=50)
        {
         d.money-=50;
         pressanykey("±¼¤F50¤¸¤F..¶ã¶ã¶ã....");
        }
       else
        {
         d.money=0;
         d.hp-=(rand()%3+3);
         pressanykey("¿ú±¼¥ú¥ú¤F..¶ã¶ã¶ã....");
        }
       d.shit+=rand()%3+2;
      }
      else
      {
       d.happy+=rand()%3+5;
       move(4,0);
       show_play_pic(5);
       if(d.money>=50)
        {
         d.money-=50;
         d.hp-=(rand()%3+3);
         pressanykey("¥Î¤F50¤¸¤F..¤£¥i¥H½|§Ú³á....");
        }
       else
        {
         d.money=0;
         d.hp-=(rand()%3+3);
         pressanykey("¿ú³Q§Ú°½¥Î¥ú¥ú¤F..:p");
        }
       d.shit+=rand()%3+2;
      }
     }
    else if(lucky==5)
     {
      d.happy+=rand()%3+6;
      d.satisfy+=rand()%3+5;
      d.shit+=2;
      move(4,0);
      if(rand()%2>0)
        show_play_pic(6);
      else
        show_play_pic(7);
      pressanykey("¦n´Î³á¾ß¨ìª±¨ã¤F»¡.....");
     }
    else if(lucky==6)
     {
      d.happy-=(rand()%3+10);
      d.shit+=(rand()%3+20);
      move(4,0);
      show_play_pic(9);
      pressanykey("¯u¬O­Ë·°  ¥i¥H¥h¶R·R°ê¼ú¨é");
     }
    else
    {
      d.happy+=rand()%3+3;
      d.satisfy+=rand()%2+1;
      d.shit+=rand()%3+2;
      d.hp-=(rand()%3+2);
      move(4,0);
      show_play_pic(8);
      pressanykey("¨S¦³¯S§Oªº¨Æµo¥Í°Õ.....");
    }
    return 0;
}

int pip_play_sport()	/*¹B°Ê*/
{
    count_tired(3,8,"Y",100,1);
    d.weight-=(rand()%3+2);
    d.satisfy+=rand()%2+3;
    if(d.satisfy>100)
      d.satisfy=100;
    d.shit+=rand()%5+10;
    d.hp-=(rand()%2+8);
    d.maxhp+=rand()%2;
    d.speed+=(2+rand()%3);
    move(4,0);
    show_play_pic(10);
    pressanykey("¹B°Ê¦n³B¦h¦h°Õ...");
    return 0;
}

int pip_play_date()	/*¬ù·|*/
{
    if(d.money<150)
    {
     pressanykey("§A¿ú¤£°÷¦h°Õ! ¬ù·|Á`±oªáÂI¿ú¿ú");
    }
    else
    {
     count_tired(3,6,"Y",100,1);
     d.happy+=rand()%5+12;
     d.shit+=rand()%3+5;
     d.hp-=rand()%4+8;
     d.satisfy+=rand()%5+7;
     d.character+=rand()%3+1;
     d.money=d.money-150;
     move(4,0);
     show_play_pic(11);
     pressanykey("¬ù·|¥h  ©I©I");
    }
    return 0;
}
int pip_play_outing()	/*­¥¹C*/
{
    int lucky;
    char buf[256];
    
    if(d.money<250)
    {
     pressanykey("§A¿ú¤£°÷¦h°Õ! ®È¹CÁ`±oªáÂI¿ú¿ú");
    }
    else
    { 
      d.weight+=rand()%2+1;
      d.money-=250;   
      count_tired(10,45,"N",100,0);
      d.hp-=rand()%10+20;
      if(d.hp>=d.maxhp)
           d.hp=d.maxhp;
      d.happy+=rand()%10+12;
      d.character+=rand()%5+5;
      d.satisfy+=rand()%10+10;
      lucky=rand()%4;
      if(lucky==0)
      {
       d.maxmp+=rand()%3;
       d.art+=rand()%2;
       show_play_pic(12);
       if(rand()%2>0)
         pressanykey("¤ß¤¤¦³¤@ªÑ²H²Hªº·PÄ±  ¦nµÎªA³á....");
       else
         pressanykey("¶³¤ô ¶~±¡ ¤ß±¡¦n¦h¤F.....");
      }
      else if(lucky==1)
      {
       d.art+=rand()%3;
       d.maxmp+=rand()%2;
       show_play_pic(13);
       if(rand()%2>0)
         pressanykey("¦³¤s¦³¤ô¦³¸¨¤é  §Î¦¨¤@´T¬üÄRªºµe..");
       else
         pressanykey("¬ÝµÛ¬ÝµÛ  ¥þ¨­¯h¾Î³£¤£¨£Åo..");
      }
      else if(lucky==2)
      {
       d.love+=rand()%3;
       show_play_pic(14);
       if(rand()%2>0)
         pressanykey("¬Ý  ¤Ó¶§§Ö¨S¤J¤ô¤¤Åo...");
       else
         pressanykey("Å¥»¡³o¬O®üÃä°Õ  §A»¡©O?");
      }      
      else if(lucky==3)
      {
       d.maxhp+=rand()%3;
       show_play_pic(15);
       if(rand()%2>0)
         pressanykey("Åý§Ú­ÌºÆ¨g¦b©]¸Ìªº®üÅy§a....©I©I..");
       else
         pressanykey("²D²nªº®ü­·ªï­±Å§¨Ó  ³Ì³ßÅw³oºØ·PÄ±¤F....");
      }
      if((rand()%301+rand()%200)%100==12)
      {
        lucky=0;
        clear();
        sprintf(buf,"[1;41m  ¬PªÅ¾Ô°«Âû ¡ã %-10s                                                    [0m",d.name); 	 
        show_play_pic(0);
        move(17,10);
        prints("[1;36m¿Ë·Rªº [1;33m%s ¡ã[0m",d.name);
        move(18,10);
        prints("[1;37m¬Ý¨ì§A³o¼Ë§V¤Oªº°ö¾i¦Û¤vªº¯à¤O  Åý§Ú¤ß¤¤¤Q¤Àªº°ª¿³³á..[m");
        move(19,10);
        prints("[1;36m¤p¤Ñ¨Ï§Ú¨M©wµ¹§A¼ú½à¹ªÀy¹ªÀy  °½°½¦aÀ°§U§A¤@¤U....^_^[0m");
        move(20,10);
        lucky=rand()%7;
        if(lucky==6)
        {
          prints("[1;33m§Ú±NÀ°§Aªº¦U¶µ¯à¤O¥þ³¡´£¤É¦Ê¤À¤§¤­³á......[0m");
          d.maxhp=d.maxhp*105/100;
          d.hp=d.maxhp;
          d.maxmp=d.maxmp*105/100;
          d.mp=d.maxmp;          
          d.attack=d.attack*105/100;
          d.resist=d.resist*105/100;          
          d.speed=d.speed*105/100;          
          d.character=d.character*105/100;          
          d.love=d.love*105/100;          
          d.wisdom=d.wisdom*105/100;     
          d.art=d.art*105/100;               
          d.brave=d.brave*105/100;          
          d.homework=d.homework*105/100;          
        }
        
        else if(lucky<=5 && lucky>=4)
        {
          prints("[1;33m§Ú±NÀ°§Aªº¾Ô°«¯à¤O¥þ³¡´£¤É¦Ê¤À¤§¤Q³á.......[0m");        
          d.attack=d.attack*110/100;
          d.resist=d.resist*110/100;          
          d.speed=d.speed*110/100;        
          d.brave=d.brave*110/100;                              
        } 
               
        else if(lucky<=3 && lucky>=2)
        {
          prints("[1;33m§Ú±NÀ°§AªºÅ]ªk¯à¤O©M¥Í©R¤O¥þ³¡´£¤É¦Ê¤À¤§¤Q³á.......[0m");        
          d.maxhp=d.maxhp*110/100;
          d.hp=d.maxhp;
          d.maxmp=d.maxmp*110/100;
          d.mp=d.maxmp;                  
        }
        else if(lucky<=1 && lucky>=0)
        {
          prints("[1;33m§Ú±NÀ°§Aªº·P¨ü¯à¤O¥þ³¡´£¤É¦Ê¤À¤§¤G¤Q³á....[0m");                
          d.character=d.character*110/100;          
          d.love=d.love*110/100;          
          d.wisdom=d.wisdom*110/100;     
          d.art=d.art*110/100;               
          d.homework=d.homework*110/100;                  
        }        
        
        pressanykey("½ÐÄ~Äò¥[ªo³á..."); 
      }
    }
    return 0;
}

int pip_play_kite()	/*­·ºå*/
{
    count_tired(4,4,"Y",100,0);
    d.weight+=(rand()%2+2);
    d.satisfy+=rand()%3+12;
    if(d.satisfy>100)
      d.satisfy=100;
    d.happy+=rand()%5+10;
    d.shit+=rand()%5+6;
    d.hp-=(rand()%2+7);
    d.affect+=rand()%4+6;
    move(4,0);
    show_play_pic(16);
    pressanykey("©ñ­·ºå¯u¦nª±°Õ...");
    return 0;
}

int pip_play_KTV()	/*KTV*/
{
    if(d.money<250)
    {
     pressanykey("§A¿ú¤£°÷¦h°Õ! °ÛºqÁ`±oªáÂI¿ú¿ú");
    }
    else
    {
     count_tired(10,10,"Y",100,0);
     d.satisfy+=rand()%2+20;
     if(d.satisfy>100)
       d.satisfy=100;
     d.happy+=rand()%3+20;
     d.shit+=rand()%5+6;
     d.money-=250;
     d.hp+=(rand()%2+6);
     d.art+=rand()%4+3;
     move(4,0);
     show_play_pic(17);
     pressanykey("§A»¡§A  ·Q­n°k...");
    }
    return 0;
}

int pip_play_guess()   /* ²q®±µ{¦¡ */
{
   int ch,com;
   int pipkey;
   char inbuf[10];
   struct tm *qtime;
   time_t now;

   time(&now);
   qtime = localtime(&now);
   d.satisfy+=(rand()%3+2);
   count_tired(2,2,"Y",100,1);
   d.shit+=rand()%3+2;
   do
   {
    if(d.death==1 || d.death==2 || d.death==3)
      return 0;  
    if(pip_mainmenu(0)) return 0;
    move(b_lines-2,0);
    clrtoeol();  
    move(b_lines, 0);
    clrtoeol();
    move(b_lines,0);
    prints("[1;44;37m  ²q®±¿ï³æ  [46m[1]§Ú¥X°Å¤M [2]§Ú¥X¥ÛÀY [3]§Ú¥X¥¬°Õ [4]²q®±°O¿ý [Q]¸õ¥X¡G         [m");   
    move(b_lines-1, 0);
    clrtoeol();
    pipkey=egetch();
    switch(pipkey)
    {
#ifdef MAPLE
      case Ctrl('R'):
	     if (currutmp->msgs[0].last_pid)
	     {
	      show_last_call_in();
	      my_write(currutmp->msgs[0].last_pid, "¤ô²y¥á¦^¥h¡G");
	     }
	     break;
#endif  // END MAPLE
      case '4':
             situ();
             break;
     }
   }while((pipkey!='1')&&(pipkey!='2')&&(pipkey!='3')&&(pipkey !='q')&&(pipkey !='Q'));

    com=rand()%3;
    move(18,0);
    clrtobot();
    switch(com){
        case 0:
          outs("¤pÂû¡G°Å¤M\n");
         break;
        case 1:
          outs("¤pÂû¡G¥ÛÀY\n");
         break;
        case 2:
          outs("¤pÂû¡G¥¬\n");
         break;
     }

    move(17,0);

    switch(pipkey){
    case '1':
      outs("§A  ¡G°Å¤M\n");
      if (com==0)
        tie();
      else  if (com==1)
        lose();
      else if (com==2)
        win();
      break;
    case '2':
      outs("§A¡@¡G¥ÛÀY\n");
      if (com==0)
        win();
      else if (com==1)
        tie();
      else if (com==2)
        lose();
      break;
    case '3':
      outs("§A¡@¡G¥¬\n");
      if (com==0)
        lose();
      else if (com==1)
        win();
      else if (com==2)
        tie();
      break;
    case 'q':
      break;
  }

}

int win()
{
    d.winn++;
    d.hp-=rand()%2+3;
    move(4,0);
    show_guess_pic(2);
    move(b_lines,0);
    pressanykey("¤pÂû¿é¤F....~>_<~");
    return;
}
int tie()
{
    d.hp-=rand()%2+3;
    d.happy+=rand()%3+5;
    move(4,0);
    show_guess_pic(3);
    move(b_lines,0);
    pressanykey("¥­¤â........-_-");
        return;
}
int lose()
{
    d.losee++;
    d.happy+=rand()%3+5;
    d.hp-=rand()%2+3;
    move(4,0);
    show_guess_pic(1);
    move(b_lines,0);
    pressanykey("¤pÂûÄ¹Åo....*^_^*");
    return;
}

int situ()
{
        clrchyiuan(19,21);
        move(19,0);
        prints("§A:[44m %d³Ó %d­t[m                     \n",d.winn,d.losee);
        move(20,0);
        prints("Âû:[44m %d³Ó %d­t[m                     \n",d.losee,d.winn);

       if (d.winn>=d.losee)
       {
        move(b_lines,0);
        pressanykey("«¢..Ä¹¤pÂû¤]¨S¦h¥úºa");
       }
       else
       {
        move(b_lines,0);
        pressanykey("²Â³J..³º¿éµ¹¤FÂû....£­...");
       }
       return;
}
