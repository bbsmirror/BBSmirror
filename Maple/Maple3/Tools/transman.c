/*-------------------------------------------------------*/
/* util/transman.c      by ernie@micro8.ee.nthu.edu.tw   */
/*-------------------------------------------------------*/
/* target : Maple Sob 2.36 至 Maple 3.02 精華區轉換      */
/* update : 98/06/15                                     */
/*-------------------------------------------------------*/
/* syntax : transman target_board                        */
/*-------------------------------------------------------*/

/*
   1. 設定 OLD_BBSHOME
   2. 程式不開目錄，使用前先確定 gem/target_board/? 目錄存在
      if not，先開新板 or transbrd
   3. 只轉 M.*.A 及 D.*.A，其他 link 不轉換
   4. 如有需要請先 chmod 644 'find PATH -perm 600`

   ps. User on ur own risk. :p
*/

#include "bbs.h"

#define OLD_BBSHOME     "/home/oldbbs"             /* 2.36 */

char *target;

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

void
transman(man_path, brd_folder)
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
         printf("=> %s\n", fpath);
         system(buf);

      }
      else if(*item.filename == 'D')
      {
         char tmp_path[256], tmp_folder[80];

         trans_man_stamp(brd_folder, 'F', &ghdr, fpath, atoi(time_str));
         ghdr.xmode = GEM_FOLDER;
         strcpy(ghdr.owner, item.owner);
         strcpy(ghdr.title, item.title + 3);
         printf("=> %s\n", fpath);
         rec_add(brd_folder, &ghdr, sizeof(ghdr));

         strcpy(tmp_folder, brd_folder);
         strcpy(tmp_path, man_path);
         ptr = brd_folder;
         sprintf(brd_folder, BBSHOME"/gem/brd/%s/%c/%s",
                 target, radix32[atoi(time_str) & 31], ghdr.xname);
         ptr = strrchr(man_path, '.');
         sprintf(ptr, "%s/.DIR", item.filename);
         transman(man_path, brd_folder);
         strcpy(brd_folder, tmp_folder);
         strcpy(man_path, tmp_path);
      }

      num++;
   }
}

main(argc, argv)
  int argc;
  char *argv[];
{
   char man_path[80], brd_folder[80];

   if(argc < 2)
   {
      printf("Usage: %s target_board\n", argv[0]);
      exit(0);
   }

   sprintf(man_path, OLD_BBSHOME"/man/boards/%s/.DIR", argv[1]);
   if(fopen(man_path, "r") == NULL)
   {
      printf("ERROR! Can't open %s\n", man_path);
      exit(1);
   }
   sprintf(brd_folder, BBSHOME"/gem/brd/%s", argv[1]);
   if(fopen(brd_folder, "r") == NULL)
   {
      printf("ERROR! %s not exist. New it first.\n", brd_folder);
      exit(1);
   }

   target = argv[1];
   sprintf(brd_folder, BBSHOME"/gem/brd/%s/.DIR", target);
   sprintf(man_path, OLD_BBSHOME"/man/boards/%s/.DIR", target);
   transman(man_path, brd_folder);

   exit(0);
}

