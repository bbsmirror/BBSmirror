#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

#ifndef FALSE
#define FALSE	0
#endif

#ifndef TRUE
#define TRUE	!FALSE	
#endif


#define REC_SIZE        sizeof(struct REC)

struct REC {
                char name[20] ;
           } ;

int ln_seek_idx(handle,name,idxsize,notfind)
/*
    seek index file  write by Aquarius Kuo.   Mar 29, 1994.

return :  >0 : record number in index file
          0 : not found
         -1 : file error
*/
int handle ;
char *name ;
int idxsize ;
int *notfind ;
{
  struct REC rn ;
  int h, t, m ;         /* real head & tail */
  int find ;

  if((t=idxsize-1)<0)
  {
    notfind=0 ;
    return(0) ;
  }

  h=0 ;
  m=(h+t)/2 ;
  find=FALSE ;
  do
  {
    lseek(handle,m*REC_SIZE,SEEK_SET) ;
    read(handle,&rn,REC_SIZE) ;
    if(strcmp(rn.name,name)==0)
    {
      find=TRUE ;
      break ;
    }

    if(strcmp(name,rn.name)>0)
    {
      h=m+1 ;
    }

    if(strcmp(name,rn.name)<0)
    {
      t=m-1 ;
    }
    m=(h+t)/2 ;
  }
  while(h<=t) ;
  if(!find)
  {
    *notfind=t ;
    return(0) ;
  }

  return(m+1) ;
}



int found_ln(name)
/*
    found the record number   write by Aquarius Kuo    Mar 29, 1994

return:  TRUE : ok
         FALSE : error occure

*/
char *name ;
{
  struct REC one ;
  int handle, posi, fl, nf ;
  char fn[80] ;

    sprintf(fn,"lastname.db") ;

    if( !file_exist(fn) ) return(0);

    fl=flength(fn)/REC_SIZE ;

    if((handle=open(fn,O_RDWR))<0)
    {
        return(FALSE) ;
    }

  if((posi=ln_seek_idx(handle,name,fl,&nf))<=0)
    return(FALSE) ;
  lseek(handle,(posi-1)*REC_SIZE,SEEK_SET) ;
  read(handle,&one,REC_SIZE) ;
  close(handle) ;
  
  return(TRUE) ;
}

