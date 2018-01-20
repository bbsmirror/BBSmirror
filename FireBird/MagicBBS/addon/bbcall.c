/*-------------------------------------------------------*/
/* alphacall.c       ( NTHU CS MapleBBS Ver 3.00 )       */
/*-------------------------------------------------------*/
/* author : yshuang@dragon2.net                          */
/* target : BBS 網路傳呼 0943/0946 聯華 Alphacall        */
/*                      & 0948 大眾電信                  */
/* create : 98/12/01                                     */
/* update : 98/12/10                                     */
/*-------------------------------------------------------*/

// MagicBBS patch begin
#include <stdio.h>

#define msg_sure_ny "\n您確定嗎(Y/n):"
#define cuser currentuser
#define vmsg(s) { prints("%s\n",s); pressanykey(NULL); }
#define outz(s) prints("%s\n",s)
#define vget(a,b,c,d,e,f) getdata(a,b,c,d,e,f,NULL,YEA)

int vans(char *s)
{
    char ch;

    prints(s);    
    ch=egetch();   
    outs("\n");
    if(ch=='Y') ch='y';
    return ch;
    
}

int f_cat(char *fname,char *buf)
{
    FILE *fp;
    
    if(fp=fopen(fname,"a+"))
     {
       fprintf(fp,buf);
       fclose(fp); }
}

void
str_ncpy(dst, src, n)
char *dst;
char *src;
int n;
{
        char *end;
        
        end = dst + n - 1;
          
        do
         {
            n = (dst >= end) ? 0 : *src++;
            *dst++ = n;
         } while (n);
}

char * 
str_str(str, tag) 
  char *str; 
  char *tag;                  /* non-empty lower case pattern */ 
{ 
  int cc, c1, c2;
  char *p1, *p2;

  cc = *tag++;
 
  while (c1 = *str)
  {
    if (c1 >= 'A' && c1 <= 'Z')
      c1 |= 0x20;

    if (c1 == cc)
    {
      p1 = str;
      p2 = tag;

      do
      {
        c2 = *p2;
        if (!c2)
          return str;
 
        p2++;
        c1 = *++p1;
        if (c1 >= 'A' && c1 <= 'Z')
          c1 |= 0x20;
      } while (c1 == c2);
    }
 
    str++;
  }

  return NULL;
}

// MagicBBS patch end

#include "bbs.h"

#include <stdlib.h>   
#include <netdb.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define	SERVER_0943	"www.pager.com.tw"
#define	SERVER_0948	"www.fitel.net.tw"

#define CGI_0943	"/tpn/tpnasp/dowebcall.asp"
#define CGI_0948	"/cgi-bin/ip.exe"

#define REFER_0943	"http://www.pager.com.tw/tpn/webcall/webcall.asp"
#define REFER_0948	"http://www.fitel.net.tw/html/svc03.htm#top"

#define LOG_0943	"log/0943.log"
#define LOG_0946	"log/0946.log"	
#define LOG_0948	"log/0948.log"

#define	WEBPORT		80
#define PARA		"Connection: Keep-Alive\nUser-Agent: Mozilla/4.5b1 [en] (X11; I; FreeBSD 2.2.7-STABLE i386)\nContent-type: application/x-www-form-urlencoded\nAccept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, image/png, */*\nAccept-Encoding: gzip\nAccept-Language: en\nAccept-Charset: iso-8859-1,*,utf-8\n"


void 
alpha0943()
{
  int sockfd;
  char *CoId="0943", ID[6], Name[32], FriendPassword[32];
  char Msg[64], trn[512], result[1024], sendform[512];
  struct sockaddr_in serv_addr; 
  struct hostent *hp;

#if 0
  memset(trn, 0, 512);
  memset(sendform, 0, 512);
  memset(result, 0, 4096);
  memset(buf, 0, 2048);
  memset(Name, 0, 32);
  memset(ID, 0, 16);
  memset(Msg, 0, 64);
#endif

  clear();
  
  if ((!vget(0, 0, "請輸入您要傳呼的號碼：0943-", ID, 7, DOECHO) &&
       !vget(1, 0, "請輸入您要傳呼的代號：", Name, 32, DOECHO)) ||
         !vget(2, 0, "請輸入傳呼訊息：", Msg, 64, DOECHO))
  {
    vmsg("放棄傳呼");
    return;
  }

  move(3, 0);
  prints("你所要傳呼的號碼：%s", ID);
  move(4, 0);
  prints("你所要傳呼的訊息：%s", Msg);

  if (vans(msg_sure_ny) != 'y')
  {
    vmsg("放棄傳呼");
    return;
  }

  sprintf(result, "User %s called 0943%s Name = %s\nMsg = %s\n",
            cuser.userid, ID, Name, Msg);
  f_cat(LOG_0943, result);
	
  sprintf(trn,"CoId=%s&ID=%s&Name=%s&FriendPassword=%s&&Year=1998&Month=12&Day=04&Hour=13&Minute=08&Msg=%s",
	    CoId, ID, Name, FriendPassword, Msg);
	
  sprintf(sendform, "POST %s HTTP/1.0\nReferer: %s\n%sContent-length:%d\n\n%s",
            CGI_0943, REFER_0943, PARA, strlen(trn), trn);
  		
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    return; 

  memset((char *)&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;

  if ((hp = gethostbyname(SERVER_0943)) == NULL) 
    return;

  memcpy(&serv_addr.sin_addr, hp->h_addr, hp->h_length);
	
  serv_addr.sin_port = htons(WEBPORT);
	
  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof serv_addr))
  {
    sprintf(result,"無法連線，傳呼失敗\n");
    f_cat(LOG_0943, result);
    vmsg("無法與伺服器取得連結，傳呼失敗");
    return;
  }
  else
  {
    outz("伺服器已經連接上，請稍後");
    refresh();
  }

  write(sockfd, sendform, strlen(sendform));
  shutdown(sockfd, 1);
	
  while (read(sockfd, result, sizeof(result)) > 0)
  {
    if (strstr(result, "正確") != NULL)
    {
      close(sockfd);
      f_cat(LOG_0943, result);
      vmsg("順利送出傳呼");
      return;
    }
    f_cat(LOG_0943, result);
    memset(result, 0, sizeof(result));
  }      
  
  close(sockfd);
  vmsg("無法順利送出傳呼");
  return;
}


void 
alpha0946()
{
  int sockfd;
  char *CoId="0946", ID[6], Name[32], FriendPassword[32];
  char Msg[64], trn[512], result[1024], sendform[512];
  struct sockaddr_in serv_addr; 
  struct hostent *hp;

#if 0
  memset(trn, 0, 512);
  memset(sendform, 0, 512);
  memset(result, 0, 4096);
  memset(buf, 0, 2048);
  memset(Name, 0, 32);
  memset(ID, 0, 16);
  memset(Msg, 0, 64);
#endif

  clear();
  
  if ((!vget(0, 0, "請輸入您要傳呼的號碼：0946-", ID, 7, DOECHO) &&
       !vget(1, 0, "請輸入您要傳呼的代號：", Name, 32, DOECHO)) ||
         !vget(2, 0, "請輸入傳呼訊息：", Msg, 64, DOECHO))
  {
    vmsg("放棄傳呼");
    return;
  }

  move(3, 0);
  prints("你所要傳呼的號碼：%s", ID);
  move(4, 0);
  prints("你所要傳呼的訊息：%s", Msg);

  if (vans(msg_sure_ny) != 'y')
  {
    vmsg("放棄傳呼");
    return;
  }

  sprintf(result, "User %s called 0946%s Name = %s\nMsg = %s\n",
            cuser.userid, ID, Name, Msg);
  f_cat(LOG_0946, result);
	
  sprintf(trn,"CoId=%s&ID=%s&Name=%s&FriendPassword=%s&&Year=1998&Month=12&Day=04&Hour=13&Minute=08&Msg=%s",
	    CoId, ID, Name, FriendPassword, Msg);
	
  sprintf(sendform, "POST %s HTTP/1.0\nReferer: %s\n%sContent-length:%d\n\n%s",
            CGI_0943, REFER_0943, PARA, strlen(trn), trn);
  		
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    return; 

  memset((char *)&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  
  if ((hp = gethostbyname(SERVER_0943)) == NULL) 
    return;

  memcpy(&serv_addr.sin_addr, hp->h_addr, hp->h_length);
  serv_addr.sin_port = htons(WEBPORT);
	
  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof serv_addr))
  {
    sprintf(result,"無法連線，傳呼失敗\n");
    f_cat(LOG_0946, result);
    vmsg("無法與伺服器取得連結，傳呼失敗");
    return;
  }
  else
  {
    outz("伺服器已經連接上，請稍後");
    refresh();
  }

  write(sockfd, sendform, strlen(sendform));
  shutdown(sockfd, 1);
	
  while (read(sockfd, result, sizeof(result)) > 0)
  {
    if (strstr(result, "正確") != NULL)
    {
      close(sockfd);
      f_cat(LOG_0946, result);
      vmsg("順利送出傳呼");
      return;
    }
    f_cat(LOG_0946, result);
    memset(result, 0, sizeof(result));
  }      
  
  close(sockfd);
  vmsg("無法順利送出傳呼");
  return;
}


void 
fitel()
{
  int i, sockfd;
  char svc_no[6], message[60], trn[512];
  char *pwd_in = "%ABP%BEP%B4%C1%B6%A1%A1A%A4%F0%BB%DD%BF%E9%A4J";
  char *sender_name = "+", *reminder_option = "OFF";
  char *isp_code = "1", result[2048], sendform[512];
  char ch, res[9], *result_ptr;
  struct sockaddr_in serv_addr; 
  struct hostent *hp;

#if 0
  bzero(trn,512);
  bzero(sendform,512);
  bzero(result,2048);
  bzero(buf,2048);
  bzero(svc_no,16);
  bzero(message,64);
#endif

  clear();
  
  if (!vget(0, 0, "請輸入您要傳呼的號碼：0948-", svc_no, 7, DOECHO) ||
       !vget(1, 0, "請輸入傳呼訊息：", message, 61, DOECHO))
  {
    vmsg("放棄傳呼");
    return;
  }

  move(2, 0);		
  prints("你所要傳呼的號碼：%s", svc_no);
  move(3, 0);
  prints("你所要傳呼的訊息：%s", message);

  if (vans(msg_sure_ny) != 'y')
  {
    vmsg("放棄傳呼");
    return;
  }

  sprintf(trn, "svc_no=%s&pwd_in=%s&isp_code=%s&sender_name=%s&message=%s&reminder_option=%s&year=87&month=08&day=27&hour=00&min=00\n",
           svc_no, pwd_in, isp_code, sender_name, message, reminder_option);

  sprintf(sendform, "POST %s HTTP/1.0\nReferer: %s\n%sContent-length:%d\n\n%s",
           CGI_0948, REFER_0948, PARA, strlen(trn), trn);
			
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    return; 
	
  memset((char *)&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
	
	
  if ((hp = gethostbyname(SERVER_0948)) == NULL) 
    return;

  memcpy(&serv_addr.sin_addr, hp->h_addr, hp->h_length);
  serv_addr.sin_port = htons(WEBPORT);
	
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof serv_addr))
  {
    vmsg("無法連線，傳呼失敗");
    return;
  }
  else
  {
    outz("伺服器已經連接上，請稍後");
    refresh();
  }

  write(sockfd, sendform, strlen(sendform));

  shutdown(sockfd, 1);

  i = 0;
  while (read(sockfd, &ch, 1))
    result[i++] = ch;
  result[i]='\0';

  close(sockfd);
  f_cat(LOG_0948, result);

  memset(res, 0, 9);
  if (result_ptr = str_str(result, "<title>"))
    str_ncpy(res, result_ptr + 7, 9);

  sprintf(result, "User %s called 0948%s\nMessage = %s\n%s\n\n",
    cuser.userid, svc_no, message, res);

  f_cat(LOG_0948, result);
  vmsg(res);

  return;
}

