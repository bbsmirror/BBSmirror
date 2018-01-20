/***************************/
/* ªÑ²¼Åo by dsyan 87.6.21 */
/*                    9/21 */
/***************************/

#include "bbs.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#define stosum 999

struct st
{
 char name[stosum][12];
 char ud[21];
 long price[stosum];
 int max_page;
 int max;
};

static void
attach_err(shmkey, name)
  int shmkey;
  char *name;
{
  fprintf(stderr, "[%s error] key = %x\n", name, shmkey);
  exit(1);
}

static void *
attach_shm(shmkey, shmsize)
  int shmkey, shmsize;
{
  void *shmptr;
  int shmid;

  shmid = shmget(shmkey, shmsize, 0);
  if (shmid < 0)
  {
    shmid = shmget(shmkey, shmsize, IPC_CREAT | 0600);
    if (shmid < 0)
      attach_err(shmkey, "shmget");
    shmptr = (void *) shmat(shmid, NULL, 0);
    if (shmptr == (void *) -1)
      attach_err(shmkey, "shmat");
    memset(shmptr, 0, shmsize);
  }
  else
  {
    shmptr = (void *) shmat(shmid, NULL, 0);
    if (shmptr == (void *) -1)
      attach_err(shmkey, "shmat");
  }
  return shmptr;
}

int
p_stock()
{
 char tmp[200],tp2[200];
 int own[stosum];
 int page=0;
 int tt=0,t1,t2,ed;
 double td,pric;
 struct st *sto;
 FILE *ff,*fff;
 time_t now;
 struct tm *ptime;
      
 if(strcmp("dsyan",cuser.userid)) return 1;
 
 more("etc/game/stock_wel",YEA);
 showtitle("ªÑ¥«¤j¦ë", BoardName);
 setutmpmode(STOCK);
 sto = attach_shm(5000, sizeof(*sto)); 
 sprintf(tmp,"/home/bbs/home/%s/stock",cuser.userid);

 if(ff=fopen(tmp,"r"))
  for(tt=0;tt<stosum;tt++) fscanf(ff,"%d\n",&own[tt]);
 else
 {
  ff=fopen(tmp,"w");
  for(tt=0;tt<stosum;tt++) 
  {
   fprintf(ff,"%d\n",0);
   own[tt]=0;
  }
 }
 fclose(ff);

 /* Åª¸ê®ÆÀÉ */
if(ff=fopen("/home/bbs/etc/game/stock_now","r"))
{
 long tmpp;
 char tmpn[12];
 tt=0; t1=0;
 fgets(tmp,150,ff);
 fgets(tmp,150,ff);
 tmp[20]=0;
 if(strcmp(tmp,sto->ud))
 {
  strcpy(sto->ud,tmp);
  if(fff=fopen("/home/bbs/etc/game/stock_name","r"))
  {
   while(fgets(sto->name[t1],12,fff)) 
   {
    fgets(tmp,12,fff);
    move(8,8); prints("%d <%s>",t1,sto->name[t1]);
    t1++;
   }
   fclose(fff);
  }
  fff=fopen("/home/bbs/etc/game/stock_log","a+");
  fprintf(fff,"[41m§ó·s¸ê®Æ [42m%s [m\n",sto->ud);
  fclose(fff);
  fff=fopen("/home/bbs/etc/game/stock_name","a+");
  while(fgets(tmp,200,ff))
  {
   if(tmp[0]!='|'||tmp[1]<'0'||tmp[1]>'9') continue;
   tmp[12]=0; tmp[53]=0; tt++;
   
   tmpp=atof(tmp+47)*100;
   move(10,10);
   prints("tmpp=%d ",tmpp);
  
   strcpy(tmpn,tmp+1);
   move(11,11);
   prints("tmpn=<%s> ",tmpn);
  
   for(t2=0;t2<t1;t2++) 
    if(!strcmp(tmpn,sto->name[t2])) break;
   if(t2==t1)
   {
    strcpy(sto->name[t2],tmpn);
    fprintf(fff,"%s\n",tmpn);
    t1++;
   }
   sto->price[t2]=tmpp;
  }
  fclose(fff);
  fclose(ff);
  sto->max=tt;
  sto->max_page=tt/40;
  if(sto->max_page%40) sto->max_page++;
 }
} 
 while(-1)
 {  
  int i,r;
/* µe­±¥Dµ{¦¡ */
 move(1,0); clrtobot();
 prints("[31;46;1m ½s¸¹ [42m ªÑ ²¼ ¦W ºÙ [43m »ù ®æ"
 	" [45m «ù¦³±i¼Æ [46;1m     ½s¸¹ [42m ªÑ ²¼ ¦W ºÙ"
 	" [43m »ù ®æ [45m «ù¦³±i¼Æ [m");
 for(i=0;i<20;i++)
 {
  move(i+2,0);
  
  r=page*40+i;
  if(r+1<=sto->max) 
   prints(" %3d)  %11s%5d.%-2d %5d         ",r+1,sto->name[r], 
     sto->price[r]/100,sto->price[r]%100,own[r]);
     
  r=page*40+i+20;
  if(r+1<=sto->max) 
   prints( "%3d)  %11s%5d.%-2d %5d\n",r+1,sto->name[r],
     sto->price[r]/100,sto->price[r]%100,own[r]);
 }
 move(22,0);
 prints("[44mn:¤U­¶ p:¤W­¶ b:¶R s:½æ v:¬Ý e:­× q:¸õ¥X ª÷:%-8d %2d/%2d %19s[m",
   cuser.money,page+1,sto->max_page,sto->ud);

  tt=igetch();
  switch(tt)
  {
  case 'b':
   now=time(0);
   ptime = localtime(&now);
   if(ptime->tm_hour>7&&ptime->tm_hour<19)
   {
   move(23,0); 
   prints("¥æ©ö®É¶¡¬°¨C¤Ñ±ß¤W¤CÂI¨ì¹j¤Ñ¦­¤W¤CÂI..");
   igetch();
   break;
   }
   move(23,0); prints("­n¶R¨º®a??(1-%d) ",sto->max);
   getdata(23,19, " ",tmp, 4, 1, 0); 
   tt=atoi(tmp);
   if(tt<1||tt>sto->max) break;
    t2=cuser.money/(sto->price[tt-1]*10*1.07);
    move(23,0); prints("­n¶R´X±i??(0-%d) ",t2);
    getdata(23,19, " ",tmp, 4, 1, 0); 
    t1=atoi(tmp);
    if(t1>t2||t1<1) break;

    fff=fopen("/home/bbs/etc/game/stock_log","a+");
    now=time(0);
    td=t1*sto->price[tt-1]*10*0.07;
    sprintf(tmp, "[33;1m%s [34m%s[m ", Cdate(&now),cuser.userid);
    fprintf(fff,"%s [32m¶R¤F [44m%s [m[43m%d ±i.. [31;1m%d[m\n", 
      tmp, sto->name[tt-1],t1,(int)td);
    fclose(fff);

    sprintf(tp2,"/home/bbs/home/%s/stock_log",cuser.userid);
    fff=fopen(tp2,"a+");
    now=time(0);
    td=t1*pric*0.07;
    fprintf(fff,"%s ¥H %f ªº»ù®æ¶R¤F %s %d ±i.. %d\n", 
      Cdate(&now), (float) sto->price[tt-1]/100,sto->name[tt-1],t1,(int)td);
    fclose(fff);

    td=t1*sto->price[tt-1]*10*1.07;
    cuser.money -= td;
    substitute_record(fn_passwd, &cuser, sizeof(userec), usernum);
    own[tt-1]+=t1;
   break;
  case 's':
   now=time(0);
   ptime = localtime(&now);
   if(ptime->tm_hour>7&&ptime->tm_hour<19)
   {
   move(23,0);
   prints("¥æ©ö®É¶¡¬°¨C¤Ñ±ß¤W¤CÂI¨ì¹j¤Ñ¦­¤W¤CÂI..");
   igetch();
   break;
   }
   move(23,0); prints("­n½æ¨º®a??(1-%d) ",sto->max);
   getdata(23,19, " ",tmp, 4, 1, 0); 
   tt=atoi(tmp);
   if(tt<1||tt>sto->max||!own[tt-1]) break;
    pric=sto->price[tt-1]*10;
    move(23,0); prints("­n½æ´X±i??(0-%d) ",own[tt-1]);
    getdata(23,19, " ",tmp, 4, 1, 0); 
    t1=atoi(tmp);
    if(t1>own[tt-1]||t1<=0) break;
    now=time(0);
    td=t1*pric*0.07;    
    fff=fopen("/home/bbs/etc/game/stock_log","a+");
    sprintf(tmp, "[33;1m%s [34m%s[m ", Cdate(&now),cuser.userid);    
    fprintf(fff,"%s [31m½æ¤F [44m%s [m[43m%d ±i.. [31;1m%d[m\n", 
      tmp, sto->name[tt-1],t1,(int)td);
    fclose(fff);

    sprintf(tp2,"/home/bbs/home/%s/stock_log",cuser.userid);
    fff=fopen(tp2,"a+");
    fprintf(fff,"%s ¥H %f ªº»ù®æ½æ¤F %s %d ±i.. %d\n", 
      Cdate(&now),(float) sto->price[tt-1]/100,sto->name[tt-1],t1,(int)td);
    fclose(fff);

    td=t1*pric*0.93;
    cuser.money += td;
    substitute_record(fn_passwd, &cuser, sizeof(userec), usernum);
    own[tt-1]-=t1;
   break;
  case 'v':
   sprintf(tp2,"/home/bbs/home/%s/stock_log",cuser.userid);
   more(tp2,YEA);
   showtitle("ªÑ¥«¤j¦ë", BoardName);
   break;
  case 'e':
   sprintf(tp2,"/home/bbs/home/%s/stock_log",cuser.userid);
   t2=vedit(tp2, NA,0);
   showtitle("ªÑ¥«¤j¦ë", BoardName);
   break;
  case 'p':
   if(page) page--;
   break;
  case 'n':
   if(page+1<sto->max_page) page++;
   break;
  case 'q':
  sprintf(tmp,"/home/bbs/home/%s/stock",cuser.userid);
  ff=fopen(tmp,"w");
  for(tt=0;tt<stosum;tt++) fprintf(ff,"%d\n",own[tt]);
  fclose(ff);
  return 1;
  }
 }
}
