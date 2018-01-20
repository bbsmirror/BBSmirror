/*
  NoCeM-INNBBSD
  Yen-Ming Lee <leeym@civil.ncku.edu.tw>
  $Id: nocem.c,v 1.10 1999/05/20 13:41:32 stb Exp $
*/

#ifndef NOCEM_H
#define NOCEM_H

typedef struct ncmperm_t
{
  char *issuer;
  char *type;
  int perm;
} ncmperm_t;

ncmperm_t *NCMPERM=NULL, **NCMPERM_BYTYPE=NULL;
static char *NCMPERM_BUF;
int NCMCOUNT = 0;

#define TEXT    0
#define NCMHDR  1
#define NCMBDY  2

#define NOPGP   -1
#define PGPGOOD 0
#define PGPBAD  1
#define PGPUN   2

#define P_OKAY  0
#define P_FAIL  -1
#define P_UNKNOWN       -2
#define P_DISALLOW      -3

#define STRLEN          80
#define MAXSPAMMID      1000

#define LeeymBBS        "bbs.civil.ncku.edu.tw"
#define LeeymEMAIL      "leeym@civil.ncku.edu.tw"
#define NCMINNBBSVER    "NoCeM-INNBBSD-0.51"

extern char NCMVER[];
extern char ISSUER[];
extern char TYPE[];
extern char ACTION[];
extern char NCMID[];
extern char COUNT[];
extern char THRESHOLD[];
extern char KEYID[];
extern char SPAMMID_NOW[];
extern char SPAMMID[][];

#endif /* NOCEM_H */
