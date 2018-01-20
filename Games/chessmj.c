/***************************************************/
/*  SevenCard game by weiren 1998/7/29             */
/*  e-mail: weiren@mail.eki.com.tw                 */
/***************************************************/
#include "bbs.h"
#define MINBET 15 /* ³Ì¤Ö­n¦³´X­¿¥»ª÷ */
#define KEY_ENTER 13

int host_card[5]={0}, guest_card[5]={0};
int    cnum[32]={ 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
                  7, 7, 7, 7, 7,
                  8, 9, 9,10,10,11,11,12,12,13,13,
                 14,14,14,14,14};
int   group[32]={ 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2,
                  3, 3, 3, 3, 3,
                  4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5,
                  6, 6, 6, 6, 6};
int   flag=0,tflag=0,tflagA=0,tflagB=0,throw[32]={0};
int   selftouch;


void
outz(msg)
  uschar *msg;
{
  int ch;

  move(b_lines, 0);
  clrtoeol();
  while (ch = *msg)
  {
    outc(ch);
    msg++;
  }
}

static inline void
zkey()                          /* press any key or timeout */
{
  struct timeval tv = {1, 100};
  int rset;

  rset = 1;
  select(1, (fd_set *)&rset, NULL, NULL, &tv);
}

void
zmsg(msg)                       /* easy message */
  char *msg;
{
  outz(msg); /* SiE: 980731: ¥Î outz ¥N´À */
  refresh();
  zkey();
}


int p_chessmj()
{
  char buf1[8];
  int chesslist[32]={0};
  int tmp[4];
  float tax=0.95; /* tax ¬°ª±®aÄ¹®É©âªºµ| */
  int i,j,jp,mo=0,k=0,x,xx,m,ch,z=1;
  int listen=0,pickup=0,picky=0;
  long int money;

  clear();
  setutmpmode(CHESSMJ);
  do{
  if(cuser.money<100){
    pressanykey("©êºp±zªº»È¨â¤£°÷®@!");
    return 0;
    }
  move(0,0);prints("±zÁÙ¦³ [1;44;33m%d[m »È¨â",cuser.money);
  getdata(1, 0, "­nª±¦h¤Ö¤@©³¦h¤Ö»È¨â(100-10000)? ", buf1, 6, DOECHO,NULL);
  money=atoi(buf1);
  if(!buf1[0])return 0;
     if(cuser.money<money*MINBET){
      pressanykey("±zªº»È¨â¤£¨¬!!(­n¦³%d­¿©³ªº¥»ª÷)",MINBET);
      return 0;}
  }while((money<100)||(money>90000));
  demoney(money*MINBET);
  move(2,0);prints("(«ö ¡ö(j)¡÷(l)¿ïµP, ¡ô(i)¥áµP, «ö ENTER(5) ­JµP)");
  move(0,0);clrtoeol();prints("±zÁÙ¦³ [1;44;33m%d[m »È¨â",cuser.money);
  for(i=0;i<32;i++) chesslist[i]=i;
  for(i=0;i<1000;i++)
  {
    int a,b,c;
    do{a=random()%32; b=random()%32;} while(a==b);
    c=chesslist[a]; chesslist[a]=chesslist[b]; chesslist[b]=c;
  }                /* ¬~µP */

  for(i=0;i<32;i++)throw[i]=32;
  selftouch=0;picky=0;
  flag=0;tflag=0;tflagA=0;tflagB=0; /* ÂkÂk¹s */

  flag=0;
  for(i=0;i<4;i++){
    host_card[i]=chesslist[flag];
    flag++;
    guest_card[i]=chesslist[flag];
    flag++;
  }        /* µo«e¥|±iµP */

  for(i=0;i<4;i++){
    for(j=0;j<(3-i);j++){
      if(guest_card[j]>guest_card[j+1]){
        x=guest_card[j];guest_card[j]=guest_card[j+1];guest_card[j+1]=x;
      }
      if(host_card[j]>host_card[j+1]){
        x=host_card[j];host_card[j]=host_card[j+1];host_card[j+1]=x;
      }
    }
  }        /* ±Æ§Ç */

  move(4,0);  prints("¢~¢w¢¡¢~¢w¢¡¢~¢w¢¡¢~¢w¢¡");
  move(5,0);  prints("¢x  ¢x¢x  ¢x¢x  ¢x¢x  ¢x");
  move(6,0);  prints("¢¢¢w¢£¢¢¢w¢£¢¢¢w¢£¢¢¢w¢£");

  for(i=0;i<4;i++)
    print_Schess(guest_card[i],15,6*i);  /* ¦L¥X«e¥|±iµP */

do{
  jp=5;x=0;z=1;
  move(18,26);
  do{
    if(mo==0){
      move(14,24);prints("[1;47;30m «ö¥ô¤@ÁäºNµP(©Î ¡õ(k) ¾ßµP) [m");
    }
      else {move(14,0);clrtoeol();}
    move(18,2+(jp-1)*6);prints("¡¶");
    ch=igetkey();
    if((ch!='5'&&ch!=KEY_ENTER)&&flag==32){
      pressanykey("¬y§½");inmoney(MINBET*money);
      return;
    }
    if(mo==0&&ch!='k'&&ch!='5'&&ch!=KEY_DOWN&&ch!=KEY_ENTER){ch='p';}
                 /* ¥|±iµP«h±j¨îºNµP */
    switch (ch)
    {
      case KEY_RIGHT:
      case 'l':
        move(18,2+(jp-1)*6);prints("  ");
        jp+=1;if(jp>5)jp=5;
        move(18,2+(jp-1)*6);prints("¡¶");
        break;
      case KEY_LEFT:
      case 'j':
        move(18,2+(jp-1)*6);prints("  ");
        jp-=1;if(jp<1)jp=1;
        move(18,2+(jp-1)*6);prints("¡¶");
        break;
      case KEY_UP:      /* ¥XµP */
      case 'i':
        move(18,2+(jp-1)*6);prints("  ");
        throw[tflag]=guest_card[jp-1];tflag++;tflagB++;
        z=0;mo=0;
        guest_card[jp-1]=guest_card[4];
        guest_card[4]=0;
        sortchess();
        /* printhostall(); */
        clear_5card();
        P_allchess();
        print_Schess(throw[tflag-1],11,(tflagB-1)*4);
        picky=0;
        break;
      case 'p':   /* ºNµP */
        if(mo==0){
          move(18,2+(jp-1)*6);prints("  ");
          guest_card[4]=chesslist[flag];
          flag++;
          print_Schess(guest_card[4],15,24);
          mo=1;
        }
        break;
      case KEY_DOWN:
      case 'k':
         if(tflag>0&&mo==0){
           guest_card[4]=throw[tflag-1];
           print_Sign(8,(tflagA-1)*4);
           print_Schess(guest_card[4],15,24);
           mo=1;picky=1;
         }
         break;
      case 'q':
         return 0;
         break;
      case KEY_ENTER:
      case '5':
         if(testall(guest_card)==1&&mo==1&&picky==0){
           selftouch=1;
           i=count_tai(guest_card,1);
           inmoney((i+MINBET)*money*tax);
           printhostfour();
           pressanykey("«z«¨¦ÛºN°Õ!!!!!");
           return;
         }
         if(tflag>0&&mo==0){
           i=guest_card[4];guest_card[4]=throw[tflag-1];
           if(testall(guest_card)==1){
             print_Sign(8,(tflagA-1)*4);
             print_Schess(guest_card[4],15,24);
             i=count_tai(guest_card,1);
             inmoney((i+MINBET)*money*tax);
             printhostfour();
             pressanykey("­J!!!!!!!!!!");
             return;
           }
           guest_card[4]=i;
         }
         break;
      case 'z':
        move(19,0);
        prints("¥»¹CÀ¸¥Ñ¯îÂÕ¤Æ¹Ò(weird.twbbs.org.tw)¯¸ªø weiren ³]­p\n");
        prints("e-mail: weiren@weiren.net");
        break;
      default:;
    }
  }while(z==1);

  zmsg("");

  host_card[4]=throw[tflag-1];
  if(testall(host_card)!=0){
    host_hula();
    i=count_tai(host_card,0);
    inmoney((MINBET-i)*money);
    pressanykey("¹q¸£­J°Õ!");
    return;
  }

  if(tflag==32){pressanykey("¬y§½");return;}

  host_card[4]=chesslist[flag];
  if(testall(host_card)!=0){
    selftouch=1;
    host_self();
    i=count_tai(host_card,0);
    inmoney((MINBET-i)*money);
    pressanykey("¹q¸£¦ÛºN!");
    return;
  }

  for(i=0;i<4;i++)tmp[i]=host_card[i];
  if(testlisten(tmp)==0){ /* ¨SÅ¥ªº¸Ü */
    for(i=0;i<4;i++){
      k=0;
      for(j=0;j<4;j++){
        if(i!=j){tmp[k]=host_card[j];k++;}
      }
      tmp[3]=throw[tflag-1]; /* §â¾ß°_¨º±i¸ò¤â¤WªºµP¤ñ¹ï */
      if(testlisten(tmp)){ /* ¾ßµP¦³Å¥ªº¸Ü */
          listen=1;
          host_card[4]=throw[tflag-1];tflag--;
          print_Sign(11,(tflagB-1)*4);  /* ¦L¾ßµP²Å¸¹ */
          xx=i; /* ¬ö¿ý¤U­n¥áªº¨º±iµP */
          pickup=1;
          i=5; /* ¸õ¥X i loop */
      }
    }
  }

  for(i=0;i<4;i++)tmp[i]=host_card[i];
  if(testlisten(tmp)==1&&pickup==0){ /* ¦³Å¥¥B­è­è¨S¾ß */
    m=0;
    for(i=0;i<4;i++)if(cnum[tmp[i]]==7)m++;
    if(m==2&&cnum[throw[tflag-1]]==7)pickup=1;
    if(m==3&&cnum[throw[tflag-1]]==7){
      pickup=1;
      for(i=0;i<tflag-1;i++)if(cnum[throw[i]]==7)pickup=0;
    }
    m=0;
    for(i=0;i<4;i++)if(cnum[tmp[i]]==14)m++;
    if(m==2&&cnum[throw[tflag-1]]==14)pickup=1;
    if(m==3&&cnum[throw[tflag-1]]==14){
      pickup=1;
      for(i=0;i<tflag-1;i++)if(cnum[throw[i]]==14)pickup=0;
    }
    if(pickup==1){
      host_card[4]=throw[tflag-1];tflag--;
      print_Sign(11,(tflagB-1)*4);  /* ¦L¾ßµP²Å¸¹ */
    }
  }


  if(!pickup){ host_card[4]=chesslist[flag];flag++;}
  /* ­è­è¨S¾ßµP²{¦b´NºNµP */
  Phost5();
  zmsg("");
  Chost5();

  if(!pickup){
    for(i=0;i<4;i++){
      k=0;
      for(j=0;j<4;j++){
        if(i!=j){tmp[k]=host_card[j];k++;}
      }
      tmp[3]=host_card[4];
      if(testlisten(tmp)){ /* ºNµP¦³Å¥ªº¸Ü */
        listen=1;
        xx=i; /* ¬ö¿ý¤U­n¥áªº¨º±iµP */
        i=5; /* ¸õ¥X i loop */
      }
    } 
  }

  for(i=0;i<4;i++)tmp[i]=host_card[i];
  
  xx=any_throw();

  throw[tflag]=host_card[xx];tflag++;tflagA++;
  host_card[xx]=host_card[4]; /* ¥á¥X¨SÅ¥¨º±i */
  print_Schess(throw[tflag-1],8,(tflagA-1)*4);

  pickup=0;
  listen=0;

}while(1);

  pressanykey("¹CÀ¸µ²§ô");
  return;
}

int print_Sign(int x,int y)
{
  move(x,y);prints("¢~¡´¢¡");
}

int print_Schess(int card,int x,int y)
{
  char *chess[33]={"«Ó","¥K","¥K","¬Û","¬Û","ÚÏ","ÚÏ","ØX","ØX","¬¶","¬¶",
                   "§L","§L","§L","§L","§L",
                   "±N","¤h","¤h","¶H","¶H","¨®","¨®","°¨","°¨","¥]","¥]",
                   "¨ò","¨ò","¨ò","¨ò","¨ò","¢æ"};
move(x,y);   prints("¢~¢w¢¡");
move(x+1,y); prints("¢x%2s¢x",chess[card]);
move(x+2,y); prints("¢¢¢w¢£");
return 0;
}

int clear_5card()
{
move(15,24); prints("      ");
move(16,24); prints("      ");
move(17,24); prints("      ");
}

int Phost5()
{
move(4,24); prints("¢~¢w¢¡");
move(5,24); prints("¢x  ¢x");
move(6,24); prints("¢¢¢w¢£");
}
int Chost5()
{
move(4,24); prints("      ");
move(5,24); prints("      ");
move(6,24); prints("      ");
}

int P_allchess()
{
  char *chess[33]={"«Ó","¥K","¥K","¬Û","¬Û","ÚÏ","ÚÏ","ØX","ØX","¬¶","¬¶",
                   "§L","§L","§L","§L","§L",
                   "±N","¤h","¤h","¶H","¶H","¨®","¨®","°¨","°¨","¥]","¥]",
                   "¨ò","¨ò","¨ò","¨ò","¨ò",""};
  int i;
  for(i=0;i<4;i++){
    move(16,2+6*i);prints("%s",chess[guest_card[i]]);
  }
}

int
sortchess()
{
  int i,j,x;
  for(i=0;i<4;i++){
    for(j=0;j<(3-i);j++){
      if(guest_card[j]>guest_card[j+1]){
        x=guest_card[j];guest_card[j]=guest_card[j+1];guest_card[j+1]=x;
      }
      if(host_card[j]>host_card[j+1]){
        x=host_card[j];host_card[j]=host_card[j+1];host_card[j+1]=x;
      }
    }
  }
}

int
testpair(a, b)
int a,b;
{
  if(cnum[a]==cnum[b])return 1;
  if(cnum[a]==1&&cnum[b]==8)return 1;
  if(cnum[a]==8&&cnum[b]==1)return 1;
  return 0;
}

int
testthree(a,b,c)
int a,b,c;
{
  int tmp;
  if(a>b){tmp=a;a=b;b=tmp;}
  if(b>c){tmp=b;b=c;c=tmp;}
  if(a>b){tmp=a;a=b;b=tmp;}
  /* move(0,0);prints("%d %d %d",a,b,c);pressanykey("testthree"); */
  if(cnum[a]== 1&&cnum[b]== 2&&cnum[c]== 3)return 1; /* «Ó¥K¬Û */
  if(cnum[a]== 4&&cnum[b]== 5&&cnum[c]== 6)return 1; /* ÚÏØX¬¶ */
  if(cnum[a]== 8&&cnum[b]== 9&&cnum[c]==10)return 1; /* ±N¤h¶H */
  if(cnum[a]==11&&cnum[b]==12&&cnum[c]==13)return 1; /* ¨®°¨¥] */
  if(cnum[a]== 7&&cnum[b]== 7&&cnum[c]== 7)return 1; /* §L§L§L */
  if(cnum[a]==14&&cnum[b]==14&&cnum[c]==14)return 1; /* ¨ò¨ò¨ò */
  return 0;
}

int
testall(set)
int set[5];
{
  int i,j,k,m,p[3];
  for(i=0;i<4;i++){
    for(j=i+1;j<5;j++){
      m=0;
      for(k=0;k<5;k++){
        if(k!=i&&k!=j){p[m]=set[k];m++;}
      }
      if(testpair(set[i],set[j])!=0 && testthree(p[0],p[1],p[2])!=0)
        return 1;
    }
  }
  return 0;
}

int
printhostall()
{
  int i;
  for(i=0;i<5;i++)
   print_Schess(host_card[i],4,6*i);
}

int
printhostfour()
{
  int i;
  for(i=0;i<4;i++)
   print_Schess(host_card[i],4,6*i);
}

int 
testlisten(set)
int set[4];
{
  int i,j,k,p[2]={0},m=0,mm=0;

  j=0;
  for(i=0;i<4;i++){if(group[set[i]]!=3)j++;}if(j==0)return 1; /* ¥|¤ä§L */
  j=0;
  for(i=0;i<4;i++){if(group[set[i]]!=6)j++;}if(j==0)return 1; /* ¥|¤ä¨ò */

  if(testthree(set[1],set[2],set[3])!=0)return 1;
  if(testthree(set[0],set[2],set[3])!=0)return 1;
  if(testthree(set[0],set[1],set[3])!=0)return 1;
  if(testthree(set[0],set[1],set[2])!=0)return 1; /* ¤T¤ä¦¨§Î«hÅ¥ */
  for(i=0;i<3;i++){
    for(j=i+1;j<4;j++){
      if(testpair(set[i],set[j])){ /* ¨â¤ä¦³­F¬Ý¥t¨â¤ä¦³¨S¦³Å¥ */
        m=0;
        for(k=0;k<4;k++){
          if(k!=i&&k!=j){p[m]=set[k];m++;}
          if(group[set[i]]==3||group[set[i]]==6)mm=1; /* ¦³­Fªº¬O§L©Î¨ò */
        }
      }
    }
  }
  if(m!=0){
    if((group[p[0]]==group[p[1]])&&(cnum[p[0]]!=cnum[p[1]]))
    return 1; /* ¨â¤ä¬O pair ¥t¨â¤ä¦³Å¥ */
    if( (group[p[0]]==group[p[1]]==3)||(group[p[0]]==group[p[1]]==6) )
    return 1;
    if(testpair(p[0],p[1])&&mm==1)
    return 1;
  }
  return 0;
}

int
host_hula()
{
  print_Sign(11,(tflagB-1)*4);  /* ¦L¾ßµP²Å¸¹ */ 
  printhostall();
}

int
host_self()
{
  printhostall();
}

int
any_throw()
{
  int i,j,k=0,z,set[5]={0},point[5]={20,20,20,20,20},tmp[4]={0};
  for(i=0;i<5;i++){     /* point[5] ¬°µû¤À¨t²Î, ¬Ý¥á­þ±iµP¤ñ¸û¦n */
    k=0;
    for(j=0;j<5;j++){
      if(i!=j){tmp[k]=host_card[j];k++;}
    }
    if(testlisten(tmp)){
      point[i]+=10; /* ¦³Å¥´N¥[ 10 ¤À */
      if(diecard(host_card[i]))point[i]+=5; /* µ´±i§ó¸Ó¥á */
      for(z=0;z<4;z++)
       if(( (cnum[host_card[i]]==cnum[tmp[z]])
          ||(cnum[tmp[z]]==1&&cnum[host_card[i]]==8) 
          ||(cnum[tmp[z]]==8&&cnum[host_card[i]]==1) )
          &&cnum[host_card[i]]!=7&&cnum[host_card[i]]!=14)point[i]+=10;
                                            /* ¨®°¨¥]¥], ¥]¸Ó¥á */
    }
  }
  k=0;
  for(i=0;i<5;i++)if(cnum[host_card[i]]==7)k++; /* ºâ¦³´X¤ä§L */
  if(k==3){
    for(i=0;i<5;i++)if(cnum[host_card[i]]!=7)point[i]+=5;
  }
    /* ¦³¤T¤ä§L´N¥[¤­¤À */
  if(k==4){ /* ¦³¥|¤ä§Lªº¸Ü */
    z=diecard(12); /* 12 ¬O§L */
    if(z>0){
      for(i=0;i<5;i++)if(cnum[host_card[i]]==7)point[i]+=5; /* §Lµ´±i´N¥á§L */
    }
    else{
      for(i=0;i<5;i++)if(cnum[host_card[i]]!=7)point[i]+=20; /* §L¨Sµ´±i´N¥[ 10 ¤À */
    }
  }
  k=0;
  for(i=0;i<5;i++)if(cnum[host_card[i]]==14)k++; /* ºâ¦³´X¤ä¨ò */
  if(k==3)for(i=0;i<5;i++)if(cnum[host_card[i]]!=14)point[i]+=5;
    /* ¦³¤T¤ä¨ò´N¥[¤­¤À */
  if(k==4){ /* ¦³¥|¤ä¨òªº¸Ü */
    z=diecard(28); /* 28 ¬O¨ò */
    if(z>0){
      for(i=0;i<5;i++)if(cnum[host_card[i]]==14)point[i]+=5; /* ¨òµ´±i´N¥á¨ò */
    }
    else{
      for(i=0;i<5;i++)if(cnum[host_card[i]]!=14)point[i]+=10; /* ¨ò¨Sµ´±i´N¥[ 10 ¤À */
    }
  }

  for(i=0;i<5;i++){
    if(cnum[host_card[i]]==7)point[i]-=1;
    if(cnum[host_card[i]]==14)point[i]-=1; /* §L¨òºÉ¶q¤£¥á */
  }
  
  for(i=0;i<4;i++){
    for(j=i+1;j<5;j++){
      if(group[host_card[i]]==group[host_card[j]]){
        point[i]-=2;point[j]-=2; /* ®t¤@¤ä¦¨¤Tªº¤£¥á */
      }
      if(testpair(host_card[i],host_card[j])){
        point[i]-=2;point[j]-=2; /* ¦³­Fªº¤£¥á */
      }
    }
  }

  for(i=0;i<4;i++)set[i]=guest_card[i];
  for(i=0;i<5;i++){set[4]=host_card[i];if(testall(set)&&random()%18>=3)point[i]=0;}
  /* ¥H¤W¨â¦æ­A½â, ¦pªG¥á¤F·|³Q­J´N¦º³£¤£¥á, ¤£­A½â¾÷²v 3/18 */

  k=0;
  for(i=0;i<5;i++)if(point[i]>k){k=point[i];z=i;}
  return z;
}

int
diecard(a) /* ¶Ç¶i¤@±iµP, ¬Ý¬O§_µ´±i */
int a;
{
  int i,k=0;
  for(i=0;i<tflag;i++){
    if(cnum[throw[i]]==cnum[a])k++;
    if(cnum[throw[i]]==1&&cnum[a]==8)return 1;
    if(cnum[throw[i]]==8&&cnum[a]==1)return 1;
  }
  if((cnum[a]==7||cnum[a]==14)&&k==4)return 1; /* §L¨òµ´±i */
  if(k==1&&(cnum[a]!=7&&cnum[a]!=14)) return 1;
  return 0;
}

int
count_tai(set,win)
int set[5],win;
{
  int i,j=0,sum=0;
  char *name[10]={"±N«Ó¹ï","±N¤h¶H","«Ó¥K¬Û",
                 "¤­§L¦XÁa","¤­¨ò³s¾î","¤T§L¤J¦C","¤T¨ò¤J¦C",
                 "®ü©³","¤Ñ­J","¦ÛºN"};
  int    tai[10]={ 2, 1, 1, 
                  5, 5, 2, 2,
                  3, 5, 1};
  int    yes[10]={0};

  if(flag==32)yes[7]=1; /* ®ü©³ */
  if(tflag<=1)yes[8]=1; /* ¤Ñ­J */
  if(selftouch==1)yes[9]=1; /* ¦ÛºN */
  
  for(i=0;i<5;i++)if(cnum[set[i]]==1||cnum[set[i]]==8)j++;
  if(j==2)yes[0]=1; /* ±N«Ó¹ï */
  j=0;
  for(i=0;i<5;i++)if(cnum[set[i]]==2)j++;
  if(j==1)yes[2]=1; /* ¥u¦³¤@¤ä¥K´N¬O «Ó¥K¬Û */

  j=0;
  for(i=0;i<5;i++)if(cnum[set[i]]==9)j++;
  if(j==1)yes[1]=1; /* ¥u¦³¤@¤ä¤h´N¬O ±N¤h¶H */

  j=0;
  for(i=0;i<5;i++)if(cnum[set[i]]==7)j++;
  if(j>=3)yes[5]=1;
  if(j==5)yes[3]=1;

  j=0;
  for(i=0;i<5;i++)if(cnum[set[i]]==14)j++;
  if(j>=3)yes[6]=1;
  if(j==5)yes[4]=1;

  for(i=0;i<10;i++)if(yes[i]!=0)sum+=tai[i];
  move(18,0);
  prints("¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{");
  move(22,0);
  prints("¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}");
  move(19,0);
  for(i=0;i<5;i++)if(yes[i]!=0)prints("    %8s [%d ¥x]  ",name[i],tai[i]);
  move(20,0);
  for(i=5;i<10;i++)if(yes[i]!=0)prints("    %8s [%d ¥x]  ",name[i],tai[i]);
  move(21,0);
  prints("    %8s [2 ¥x]  ","©³");
  prints("    %8s [%d ¥x]","¦X­p",sum+2);
  game_log(CHESSMJ,"%s %2d¥x[m",win?"[32;1mÄ¹":"[31;1m¿é",sum+2);
  return sum+2;
}

