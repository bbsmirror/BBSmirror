/*-------------------------------------------------------*/
/* util/transusr.c      by ernie@micro8.ee.nthu.edu.tw   */
/*-------------------------------------------------------*/
/* target : Maple Sob 2.36 至 Maple 3.02 使用者轉換      */
/*          .PASSWDS => .USR .ACCT                       */
/* update : 98/06/14                                     */
/*-------------------------------------------------------*/
/* syntax : transusr                                     */
/*-------------------------------------------------------*/

/*
   1. 設定 OLD_BBSHOME，FN_PASSWD，OLD_MAXSIGLINES(sob config.h)
   2. 修改 struct userec 及 creat_dirs()
      (userec 兩版定義的字串長度不一，請自行換成數字)
   3. 除 plans 檔名，好友名單、暫存檔等都不轉換
   4. Sob 有九個簽名檔，只轉前三個
   5. 信箱中的 internet mail 如有需要請先 chmod 644 `find PATH -perm 600`
   6. HAVE_PERSONAL_GEM 是 Sob 的個人精華區，M3 沒有，需要的話請自行改寫

   ps. 使用前請先行備份，use on ur own risk. 程式拙劣請包涵 :p
   ps. 感謝 lkchu 的 Maple 3.02 for FreeBSD
*/

#include "bbs.h"

#undef  HAVE_PERSONAL_GEM

#define OLD_BBSHOME     "/home/oldbbs"          /* 2.36 */
#define FN_PASSWD       "/home/oldbbs/.PASSWDS" /* 2.36 */
#define OLD_MAXSIGLINES 6                       /* 2.36 */

/*-------------------------------------------------------*/
/* 2.36 .PASSWDS struct                                  */
/*-------------------------------------------------------*/

struct userec
{
  char userid[13];
  char realname[20];
  char username[24];
  char passwd[14];
  uschar uflag;
  usint userlevel;
  ushort numlogins;
  ushort numposts;
  time_t firstlogin;
  time_t lastlogin;
  char lasthost[16];
  long money;
  uschar invisible;
  char remoteuser[3];
  char email[50];
  char address[50];
  char justify[39];
  uschar month;
  uschar day;
  uschar year;
  uschar sex;
  uschar state;
  usint  exmailbox;
  uschar pager;
  int  test1;
  int  test2;
  usint  test3;
  usint  test4;
  usint  test5;
  long int acc;
  long int long1;
  long int long2;
  float  f1;
  float  f2;
  float  f3;
  char pad[204];
};
typedef struct userec userec;

/* ----------------------------------------------------- */
/* 2.36 DIR of board struct : 128 bytes                  */
/* ----------------------------------------------------- */

struct fileheader
{
  char filename[33];            /* M.9876543210.A */
  char savemode;                /* file save mode */
  char owner[14];               /* uid[.] */
  char date[6];                 /* [02/02] or space(5) */
  char title[73];
  uschar filemode;              /* must be last field @ boards.c */
};
typedef struct fileheader fileheader;

/* ----------------------------------------------------- */
/* 2.36 functions                                        */
/* ----------------------------------------------------- */

int
get_record(fpath, rptr, size, id)
  char *fpath;
  char *rptr;
  int size, id;
{
  int fd;

  if ((fd = open(fpath, O_RDONLY, 0)) != -1)
  {
    if (lseek(fd, size * (id - 1), SEEK_SET) != -1)
    {
      if (read(fd, rptr, size) == size)
      {
        close(fd);
        return 0;
      }
    }
    close(fd);
  }
  return -1;
}

/* ----------------------------------------------------- */
/* 2.39 functions                                        */
/* ----------------------------------------------------- */

char radix32[32] = {
  '0', '1', '2', '3', '4', '5', '6', '7',
  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
  'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
  'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
};

void
str_lower(dst, src)
  char *dst, *src;
{
  int ch;

  do
  {
    ch = *src++;
    if (ch >= 'A' && ch <= 'Z')
      ch |= 0x20;
    *dst++ = ch;
  } while (ch);
}


void
trans_man_stamp(folder, token, hdr, fpath, time)
  char *folder;
  int token;
  HDR *hdr;
  char *fpath;
  time_t time;
{
  char *fname, *family;
  int rc;

  fname = fpath;
  while (rc = *folder++)
  {
    *fname++ = rc;
    if (rc == '/')
      family = fname;
  }
  if (*family != '.')
  {
    fname = family;
    family -= 2;
  }
  else
  {
    fname = family + 1;
    *fname++ = '/';
  }

  *fname++ = token;

  *family = radix32[time & 31];
  archiv32(time, fname);

  if (rc = open(fpath, O_WRONLY | O_CREAT | O_EXCL, 0600))
  {
    memset(hdr, 0, sizeof(HDR));
    hdr->chrono = time;
    str_stamp(hdr->date, &hdr->chrono);
    strcpy(hdr->xname, --fname);
    close(rc);
  }
  return;
}

/* ----------------------------------------------------- */

bad_user_id(userid)
  char *userid;
{
  register char ch;

  if (strlen(userid) < 2)
    return 1;

  if (!isalpha(*userid))
    return 1;

  if (!strcasecmp(userid, "new"))
    return 1;

  while (ch = *(++userid))
  {
    if (!isalnum(ch))
      return 1;
  }
  return 0;
}

static int
uniq_userno(fd)
  int fd;
{
  char buf[4096];
  int userno, size;
  SCHEMA *sp;                   /* record length 16 可整除 4096 */

  userno = 1;

  while ((size = read(fd, buf, sizeof(buf))) > 0)
  {
    sp = (SCHEMA *) buf;
    do
    {
      if (sp->userid[0] == '\0')
      {
        lseek(fd, -size, SEEK_CUR);
        return userno;
      }
      userno++;
      size -= sizeof(SCHEMA);
      sp++;
    } while (size);
  }

  return userno;
}

void
transfer_mail(old)
   userec *old;
{
   int num = 1;
   char f_dir[40];
   fileheader fh;
   HDR mhdr;

   sprintf(f_dir, OLD_BBSHOME"/home/%s/.DIR", old->userid);
   while(get_record(f_dir, &fh, sizeof(fh), num) != -1)
   {
      char new_name[10] = "@", time_str[10], buf[256], buf1[20];

      memset(&mhdr, 0, sizeof(mhdr));
      strncpy(time_str, fh.filename + 2, 9);
      new_name[1] = radix32[atoi(time_str) & 31];
      archiv32(atoi(time_str), new_name + 1);
      str_lower(buf1, old->userid);
      sprintf(buf, "cp "OLD_BBSHOME"/home/%s/%s "BBSHOME"/usr/%c/%s/@/%s",
         old->userid, fh.filename,
         tolower(*old->userid), buf1, new_name);
      system(buf);
      mhdr.chrono = (time_t)atoi(time_str);
      strcpy(mhdr.xname, new_name);
      strcpy(mhdr.owner, fh.owner);
      strcpy(mhdr.title, fh.title);
      str_stamp(mhdr.date, &mhdr.chrono);
      if(fh.filemode & 0x2)
         mhdr.xmode |= MAIL_MARKED;
      mhdr.xmode |= MAIL_READ;                  /* 設成已讀 */
      sprintf(buf, BBSHOME"/usr/%c/%s/.DIR",
         tolower(*old->userid), buf1);
      rec_add(buf, &mhdr, sizeof(mhdr));

      num++;
   }
}

#ifdef HAVE_PERSONAL_GEM
void
transfer_man(old, man_path, brd_folder)
   userec *old;
   char *man_path, *brd_folder;
{
   int num;
   char fpath[80];
   fileheader item;
   HDR ghdr;

   num = 1;
   while(get_record(man_path, &item, sizeof(fileheader), num) != -1)
   {
      char time_str[10];
      char *ptr;

      strncpy(time_str, item.filename + 2, 9);

      if(*item.filename == 'M')                 /* 只轉 M.x.A 及 D.x.a */
      {
         char buf[256];

         ptr = brd_folder;
         trans_man_stamp(ptr, 'A', &ghdr, fpath, (time_t)atoi(time_str));
         strcpy(ghdr.owner, item.owner);
         strcpy(ghdr.title, item.title + 3);
         rec_add(brd_folder, &ghdr, sizeof(ghdr));
         sprintf(buf, "cp %s", man_path);
         ptr = strrchr(buf, '/') + 1;
         sprintf(ptr, "%s %s", item.filename, fpath);
         system(buf);

      }
      else if(*item.filename == 'D')
      {
         char tmp_path[256], tmp_folder[80], buf[20];

         trans_man_stamp(brd_folder, 'F', &ghdr, fpath, atoi(time_str));
         ghdr.xmode = GEM_FOLDER;
         strcpy(ghdr.owner, item.owner);
         strcpy(ghdr.title, item.title + 3);
         rec_add(brd_folder, &ghdr, sizeof(ghdr));

         strcpy(tmp_folder, brd_folder);
         strcpy(tmp_path, man_path);
         ptr = brd_folder;
         str_lower(buf, old->userid);
         sprintf(brd_folder, BBSHOME"/usr/%c/%s/gem/%c/%s",
                 tolower(*old->userid), buf,
                 radix32[atoi(time_str) & 31], ghdr.xname);
         ptr = strrchr(man_path, '.');
         sprintf(ptr, "%s/.DIR", item.filename);
         transfer_man(old, man_path, brd_folder);
         strcpy(brd_folder, tmp_folder);
         strcpy(man_path, tmp_path);
      }

      num++;
   }
}
#endif

void
creat_dirs(old)
   userec *old;
{
   ACCT new;
   SCHEMA slot;
   int fd;
   char usr_path[80], buf[20];

   memset(&new, 0, sizeof(new));
   memset(&slot, 0, sizeof(slot));

   strcpy(new.userid, old->userid);
   strcpy(new.passwd, old->passwd);
   strcpy(new.realname, old->realname);
   strcpy(new.username, old->username);
   new.numlogins = old->numlogins;
   new.numposts = old->numposts;
   new.firstlogin = old->firstlogin;
   new.lastlogin = old->lastlogin;
   strcpy(new.lasthost, old->lasthost);
   strcpy(new.email, old->email);
   strcpy(new.address, old->address);
   strcpy(new.justify, old->justify);
   new.year = old->year;
   new.month = old->month;
   new.day = old->day;
   new.sex = old->sex;
   new.exemailbox = old->exmailbox;
   new.exemailk = old->test5;
   new.water = old->test4;
   new.tcheck = new.tvalid = time(0);
   new.ufo = UFO_COLOR | UFO_MOVIE | UFO_BNOTE;

   if(old->userlevel & 000001)   new.userlevel |= PERM_BASIC;
   if(old->userlevel & 000002)   new.userlevel |= PERM_CHAT;
   if(old->userlevel & 000004)   new.userlevel |= PERM_PAGE;
   if(old->userlevel & 000010)   new.userlevel |= PERM_POST;
   if(old->userlevel & 000020)   new.userlevel |= PERM_VALID;
   if(old->userlevel & 000040)   new.userlevel |= PERM_MBOX;
   if(old->userlevel & 000100)   new.userlevel |= PERM_CLOAK;
   if(old->userlevel & 000200)   new.userlevel |= PERM_SEECLOAK;
   if(old->userlevel & 000400)   new.userlevel |= PERM_XEMPT;
   if(old->userlevel & 001000)   new.userlevel |= PERM_DENYPOST;
   if(old->userlevel & 002000)   new.userlevel |= PERM_BM;
   if(old->userlevel & 004000)   new.userlevel |= PERM_ACCOUNTS;
   if(old->userlevel & 010000)   new.userlevel |= PERM_CHATROOM;
   if(old->userlevel & 020000)   new.userlevel |= PERM_BOARD;
   if(old->userlevel & 040000)   new.userlevel |= PERM_SYSOP;

   slot.uptime = time(0);
   strcpy(slot.userid, old->userid);

   fd = open(FN_SCHEMA, O_RDWR | O_CREAT, 0600);
   new.userno = uniq_userno(fd);
   write(fd, &slot, sizeof(slot));
   close(fd);

   str_lower(buf, new.userid);
   sprintf(usr_path, BBSHOME"/usr/%c/%s",
      tolower(*new.userid), buf);
   mkdir(usr_path, 0700);
   strcat(usr_path, "/@");
   mkdir(usr_path, 0700);

   sprintf(usr_path, BBSHOME"/usr/%c/%s/.ACCT",
      tolower(*new.userid), buf);
   fd = open(usr_path, O_WRONLY | O_CREAT, 0600);
   write(fd, &new, sizeof(cuser));
   close(fd);
}

void
transfer_sig(old)
   userec *old;
{
   int fd, fd1;
   int l, m, n;
   char ch, RETURN = '\n';
   char f_sig[80], f_sign[80], buf[20];

   str_lower(buf, old->userid);
   sprintf(f_sign, BBSHOME"/usr/%c/%s/sign", tolower(*old->userid), buf);
   if(fd = open(f_sign, O_WRONLY | O_CREAT | O_TRUNC, 0644))
   {
      for(m = 1; m <= 3; m++)                   /* 3.0 只有三個簽名 */
      {
         sprintf(f_sig, OLD_BBSHOME"/home/%s/sig.%d", old->userid, m);
         if(dashf(f_sig) && (fd1 = open(f_sig, O_RDONLY)))
         {
            n = l = 0;
            while(read(fd1, &ch, sizeof(ch)))
            {
               if(ch == RETURN)
                  l++;
               write(fd, &ch, sizeof(ch));
            }
            while(n++ < MAXSIGLINES - l)
               write(fd, &RETURN, 1);
            close(fd1);
         }
      }
      close(fd);
   }

   return;
}

void
copy_file(old, file)
   userec *old;
   char *file;
{
   char cmd[256];

   sprintf(cmd, OLD_BBSHOME"/home/%s/%s", old->userid, file);
   if(dashf(cmd))
   {
      char buf[20];

      str_lower(buf, old->userid);
      sprintf(cmd, "cp "OLD_BBSHOME"/home/%s/%s "BBSHOME"/usr/%c/%s/%s",
         old->userid, file, tolower(*old->userid), buf, file);
      system(cmd);
   }
   return;
}

void
transusr()
{
   int num = 1;
   userec user;
   char userhome[80];

   while(get_record(FN_PASSWD, &user, sizeof(user), num) != -1)
   {
      printf("%s => ", user.userid);
      usr_fpath(userhome, user.userid, NULL);
      if(dashd(userhome))
      {
         printf("new home exists\n");
         num++;
         continue;
      }
      sprintf(userhome, OLD_BBSHOME"/home/%s", user.userid);
      if(fopen(userhome, "r") == NULL || bad_user_id(user.userid))
      {
         printf("bad id or old home not exists\n");
         num++;
         continue;
      }
      printf("transfering => ", user.userid);
      creat_dirs(&user);
      transfer_mail(&user);

#ifdef HAVE_PERSONAL_GEM
      sprintf(userhome, OLD_BBSHOME"/home/%s/man", user.userid);
      if(dashd(userhome))
      {
         char gem_folder[80], buf[20];

         str_lower(buf, user.userid);
         sprintf(gem_folder, BBSHOME"/usr/%c/%s/gem",
            tolower(*user.userid), buf);
         mak_dirs(gem_folder);
         strcat(gem_folder, "/.DIR");
         sprintf(userhome, OLD_BBSHOME"/home/%s/man/.DIR", user.userid);
         transfer_man(&user, userhome, gem_folder);
      }
#endif

      transfer_sig(&user);
      copy_file(&user, "plans");

      printf("transfer complete\n\n");

      num++;
   }

   return;
}

main(argc, argv)
   int argc;
   char *argv[];
{
   if(!fopen(FN_PASSWD, "r"))
   {
      printf("ERROR! Can't open %s\n", FN_PASSWD);
      exit(1);
   }
   if(!fopen(OLD_BBSHOME"/home", "r"))
   {
      printf("ERROR! Can't open %s\n", OLD_BBSHOME"/home");
      exit(1);
   }

   transusr();

   exit(0);
}

