/*-------------------------------------------------------*/
/* util/bbsqmail.c      ( NTHU CS MapleBBS Ver 2.36 )    */
/*-------------------------------------------------------*/
/* target : (1) qmail-command(filter) for bbs mail       */
/* update : 97/09/15                                     */
/*-------------------------------------------------------*/
/* from woju's fromzero 2.1 				 */
/* patch : skybinary.bbs@starbbs.net 			 */

#include "bbs.h"
#include "cache.c"

#define STRCPY(dst, src) sprintf(dst, "%.*s", sizeof(dst)  - 1, src)


userec record;

#define JUNK            0
#define NET_SAVE        1
#define LOCAL_SAVE      2

int mymode = JUNK;


#define LOG_FILE        "log/mailog"


/* ----------------------------------------------------- */
/* buffered I/O for stdin                                */
/* ----------------------------------------------------- */


#define POOL_SIZE       8192
#define LINE_SIZE       256
#define MAXHEADER       50

char pool[POOL_SIZE];
char mybuf[LINE_SIZE];
char header[MAXHEADER + 1][LINE_SIZE];
char myto[LINE_SIZE + 10], myfrom[LINE_SIZE + 10];
int pool_size = POOL_SIZE;
int pool_ptr = POOL_SIZE;
int headerline = 0;


readline(char* buf)
{
   register char ch;
   register int len, bytes;

   len = bytes = 0;
   do {
      if (pool_ptr >= pool_size) {
         if (pool_size = fread(pool, 1, POOL_SIZE, stdin))
            pool_ptr = 0;
         else
            break;
      }
      ch = pool[pool_ptr++];
      bytes++;

      if (ch == '\r')
         continue;

      buf[len++] = ch;
   } while (ch != '\n' && len < (LINE_SIZE - 1));

   buf[len] = 0;
   if (headerline >= 0 && headerline < MAXHEADER) {
      strncpy(header[headerline++], buf, sizeof(*header));
   }
   return bytes;
}


/* ----------------------------------------------------- */
/* record mailog for management                      */
/* ----------------------------------------------------- */

mailog(char* mode, char* msg)
{
   FILE *fp;

   if (fp = fopen(LOG_FILE, "a")) {
      time_t now;
      struct tm *p;

      time(&now);
      p = localtime(&now);
      fprintf(fp, "%02d/%02d/%02d %02d:%02d:%02d <%s> %s\n",
         p->tm_year, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min,
         p->tm_sec, mode, msg);
      fclose(fp);
   }
}


junk(char* reason)
{
   FILE* fp;
   int i;
   char msgbuf[256];

   sprintf(msgbuf, "junk: %.100s, from <%.100s>", reason, getenv("SENDER"));
   mailog("bbsqmail", msgbuf);
   if (fp = popen("bin/bbspost junk", "w")) {
      for (i = 0; i < headerline; i++)
         fputs(header[i], fp);
      if (headerline >= MAXHEADER)
         fputs(mybuf, fp);
      headerline = -1;
      while (readline(mybuf))
         fputs(mybuf, fp);
      pclose(fp);
   }
   return 0;
}

mail2bbs(char* userid)
{
   FILE* fp;
   int i;
   char msgbuf[256];

   sprintf(msgbuf, "bin/bbsmail %s", userid);
   if (fp = popen(msgbuf, "w")) {
      for (i = 0; i < headerline; i++)
         fputs(header[i], fp);
      headerline = -1;
      while (readline(mybuf))
         fputs(mybuf, fp);
      pclose(fp);
   }
   return 0;
}


bbsqmail()
{
   int dirty;
   char *ip, *ptr;
   char userid[IDLEN + 1];
   int c;

   /* parse header */

   while (!isalpha(c = getc(stdin)))
      ;
   ungetc(c, stdin);

   readline(mybuf);

   dirty = *myto = *myfrom = 0;
   if (ip = getenv("SENDER"))
      STRCPY(myfrom, ip);

   STRCPY(myto, getenv("EXT"));
   while (!*myto || !*myfrom) {
      if (*mybuf == '\n')
         return junk("no to-addr or from-addr");
      else if (!*myto && (!strncasecmp(mybuf, "Delivered-To:", 13) ||
                          !strncasecmp(mybuf, "To:", 3))) {
         if ((ip = strchr(mybuf, '<')) && (ptr = strrchr(ip, '>'))) {
            *ptr = 0;
            STRCPY(myto, ++ip);
         }
         else {
            strtok(mybuf, " \t\n\r");
            if (ip = strtok(0, " \t\n\r"))
               STRCPY(myto, ip);
            else
               return junk("invalid to-addr");
         }
      }
      else if (!*myfrom && !strncasecmp(mybuf, "From:", 5)) {
         if ((ip = strchr(mybuf, '<')) && (ptr = strrchr(ip, '>'))) {
            *ptr = 0;
            STRCPY(myfrom, ++ip);
         }
         else {
            strtok(mybuf, " \t\n\r");
            if (ip = strtok(0, " \t\n\r"))
               STRCPY(myfrom, ip);
            else
               return junk("invalid from-addr");
         }
      }
      if ((++dirty >= MAXHEADER) || !readline(mybuf))
         return junk("header to large");
   }
   STRCPY(userid, myto);
   for (c = 0; c < IDLEN && isalnum(userid[c]); c++)
      ;
   userid[c] = 0;
   if (!*userid || invaliduser(userid) || !searchuser(userid)) {
      printf("no such user <%s>", userid);
      return 100;
/*
      char buf[200];

      sprintf(buf, "no such user <%s>", userid);
      return junk(buf);
*/
   }
   return mail2bbs(userid);
}

invaliduser(char* userid)
{
   if (strcasecmp(userid, "guest") == 0)
      return 1;
   return 0;
}

main()
{
   chdir(BBSHOME);
   setgid(BBSGID);
   setuid(BBSUID);

   return bbsqmail();
}
