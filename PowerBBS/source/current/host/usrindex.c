#include "pbbs.h"

#define REC_SIZE        sizeof(struct REC)

struct REC {
                char name[20] ;
                int recno ;
           } ;

int seek_idx(handle,name,idxsize,notfind)
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


int do_index(name,recno)
/*
    add one record to index file write by Aquarius Kuo    Mar 29, 1994

return:  TRUE : ok
         FALSE : error occure

*/
char *name ;
int recno ;
{
  char fn[80] ;
  struct REC new, all[1000] ;
  int posi ;
  int handle, fl, nf ;
  int i, page, last ;

    bzero((char *)&new,REC_SIZE) ;
    sprintf(fn,"%s.idx",USER_DATA_BASE) ;
    if(file_exist(fn))
      fl=flength(fn)/REC_SIZE ;
    if((handle=open(fn,O_RDWR))<0)
    {
      if((handle=open(fn,O_CREAT|O_RDWR,S_IREAD|S_IWRITE))<0)
      {
        return(FALSE) ;
      }
      else
      {
	strcpy(new.name,name) ;
        new.recno=recno ;
	write(handle,&new,REC_SIZE) ;
	close(handle) ;
        return(TRUE) ;
      }
    }


    posi=seek_idx(handle,name,fl,&nf) ;

    if(posi<0)  return(FALSE) ;
    if(posi==0)  posi=nf+1 ;
    page=(fl-posi)/1000 ;
    last=(fl-posi)%1000 ;
    strcpy(new.name,name) ;
    new.recno=recno ;
    
    flock(handle,LOCK_EX) ;	/*-- lock file --*/
    if(last>0)
    {
      lseek(handle,(posi+page*1000)*REC_SIZE,SEEK_SET) ;
      read(handle,all,REC_SIZE*last) ;
      lseek(handle,(posi+page*1000+1)*REC_SIZE,SEEK_SET) ;
      write(handle,all,REC_SIZE*last) ;
    }
    for(i=page; i>0; i--)
    {
      lseek(handle,(posi+(i-1)*1000)*REC_SIZE,SEEK_SET) ;
      read(handle,all,REC_SIZE*1000) ;
      lseek(handle,(posi+(i-1)*1000+1)*REC_SIZE,SEEK_SET) ;
      write(handle,all,REC_SIZE*1000) ;
    }
    lseek(handle,posi*REC_SIZE,SEEK_SET) ;
    write(handle,&new,REC_SIZE) ;
    flock(handle,LOCK_UN) ;
    close(handle) ;
    return(TRUE) ;

}

int found(name)
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

    sprintf(fn,"%s.idx",USER_DATA_BASE) ;

    if( !file_exist(fn) ) return(0);

    fl=flength(fn)/REC_SIZE ;

    if((handle=open(fn,O_RDWR))<0)
    {
        return(FALSE) ;
    }

  if((posi=seek_idx(handle,name,fl,&nf))<=0)
    return(FALSE) ;
  lseek(handle,(posi-1)*REC_SIZE,SEEK_SET) ;
  read(handle,&one,REC_SIZE) ;
  close(handle) ;
  
  return(one.recno) ;
}

