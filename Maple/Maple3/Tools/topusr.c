#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bbs.h"

#define	TOPLOGINS	(0)
#define	TOPPOSTS	(1)

#define	TOPNUM		(20)
#define	TOPNUM_HALF	(TOPNUM/2)

typedef struct
{
  char userid[IDLEN + 1];
  char username[24];
  int num;
} DATA;

DATA toplogins[TOPNUM], topposts[TOPNUM];

int
sort_compare(p1, p2)
  const void *p1;
  const void *p2;
{
  DATA *a1, *a2;

  a1 = (DATA *) p1;
  a2 = (DATA *) p2;

  return (a2->num-a1->num);
}

DATA *
findmin(src)
  DATA *src;
{
  int i;
  DATA *p;

  p = src;
  for (i = 0; i < TOPNUM; i++)
    if (src[i].num < p->num)
      p = src+i;
  return (p);
}

void
merge_id_nick(dst, userid, nick)
  char *dst;
  char *userid;
  char *nick;
{
  if (*userid)
  {
    sprintf(dst, "%s (%s)", userid, nick);

    if (strlen(dst) > 25)
      dst[25] = 0;
  }
  else
    dst[0] = NULL;
}

void
write_data(title, data)
  char *title;
  DATA *data;
{
  char buf[256];
  int i;

  sprintf(buf, "[1;32m%%%ds[m\n\n", 40+strlen(title)/2);
  printf(buf, title);

  puts("[1;31m¦W¦¸[m  [1;33mID[m ([1;34mNickname[m)  \
           [1;36m¦¸¼Æ[m    [1;31m¦W¦¸[m  [1;33mID[m ([1;34m\
Nickname[m)             [1;36m¦¸¼Æ[m\n-----------------------------\
-------    ------------------------------------");

  for (i = 0; i < TOPNUM_HALF; i++)
  {
    char buf1[80], buf2[80];

    merge_id_nick(buf1, data[i].userid, data[i].username);
    merge_id_nick(buf2, data[i+TOPNUM_HALF].userid,
		  data[i+TOPNUM_HALF].username);

    printf("[%2d]  %-25s%5d    [%2d]  %-25s%5d\n", i, buf1, data[i].num,
	   i+TOPNUM_HALF, buf2, data[i+TOPNUM_HALF].num);
  }

  printf("\n");
}

int
main()
{
  char c;

  memset(&toplogins, 0, sizeof(toplogins));
  memset(&topposts, 0, sizeof(topposts));

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
      DATA *p;
      int fd;

      if (de->d_name[0] <= ' ' || de->d_name[0] == '.')
	continue;

      sprintf(buf, "%s/.ACCT", de->d_name);
      if ((fd = open(buf, O_RDONLY)) < 0)
	continue;

      read(fd, &cuser, sizeof(cuser));
      close(fd);

      if ((p = findmin(&toplogins))->num < cuser.numlogins)
      {
	strncpy(p->userid, cuser.userid, IDLEN);
	strncpy(p->username, cuser.username, 24);
	p->num = cuser.numlogins;
      }

      if ((p = findmin(&topposts))->num < cuser.numposts)
      {
	strncpy(p->userid, cuser.userid, IDLEN);
	strncpy(p->username, cuser.username, 24);
	p->num = cuser.numposts;
      }
    }
  }

  qsort(toplogins, TOPNUM, sizeof(DATA), sort_compare);
  qsort(topposts, TOPNUM, sizeof(DATA), sort_compare);

  write_data("¤W¯¸¦¸¼Æ±Æ¦æº]", &toplogins);
  write_data("Äé¤ô¦¸¼Æ±Æ¦æº]", &topposts);
}
