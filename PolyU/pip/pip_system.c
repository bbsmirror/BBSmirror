/*---------------------------------------------------------------------------*/
/* ¨t²Î¿ï³æ:­Ó¤H¸ê®Æ  ¤pÂû©ñ¥Í  ¯S§OªA°È                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/
#include <time.h>
#include "bbs.h"
#include "pip.h"
extern struct chicken d;
extern time_t start_time;
extern time_t lasttime;
#define getdata(a, b, c , d, e, f, g) getdata(a,b,c,d,e,f,NULL,g)

char weaponhead[7][10]={
"¨S¦³¸Ë³Æ",
"¶ì½¦´U¤l", 
"¤û¥Ö¤p´U",
"¡À¦w¥þ´U",
"¿ûÅKÀY²¯",
"Å]ªk¾vãT",
"¶Àª÷¸t²¯"};


char weaponrhand[10][10]={
"¨S¦³¸Ë³Æ",
"¤j¤ì´Î",  
"ª÷ÄÝ§æ¤â",
"«C»É¼C",  
"´¸¹p¼C", 
"ÂÍÁl¤M", 
"§Ñ±¡¼C", 
"·àÀYÄ_¤M",
"±OÀs¤M",  
"¶Àª÷¸t§ú"
};  

char weaponlhand[8][10]={
"¨S¦³¸Ë³Æ",
"¤j¤ì´Î", 
"ª÷ÄÝ§æ¤â",
"¤ì¬Þ",
"¤£ÄÃ¿û¬Þ",
"¥Õª÷¤§¬Þ",
"Å]ªk¬Þ",
"¶Àª÷¸t¬Þ"
};


char weaponbody[7][10]={
"¨S¦³¸Ë³Æ",
"¶ì½¦«`¥Ò",
"¯S¯Å¥Ö¥Ò",
"¿ûÅK²¯¥Ò",
"Å]ªk©Ü­·",
"¥Õª÷²¯¥Ò",
"¶Àª÷¸t¦ç"};

char weaponfoot[8][12]={
"¨S¦³¸Ë³Æ",
"¶ì½¦©ì¾c",
"ªF¬v¤ì®j",
"¯S¯Å«B¾c",
"NIKE¹B°Ê¾c",
"Æs³½¥Ö¹u",
"­¸¤ÑÅ]¹u",
"¶Àª÷¸t¹u"
};

int 
pip_system_freepip()
{
      char buf[256];
      move(b_lines-1, 0);
      clrtoeol();
#ifdef MAPLE
      getdata(b_lines-1,1, "¯uªº­n©ñ¥Í¶Ü¡H(y/N)", buf, 2, 1, 0);
#else
      getdata(b_lines-1,1, "¯uªº­n©ñ¥Í¶Ü¡H(y/N)", buf, 2, DOECHO, YEA);
#endif  // END MAPLE
      if (buf[0]!='y'&&buf[0]!='Y') return 0;
      sprintf(buf,"%s ³Q¬½¤ßªº %s ¥á±¼¤F~",d.name,cuser.userid);
      pressanykey(buf);
      d.death=2;
      pipdie("[1;31m³Q¬½¤ß¥á±ó:~~[0m",2);
      return 0;
}


int
pip_system_service()
{
     int pipkey;
     int oldchoice;
     char buf[200];
     char oldname[21];
     time_t now;     

     move(b_lines, 0);
     clrtoeol();
     move(b_lines,0);
     prints("[1;44m  ªA°È¶µ¥Ø  [46m[1]©R¦W¤j®v [2]ÅÜ©Ê¤â³N [3]µ²§½³]§½                                [0m");
     pipkey=egetch();
     
     switch(pipkey)
     {
     case '1':
       move(b_lines-1,0);
       clrtobot();
#ifdef MAPLE
       getdata(b_lines-1, 1, "À°¤pÂû­«·s¨ú­Ó¦n¦W¦r¡G", buf, 11, DOECHO,NULL);
#else
       getdata(b_lines-1, 1, "À°¤pÂû­«·s¨ú­Ó¦n¦W¦r¡G", buf, 11, DOECHO,YEA);
#endif  // END MAPLE
       if(!buf[0])
       {
         pressanykey("µ¥¤@¤U·Q¦n¦A¨Ó¦n¤F  :)");
         break;
       }
       else
       {
        strcpy(oldname,d.name);
        strcpy(d.name,buf);
        /*§ï¦W°O¿ý*/
        now=time(0);
        sprintf(buf, "[1;37m%s %-11s§â¤pÂû [%s] §ï¦W¦¨ [%s] [0m\n", Cdate(&now), cuser.userid,oldname,d.name);
        pip_log_record(buf);
        pressanykey("¶â¶â  ´«¤@­Ó·sªº¦W¦r³á...");
       }
       break;
       
     case '2':  /*ÅÜ©Ê*/
       move(b_lines-1,0);
       clrtobot();
       /*1:¤½ 2:¥À */
       if(d.sex==1)
       { 
         oldchoice=2; /*¤½-->¥À*/
         move(b_lines-1, 0);
         prints("[1;33m±N¤pÂû¥Ñ[32m¡ñ[33mÅÜ©Ê¦¨[35m¡ð[33mªº¶Ü¡H [37m[y/N][0m");
       }
       else
       { 
         oldchoice=1; /*¥À-->¤½*/
         move(b_lines-1, 0); 
         prints("[1;33m±N¤pÂû¥Ñ[35m¡ð[33mÅÜ©Ê¦¨[35m¡ñ[33mªº¶Ü¡H [37m[y/N][0m");
       }
       move(b_lines,0);
       prints("[1;44m  ªA°È¶µ¥Ø  [46m[1]©R¦W¤j®v [2]ÅÜ©Ê¤â³N [3]µ²§½³]§½                                [0m");
       pipkey=egetch();
       if(pipkey=='Y' || pipkey=='y')
       {
         /*§ï¦W°O¿ý*/
         now=time(0);
         if(d.sex==1)
           sprintf(buf,"[1;37m%s %-11s§â¤pÂû [%s] ¥Ñ¡ñÅÜ©Ê¦¨¡ð¤F[0m\n",Cdate(&now), cuser.userid,d.name);
         else
           sprintf(buf,"[1;37m%s %-11s§â¤pÂû [%s] ¥Ñ¡ðÅÜ©Ê¦¨¡ñ¤F[0m\n",Cdate(&now), cuser.userid,d.name);           
         pip_log_record(buf);
         pressanykey("ÅÜ©Ê¤â³N§¹²¦...");       
         d.sex=oldchoice;
       }  
       break;
       
     case '3':
       move(b_lines-1,0);
       clrtobot();
       /*1:¤£­n¥B¥¼±B 4:­n¥B¥¼±B */
       oldchoice=d.wantend;
       if(d.wantend==1 || d.wantend==2 || d.wantend==3)
       { 
         oldchoice+=3; /*¨S¦³-->¦³*/
         move(b_lines-1, 0); 
         prints("[1;33m±N¤pÂû¹CÀ¸§ï¦¨[32m[¦³20·³µ²§½][33m? [37m[y/N][0m");
	 sprintf(buf,"¤pÂû¹CÀ¸³]©w¦¨[¦³20·³µ²§½]..");         
       }
       else
       { 
         oldchoice-=3; /*¦³-->¨S¦³*/
         move(b_lines-1, 0); 
         prints("[1;33m±N¤pÂû¹CÀ¸§ï¦¨[32m[¨S¦³20·³µ²§½][33m? [37m[y/N][0m");
         sprintf(buf,"¤pÂû¹CÀ¸³]©w¦¨[¨S¦³20·³µ²§½]..");
       }
       move(b_lines,0);
       prints("[1;44m  ªA°È¶µ¥Ø  [46m[1]©R¦W¤j®v [2]ÅÜ©Ê¤â³N [3]µ²§½³]§½                                [0m");
       pipkey=egetch();
       if(pipkey=='Y' || pipkey=='y')
       {
         d.wantend=oldchoice;
         pressanykey(buf);
       }  
       break;     
     } 
     return 0;
}

int
pip_data_list()  /*¬Ý¤pÂû­Ó¤H¸Ô²Ó¸ê®Æ*/
{
  char buf[256];
  char inbuf1[20];
  char inbuf2[20];
  int tm;
  int pipkey;
  int page=1;
  
  tm=(time(0)-start_time+d.bbtime)/60/30;

  clear();  
  move(1,0);
  prints("       [1;33mùÝùùùùùùùûùúùùùùùùùûùÝùùùùùùùßùúùùùùùùùû[m\n");
  prints("       [0;37mùøùúùû  ùøùø ùù   ùøùãùßùÝùùùåùø ùù   ùø[m\n");
  prints("       [1;37mùøùüùý  ùøùøùÝùß  ùø  ùøùø    ùøùÝùß  ùø[m\n");
  prints("       [1;34mùãùùùùùùùýùãùåùãùùùå  ùãùå    ùãùåùãùùùå[32m......................[m");
  do
  { clrchyiuan(5,23);
    switch(page)
    {
     case 1:
       move(5,0);
       sprintf(buf,
       "[1;31m ¢~¢t[41;37m °ò¥»¸ê®Æ [0;1;31m¢u¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢¡[m\n");  
       prints(buf);
  
       sprintf(buf,
       "[1;31m ¢x[33m¡Ì©m    ¦W :[37m %-10s [33m¡Ì¥Í    ¤é :[37m %02d/%02d/%02d   [33m¡Ì¦~    ¬ö :[37m %-2d         [31m¢x[m\n",
       d.name,d.year,d.month,d.day,tm);
       prints(buf);  
  
       sprintf(inbuf1,"%d/%d",d.hp,d.maxhp);  
       sprintf(inbuf2,"%d/%d",d.mp,d.maxmp);  
       sprintf(buf,
       "[1;31m ¢x[33m¡ÌÅé    ­« :[37m %-5d(¦Ì§J)[33m¡ÌÅé    ¤O :[37m %-11s[33m¡Ìªk    ¤O :[37m %-11s[31m¢x[m\n",
       d.weight,inbuf1,inbuf2);
       prints(buf);  
  
       sprintf(buf,
       "[1;31m ¢x[33m¡Ì¯h    ³Ò :[37m %-3d        [33m¡Ì¯f    ®ð :[37m %-3d        [33m¡ÌÅ¼    Å¼ :[37m %-3d        [31m¢x[m\n",
       d.tired,d.sick,d.shit);
       prints(buf);  
   
       sprintf(buf,  
       "[1;31m ¢x[33m¡ÌµÃ    ¤O :[37m %-7d    [33m¡Ì¿Ë¤lÃö«Y :[37m %-7d    [33m¡Ìª÷    ¿ú :[37m %-11d[31m¢x[m\n",
       d.wrist,d.relation,d.money);
       prints(buf);  
  
       sprintf(buf,  
       "[1;31m ¢u¢t[41;37m ¯à¤O¸ê®Æ [0;1;31m¢u¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢t[m\n");
       prints(buf);  
   
       sprintf(buf,   
       "[1;31m ¢x[33m¡Ì®ð    ½è :[37m %-10d [33m¡Ì´¼    ¤O :[37m %-10d [33m¡Ì·R    ¤ß :[37m %-10d [31m¢x[m\n",
       d.character,d.wisdom,d.love);
       prints(buf);  
   
       sprintf(buf, 
       "[1;31m ¢x[33m¡ÌÃÀ    ³N :[37m %-10d [33m¡Ì¹D    ¼w :[37m %-10d [33m¡Ì®a    ¨Æ :[37m %-10d [31m¢x[m\n",
       d.art,d.etchics,d.homework);
       prints(buf);  
 
       sprintf(buf, 
       "[1;31m ¢x[33m¡ÌÂ§    »ö :[37m %-10d [33m¡ÌÀ³    ¹ï :[37m %-10d [33m¡Ì²i    ¶¹ :[37m %-10d [31m¢x[m\n",
       d.manners,d.speech,d.cookskill);
       prints(buf);    
 
       sprintf(buf,  
       "[1;31m ¢u¢t[41;37m ª¬ºA¸ê®Æ [0;1;31m¢u¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢t[m\n");
       prints(buf);  
 
       sprintf(buf, 
       "[1;31m ¢x[33m¡Ì§Ö    ¼Ö :[37m %-10d [33m¡Ìº¡    ·N :[37m %-10d [33m¡Ì¤H    »Ú :[37m %-10d [31m¢x[m\n",
       d.happy,d.satisfy,d.toman);
       prints(buf);
  
       sprintf(buf, 
       "[1;31m ¢x[33m¡Ì¾y    ¤O :[37m %-10d [33m¡Ì«i    ´± :[37m %-10d [33m¡Ì«H    ¥õ :[37m %-10d [31m¢x[m\n",
       d.charm,d.brave,d.belief);
       prints(buf);  

       sprintf(buf, 
       "[1;31m ¢x[33m¡Ì¸o    Ä^ :[37m %-10d [33m¡Ì·P    ¨ü :[37m %-10d [33m            [37m            [31m¢x[m\n",
       d.offense,d.affect);
       prints(buf);  

       sprintf(buf, 
       "[1;31m ¢u¢t[41;37m µû»ù¸ê®Æ [0;1;31m¢u¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢t[m\n");
       prints(buf);  

       sprintf(buf, 
       "[1;31m ¢x[33m¡ÌªÀ¥æµû»ù :[37m %-10d [33m¡Ì¾Ô°«µû»ù :[37m %-10d [33m¡ÌÅ]ªkµû»ù :[37m %-10d [31m¢x[m\n",
       d.social,d.hexp,d.mexp);
       prints(buf);  

       sprintf(buf, 
       "[1;31m ¢x[33m¡Ì®a¨Æµû»ù :[37m %-10d [33m            [37m            [33m            [37m            [31m¢x[m\n",
       d.family);
       prints(buf);  
  
       sprintf(buf, 
       "[1;31m ¢¢¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢£[m\n");
       prints(buf);  
       
       move(b_lines-1,0);       
       sprintf(buf, 
       "                                                              [1;36m²Ä¤@­¶[37m/[36m¦@¤G­¶[m\n");
       prints(buf);  
       break;

     case 2:
       move(5,0);
       sprintf(buf, 
       "[1;31m ¢~¢t[41;37m ª««~¸ê®Æ [0;1;31m¢u¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢¡[m\n");
       prints(buf);  
  
       sprintf(buf, 
       "[1;31m ¢x[33m¡Ì­¹    ª« :[37m %-10d [33m¡Ì¹s    ­¹ :[37m %-10d [33m¡Ì¤j ¸É ¤Y :[37m %-10d [31m¢x[m\n",
       d.food,d.cookie,d.bighp);
       prints(buf);  
  
       sprintf(buf, 
       "[1;31m ¢x[33m¡ÌÃÄ    ¯ó :[37m %-10d [33m¡Ì®Ñ    ¥» :[37m %-10d [33m¡Ìª±    ¨ã :[37m %-10d [31m¢x[m\n",
       d.medicine,d.book,d.playtool);
       prints(buf);  
  
       sprintf(buf, 
       "[1;31m ¢u¢t[41;37m ¹CÀ¸¸ê®Æ [0;1;31m¢u¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢t[m\n");
       prints(buf);  
  
       sprintf(buf, 
       "[1;31m ¢x[33m¡Ì²q ®± Ä¹ :[37m %-10d [33m¡Ì²q ®± ¿é :[37m %-10d                         [31m¢x[m\n",
       d.winn,d.losee);
       prints(buf);  
  
       sprintf(buf, 
       "[1;31m ¢u¢t[41;37m ªZ¤O¸ê®Æ [0;1;31m¢u¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢t[m\n");
       prints(buf);  
  
       sprintf(buf, 
       "[1;31m ¢x[33m¡Ì§ð À» ¤O :[37m %-10d [33m¡Ì¨¾ ¿m ¤O :[37m %-10d [33m¡Ì³t «× ­È :[37m %-10d [31m¢x[m\n",
       d.attack,d.resist,d.speed);
       prints(buf);  
       sprintf(buf, 
       "[1;31m ¢x[33m¡Ì§ÜÅ]¯à¤O :[37m %-10d [33m¡Ì¾Ô°«§Þ³N :[37m %-10d [33m¡ÌÅ]ªk§Þ³N :[37m %-10d [31m¢x[m\n",
       d.mresist,d.hskill,d.mskill);
       prints(buf);  
  
       sprintf(buf, 
       "[1;31m ¢x[33m¡ÌÀY³¡¸Ë³Æ :[37m %-10s [33m¡Ì¥k¤â¸Ë³Æ :[37m %-10s [33m¡Ì¥ª¤â¸Ë³Æ :[37m %-10s [31m¢x[m\n",
       weaponhead[d.weaponhead],weaponrhand[d.weaponrhand],weaponlhand[d.weaponlhand]);
       prints(buf);  
  
       sprintf(buf, 
       "[1;31m ¢x[33m¡Ì¨­Åé¸Ë³Æ :[37m %-10s [33m¡Ì¸}³¡¸Ë³Æ :[37m %-10s [33m            [37m            [31m¢x[m\n",
       weaponbody[d.weaponbody],weaponfoot[d.weaponfoot]);
       prints(buf);  
  
       sprintf(buf, 
       "[1;31m ¢¢¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢£[m\n");
       prints(buf); 

       move(b_lines-1,0);
       sprintf(buf, 
       "                                                              [1;36m²Ä¤G­¶[37m/[36m¦@¤G­¶[m\n");
       prints(buf);          
       break;
    }
    move(b_lines,0);
    sprintf(buf,"[1;44;37m  ¸ê®Æ¿ï³æ  [46m  [¡ô/PAGE UP]©¹¤W¤@­¶ [¡õ/PAGE DOWN]©¹¤U¤@­¶ [Q]Â÷¶}:            [m");
    prints(buf);    
    pipkey=egetch();
    switch(pipkey)
    {
      case KEY_UP:
      case KEY_PGUP:
      case KEY_DOWN:
      case KEY_PGDN:
        if(page==1)
           page=2;
        else if(page==2)
           page=1;
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
