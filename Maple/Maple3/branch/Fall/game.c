
#include "bbs.h"

#define FN_BLACKJACK	"game/blackjack.log"
#define FN_GAGB		"game/gagb.log"
#define FN_DICE		"game/dice.log"
#define FN_BINGO	"game/bingo.log"
  
/* ¶Â³Ç§J¹CÀ¸ */
int BlackJack()
{
  char buf[8];
  int    num[52]={11,11,11,11,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,
                   7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,
                  10,10,10,10,10,10,10,10};
  int cardlist[52]={0};
  int i,j,m,tmp=0,tmp2,ch;
  int win=2,win_jack=5; /* win ¬°Ä¹®Éªº­¿²v, win_jack ¬°«e¨â±i´N 21 ÂI­¿²v */
  int six=10, seven=20, aj=10, super_jack=20; /* 777, A+J, spade A+J ªº­¿²v */
  int host_count=2, guest_count=1, card_count=3, A_count=0, AA_count=0;
  int host_point=0, guest_point=0, mov_y=4;
  int host_card[12]={0}, guest_card[12]={0};
  long int money;

  int CHEAT=0; /* °µ¹ú°Ñ¼Æ, 1 ´N§@¹ú, 0 ´N¤£§@ */

  FILE *fpp;
  time_t now = time(0);
  time(&now);

  clear();
  utmp_mode(M_BLACKJACK);
  do{
  move(0,0);prints("±z¨­¤WÁÙ¦³ [1;44;33m%d[m ¤¸",cuser.money);
  vget(1, 0, "­n©ãª`¦h¤Ö¿ú(1 - 250000)? ", buf, 7, DOECHO);
  money=atoi(buf);
  if(!buf[0])return 0;
  if(check_money(money)) return 0;
  }while((money<1)||(money>250000));
  demoney(money);
  move(2,0);prints("(«ö y ÄòµP, n ¤£ÄòµP, d double)");
  move(0,0);clrtoeol();prints("±zÁÙ¦³ [1;44;33m%d[m »È¨â",cuser.money);
  for(i=1;i<=52;i++){
    m=0;
    do{
    j=(time(0)+cuser.money+rand())%52;
    if (cardlist[j]==0){cardlist[j]=i;m=1;}
    }while(m==0);
  };
  for(i=0;i<52;i++)cardlist[i]--; /* ¬~µP */

  if(money>=20000)CHEAT=1;
  if(CHEAT==1){
    if(cardlist[1]<=3){
      tmp2=cardlist[50];
      cardlist[50]=cardlist[1];
      cardlist[1]=tmp2;
    }
  }                             /* §@¹ú½X */

  host_card[0]=cardlist[0];
  if(host_card[0]<4)AA_count++;
  guest_card[0]=cardlist[1];

  if(guest_card[0]<4)A_count++;
  host_card[1]=cardlist[2];
  if(host_card[1]<4)AA_count++; /* µo«e¤T±iµP */

  move(5,0);  prints("¢~¢w¢w¢w¢¡");
  move(6,0);  prints("¢x      ¢x");
  move(7,0);  prints("¢x      ¢x");
  move(8,0);  prints("¢x      ¢x");
  move(9,0);  prints("¢x      ¢x");
  move(10,0); prints("¢x      ¢x");
  move(11,0); prints("¢¢¢w¢w¢w¢£");
  print_card(host_card[1],5,4);
  print_card(guest_card[0],15,0);  /* ¦L¥X«e¤T±iµP */

  host_point=num[host_card[1]];
  guest_point=num[guest_card[0]];

  do{
    m=1;
    guest_card[guest_count]=cardlist[card_count];
    if(guest_card[guest_count]<4)A_count++;
    print_card(guest_card[guest_count],15,mov_y);
    guest_point+=num[guest_card[guest_count]];

    if((guest_card[0]>=24&&guest_card[0]<=27)&&(guest_card[1]>=24&&guest_card[1]<=27)&&(guest_card[2]>=24&&guest_card[2]<=27)){
      move(18,3);prints("[1;41;33m     ¢¶¢¶¢¶     [m");
      move(3,0);prints("[1;41;33m¢¶¢¶¢¶ !!! ±o¼úª÷ %d »È¨â[m",money*seven);
      inmoney(money*seven);
      move(0,0);clrtoeol();prints("±zÁÙ¦³ [1;44;33m%d[m »È¨â",cuser.money);
      fpp = fopen(FN_BLACKJACK,"a");
      fprintf(fpp,"[1;32m%12s[m ¤¤¤F [1;33m%7d[m ¤¸ªº [1;42;33m  ¢¶¢¶¢¶   [m %s ",cuser.userid,money*seven,ctime(&now));
      fclose(fpp);
      vmsg(NULL);
      return 0;
    }

    if((guest_card[0]==40&&guest_card[1]==0)||(guest_card[0]==0&&guest_card[1]==40)){
      move(18,3);prints("[1;41;33m ¶W¯Å¥¿²Î BLACK JACK  [m");
      move(3,0);prints("[1;41;33m¶W¯Å¥¿²Î BLACK JACK !!! ±o¼úª÷ %d »È¨â[m",money*super_jack);
      inmoney(money*super_jack);
      move(0,0);clrtoeol();prints("±zÁÙ¦³ [1;44;33m%d[m »È¨â",cuser.money);
      fpp = fopen(FN_BLACKJACK,"a");
      fprintf(fpp,"[1;32m%12s[m ¤¤¤F [1;33m%7d[m ¤¸ªº [1;41;33m ¥¿²Î ¢Ï¢Ø [m %s ",cuser.userid,money*super_jack,ctime(&now));
      fclose(fpp);
      vmsg(NULL);
      return 0;
    }

    if((guest_card[0]<=3&&guest_card[0]>=0)&&(guest_card[1]<=43&&guest_card[1]>=40))tmp=1;

if((tmp==1)||((guest_card[1]<=3&&guest_card[1]>=0)&&(guest_card[0]<=43&&guest_card[0]>=40))){
      move(18,3);prints("[1;41;33m SUPER BLACK JACK  [m");
      move(3,0);prints("[1;41;33mSUPER BLACK JACK !!! ±o¼úª÷ %d »È¨â[m",money*aj);
      inmoney(money*aj);
      move(0,0);clrtoeol();prints("±zÁÙ¦³ [1;44;33m%d[m »È¨â",cuser.money);
      fpp = fopen(FN_BLACKJACK,"a");
      fprintf(fpp,"[1;32m%12s[m ¤¤¤F [1;33m%7d[m ¤¸ªº [1;44;33m Super¢Ï¢Ø [m %s ",cuser.userid,money*aj,ctime(&now));
      fclose(fpp);
      vmsg(NULL);
      return 0;
    }

    if(guest_point==21&&guest_count==1){
      move(18,3);prints("[1;41;33m  BLACK JACK  [m");
      move(3,0);prints("[1;41;33mBLACK JACK !!![44m ±o¼úª÷ %d »È¨â[m",money*win_jack);
      inmoney(money*win_jack);
      move(0,0);clrtoeol();prints("±zÁÙ¦³ [1;44;33m%d[m »È¨â",cuser.money);
    if(money*win_jack>=500000){
      fpp = fopen(FN_BLACKJACK,"a");
      fprintf(fpp,"[1;32m%12s[m ¤¤¤F [1;33m%7d[m ¤¸ªº [1;47;30m BlackJack [m %s ",cuser.userid,money*win_jack,ctime(&now));
      fclose(fpp);
    }

      vmsg(NULL);
      return 0;
    }                        /* «e¨â±i´N 21 ÂI */

    if(guest_point>21){
      if(A_count>0){guest_point-=10;A_count--;};
    }
    move(12,0); clrtoeol();prints("[1;32mÂI¼Æ: [33m%d[m",host_point);
    move(14,0); clrtoeol();prints("[1;32mÂI¼Æ: [33m%d[m",guest_point);
    if(guest_point>21){
      vmsg("  Ãz±¼°Õ~~~  ");
      return 0;
    }

    if(guest_count==5){
      move(18,3);prints("[1;41;33m            ¹L¤»Ãö            [m");
      move(3,0);prints("[1;41;33m¹L¤»Ãö !!! ±o¼úª÷ %d »È¨â[m",money*six);
      inmoney(money*six);
      move(0,0);clrtoeol();prints("±zÁÙ¦³ [1;44;33m%d[m »È¨â",cuser.money);
      fpp = fopen(FN_BLACKJACK,"a");
      fprintf(fpp,"[1;32m%12s[m ¤¤¤F [1;33m%7d[m ¤¸ªº [1;44;33m  ¹L¤»Ãö   [m %s ",cuser.userid,money*six,ctime(&now));
      fclose(fpp);
      vmsg(NULL);
      return 0;
    }

    guest_count++;
    card_count++;
    mov_y+=4;

    do{
      if(ch=='d')m=0;
      if(m!=0)ch=vkey();
    }while(ch!='y'&&ch!='n'&&ch!='d'&&m!=0); /* §ì key */

    if(ch=='d'&&m!=0&&guest_count==2){
      if(cuser.money>=money){
        demoney(money);
        money*=2;
      }
      else ch='n';
      move(0,0);clrtoeol();prints("±zÁÙ¦³ [1;44;33m%d[m »È¨â",cuser.money);
    }                                      /* double */

    if(ch=='d'&&guest_count>2)ch='n';
    if(guest_point==21)ch='n';
  }while(ch!='n'&&m!=0);

  mov_y=8;

  print_card(host_card[0],5,0);
  print_card(host_card[1],5,4);
  host_point+=num[host_card[0]];

  do{

    if(host_point<guest_point){
      host_card[host_count]=cardlist[card_count];
      print_card(host_card[host_count],5,mov_y);
      if(host_card[host_count]<4)AA_count++;
      host_point+=num[host_card[host_count]];
    }
    if(host_point>21){
      if(AA_count>0){host_point-=10;AA_count--;};
    }
    move(12,0); clrtoeol();prints("[1;32mÂI¼Æ: [33m%d[m",host_point);
    move(14,0); clrtoeol();prints("[1;32mÂI¼Æ: [33m%d[m",guest_point);
    if(host_point>21){
      move(14,0); clrtoeol(); prints("[1;32mÂI¼Æ: [33m%d [1;41;33m WINNER [m",guest_point);

      move(3,0);prints("[1;44;33m§AÄ¹¤F~~~~ ±o¼úª÷ %d »È¨â[m",money*win);
      inmoney(money*win);
      move(0,0);clrtoeol();prints("±zÁÙ¦³ [1;44;33m%d[m »È¨â",cuser.money);
      vmsg(NULL);
      return 0;
    }
    host_count++;
    card_count++;
    mov_y+=4;
  }while(host_point<guest_point);

  vmsg("§A¿é¤F~~~~ »È¨â¨S¦¬!");

return 0;
}


int print_card(int card,int x,int y)
{
  char *flower[4]={"¢á","¢Ö","¢Ò","¢Ñ"};
  char *poker[52]={"¢Ï","¢Ï","¢Ï","¢Ï","¢±","¢±","¢±","¢±","¢²","¢²","¢²","¢²",
                   "¢³","¢³","¢³","¢³","¢´","¢´","¢´","¢´","¢µ","¢µ","¢µ","¢µ",
                   "¢¶","¢¶","¢¶","¢¶","¢·","¢·","¢·","¢·","¢¸","¢¸","¢¸","¢¸",
                   "10","10","10","10","¢Ø","¢Ø","¢Ø","¢Ø","¢ß","¢ß","¢ß","¢ß",
                   "¢Ù","¢Ù","¢Ù","¢Ù"};

move(x,y);   prints("¢~¢w¢w¢w¢¡");
move(x+1,y); prints("¢x%s    ¢x",poker[card]);
move(x+2,y); prints("¢x%s    ¢x",flower[card%4]);
move(x+3,y); prints("¢x      ¢x");
move(x+4,y); prints("¢x      ¢x");
move(x+5,y); prints("¢x      ¢x");
move(x+6,y); prints("¢¢¢w¢w¢w¢£");
return 0;
}




int
gagb()
{
  int  money;
  char genbuf[200],buf[80];
  char ans[5]="";
  /* ­¿²v        0  1   2   3   4   5   6   7   8   9   10 */
  float bet[11]={0,100, 50, 10, 3 ,1.5,1.2,0.9, 0.8 ,0.5,0.1};
  int a,b,c,count;
  FILE *fp;
  time_t now;
  
  utmp_mode(M_XAXB);
  srand(time(0));
  clear();
  move(1,0);
  prints("[1m²{¦b§A¨­¤W¦@¦³ [33m%d [37m¤¸¡C[m",cuser.money);
  move(6,0);
  prints("[36m%s[m",msg_seperator);
  move(17,0);
  prints("[36m%s[m",msg_seperator);

  vget(3, 0, "½Ð°Ý§A­n¤Uª`¦h¤Ö(1 ~ 10000)¡H ", genbuf, 6,DOECHO);
  money=atoi(genbuf);
  if(money<=0||money>cuser.money||money>10000) 
    return;
  demoney(money); 

  move(1,15); 
  prints("%d",cuser.money);

  do{
    itoa(rand()%10000,ans);
    for (a=0;a<3;a++)
    for (b=a+1;b<4;b++)
    if(ans[a]==ans[b]) ans[0]=0;
  }while (!ans[0]);

  for(count=1;count<11;count++)
  {
    do{
      vget(5,0,"½Ð²q ¡÷ ",genbuf,5,DOECHO);
      if(!strcmp(genbuf,"¿ß¦Ñ¤j"))
      {
        prints("%s",ans);
        igetch();
      }
      c=atoi(genbuf);
      itoa(c,genbuf);
      for (a=0;a<3;a++)
      for (b=a+1;b<4;b++)
      if(genbuf[a]==genbuf[b]) 
        genbuf[0]=0;
      if(!genbuf[0])
      {
        vmsg("¿é¤J¼Æ¦r¦³°ÝÃD!!");
      }
    }while (!genbuf[0]);
    move(count+6,0);
    prints("  [1;31m²Ä [37m%2d [31m¦¸¡G [37m%s  ->  [33m%dA [36m%dB [m",count,genbuf,an(genbuf,ans),bn(genbuf,ans));
    if(an(genbuf,ans)==4) break;
  }
  now=time(0);

  fp=fopen(FN_GAGB,"a+");
  sprintf(genbuf, "%s %-13s ", Ctime(&now),cuser.userid);
  if(count > 10)
  {
    sprintf(buf,"§A¿é¤FËç¡I¥¿½Tµª®×¬O %s¡A¤U¦¸¦A¥[ªo§a!!",ans);
    fprintf(fp,"[1;31m%s ¥i¼¦¨S²q¨ì¡A¿é¤F %d ¤¸¡I[m\n", genbuf, money);
  }
  else
  {
  int oldmoney=money;
    money *= bet[count];
    inmoney(money);
    if(money-oldmoney > 0)
      sprintf(buf,"®¥³ß¡IÁ`¦@²q¤F %d ¦¸¡A²bÁÈ¼úª÷ %d ¤¸",count,money-oldmoney);
    if(money-oldmoney == 0)
      sprintf(buf,"­ü¡ã¡ãÁ`¦@²q¤F %d ¦¸¡A¨S¿é¨SÄ¹¡I",count);
    if(money-oldmoney < 0)
      sprintf(buf,"°Ú¡ã¡ãÁ`¦@²q¤F %d ¦¸¡A½ß¿ú %d ¤¸¡I",count,oldmoney-money);
    move(1,15); 
    prints("%d",cuser.money);
    if(money-oldmoney > 0)
      fprintf(fp,"[1;33m%s ²q¤F %d ¦¸¡A²bÁÈ %d ¤¸¡I[m\n", genbuf,count,money-oldmoney);
    if(money-oldmoney < 0)
      fprintf(fp,"[1;31m%s ²q¤F %d ¦¸¡AÁ«¤F %d ¤¸¡I[m\n", genbuf,count,oldmoney-money);
  }
  fclose(fp);

  vmsg(buf);
  return 0;
}

itoa(i,a)
int i;
char *a;
{
 int j,k,l=1000;
// prints("itoa: i=%d ",i);

 for(j=3;j>0;j--)
 {
  k=i-(i%l);
  i-=k;
  k=k/l+48;
  a[3-j]=k;
  l/=10;
 }
 a[3]=i+48;
 a[4]=0;

// prints(" a=%s\n",a);
// igetch();
}

int
an(a,b)
char *a,*b;
{
 int i,k=0;
 for(i=0;i<4;i++)
  if(*(a+i)==*(b+i)) k++;
 return k;
}

int
bn(a,b)
char *a,*b;
{
 int i,j,k=0;
 for(i=0;i<4;i++)
  for(j=0;j<4;j++)
   if(*(a+i)==*(b+j)) k++;
 return (k-an(a,b));
}


/*
  µ{¦¡³]­p¡Gwsyfish
  ¦Û¤vµû»y¡G¼g±o«ÜÄê¡A¶Ã¼g¤@³q¡A¨SÔ£²`«×:)
  ¬Û®eµ{«×¡GPttªO¥»À³¸Ó³£¦æ§a¡A´N¥Îinmoney©Mdemoney¡A¨ä¥L¦pSob´N­n§ï¤@¤UÅo
  ªþ±a¤@´£¡G³oµ{¦¡¸Ì­±¦³­A½â¡A´Á±æ­È¤£¬O 0
*/
char *dice[6][3] = {"        ",
                    "   ¡´   ",
                    "        ",
                    "   ¡´   ",
                    "        ",
                    "   ¡´   ",
                    "   ¡´   ",
                    "   ¡´   ",
                    "   ¡´   ",
                    "¡´    ¡´",
                    "        ",
                    "¡´    ¡´",
                    "¡´    ¡´",
                    "   ¡´   ",
                    "¡´    ¡´",
                    "¡´    ¡´",
                    "¡´    ¡´",
                    "¡´    ¡´"
};

int
x_dice()
{
  char choice[11],buf[60];
  int  i, money;
  char tmpchar;    /* ¬ö¿ý¿ï¶µ */
  char tmpdice[3]; /* ¤T­Ó»ë¤lªº­È */
  char totaldice;
  time_t now = time(0);
  FILE *fp;

  time(&now);

  utmp_mode(M_DICE);
  while(1)
  {
    clear();     
    vget(1, 0, "½Ð°Ý­n¤Uª`¦h¤Ö©O©O¡H(³Ì¦h 250000 ¤¸) ",
            choice, 7, LCECHO);
    money = atoi(choice);
    if(money <= 0 || money > 250000 || money > cuser.money)
    {
      vmsg("¤Uª`ª÷ÃB¿é¤J¦³»~¡IÂ÷¶}½ä³õ");
      break;
    }
    outs("\n¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{\n"
         "¢x ¢±­¿  1. ¤j      2. ¤p                                                 ¢x\n"
         "¢x ¢´­¿  3. ¤TÂI    4. ¥|ÂI     5. ¤­ÂI    6. ¤»ÂI    7. ¤CÂI    8. ¤KÂI  ¢x\n"
         "¢x       9. ¤EÂI   10. ¤QÂI    11. ¤Q¤@ÂI 12. ¤Q¤GÂI 13. ¤Q¤TÂI 14. ¤Q¥|ÂI¢x\n"
         "¢x      15. ¤Q¤­ÂI 16. ¤Q¤»ÂI  17. ¤Q¤CÂI 18. ¤Q¤KÂI                      ¢x\n"
         "¢x ¢¸­¿ 19. ¤@¤@¤@ 20. ¤G¤G¤G  21. ¤T¤T¤T 22. ¥|¥|¥| 23. ¤­¤­¤­ 24. ¤»¤»¤»¢x\n"
         "¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}\n");
    vget(11, 0, "­n©ã­þ¤@¶µ©O¡H(½Ð¿é¤J¸¹½X) ", choice, 3, LCECHO);
    tmpchar = atoi(choice);
    if(tmpchar <= 0 || tmpchar > 24)
    {
      vmsg("­n©ãªº¶µ¥Ø¿é¤J¦³»~¡IÂ÷¶}½ä³õ");
      break;
    }
    demoney(money);
    outs("\n«ö¥ô¤@ÁäÂY¥X»ë¤l....\n");
    vkey();

    do
    {
      totaldice = 0;
      for(i = 0; i < 3; i++)
      {
        tmpdice[i] = rand() % 6 + 1;
        totaldice += tmpdice[i];
      }

      if (((tmpchar == 1) && totaldice > 10) ||
          ((tmpchar == 2) && totaldice <= 10))
      {
        if ((rand() % 10) < 7) /* §@¹ú¥Î¡A¤¤¼ú²v¬°­ì¨Ó¤§70% */
          break;
      }
      else
        break;

    }while(tmpchar <= 2);

    outs("\n¢~¢w¢w¢w¢w¢¡¢~¢w¢w¢w¢w¢¡¢~¢w¢w¢w¢w¢¡\n");

    for(i = 0; i < 3; i++)
      prints("¢x%s¢x¢x%s¢x¢x%s¢x\n",
             dice[tmpdice[0] - 1][i],
             dice[tmpdice[1] - 1][i],
             dice[tmpdice[2] - 1][i]);

    outs("¢¢¢w¢w¢w¢w¢£¢¢¢w¢w¢w¢w¢£¢¢¢w¢w¢w¢w¢£\n\n");

    if((tmpchar == 1 && totaldice > 10)
       || (tmpchar == 2 && totaldice <= 10)) /* ³B²z¤j¤p */
      sprintf(buf,"¤¤¤F¡I±o¨ì¢±­¿¼úª÷ %d ¤¸¡AÁ`¦@¦³ %d ¤¸",
              money * 2, inmoney(money * 2));
    else if(tmpchar <= 18 && totaldice == tmpchar) /* ³B²zÁ`©M */
      sprintf(buf,"¤¤¤F¡I±o¨ì¢´­¿¼úª÷ %d ¤¸¡AÁ`¦@¦³ %d ¤¸",
              money * 5, inmoney(money * 5));
    else if((tmpchar - 18) == tmpdice[0] && (tmpdice[0] == tmpdice[1])
            && (tmpdice[1] == tmpdice[2])) /* ³B²z¤T­Ó¤@¼ËÁ`©M */
      sprintf(buf,"¤¤¤F¡I±o¨ì¢¸­¿¼úª÷ %d ¤¸¡AÁ`¦@¦³ %d ¤¸",
            money * 9, inmoney(money * 9));

    else /* ³B²z¨S¤¤ */
      sprintf(buf,"«Ü¥i±¤¨S¦³©ã¤¤¡I");
    fp = fopen(FN_DICE,"a");
      fprintf(fp,"%s %s %s",cuser.userid,buf,ctime(&now));
    fclose(fp);
    vmsg(buf);
  }
  return 0;
 }



/* write by dsyan               */
/* 87/10/24                     */
/* ¤Ñªø¦a¤[ Forever.twbbs.org   */

#undef  GP_DEBUG

char card[52],mycard[5],cpucard[5],sty[100],now;

show_money(int m)
{
  move(19,0);
  clrtoeol();
  prints("[1;37;44m§A²{¦³²{ª÷: [36m%-18d[37m©ãª`ª÷ÃB: [36m%-20d[m",
  cuser.money,m);
}

static int
forq(a,b)
char *a,*b;
{
 char c=(*a)%13;
 char d=(*b)%13;
 if(!c) c=13; if(!d) d=13;
 if(c==1) c=14; if(d==1) d=14;
 if(c==d) return *a-*b;
 return c-d;
}

int
p_gp()
{
 char genbuf[200],hold[5];
 char ans[5];
 int bet,i,j,k,tmp,x,xx,doub,gw=0,cont=0;

 srandom(time(0));
 more("game/gp.welcome",NULL);

 utmp_mode(M_GP);
 bet=0;
 while(-1)
 {
  clear();
  ans[0]=0;
  show_money(bet);
  if(cont==0)
  do
  {
   vget(21, 0,"­n¤Uª`¦h¤Ö©O(¤W­­1000)? «ö Enter Â÷¶}>", genbuf, 5, 1);
   bet=atoi(genbuf);
   if(bet<0) bet=0;
  } while(bet>1000);
  if(!bet) return 0;
  if(check_money(bet)) return 0;
  move(21,0); clrtoeol();
  if(cont>0)
  prints("[33;1m (¡ö)(¡÷)§ïÅÜ¿ïµP  (SPCAE)§ïÅÜ´«µP  (Enter)½T©w[m");
  else
  prints("[33;1m (¡ö)(¡÷)§ïÅÜ¿ïµP  (d)Double  (SPCAE)§ïÅÜ´«µP  (Enter)½T©w[m");
  demoney(bet);
  show_money(bet);

  for(i=0;i<52;i++) card[i]=i; /* 0~51 ..¶Â³Ç§J¬O 1~52 */

  for(i=0;i<1000;i++)
  {
   j=random()%52; k=random()%52;
   tmp=card[j]; card[j]=card[k]; card[k]=tmp;
  }

  now=doub=0;
  for(i=0;i<5;i++)
  {
   mycard[i]=card[now++];
   hold[i]=1;
  }
  qsort(mycard,5,sizeof(char),forq);

  for(i=0;i<5;i++)
   show_card(0,mycard[i],i);

  x=xx=tmp=0;
  while(tmp!=10)
  {
   for(i=0;i<5;i++)
   {
    move(16, i*4+2); outs(hold[i]<0?"«O":"  ");
    move(17, i*4+2); outs(hold[i]<0?"¯d":"  ");
   }
   move(11,xx*4+2); outs("  ");
   move(11,x*4+2); outs("¡õ");
   move(b_lines-1,0);
   refresh();
   xx=x;

   tmp=vkey();
   switch(tmp)
   {
#ifdef GP_DEBUG
    case KEY_UP:
     vget(21, 0,"§âµP´«¦¨> ", genbuf, 3,DOECHO);
     mycard[x]=atoi(genbuf);
     qsort(mycard,5,sizeof(char),forq);
     for(i=0;i<5;i++)
      show_card(0,mycard[i],i);
     break;
#endif
    case KEY_LEFT: case 'l': x=x?x-1:4; break;
    case KEY_RIGHT: case 'r': x=(x==4)?0:x+1; break;
    case ' ': hold[x]*=-1; break;
    case 'd':
     if(!cont&&!doub&&cuser.money>=bet)
     {
      doub++;
      move(21,0); clrtoeol();
      prints("[33;1m (¡ö)(¡÷)§ïÅÜ¿ïµP  (SPCAE)§ïÅÜ´«µP  (Enter)½T©w[m");
      demoney(bet);
      bet*=2;
      show_money(bet);
     }
     break;
   }
  }

  for(i=0;i<5;i++)
   if(hold[i]==1)
    mycard[i]=card[now++];
  qsort(mycard,5,sizeof(char),forq);
  for(i=0;i<5;i++)
   show_card(0,mycard[i],i);
  move(11,x*4+2); outs("  ");

  cpu();
#ifdef GP_DEBUG
for(x=0;x<5;x++)
{
     vget(21, 0,"§âµP´«¦¨> ", genbuf, 3,DOECHO);
     cpucard[x]=atoi(genbuf);
}
     qsort(cpucard,5,sizeof(char),forq);
     for(i=0;i<5;i++)
      show_card(1,cpucard[i],i);
#endif
  i=gp_win();

  if(i<0)
  {
   inmoney(bet*2);
   sprintf(genbuf,"«z!!¦n´Î³á!!²bÁÈ %d ¤¸«¨.. :DDD",bet);
   vmsg( genbuf );
   if (cont>0)
   sprintf(genbuf,"%s ,%s ³s³Ó %d ¦¸, Ä¹¤F %d ¤¸",
        sty,cuser.userid,cont+1,bet);
   else
   sprintf(genbuf,"%s ,%s Ä¹¤F %d ¤¸",sty,cuser.userid,bet);
   log_file("game/gp.log",genbuf);
   bet = ( bet > 50000 ? 100000 : bet * 2 );gw=1;
  }
  else if(i>1000)
  {
   switch(i)
   {
    case 1001: doub=15; break;
    case 1002: doub=10; break;
    case 1003: doub=5; break;
   }
   inmoney(bet*2*doub);
   sprintf(genbuf,"«z!!¦n´Î³á!!²bÁÈ %d ¤¸«¨.. :DDD",bet*2*doub-bet);
   vmsg( genbuf );
   if(cont>0)
   sprintf(genbuf,"%s ,%s ³s³Ó %d ¦¸, Ä¹¤F %d ¤¸",
        sty,cuser.userid,cont+1,bet*doub);
   else
   sprintf(genbuf,"%s ,%s Ä¹¤F %d ¤¸",sty,cuser.userid,bet*doub);
   log_file("game/gp.log",genbuf);
   bet = ( bet > 50000 ? 100000 : bet * 2 * doub ); gw=1;
   bet = ( bet >= 100000 ? 100000 : bet );
  }
  else
  {
   vmsg("¿é¤F..:~~~");
   if(cont>1)
   sprintf(genbuf,"%s ,%s ¤¤¤î %d ³s³Ó, ¿é¤F %d ¤¸",
        sty,cuser.userid,cont,bet);
   else
   sprintf(genbuf,"%s ,%s ¿é¤F %d ¤¸",sty,cuser.userid,bet);
   log_file("game/gp.log",genbuf);
   cont=0;bet=0;
  }

  if ( gw==1 )
  {
    gw=0;
    vget(21, 0,"±z­n§â¼úª÷Ä~ÄòÀ£ª`¶Ü (y/n)?", ans, 2,DOECHO);
    if ( ans[0]=='y' || ans[0]=='Y' )
       cont++;
    else
    {
       cont=0;bet=0;
    }
  }
 }
}

show_card(isDealer,c,x)
int isDealer,c,x;
{
  int beginL;
  char *suit[4] = {"¢Ñ","¢Ò","¢Ö","¢á"};
  char *num[13] = {"¢Ù","¢Ï","¢±","¢²","¢³","¢´","¢µ",
                   "¢¶","¢·","¢¸","10","¢Ø","¢ß"};

  beginL=(isDealer)? 2: 12;
  move(beginL, x*4);      outs("¢~¢w¢w¢w¢¡");
  move(beginL+1, x*4);  prints("¢x%2s    ¢x", num[c%13]);
  move(beginL+2, x*4);  prints("¢x%2s    ¢x", suit[c/13]); /* ¡ö³o¸Ì¸ò¶Â³Ç§J */
#ifdef GP_DEBUG
  move(beginL+3, x*4);  prints("¢x%2d    ¢x",c);              /*   ¦³ÂI¤£¦P³á!! */
#else
  move(beginL+3, x*4);    outs("¢x      ¢x");              /*   ¦³ÂI¤£¦P³á!! */
#endif
  move(beginL+4, x*4);    outs("¢x      ¢x");
  move(beginL+5, x*4);    outs("¢x      ¢x");
  move(beginL+6, x*4);    outs("¢¢¢w¢w¢w¢£");
}

cpu()
{
 char i,j,hold[5];
 char p[13],q[5],r[4];
 char a[5],b[5];

 for(i=0;i<5;i++)
 {
  cpucard[i]=card[now++];
  hold[i]=0;
 }
 qsort(cpucard,5,sizeof(char),forq);
 for(i=0;i<5;i++)
  show_card(1,cpucard[i],i);

 tran(a,b,cpucard);
 check(p,q,r,cpucard);

 for(i=0;i<13;i++)
  if(p[i]>1)
   for(j=0;j<5;j++)
    if(i==cpucard[j]%13) hold[j]=-1;

 for(i=0;i<5;i++)
 {
  if(a[i]==13 || a[i]==1) hold[i]=-1;
  move(6, i*4+2); outs(hold[i]<0?"«O":"  ");
  move(7, i*4+2); outs(hold[i]<0?"¯d":"  ");
 }

 vmsg("¹q¸£´«µP«e..");

 for(i=0;i<5;i++)
  if(!hold[i]) cpucard[i]=card[now++];
 qsort(cpucard,5,sizeof(char),forq);
 for(i=0;i<5;i++)
  show_card(1,cpucard[i],i);
}

int
gp_win()
{
 int my,cpu,ret;
 char myx,myy,cpux,cpuy;

 my=complex(mycard,&myx,&myy);
 cpu=complex(cpucard,&cpux,&cpuy);
 show_style(my,cpu);

 if(my!=cpu)
  ret=my-cpu;
 else if (myx==1 && cpux!=1)
  ret=-1;
 else if (myx!=1 && cpux==1)
  ret=1;
 else if(myx!=cpux)
  ret=cpux-myx;
 else if (myy!=cpuy)
  ret=cpuy-myy;

 if(ret<0)
  switch(my)
  {
   case 1: ret=1001; break;
   case 2: ret=1002; break;
   case 3: ret=1003; break;
  }

 return ret;
}

// ¦Pªá¶¶¡BÅKªK¡B¸¬¡B¦Pªá¡B¶¶¡B¤T±ø¡B¨ß­F¡B­F¡B¤@°¦
int
complex(cc,x,y)
char *cc,*x,*y;
{
 char p[13],q[5],r[4];
 char a[5],b[5],c[5],d[5];
 int i,j,k;

 tran(a,b,cc);
 check(p,q,r,cc);

/* ¦Pªá¶¶ */
 if((a[0]==a[1]-1 && a[1]==a[2]-1 && a[2]==a[3]-1 && a[3]==a[4]-1) &&
    (b[0]==b[1] && b[1]==b[2] && b[2]==b[3] &&b[3]==b[4]))
 { *x=a[4]; *y=b[4]; return 1;}

 if(a[4]==1 && a[0]==2 && a[1]==3 && a[2]==4 && a[3]==5 &&
    (b[0]==b[1] && b[1]==b[2] && b[2]==b[3] && b[3]==b[4]))
 { *x=a[3]; *y=b[4]; return 1;}

 if(a[4]==1 && a[0]==10 && a[1]==11 && a[2]==12 && a[3]==13 &&
    (b[0]==b[1] && b[1]==b[2] && b[2]==b[3] && b[3]==b[4]))
 { *x=1; *y=b[4]; return 1;}

/* ¥|±i */
 if(q[4]==1)
 {
   for(i=0;i<13;i++) if(p[i]==4) *x=i?i:13;
   return 2;
 }

/* ¸¬Äª */
 if(q[3]==1&&q[2]==1)
 {
  for(i=0;i<13;i++) if(p[i]==3) *x=i?i:13;
  return 3;
 }

/* ¦Pªá */
 for(i=0;i<4;i++) if(r[i]==5) {*x=i; return 4;}

/* ¶¶¤l */
 memcpy(c,a,5); memcpy(d,b,5);
 for(i=0;i<4;i++)
  for(j=i;j<5;j++)
  if(c[i]>c[j])
  {
   k=c[i]; c[i]=c[j]; c[j]=k;
   k=d[i]; d[i]=d[j]; d[j]=k;
  }

 if(10==c[1] && c[1]==c[2]-1 && c[2]==c[3]-1 && c[3]==c[4]-1 && c[0]==1)
 { *x=1; *y=d[0]; return 5;}

 if(c[0]==c[1]-1 && c[1]==c[2]-1 && c[2]==c[3]-1 && c[3]==c[4]-1)
 { *x=c[4]; *y=d[4]; return 5;}

/* ¤T±ø */
 if(q[3]==1)
  for(i=0;i<13;i++)
   if(p[i]==3) { *x=i?i:13; return 6;}

/* ¨ß­F */
 if(q[2]==2)
 {
  for(*x=0,i=0;i<13;i++)
   if(p[i]==2)
   {
    if((i>1?i:i+13)>(*x==1?14:*x))
    {
     *x=i?i:13; *y=0;
     for(j=0;j<5;j++) if(a[j]==i&&b[j]>*y) *y=b[j];
    }
   }
  return 7;
 }

/* ­F */
 if(q[2]==1)
  for(i=0;i<13;i++)
   if(p[i]==2)
   {
    *x=i?i:13; *y=0;
    for(j=0;j<5;j++) if(a[j]==i&&b[j]>*y) *y=b[j];
    return 8;
   }

/* ¤@±i */
 *x=0; *y=0;
 for(i=0;i<5;i++)
  if((a[i]=a[i]?a[i]:13>*x||a[i]==1)&&*x!=1)
  { *x=a[i]; *y=b[i];}

 return 9;
}

/* a ¬OÂI¼Æ .. b ¬Oªá¦â */
tran(a,b,c)
char *a,*b,*c;
{
 int i;
 for(i=0;i<5;i++)
 {
  a[i]=c[i]%13;
  if(!a[i]) a[i]=13;
 }

 for(i=0;i<5;i++)
  b[i]=c[i]/13;
}

check(p,q,r,cc)
char *p,*q,*r,*cc;
{
 char i;

 for(i=0;i<13;i++) p[i]=0;
 for(i=0;i<5;i++) q[i]=0;
 for(i=0;i<4;i++) r[i]=0;

 for(i=0;i<5;i++)
  p[cc[i]%13]++;

 for(i=0;i<13;i++)
  q[p[i]]++;

 for(i=0;i<5;i++)
  r[cc[i]/13]++;
}

// ¦Pªá¶¶¡BÅKªK¡B¸¬¡B¦Pªá¡B¶¶¡B¤T±ø¡B¨ß­F¡B­F¡B¤@°¦
show_style(my,cpu)
char my,cpu;
{
 char *style[9]={"¦Pªá¶¶","¥|±i","¸¬Äª","¦Pªá","¶¶¤l",
              "¤T±ø","¨ß­F","³æ­F","¤@±i"};
 move(5,26); prints("[41;37;1m%s[m",style[cpu-1]);
 move(15,26); prints("[41;37;1m%s[m",style[my-1]);
 sprintf(sty,"§ÚªºµP[44;1m%s[m..¹q¸£ªºµP[44;1m%s[m",
  style[my-1],style[cpu-1]);
}

/********************************/
/* BBS ¯¸¤º¹CÀ¸¡V¤Ñ¦a¤E¤E       */
/*                     11/26/98 */
/* dsyan.bbs@Forever.twbbs.org  */
/********************************/

#undef  NINE_DEBUG

//               0  1  2  3  4  5  6  7  8  9 10 11 12 /* ¹q¸£ AI ©Ò¦b */
// char cp[13]={ 9, 8, 7, 6, 3, 2, 1, 0,11, 5, 4,10,12};
char tb[13]=  { 7, 6, 5, 4,10, 9, 3, 2, 1, 0,11, 8,12};
char *tu[4] = {"¡õ","¡÷","¡ô","¡ö"};
char card[52],hand[4][5],now,dir,turn,live;
char buf[255];
int sum;

static int
forqp(a,b)
char *a,*b;
{
 return tb[(*a)%13]-tb[(*b)%13];
}

p_nine()
{
 char genbuf[200];
 int bet,i,j,k,tmp,x,xx;
 FILE *fs;
 srandom(time(0));
 more("game/99.welcome",NULL);
 while(-1)
 {
  utmp_mode(M_NINE);
  show_money(bet=0);
  do
  {
   vget(21, 0,"­n¤Uª`¦h¤Ö©O(¤W­­5000)? «ö Enter Â÷¶}>", genbuf, 5, DOECHO);
   bet=atoi(genbuf);
   if(bet<0) bet=0;
  } while(bet>5000);
  if(!bet) return 0;
  if(check_money(bet))return 0;

  move(1,0);
  fs=fopen("game/99","r");
  while (fgets(genbuf, 255, fs)) prints(genbuf);

  move(21,0); clrtoeol();
  prints("[33;1m (¡ö)(¡÷)§ïÅÜ¿ïµP  (¡õ)¬d¸ß¸ÓµP§@¥Î (SPCAE)(Enter)¥´µP  [m");
  demoney(bet);
  show_money(bet);

  for(i=0;i<52;i++) card[i]=1;

  for(i=0;i<4;i++)
  {
   for(j=0;j<5;j++)
   {
    while(-1)
    {
     k=random()%52;
     if(card[k])
     {
      hand[i][j]=k;
      card[k]=0;
      break;
  }}}}

  qsort(hand[0],5,sizeof(char),forqp);
  x=xx=now=turn=sum=tmp=0;
  dir=1; live=3;
  show_mycard(100);

  while(-1)
  {
   move(9,52); prints(tu[turn]); refresh();
   sum++;
   if(turn) //¹q¸£
   {
    qsort(hand[turn],5,sizeof(char),forqp);
    for(i=0;i<5;i++)
    {
     tmp=hand[turn][i]%13;
     if(tmp==0 || tmp==4 || tmp==5 || tmp>9) break;
     if(now+tmp<=99 && now+tmp>=0) break;
    }
    if(i<2) if (tmp==0 || tmp==4 || tmp==5 || tmp>9) i+=random()%(5-i);
    if(i==5) cpu_die();
     else add(&(hand[turn][i]));
    if(random()%5==0) mmsg();
    continue;
   }

   if(!live)
   {
//    game_log(NINE, "[32;1m¦b %d ±iµPÄ¹¤F.. :)) [m %d",sum,bet);
    if(sum<25) live=20;
    else if(sum<50) live=15;
    else if(sum<100) live=10;
    else if(sum<150) live=7;
    else if(sum<200) live=5;
    else live=3;
    inmoney(bet*(live+1));
    sprintf(buf,"Ä¹¤F %d ... :D",bet*live);
    vmsg(buf);
    break;
   }

   tmp=hand[0][4]%13;
   if(tmp!=0 && tmp!=4 && tmp!=5 && tmp<10 && now+tmp>99)
   {
    vmsg("¶ã¶ã¶ã..³Q¹qÃz¤F!!.. :~");
//    game_log(NINE, "[31;1m¦b %d ±iµP³Q¹q¸£¹qÃz±¼¤F.. :~ %d[m %d",sum,live,bet);
    break;
   }

   while(tmp!=13 && tmp!=32) //¤HÃþ
   {
    move(18,xx*4+30); outs("  ");
    move(18,(xx=x)*4+30);

    if(tb[hand[0][x]%13]<7)
    {
     if(hand[0][x]%13+now>99) outs("¡I");
      else outs("¡³");
    }
    else outs("¡¹");

    move(18,x*4+31);
    refresh();

    switch(tmp=vkey())
    {
#ifdef NINE_DEBUG
     case KEY_UP:
      vget(22, 0,"§âµP´«¦¨> ", genbuf, 3, DOECHO);
      card[hand[0][x]]=3;
      hand[0][x]=atoi(genbuf);
      card[hand[0][x]]=0;
      qsort(hand[0],5,sizeof(char),forqp);
      show_mycard(100);
      break;
#endif
     case KEY_DOWN:
      nhelp(hand[0][x]);
      break;
     case KEY_LEFT: case 'l':
      x=x?x-1:4;
      break;
     case KEY_RIGHT: case 'r':
      x=(x==4)?0:x+1;
      break;
     case 'q':
      break;
    }
    if(tmp=='q') return;
   }

   move(18,xx*4+30); outs("  ");
   if(add(&(hand[0][x])))
   {
    vmsg("¶ã¶ã¶ã..¥ÕÄêÃz¤F!!.. :~");
//    game_log(NINE, "[31;1m¦b %d ±iµP¥ÕÄêÃz¤F.. :~ %d[m %d",sum,live,bet);
    break;
   }
   qsort(hand[0],5,sizeof(char),forqp);
   show_mycard(100);
}}}

show_mycard(t)
char t;
{
  char i;
#ifdef NINE_DEBUG
  char j;
#endif
  char *suit[4] = {"¢Ñ","¢Ò","¢Ö","¢á"};
  char *num[13] = {"¢Ù","¢Ï","¢±","¢²","¢³","¢´","¢µ",
                   "¢¶","¢·","¢¸","10","¢Ø","¢ß"};
  char coorx[4] = {30,38,30,22};
  char coory[4] = {8,6,4,6};

#ifdef NINE_DEBUG
  move(22,0);
  for(i=3;i>0;i--)
  {
   if(hand[i][0]==-1) continue;
   qsort(hand[i],5,sizeof(char),forqp);
   for(j=0;j<5;j++)
    prints(num[hand[i][j]%13]);
   prints("  ");
  }
#endif

  if(t==100)
  {
   for(i=0;i<5;i++)
   {
    move(16, 30+i*4); prints(num[hand[0][i]%13]);
    move(17, 30+i*4); prints(suit[hand[0][i]/13]);
   }
   return;
  }

  move(coory[turn], coorx[turn]);
  prints("¢~¢w¢w¢w¢¡");
  move(coory[turn]+1,coorx[turn]);
  prints("¢x%s    ¢x",num[t%13]);
  move(coory[turn]+2,coorx[turn]);
  prints("¢x%s    ¢x",suit[t/13]);
  move(coory[turn]+3,coorx[turn]);
  prints("¢x      ¢x");
  move(coory[turn]+4,coorx[turn]);
  prints("¢x      ¢x");
//  prints("¢x    %s¢x",num[t%13]);
  move(coory[turn]+5,coorx[turn]);
  prints("¢x      ¢x");
//  prints("¢x    %s¢x",suit[t/13]);
  move(coory[turn]+6, coorx[turn]);
  prints("¢¢¢w¢w¢w¢£");

  move(8,50); prints("%s  %s",dir==1?"¡ú":"¡ù",dir==1?"¡ø":"¡û");
  move(10,50); prints("%s  %s",dir==1?"¡û":"¡ø",dir==1?"¡ù":"¡ú");

  move(13,46); prints("ÂI¼Æ¡G%c%c%c%c",(now/10)?162:32,
   (now/10)?(now/10+175):32,162,now%10+175);
  move(14,46); prints("±i¼Æ¡G%d",sum);
  refresh();
  sleep(1);
  move(21,0); clrtoeol(); refresh();
  prints("[33;1m (¡ö)(¡÷)§ïÅÜ¿ïµP  (¡õ)¬d¸ß¸ÓµP§@¥Î (SPCAE)(Enter)¥´µP [m");
}

int add(t)
char *t;
{
  int k=0,change=0;

   switch(*t%13)
   {
    case 4:  //4 °jÂà
     dir=-dir;
     break;

    case 5:  //5 «ü©w
     move(21,0); clrtoeol();

     prints("«ü©w¨º¤@®a¡H ");
     for(change=3;change>=0;change--)
      if(turn!=change && hand[change][0]!=-1)
       prints("(%s) ",tu[change]);

     change=0;

     while(!change)
     {
      int tmp;
      if(turn || live==1) tmp=random()%4+3;
       else tmp=vkey();

      if((turn!=3 && hand[3][0]!=-1) && (tmp==KEY_LEFT || tmp==6) )
       change=6;
      else if((turn!=2 && hand[2][0]!=-1) && (tmp==KEY_UP || tmp==5) )
       change=5;
      else if((turn!=1 && hand[1][0]!=-1) && (tmp==KEY_RIGHT || tmp==4) )
       change=4;
      else if((turn!=0 && hand[0][0]!=-1) && tmp==3)
       change=3;
     }

     prints("[32;1m(%s)[m",tu[change-3]);
     break;

    case 10: //10 ¥[©Î´î10
     ten_or_twenty(10);
     break;

    case 11: //J PASS
     break;

    case 12: //Q ¥[©Î´î20
     ten_or_twenty(20);
     break;

    case 0:  //K °¨¤WÅÜ99
     now=99;
     break;

    default:
     if((now+(*t%13))>99) return -1;
      else now+=(*t%13);
     break;
   }

   refresh();
   show_mycard(*t);
   while(-1)
   {
    k=random()%52;
    if(card[k]==1 && card[k]!=0)
    {
     card[*t]=3; *t=k; card[k]=0;
     break;
    }
    else card[k]--;
   }

   while(-1)
   {
    if(change)
    { turn=change-3; break;}
    else
    {
     turn=(turn+4+dir)%4;
     if(hand[turn][0]>-1) break;
   }}
   return 0;
}

ten_or_twenty(t)
int t;
{
     if(now<t-1) now+=t;
     else if(now>99-t) now-=t;
     else
     {
      int tmp=0;
      move(21,0); clrtoeol();
      prints("(¡ö)(+)¥[%d  (¡÷)(-)´î%d  ",t,t);

      while(!tmp)
      {
       if(turn) tmp=random()%2+5;
        else tmp=vkey();
       switch(tmp)
       {
        case KEY_LEFT: case '+': case 5:
         now+=t; prints("[32;1m¥[ %d[m",t); break;
        case KEY_RIGHT: case '-': case 6:
         now-=t; prints("[32;1m´î %d[m",t); break;
        default:
         tmp=0;
       }
      }
     }
}

cpu_die()
{
 switch(turn)
 {
  case 1: move(9,55); break;
  case 2: move(7,52); break;
  case 3: move(9,49); break;
 }
 prints("  ");
 live--;
 sprintf(buf,"¹q¸£ %d Ãz¤F!!! .. :DD",turn);
 vmsg(buf);
 hand[turn][0]=-1;
 while(-1)
 {
  turn=(turn+4+dir)%4;
  if(hand[turn][0]>-1) break;
 }
}

nhelp(t)
int t;
{
 t%=13;
 switch(t)
 {
  case 0: vmsg("¤E¤E¡GÂI¼Æ°¨¤WÅÜ¦¨¢¸¢¸"); break;
  case 4: vmsg("°jÂà¡G¹CÀ¸¶i¦æ¤è¦V¬Û¤Ï"); break;
  case 5: vmsg("«ü©w¡G¦Û¥Ñ«ü©w¤U¤@­Óª±®a"); break;
  case 11: vmsg("PASS¡G¥iPASS¤@¦¸"); break;
  case 10: vmsg("ÂI¼Æ¥[©Î´î 10"); break;
  case 12: vmsg("ÂI¼Æ¥[©Î´î 20"); break;
  default:
    sprintf(buf,"ÂI¼Æ¥[ %d",t);
    vmsg(buf); break;
 }
}

mmsg()
{
char *msg[12]={
"³Þ¡K¥´§Ö¤@ÂI°Õ¡I",
"¥´µP±M¤ß¤@ÂI¡A¤£­n¬y¤f¤ô¡K",
"¤£­n¬Ý¬ü¬Ü¡K",
"¤j·Ý¦æ¦æ¦n¡A©ñ¹L§Ú§a¡K",
"±µ©Û¨ü¦º§a¡I¡I¡I",
"«z¡A§A¦n¼F®`³á¡I³ºµM¯à¥´¥X³o±iµP¡I",
"§A¤@©w¬O½ä®{Âà¥@ªº¡I",
"last hand¡K",
"¦Aª±¹qÃz§A¡I",
"«z¡K§A¦³¯Ý¦Ù«¨..",
"§Aªº¨{¤l¶]¥X¨Ó¤F«¨¡K",
"dsyan¬O¦n¤H¡Kgwen¬O«Ó­ô¡K"};
 move(21,0); clrtoeol(); refresh();
 prints("[%d;1m%s[m",random()%7+31,msg[random()%12]);
}



/* bingo */
int 
bingo()
{

 int place[5][5][3]={{{3,2,0},{3,6,0},{3,10,0},{3,14,0},{3,18,0}},
       		     {{5,2,0},{5,6,0},{5,10,0},{5,14,0},{5,18,0}},
  		     {{7,2,0},{7,6,0},{7,10,0},{7,14,0},{7,18,0}},
  		     {{9,2,0},{9,6,0},{9,10,0},{9,14,0},{9,18,0}},
  		     {{11,2,0},{11,6,0},{11,10,0},{11,14,0},{11,18,0}}};

 int account,bet,i=0,j=0,k=0,used[25]={0},ranrow,rancol,line=0,pp=0;
 char co[2];
 char m1[8];
 int money;
 int may=20;
 utmp_mode(M_BINGO);
 
while(-1)
{
account=13;
for(i=0;i<25;i++)
used[i]=0;
for(i=0;i<5;i++)
for(j=0;j<5;j++)
place[i][j][2]=0;
i=0;j=0;k=0;
line=0;pp=0; 

 clear();
  do
    {
       vget(1, 0,"­n¤U¦h¤Ö©O(¤W­­5000)? «ö Enter Â÷¶}>", m1, 6,DOECHO);
          money=atoi(m1);
             if(money<0) money=0;
               } while(money>5000);
                 if(!money) 
                   return 0;
                   if(money>cuser.money)
                     {
                        vmsg("§Aªº²{ª÷¤£°÷³á.. :)");
                           return 0;
                     }
 demoney(money);                            

 while(account>=0)
 {
 clear();
 prints("\n\n");
 j=0;
  for(i=0;i<=10;i++)
   {
    if(i%2==0)
    outs("   [1;34;40m¡½¡½¡½¡½¡½¡½¡½¡½¡½¡½¡½[0m\n");
    else
    {
    outs("   [1;34;40m¡½");
    if(place[j][0][2])
    prints("[1;37;40m%2d",place[j][0][2]);
    else prints("[1;32m¡½");
    outs("[1;34;40m¡½");
    if(place[j][1][2])
    prints("[1;37;40m%2d",place[j][1][2]);
    else prints("[1;32m¡½");
    outs("[1;34;40m¡½");
    if(place[j][2][2])
    prints("[1;37;40m%2d",place[j][2][2]);
    else prints("[1;32m¡½");
    outs("[1;34;40m¡½");
    if(place[j][3][2])
    prints("[1;37;40m%2d",place[j][3][2]);
    else prints("[1;32m¡½");
    outs("[1;34;40m¡½");
    if(place[j][4][2])
    prints("[1;37;40m%2d",place[j][4][2]);
    else prints("[1;32m¡½");
    outs("[1;34;40m¡½[0m\n");
    j++;
    }
   }
prints("\n\n\n\n");   
prints("[1;37;44m©|¥¼¶}¥Xªº¸¹½X[0m\n");
   for(i=1;i<=25;i++)
   {
     pp+=3;
     if(used[i-1]==0)
     prints(" %2d",i);
   }
if(line==1 || account==1) break;

if(account>9) may=20;
else if(account==9) may=10;
else if(account==8) may=9;
else if(account==7) may=8;
else if(account==6) may=7;
else if(account==5) may=6;
else if(account==4) may=5;
else if(account==3) may=3;
else if(account==2) may=1;


 prints("\n©|¦³[1;33;41m %2d [0m¦¸¾÷·|¥i²q ¤U¦¸²q¤¤¥i±o[1;37;44m %d [0m­¿ \n",account-1,may);
 vget(20,0,"½Ð¿é¤J±zªº¸¹½X : ",co,3,DOECHO);

 bet=atoi(co);
 if(bet<=0 || bet > 25 || used[bet-1]!=0) continue;
  used[bet-1]=1;
  ranrow=random();
  ranrow=ranrow%5;
  rancol=random();
  rancol=rancol%5;

  while(place[ranrow][rancol][2]!=0)
  {
     ranrow=random();
      ranrow=ranrow%5;
        rancol=random();
        rancol=rancol%5;
  }
  place[ranrow][rancol][2]=bet;  
  account--;
  
 for(i=0;i<5;i++)
   {
    if (place[i][0][2]!=0 && place[i][1][2]!=0 && place[i][2][2]!=0 && place[i][3][2]!=0 &&place[i][4][2]!=0 )
    {
      line=1;
    }  
   }   
 for(i=0;i<5;i++)
  {
   if(place[0][i][2]!=0 &&place[1][i][2]!=0 &&place[2][i][2]!=0 &&place[3][i][2]!=0 &&place[4][i][2]!=0 )
   {
   line=1;
   }
  }

if(place[0][0][2]!=0 && place[1][1][2]!=0 && place[3][3][2]!=0 && place[4][4][2]!=0 && place[2][2][2]!=0)
line=1;
if(place[0][4][2]!=0 && place[1][3][2]!=0 && place[2][2][2]!=0 && place[3][2][2]!=0 && place[0][4][2]!=0)
line=1;

 }
 
if(line==1)
{
prints("\n®¥³ß§A...Ä¹¤F[1;33;41m %d [0m¤¸ ",(money*may)); 
inmoney((money*may)+money);
log_file(FN_BINGO," ÁÈ¤F %d ¤¸ ",(money*may));
}
else 
{
prints("\n¹B®ð¤£¨Î...¦A¨Ó¤@½L§a!!");
log_file(FN_BINGO," ¿é±¼¤F  ");
}
 vmsg(NULL);
} 
 return 0;
}       
  
