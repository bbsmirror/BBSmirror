/*-------------------------------------------------------*/
/* acct.c	( NTHU CS MapleBBS Ver 3.00 )		 */
/*-------------------------------------------------------*/
/* target : account / administration routines	 	 */
/* create : 95/03/29				 	 */
/* update : 96/04/05				 	 */
/*-------------------------------------------------------*/


#define	_ADMIN_C_


#include "bbs.h"


extern BCACHE *bshm;


#define STR_PERM      "bctpjm#x--------PTCM--L*B#--ACBS"


/* ----------------------------------------------------- */
/* (.ACCT) 使用者帳號 (account) subroutines		 */
/* ----------------------------------------------------- */


int
acct_load(acct, userid)
  ACCT *acct;
  char *userid;
{
  int fd;

  usr_fpath((char *) acct, userid, fn_acct);
  fd = open((char *) acct, O_RDONLY);
  if (fd >= 0)
  {
    read(fd, acct, sizeof(ACCT));
    close(fd);
  }
  return fd;
}


void
acct_save(acct)
  ACCT *acct;
{
  int fd;
  char fpath[80];

  usr_fpath(fpath, acct->userid, fn_acct);
  fd = open(fpath, O_WRONLY, 0600);	/* fpath 必須已經存在 */
  if (fd >= 0)
  {
    write(fd, acct, sizeof(ACCT));
    close(fd);
  }
}


int
acct_userno(userid)
  char *userid;
{
  int fd;
  int userno;
  char fpath[80];

  usr_fpath(fpath, userid, fn_acct);
  fd = open(fpath, O_RDONLY);
  if (fd >= 0)
  {
    read(fd, &userno, sizeof(userno));
    close(fd);
    return userno;
  }
  return 0;
}


/* ----------------------------------------------------- */
/* name complete for user ID				 */
/* ----------------------------------------------------- */
/* return value :					 */
/* 0 : 使用直接按 enter ==> cancel			 */
/* -1 : bad user id					 */
/* ow.: 傳回該 userid 之 userno				 */
/* ----------------------------------------------------- */


int
acct_get(msg, acct)
  char *msg;
  ACCT *acct;
{
  if (!vget(1, 0, msg, acct->userid, IDLEN + 1, GET_USER))
    return 0;

  if (acct_load(acct, acct->userid) >= 0)
    return acct->userno;

  vmsg(err_uid);
  return -1;
}


/* ----------------------------------------------------- */
/* 設定系統檔案						 */
/* ----------------------------------------------------- */


static void
x_file(mode, xlist, flist)
  int mode;			/* M_XFILES / M_UFILES */
  char *xlist[];		/* description list */
char *flist[];			/* filename list */
{
  int n, i;
  char *fpath, *desc;
  char buf[80];

  move(12, 0);
  clrtobot();
  n = 0;
  while (desc = xlist[n])
  {
    n++;
    move(n + 12, 17);
    prints("(\033[1;36m%d\033[m) %s", n, desc);
    if (mode == M_XFILES)
    {
      move(n + 12, 50); /* Thor.980806: 註解: 印出檔名 */
      outs(flist[n - 1]);
    }
  }

  vget(b_lines, 0, "請選擇檔案編號，或按 [0] 取消：", buf, 3, DOECHO);
  i = atoi(buf);
  if (i <= 0 || i > n)
    return;

  n = vget(b_lines, 36, "(D)刪除 (E)編輯 [Q]取消？", buf, 3, LCECHO);
  if (n != 'd' && n != 'e')
    return;

  fpath = flist[--i];
  if (mode == M_UFILES)
    usr_fpath(buf, cuser.userid, fpath);
  else				/* M_XFILES */
    sprintf(buf, "etc/%s", fpath);

  if (n == 'd')
  {
    unlink(buf);
  }
  else
  {
    vmsg(vedit(buf, NA) ? "原封不動" : "更新完畢");
  } /* Thor.981020: 注意被talk的問題  */
}


int
m_xfile()
{
  static char *desc[] =
  {
    "看板期限",
    "不雅名單",
    "註冊提示畫面",
    "新手上路須知",
    "身份認證信函",
    "身份認證的方法",
    "E-mail post 簡介",
    "廣告/垃圾信名單",          /* lkchu.981201: 線上編輯 mail.acl, 
                                                 但須重跑 bmtad 才能更新 */
    NULL
  };

  static char *path[] =
  {
    "expire.conf",
    "badid",
    "register",
    "newuser",
    "valid",
    "justify",
    "emailpost",
    "mail.acl"
  };

  x_file(M_XFILES, desc, path);
  return 0;
}


/* ----------------------------------------------------- */
/* bit-wise display and setup				 */
/* ----------------------------------------------------- */


static void
bitmsg(msg, str, level)
  char *msg, *str;
  int level;
{
  int cc;

  outs(msg);
  while (cc = *str)
  {
    outc((level & 1) ? cc : '-');
    level >>= 1;
    str++;
  }

  outc('\n');
}


usint
bitset(pbits, count, maxon, msg, perms)
  usint pbits;
  int count;			/* 共有幾個選項 */
  int maxon;			/* 最多可以 enable 幾項 */
  char *msg;
  char *perms[];
{
  int i, j, on;

  extern char radix32[32];

  move(2, 0);
  clrtobot();
  outs(msg);

  for (i = on = 0, j = 1; i < count; i++)
  {
    msg = "□";
    if (pbits & j)
    {
      on++;
      msg = "■";
    }
    move(5 + (i & 15), (i < 16 ? 0 : 40));
    prints("%c %s %s", radix32[i], msg, perms[i]);
    j <<= 1;
  }

  while (i = vans("請按鍵切換設定，或按 [Return] 結束："))
  {
    i -= '0';
    if (i >= 10)
      i -= 'a' - '0' - 10;

    if (i >= 0 && i < count)
    {
      j = 1 << i;
      if (pbits & j)
      {
	on--;
	msg = "□";
      }
      else
      {
	if (on >= maxon)
	  continue;
	on++;
	msg = "■";
      }

      pbits ^= j;
      move(5 + (i & 15), (i < 16 ? 2 : 42));
      outs(msg);
    }
  }
  return (pbits);
}


static usint
setperm(level)
  usint level;
{
  if (cuser.userlevel & PERM_SYSOP)
    return bitset(level, NUMPERMS, NUMPERMS, MSG_USERPERM, perm_tbl);

  /* [帳號管理員] 不能管 SYSOP */

  if (level & PERM_SYSOP)
    return level;

  return bitset(level, NUMPERMS - 4, NUMPERMS - 4, MSG_USERPERM, perm_tbl);
}


/* ----------------------------------------------------- */
/* 帳號管理						 */
/* ----------------------------------------------------- */


static void
bm_list(userid)			/* 顯示 userid 是哪些板的板主 */
  char *userid;
{
  int len, ch;
  BRD *bhdr, *tail;
  char *list;
  extern BCACHE *bshm;

  len = strlen(userid);
  outs("擔任板主：");

  bhdr = bshm->bcache;
  tail = bhdr + bshm->number;

  do
  {
    list = bhdr->BM;
    ch = *list;
    if ((ch > ' ') && (ch < 128))
    {
      do
      {
	if (!str_ncmp(list, userid, len))
	{
	  ch = list[len];
	  if ((ch == 0) || (ch == '/'))
	  {
	    outs(bhdr->brdname);
	    outc(' ');
	    break;
	  }
	}
	while (ch = *list++)
	{
	  if (ch == '/')
	    break;
	}
      } while (ch);
    }
  } while (++bhdr < tail);

  outc('\n');
}


void
acct_show(u, adm)
  ACCT *u;
  int adm;			/* 1: admin 2: reg-form */
{
  int diff;
  usint ulevel;
  char *uid, buf[80];

  clrtobot();

  uid = u->userid;
  if (adm != 2)
    prints("\n代    號：%s", uid);

  prints(
    "\n暱    稱：%s\n"
    "真實姓名：%s\n"
    "居住住址：%s\n"
    "郵件信箱：%s\n",
    u->username,
    u->realname,
    u->address,
    u->email);

  prints("註冊日期：%s", ctime(&u->firstlogin));

  prints("光臨日期：%s", ctime(&u->lastlogin));

  diff = u->staytime / 60;
  prints("上站次數：%d 次 (共 %d 時 %d 分)\n",
    u->numlogins, diff / 60, diff % 60);

  prints("文章數目：%d 篇     ", u->numposts);


  usr_fpath(buf, uid, fn_dir);
  prints("個人信件：%d 封\n", rec_num(buf, sizeof(HDR)));

#ifdef COINAGE
/* mat 981206: 增加錢，姓別，生日的欄位 */
  if(!(u->sex==0))
     prints("性    別：%s      ",((u->sex==1) ? "男寶寶" :  "女寶寶"));
   
  prints("生　　日：19%02d/%02d/%02d\n",u->year,u->month,u->day);
    
/*  prints("金    幣：%-9d  ",u->gold); */
  prints("現    金：%-9d\n",u->money);
     
  prints("金幣存款：%-9d   銀幣存款：%-9d\n",u->bankgold,u->banksilver);
      
#endif

  ulevel = u->userlevel;  
  outs("身分認證：\033[32m");
  if (ulevel & PERM_VALID)
  {
    outs(u->tvalid ? Ctime(&u->tvalid) : "有效期間已過，請重新認證");
  }
  else
  {
    outs("請參考本站公佈欄進行確認，以提昇權限");
  }
  outs("\033[m\n");

  if (adm)
  {
    prints("認證資料：%s\n", u->justify);
    prints("認證地址：%s\n", u->vmail);
    prints("RFC 931 ：%s\n", u->ident);
    prints("上站地點：%s (%d)\n", u->lasthost, u->numemail);
    bitmsg(MSG_USERPERM, STR_PERM, ulevel);
    bitmsg("旗    標：", "amnsEPQFAC", u->ufo);
  }
  else
  {
    diff = (time(0) - ap_start) / 60;
    prints("停留期間：%d 小時 %d 分\n", diff / 60, diff % 60);
  }

  if (adm == 2)
    return;

  /* Thor: 想看看這個 user 是那些版的版主 */

  if (ulevel & PERM_BM)
    bm_list(uid);

#ifdef	NEWUSER_LIMIT
  if (u->lastlogin - u->firstlogin < 3 * 86400)
    outs("\n新手上路：三天後開放權限");
#endif
}


void
acct_setup(u, adm)
  ACCT *u;
  int adm;
{
  ACCT x;
  int i, num;
  char *str, buf[80], pass[PASSLEN];
#ifdef COINAGE
  unsigned long int longnum;
#endif
 

  acct_show(u, adm);
  memcpy(&x, u, sizeof(ACCT));

  if (adm)
  {
    adm = vans("設定 1)資料 2)權限 Q)取消 [Q] ");
    if (adm == '2')
      goto set_perm;

    if (adm != '1')
      return;
  }
  else
  {
    if (vans("修改資料(Y/N)?[N] ") != 'y')
      return;
  }

  move(i = 3, 0);
  clrtobot();

  if (adm)
  {
    str = x.userid;
    for (;;)
    {
      vget(i, 0, "使用者代號(不改請按 Enter)：", str, IDLEN + 1, GCARRY);
      if (!str_cmp(str, u->userid) || !acct_userno(str))
	break;
      vmsg("錯誤！已有相同 ID 的使用者");
    }
  }
  else
  {
    vget(i, 0, "請確認密碼：", buf, PASSLEN, NOECHO);
    if (chkpasswd(u->passwd, buf))
    {
      vmsg("密碼錯誤");
      return;
    }
  }

  i++;
  for (;;)
  {
    if (!vget(++i, 0, "設定新密碼(不改請按 Enter)：", buf, PASSLEN, NOECHO))
      break;

    strcpy(pass, buf);
    vget(i + 1, 0, "檢查新密碼：", buf, PASSLEN, NOECHO);
    if (!strcmp(buf, pass))
    {
      buf[8] = '\0';
      str_ncpy(x.passwd, genpasswd(buf), PASSLEN);
      i++;
      break;
    }
  }

  i++;
  str = x.username;
  do
  {
    vget(i, 0, "暱    稱：", str, sizeof(x.username), GCARRY);
  } while (str_len(str) < 1);

  i++;
  str = x.realname;
  do
  {
    vget(i, 0, "真實姓名：", str, sizeof(x.realname), GCARRY);
  } while (str_len(str) < 4);

  i++;
  str = x.address;
  do
  {
    /* Thor.980730:lkchu patch: 若是 i++ 則會一直往下印 */
    vget(i, 0, "居住地址：", str, sizeof(x.address), GCARRY);
  } while (str_len(str) < 8);

#ifdef COINAGE

  sprintf(buf, "%d", u->sex);
  vget(++i, 0, "性    別：", buf, 2,GCARRY);
  if ((num = atoi(buf)) >= 0)
    x.sex = num;
    
  sprintf(buf, "%02d/%02d/%02d",u->year,u->month,u->day);
  vget(++i, 0, "生    日：", buf, 9,GCARRY);
  x.year =  (buf[0] - '0') * 10 + (buf[1] - '0');
  x.month = (buf[3] - '0') * 10 + (buf[4] - '0');
  x.day =   (buf[6] - '0') * 10 + (buf[7] - '0');

#endif        
  if (adm)
  {
    vget(++i, 0, "認證資料：", x.justify, 44, GCARRY);

    sprintf(buf, "%d", u->numlogins);
    vget(++i, 0, "上線次數：", buf, 10, GCARRY);
    if ((num = atoi(buf)) >= 0)
      x.numlogins = num;

    sprintf(buf, "%d", u->numposts);
    vget(++i, 0, "文章篇數：", buf, 10, GCARRY);
    if ((num = atoi(buf)) >= 0)
      x.numposts = num;
    
#ifdef COINAGE

#if 0
    sprintf(buf, "%d", u->gold);
    vget(++i, 0, "金    幣：", buf,10 ,GCARRY);
    if (((longnum = atol(buf))>=0)  && (longnum <= MAXMONEY))
      x.gold=longnum;
#endif    
    
    sprintf(buf, "%d", u->money);
    vget(++i, 0, "現    金：", buf,10 ,GCARRY);
    if (((longnum = atol(buf))>=0)  &&(longnum <= MAXMONEY))
      x.money=longnum; 
           
    sprintf(buf, "%d", u->bankgold);
    vget(++i, 0, "金幣存款：", buf,10 ,GCARRY);
    if (((longnum = atol(buf))>=0)  &&(longnum <= MAXMONEY))
      x.bankgold=longnum;

    sprintf(buf, "%d", u->banksilver);
    vget(++i, 0, "銀幣存款：", buf,10 ,GCARRY);
    if (((longnum = atol(buf))>=0)  &&(longnum <= MAXMONEY))
      x.banksilver=longnum;
                                    
#endif
                                                                  
    /* lkchu.981201: 特殊用途 :p */
    vget(++i, 0, "認證地址：", x.vmail, 44, GCARRY);
    vget(++i, 0, "上站地點：", x.lasthost, 30, GCARRY);
    vget(++i, 0, "RFC 931 ：", x.ident, 44, GCARRY);

    if (vans("設定權限(Y/N)?[N] ") == 'y')
    {
set_perm:

      i = setperm(num = x.userlevel);

      if (i == num)
      {
	vmsg("取消修改");
	if (adm == '2')
	  return;
      }
      else
      {
	x.userlevel = i;
      }
    }
  }

  if (vans(msg_sure_ny) != 'y')
    return;

  if (adm)
  {
    char buf[256];
    time_t now;
  
    if (str_cmp(u->userid, x.userid))
    { /* Thor: 980806: 特別注意如果 usr每個字母不在同一partition的話會有問題 */
      char dst[80];

      usr_fpath(buf, u->userid, NULL);
      usr_fpath(dst, x.userid, NULL);
      rename(buf, dst);
    }
    /* lkchu.981201: security log */
    time(&now);
    sprintf(buf, "[%s] %12.12s 更動 %12.12s 之權限 %x --> %x\n", Etime(&now),
             cuser.userid, x.userid, u->userlevel, x.userlevel);
    f_cat(FN_SECURITY, buf);
                             
  }
  else
  {
    /* Thor: 這樣即使在線上, 也可以改 userlevel */

    if (acct_load(u, x.userid) >= 0)
      x.userlevel = u->userlevel;
  }

  memcpy(u, &x, sizeof(x));
  acct_save(u);
}


int
u_info()
{
  char *str, username[24]; /* Thor.980727:lkchu patch: username[20] -> 24 */

  move(2, 0);
  strcpy(username, str = cuser.username);
  acct_setup(&cuser, 0);
  if (strcmp(username, str))
    memcpy(cutmp->username, str, sizeof(cuser.username));
  return 0;
}


int
m_user()
{
  int ans;
  ACCT acct;

  while (ans = acct_get(msg_uid, &acct))
  {
    if (ans > 0)
      acct_setup(&acct, 1);
  }
  return 0;
}


/* ----------------------------------------------------- */
/* 設定 E-mail address					 */
/* ----------------------------------------------------- */


static int
ban_addr(addr)
  char *addr;
{
  int i;
  char *host, *str;
  char foo[64]; /* SoC: 放置待檢查的 email address */

  static char *invalid[] =
  {"@bbs", "bbs@", "root@", "gopher@",
    "guest@", "@ppp", "@slip", "@dial", "unknown@", "@anon.penet.fi",
    "193.64.202.3", NULL
  };

  /* SoC: 保持原 email 的大小寫 */
  str_lower(foo, addr);

  for (i = 0; str = invalid[i]; i++)
  {
    if (strstr(foo, str))
      return 1;
  }

  /* check for mail.acl (lower case filter) */

  host = (char *) strchr(foo, '@');
  *host = '\0';
  i = acl_has(MAIL_ACLFILE, foo, host + 1);
  /* *host = '@'; */
  return i > 0;
}


int
u_addr()
{
  char *msg, addr[64];

  more("etc/e-mail", (char *)-1);
		     /* lkchu.981201 */
  if (vget(b_lines - 2, 0, "E-Mail 地址：", addr, sizeof(cuser.email), DOECHO))
  {
    if (not_addr(addr) || ban_addr(addr))
    {
      msg = "不合格的 E-mail address";
    }
    else
    {
      int vtime;

      vtime = bsmtp(NULL, NULL, addr, MQ_JUSTIFY);

      if (vtime < 0)
      {
	msg = "身份認證信函無法寄出，請正確填寫 E-mail address";
      }
      else
      {
	cuser.userlevel &= ~(PERM_VALID /* | PERM_POST | PERM_PAGE */ );
	cuser.vtime = vtime;
	strcpy(cuser.email, addr);
	acct_save(&cuser);

	more("etc/justify", (char *)-1);
			    /* lkchu.981201 */
	prints("\n%s(%s)您好，由於您更新 E-mail address 的設定，\n"
	  "請您儘快到 \033[44m%s\033[m 所在的工作站回覆『身份認證信函』。",
	  cuser.userid, cuser.username, addr);
	msg = NULL;
      }
    }
    vmsg(msg);
  }

  return 0;
}


int
u_setup()
{
  int ufo, nflag, len;

  static char *flags[] =
  {
     /* COLOR */ "彩色模式",
     /* MOVIE */ "動畫顯示",
     /* BRDNEW */ "新文章",
     /* BNOTE */ "顯示進板畫面",
     /* VEDIT */ "簡化編輯器",

     /* PAGER */ "關閉呼叫器",
     /* QUITE */ "遠離塵囂",
     /* PAL */ "只顯示好友",
     /* ALOHA */ "好友上站通知 -",

     /* MOTD */ "簡化進站畫面",

     /* SELECT */ "快速扣應線上使用者", /* lkchu.981201: 選擇線上使用者扣應 */
    "保留",
    "保留",
    "保留",
    "保留",
    "保留",
    "保留",
    "保留",
    "保留",

     /* CLOAK */ "隱身術",
     /* ACL */ "ACL"
  };

  nflag = cuser.userlevel;
  if (!nflag)
    len = 5;
  else if (nflag & PERM_ADMIN)
    len = 21;  
  /* Thor.980910: 需注意有PERM_ADMIN除了可用acl, 還順便也可以用隱身術了:P */
  else if (nflag & PERM_CLOAK)
    len = 20;
  else
    len = 11;   /* lkchu.981201: 增加項目要更改 len 大小 */

  ufo = cuser.ufo;
  nflag = bitset(ufo, len, len, "操作模式設定：", flags);
  if (nflag != ufo)
  {
    /* Thor.980805: 解決 ufo BIFF的同步問題 */
    nflag = (nflag & ~UFO_UTMP_MASK) | (cutmp->ufo & UFO_UTMP_MASK);

    cutmp->ufo = cuser.ufo = nflag; 
    /* Thor.980805: 要特別注意 cuser.ufo和cutmp->ufo的UFO_BIFF的同步問題,再改 */

    showansi = nflag & UFO_COLOR;
    outs(str_ransi);
  }
  return 0;
}


int
u_lock()
{
  char buf[PASSLEN];

  blog("LOCK ", "screen");

  do
  {
    vget(b_lines, 0, "◆ 請輸入密碼，以解除螢幕鎖定：",
      buf, PASSLEN, NOECHO);
  } while (chkpasswd(cuser.passwd, buf));

  return XEASY;
}


int
u_xfile()
{
  int i;

  static char *desc[] = {
    "上站地點設定檔",
    "名片檔",
    "簽名檔",
#if 0
    /* Thor.981108: 防止修改, 以便查證 */
    "熱訊記錄",
#endif
    "暫存檔.1",
    "暫存檔.2",
    "暫存檔.3",
    "暫存檔.4",
    "暫存檔.5",
  NULL};

  static char *path[] = {
    "acl",
    "plans",
    "sign",
#if 0
    /* Thor.981108: 防止修改, 以便查證 */
    FN_BMW,
#endif
    "buf.1",
    "buf.2",
    "buf.3",
    "buf.4",
    "buf.5"
  };

  i = (cuser.userlevel & PERM_ADMIN) ? 0 : 1;
  x_file(M_UFILES, &desc[i], &path[i]);
  return 0;
}


/* ----------------------------------------------------- */
/* 看板管理						 */
/* ----------------------------------------------------- */


static int
valid_brdname(brd)
  char *brd;
{
  int ch;

  if (!is_alnum(*brd))
    return 0;

  while (ch = *++brd)
  {
    if (!is_alnum(ch) && ch != '.' && ch != '-' && ch != '_')
      return 0;
  }
  return 1;
}


static int
m_setbrd(brd)
  BRD *brd;
{
  int i;
  char *data, buf[4], old_brdname[IDLEN + 1];

  data = brd->brdname;
  i = *data ? 11 : 1;
  strcpy(old_brdname, data);

  for (;;)
  {
    if (!vget(i, 0, MSG_BID, data, IDLEN + 1, GCARRY))
    {
      if (i == 1)
	return -1;

      strcpy(data, old_brdname);/* Thor:若是清空則設為原名稱 */
      continue;
    }

    if (!strcmp(old_brdname, data) && valid_brdname(data))
    {				/* Thor: 與原名同則跳過 */
      break;
    }

    if (brd_bno(data) >= 0)
    {
      outs("\n錯誤! 板名雷同");
    }
    else if (valid_brdname(data))
    {
      break;
    }
  }

  vget(++i, 0, "看板主題：", brd->title, BTLEN + 1, GCARRY);
  vget(++i, 0, "板主名單：", brd->BM, BMLEN + 1, GCARRY);

  data = buf;

  if (vget(++i, 0, "閱\讀權限(Y/N)？[N] ", data, 3, LCECHO) == 'y')
  {
    brd->readlevel =
      bitset(brd->readlevel, NUMPERMS, NUMPERMS, MSG_READPERM, perm_tbl);
    move(2, 0);
    clrtobot();
    i = 1;
  }

  if (vget(++i, 0, "發表權限(Y/N)？[N] ", data, 3, LCECHO) == 'y')
  {
    brd->postlevel =
      bitset(brd->postlevel, NUMPERMS, NUMPERMS, MSG_POSTPERM, perm_tbl);
    move(2, 0);
    clrtobot();
    i = 1;
  }

  if (vget(++i, 0, "設定屬性(Y/N)？[N] ", data, 3, LCECHO) == 'y')
  {
#define NUMATTRS        7       /* lkchu.981201: 增加屬性別忘了改 */

    static char *battrs[NUMATTRS] = {
      "不可 Zap",
      "不轉信",
      "不記錄篇數",
      "不做熱門話題統計",
      "不公開選舉結果",
      "匿名看板",
      "不可轉寄文章"            /* lkchu.981201 */
      
    };

    brd->battr = bitset(brd->battr, NUMATTRS, NUMATTRS, MSG_BRDATTR, battrs);
  }
  return 0;
}


int
m_newbrd()
{
  BRD newboard;
  int bno;
  char fpath[80];
  HDR hdr;

  vs_bar("建立新板");
  memset(&newboard, 0, sizeof(newboard));
  if (m_setbrd(&newboard))
    return -1;

  if (vans(msg_sure_ny) != 'y')
    return 0;

  time(&newboard.bstamp);
  if ((bno = brd_bno("")) >= 0)
  {
    rec_put(FN_BRD, &newboard, sizeof(newboard), bno);
  }
  /* Thor.981102: 防止超過shm看板個數 */
  else if ( bshm->number >= MAXBOARD)
  {
    vmsg("超過系統所能容納看版個數，請調整系統參數");
    return -1;
  }
  else if (rec_add(FN_BRD, &newboard, sizeof(newboard)) < 0)
  {
    vmsg("無法建立新板");
    return -1;
  }

  sprintf(fpath, "gem/brd/%s", newboard.brdname);
  mak_dirs(fpath);
  mak_dirs(fpath + 4);

  bshm->uptime = 0;		/* force reload of bcache */
  bshm_init();

  /* 順便加進 NewBoard */

  if (vans("是否加入 [NewBoard] 群組(Y/N)?[Y] ") != 'n')
  {
    brd2gem(&newboard, &hdr);
    rec_add("gem/@/@NewBoard", &hdr, sizeof(HDR));
  }

  vmsg("新板成立");
  return 0;
}


void
brd_edit(bno)
  int bno;
{
  BRD *bhdr, newbh;
  char buf[80];

  vs_bar("看板設定");
  bhdr = bshm->bcache + bno;
  memcpy(&newbh, bhdr, sizeof(BRD));
  prints("看板名稱：%s\n看板說明：%s\n板主名單：%s\n",
    newbh.brdname, newbh.title, newbh.BM);

  bitmsg(MSG_READPERM, STR_PERM, newbh.readlevel);
  bitmsg(MSG_POSTPERM, STR_PERM, newbh.postlevel);
  bitmsg(MSG_BRDATTR, "zTcs", newbh.battr);

  switch (vget(8, 0, "(D)刪除 (E)設定 (Q)取消？[Q] ", buf, 3, LCECHO))
  {
  case 'd':

    if (vget(9, 0, msg_sure_ny, buf, 3, LCECHO) != 'y')
    {
      vmsg(MSG_DEL_CANCEL);
    }
    else
    {
      char *bname = bhdr->brdname;
      sprintf(buf, "gem/brd/%s", bname);
      f_rm(buf);
      f_rm(buf + 4);
      memset(&newbh, 0, sizeof(newbh));
      sprintf(newbh.title, "[%s] deleted by %s", bname, cuser.userid);
      memcpy(bhdr, &newbh, sizeof(BRD));
      rec_put(FN_BRD, &newbh, sizeof(newbh), bno);
      blog("Admin", newbh.title);
      vmsg("刪板完畢");
    }
    break;

  case 'e':

    move(9, 0);
    outs("直接按 [Return] 不修改該項設定");

    if (!m_setbrd(&newbh))
    {
      if ((vans(msg_sure_ny) == 'y') &&
	memcmp(&newbh, bhdr, sizeof(newbh)))
      {
	if (strcmp(bhdr->brdname, newbh.brdname))
	{
	  char src[80], dst[80];
          /* Thor.980806: 特別注意如果 board不在同一partition裏的話會有問題 */
	  sprintf(src, "gem/brd/%s", bhdr->brdname);
	  sprintf(dst, "gem/brd/%s", newbh.brdname);
	  rename(src, dst);
	  rename(src + 4, dst + 4);
	}
	memcpy(bhdr, &newbh, sizeof(BRD));
	rec_put(FN_BRD, &newbh, sizeof(BRD), bno);
      }
    }
    vmsg("設定完畢");
    break;
  }
}


#ifdef	HAVE_REGISTER_FORM
/* ----------------------------------------------------- */
/* 使用者填寫註冊表格					 */
/* ----------------------------------------------------- */


static void
getfield(line, len, buf, desc, hint)
  int line, len;
  char *hint, *desc, *buf;
{
  move(line, 0);
  prints("%s：%s", desc, hint);
  vget(line + 1, 10, NULL, buf, len, GCARRY);
}


int
u_register()
{
  FILE *fn;
  int ans;
  RFORM rform;

  if (cuser.userlevel & PERM_VALID)
  {
    vmsg("您的身份確認已經完成，不需填寫申請表"); /* lkchu.981201: 用 vmsg 較佳 */
    return XEASY;
  }

  if (fn = fopen(fn_rform, "rb"))
  {
    while (fread(&rform, sizeof(RFORM), 1, fn))
    {
      if ((rform.userno == cuser.userno) &&
	!str_cmp(rform.userid, cuser.userid))
      {
	fclose(fn);
	vmsg("您的註冊申請單尚在處理中，請耐心等候"); /* lkchu.981201: 用 vmsg 較佳 :p */
	return XEASY;
      }
    }
    fclose(fn);
  }

  if (vans("您確定要填寫註冊單嗎(Y/N)？[N] ") != 'y')
    return XEASY;

  move(2, 0);
  clrtobot();
  prints("%s(%s) 您好，請據實填寫以下的資料：\n(按 [Enter] 接受初始設定)",
    cuser.userid, cuser.username);

  memset(&rform, 0, sizeof(RFORM));
  strcpy(rform.realname, cuser.realname);
  strcpy(rform.address, cuser.address);
  rform.career[0] = rform.phone[0] = '\0';
  for (;;)
  {
    getfield(5, 20, rform.realname, "真實姓名", "請用中文");
    getfield(8, 50, rform.career, "服務單位", "學校系級或單位職稱");
    getfield(11, 60, rform.address, "目前住址", "包括寢室或門牌號碼");
    getfield(14, 20, rform.phone, "連絡電話", "包括長途撥號區域碼");
    ans = vans("以上資料是否正確(Y/N)？(Q)取消 [N] ");
    if (ans == 'q')
      return 0;
    if (ans == 'y')
      break;
  }
  strcpy(cuser.realname, rform.realname);
  strcpy(cuser.address, rform.address);

  rform.userno = cuser.userno;
  strcpy(rform.userid, cuser.userid);
  (void) time(&rform.rtime);
  rec_add(fn_rform, &rform, sizeof(RFORM));
  return 0;
}


/* ----------------------------------------------------- */
/* 處理 Register Form					 */
/* ----------------------------------------------------- */


static int
scan_register_form(fd)
  int fd;
{
  static char logfile[] = FN_RFORM_LOG;
  static char *reason[] = {"輸入真實姓名", "詳實填寫申請表",
    "詳填住址資料", "詳填連絡電話", "詳填服務單位、或學校系級",
  "用中文填寫申請單", "採用 E-mail 認證", NULL};

  ACCT muser;
  RFORM rform;
  HDR fhdr;
  FILE *fout;

  int op, n;
  char buf[128], msg[128], *agent, *userid, *str;

  vs_bar("審核使用者註冊資料");
  agent = cuser.userid;

  while (read(fd, &rform, sizeof(RFORM)) == sizeof(RFORM))
  {
    userid = rform.userid;
    move(2, 0);
    prints("申請代號: %s (申請時間：%s)\n", userid, Ctime(&rform.rtime));
    prints("真實姓名: %s\n", rform.realname);
    prints("服務單位: %s\n", rform.career);
    prints("目前住址: %s\n", rform.address);
    prints("連絡電話: %s\n%s\n", rform.phone, msg_seperator);
    clrtobot();

    if ((acct_load(&muser, userid) < 0) || (muser.userno != rform.userno))
    {
      vmsg("查無此人");
      op = 'd';
    }
    else
    {
      acct_show(&muser, 2);
      if (muser.userlevel & PERM_VALID)
      {
	vmsg("此帳號已經完成註冊");
	op = 'd';
      }
      else
      {
	op = vans("是否接受(Y/N/Q/Del/Skip)？[S] ");
      }
    }

    switch (op)
    {
    case 'y':

      muser.userlevel |= PERM_VALID;
      strcpy(muser.realname, rform.realname);
      strcpy(muser.address, rform.address);
      sprintf(msg, "%s:%s:%s", rform.phone, rform.career, agent);
      /* str_ncpy(muser.justify, msg, 59); */
      str_ncpy(muser.justify, msg, sizeof(muser.justify));
      /* Thor.980921: 保險起見 */

      /* Thor.981022: 手動認證也改認證時間, 每半年會再自動認證一次*/
      time(&muser.tvalid);

      acct_save(&muser);

      usr_fpath(buf, userid, "justify");
      if (fout = fopen(buf, "w"))
      {
	fprintf(fout, "%s\n", msg);
	fclose(fout);
      }

      usr_fpath(buf, userid, fn_dir);
      /* lkchu.981201: 改成 etc/justified 與 bmtad & mailpost 相同 */
      hdr_stamp(buf, HDR_LINK, &fhdr, "etc/justified" /* "etc/approved" */);
      strcpy(fhdr.title, "[註冊成功\] 您已經通過身分認證了！");
      strcpy(fhdr.owner, cuser.userid);
      rec_add(buf, &fhdr, sizeof(fhdr));

      strcpy(rform.agent, agent);
      rec_add(logfile, &rform, sizeof(RFORM));

      break;

    case 'q':			/* 太累了，結束休息 */

      do
      {
	rec_add(fn_rform, &rform, sizeof(RFORM));
      } while (read(fd, &rform, sizeof(RFORM)) == sizeof(RFORM));

    case 'd':
      break;

    case 'n':

      move(9, 0);
      prints("請提出退回申請表原因，按 <enter> 取消\n\n");
      for (n = 0; str = reason[n]; n++)
	prints("%d) 請%s\n", n, str);
      clrtobot();

      if (op = vget(b_lines, 0, "退回原因：", buf, 60, DOECHO))
      {
	int i;
	char folder[80], fpath[80];
	HDR fhdr;

	i = op - '0';
	if (i >= 0 && i < n)
	  strcpy(buf, reason[i]);

	usr_fpath(folder, muser.userid, fn_dir);
	if (fout = fdopen(hdr_stamp(folder, 0, &fhdr, fpath), "w"))
	{
	  fprintf(fout, "\t由於您提供的資料不夠詳實，無法確認身分，"
	    "\n\n\t請重新填寫註冊表單：%s。\n", buf);
	  fclose(fout);

	  strcpy(fhdr.owner, agent);
	  strcpy(fhdr.title, "[冷心使者] 請您重新填寫註冊表單");
	  rec_add(folder, &fhdr, sizeof(fhdr));
	}

	strcpy(rform.reply, buf);	/* 理由 */
	strcpy(rform.agent, agent);
	rec_add(logfile, &rform, sizeof(RFORM));

	break;
      }

    default:			/* put back to regfile */

      rec_add(fn_rform, &rform, sizeof(RFORM));
    }
  }
}


int
m_register()
{
  int num;
  char buf[80];

  num = rec_num(fn_rform, sizeof(RFORM));
  if (num <= 0)
  {
    vmsg("目前並無新註冊資料"); /* lkchu.981201: 用 vmsg 較佳 :p */
    return XEASY;
  }

  sprintf(buf, "共有 %d 筆資料，開始審核嗎(Y/N)？[N] ", num);
  num = XEASY;

  if (vans(buf) == 'y')
  {
    sprintf(buf, "%s.tmp", fn_rform);
    if (dashf(buf))
    {
      vmsg("其他 SYSOP 也在審核註冊申請單");
    }
    else
    {
      int fd;

      rename(fn_rform, buf);
      fd = open(buf, O_RDONLY);
      if (fd >= 0)
      {
	scan_register_form(fd);
	close(fd);
	unlink(buf);
	num = 0;
      }
      else
      {
	vmsg("無法開啟註冊資料工作檔");
      }
    }
  }
  return num;
}
#endif


/* ----------------------------------------------------- */
/* 產生追蹤記錄：建議改用 log_usies()、TRACE()		 */
/* ----------------------------------------------------- */


#ifdef	HAVE_REPORT
void
report(s)
  char *s;
{
  static int disable = NA;
  int fd;

  if (disable)
    return;

  if ((fd = open("trace", O_WRONLY, 0600)) != -1)
  {
    char buf[256];
    char *thetime;
    time_t dtime;

    time(&dtime);
    thetime = Etime(&dtime);

    /* flock(fd, LOCK_EX); */
    /* Thor.981205: 用 fcntl 取代flock, POSIX標準用法 */
    f_exlock(fd);

    lseek(fd, 0, L_XTND);
    sprintf(buf, "%s %s %s\n", cuser.userid, thetime, s);
    write(fd, buf, strlen(buf));

    /* flock(fd, LOCK_UN); */
    /* Thor.981205: 用 fcntl 取代flock, POSIX標準用法 */
    f_unlock(fd);

    close(fd);
  }
  else
    disable = YEA;
}


int
m_trace()
{
  struct stat bstatb, ostatb, cstatb;
  int btflag, otflag, ctflag, done = 0;
  char ans[2];
  char *msg;

  clear();
  move(0, 0);
  outs("Set Trace Options");
  clrtobot();
  while (!done)
  {
    move(2, 0);
    otflag = stat("trace", &ostatb);
    ctflag = stat("trace.chatd", &cstatb);
    btflag = stat("trace.bvote", &bstatb);
    outs("Current Trace Settings:\n");
    if (otflag)
      outs("Normal tracing is OFF\n");
    else
      prints("Normal tracing is ON (size = %d)\n", ostatb.st_size);
    if (ctflag)
      outs("Chatd  tracing is OFF\n");
    else
      prints("Chatd  tracing is ON (size = %d)\n", cstatb.st_size);
    if (btflag)
      outs("BVote  tracing is OFF\n");
    else
      prints("BVote  tracing is ON (size = %d)\n", bstatb.st_size);

    move(8, 0);
    outs("Enter:\n");
    prints("<1> to %s Normal tracing\n", otflag ? "enable " : "disable");
    prints("<2> to %s Chatd  tracing\n", ctflag ? "enable " : "disable");
    prints("<3> to %s BVote  tracing\n", btflag ? "enable " : "disable");
    vget(12, 0, "Anything else to exit：", ans, 2, DOECHO);

    switch (ans[0])
    {
    case '1':
      if (otflag)
      {
	system("/bin/touch trace");
	msg = "BBS   tracing enabled.";
	report("opened report log");
      }
      else
      {
	report("closed report log");
	system("/bin/mv trace trace.old");
	msg = "BBS   tracing disabled; log is in trace.old";
      }
      break;

    case '2':
      if (ctflag)
      {
	system("/bin/touch trace.chatd");
	msg = "Chat  tracing enabled.";
	report("chatd trace log opened");
      }
      else
      {
	system("/bin/mv trace.chatd trace.chatd.old");
	msg = "Chat  tracing disabled; log is in trace.chatd.old";
	report("chatd trace log closed");
      }
      break;

    case '3':
      if (btflag)
      {
	system("/bin/touch trace.bvote");
	msg = "BVote tracing enabled.";
	report("BVote trace log opened");
      }
      else
      {
	system("/bin/mv trace.bvote trace.bvote.old");
	msg = "BVote tracing disabled; log is in trace.bvote.old";
	report("BoardVote trace log closed");
      }
      break;

    default:
      msg = NULL;
      done = 1;
    }
    move(b_lines - 1, 0);
    if (msg)
      prints("%s\n", msg);
  }
  clear();
}
#endif				/* HAVE_REPORT */
