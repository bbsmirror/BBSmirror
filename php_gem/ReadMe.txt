
	這是 php.twbbs.org 的 plan 版精華區的壓縮檔.
	以下是 .DIR 的結構, 希望對大家有幫助 :)

typedef struct
{
  char filename[FNLEN];         /* M.9876543210.A */
  char savemode;                /* file save mode */
  char owner[IDLEN + 2];        /* uid[.] */
  char date[6];                 /* [02/02] or space(5) */
  char title[TTLEN + 1];
  uschar filemode;              /* must be last field @ boards.c */
}	fileheader;

