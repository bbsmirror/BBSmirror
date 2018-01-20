#include "../bbs.h"
#include "cgic.h"
#include <stdio.h>

#define BBSHOME "/home/bbs"
#define ME      "http://tsunami.ml.org/cgi-bin/sboard"
#define READPOST "http://tsunami.ml.org/cgi-bin/readpost"

int cgiMain()
{
   struct boardheader bh;
   int i,fd;
   struct stat st ;
   char buf[255],id[IDLEN],p[10],class[10];
   time_t t;
   
   cgiFormStringNoNewlines("id", id, IDLEN);
   cgiFormStringNoNewlines("p", p, 10);
   cgiFormStringNoNewlines("class",class,10);
    
   ht_header("魔法王國BBS - 選擇看版");      

   if(resumeuser(id,p)!=0) 
       ht_exit(-1); 
   ht_default_color();
   
   sprintf(buf,"%s/.BOARDS",BBSHOME);
   
   if((fd=open(buf,O_RDONLY))==NULL)
                           exit(-1);

   fstat(fd,&st);                         

   fprintf(cgiOut,"<CENTER><TABLE BORDER=3>\n");   
   fprintf(cgiOut,"<TR BGCOLOR=\"#FFCCCC\"><TD>看版</TD><TD>中文說明</TD><TD>版主</TD></TR>");
     for(i=0;i<(st.st_size/sizeof(bh));i++)
     {
        lseek(fd,i*sizeof(bh),SEEK_SET);
        if(read(fd,&bh,sizeof(bh))>0)
         if(!class[0] || (bh.title[0]==class[0])) 
          if( (bh.level & PERM_POSTMASK) || HAS_PERM(bh.level) )
            fprintf(cgiOut,"<TR><TD>%s</TD><TD><A HREF=%s?board=%s&id=%s&p=%s>%s</A></TD><TD>
          <A HREF=mailto:%s.bbs@tsunami.ml.org>%s</A></TD></TR>\n",bh.filename,READPOST,bh.filename,id,p,bh.title+1,strtok(bh.BM," "),bh.BM);
     }
   fprintf(cgiOut,"</TABLE>\n");
   ht_end();
   close(fd);
}
