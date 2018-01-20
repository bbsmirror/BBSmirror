/*    Pirate Bulletin Board System
    Copyright (C) 1990, Edward Luke, lush@Athena.EE.MsState.EDU
    Eagles Bulletin Board System
    Copyright (C) 1992, Raymond Rocker, rocker@rock.b11.ingr.com
                        Guy Vega, gtvega@seabass.st.usm.edu
                        Dominic Tynes, dbtynes@seabass.st.usm.edu

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 1, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "bbs.h"
#ifdef lint
#include <sys/uio.h>
#endif
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define M_INT 8         /* monitor mode update interval */
#define P_INT 20        /* interval to check for page req. in talk/chat */
extern char BoardName[];
extern int iscolor;
extern int RMSG;
extern int datacoming;
extern void r_msg();
extern int numf,friendmode;
struct friend *topfriend;
extern struct screenline *big_picture;
struct user_info * t_search(char *sid,int pid);
int talkidletime=0;
int ulistpage;
int friend_query();
int friend_mail();
int friend_dele();
int friend_add();
int friend_edit();
int friend_help();
char idlestr[16];

struct one_key  friend_list[] = {
    'r',        friend_query,
    'm',        friend_mail,
    'M',        friend_mail,
    'a',        friend_add,
    'A',        friend_add,
    'd',        friend_dele,
    'D',        friend_dele,
    'E',        friend_edit,
    'h',        friend_help,
    'H',        friend_help,
    '\0',       NULL
} ;


struct talk_win {
    int         curcol, curln;
    int         sline, eline;
};

int     nowmovie;
int     bind(/*int,struct sockaddr *, int*/) ;
char    *sysconf_str();


#include "modetype.c"

extern int t_columns;
char    *talk_uent_buf;

/* begin - jjyang */
char save_page_requestor[STRLEN];
/* end - jjyang */

int t_cmpuids();
int cmpfnames();
int
ishidden(user)
char *user;
{
    int tuid;
    struct user_info uin;

    if (!(tuid = getuser(user))) return 0;
    search_ulist( &uin, t_cmpuids, tuid );
    return( uin.invisible );
}

char *
modestring(mode, towho, complete, chatid)
int mode, towho, complete;
char *chatid;
{
    static char modestr[STRLEN];
    struct userec urec;

    if (chatid) {
        if (complete) sprintf(modestr, "%s(%s)", ModeType(mode), chatid);
        else return (ModeType(mode));
        return (modestr);
    }
    if (mode != TALK && mode != PAGE && mode != QUERY && mode != FIVE) //paul
        return (ModeType(mode));
    if (get_record(PASSFILE, &urec, sizeof(urec), towho) == -1)
        return (ModeType(mode));

    if (mode != QUERY && !HAS_PERM(PERM_SYSOP) && 
        ishidden(urec.userid)) return (ModeType(TMENU));        
    if (complete)
        sprintf(modestr, "%s<%s>", ModeType(mode), urec.userid);
    else
        return (ModeType(mode));
    return (modestr);
}

char
pagerchar(friend, uentp)
int friend;
struct user_info *uentp;
{
    if (badfriend(uinfo.uid,uentp)) return 'X';
    if (uentp->pager&ALL_PAGER) return ' ';
    if ((friend)) 
    {
        if(uentp->pager&FRIEND_PAGER)
                return 'O';
        else
                return '#';
    }
    return '*';
}

char
canpage(friend, uentp)
int friend;
struct user_info *uentp;
{
    if(badfriend(uinfo.uid,uentp)) return NA;
    if ((uentp->pager&ALL_PAGER) || HAS_PERM(PERM_SYSOP)) return YEA;
    if ((uentp->pager&FRIEND_PAGER))
    {
        if(friend)
                return YEA;
    }
    return NA;
}

#ifdef SHOW_IDLE_TIME
char *
idle_str( uent )
struct user_info *uent ;
{
    static char hh_mm_ss[ 32 ];
    struct stat buf;
    char        tty[ 128 ];
    time_t      now, diff;
    int         hh, mm, ss;

    strcpy( tty, uent->tty );

    if ( (stat( tty, &buf ) != 0) || 
         (strstr( tty, "tty" ) == NULL)) {
        strcpy( hh_mm_ss, "¤£¸Ô");
        return hh_mm_ss;
    };

    now = time( 0 );

    diff = now - buf.st_atime;

#ifdef DOTIMEOUT
   if(!HAS_PERM(PERM_SYSOP))
   {
    /* the 60 * 60 * 24 * 5 is to prevent fault /dev mount from
       kicking out all users */

    if ((diff > IDLE_TIMEOUT) && (diff < 60 * 60 * 24 * 5 )) 
        kill( uent->pid, SIGHUP );
   }
#endif
    ss = diff % 60;
    mm = diff / 60;
    
    if ( mm > 0 ) 
        sprintf( hh_mm_ss, "%d:%02d", mm, ss );
    else if ( ss > 0 ) 
        sprintf( hh_mm_ss, "%d", ss );
    else sprintf ( hh_mm_ss, "   ");

    return hh_mm_ss;
}
#endif


int
listcuent(uentp)
struct user_info *uentp ;
{
    if(uentp == NULL) {
        CreateNameList() ;
        return 0;
    }
    if(uentp->uid == usernum)
        return 0;
    if(!uentp->active || !uentp->pid)
        return 0;
    if(uentp->mode == ULDL)
        return 0;
    if(!HAS_PERM(PERM_SYSOP) && uentp->invisible)
        return 0;
    AddNameList( uentp->userid );
    return 0 ;
}

void
creat_list()
{
    listcuent(NULL) ;
    apply_ulist( listcuent );
}

int
t_pager()
{

    if(uinfo.pager&ALL_PAGER)
    {
        uinfo.pager&=~ALL_PAGER;
        if( DEFINE(DEF_FRIENDCALL))
                uinfo.pager|=FRIEND_PAGER;
        else
                uinfo.pager&=~FRIEND_PAGER;
    }else
    {
        uinfo.pager|=ALL_PAGER;
        uinfo.pager|=FRIEND_PAGER;
    }

    if ( !uinfo.in_chat && uinfo.mode!=TALK) {
        move( 1, 0 );
        prints( "±zªº©I¥s¾¹ (pager) ¤w¸g[1m%s[m¤F!",
                (uinfo.pager&ALL_PAGER) ? "¥´¶}" : "Ãö³¬" );
        pressreturn();
    }
    update_utmp();
    return 0 ;
}

/*Add by SmallPig*/
/*¦¹¨ç¼Æ¥u­t³d¦C¦L»¡©úÀÉ¡A¨Ã¤£ºÞ²M°£©Î©w¦ìªº°ÝÃD¡C*/
int
show_user_plan(userid)
char userid[IDLEN];
{
        int i;
        char pfile[STRLEN],pbuf[256];
        FILE *pf;

        sethomefile(pfile,userid,"plans");
        if ((pf = fopen(pfile, "r")) == NULL)
        {
                prints("[1;36m¨S¦³­Ó¤H»¡©úÀÉ[m\n");
                return NA;
        }
        else 
        {
                prints("[1;36m­Ó¤H»¡©úÀÉ¦p¤U¡G[m\n");
                for (i=1; i<=MAXQUERYLINES; i++) 
                {
                if (fgets(pbuf, sizeof(pbuf), pf))
                        prints("%s", pbuf);
                else break;
                }
        fclose(pf);
        return YEA;
        }
}



/* Modified By Excellent*/
int
t_query(q_id)
char q_id[IDLEN];
{
    char        uident[STRLEN], *newline ;
    int         tuid=0;
    int         exp,perf;/*Add by SmallPig*/
    struct user_info uin;
    char buf[255];
    char qry_mail_dir[STRLEN];
    FILE *fp;

  if(uinfo.mode!=LUSERS&&uinfo.mode!=LAUSERS&&uinfo.mode!=FRIEND&&uinfo.mode!=READING
     &&uinfo.mode!=MAIL&&uinfo.mode!=RMAIL&&uinfo.mode!=GMENU){
    modify_user_mode( QUERY );
    refresh();
/*    count = shortulist(NULL);*/
    move(2,0);
    clrtobot();
    prints("<¿é¤J¨Ï¥ÎªÌ¥N¸¹, «öªÅ¥ÕÁä¥i¦C¥X²Å¦X¦r¦ê>\n");
    move(1,0);
    clrtoeol();
    prints("¬d¸ß½Ö: ");
    usercomplete(NULL,uident);
    if(uident[0] == '\0') {
        clear() ;
        return 0 ;
    }
  }else
  {
    strcpy(uident,strtok(q_id," "));
  }
    if(!(tuid = getuser(uident))) {
        move(2,0) ;
        clrtoeol();
        prints("[1m¤£¥¿½Tªº¨Ï¥ÎªÌ¥N¸¹[m\n") ;
        pressanykey(NULL) ;
        move(2,0) ;
        clrtoeol() ;
        return -1 ;
    }
    uinfo.destuid = tuid ;
    update_utmp();
   
    search_ulist( &uin, t_cmpuids, tuid );

    clear();
 
    sprintf(qry_mail_dir,"mail/%c/%s/%s",toupper(lookupuser.userid[0]),lookupuser.userid,DOT_DIR);
   
    move(0,0);
    if(fp=fopen("etc/query","r"))
     { while(fgets(buf,sizeof(buf),fp))
           prints(buf); 
       fclose(fp); }
    if(HAS_PERM(PERM_SYSOP))
         prints("%s %s%s%s\n",lookupuser.realname, 
                              lookupuser.card & CARD_GOLD     ? "[\x1b[1mª÷¥d\x1b[m] ": "",
                              lookupuser.card & CARD_SILVER   ? "[\x1b[1m»È¥d\x1b[m] ": "",
                              lookupuser.card & CARD_MAGICPRO ? "[\x1b[1m¸ªªá\x1b[m]" : "");
    if(HAS_PERM(PERM_SYSOP) || !strcmp(lookupuser.userid,currentuser.userid))
          prints("¦b»È¦æ¤º¦³\x1b[1m%d\x1b[m¤¸¦s´Ú¡A",lookupuser.bank);
    prints("«H½c¤º%s·s«H¥ó¡C",check_query_mail(qry_mail_dir)==1 ? "¦³" : "¨S¦³" );

   t_search_ulist( &uin, t_cmpuids, tuid );  
#if defined(QUERY_REALNAMES)
    if (HAS_PERM(PERM_BASIC))   
        prints("Real Name: %s \n",lookupuser.realname);
#endif
    show_user_plan(lookupuser.userid);
   if(uinfo.mode!=LUSERS&&uinfo.mode!=LAUSERS&&uinfo.mode!=FRIEND&&uinfo.mode!=GMENU)
     {   pressanykey(NULL); clear(); }
        
    uinfo.destuid = 0;
    return 0;
}               

int
count_active(uentp)
struct user_info *uentp ;
{
    static int count ;

    if(uentp == NULL) {
        int c = count;
        count = 0;
        return c;
    }
    if(!uentp->active || !uentp->pid)
        return 0 ;
    count++ ;
    return 1 ;
}

int
count_useshell(uentp)
struct user_info *uentp ;
{
    static int count ;

    if(uentp == NULL) {
        int c = count;
        count = 0;
        return c;
    }
    if(!uentp->active || !uentp->pid)
        return 0 ;
    if(uentp->mode==WWW||uentp->mode==CSIE_TIN||uentp->mode==CSIE_GOPHER
        ||uentp->mode==EXCE_CHESS||uentp->mode==EXCE_BIG2||uentp->mode==EXCE_MJ
        ||uentp->mode==IRCCHAT)
        count++ ;
    return 1 ;
}

int
count_user_logins(uentp)
struct user_info *uentp ;
{
    static int count ;

    if(uentp == NULL) {
       int c = count;
       count = 0;
       return c;
    }
    if(!uentp->active || !uentp->pid)
       return 0 ;
    if(!strcmp(uentp->userid,save_page_requestor))
        count++ ;
    return 1 ;
}

int
count_visible_active(uentp)
struct user_info *uentp ;
{
    static int count ;
    
    if(uentp == NULL) {
       int c = count;
       count = 0;
       return c;
    }
    if(!uentp->active || !uentp->pid)
       return 0 ;
    count++ ;
    if(!HAS_PERM(PERM_SYSOP) && uentp->invisible)
       count--;
    return 1 ;
}

int
alcounter(uentp)
struct user_info *uentp ;
{
    static int vi_users,vi_friends;
    int canseecloak;

    if(uentp == NULL) {
       count_friends= vi_friends;
       count_users= vi_users;
       vi_users=vi_friends=0;
       return 1;
    }
    if(!uentp->active || !uentp->pid)
       return 0 ;

    canseecloak=(!HAS_PERM(PERM_SEECLOAK) && uentp->invisible)?0:1;
    if(myfriend(uentp->uid))
    {
        vi_friends++ ;
       if(!canseecloak)
                vi_friends--;
    }
    vi_users++ ;
    if(!canseecloak)
       vi_users--;
    return 1 ;
}

int
num_alcounter()
{
    alcounter(NULL) ;
    apply_ulist( alcounter ) ;
    alcounter(NULL) ;
    return;
}

int
num_useshell()
{
    count_useshell(NULL) ;
    apply_ulist( count_useshell) ;
    return count_useshell(NULL) ;
}

int
num_active_users()
{
    count_active(NULL) ;
    apply_ulist( count_active ) ;
    return count_active(NULL) ;
}
int
num_user_logins(uid)
char *uid;
{
    strcpy(save_page_requestor,uid);
    count_active(NULL) ;
    apply_ulist( count_user_logins ) ;
    return count_user_logins(NULL) ;
}
int
num_visible_users()
{
    count_visible_active(NULL) ;
    apply_ulist( count_visible_active ) ;
    return count_visible_active(NULL) ;
}

int  
cmpfnames(userid, uv)  // Compare friend list (bad friend not included)
char    *userid;
struct friend *uv;
{
        return uv->type == FR_GOOD ? !strcmp(userid, uv->id) : 0;
}

int  // Compare friend list include bad friend
cmpfbnames(userid, uv)
char    *userid;
struct friend *uv;
{
        return !strcmp(userid, uv->id) ;
}

int
t_cmpuids(uid,up)
int uid ;
struct user_info *up ;
{
    return (up->active && uid == up->uid) ;
}

int
/*  modified by netty  */
t_talk()
{
    int  netty_talk ;
    
#ifdef DOTIMEOUT
        init_alarm();
#else
        signal(SIGALRM, SIG_IGN);
#endif
    refresh();
    netty_talk = ttt_talk();
    clear() ;
    return (netty_talk);
}
int
ttt_talk(userinfo)
struct user_info *userinfo ;
{
   char uident[STRLEN] ;
   char test[STRLEN];
   int tuid, ucount, unum, tmp ;
   struct user_info uin ;
   int five=0; // by paul 
   move(1,0);
   clrtobot();
   if(uinfo.mode!=LUSERS&&uinfo.mode!=FRIEND){
     move(2,0) ;
     prints("<¿é¤J¨Ï¥ÎªÌ¥N¸¹>\n") ;
     move(1,0) ;
     clrtoeol() ;
     prints("¸ò½Ö²á¤Ñ: ") ;
     creat_list() ;
     namecomplete(NULL,uident) ;
     if(uident[0] == '\0') {
        clear() ;
        return 0 ;
    }
    if(!(tuid = searchuser(uident)) || tuid == usernum) {
        move(2,0) ;
        prints("¿ù»~¥N¸¹\n") ;
        pressreturn() ;
        move(2,0) ;
        clrtoeol() ;
        return -1 ;
    }
    ucount=count_logins( &uin, t_cmpuids, tuid, 0);
    move(3,0);
    prints("¥Ø«e %s ªº %d logins ¦p¤U: \n", uident, ucount);
    clrtobot() ;
    if(ucount>1) {
    list:   move(5,0) ;
    prints("(0) ºâ¤Fºâ¤F¡A¤£²á¤F¡C\n");
    ucount=count_logins( &uin, t_cmpuids, tuid, 0);
    count_logins( &uin, t_cmpuids, tuid, 1);
    clrtobot() ;
    tmp=ucount+8;
    getdata( tmp, 0, "½Ð¿ï¤@­Ó§A¬Ýªº¤ñ¸û¶¶²´ªº [0]: ",
    genbuf, 4, DOECHO, NULL,YEA);
    unum=atoi(genbuf);
    if(unum == 0) { clear(); return 0; }
      if(unum > ucount || unum < 0) {
        move(tmp,0);
        prints("²Â²Â¡I§A¿ï¿ù¤F°Õ¡I\n") ;
        clrtobot();
        pressreturn();
        goto list;
        }
        search_ulistn( &uin, t_cmpuids, tuid, unum );
    }else
        search_ulist( &uin, t_cmpuids, tuid );
   }else
   {
/*     memcpy(&uin,userinfo,sizeof(uin));*/
     uin=*userinfo;
     tuid=uin.uid;
     strcpy(uident,uin.userid);
     move(1,0) ;
     clrtoeol() ;
     prints("¸ò½Ö²á¤Ñ: %s",uin.userid) ;
   }
    /*  check if pager on/off       --gtv */
    if(!canpage(can_override(uin.userid, currentuser.userid),&uin)) 
    {
          move(2,0) ;
          prints("¹ï¤è©I¥s¾¹¤wÃö³¬.\n") ;
          pressreturn() ;
          move(2,0) ;
          clrtoeol() ;
          return -1 ;
    }
   /*modified by Excellent*/
    if(uin.mode == ULDL || uin.mode == IRCCHAT || 
        uin.mode == BBSNET || uin.mode == FOURM || uin.mode==EXCE_BIG2 ||
        uin.mode == EXCE_MJ || uin.mode==EXCE_CHESS || uin.mode==FIVE) {
        move(2,0) ;
        prints("¥Ø«eµLªk©I¥s.\n") ;
        pressreturn() ;
        move(2,0) ;
        clrtoeol() ;
        return -1 ;
    }
    if(!uin.active || (kill(uin.pid,0) == -1)) {
        move(2,0) ;
        prints("¹ï¤è¤wÂ÷¶}\n") ;
        pressreturn() ;
        move(2,0) ;
        clrtoeol() ;
        return -1 ;
    } else {
        int sock, msgsock, length ;
        struct sockaddr_in server ;
        char c ;
        char buf[512] ;

        move( 3, 0 );
        clrtobot();
        show_user_plan(uident);
//modified by paul start
     //   getdata( 2, 0, "½T©w­n©M¥L/¦o½Í¤Ñ¶Ü? (Y/N) [N]: ", genbuf, 4, DOECHO, NULL,YEA);
     getdata(2, 0, "·Q§ä¹ï¤è½Í¤Ñ½Ð«ö'y',¤U¤­¤l´Ñ½Ð«ö'f'?(Y/F/N)[N]:",genbuf, 4, DOECHO, NULL,YEA);
     if (*genbuf != 'y' && *genbuf != 'f'){
        clear(); return 0;
     }
     if(*genbuf == 'f')
        five=1;
//        if ( *genbuf != 'y' && *genbuf != 'Y' ) {
//            clear();
//            return 0;
//        }
       if(five==1) sprintf(buf,"FIVE to '%s'",uident) ;
       else sprintf(buf,"Talk to '%s'",uident) ;
//        sprintf(buf,"Talk to '%s'",uident) ;
//modified by paul end
        report(buf) ;
        sock = socket(AF_INET, SOCK_STREAM, 0) ;
        if(sock < 0) {
            perror("socket err\n") ;
            return -1 ;
        }

        server.sin_family = AF_INET ;
        server.sin_addr.s_addr = INADDR_ANY ;
        server.sin_port = 0 ;
        if(bind(sock, (struct sockaddr *) & server, sizeof server ) < 0) {
            perror("bind err") ;
            return -1 ;
        }
        length = sizeof server ;
        if(getsockname(sock, (struct sockaddr *) &server, &length) < 0) {
            perror("socket name err") ;
            return -1 ;
        }
        uinfo.sockactive = YEA ;
        uinfo.sockaddr = server.sin_port ;
        uinfo.destuid = tuid ;

//modified by paul start
//        modify_user_mode( PAGE );
        if(five) modify_user_mode( FIVE );
        else modify_user_mode( PAGE );
//modified by paul end 

        kill(uin.pid,SIGUSR1) ;
        clear() ;
        prints("©I¥s %s ¤¤...\n¿é¤J Ctrl-D µ²§ô\n", uident) ;

        listen(sock,1) ;
        add_io(sock,20) ;
        while(YEA) {
            int ch ;
            ch = egetch() ;
            if(ch == I_TIMEOUT) {
                move(0,0) ;
                prints("¦A¦¸©I¥s.\n") ;
                bell() ;
                if(kill(uin.pid,SIGUSR1) == -1) {
                    move(0,0) ;
                    prints("¹ï¤è¤wÂ÷½u\n") ;
                    pressreturn() ;
                    /*Add by SmallPig 2 lines*/
                    uinfo.sockactive = NA ;
                    uinfo.destuid = 0 ;
                    return -1 ;
                }
                continue ;
            }
            if(ch == I_OTHERDATA)
                break ;
            if(ch == '\004') {
                add_io(0,0) ;
                close(sock) ;
                uinfo.sockactive = NA ;
                uinfo.destuid = 0 ;
                clear() ;
                return 0 ;
            }
        }

        msgsock = accept(sock, (struct sockaddr *)0, (int *) 0) ;
        if(msgsock == -1) {
            perror("accept") ;
            return -1 ;
        }
        add_io(0,0) ;
        close(sock) ;
        uinfo.sockactive = NA ;
/*      uinfo.destuid = 0 ;*/
        read(msgsock,&c,sizeof c) ;

        clear() ;

//modified by paul start 
        if (c == 'y' || c=='Y'|| c == 'f'){
//      if(c == 'y'|| c=='Y' ) {
          sprintf( save_page_requestor, "%s (%s)", uin.userid, uin.username);
//        do_talk(msgsock) ;
        if(five==1) five_pk(msgsock,1);
        else do_talk(msgsock);
//modified by paul end

/*Add by SmallPig*/
        } else if(c=='n'||c=='N'){
            prints("%s (%s)»¡¡G©êºp¡A§Ú²{¦b«Ü¦£¡A¤£¯à¸ò§A²á¡C\n", uin.userid, uin.username) ;
            pressreturn() ;
        } else if(c=='b' || c=='B')
        {   prints("%s (%s)»¡¡G§Ú²{¦b«Ü·Ð¡A¤£·Q¸ò§O¤H²á¤Ñ¡C\n", uin.userid, uin.username) ;
            pressreturn() ;
        } else if(c=='c' || c=='C')
        {   prints("%s (%s)»¡¡G§Ú¦³«æ¨Æ¡A§Úµ¥¤@¤U¦A Call §A¡C\n", uin.userid, uin.username) ;
            pressreturn() ;
        } else if(c=='d' || c=='D')
        {   prints("%s (%s)»¡¡G½Ð§A¤£­n¦A Page¡A§Ú¤£·Q¸ò§A²á¡C\n", uin.userid, uin.username) ;
            pressreturn() ;
        } else if(c=='e' || c=='E')
        {   prints("%s (%s)»¡¡G§Ú­nÂ÷¶}¤F¡A¤U¦¸¦b²á§a¡C\n", uin.userid, uin.username) ;
            pressreturn() ;
        } else if(c=='F' || c=='f')
        {   prints("%s (%s)»¡¡G½Ð§A±H¤@«Ê«Hµ¹§Ú¡A§Ú²{¦b¨SªÅ¡C\n", uin.userid, uin.username) ;
            pressreturn() ;
        } else if(c=='M' || c=='m')
        {   
                read(msgsock,test,sizeof test) ;
                prints("%s (%s)»¡¡G%s\n", uin.userid, uin.username,test);
                pressreturn() ;
        } else{
                    sprintf( save_page_requestor, "%s (%s)", uin.userid, uin.username);
                    do_talk(msgsock) ;
        }                        
        close(msgsock) ;
        clear() ;
        refresh();
        uinfo.destuid = 0;
    }
    return 0 ;
}

extern int talkrequest ;
extern int ntalkrequest ;
struct user_info  ui ;
char page_requestor[STRLEN];
char page_requestorid[STRLEN];

int
cmpunums(unum,up)
int unum ;
struct user_info *up ;
{
    if(!up->active)
      return 0 ;
        return (unum == up->destuid) ;
}

int
cmpmsgnum(unum,up)
int unum ;
struct user_info *up ;
{
    if(!up->active)
      return 0 ;
        return (unum == up->destuid&&up->sockactive==2) ;
}

int
setpagerequest(mode)
int mode;
{
    int tuid;
    if(mode==0)
            tuid = search_ulist( &ui, cmpunums, usernum );      
    else
            tuid = search_ulist( &ui, cmpmsgnum, usernum );
    if(tuid == 0)
        return 1;
    if(!ui.sockactive)
        return 1;
    uinfo.destuid = ui.uid;
    sprintf(page_requestor, "%s (%s)", ui.userid, ui.username);
    strcpy( page_requestorid, ui.userid );
    return 0;
}

int
servicepage( line, mesg )
int     line;
char    *mesg;
{
    static time_t last_check;
    time_t now;
    char buf[STRLEN];
    int tuid = search_ulist( &ui, cmpunums, usernum );

    if(tuid == 0 || !ui.sockactive) talkrequest = NA;
    if (!talkrequest) {
        if (page_requestor[0]) {
            switch (uinfo.mode) {
                case TALK:
                case FIVE: //by paul
                    move(line, 0);
                    printdash( mesg );
                    break;
                default: /* a chat mode */
                    sprintf(buf, "** %s ¤w°±¤î©I¥s.", page_requestor);
                    printchatline(buf);
            }
            memset(page_requestor, 0, STRLEN);
            last_check = 0;
        }
        return NA;
    } else {
        now = time(0);
        if (now - last_check > P_INT) {
            last_check = now;
            if (!page_requestor[0] && setpagerequest(0/*For Talk*/))
                return NA;
            else switch (uinfo.mode) {
                case TALK:
                    move(line, 0);
                    sprintf(buf, "** %s ¥¿¦b©I¥s§A", page_requestor);
                    printdash( buf );
                    break;
                default: /* chat */
                    sprintf(buf, "** %s ¥¿¦b©I¥s§A", page_requestor);
                    printchatline(buf);
            }
        }
    }
    return YEA;
}

static char npage_requestor[STRLEN];

int
setnpagerequest()
{
    char tmp_buf[STRLEN + 128];
    FILE *getpager;

    if (sysconf_str("GETPAGER") == NULL) return 1;

    sprintf(tmp_buf,"%s %s", sysconf_str("GETPAGER"),currentuser.userid);
    getpager = popen(tmp_buf,"r"); 
    if (getpager == NULL) 
       return 1;
    fgets(npage_requestor, STRLEN, getpager);
    if ( *npage_requestor == '\0')
       return 1;
    return 0;
}
void
ndo_talk(pager,reject)
char *pager ;
int reject;
{
    char tmp_buf[STRLEN + 128];

    if (reject) {
     sprintf(tmp_buf,"/bin/sh %s %s", sysconf_str("REJECTCALL"),pager);
    } else {
     sprintf(tmp_buf,"/bin/sh %s %s", sysconf_str("NTALK"),pager);
     modify_user_mode( TALK );
    }
    reset_tty() ;
    do_exec(tmp_buf,NULL) ;
    restore_tty() ;
    modify_user_mode( MMENU );
}

int
ntalkreply()
{
    char buf[512] ;
    char inbuf[STRLEN*2];

    talkrequest = NA ;
    ntalkrequest = NA ;

    if (setnpagerequest()) return 0;    

#ifdef DOTIMEOUT
    init_alarm();
#else
    signal(SIGALRM, SIG_IGN);
#endif
    lbar("",""); /* ²M°£¥ú´Î */
    clear() ;
    move(1,0);
prints("([1mN[m)¡i©êºp¡A§Ú²{¦b«Ü¦£¡A¤£¯à¸ò§A²á¡C¡j([1mB[m)¡i§Ú²{¦b«Ü·Ð¡A¤£·Q¸ò§O¤H²á¤Ñ¡C ¡j\n");
prints("([1mC[m)¡i§Ú¦³«æ¨Æ¡A§Úµ¥¤@¤U¦A Call §A¡C¡j([1mD[m)¡i½Ð¤£­n¦A Page¡A§Ú¤£·Q¸ò§A²á¡C¡j\n");
prints("([1mE[m)¡i§Ú­nÂ÷¶}¤F¡A¤U¦¸¦b²á§a¡C      ¡j([1mF[m)¡i½Ð±H¤@«Ê«Hµ¹§Ú¡A§Ú²{¦b¨SªÅ¡C ¡j\n");
   sprintf( inbuf, "§A·Q¸ò %s ²á²á¤Ñ¶Ü? (Y N B C D E F)[Y]: ", npage_requestor );

    getdata(0,0, inbuf ,buf,2,DOECHO,NULL,YEA) ;

    if(buf[0] != 'n' && buf[0] != 'N'&& buf[0] != 'B'&& buf[0] != 'b'
       && buf[0] != 'C'&& buf[0] != 'c'&& buf[0] != 'D'&& buf[0] != 'd'
       && buf[0] != 'e'&& buf[0] != 'E'&& buf[0] != 'f'&& buf[0] != 'F') 
    buf[0] = 'y';
    if(buf[0] != 'y') {
        report("page refused");
        ndo_talk(npage_requestor,1) ;
        clear() ;
        refresh();
        return 0 ;
    }
                        
    clear() ;
    report("page accepted");
    ndo_talk(npage_requestor,0);
    clear() ;
    return 0 ;
}
int
talkreply()
{
    int a,saveRMSG;
    struct hostent *h ;
    char buf[512] ;
    char reason[51];
    char hostname[STRLEN] ;
    struct sockaddr_in sin ;
    char inbuf[STRLEN*2];

//modified by paul start
    struct user_info uip;
    int five=0;            
    int tuid;
//modified by paul end

    talkrequest = NA ;
#ifdef BBSNTALKD
    ntalkrequest = NA ;
#endif
    if (setpagerequest(0/*For Talk*/)) return 0;     
    /*  added by netty  */
#ifdef DOTIMEOUT
    init_alarm();
#else
    signal(SIGALRM, SIG_IGN);
#endif
    lbar("",""); /* ²M°£¥ú´Î */
    clear() ;

//modified by paul start
  if(!(tuid = getuser(page_requestorid))) return 0;
  search_ulist( &uip, t_cmpuids, tuid );
  uinfo.destuid = uip.uid;
  getuser(uip.userid);
  if(uip.mode == FIVE) five=1;
//modified by paul end

/* to show plan -cuteyu */
    move( 5, 0 );
    clrtobot();
    show_user_plan(page_requestorid);
    /*Add by SmallPig*/
    move(1,0);
prints("([1mN[m)¡i©êºp¡A§Ú²{¦b«Ü¦£¡A¤£¯à¸ò§A²á¡C¡j([1mB[m)¡i§Ú²{¦b«Ü·Ð¡A¤£·Q¸ò§O¤H²á¤Ñ¡C ¡j\n");
prints("([1mC[m)¡i§Ú¦³«æ¨Æ¡A§Úµ¥¤@¤U¦A Call §A¡C¡j([1mD[m)¡i½Ð¤£­n¦A Page¡A§Ú¤£·Q¸ò§A²á¡C¡j\n");
prints("([1mE[m)¡i§Ú­nÂ÷¶}¤F¡A¤U¦¸¦b²á§a¡C      ¡j([1mF[m)¡i½Ð±H¤@«Ê«Hµ¹§Ú¡A§Ú²{¦b¨SªÅ¡C ¡j\n");
prints("([1mM[m)¡i¯d¨¥µ¹ %-12s           ¡j\n",page_requestorid);

//modified by paul start
  sprintf(inbuf, "§A·Q¸ò %s %s¶Ü¡H½Ð¿ï¾Ü(Y/N/A/B/C/D)[Y] ",page_requestor,(five)?"¤U¤­¤l´Ñ":"²á²á¤Ñ"); 
 //  sprintf( inbuf, "§A·Q¸ò %s ²á²á¤Ñ¶Ü? (Y N B C D E F)[Y]: ", page_requestor );
//modified by paul end
    strcpy(save_page_requestor, page_requestor);
    memset(page_requestor, 0, sizeof(page_requestor));
    memset(page_requestorid, 0, sizeof(page_requestorid));
    getdata(0,0, inbuf ,buf,2,DOECHO,NULL,YEA) ;
    gethostname(hostname,STRLEN) ;
    if(!(h = gethostbyname(hostname))) {
        perror("gethostbyname") ;
        return -1 ;
    }
    memset(&sin, 0, sizeof sin) ;
    sin.sin_family = h->h_addrtype ;
    memcpy( &sin.sin_addr, h->h_addr, h->h_length) ;
    sin.sin_port = ui.sockaddr ;
    a = socket(sin.sin_family,SOCK_STREAM,0) ;
    if((connect(a, (struct sockaddr *)&sin, sizeof sin))) {
        perror("connect err") ;
        return -1 ;
    }
    if(buf[0] != 'n' && buf[0] != 'N'&& buf[0] != 'B'&& buf[0] != 'b'
       && buf[0] != 'C'&& buf[0] != 'c'&& buf[0] != 'D'&& buf[0] != 'd'
       && buf[0] != 'e'&& buf[0] != 'E'&& buf[0] != 'f'&& buf[0] != 'F'
       && buf[0] != 'm'&& buf[0] != 'M')
      buf[0]='y';            

    if(buf[0]=='M'||buf[0]=='m')
    {
       move(1,0);
       clrtobot();
       getdata(1,0, "¯d¸Ü¡G" ,reason,50,DOECHO,NULL,YEA) ;
    }   
    write(a,buf,1) ;
    if(buf[0]=='M'||buf[0]=='m')
          write(a,reason,sizeof reason) ;
    if(buf[0] != 'y') {
        close(a) ;
        report("page refused");
        clear() ;
        refresh();
        return 0 ;
    }
    report("page accepted");
    clear();
    saveRMSG=RMSG; // fix for talking when reply messages
    RMSG=NA;

//modified by paul start
//    do_talk(a) ;
   if(!five) do_talk(a);
   else five_pk(a,0);
//modified by paul end 

    RMSG=saveRMSG;
    close(a) ;
    clear() ;
    refresh();
    return 0 ;
}

int
dotalkent(uentp, buf)
struct user_info *uentp;
char *buf;
{
    char mch;
    if (!uentp->active || !uentp->pid) return -1;
    if(!HAS_PERM(PERM_SYSOP) && uentp->invisible)
        return -1;
    switch(uentp->mode) {
        case ULDL: mch = 'U'; break;
        case TALK: mch = 'T'; break;
        case CHAT1:
        case CHAT2:
        case CHAT3:
        case CHAT4: mch = 'C'; break;
        case IRCCHAT: mch = 'I'; break;
        case FOURM: mch = '4'; break;
        case BBSNET: mch = 'B'; break;
        case READNEW:
        case READING: mch = 'R'; break;
        case POSTING: mch = 'P'; break;
        case SMAIL:
        case RMAIL:
        case MAIL: mch = 'M'; break;
        default: mch = '-';
    }
    sprintf(buf, "%s%s(%c), ", uentp->invisible?"*":"", uentp->userid, mch);
    return 0;
}
 
int
dotalkuent(uentp)
struct user_info *uentp;
{
    char        buf[ STRLEN ];

    if( dotalkent( uentp, buf ) != -1 ) {
        strcpy( talk_uent_buf, buf );
        talk_uent_buf += strlen( buf );
    }
    return 0;
}
 
/*
void
do_talk_nextline( twin )
struct talk_win *twin;
{
    twin->curln = twin->curln + 1;
    if( twin->curln > twin->eline )
        twin->curln = twin->sline;
/*    if( curln != twin->eline ) {
        move( curln + 1, 0 );
        clrtoeol();
    }* /
    move( twin->curln, 0 );
    clrtoeol();
    twin->curcol = 0;
}
*/

void
do_talk_nextline( twin )
struct talk_win *twin;
{
    int line;
    struct screenline *bp;

    twin->curln++;
    if(twin->curln > twin->eline) {
       for(line = twin->sline; line < twin->eline; line++) {
           move(line, 0);
           clrtoeol();
           bp = (struct screenline *)lineptr(line + 1);
           bp->data[bp->len] = '\0';
           outs(bp->data);
       }
       twin->curln = twin->eline;
    }

    move(twin->curln, 0);
    clrtoeol();
    twin->curcol = 0;
} 

void
do_talk_char( twin, ch )
struct talk_win *twin;
int             ch ;
{
    extern int dumb_term ;

    if(isprint2(ch)) {
        if( twin->curcol < 79) {
            move( twin->curln, (twin->curcol)++ );
            prints( "%c",ch );
            return;
        }
        do_talk_nextline( twin );
        twin->curcol++;
        prints( "%c", ch );
        return;
    }
    switch(ch) {
        case Ctrl('H'):
        case '\177':
            if(dumb_term) ochar(Ctrl('H')) ;
            if( twin->curcol == 0 ) {
                return;
            }
            (twin->curcol)-- ;
            move( twin->curln, twin->curcol );
            if(!dumb_term) prints(" ") ;
            move( twin->curln, twin->curcol );
            return ;
        case Ctrl('M'):
        case Ctrl('J'):
            if(dumb_term) prints("\n") ;
            do_talk_nextline( twin );
            return ;
        case Ctrl('G'):
            bell() ;
            return ;
        case Ctrl('R'):
            r_msg();
            return ;
        default:
            break ;
    }
    return ;
}

void
do_talk_string( twin, str )
struct talk_win *twin;
char            *str;
{
    while( *str ) {
        do_talk_char( twin, *str++ );
    }
}

void
dotalkuserlist( twin )
struct talk_win *twin;
{
    char        bigbuf[ MAXACTIVE * 20 ];
    int         savecolumns;

    do_talk_string( twin, "\n*** ¤W½uºô¤Í ***\n" );
    savecolumns = (t_columns > STRLEN ? t_columns : 0);
    talk_uent_buf = bigbuf;
    if( apply_ulist( dotalkuent ) == -1 ) {
        strcpy( bigbuf, "¨S¦³¥ô¦ó¨Ï¥ÎªÌ¤W½u\n" );
    }
    strcpy( talk_uent_buf, "\n" );
    do_talk_string( twin, bigbuf );
    if (savecolumns) t_columns = savecolumns;        
}

char talkobuf[80] ;
int talkobuflen ;
int talkflushfd ;

void
talkflush()
{
    if(talkobuflen) 
      write(talkflushfd,talkobuf,talkobuflen) ;
    talkobuflen = 0 ;
}

int
moveto(mode,twin)
struct talk_win *twin;
{
        if(mode==1)
                twin->curln--;
        if(mode==2)
                twin->curln++;
        if(mode==3)
                twin->curcol++;
        if(mode==4)
                twin->curcol--;
        if(twin->curcol<0)
        {
                twin->curln--;
                twin->curcol=0;
        }else if(twin->curcol>79)
        {
                twin->curln++;
                twin->curcol=0;
        }
        if(twin->curln<twin->sline)
        {
                twin->curln=twin->eline;
        }
        if(twin->curln>twin->eline)
        {
                twin->curln=twin->sline;
        }
        move(twin->curln,twin->curcol);
}

void
endmsg()
{
        int x,y;
        int tmpansi;
        tmpansi=showansi;
        showansi=1;
        talkidletime+=60;
        if(talkidletime>=IDLE_TIMEOUT)
                kill(getpid(),SIGHUP);
        if(uinfo.in_chat == YEA)
                return;
        getyx(&x,&y);
        update_endline();
        signal(SIGALRM, endmsg);
        move(x,y);
        refresh();
        alarm(60);
        showansi=tmpansi;
    return;
}


int
do_talk(fd)
int fd ;
{
    struct talk_win     mywin, itswin;
    char        mid_line[ 256 ];
    int         page_pending = NA;
    int         i,i2;
    int         previous_mode;

    signal(SIGALRM, SIG_IGN);
    endmsg();
    refresh() ;
    previous_mode=uinfo.mode;
    modify_user_mode( TALK );
    sprintf( mid_line, "\x1b[1;31;46m  ÄN\x1b[33m¾ô\x1b[32m²Ó\x1b[34m»y  \x1b[37;45m  %s (%s) ©M %s", 
        currentuser.userid, currentuser.username, save_page_requestor);

    memset( &mywin,  0, sizeof( mywin ) );
    memset( &itswin, 0, sizeof( itswin ) );
    i = (t_lines-1) / 2;
    mywin.eline = i - 1;
    itswin.curln = itswin.sline = i + 1;
    itswin.eline = t_lines - 2;
    move( i, 0 );

    outs( mid_line );
    printoeol();
    outs( "\x1b[m" );
            
    move( 0, 0 );

    talkobuflen = 0 ;
    talkflushfd = fd ;
    add_io(fd,0) ;
    add_flush(talkflush) ;

    while(YEA) {
        int ch ;
        if (talkrequest) page_pending = YEA;
        if (page_pending)
            page_pending = servicepage( (t_lines-1) / 2, mid_line );
        ch = egetch();
        talkidletime=0;
        if ( ch == '' ) 
        {
           igetch();
           igetch();    
           continue;
        }
        if(ch == I_OTHERDATA) {
            char data[80];
            int  datac;
            register int i ;

            datac = read(fd,data,80) ;
            if(datac<=0) 
                break ;
            for(i=0;i<datac;i++)
            {
            if(data[i]>=1&&data[i]<=4)
            {
                moveto(data[i]-'\0',&itswin);
                continue;
            }
                do_talk_char( &itswin, data[i] );
            }
        } else {
            if(ch == Ctrl('D') || ch == Ctrl('C'))
                break ;
            if(isprint2(ch) || ch == Ctrl('H') || ch == '\177'
                || ch == Ctrl('G') || ch == Ctrl('M') ) {
                talkobuf[talkobuflen++] = ch ;
                if(talkobuflen == 80) talkflush() ;
                do_talk_char( &mywin, ch );
            } else if (ch == '\n') {
                talkobuf[talkobuflen++] = '\r';
                talkflush();
                do_talk_char( &mywin, '\r' );
/*            } else if (ch == Ctrl('T')) {
                now=time(0);
                strcpy(ct,ctime(&now));
                do_talk_string( &mywin, ct);
            } else if (ch == Ctrl('U') || ch == Ctrl('W')) {
                dotalkuserlist( &mywin );*/
            }else if(ch>=KEY_UP&&ch<=KEY_LEFT)
            {
                  moveto(ch-KEY_UP+1,&mywin);
                  talkobuf[talkobuflen++] = ch -KEY_UP+1;
                  if(talkobuflen == 80) talkflush() ;
            }
            else if (ch == Ctrl('E')) {
               for(i2=0;i2<=10;i2++)
               {
                talkobuf[talkobuflen++] = '\r';
                talkflush();
                do_talk_char( &mywin, '\r' );
               }
            } else if (ch == Ctrl('P') && HAS_PERM(PERM_BASIC)) {
                t_pager();
                update_utmp();
                update_endline();
            } else if (ch == Ctrl('R')) {
                r_msg();
            }
            
        }
    }
    add_io(0,0) ;
    talkflush() ;
    signal(SIGALRM, SIG_IGN);
    add_flush(NULL) ;
    modify_user_mode(previous_mode);
    return 0;
}

int
shortulist(uentp)
struct user_info *uentp;
{
    int i;
    int pageusers=60;
    extern struct user_info *user_record[];
    extern int range;

    fill_userlist();
    if(ulistpage>((range-1)/pageusers))
        ulistpage=0;
    if(ulistpage<0)
        ulistpage=(range-1)/pageusers;
    move(1,0);
    clrtoeol();
    prints("¨C¹j [1;32m%d[m ¬í§ó·s¤@¦¸¡A[1;32mCtrl-C[m ©Î [1;32mCtrl-D[m Â÷¶}¡A[1;32mF[m §ó´«¼Ò¦¡ [1;32m¡ô¡õ[m ¤W¡B¤U¤@­¶ ²Ä[1;32m %1d[m ­¶",M_INT,ulistpage+1);
    clrtoeol();
    move(3 , 0);
    clrtobot();
    for(i=ulistpage*pageusers;i<(ulistpage+1)*pageusers&&i<range;i++)
    {
        char ubuf[STRLEN];
        int ovv;
        
        if(i<numf||friendmode)
                ovv=YEA;
        else
                ovv=NA;
        sprintf(ubuf,"%s%-12.12s %s%-10.10s[m",(ovv)?"[1;32m¡D":"  ",user_record[i]->userid,(user_record[i]->invisible==YEA)?"[1;34m":"",
        modestring(user_record[i]->mode, user_record[i]->destuid, 0, NULL));
        prints("%s",ubuf);
        if((i+1)%3==0)
                prints("\n");
        else
                prints(" |");
    }
    return range;
}

int
do_list( modestr )
char *modestr;
{       
    char        buf[ STRLEN ];
    int         count;
    extern int RMSG;

    if(RMSG!=YEA)/*¦pªG¦¬¨ì Msg ²Ä¤@¦æ¤£Åã¥Ü¡C*/
    {
            move(0,0);
            clrtoeol();
            if(chkmail())
/* modified by maniac 2/10/98 */
                showtitle(modestr,"[±z¦³«H¥ó]");
            else
                showtitle(modestr,BoardName);
    }
    move(2,0);
    clrtoeol();
    sprintf( buf, "  %-12s %-10s", "¨Ï¥ÎªÌ¥N¸¹", "¥Ø«e°ÊºA" );
    prints( "[1;33;44m%s |%s |%s[m", buf, buf, buf );
/*    if(apply_ulist( shortulist ) == -1) {
        prints("No Users Exist\n") ;
        return 0;
    }
    count = shortulist(NULL);*/
    count = shortulist();
    if (uinfo.mode == MONITOR) {
        time_t thetime = time(0);               
        move(t_lines-1, 0);
        prints("[1;44;33m¥Ø«e¦³ [32m%3d[33m %6s¤W½u, ®É¶¡: [32m%s [33m, ¥Ø«eª¬ºA¡G[36m%10s   [m"
        ,count, friendmode ? "¦nªB¤Í":"¨Ï¥ÎªÌ",Ctime(&thetime),friendmode ? "§Aªº¦nªB¤Í":"©Ò¦³¨Ï¥ÎªÌ");
    }
    refresh();
    return 0;
}

int
t_list()
{
    modify_user_mode( LUSERS );
    report("t_list");
    do_list("¨Ï¥ÎªÌª¬ºA");
    pressreturn();
    refresh();
    clear();
    return 0;
}

                    
void
sig_catcher()
{
    ulistpage++;
    if (uinfo.mode != MONITOR) {
#ifdef DOTIMEOUT
        init_alarm();
#else
        signal(SIGALRM, SIG_IGN);
#endif
        return;
    }           
    if (signal(SIGALRM, sig_catcher)==SIG_ERR) {
        perror("signal");
        exit(1);
    }
/*#ifdef DOTIMEOUT
    idle_monitor_time += M_INT;
    if (idle_monitor_time > MONITOR_TIMEOUT) {
        clear();
        fprintf(stderr, "timeout ...\n");
        kill(getpid(), SIGHUP);
    }
#endif*/
    do_list("±´µø¥Á±¡");
    alarm(M_INT);
}

int
t_monitor()
{
    int i;
        

    alarm(0);
    signal(SIGALRM, sig_catcher);
/*    idle_monitor_time = 0;*/
    report("monitor");
    modify_user_mode( MONITOR );
    ulistpage=0;
    do_list("±´µø¥Á±¡");
    alarm(M_INT);
    while (YEA) {
        i=egetch();
        if(i=='f' ||i=='F'){
                if(friendmode==YEA)
                        friendmode=NA;
                else
                        friendmode=YEA;
                do_list("±´µø¥Á±¡");
        }
        if(i == KEY_DOWN)
        {
                ulistpage++;
                do_list("±´µø¥Á±¡");
        }
        if(i == KEY_UP)
        {
                ulistpage--;
                do_list("±´µø¥Á±¡");
        }
        if (i == Ctrl('D') || i == Ctrl('C')|| i== KEY_LEFT) break;
/*        else if (i == -1) {
            if (errno != EINTR) { perror("read"); exit(1); }
        } else idle_monitor_time = 0;*/
    }
    move(2,0);
    clrtoeol();
    clear();
    return 0;
}

void
exec_cmd( umode, pager, cmdfile )
int     umode, pager;
char    *cmdfile;
{
    char buf[STRLEN*2] ;
    char userhome[STRLEN];
    int save_pager;
    extern int RUNSH;

    if(num_useshell()>=15)
    {
        clear();
        prints("¤Ó¦h¤H¨Ï¥Î¥~³¡µ{¦¡¤F¡A§Aµ¥¤@¤U¦b¥Î...");
        pressanykey(NULL);
        return ;
    }

    if( ! dashf( cmdfile ) ) {
        move(2,0);
        prints( "no %s\n", cmdfile );
        pressreturn();
        return;
    }
    save_pager = uinfo.pager;
    if( pager == NA ) {
        uinfo.pager = 0;
    }
    modify_user_mode( umode );

    sprintf(userhome,"home/%c/%s",toupper(currentuser.userid[0]),currentuser.userid);
    sprintf( buf, "/bin/sh %s %s %s %s", cmdfile, userhome,currentuser.userid, currentuser.username);
    reset_tty() ;
    RUNSH=YEA;
    do_exec(buf,NULL) ;
    RUNSH=NA;
    restore_tty() ;

    uinfo.pager = save_pager;
    clear();
}

void
system_cmd( umode, pager, cmdfile )
int     umode, pager;
char    *cmdfile;
{
    char buf[STRLEN*2] ;
    char userhome[STRLEN];
    int save_pager;
    extern int RUNSH;

    if(num_useshell()>=15)
    {
        clear();
        prints("¤Ó¦h¤H¨Ï¥Î¥~³¡µ{¦¡¤F¡A§Aµ¥¤@¤U¦b¥Î...");
        pressanykey(NULL);
        return ;
    }

    if( ! dashf( cmdfile ) ) {
        move(2,0);
        prints( "no %s\n", cmdfile );
        pressreturn();
        return;
    }
    save_pager = uinfo.pager;
    if( pager == NA ) {
        uinfo.pager = 0;
    }
    modify_user_mode( umode );

    reset_tty() ;
    RUNSH=YEA;
    system(cmdfile);
    RUNSH=NA;
    restore_tty() ;
    uinfo.pager = save_pager;
    clear();
}

#ifdef IRC
void
t_irc() {
    exec_cmd( IRCCHAT, NA, "bin/irc.sh" );
}
#endif /* IRC */

void
t_announce() {
    exec_cmd( CSIE_ANNOUNCE, YEA, "bin/faq.sh" );
}

void
t_tin() {
    exec_cmd( CSIE_TIN, YEA, "bin/tin.sh" );
}

void
t_gopher() {
    exec_cmd( CSIE_GOPHER, YEA, "bin/gopher.sh" );
}
void
t_www() {
    exec_cmd( WWW, YEA, "bin/www.sh" );
}

/*Add By Excellent*/
void
x_excemj() {
    signal(SIGTTOU,SIG_IGN);
    clear();
    exec_cmd( EXCE_MJ, NA, "bin/exemj.sh" );
    signal(SIGTTOU,r_msg);
        }
        
void
x_excefc() {
    signal(SIGTTOU,SIG_IGN);
    clear();
    exec_cmd( EXCE_FCHESS, NA, "bin/exefc.sh" );
    signal(SIGTTOU,r_msg);
        }
        
void
x_excetet() {
    signal(SIGTTOU,SIG_IGN);
    clear();
    exec_cmd( EXCE_TETRIS, NA, "bin/exetetris.sh" );
    signal(SIGTTOU,r_msg);
        }        
        
void
x_excetet2() {
    signal(SIGTTOU,SIG_IGN);
    clear();
    exec_cmd( EXCE_TETRIS, NA, "bin/exetetris2.sh" );
    signal(SIGTTOU,r_msg);
        }        

void
x_excefc2() {
    signal(SIGTTOU,SIG_IGN);
    clear();
    system_cmd(EXCE_FCHESS,NA,"bin/exefc2.sh");
    signal(SIGTTOU,r_msg);
        }  
        
void
x_excecon() {
    signal(SIGTTOU,SIG_IGN);
    clear();
    system_cmd(EXCE_CONCHESS,NA,"bin/execon.sh");
    signal(SIGTTOU,r_msg);
        }  
      
void
x_excebw() {
    signal(SIGTTOU,SIG_IGN);
    clear();
    system_cmd(EXCE_BWCHESS,NA,"bin/exebw.sh" );
    signal(SIGTTOU,r_msg);
        }

void
x_excebig2() {
    clear();
    signal(SIGTTOU,SIG_IGN);
    clear();
    system_cmd(EXCE_BIG2,NA, "bin/exebig2.sh" );
    signal(SIGTTOU,r_msg);
        }

/* Add By Excellent */
void
x_excechess() {
    clear();
    exec_cmd( EXCE_CHESS, YEA, "bin/excechess.sh" );
        }        


/*Add by SmallPig*/
int
seek_in_file(filename,seekstr)
char filename[STRLEN],seekstr[STRLEN];
{
    FILE *fp;
    char buf[STRLEN];
    char *namep;

    if ((fp = fopen(filename, "r")) == NULL)
        return 0;
    while (fgets(buf, STRLEN, fp) != NULL) {
        namep = (char *)strtok( buf, ": \n\r\t" );
        if (namep != NULL && ci_strcmp(namep, seekstr) == 0 ) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}


int
can_override( userid, whoasks )
char *userid;
char *whoasks;
{
    struct friend fh;

    sethomefile( genbuf, userid, "friends" );
    return  (search_record( genbuf, &fh, sizeof(fh), cmpfnames, whoasks )>0)?YEA:NA;
}

int
listfilecontent(fname)
char *fname;
{
    FILE *fp;
    int x = 0, y = 3, cnt = 0, max = 0, len;
    char u_buf[20], line[STRLEN], *nick;

    move(y,x);
    CreateNameList();
    strcpy(genbuf,fname);
    if ((fp = fopen(genbuf, "r")) == NULL) {
        prints("(none)\n");
        return 0;
    }
    while(fgets(genbuf, STRLEN, fp) != NULL) {
        strtok( genbuf, " \n\r\t" );
        strcpy( u_buf, genbuf );
        AddNameList( u_buf );
        nick = (char *) strtok( NULL, "\n\r\t" );
        if( nick != NULL ) {
            while( *nick == ' ' )  nick++;
            if( *nick == '\0' )  nick = NULL;
        }
        if( nick == NULL ) {
            strcpy( line, u_buf );
        } else {
            sprintf( line, "%-12s%s", u_buf, nick );
        }
        if( (len = strlen( line )) > max )  max = len;
        if( x + len > 78 )  line[ 78 - x ] = '\0';
        prints( "%s", line );
        cnt++;
        if ((++y) >= t_lines-1) {
            y = 3;
            x += max + 2;
            max = 0;
            if( x > 70 )  break;
        }
        move(y,x);
    }
    fclose(fp);
    if (cnt == 0) prints("(none)\n");
    return cnt;
}

int
addtofile(filename,str)
char filename[STRLEN],str[STRLEN];
{
    FILE *fp;
    int rc;

    if ((fp = fopen(filename, "a")) == NULL)
        return -1;
    flock(fileno(fp), LOCK_EX);
    rc = fprintf( fp, "%s\n",str);
    flock(fileno(fp), LOCK_UN);
    fclose(fp);
    return(rc == EOF ? -1 : 1);
}

int
addtooverride(uident)
char *uident;
{
    struct friend tmp;
    int  n;
    char buf[STRLEN];
    
    memset(&tmp,0,sizeof(tmp));
    setuserfile( buf, "friends" );
    if(get_num_records(buf,sizeof(struct friend))>=MAXFRIENDS)
    {
           move(t_lines-2,0);
           clrtoeol();
           prints("©êºp¡A¨Ì·Ó§Aªº¸gÅç­È¡A§A¥u¯à³]©w %d ­Ó¦n¤Í, ½Ð«ö¥ô¦ó¥óÄ~Äò...",MAXFRIENDS);
           egetch();
           move(t_lines-2,0);
           clrtoeol();
           return -1;
    }
    if( myfriend( getuser(uident) ) || strcmp(uident,currentuser.userid)==0 || 
        badfriend( getuser(uident), &uinfo ) )
        return -1;
   if(uinfo.mode!=LUSERS&&uinfo.mode!=LAUSERS&&uinfo.mode!=FRIEND)
   {
           strcpy(tmp.id,uident);
           move(2,0);
           clrtoeol();
           sprintf(genbuf,"½Ð¿é¤Jµ¹¦n¤Í¡i%s¡jªº»¡©ú: ",tmp.id);
           getdata(2,0,genbuf, tmp.exp,14,DOECHO,NULL,YEA);
           move(2,0);
           clrtoeol();
           getdata(2,0,"·l¤Í(y/N):",genbuf,2,DOECHO,NULL,YEA);
   }
   else
   {
           move(t_lines-2,0);
           clrtoeol();
           refresh();
           strcpy(tmp.id,uident);
           sprintf(genbuf,"½Ð¿é¤Jµ¹¦n¤Í¡i%s¡jªº»¡©ú: ",tmp.id);
           getdata(t_lines-2,0,genbuf, tmp.exp,14,DOECHO,NULL,YEA);
           move(t_lines-2,0);
           clrtoeol();
           getdata(t_lines-2,0,"·l¤Í(y/N):",genbuf,2,DOECHO,NULL,YEA);           
   }
   
   if(genbuf[0]=='y' || genbuf[0]=='Y') tmp.type=FR_BAD; else tmp.type=FR_GOOD;
    setuserfile( genbuf, "friends" );
    n=append_record(genbuf,&tmp,sizeof(struct friend));
    if(n!=-1)
            getfriendstr();
    else
        report("append friendfile error");
        
    return n;
} 

int
del_from_file(filename,str)
char filename[STRLEN],str[STRLEN];
{
    FILE *fp, *nfp;
    int deleted = NA;
    char fnnew[STRLEN];

    if ((fp = fopen(filename, "r")) == NULL) return -1;
    sprintf( fnnew, "%s.%d", filename, getuid());
    if ((nfp = fopen(fnnew, "w")) == NULL) return -1;
    while(fgets(genbuf, STRLEN, fp) != NULL) {
        if( strncmp(genbuf, str, strlen(str)) == 0 )
            deleted = YEA;
        else if( *genbuf > ' ' )
            fputs(genbuf, nfp);
    }
    fclose(fp);
    fclose(nfp);
    if (!deleted) return -1;
    return(rename(fnnew, filename));
}


int
deleteoverride(uident)
char *uident;
{
    int deleted;
    struct friend fh;

    setuserfile( genbuf, "friends" );
    deleted = search_record( genbuf, &fh, sizeof(fh), cmpfbnames, uident );
    if(deleted>0)
    {
        if(delete_record(genbuf,sizeof(fh),deleted)!=-1)
                getfriendstr();
        else
        {
           deleted=-1;
           report("delete friend error");
        }
    }
    return (deleted>0)?1:-1;
}

friend_title()
{
    if ( chkmail() )
        strcpy( genbuf, "[±z¦³«H¥ó]" );
    else                
        strcpy( genbuf, BoardName );
    showtitle("[½s¿è¦n¤Í¦W³æ]",genbuf);

    prints(" [[1;32m¡ö[m,[1;32me[m] Â÷¶} [[1;32mh[m] ¨D§U [[1;32m¡÷[m,[1;32mr[m] ¦n¤Í»¡©úÀÉ [[1;32m¡ô[m,[1;32m¡õ[m] ¿ï¾Ü [[1;32ma[m] ¼W¥[¦n¤Í [[1;32md[m] §R°£¦n¤Í\n");
    prints("[1;44m ½s¸¹  ¦n¤Í¥N¸¹      ¦n¤Í»¡©ú                                                   [m\n");
}

char *
friend_doentry(ent,fh)
int ent;
struct friend *fh;
{
        static char buf[STRLEN/2];
        
        sprintf(buf," %4d  %-12.12s  %s",ent,fh->id,fh->exp);
        return buf;
}

int
friend_edit(ent,fh,direc)
int ent;
struct friend *fh;
char *direc;
{
     struct friend nh;        
     char buf[STRLEN/2];
     int pos;  

     pos=search_record( direc, &nh, sizeof(nh), cmpfbnames, fh->id );
     move(t_lines-2,0);
     clrtoeol();
     if(pos>0)
     {
        sprintf(buf,"½Ð¿é¤J %s ªº·s¦n¤Í»¡©ú: ",fh->id);
        getdata(t_lines-2,0,buf,nh.exp,15,DOECHO,NULL,NA);
     }
      if(substitute_record(direc, &nh, sizeof(nh), pos)<0)
        report("Friend files subs err");
      move(t_lines-2,0);
      clrtoeol();
      return NEWDIRECT;
}

int
friend_help()
{
        show_help("help/friendshelp");
        return FULLUPDATE;
}

int
friend_add(ent,fh,direct)
int ent;
struct friend *fh;
char *direct;
{
      char uident[13];

      clear();
      move(1,0);
      usercomplete("½Ð¿é¤J­n¼W¥[ªº¥N¸¹: ", uident);
      if( uident[0] != '\0' )
      {
        if(getuser(uident)<=0)
        {
                move(2,0);
                prints("¿ù»~ªº¨Ï¥ÎªÌ¥N¸¹...");
                pressanykey(NULL);
        }else
           addtooverride(uident);
      }
      return FULLUPDATE;
}

int
friend_dele(ent,fh,direct)
int ent;
struct friend *fh;
char *direct;
{
      char buf[STRLEN];
      int deleted=NA;

      saveline(t_lines-2, 0);
      move(t_lines-2,0);
      clrtoeol();
      sprintf(buf,"¬O§_§â¡i%s¡j±q¦n¤Í¦W³æ¤¤¥h°£",fh->id);
      if(askyn(buf,NA)==YEA)
      {
         move(t_lines-2,0);
         clrtoeol();
         if(deleteoverride(fh->id)==1)
         {
                prints("¤w±q¦n¤Í¦W³æ¤¤²¾°£¡i%s¡j,«ö¥ô¦óÁäÄ~Äò...",fh->id);
                deleted=YEA;
         }
         else
                prints("§ä¤£¨ì¡i%s¡j,«ö¥ô¦óÁäÄ~Äò...",fh->id);
      }
      else
      {
         move(t_lines-2,0);
         clrtoeol();
         prints("¨ú®ø§R°£¦n¤Í...");
      }
      igetkey();
      move(t_lines-2,0);
      clrtoeol();
      saveline(t_lines-2, 1);
      return (deleted)?PARTUPDATE:DONOTHING;
}

int
friend_mail(ent,fh,direct)
int ent;
struct friend *fh;
char *direct;
{
      if(!HAS_PERM(PERM_POST))
          return DONOTHING;
      m_send(fh->id);
      return FULLUPDATE;
}

int
friend_query(ent,fh,direct)
int ent;
struct friend *fh;
char *direct;
{
    int ch;

    if(t_query(fh->id)==-1)
        return FULLUPDATE;
    move(t_lines-1, 0);
    clrtoeol();
    prints("[44m[1;31m[Åª¨ú¦n¤Í»¡©úÀÉ][33m ±H«Hµ¹¦n¤Í m ¢x µ²§ô Q,¡ö ¢x¤W¤@¦ì ¡ô¢x¤U¤@¦ì <Space>,¡õ      [m");
    ch = egetch();
    switch( ch ) {
        case 'N': case 'Q':
        case 'n': case 'q': case KEY_LEFT:
                break;
        case 'm': case 'M':
             m_send(fh->id);
             break;
        case ' ':
        case 'j': case KEY_RIGHT: case KEY_DOWN: case KEY_PGDN:
                return READ_NEXT;
        case KEY_UP: case KEY_PGUP:
                return READ_PREV;
        case Ctrl('R'): r_msg(); break;        
        default : break;
    }
    return FULLUPDATE ;
}

void
t_override()
{
    
    setuserfile( genbuf, "friends" );
    i_read( GMENU, genbuf , friend_title , friend_doentry, friend_list ,sizeof(struct friend));
    clear();
    return;
}               

struct user_info *
t_search(sid,pid)
char *sid;
int  pid;
{
    int         i;
    extern      struct UTMPFILE *utmpshm;
    struct      user_info *cur,*tmp=NULL;

    resolve_utmp();
    for( i = 0; i < USHM_SIZE; i++ ) 
    {
        cur = &(utmpshm->uinfo[ i ]);
        if (!cur->active || !cur->pid )
            continue;
        if( !strcasecmp(cur->userid,sid) ) 
        {
                if(pid==0)
                        return cur;
                tmp=cur;
                if(pid==cur->pid)
                        break;
        }
    }
    return tmp;
}

int
cmpfuid( a,b )
struct friend   *a,*b;
{
    return strcasecmp(a->id,b->id);
}

int
getfriendstr()
{
    extern int nf;
    
    fill_flist(); // add by Magi
    update_utmp();    

    if(topfriend!=NULL)
        free(topfriend);
    setuserfile( genbuf, "friends" );
    nf=get_num_records(genbuf,sizeof(struct friend));
    if(nf<=0)
        return 0;
    nf=(nf>=MAXFRIENDS)?MAXFRIENDS:nf;
    topfriend=(struct friend *)calloc(sizeof(struct friend),nf);
    get_records(genbuf,topfriend,sizeof(struct friend),1,nf);
    qsort( topfriend, nf, sizeof( topfriend[0] ), cmpfuid );/*For Bi_Search*/


}

int
wait_friend()
{
        FILE *fp;
        int tuid;       
        char buf[STRLEN];
        char uid[13];

        modify_user_mode( WFRIEND );
        clear();
        move(1,0);
        usercomplete("½Ð¿é¤J¨Ï¥ÎªÌ¥N¸¹¥H¥[¤J¨t²Îªº´M¤H¦W¥U: ", uid);
        if(uid[0] == '\0') 
        {
          clear() ;
          return 0 ;
        }
        if(!(tuid = getuser(uid))) 
        {
          move(2,0) ;
          prints("[1m¤£¥¿½Tªº¨Ï¥ÎªÌ¥N¸¹[m\n") ;
          pressanykey(NULL) ;
          clear();
          return -1 ;
        }
        sprintf(buf,"§A½T©w­n§â [1m%s[m ¥[¤J¨t²Î´M¤H¦W³æ¤¤",uid);
        move(2,0);
        if(askyn(buf,YEA)==NA)
        {
                clear();
                return;
        }
        if((fp=fopen("friendbook","a"))==NULL)
        {
                prints("¨t²Îªº´M¤H¦W¥UµLªk¶}±Ò¡A½Ð³qª¾¯¸ªø...\n");
                pressanykey(NULL);
                return NA;
        }
        sprintf(buf,"%d@%s",tuid,currentuser.userid);
        if(!seek_in_file("friendbook",buf))
           fprintf(fp,"%s\n",buf);
        fclose(fp);
        move(3,0);
        prints("¤w¸gÀ°§A¥[¤J´M¤H¦W¥U¤¤¡A[1m%s[m ¤W¯¸¨t²Î¤@©w·|³qª¾§A...\n",uid);
        pressanykey(NULL);
        clear();
        return;
}

int
t_useridle()
{
char genbuf[20];
int old_mode;

       old_mode=uinfo.mode;
       modify_user_mode(IDLE);
       getdata(22,0,"²z¥Ñ¡G[0]µo§b (1)±µ¹q¸Ü (2)³V­¹ (3)¥´½OºÎ (4)¸Ë¦º (5)Ã¹¤¦ (6)¨ä¥L (Q)¨S¨Æ¡H", genbuf, 2, DOECHO, NULL,YEA);
       switch (genbuf[0])
       {
       case '0': strcpy(uinfo.chatid,"°¸¦bªá§b°Õ"); break;
       case '1': strcpy(uinfo.chatid,"±¡¤H¨Ó¹q"); break;
       case '2': strcpy(uinfo.chatid,"³V­¹¤¤"); break;
       case '3': strcpy(uinfo.chatid,"«ô¨£©P¤½"); break;
       case '4': strcpy(uinfo.chatid,"°²¦ºª¬ºA"); break;
       case '5': strcpy(uinfo.chatid,"§Ú¦b«ä¦Ò"); break;
       case '6': 
          getdata(23,0,"µo§bªº²z¥Ñ¡G",uinfo.chatid,sizeof(uinfo.chatid),DOECHO,NULL,YEA); 
          break;
       case 'Q':
       case 'q': 
                 modify_user_mode(old_mode); 
                 return -1;
       default : strcpy(uinfo.chatid,"°¸¦bªá§b°Õ"); 
       }
       move(23,0);
       clrtoeol();
       prints("µo§b¤¤:%s",uinfo.chatid);
       update_ulist( &uinfo, utmpent );
       refresh();
       igetkey();
       uinfo.chatid[0]=0;
       modify_user_mode(old_mode);
       update_ulist( &uinfo, utmpent);
}

int count_friend_me(uentp)  // ºâ¦³¦h¤Ö¤H»P§Ú¬°¤Í
struct user_info *uentp ;
{
    static int count ;

    if(uentp == NULL) {
        int c = count;
        count = 0;
        return c;
    }
    
    if(uentp->uid==usernum || !uentp->active || !uentp->pid || ( !HAS_PERM(PERM_SEECLOAK) && uentp->invisible) ) return 0;
    
    if(friendwithme(uentp))
	 { count++ ; return 1; }
    return 0 ;
}

int count_bad_friend(uentp)  // ºâ¦³¦h¤ÖÃa¤H
struct user_info *uentp ;
{
    static int count ;
    int i=0;

    if(uentp == NULL) {
        int c = count;
        count = 0;
        return c;
    }
    if(uentp->uid==usernum || !uentp->active || !uentp->pid ||( !HAS_PERM(PERM_SEECLOAK) &&  uentp->invisible)) return 0;
    
    if( badfriend(uentp->uid,&uinfo) )
	 { count++ ; return 1; }
    return 0 ;
}

int badfriend(int uid, struct user_info *u2)  // Check if uid in u2's blacklist
{
    int i=0;
    
    while(u2->friend[i].uid!=-1)
    {
           if((uid==u2->friend[i].uid) && (u2->friend[i].type==FR_BAD))
                return 1;
           i++; }
    return 0;
}
