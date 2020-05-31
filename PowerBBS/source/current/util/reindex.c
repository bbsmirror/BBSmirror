/********************************
    modify user data base
    write by Aquarisu Kuo
    May 4, 1994
**********************************/
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

/* #ifndef NEXTSTEP */
#ifndef NOMALLOC 		/* Jones */
#include <malloc.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

#include "../host/dbf.h"
#include "../setup.h"

#define REC_SIZE        sizeof(struct REC)

struct REC {
                char name[20] ;
                int recno ;
           } ;
/*
	flength --- get length of a file
*/
flength(filename)
	char *filename;
{
	int test;
	unsigned long len;
	
        test=open(filename, O_RDONLY);
        lseek(test, 0, SEEK_END);
       	len = tell(test);
	close(test);

	return(len);
}
/*end of flength*/

/*	#ifdef NETBSD 	*/
#ifdef TELL		/* Jones */
/*
	NetBSD does not support tell() function, use fstat as alternative one
*/
tell(fd)
        int fd;
{
        struct stat buf;
        fstat(fd, &buf);
        return(buf.st_size);
}
#endif

/***********************************
  reindex user database
*/
main()
{
  int utf, handle ;
  int i, radix, cnt ;
  struct udb rec ;
  long maxno ;
  char filename[100] ;
  struct LINK {
                struct REC body ;
                struct LINK *next ;
              } ;
  struct LINK *ptr, *head[255], *tmp ;

  chdir(SYSTEM_PATH);	/*change to pbbs system path which set at setup.h*/

  sprintf(filename, "%s.dbf", USER_DATA_BASE) ;
  if((maxno=flength(filename)/sizeof(struct udb))<=0)
  {
    printf("\r\n\nNo user index here!!\r\n") ;
    exit(1) ;
  }
        
        if( (utf=open(filename, O_RDONLY)) <= 0 )
                exit(1) ;
        
        ptr=NULL ;
	for(i=0; i<255; i++)
	{
	  head[i]=NULL ;
	}

        lseek(utf,sizeof(struct udb), SEEK_SET) ;
        
        for(i=1; i<maxno; i++)
        {
          read(utf,&rec,sizeof(struct udb)) ;
          
          if(rec.delete_mark!='X')
          {
            /* inster_index */
            tmp=(struct LINK *)malloc(sizeof(struct LINK)) ;
            tmp->body.recno=i ;
            strcpy(tmp->body.name,rec.bbs_name) ;
            
	    radix=(int) tmp->body.name[0] ;

            if(head[radix]==NULL)      /* the first one */
            {
              head[radix]=ptr=tmp ;
              ptr->next=NULL ;
              continue ;
            }
            
            
            ptr=head[radix] ;
	    
            if(strcmp(ptr->body.name,tmp->body.name)>0)   /* check the head */
            {
              tmp->next=head[radix] ;
              head[radix]=tmp ;
              continue ;
            }

            while( ptr->next != NULL )
            {
              if( strcmp(ptr->next->body.name, tmp->body.name)>0 )
              {
                tmp->next=ptr->next ;
                ptr->next=tmp ;
                break ;
              }
              ptr=ptr->next ;
            }

            if(ptr->next==NULL)         /* check the last one */
            {
              ptr->next=tmp ;
              tmp->next=NULL ;
              continue ;
            }
	    
          }
        }
        close(utf) ;
                
        sprintf(filename, "%s.idx", USER_DATA_BASE) ;
        if((handle=open(filename,O_CREAT|O_WRONLY,S_IWUSR|S_IRUSR))<2)
        {
          printf("index file open error!\r\n") ;
          exit(0) ;
        }
        
        flock(handle,LOCK_EX) ;
        
        /* rewrite index file */
	cnt=0 ;		/* count the total records */
	for(i=0; i<255; i++)
	{
          ptr=head[i] ;
          while(ptr!=NULL)
          {
	    cnt++ ;
            write(handle,&(ptr->body),REC_SIZE) ;
            ptr=ptr->next ;
          }
	}
          
	ftruncate(handle,cnt*REC_SIZE) ;
        flock(handle,LOCK_UN) ;
        close(handle) ;
	exit(0) ;
}
        
        
