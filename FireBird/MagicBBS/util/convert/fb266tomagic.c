// 警告: 此程式尚未測試過，僅供參考使用
// 不保證其正確性，使用前請先備份.PASSWDS檔案

#include "../bbs.h"

struct oldrec {                  /* Structure used to hold information in */
        char            userid[IDLEN+2];   /* PASSFILE */
        time_t          firstlogin;
        char            lasthost[16];
        unsigned int    numlogins;
        unsigned int    numposts;
        char            flags[2];
        char            passwd[PASSLEN];
        char            username[NAMELEN];
        char            ident[NAMELEN];
        char            termtype[STRLEN];
        unsigned int    userlevel;
        time_t          lastlogin;
        time_t          stay;
        char            realname[NAMELEN];
        char            address[STRLEN];
        char            email[STRLEN];
        int             signature;
        unsigned int    userdefine;
        time_t          notedate;
        int             noteline;
} old;

struct newrec {                  /* Structure used to hold information in */
        char            userid[IDLEN+2];   /* PASSFILE */
        time_t          firstlogin;
        char            lasthost[16];
        unsigned int    numlogins;
        unsigned int    numposts;
        char            flags[2];
        char            passwd[PASSLEN];
        char            username[NAMELEN];
        char            ident[NAMELEN];
        char            termtype[STRLEN];
        unsigned        userlevel;
        time_t          lastlogin;
        time_t          stay;
        char            realname[NAMELEN];
        char            address[STRLEN];
        char            email[STRLEN];
        int             signature;
        unsigned int    userdefine;
	int             editor;  
                                     /* 以下為魔法王國新增部份 */
        unsigned int    showfile;
        int             magic;
        int             addmagic;
        uschar          bmonth; 
        uschar          bday;
        uschar          byear;
        uschar          sex;
        int             money;
        int             bank;
        int             lent;
        
        int             unused0;
        int             unused1;
        unsigned int    unsign_0000;
        unsigned int    unsign_ffff;

}new ;

void main(void)
{
  int fdr,fdw;
  
  fdr=open(".PASSWDS",O_RDONLY);
  fdw=open(".PASSWDS.new",O_WRONLY | O_CREAT | O_TRUNC, 0644);

  while(read(fdr,&old,sizeof(old))==sizeof(old))
  {    
        memcpy(new.userid,old.userid,IDLEN+2);   /* PASSFILE */
        new.firstlogin=old.firstlogin;
        memcpy(new.lasthost,old.lasthost,16);
        new.numlogins=old.numlogins;
        new.numposts=old.numposts;
        memcpy(new.flags,old.flags,2);
        memcpy(new.passwd,old.passwd,PASSLEN);
        memcpy(new.username,old.username,NAMELEN);
        memcpy(new.ident,old.ident,NAMELEN);
        memcpy(new.termtype,old.termtype,STRLEN);
        new.userlevel=old.userlevel;
        new.lastlogin=old.lastlogin;
        new.stay=old.stay;
        memcpy(new.realname,old.realname,NAMELEN);
        memcpy(new.address,old.address,STRLEN);
        memcpy(new.email,old.email,STRLEN);
        new.signature=old.signature;
        new.userdefine=old.userdefine;
	new.editor=0;  

	new.sex=0;
        new.showfile=0xffff;
        new.addmagic=0;
        new.bmonth=0; 
        new.bday=0;
        new.byear=0;
        
        new.money=1000;
        new.lent=0;
        new.bank=0;
        new.magic=0;

        
        new.unsign_0000=0x0000;
        new.unsign_ffff=0xffff;
        new.unused0=0;
        new.unused1=0;       
        
        write(fdw,&new,sizeof(new));
   }
   close(fdr);
   close(fdw);
}     
