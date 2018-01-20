/* 自動發信程式 by Magi 2/23/98 */

#include "../bbs.h"
#include <stdio.h>
#include <time.h>
#define BBSHOME "/home/bbs"

int main(int argc,char *argv[])
{
    int fd;
    struct fileheader fh;
    char Buf[200],fname[20],ch='A';
    long now;
    struct stat st;
    
    if (argc!=5) 
    { printf("usage: %s filename boardname author title\n",argv[0]); exit(-1); }
    
    now=time(0);
    
    do 
    {
      sprintf(fname,"M.%d.%c",now,ch++);
      sprintf(Buf,BBSHOME "/boards/%s/%s",argv[2],fname);
    }
    while(stat(Buf,&st)==0);
    
    sprintf(Buf,"cp %s %s/boards/%s/%s",argv[1],BBSHOME,argv[2],fname);
    system(Buf);

    strcpy(fh.filename,fname);
    strncpy(fh.owner,argv[3],STRLEN);
    strncpy(fh.title,argv[4],STRLEN);
    fh.filename[ STRLEN - 1 ] = 'S';
    fh.filename[ STRLEN - 2 ] = 'S';
   
    sprintf(Buf,"%s/boards/%s/.DIR",BBSHOME,argv[2]);
    umask(~(S_IRUSR | S_IWUSR | S_IRGRP));
    fd=open(Buf,O_WRONLY | O_APPEND | O_CREAT);    
    write(fd,&fh,sizeof(fh));
    close(fd);    
}    
