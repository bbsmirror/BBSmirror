/*-------------------------------------------------------*/
/* util/transbrd.c      by ernie@micro8.ee.nthu.edu.tw   */
/*-------------------------------------------------------*/
/* target : Maple Sob 2.36 至 Maple 3.02 看板轉換        */
/*          .BOARDS => .BRD                              */
/* update : 98/06/14                                     */
/*-------------------------------------------------------*/
/* syntax : transbrd target_board                        */
/*-------------------------------------------------------*/

/*
   1. 設定 OLD_BBSHOME, FN_BOARD, ANONYMOUS_ID, ANONYMOUS_NAME
   2. Sob 看板分類(boardheader.title 前 4 bytes)捨棄(line 233)
   3. 投票不轉換
   4. 進板畫面 copy
   5. 如有需要請 chmod 644 `find PATH -perm 600`
   6. 開 gem 目錄 gem/target_board/? 但不轉換 gem
   7. 不會更新 bshm，使用後請自行更新
   8. 轉換後請手動設看板權限

   ps. Use on ur own risk.
*/

#include "bbs.h"

#define OLD_BBSHOME     "/home/oldbbs"          /* 2.36 */
#define FN_BOARD        "/home/oldbbs/.BOARDS"  /* 2.36 */

#define ANONYMOUS_ID    "秘密客"                /* 匿名 ID */
#define ANONYMOUS_NAME  "猜猜我是誰? ^o^"       /* 匿名暱稱 */

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
/* BOARDS struct : 128 bytes                             */
/* ----------------------------------------------------- */

struct boardheader
{
  char brdname[IDLEN + 1];      /* bid */
  char title[BTLEN + 1];
  char BM[IDLEN * 3 + 3];       /* BMs' uid, token '/' */
  char pad[11];
  time_t bupdate;               /* note update time */
  char pad2[3];
  uschar bvote;                 /* Vote flags */
  time_t vtime;                 /* Vote close time */
  usint level;
};
typedef struct boardheader boardheader;

/* ----------------------------------------------------- */
/* 2.36 functions                                        */
/* ----------------------------------------------------- */

/* Case Independent strncmp */

int
ci_strncmp(s1, s2, n)
  register char *s1, *s2;
  register int n;
{
  register char c1, c2;
  register int diff;

  do
  {
    c1 = *s1++;
    if (c1 >= 'A' && c1 <= 'Z')
      c1 |= 32;

    c2 = *s2++;
    if (c2 >= 'A' && c2 <= 'Z')
      c2 |= 32;

    if (diff = c1 - c2)
      return (diff);
  } while (--n && c1);

  return 0;
}

int
cmpbnames(bname, brec)
  char *bname;
  boardheader *brec;
{
  return (!ci_strncmp(bname, brec->brdname, sizeof(brec->brdname)));
}

int
search_record(fpath, rptr, size, fptr, farg)
  char *fpath;
  char *rptr;
  int size;
  int (*fptr) ();
  int farg;
{
  int fd;
  int id = 1;

  if ((fd = open(fpath, O_RDONLY, 0)) == -1)
    return 0;
  while (read(fd, rptr, size) == size)
  {
    if ((*fptr) (farg, rptr))
    {
      close(fd);
      return id;
    }
    id++;
  }
  close(fd);
  return 0;
}

int
get_record(fpath, rptr, size, id)
  char *fpath;
  char *rptr;
  int size, id;
{
  int fd;

  if ((fd = open(fpath, O_RDONLY, 0)) != -1)
  {
    if (lseek(fd, (off_t)size * (id - 1), SEEK_SET) != -1)
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

char *str_board_file = OLD_BBSHOME"/boards/%s/%s";
char *str_dotdir = ".DIR";

void
setbfile(buf, boardname, fname)
  char *buf, *boardname, *fname;
{
  sprintf(buf, str_board_file, boardname, fname);
}

/*-------------------------------------------------------*/

char radix32[32] = {
  '0', '1', '2', '3', '4', '5', '6', '7',
  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
  'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
  'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
};


void
trans_hdr_stamp(folder, t, hdr, fpath)
  char *folder;
  time_t t;
  HDR *hdr;
  char *fpath;
{
   FILE *fp;
   char *fname, *family;
   int rc;

   fname = fpath;
   while (rc = *folder++)
   {
      *fname++ = rc;
      if (rc == '/')
         family = fname;
   }
   fname = family + 1;
   *fname++ = '/';
   *fname = 'A';

   for (;;)
   {
      *family = radix32[t & 31];
      archiv32(t, fname);

      if(fp = fopen(fpath, "r"))
      {
         fclose(fp);
         t++;
      }
      else
      {
         memset(hdr, 0, sizeof(HDR));
         hdr->chrono = t;
         str_stamp(hdr->date, &hdr->chrono);
         strcpy(hdr->xname, --fname);
         break;
      }
   }

   return;
}

void
transbrd(bh)
   boardheader *bh;
{
   BRD newboard;
   HDR post;
   FILE *fp;
   fileheader fh;
   char folder[80], fpath[80], o_dot_dir[80], time_str[10], buf[256];
   int num;

   sprintf(fpath, BBSHOME"/brd/%s", bh->brdname);
   if(fp = fopen(fpath, "r"))
   {
      printf("%s has already exist! Please check it.\n");
      fclose(fp);
      exit(1);
   }

   /* 開新目錄 */

   memset(&newboard, 0, sizeof(newboard));
   strncpy(newboard.brdname, bh->brdname, IDLEN + 1);
   strncpy(newboard.title, bh->title + 4, BTLEN + 1); /* 2.36 title 有分類 */
   strncpy(newboard.BM, bh->BM, BMLEN + 1);
   time(&newboard.bstamp);

   if ((num = rec_num(FN_BRD, sizeof(newboard))) >= 0)
   {
      rec_put(FN_BRD, &newboard, sizeof(newboard), num);
      printf("Record created in %s\n", FN_BRD);
   }
   else if (rec_add(FN_BRD, &newboard, sizeof(newboard)) < 0)
   {
      printf("ERROR! Can't build new record in %s\n", FN_BRD);
      exit(1);
   }

   sprintf(fpath, "gem/brd/%s", newboard.brdname);
   printf("Creating %s dirs...\n", fpath);
   mak_dirs(fpath);
   printf("Creating %s dirs...\n\n", fpath + 4);
   mak_dirs(fpath + 4);

   /* 文章檔名 */

   sprintf(o_dot_dir, str_board_file, bh->brdname, ".DIR");
   if(!(fp = fopen(o_dot_dir, "r")))
   {
      printf("ERROR! Can't open %s\n", o_dot_dir);
      fclose(fp);
      exit(1);
   }

   brd_fpath(folder, newboard.brdname, ".DIR");
   num = 1;
   while(get_record(o_dot_dir, &fh, sizeof(fh), num) != -1)
   {
      memset(&post, 0, sizeof(post));
      strncpy(time_str, fh.filename + 2, 9);
      time_str[9] = '\0';
      trans_hdr_stamp(folder, (time_t)atoi(time_str), &post, fpath);
      strcpy(post.owner, fh.owner);
      strcpy(post.title, fh.title);

      if(fh.filemode & 0x2)                     /* FILE_MARKED 0x2 */
         post.xmode |= POST_MARKED;

      if(!strcmp(fh.owner, ANONYMOUS_ID))
         strcpy(post.nick, ANONYMOUS_NAME);

      if (!rec_add(folder, &post, sizeof(HDR)))
      {
         char buf1[80];

         setbfile(buf1, bh->brdname, fh.filename);
         sprintf(buf, "cp %s "BBSHOME"/%s", buf1, fpath);
         printf("%s -> "BBSHOME"/%s\n", buf1, fpath);
         system(buf);
      }

      num++;
   }

   {  /* 進板畫面 */
      char buf1[80];

      setbfile(buf1, bh->brdname, "notes");
      brd_fpath(fpath, newboard.brdname, "note");
      sprintf(buf, "cp %s "BBSHOME"/%s", buf1, fpath);
      printf("%s -> "BBSHOME"/%s\n", buf1, fpath);
      system(buf);
   }
}

main(argc, argv)
   int argc;
   char *argv[];
{
   boardheader bh;

   if (argc < 2)
   {
      printf("Usage: %s target_board\n", argv[0]);
      exit(0);
   }

   if(fopen(FN_BOARD, "r") == NULL)
   {
      printf("ERROR! Can't open %s\n", FN_BOARD);
      exit(1);
   }

   if(!search_record(FN_BOARD, &bh, sizeof(bh), cmpbnames, (int)argv[1]))
   {
      printf("ERROR! Can't find %s in %s\n", argv[1], FN_BOARD);
      exit(1);
   }

   transbrd(&bh);

   exit(0);
}
