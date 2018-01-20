/*---------------------------------------------------------------------------*/
/* µ²§½¨ç¦¡                                                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
#include <time.h>
#include "bbs.h"
#include "pip.h"
extern struct chicken d;
extern time_t start_time;
extern time_t lasttime;
#define getdata(a, b, c , d, e, f, g) getdata(a,b,c,d,e,f,NULL,g)

/*--------------------------------------------------------------------------*/
/*  µ²§½°Ñ¼Æ³]©w                                                            */
/*--------------------------------------------------------------------------*/
struct newendingset
{
  char *girl;		/*¤k¥Íµ²§½ªºÂ¾·~*/ 
  char *boy;		/*¨k¥Íµ²§½ªºÂ¾·~*/
  int grade;		/*µû¤À*/
};
typedef struct newendingset newendingset;

/*¸U¯à*/
struct newendingset endmodeall_purpose[] = {
"¤k©ÊÂ¾·~",		"¨k¥ÍÂ¾·~",		0,
"¦¨¬°³o­Ó°ê®a·s¤k¤ý",	"¦¨¬°³o­Ó°ê®a·s°ê¤ý",	500,
"¦¨¬°°ê®aªº®_¬Û",	"¦¨¬°°ê®aªº®_¬Û",	400,
"¦¨¬°±Ð·|¤¤ªº¤j¥D±Ð",	"¦¨¬°±Ð·|¤¤ªº¤j¥D±Ð",	350,
"¦¨¬°°ê®aªº¤j¦Ú",	"¦¨¬°°ê®aªº¤j¦Ú",	320,
"¦¨¬°¤@¦ì³Õ¤h",		"¦¨¬°¤@¦ì³Õ¤h",		300,
"¦¨¬°±Ð·|¤¤ªº­×¤k",	"¦¨¬°±Ð·|¤¤ªº¯«¤÷",	150,
"¦¨¬°ªk®x¤Wªº¤jªk©x",   "¦¨¬°ªk®x¤Wªºªk©x",	200,
"¦¨¬°ª¾¦Wªº¾ÇªÌ",	"¦¨¬°ª¾¦Wªº¾ÇªÌ",	120,
"¦¨¬°¤@¦W¤k©x",		"¦¨¬°¤@¦W¨k©x",		100,
"¦b¨|¥®°|¤u§@",		"¦b¨|¥®°|¤u§@",		100,
"¦b®ÈÀ]¤u§@",		"¦b®ÈÀ]¤u§@",		100,
"¦b¹A³õ¤u§@",		"¦b¹A³õ¤u§@",		100,
"¦bÀ\\ÆU¤u§@",		"¦bÀ\\ÆU¤u§@",		100,
"¦b±Ð°ó¤u§@",		"¦b±Ð°ó¤u§@",		100,
"¦b¦aÅu¤u§@",		"¦b¦aÅu¤u§@",		100,
"¦b¥ï¤ì³õ¤u§@",		"¦b¥ï¤ì³õ¤u§@",		100,
"¦b¬ü®e°|¤u§@",		"¦b¬ü®e°|¤u§@",		100,
"¦b¬¼Ây°Ï¤u§@",		"¦b¬¼Ây°Ï¤u§@",		100,
"¦b¤u¦a¤u§@",		"¦b¤u¦a¤u§@",		100,
"¦b¹Ó¶é¤u§@",		"¦b¹Ó¶é¤u§@",		100,
"¾á¥ô®a®x±Ð®v¤u§@",	"¾á¥ô®a®x±Ð®v¤u§@",	100,
"¦b°s®a¤u§@",		"¦b°s®a¤u§@",		100,
"¦b°s©±¤u§@",		"¦b°s©±¤u§@",		100,
"¦b¤j©]Á`·|¤u§@",	"¦b¤j©]Á`·|¤u§@",	100,
"¦b®a¤¤À°¦£",		"¦b®a¤¤À°¦£",		50,
"¦b¨|¥®°|­Ý®t",		"¦b¨|¥®°|­Ý®t",		50,
"¦b®ÈÀ]­Ý®t",		"¦b®ÈÀ]­Ý®t",		50,
"¦b¹A³õ­Ý®t",		"¦b¹A³õ­Ý®t",		50,
"¦bÀ\\ÆU­Ý®t",		"¦bÀ\\ÆU­Ý®t",		50,
"¦b±Ð°ó­Ý®t",		"¦b±Ð°ó­Ý®t",		50,
"¦b¦aÅu­Ý®t",		"¦b¦aÅu­Ý®t",		50,
"¦b¥ï¤ì³õ­Ý®t",		"¦b¥ï¤ì³õ­Ý®t",		50,
"¦b¬ü®e°|­Ý®t",		"¦b¬ü®e°|­Ý®t",		50,
"¦b¬¼Ây°Ï­Ý®t",		"¦b¬¼Ây°Ï­Ý®t",		50,
"¦b¤u¦a­Ý®t",		"¦b¤u¦a­Ý®t",		50,
"¦b¹Ó¶é­Ý®t",		"¦b¹Ó¶é­Ý®t",		50,
"¾á¥ô®a®x±Ð®v­Ý®t",	"¾á¥ô®a®x±Ð®v­Ý®t",	50,
"¦b°s®a­Ý®t",		"¦b°s®a­Ý®t",		50,
"¦b°s©±­Ý®t",		"¦b°s©±­Ý®t",		50,
"¦b¤j©]Á`·|­Ý®t",	"¦b¤j©]Á`·|­Ý®t",	50,
NULL,		NULL,	0
};

/*¾Ô°«*/
struct newendingset endmodecombat[] = {
"¤k©ÊÂ¾·~",		"¨k¥ÍÂ¾·~",			0,
"³Q«Ê¬°«iªÌ ¾Ô¤h«¬",  	"³Q«Ê¬°«iªÌ ¾Ô¤h«¬",		420,
"³Q©ÞÀÂ¦¨¬°¤@°êªº±N­x",	"³Q©ÞÀÂ¦¨¬°¤@°êªº±N­x",		300,
"·í¤W¤F°ê®aªñ½Ã¶¤¶¤ªø",	"·í¤W¤F°ê®aªñ½Ã¶¤¶¤ªø",		200,
"·í¤FªZ³N¦Ñ®v",		"·í¤FªZ³N¦Ñ®v",			150,
"ÅÜ¦¨ÃM¤h³ø®Ä°ê®a",	"ÅÜ¦¨ÃM¤h³ø®Ä°ê®a",		160,
"§ë¨­­x®È¥Í¬¡¡A¦¨¬°¤h§L","§ë¨­­x®È¥Í¬¡¡A¦¨¬°¤h§L",	80,
"ÅÜ¦¨¼úª÷Ây¤H",		"ÅÜ¦¨¼úª÷Ây¤H",			0,
"¥H¶Ä§L¤u§@ºû¥Í",	"¥H¶Ä§L¤u§@ºû¥Í",		0,
NULL,           NULL,   0
};

/*Å]ªk*/
struct newendingset endmodemagic[] = {
"¤k©ÊÂ¾·~",	     	"¨k¥ÍÂ¾·~",		0,
"³Q«Ê¬°«iªÌ Å]ªk«¬",	"³Q«Ê¬°«iªÌ Å]ªk«¬",	420,
"³Q¸u¬°¤ý®cÅ]ªk®v",	"³Q¸u¬°¤ý©xÅ]ªk®v",	280,
"·í¤FÅ]ªk¦Ñ®v",		"·í¤FÅ]ªk¦Ñ®v",		160,
"ÅÜ¦¨¤@¦ìÅ]¾É¤h",	"ÅÜ¦¨¤@¦ìÅ]¾É¤h",	180,
"·í¤FÅ]ªk®v",		"·í¤FÅ]ªk®v",		120,
"¥H¥e¤R®vÀ°¤Hºâ©R¬°¥Í",	"¥H¥e¤R®vÀ°¤Hºâ©R¬°¥Í",	40,
"¦¨¬°¤@­ÓÅ]³N®v",	"¦¨¬°¤@­ÓÅ]³N®v",	20,
"¦¨¬°µóÀYÃÀ¤H",		"¦¨¬°µóÀYÃÀ¤H",		10,
NULL,           NULL	,0
};

/*ªÀ¥æ*/
struct newendingset endmodesocial[] = {
"¤k©ÊÂ¾·~",     	"¨k¥ÍÂ¾·~",		0,
"¦¨¬°°ê¤ýªºÃd¦m",	"¦¨¬°¤k¤ýªº¾t°¨·Ý",	170,
"³Q¬D¿ï¦¨¬°¤ý¦m",	"³Q¿ï¤¤·í¤k¤ýªº¤Ò´B",	260,
"³Q§BÀï¬Ý¤¤¡A¦¨¬°¤Ò¤H",	"¦¨¬°¤F¤k§BÀïªº¤Ò´B",	130,
"¦¨¬°´I»¨ªº©d¤l",	"¦¨¬°¤k´I»¨ªº¤Ò´B",	100,
"¦¨¬°°Ó¤Hªº©d¤l",	"¦¨¬°¤k°Ó¤Hªº¤Ò´B",	80,
"¦¨¬°¹A¤Hªº©d¤l",	"¦¨¬°¤k¹A¤Hªº¤Ò´B",	80,
"¦¨¬°¦a¥Dªº±¡°ü",	"¦¨¬°¤k¦a¥Dªº±¡¤Ò",	-40,
NULL,           NULL,	0
};
/*ÃÀ³N*/
struct newendingset endmodeart[] = {
"¤k©ÊÂ¾·~",		"¨k¥ÍÂ¾·~",	0,
"¦¨¬°¤F¤p¤¡",		"¦¨¬°¤F¤p¤¡",	100,
"¦¨¬°¤F§@®a",		"¦¨¬°¤F§@®a",	100,
"¦¨¬°¤Fµe®a",		"¦¨¬°¤Fµe®a",	100,
"¦¨¬°¤F»RÁÐ®a",		"¦¨¬°¤F»RÁÐ®a",	100,
NULL,           NULL,	0
};

/*·t¶Â*/
struct newendingset endmodeblack[] = {
"¤k©ÊÂ¾·~",     	"¨k¥ÍÂ¾·~",		0,
"ÅÜ¦¨¤FÅ]¤ý",		"ÅÜ¦¨¤FÅ]¤ý",		-1000,
"²V¦¨¤F¤Ó©f",		"²V¦¨¤F¬yª]",		-350,
"°µ¤F[¢á¢Û¤k¤ý]ªº¤u§@",	"°µ¤F[¢á¢Û°ê¤ý]ªº¤u§@",	-150,
"·í¤F¶Âµóªº¤j©j",	"·í¤F¶Âµóªº¦Ñ¤j",	-500,
"ÅÜ¦¨°ª¯Å±@°ü",		"ÅÜ¦¨°ª¯Å±¡¤Ò",		-350,
"ÅÜ¦¨¶B´Û®v¶B´Û§O¤H",	"ÅÜ¦¨ª÷¥úÄÒÄF§O¤H¿ú",	-350,
"¥H¬yÅaªº¤u§@¥Í¬¡",	"¥H¤û­¦ªº¤u§@¥Í¬¡",	-350,
NULL,		NULL,	0
};

/*®a¨Æ*/
struct newendingset endmodefamily[] = {
"¤k©ÊÂ¾·~",     	"¨k¥ÍÂ¾·~",		0,
"¥¿¦b·s®Q­×¦æ",		"¥¿¦b·s­¦­×¦æ",		50,
NULL,		NULL,	0
};


int /*µ²§½µe­±*/
pip_ending_screen()
{
  time_t now;
  char buf[256];
  char endbuf1[50];
  char endbuf2[50];
  char endbuf3[50];
  int endgrade=0;
  int endmode=0;
  clear();
  pip_ending_decide(endbuf1,endbuf2,endbuf3,&endmode,&endgrade);
  move(1,9); 
  prints("[1;33mùÝùùùùùùùßùÝùùùùùûùßùÝùùùùùùùûùÝùùùùùùùßùÝùùùùùûùßùúùùùùùùùû[0m");
  move(2,9);
  prints("[1;37mùø      ùøùø    ùøùøùø      ùøùø      ùøùø    ùøùøùø      ùø[0m");
  move(3,9);
  prints("[0;37mùø    ùùùâùø    ùøùøùø  ùúùûùøùãùùùßùÝùåùø    ùøùøùø  ùÝùùùß[0m");
  move(4,9);
  prints("[0;37mùø    ùùùâùø  ùø  ùøùø  ùüùýùøùÝùùùåùãùßùø  ùø  ùøùø  ùüùýùø[0m");
  move(5,9);
  prints("[1;37mùø      ùøùø  ùø  ùøùø      ùøùø      ùøùø  ùø  ùøùø      ùø[0m");
  move(6,9);
  prints("[1;35mùãùùùùùùùåùãùùùüùùùåùãùùùùùùùýùãùùùùùùùåùãùùùüùùùåùüùùùùùùùý[0m");
  move(7,8);
  prints("[1;31m¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w[41;37m ¬PªÅ¾Ô°«Âûµ²§½³ø§i [0;1;31m¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w[0m");
  move(9,10);
  prints("[1;36m³o­Ó®É¶¡¤£ª¾¤£Ä±¦aÁÙ¬O¨ìÁ{¤F...[0m");
  move(11,10);
  prints("[1;37m[33m%s[37m ±oÂ÷¶}§Aªº·Å·xÃh©ê¡A¦Û¤v¤@°¦Âû¦b¥~­±¨D¥Í¦s¤F.....[0m",d.name);
  move(13,10);
  prints("[1;36m¦b§A·ÓÅU±Ð¾É¥Lªº³o¬q®É¥ú¡AÅý¥L±µÄ²¤F«Ü¦h»â°ì¡A°ö¾i¤F«Ü¦hªº¯à¤O....[0m");
  move(15,10);
  prints("[1;37m¦]¬°³o¨Ç¡AÅý¤pÂû [33m%s[37m ¤§«áªº¥Í¬¡¡AÅÜ±o§ó¦hªö¦h«º¤F........[0m",d.name);
  move(17,10);
  prints("[1;36m¹ï©ó§AªºÃö¤ß¡A§Aªº¥I¥X¡A§A©Ò¦³ªº·R......[0m");
  move(19,10);
  prints("[1;37m[33m%s[37m ·|¥Ã»·³£»Ê°O¦b¤ßªº....[0m",d.name);
  pressanykey("±µ¤U¨Ó¬Ý¥¼¨Óµo®i");
  clrchyiuan(7,19);
  move(7,8);
  prints("[1;34m¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w[44;37m ¬PªÅ¾Ô°«Âû¥¼¨Óµo®i [0;1;34m¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w[0m");
  move(9,10);
  prints("[1;36m³z¹L¤ô´¹²y¡AÅý§Ú­Ì¤@°_¨Ó¬Ý [33m%s[36m ªº¥¼¨Óµo®i§a.....[0m",d.name);
  move(11,10);
  prints("[1;37m¤pÂû [33m%s[37m «á¨Ó%s....[0m",d.name,endbuf1);
  move(13,10);
  prints("[1;36m¦]¬°¥Lªº¤§«eªº§V¤O¡A¨Ï±o¥L¦b³o¤@¤è­±%s....[0m",endbuf2);
  move(15,10);
  prints("[1;37m¦Ü©ó¤pÂûªº±B«Ãª¬ªp¡A¥L«á¨Ó%s¡A±B«Ãºâ¬O«Ü¬üº¡.....[0m",endbuf3);
  move(17,10);
  prints("[1;36m¶â..³o¬O¤@­Ó¤£¿ùªºµ²§½­ò..........[0m");
  pressanykey("§Ú·Q  §A¤@©w«Ü·P°Ê§a.....");
  show_ending_pic(0);
  pressanykey("¬Ý¤@¬Ý¤À¼ÆÅo");
  endgrade=pip_game_over(endgrade);
  pressanykey("¤U¤@­¶¬O¤pÂû¸ê®Æ  »°§Öcopy¤U¨Ó°µ¬ö©À");
  pip_data_list();
  pressanykey("Åwªï¦A¨Ó¬D¾Ô....");
  /*°O¿ý¶}©l*/
  now=time(0);
  sprintf(buf, "[1;35m¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w[0m\n");
  pip_log_record(buf);
  sprintf(buf, "[1;37m¦b [33m%s [37mªº®É­Ô¡A[36m%s [37mªº¤pÂû [32m%s[37m ¥X²{¤Fµ²§½[0m\n", Cdate(&now), cuser.userid,d.name);
  pip_log_record(buf);
  sprintf(buf, "[1;37m¤pÂû [32m%s [37m§V¤O¥[±j¦Û¤v¡A«á¨Ó%s[0m\n[1;37m¦]¬°¤§«eªº§V¤O¡A¨Ï±o¦b³o¤@¤è­±%s[0m\n",d.name,endbuf1,endbuf2);
  pip_log_record(buf);
  sprintf(buf, "[1;37m¦Ü©ó±B«Ãª¬ªp¡A¥L«á¨Ó%s¡A±B«Ãºâ¬O«Ü¬üº¡.....[0m\n\n[1;37m¤pÂû [32n%s[37m ªºÁ`¿n¤À¡× [33m%d[0m\n",endbuf3,d.name,endgrade);
  pip_log_record(buf);
  sprintf(buf, "[1;35m¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w[0m\n");
  pip_log_record(buf);  
  /*°O¿ý²×¤î*/
  d.death=3;
  pipdie("[1;31m¹CÀ¸µ²§ôÅo...[m  ",3);
  return 0;
}

int 
pip_ending_decide(endbuf1,endbuf2,endbuf3,endmode,endgrade)
char *endbuf1,*endbuf2,*endbuf3;
int *endmode,*endgrade;
{
  char *name[8][2]={{"¨kªº","¤kªº"},
  	           {"¶ùµ¹¤ý¤l","°ù¤F¤½¥D"},
  	           {"¶ùµ¹§A","°ù¤F§A"},
                   {"¶ùµ¹°Ó¤H¢Ï","°ù¤F¤k°Ó¤H¢Ï"},
                   {"¶ùµ¹°Ó¤H¢Ð","°ù¤F¤k°Ó¤H¢Ð"},
                   {"¶ùµ¹°Ó¤H¢Ñ","°ù¤F¤k°Ó¤H¢Ñ"},
                   {"¶ùµ¹°Ó¤H¢Ò","°ù¤F¤k°Ó¤H¢Ò"},
                   {"¶ùµ¹°Ó¤H¢Ó","°ù¤F¤k°Ó¤H¢Ó"}}; 
  int m=0,n=0,grade=0;
  int modeall_purpose=0;
  char buf1[256];
  char buf2[256];
  
  *endmode=pip_future_decide(&modeall_purpose);
  switch(*endmode)
  {
  /*1:·t¶Â 2:ÃÀ³N 3:¸U¯à 4:¾Ô¤h 5:Å]ªk 6:ªÀ¥æ 7:®a¨Æ*/
    case 1:
      pip_endingblack(buf1,&m,&n,&grade);    
      break;
    case 2:
      pip_endingart(buf1,&m,&n,&grade);
      break;
    case 3:
      pip_endingall_purpose(buf1,&m,&n,&grade,modeall_purpose);
      break;
    case 4:
      pip_endingcombat(buf1,&m,&n,&grade);
      break;
    case 5:
      pip_endingmagic(buf1,&m,&n,&grade);
      break;
    case 6:
      pip_endingsocial(buf1,&m,&n,&grade);
      break;
    case 7:
      pip_endingfamily(buf1,&m,&n,&grade);
      break;
  }
  
  grade+=pip_marry_decide();
  strcpy(endbuf1, buf1);  
  if(n==1)
  {
    *endgrade=grade+300;
    sprintf(buf2,"«D±`ªº¶¶§Q..");
  }
  else if(n==2)
  {
    *endgrade=grade+100;
    sprintf(buf2,"ªí²{ÁÙ¤£¿ù..");
  }
  else if(n==3)
  {
    *endgrade=grade-10;
    sprintf(buf2,"±`¹J¨ì«Ü¦h°ÝÃD....");
  }  
  strcpy(endbuf2, buf2);  
  if(d.lover>=1 && d.lover <=7)
  {
    if(d.sex==1)
      sprintf(buf2,"%s",name[d.lover][1]);
    else
      sprintf(buf2,"%s",name[d.lover][0]);
  }
  else if(d.lover==10)
    sprintf(buf2,"%s",buf1);
  else if(d.lover==0)
  {
    if(d.sex==1)
      sprintf(buf2,"°ù¤F¦P¦æªº¤k«Ä");
    else
      sprintf(buf2,"¶ùµ¹¤F¦P¦æªº¨k¥Í");  
  } 
  strcpy(endbuf3, buf2);  
  return 0;
}
/*µ²§½§PÂ_*/
/*1:·t¶Â 2:ÃÀ³N 3:¸U¯à 4:¾Ô¤h 5:Å]ªk 6:ªÀ¥æ 7:®a¨Æ*/
int
pip_future_decide(modeall_purpose)
int *modeall_purpose;
{
  int endmode;
  /*·t¶Â*/
  if((d.etchics==0 && d.offense >=100) || (d.etchics>0 && d.etchics<50 && d.offense >=250))
     endmode=1;
  /*ÃÀ³N*/
  else if(d.art>d.hexp && d.art>d.mexp && d.art>d.hskill && d.art>d.mskill &&
          d.art>d.social && d.art>d.family && d.art>d.homework && d.art>d.wisdom &&
          d.art>d.charm && d.art>d.belief && d.art>d.manners && d.art>d.speech &&
          d.art>d.cookskill && d.art>d.love)
     endmode=2;
  /*¾Ô°«*/
  else if(d.hexp>=d.social && d.hexp>=d.mexp && d.hexp>=d.family)
  {
     *modeall_purpose=1;
     if(d.hexp>d.social+50 || d.hexp>d.mexp+50 || d.hexp>d.family+50)
        endmode=4;
     else
        endmode=3;     
  }
  /*Å]ªk*/
  else if(d.mexp>=d.hexp && d.mexp>=d.social && d.mexp>=d.family)
  {  
     *modeall_purpose=2;
     if(d.mexp>d.hexp || d.mexp>d.social || d.mexp>d.family)
        endmode=5;
     else
        endmode=3;
  }   
  else if(d.social>=d.hexp && d.social>=d.mexp && d.social>=d.family)
  {
     *modeall_purpose=3;
     if(d.social>d.hexp+50 || d.social>d.mexp+50 || d.social>d.family+50)
        endmode=6;
     else
        endmode=3;
  }

  else 
  {  
     *modeall_purpose=4;
     if(d.family>d.hexp+50 || d.family>d.mexp+50 || d.family>d.social+50)
        endmode=7;
     else
        endmode=3;     
  }     
  return endmode;
}
/*µ²±Bªº§PÂ_*/
int
pip_marry_decide()
{
  int grade;
  if(d.lover!=0)
  {  
     /* 3 4 5 6 7:°Ó¤H */
     d.lover=d.lover;
     grade=80;
  }
  else
  {
     if(d.royalJ>=d.relation && d.royalJ>=100)
     {
        d.lover=1;  /*¤ý¤l*/
        grade=200;
     }
     else if(d.relation>d.royalJ && d.relation>=100)
     {
        d.lover=2;  /*¤÷¿Ë©Î¥À¿Ë*/
        grade=0;
     }
     else
     {
        d.lover=0;
        grade=40;
     }
  }
  return grade;
}


int
pip_endingblack(buf,m,n,grade) /*·t¶Â*/
char *buf;
int *m,*n,*grade;
{
 if(d.offense>=500 && d.mexp>=500) /*Å]¤ý*/
 {
   *m=1;
   if(d.mexp>=1000)
     *n=1;
   else if(d.mexp<1000 && d.mexp >=800)
     *n=2;
   else
     *n=3;
 }

else if(d.hexp>=600)  /*¬yª]*/
 {
   *m=2;
   if(d.wisdom>=350)
     *n=1;
   else if(d.wisdom<350 && d.wisdom>=300)
     *n=2;
   else 
     *n=3;  
 } 
 else if(d.speech>=100 && d.art>=80) /*SM*/
 {
   *m=3;
   if(d.speech>150 && d.art>=120)
     *n=1;
   else if(d.speech>120 && d.art>=100)
     *n=2;
   else   
     *n=3;
 }
 else if(d.hexp>=320 && d.character>200 && d.charm< 200)	/*¶Âµó¦Ñ¤j*/
 {
   *m=4;
   if(d.hexp>=400)
     *n=1;
   else if(d.hexp<400 && d.hexp>=360)
     *n=2;
   else 
     *n=3;  
 }
 else if(d.character>=200 && d.charm >=200 && d.speech>70 && d.toman >70)  /*°ª¯Å±@°ü*/
 {
   *m=5;
   if(d.charm>=300)
     *n=1;
   else if(d.charm<300 && d.charm>=250)
     *n=2;
   else 
     *n=3;  
 }
 
 else if(d.wisdom>=450)  /*¶BÄF®v*/
 {
   *m=6;
   if(d.wisdom>=550)
     *n=1;
   else if(d.wisdom<550 && d.wisdom>=500)
     *n=2;
   else 
     *n=3;  
 }
 
 else /*¬yÅa*/
 {
   *m=7;
   if(d.charm>=350)
     *n=1;
   else if(d.charm<350 && d.charm>=300)
     *n=2;
   else 
     *n=3;  
 }
 if(d.sex==1)
   strcpy(buf, endmodeblack[*m].boy);
 else
   strcpy(buf, endmodeblack[*m].girl);
 *grade=endmodeblack[*m].grade;
 return 0; 
}


int
pip_endingsocial(buf,m,n,grade) /*ªÀ¥æ*/
char *buf;
int *m,*n,*grade;
{
 int class;
 if(d.social>600) class=1;
 else if(d.social>450) class=2;
 else if(d.social>380) class=3;
 else if(d.social>250) class=4;
 else class=5;

 switch(class)
 {
   case 1:
     if(d.charm>500)
     {
       *m=1;
       d.lover=10;
       if(d.character>=700)
        *n=1;
       else if(d.character<700 && d.character>=500)
        *n=2;
       else   
        *n=3;
     }
     else
     {
       *m=2;
       d.lover=10;
       if(d.character>=700)
        *n=1;
       else if(d.character<700 && d.character>=500)
        *n=2;
       else   
        *n=3;
     }
     break;
     
   case 2:
     *m=1;
     d.lover=10;
     if(d.character>=700)
        *n=1;
     else if(d.character<700 && d.character>=500)
        *n=2;
     else   
        *n=3;   
     break;
     
   case 3:
     if(d.character>=d.charm)
     {
       *m=3;
       d.lover=10;
       if(d.toman>=250)
         *n=1;
       else if(d.toman<250 && d.toman>=200)
         *n=2;
       else   
         *n=3;     
     }
     else
     {
       *m=4;
       d.lover=10;
       if(d.character>=400)
         *n=1;
       else if(d.character<400 && d.character>=300)
         *n=2;
       else   
         *n=3;     
     }
     break;
     
   case 4:
     if(d.wisdom>=d.affect)	
     {
	   *m=5;
	   d.lover=10;
	   if(d.toman>120 && d.cookskill>300 && d.homework>300)
	     *n=1;
	   else if(d.toman<120 && d.cookskill<300 && d.homework<300 &&d.toman>100 && d.cookskill>250 && d.homework>250)
	     *n=2;
	   else   
	     *n=3;     	
     }
     else
     {
	   *m=6;
	   d.lover=10;
	   if(d.hp>=400)
	     *n=1;
	   else if(d.hp<400 && d.hp>=300)
	     *n=2;
	   else   
	     *n=3;     
     }
     break;
   
   case 5:
     *m=7;
     d.lover=10;
     if(d.charm>=200)
       *n=1;
     else if(d.charm<200 && d.charm>=100)
       *n=2;
     else   
       *n=3;
     break;
 }
 if(d.sex==1)
   strcpy(buf, endmodesocial[*m].boy);
 else
   strcpy(buf, endmodesocial[*m].girl);
 *grade=endmodesocial[*m].grade;
 return 0; 
}

int
pip_endingmagic(buf,m,n,grade) /*Å]ªk*/
char *buf;
int *m,*n,*grade;
{
 int class;
 if(d.mexp>800) class=1;
 else if(d.mexp>600) class=2;
 else if(d.mexp>500) class=3;
 else if(d.mexp>300) class=4;
 else class=5;

 switch(class)
 {
    case 1:
      if(d.affect>d.wisdom && d.affect>d.belief && d.etchics>100)
      {
	   *m=1;
	   if(d.etchics>=800)
	     *n=1;
	   else if(d.etchics<800 && d.etchics>=400)
	     *n=2;
	   else   
	     *n=3;      
      }
      else if(d.etchics<50)
      {
	   *m=4;
	   if(d.hp>=400)
	     *n=1;
	   else if(d.hp<400 && d.hp>=200)
	     *n=2;
	   else   
	     *n=3;    
      }
      else
      {
	   *m=2;
	   if(d.wisdom>=800)
	     *n=1;
	   else if(d.wisdom<800 && d.wisdom>=400)
	     *n=2;
	   else   
	     *n=3;      
      }
      break;
      
    case 2:
      if(d.etchics>=50)
      {
	   *m=3;
	   if(d.wisdom>=500)
	     *n=1;
	   else if(d.wisdom<500 && d.wisdom>=200)
	     *n=2;
	   else   
	     *n=3;     
      }
      else
      {
	   *m=4;
	   if(d.hp>=400)
	     *n=1;
	   else if(d.hp<400 && d.hp>=200)
	     *n=2;
	   else   
	     *n=3;          
      }
      break;
    
    case 3:
      *m=5;
      if(d.mskill>=300)
	*n=1;
      else if(d.mskill<300 && d.mskill>=150)
	*n=2;
      else   
	*n=3;
      break;

    case 4:
      *m=6;
      if(d.speech>=150)
	*n=1;
      else if(d.speech<150 && d.speech>=60)
	*n=2;
      else   
	*n=3;
      break; 
     
    case 5:
      if(d.character>=200)
      {
	*m=7;
        if(d.speech>=150)
 	  *n=1;
        else if(d.speech<150 && d.speech>=60)
      	  *n=2;
        else   
	  *n=3;        
      }
      else
      {
        *m=8;
        if(d.speech>=150)
 	  *n=1;
        else if(d.speech<150 && d.speech>=60)
      	  *n=2;
        else   
	  *n=3;      
      }
      break;
    
 }

 if(d.sex==1)
   strcpy(buf, endmodemagic[*m].boy);
 else
   strcpy(buf, endmodemagic[*m].girl); 
 *grade=endmodemagic[*m].grade;
 return 0; 
}

int
pip_endingcombat(buf,m,n,grade) /*¾Ô°«*/
char *buf;
int *m,*n,*grade;
{
 int class;
 if(d.hexp>1500) class=1;
 else if(d.hexp>1000) class=2;
 else if(d.hexp>800) class=3;
 else class=4;

 switch(class)
 {
    case 1:
      if(d.affect>d.wisdom && d.affect>d.belief && d.etchics>100)
      {
	   *m=1;
	   if(d.etchics>=800)
	     *n=1;
	   else if(d.etchics<800 && d.etchics>=400)
	     *n=2;
	   else   
	     *n=3;      
      }
      else if(d.etchics<50)
      {

      }
      else
      {
	   *m=2;
	   if(d.wisdom>=800)
	     *n=1;
	   else if(d.wisdom<800 && d.wisdom>=400)
	     *n=2;
	   else   
	     *n=3;      
      }
      break;	
    
    case 2:
      if(d.character>=300 && d.etchics>50)
      {
	   *m=3;
	   if(d.etchics>=300 && d.charm >=300)
	     *n=1;
	   else if(d.etchics<300 && d.charm<300 && d.etchics>=250 && d.charm >=250)
	     *n=2;
	   else   
	     *n=3;      
      }
      else if(d.character<300 && d.etchics>50)
      {
	   *m=4;
	   if(d.speech>=200)
	     *n=1;
	   else if(d.speech<150 && d.speech>=80)
	     *n=2;
	   else   
	     *n=3;      
      }
      else
      {
	   *m=7;
	   if(d.hp>=400)
	     *n=1;
	   else if(d.hp<400 && d.hp>=200)
	     *n=2;
	   else   
	     *n=3;          
      }
      break;
    
    case 3:
      if(d.character>=400 && d.etchics>50)
      {
	   *m=5;
	   if(d.etchics>=300)
	     *n=1;
	   else if(d.etchics<300 && d.etchics>=150)
	     *n=2;
	   else   
	     *n=3;      
      }
      else if(d.character<400 && d.etchics>50)
      {
	   *m=4;
	   if(d.speech>=200)
	     *n=1;
	   else if(d.speech<150 && d.speech>=80)
	     *n=2;
	   else   
	     *n=3;      
      }
      else
      {
	   *m=7;
	   if(d.hp>=400)
	     *n=1;
	   else if(d.hp<400 && d.hp>=200)
	     *n=2;
	   else   
	     *n=3;          
      }
      break;    
    
    case 4:
      if(d.etchics>=50)
      {
	   *m=6;
      }
      else
      {
	   *m=8;
      }
      if(d.hskill>=100)
        *n=1;
      else if(d.hskill<100 && d.hskill>=80)
        *n=2;
      else   
        *n=3;       
      break;
 }

 if(d.sex==1)
   strcpy(buf, endmodecombat[*m].boy);
 else
   strcpy(buf, endmodecombat[*m].girl);
 *grade=endmodecombat[*m].grade;
 return 0;
}


int
pip_endingfamily(buf,m,n,grade) /*®a¨Æ*/
char *buf;
int *m,*n,*grade;
{
 *m=1;
 if(d.charm>=200)
   *n=1;
 else if(d.charm<200 && d.charm>100)
   *n=2;
 else 
   *n=3;
   
 if(d.sex==1)
   strcpy(buf, endmodefamily[*m].boy);
 else
   strcpy(buf, endmodefamily[*m].girl);
 *grade=endmodefamily[*m].grade;
 return 0;
}


int
pip_endingall_purpose(buf,m,n,grade,mode) /*¸U¯à*/
char *buf;
int *m,*n,*grade;
int mode;
{
 int data;
 int class;
 int num=0;
 
 if(mode==1)
    data=d.hexp;
 else if(mode==2)
    data=d.mexp;
 else if(mode==3)
    data=d.social;
 else if(mode==4)
    data=d.family;
 if(class>1000) class=1;
 else if(class>800) class=2;
 else if(class>500) class=3;
 else if(class>300) class=4;
 else class=5;

 data=pip_max_worktime(&num);
 switch(class)
 {
   case 1:
	if(d.character>=1000)
	{
	   *m=1;
	   if(d.etchics>=900)
	     *n=1;
	   else if(d.etchics<900 && d.etchics>=600)
	     *n=2;
	   else   
	     *n=3;	
	}
	else
	{
	   *m=2;
	   if(d.etchics>=650)
	     *n=1;
	   else if(d.etchics<650 && d.etchics>=400)
	     *n=2;
	   else   
	     *n=3;	
	}
	break;
   
   case 2:
	if(d.belief > d.etchics && d.belief > d.wisdom)
	{
	   *m=3;
	   if(d.etchics>=500)
	     *n=1;
	   else if(d.etchics<500 && d.etchics>=250)
	     *n=2;
	   else   
	     *n=3;	
	}
	else if(d.etchics > d.belief && d.etchics > d.wisdom)
	{
	   *m=4;
	   if(d.wisdom>=800)
	     *n=1;
	   else if(d.wisdom<800 && d.wisdom>=600)
	     *n=2;
	   else   
	     *n=3;	
	}
	else
	{
	   *m=5;
	   if(d.affect>=800)
	     *n=1;
	   else if(d.affect<800 && d.affect>=400)
	     *n=2;
	   else   
	     *n=3;	
	}
	break;

   case 3:
	if(d.belief > d.etchics && d.belief > d.wisdom)
	{
	   *m=6;
	   if(d.belief>=400)
	     *n=1;
	   else if(d.belief<400 && d.belief>=150)
	     *n=2;
	   else   
	     *n=3;	
	}
	else if(d.etchics > d.belief && d.etchics > d.wisdom)
	{
	   *m=7;
	   if(d.wisdom>=700)
	     *n=1;
	   else if(d.wisdom<700 && d.wisdom>=400)
	     *n=2;
	   else   
	     *n=3;	
	}
	else
	{
	   *m=8;
	   if(d.affect>=800)
	     *n=1;
	   else if(d.affect<800 && d.affect>=400)
	     *n=2;
	   else   
	     *n=3;	
	}
	break;   

   case 4:
	if(num>=2)
	{
	   *m=8+num;
	   switch(num)
	   {
	   	case 2:
	   		if(d.love>100)	*n=1;
	   		else if(d.love>50) *n=2;
	   		else *n=3;
	   		break;
	   	case 3:
	   		if(d.homework>100) *n=1;
	   		else if(d.homework>50) *n=2;
	   		else *n=3;
	   		break;
	   	case 4:
	   		if(d.hp>600) *n=1;
	   		else if(d.hp>300) *n=2;
	   		else *n=3;
	   		break;
	   	case 5:
	   		if(d.cookskill>200) *n=1;
	   		else if(d.cookskill>100) *n=2;
	   		else *n=3;
	   		break;
	   	case 6:
	   		if((d.belief+d.etchics)>600) *n=1;
	   		else if((d.belief+d.etchics)>200) *n=2;
	   		else *n=3;
	   		break;
	   	case 7:
	   		if(d.speech>150) *n=1;
	   		else if(d.speech>50) *n=2;
	   		else *n=3;
	   		break;
	   	case 8:
	   		if((d.hp+d.wrist)>900) *n=1;
	   		else if((d.hp+d.wrist)>600) *n=2;
	   		else *n=3;
	   		break;
	   	case 9:
	   	case 11:
	   		if(d.art>250) *n=1;
	   		else if(d.art>100) *n=2;
	   		else *n=3;
	   		break;
	   	case 10:
	   		if(d.hskill>250) *n=1;
	   		else if(d.hskill>100) *n=2;
	   		else *n=3;
	   		break;
	   	case 12:
	   		if(d.belief>500) *n=1;
	   		else if(d.belief>200) *n=2;
	   		else *n=3;
	   		break;
	   	case 13:
	   		if(d.wisdom>500) *n=1;
	   		else if(d.wisdom>200) *n=2;
	   		else *n=3;
	   		break;	
	   	case 14:
	   	case 16:
	   		if(d.charm>1000) *n=1;
	   		else if(d.charm>500) *n=2;
	   		else *n=3;
	   		break;
	   	case 15:
	   		if(d.charm>700) *n=1;
	   		else if(d.charm>300) *n=2;
	   		else *n=3;
	   		break;	   	
	   }
	}
	else
	{
	   *m=9;
	   if(d.etchics > 400)
	     *n=1;
	   else if(d.etchics >200)
	     *n=2;
	   else
	     *n=3;
	}
	break;
   case 5:
	if(num>=2)
	{
	   *m=24+num;
	   switch(num)
	   {
	   	case 2:
	   	case 3:
	   		if(d.hp>400) *n=1;
	   		else if(d.hp>150) *n=2;
	   		else *n=3;
	   		break;
	   	case 4:
	   	case 10:
	   	case 11:
	   		if(d.hp>600) *n=1;
	   		else if(d.hp>300) *n=2;
	   		else *n=3;
	   		break;
	   	case 5:
	   		if(d.cookskill>150) *n=1;
	   		else if(d.cookskill>80) *n=2;
	   		else *n=3;
	   		break;
	   	case 6:
	   		if((d.belief+d.etchics)>600) *n=1;
	   		else if((d.belief+d.etchics)>200) *n=2;
	   		else *n=3;
	   		break;
	   	case 7:
	   		if(d.speech>150) *n=1;
	   		else if(d.speech>50) *n=2;
	   		else *n=3;
	   		break;
	   	case 8:
	   		if((d.hp+d.wrist)>700) *n=1;
	   		else if((d.hp+d.wrist)>300) *n=2;
	   		else *n=3;
	   		break;
	   	case 9:
	   		if(d.art>100) *n=1;
	   		else if(d.art>50) *n=2;
	   		else *n=3;
	   		break;
	   	case 12:
	   		if(d.hp>300) *n=1;
	   		else if(d.hp>150) *n=2;
	   		else *n=3;
	   		break;
	   	case 13:
	   		if(d.speech>100) *n=1;
	   		else if(d.speech>40) *n=2;
	   		else *n=3;
	   		break;	
	   	case 14:
	   	case 16:
	   		if(d.charm>1000) *n=1;
	   		else if(d.charm>500) *n=2;
	   		else *n=3;
	   		break;
	   	case 15:
	   		if(d.charm>700) *n=1;
	   		else if(d.charm>300) *n=2;
	   		else *n=3;
	   		break;	   	
	   }
	}
	else
	{
	   *m=25;
	   if(d.relation > 100)
	     *n=1;
	   else if(d.relation >50)
	     *n=2;
	   else
	     *n=3;
	}
	break; 
 } 

 if(d.sex==1)
   strcpy(buf, endmodeall_purpose[*m].boy);
 else
   strcpy(buf, endmodeall_purpose[*m].girl);
 *grade=endmodeall_purpose[*m].grade;
 return 0;
}

int
pip_endingart(buf,m,n,grade) /*ÃÀ³N*/
char *buf;
int *m,*n,*grade;
{
 if(d.speech>=100)
 {
   *m=1;
   if(d.hp>=300 && d.affect>=350)
     *n=1;
   else if(d.hp<300 && d.affect<350 && d.hp>=250 && d.affect>=300)
     *n=2;
   else   
     *n=3;
 } 
 else if(d.wisdom>=400)
 {
   *m=2;
   if(d.affect>=500)
     *n=1;
   else if(d.affect<500 && d.affect>=450)
     *n=2;
   else   
     *n=3;
 }
 else if(d.classI>=d.classJ)
 {
   *m=3;
   if(d.affect>=350)
     *n=1;
   else if(d.affect<350 && d.affect>=300)
     *n=2;
   else   
     *n=3;
 }
 else 
 {
   *m=4;
   if(d.affect>=200 && d.hp>150)
     *n=1;
   else if(d.affect<200 && d.affect>=180 && d.hp>150)
     *n=2;
   else   
     *n=3;
 }
 if(d.sex==1)
   strcpy(buf, endmodeart[*m].boy);
 else
   strcpy(buf, endmodeart[*m].girl);
 *grade=endmodeart[*m].grade;  
 return 0;
}

int
pip_max_worktime(num)
int *num;
{
  int data=20;
  if(d.workA>data)
  {
     data=d.workA;
     *num=1;
  }
  if(d.workB>data)
  {
     data=d.workB;
     *num=2;
  }
  if(d.workC>data)
  {
     data=d.workC;
     *num=3;
  }
  if(d.workD>data)
  {
     data=d.workD;
     *num=4;
  }
  if(d.workE>data)
  {
     data=d.workE;
     *num=5;
  }

  if(d.workF>data)
  {
     data=d.workF;
     *num=6;
  }
  if(d.workG>data)
  {
     data=d.workG;
     *num=7;
  }
  if(d.workH>data)
  {
     data=d.workH;
     *num=8;
  }
  if(d.workI>data)
  {
     data=d.workI;
     *num=9;
  }
  if(d.workJ>data)
  {
     data=d.workJ;
     *num=10;
  }
  if(d.workK>data)
  {
     data=d.workK;
     *num=11;
  }
  if(d.workL>data)
  {
     data=d.workL;
     *num=12;
  }
  if(d.workM>data)
  {
     data=d.workM;
     *num=13;
  }
  if(d.workN>data)
  {
     data=d.workN;
     *num=14;
  }
  if(d.workO>data)
  {
     data=d.workO;
     *num=16;
  }
  if(d.workP>data)
  {
     data=d.workP;
     *num=16;
  }  

  return data;
}

int pip_game_over(endgrade)
int endgrade;
{
	long gradebasic;
	long gradeall;
	
	gradebasic=(d.maxhp+d.wrist+d.wisdom+d.character+d.charm+d.etchics+d.belief+d.affect)/10-d.offense;
	clrchyiuan(1,23);
	gradeall=gradebasic+endgrade;
	move(8,17);
	prints("[1;36m·PÁÂ±zª±§¹¾ã­Ó¬PªÅ¤pÂûªº¹CÀ¸.....[0m");
	move(10,17);
	prints("[1;37m¸g¹L¨t²Î­pºâªºµ²ªG¡G[0m");
	move(12,17);
	prints("[1;36m±zªº¤pÂû [37m%s [36mÁ`±o¤À¡× [1;5;33m%d [0m",d.name,gradeall);
	return gradeall;
}

int pip_divine() /*¥e¤R®v¨Ó³X*/
{
  char buf[256];
  char ans[4];
  char endbuf1[50];
  char endbuf2[50];
  char endbuf3[50];
  int endgrade=0;
  int endmode=0;
  long money;
  int tm;
  int randvalue;
  
  tm=d.bbtime/60/30;
  move(b_lines-2,0);
  money=300*(tm+1);
  clrchyiuan(0,24);
  move(10,14);
  prints("[1;33;5m¥n¥n¥n...[0;1;37m¬ðµM¶Ç¨Ó°}°}ªººVªùÁn.........[0m");
  pressanykey("¥hÁ@Á@¬O½Ö§a......");
  clrchyiuan(0,24);
  move(10,14);
  prints("[1;37;46m    ­ì¨Ó¬O¶³¹C¥|®üªº¥e¤R®v¨Ó³X¤F.......    [0m");
  pressanykey("¶}ªùÅý¥L¶i¨Ó§a....");
  if(d.money>=money)
  {
    randvalue=rand()%5;
    sprintf(buf,"§A­n¥e¤R¶Ü? ­nªá%d¤¸³á...[Y/n]",money);
#ifdef MAPLE
    getdata(12,14,buf, ans, 2, 1, 0);
#else
    getdata(12,14,buf, ans, 2, DOECHO, YEA);
#endif  // END MAPLE
    if(ans[0]!='N' && ans[0]!='n')
    {
      pip_ending_decide(endbuf1,endbuf2,endbuf3,&endmode,&endgrade);
      if(randvalue==0)
      		sprintf(buf,"[1;37m  §Aªº¤pÂû%s¥H«á¥i¯àªº¨­¥÷¬O%s  [0m",d.name,endmodemagic[2+rand()%5].girl);
      else if(randvalue==1)
      		sprintf(buf,"[1;37m  §Aªº¤pÂû%s¥H«á¥i¯àªº¨­¥÷¬O%s  [0m",d.name,endmodecombat[2+rand()%6].girl);
      else if(randvalue==2)
      		sprintf(buf,"[1;37m  §Aªº¤pÂû%s¥H«á¥i¯àªº¨­¥÷¬O%s  [0m",d.name,endmodeall_purpose[6+rand()%15].girl);
      else if(randvalue==3)
      		sprintf(buf,"[1;37m  §Aªº¤pÂû%s¥H«á¥i¯àªº¨­¥÷¬O%s  [0m",d.name,endmodeart[2+rand()%6].girl);
      else if(randvalue==4)
      		sprintf(buf,"[1;37m  §Aªº¤pÂû%s¥H«á¥i¯àªº¨­¥÷¬O%s  [0m",d.name,endbuf1);
      d.money-=money;
      clrchyiuan(0,24);
      move(10,14);
      prints("[1;33m¦b§Ú¥e¤Rµ²ªG¬Ý¨Ó....[0m");
      move(12,14);
      prints(buf);
      pressanykey("ÁÂÁÂ´fÅU¡A¦³½t¦A¨£­±¤F.(¤£·Ç¤£¯à©Ç§Ú³á)");
    }
    else
    {
      pressanykey("§A¤£·Q¥e¤R°Ú?..¯u¥i±¤..¨º¥u¦³µ¥¤U¦¸§a...");
    }
  }
  else
  {
    pressanykey("§Aªº¿ú¤£°÷³á..¯u¬O¥i±¤..µ¥¤U¦¸§a...");
  }
  return 0;
}
