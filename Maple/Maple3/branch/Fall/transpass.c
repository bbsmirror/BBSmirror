#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bbs.h"

struct new
{
  int userno;			/* unique positive code */
  char userid[IDLEN + 1];
  char passwd[PASSLEN];
  uschar signature;
  char realname[20];
  char username[24];
  usint userlevel;
  int numlogins;
  int numposts;
  usint ufo;
  time_t firstlogin;
  time_t lastlogin; 
  time_t staytime;		/* 總共停留時間 */
  time_t tcheck;		/* time to check mbox/pal */
  char lasthost[32];
  int numemail;			/* 寄發 Inetrnet E-mail 次數 */
  time_t tvalid;		/* 通過認證、更改 mail address 的時間 */
  char email[60];
  char address[60];
  char justify[60];		/* FROM of replied justify mail */
  char vmail[60];		/* 通過認證之 email */
  char ident[140 - 20];
  time_t vtime;			/* validate time */
  uschar year;	 		/* 生日(年) */
  uschar month;			/* 生日(月) */
  uschar day;			/* 生日(日) */
  uschar sex;			/* 性別 */
  unsigned long int money;	/* 現金(銀幣) */
  unsigned long int bankgold;	/* 銀行存款(金幣) */
  unsigned long int banksilver; /* 銀行存款(銀幣) */
};

typedef struct new new;
      
int main()
{
  new new;
  char c;

  for (c = 'a'; c <= 'z'; c++)
  {
    char buf[64];
    struct dirent *de;
    DIR *dirp;

    sprintf(buf, BBSHOME "/usr/%c", c);
    chdir(buf);

    if (!(dirp = opendir(".")))
      continue;

    while (de = readdir(dirp))
    {
      ACCT cuser;
      int fd;

      if (de->d_name[0] <= ' ' || de->d_name[0] == '.')
	continue;

      sprintf(buf, "%s/.ACCT", de->d_name);
      if ((fd = open(buf, O_RDWR)) < 0)
	continue;

      read(fd, &cuser, sizeof(cuser));
      memset(&new, 0, sizeof(new));

      strcpy(new.userid,cuser.userid);
      strcpy(new.passwd,cuser.passwd);
      new.signature=cuser.signature;
      strcpy(new.realname,cuser.realname);
      strcpy(new.username,cuser.username);
      new.userlevel=cuser.userlevel;
      new.numlogins=cuser.numlogins;
      new.numposts=cuser.numposts;
      new.ufo=cuser.ufo;
      new.firstlogin=cuser.firstlogin;
      new.lastlogin=cuser.lastlogin;
      new.staytime=cuser.staytime;
      new.tcheck=cuser.tcheck;
      strcpy(new.lasthost,cuser.lasthost);
      new.numemail=cuser.numemail;
      new.tvalid=cuser.tvalid;
      strcpy(new.email,cuser.email);
      strcpy(new.address,cuser.address);
      strcpy(new.justify,cuser.justify);
      strcpy(new.vmail,cuser.vmail);
      strcpy(new.ident,cuser.ident);
      new.vtime=cuser.vtime;
      new.year=0;
      new.month=0;
      new.day=0; 
      new.sex=0;
      new.money=1000;       /* 給每鍋user 1000元 */
      new.bankgold=0;	
      new.banksilver=0;                  

      lseek(fd,0L,SEEK_SET);
      write(fd, &new, sizeof(new));
      close(fd);
    }
  }
}
 