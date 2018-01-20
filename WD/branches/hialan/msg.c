int
talk_mail2user()
{
  char fname[128];

  setuserfile(fname, fn_writelog);
  mail2user(cuser.userid, "¼ö½u\033[37;41m°O¿ý\033[m", fname);
  unlink(fname);
  
  /* itoc.011104: delete BMW */
  sethomefile(fname, cuser.userid, FN_BMW);
  unlink(fname);
  
  return 0;
}

int
my_write(pid, hint)
  pid_t pid;
  char *hint;
{
   if (*hint != 1) 
   {
      sethomefile(genbuf, uin->userid, fn_writelog);
      if (fp = fopen(genbuf, "a")) 
      {
        fprintf(fp, COLOR2"[1;33;41m¡i[37m %s [33m¡j[1;47;34m %s %s [0m[%s]\n",
          cuser.userid, (*hint == 2) ? "[1;33;42m¼s¼½" : "", msg, Cdatelite(&now));
        fclose(fp);
      }
      sethomefile(genbuf, cuser.userid, fn_writelog);
      if (fp = fopen(genbuf, "a")) 
      {
        fprintf(fp, "To %s: %s [%s]\n", uin->userid, msg, Cdatelite(&now));
        fclose(fp);
        update_data();
        ++cuser.sendmsg;
        substitute_record(fn_passwd, &cuser, sizeof(userec), usernum);
      }
/* itoc.011104: for BMW */
      {
        fileheader bmw;
        time_t now = time(0);
        struct tm *ptime = localtime(&now);
        
        sprintf(bmw.date, "%02d:%02d", ptime->tm_hour, ptime->tm_min);
        strcpy(bmw.title, msg);
                                                                                
        bmw.savemode = 1;             /* ¹ï¤è¬O±µ¦¬ºÝ */
        strcpy(bmw.owner, cuser.userid);
        sethomefile(genbuf, uin->userid, FN_BMW);
        rec_add(genbuf, &bmw, sizeof(fileheader));
                                                                                
        bmw.savemode = 0;             /* §Ú¬O¶Ç°eºÝ */
        strcpy(bmw.owner, uin->userid);
        sethomefile(genbuf, cuser.userid, FN_BMW);
        rec_add(genbuf, &bmw, sizeof(fileheader));
      }
   }
   if (*hint == 2 && uin->msgcount) 
   {
      uin->destuip = currutmp;
      uin->sig = 2;
      kill(uin->pid, SIGUSR1);
   }

}

/* itoc.011104: for BMW */
int
bmw_refresh()
{
  return RC_FULL;
}

extern int write_msg();  //bbs.c

struct one_key bmwlist_key[]={
'w' , write_msg,
's' , bmw_refresh,
'\0', NULL};

void
bmwtitle()
{
  char buf[256];
  
  sprintf(buf,"%s [½u¤W %d ¤H]",BOARDNAME, count_ulist());
  showtitle("¤ô²y¦^ÅU", buf);

  prints("[¡ô/¡õ]¤W¤U [PgUp/PgDn]¤W¤U­¶ [Home/End]­º§À [¡ö][q]Â÷¶}\n");
  prints("\033[1;37;46m ½s¸¹ ¥N ¸¹       ¤ß  ±¡  ¬G  ¨Æ"
         "                                         ®É¶¡ \033[m\n");
}

void
bmw_lightbar(num, bmw, row, bar, barcolor)
   fileheader *bmw;
   int bar, row, num;
   char *barcolor;
{
  move(row, 0);
  clrtoeol();
  prints("%4d %s%-13s%s%-55.55s\033[m%s",
       num, (barcolor) ? barcolor : (bmw->savemode) ? "\033[33m" : "\033[m", 
       bmw->owner, (bmw->savemode) ? "\033[0;33m" : "\033[m", 
       bmw->title, bmw->date);
}

                                                                                
int
t_bmw()
{
  char fname[80];
  char *choose[3] = {"cC.²M°£","mM.²¾¦Ü³Æ§Ñ¿ý","rR.«O¯d"};  
  
  sethomefile(fname, cuser.userid, FN_BMW);
  if(dashf(fname))
  {
    i_read(SEEWATER, fname, bmwtitle, bmw_lightbar, bmwlist_key, NULL);
  
    switch (getans2(b_lines, 0, "", choose, 3, 'r'))
    {
      case 'm':
        talk_mail2user();
        break;            
    
      case 'c':
        unlink(fname);
           
        /* itoc.011104: delete BMW */
        sethomefile(fname, cuser.userid, fn_writelog);
        unlink(fname);

      default:
        break;
    }
  }
  else
    pressanykey("±z©|¥¼¦¬¨ì¤ô²y³á!!");
  
  return RC_FULL;
}
