/*-------------------------------------------------------*/
/* util/poststat.c      ( NTHU CS MapleBBS Ver 2.36 )    */
/*-------------------------------------------------------*/
/* target : ²Î­p¤µ¤é¡B¶g¡B¤ë¡B¦~¼öªù¸ÜÃD                 */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/

// Fix for MagicBBS by Magi 98/01

#include <stdio.h>
#include <time.h>


char *myfile[] = {"day", "week", "month", "year"};
int mycount[4] = {7, 4, 12};
int mytop[] = {10, 50, 100, 100};
char *mytitle[] = {"¤é¤Q", "¶g¤­¤Q", "¤ë¦Ê", "¦~«×¦Ê"};


#define HASHSIZE 1024
#define TOPCOUNT 200


struct postrec
{
  char author[13];              /* author name */
  char board[13];               /* board name */
  char title[66];               /* title name */
  time_t date;                  /* last post's date */
  int number;                   /* post number */
  struct postrec *next;         /* next rec */
}      *bucket[HASHSIZE];


/* 100 bytes */
struct posttop
{
  char author[13];              /* author name */
  char board[13];               /* board name */
  char title[66];               /* title name */
  time_t date;                  /* last post's date */
  int number;                   /* post number */
}       top[TOPCOUNT], postlog;


int
hash(key)
  char *key;
{
  int i, value = 0;

  for (i = 0; key[i] && i < 80; i++)
    value += key[i] < 0 ? -key[i] : key[i];

  value = value % HASHSIZE;
  return value;
}


/* ---------------------------------- */
/* hash structure : array + link list */
/* ---------------------------------- */


void
search(t)
  struct posttop *t;
{
  struct postrec *p, *q, *s;
  int i, found = 0;

  i = hash(t->title);
  q = NULL;
  p = bucket[i];
  while (p && (!found))
  {
    if (!strcmp(p->title, t->title) && !strcmp(p->board, t->board))
      found = 1;
    else
    {
      q = p;
      p = p->next;
    }
  }
  if (found)
  {
    p->number += t->number;
    if (p->date < t->date)      /* ¨ú¸ûªñ¤é´Á */
      p->date = t->date;
  }
  else
  {
    s = (struct postrec *) malloc(sizeof(struct postrec));
    memcpy(s, t, sizeof(struct posttop));
    s->next = NULL;
    if (q == NULL)
      bucket[i] = s;
    else
      q->next = s;
  }
}


int
sort(pp, count)
  struct postrec *pp;
{
  int i, j;

  for (i = 0; i <= count; i++)
  {
    if (pp->number > top[i].number)
    {
      if (count < TOPCOUNT - 1)
        count++;
      for (j = count - 1; j >= i; j--)
        memcpy(&top[j + 1], &top[j], sizeof(struct posttop));

      memcpy(&top[i], pp, sizeof(struct posttop));
      break;
    }
  }
  return count;
}


void
load_stat(fname)
  char *fname;
{
  FILE *fp;

  if (fp = fopen(fname, "r"))
  {
    int count = fread(top, sizeof(struct posttop), TOPCOUNT, fp);
    fclose(fp);
    while (count)
      search(&top[--count]);
  }
}


void
poststat(mytype)
  int mytype;
{
  static char *logfile = ".post";
  static char *oldfile = ".post.old";

  FILE *fp;
  char buf[40],buf2[13], curfile[40] = "etc/posts/day.0", *p;
  struct postrec *pp;
  int i, j;

  if (mytype < 0)
  {
    /* --------------------------------------- */
    /* load .post and statictic processing     */
    /* --------------------------------------- */

    remove(oldfile);
    rename(logfile, oldfile);
    if ((fp = fopen(oldfile, "r")) == NULL)
      return;
    mytype = 0;
    load_stat(curfile);

    while (fread(top, sizeof(struct posttop), 1, fp))
      search(top);
    fclose(fp);
  }
  else
  {
    /* ---------------------------------------------- */
    /* load previous results and statictic processing */
    /* ---------------------------------------------- */

    i = mycount[mytype];
    p = myfile[mytype];
    while (i)
    {
      sprintf(buf, "etc/posts/%s.%d", p, i);
      sprintf(curfile, "etc/posts/%s.%d", p, --i);
      load_stat(curfile);
      rename(curfile, buf);
    }
    mytype++;
  }

  /* ---------------------------------------------- */
  /* sort top 100 issue and save results            */
  /* ---------------------------------------------- */

  memset(top, 0, sizeof(top));
  for (i = j = 0; i < HASHSIZE; i++)
  {
    for (pp = bucket[i]; pp; pp = pp->next)
    {

#ifdef  DEBUG
      printf("Title : %s, Board: %s\nPostNo : %d, Author: %s\n"
        ,pp->title
        ,pp->board
        ,pp->number
        ,pp->author);
#endif

      j = sort(pp, j);
    }
  }

  p = myfile[mytype];
  sprintf(curfile, "etc/posts/%s.0", p);
  if (fp = fopen(curfile, "w"))
  {
    fwrite(top, sizeof(struct posttop), j, fp);
    fclose(fp);
  }

  sprintf(curfile, "etc/posts/%s", p);
  if (fp = fopen(curfile, "w"))
  {
    fprintf(fp, "\t\t[1;34m-----[37m=====[41m ¥»%s¤j¼öªù¸ÜÃD [40m=====[34m-----[0m\n\n", mytitle[mytype]);

    i = mytop[mytype];
    if (j > i)
      j = i;
    for (i = 0; i < j; i++)
    {
      strcpy(buf, ctime(&top[i].date));
      buf[20] = NULL;
      p = buf + 4;
      strncpy(buf2,top[i].board,13);
      buf2[13]=0;
      fprintf(fp,
        "[1;37m²Ä[1;31m%3d[37m ¦W [37m«H°Ï : [33m%-16s[37m¡i[32m%s[37m¡j[36m%4d [37m½g[35m%+16s\n"
        "     [37m¼ÐÃD : [1;44;37m%-60.60s[40m\n"
        ,i + 1, buf2, p, top[i].number, top[i].author, top[i].title);
    }
    fclose(fp);
  }

  /* free statistics */

  for (i = 0; i < HASHSIZE; i++)
  {
    for (pp = bucket[i]; pp; pp = pp->next)
      free(pp);
    bucket[i] = NULL;
  }
}


main(argc, argv)
  char *argv[];
{
  time_t now;
  struct tm *ptime;

  if (argc < 2)
  {
    printf("Usage:\t%s bbshome [day]\n", argv[0]);
    return (-1);
  }

  chdir(argv[1]);

  if (argc == 3)
  {
    poststat(atoi(argv[2]));
    return (0);
  }

  time(&now);
  ptime = localtime(&now);
  if (ptime->tm_hour == 0)
  {
    if (ptime->tm_mday == 1)
      poststat(2);
    if (ptime->tm_wday == 0)
      poststat(1);
    poststat(0);
  }
  poststat(-1);
}
