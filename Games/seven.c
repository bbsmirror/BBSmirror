/***************************************************/
/*  SevenCard game by weiren 1998/7/29             */
/*  e-mail: weiren@mail.eki.com.tw                 */
/***************************************************/
#include "bbs.h"

int p_seven()
{
  char buf1[8],log[80];
  char *kind[9]={"¯QÀs","³æ­F","¨ß­F","¤T±ø","¶¶¤l","¦Pªá","¸¬Äª",
                 "ÅK¤ä","¬h¤B"};
  char *poker[52]={"¢±","¢±","¢±","¢±","¢²","¢²","¢²","¢²",
                   "¢³","¢³","¢³","¢³","¢´","¢´","¢´","¢´","¢µ","¢µ","¢µ","¢µ",
                   "¢¶","¢¶","¢¶","¢¶","¢·","¢·","¢·","¢·","¢¸","¢¸","¢¸","¢¸",
                   "10","10","10","10","¢Ø","¢Ø","¢Ø","¢Ø","¢ß","¢ß","¢ß","¢ß",
                   "¢Ù","¢Ù","¢Ù","¢Ù","¢Ï","¢Ï","¢Ï","¢Ï"};
  int cardlist[52]={0};
  int mark[2]={7,7}, set[6],key,tax=0; /* tax ¬°ª±®aÄ¹®É©âªºµ| */
  int i,j,k,x,m,ch,z=1;
  int win,color,color2,bet;
  int host_card[7]={0}, guest_card[7]={0};

  time_t now = time(0);
  time(&now);

while(-1){
  clear();
  setutmpmode(SEVENCARD);
  showtitle("½ä«°¤C±i", BoardName);
  show_money(bet=0);
  do
  {
   getdata(21, 0,"­n¤Uª`¦h¤Ö©O(¤W­­1000)? «ö Enter Â÷¶}>", buf1, 5, 1, 0); 
   bet=atoi(buf1);
   if(bet<0) bet=0;
  } while(bet>1000);
  if(!bet) return 0;
  if(bet>cuser.money) 
  {
   pressanykey("§Aªº²{ª÷¤£°÷³á.. :)");
   return 0;
  }

  demoney(bet);
  show_money(bet);
  move(21,0);prints("(«ö ¡ô¡õ¡ö¡÷ ©Î ijkl ¿ïµP, ¿ï¦n«ö enter ÅuµP)");
  
  for(i=0;i<52;i++) cardlist[i]=0;
  mark[0]=mark[1]=7; 
  z=1;
  
  for(i=1;i<=52;i++){
    m=0;
    do{
    j=(time(0)+cuser.money+random())%52;
    if (cardlist[j]==0){cardlist[j]=i;m=1;}
    }while(m==0);
  };
  for(i=0;i<52;i++)cardlist[i]--; /* ¬~µP */

  j=0;
  for(i=0;i<7;i++){
    host_card[i]=cardlist[j];
    j++;
    guest_card[i]=cardlist[j];
    j++;
  }        /* µo«e¤Q¥|±iµP */

  for(i=0;i<7;i++){
    for(j=0;j<(6-i);j++){
      if(guest_card[j]>guest_card[j+1]){
        x=guest_card[j];guest_card[j]=guest_card[j+1];guest_card[j+1]=x;
      }
      if(host_card[j]>host_card[j+1]){
        x=host_card[j];host_card[j]=host_card[j+1];host_card[j+1]=x;
      }
    }
  }        /* ±Æ§Ç */
  move(1,0);
  prints("[33;1m¥»¹CÀ¸¥Ñ¯îÂÕ¤Û¹Ò(weird.twbbs.org)¯¸ªø weiren ³]­p´£¨Ñ! ¯S¦¹·PÁÂ!!\n");
  prints("e-mail: weiren@mail.eki.com.tw[m");

  move(3,0);  prints("¢~¢w¢~¢w¢~¢w¢~¢w¢~¢w¢~¢w¢~¢w¢w¢w¢¡");
  move(4,0);  prints("¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x      ¢x");
  move(5,0);  prints("¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x      ¢x");
  move(6,0);  prints("¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x      ¢x");
  move(7,0);  prints("¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x      ¢x");
  move(8,0);  prints("¢x  ¢x  ¢x  ¢x  ¢x  ¢x  ¢x      ¢x");
  move(9,0);  prints("¢¢¢w¢¢¢w¢¢¢w¢¢¢w¢¢¢w¢¢¢w¢¢¢w¢w¢w¢£");

  for(i=0;i<7;i++){
    print_Scard(guest_card[i],11,0+4*i);  /* ¦L¥X«e¤C±iµP */
  }

  j=2;k=0;x=0;
  move(15,2);
  do{
    ch=igetkey();
    switch (ch)
    {
      case KEY_RIGHT:
      case 'l':
        j+=4;if(j>26)j=26;
        break;
      case KEY_LEFT:
      case 'j':
        j-=4;if(j<2)j=2;
        break;
      case KEY_UP:
      case 'i':
        k=(j-2)/4;
        if(x<2&&mark[0]!=k&&mark[1]!=k){
          if(mark[0]==7)mark[0]=k;
          else mark[1]=k;
          x++;
          cursor_show(15,j);
          }
        break;
      case KEY_DOWN:
      case 'k':
        k=(j-2)/4;
        if(mark[0]==k){mark[0]=7;x--;}
        if(mark[1]==k){mark[1]=7;x--;}
        cursor_clear(15,j);
        break;
      case 13:   /* ¿ï¥X¨â±i«á«ö enter */
        if(x==2)z=0;
        break;
        prints("¥»¹CÀ¸¥Ñ¯îÂÕ¤Û¹Ò(weird.twbbs.org)¯¸ªø weiren ³]­p\n");
        prints("e-mail: weiren@mail.eki.com.tw");
    }
    move(15,j);
  }while(z==1);

  if(mark[0]>mark[1]){i=mark[0];mark[0]=mark[1];mark[1]=i;}
  for(i=1;i<18;i++){move(i,0);clrtoeol();}
  print_Scard(guest_card[mark[0]],11,0);
  print_Scard(guest_card[mark[1]],11,4);
  j=0;
  for(i=0;i<7;i++){
    if(i!=mark[0]&&i!=mark[1]){
      print_Scard(guest_card[i],11,16+j*4);
      set[j]=guest_card[i];
      j++;
    }
  }                   /* ¦L¥Xª±®a¤À¦n¨â°ô«áªºµP */
  set[5]=5;
  if(diedragon(set,guest_card[mark[0]],guest_card[mark[1]])==1)
    {;pressanykey("­ËÀs!");continue;}
  if(guest_card[mark[0]]/4==guest_card[mark[1]]/4)x=1;
  
  key=find_host(host_card);
  print_hostcard(host_card,key,log);
  i=bigsmall(host_card,guest_card,key,mark);
  switch(i){
    case 0:win=2;color=41;color2=41;break; /* ª±®a duA duB ¬ÒÄ¹  */
    case 1:win=1;color=41;color2=47;break; /*      duA Ä¹ duB ¿é */
    case 2:win=1;color=47;color2=41;break; /*      duA ¿é duB Ä¹ */
    case 3:win=0;color=47;color2=47;break; /*      ¨â½ä¬Ò¿é */
  }
  game_log(SEVENCARD,"§ÚªºµP[46;1m%s%s%s[m..¹q¸£[45;1m%s[m..%s..%d[m",poker[guest_card[mark[0]]],
   x==1?"­F":poker[guest_card[mark[1]]],kind[find_all(set)],log,
   win?(win==1?"[33;1m¥­¤â":"[32;1mÄ¹¤F"):"[31;1m¿é¤F",bet);
  move(15,4);
  prints("[1;%d;%dm   %s%s   [m  ¢x  ¢x  [1;%d;%dm         %s         [m"
       ,color,  color==41?33:30
       ,poker[guest_card[mark[0]]],x==1?"­F":poker[guest_card[mark[1]]]
       ,color2, color2==41?33:30
       ,kind[find_all(set)]);
  i=bet*2-bet/100*tax;
  switch(win){
    case 2:pressanykey("[1;33m§AÄ¹¤F %d !!.. :D[44m",i-bet);inmoney(i);break;
    case 1:pressanykey("[1;36m¥­¤â!!..[44m");inmoney(bet);break;
    case 0:pressanykey("[1;31m§A¿é¤F³á.. :))[44m" );break;
  }
}}

diedragon(set,a,b)
int set[6],a,b;
{
  int card[13]={0},i,z,first[2];
  first[0]=a;first[1]=b;
  z=find_all(set);
  if(z==0){ /* ²Ä¤G°ô¯QÀs */
    if(first[0]/4==first[1]/4)return 1;
    if(first[1]/4>set[4]/4)return 1;
    if(first[1]/4==set[4]/4){
      if(first[0]/4>set[3]/4)return 1;
     } /* ­ËÀs */
  }
  if(z==1){
    for(i=0;i<5;i++)card[set[i]/4]++;
    for(i=0;i<13;i++)
      if(card[i]==2)
        if(first[0]/4==first[1]/4)
          if(first[0]/4>i)return 1; /* ¨â½ä³£³æ­F¥B­ËÀs */
  }
  return 0;
}

bigsmall(h,g,key,gm)
int h[7],g[7],key,gm[2];
{
  int hm[2],i,j,k=0,tmp=0,tmp2=0,duA=0,duB=0,hset[6],gset[6];
  int gc[13]={0},hc[13]={0},x,a,b;/* duA duB ¬O¨â½ä§P©w¿éÄ¹°Ñ¼Æ, 1 ¬O¹q¸£Ä¹ */
  for(i=0;i<6;i++){
    for(j=i+1;j<7;j++){
      if(key==k){hm[0]=i;hm[1]=j;};
      k++;
    }
  }
  if(hm[1]<hm[0]){k=hm[1];hm[1]=hm[0];hm[0]=k;};
  if(gm[1]<gm[0]){k=gm[1];gm[1]=gm[0];gm[0]=k;};
  if(h[hm[0]]/4==h[hm[1]]/4)tmp=1;
  if(g[gm[0]]/4==g[gm[1]]/4)tmp2=1;
  if(tmp==tmp2){
    if(h[hm[1]]/4>g[gm[1]]/4)duA=1;  /* duA=1 ªí¥Ü²Ä¤@°ô¸Ë®aÄ¹ */
    if(h[hm[1]]/4==g[gm[1]]/4&&tmp==1)duA=1; /* ²Ä¤@½ä³£­F¥B¥­¤â, ²ø®aÄ¹ */
    if(h[hm[1]]/4==g[gm[1]]/4&&tmp==0)
      if(h[hm[0]]/4>=g[gm[0]]/4)duA=1;
  }
  if(tmp>tmp2)duA=1;
  if(tmp<tmp2)duA=0;
  k=0;j=0;
  for(i=0;i<7;i++){
    if(i!=hm[0]&&i!=hm[1]){hset[j]=h[i];j++;};
    if(i!=gm[0]&&i!=gm[1]){gset[k]=g[i];k++;};
  }hset[5]=5;gset[5]=5;
  tmp=find_all(hset);
  tmp2=find_all(gset);
  if(tmp>tmp2)duB=1;
  if(tmp==tmp2){
    for(i=0;i<5;i++){gc[gset[i]/4]++;hc[hset[i]/4]++;}
    switch(tmp){
      case 0:i=12;x=0;duB=1;     /* ¨â¤è³£¬O¯QÀs */
             do{
               if(hc[i]>gc[i]){duB=1;x=1;}
               if(hc[i]<gc[i]){duB=0;x=1;}
               i--;if(i<0)x=1;
             }while(x==0);
             break;
      case 1:for(i=0;i<12;i++){if(hc[i]==2)a=i;if(gc[i]==2)b=i;};
             if(a>b)duB=1;   /* ¨â¤è³£¬O­F */
             if(a==b){
                       i=12;j=12;x=0;duB=1;
                       do{
                         if(hc[i]==2)i--;
                         if(hc[j]==2)j--;
                         if(hc[i]>gc[j]){duB=1;x=1;}
                         if(hc[i]<gc[j]){duB=0;x=1;}
                         i--;j--;if(i<0||j<0)x=1;
                       }while(x==0);
                     }
             break;
      case 2:i=12;x=0;duB=2; /* ¨â¤è³£¬O¨ß­F */
             do{
               if(hc[i]>gc[i]&&hc[i]!=1){duB=1;x=1;};
               if(hc[i]<gc[i]&&gc[i]!=1){duB=0;x=1;};
               i--;
               if(i<0)x=1;
             }while(x==0);
             if(duB==2){
               for(i=0;i<12;i++){if(hc[i]==1)a=i;if(gc[i]==1)b=i;};
               duB=1;
               if(a<b)duB=0;
             }
             break;
      case 3:
      case 6:for(i=0;i<12;i++){if(hc[i]==3)a=i;if(gc[i]==3)b=i;};
             if(a>b)duB=1; /* ¨â¤è³£¬O¤T±ø(­J¿c) */
             if(a<b)duB=0;
             break;
      case 4:i=12;x=0;a=0;b=0;     /* ¨â¤è³£¬O¶¶¤l */
             do{
               if(hc[i]>gc[i]){duB=1;x=1;};
               if(hc[i]<gc[i]){duB=0;x=1;};
               i--;if(i<0){duB=1;x=1;};
             }while(x==0);
             if(hc[12]==hc[0]&&hc[0]==1)a=1;
             if(gc[12]==gc[0]&&gc[0]==1)b=1;
             if(a>b)duB=0;
             if(a<b)duB=1;
             if(a==b&&b==1)duB=1;
             break;
      case 5:if(hset[0]%4>gset[0]%4)duB=1; /* ¨â¤è³£¬O¦Pªá */
             if(hset[0]%4<gset[0]%4)duB=0;
             if(hset[0]%4==gset[0]%4){
               if(hset[4]>gset[4])duB=1;
               if(hset[4]<gset[4])duB=0;
             }
             break;
      case 7:for(i=0;i<12;i++){if(hc[i]==4)a=i;if(gc[i]==4)b=i;};
             if(a>b)duB=1; /* ¨â¤è³£¬OÅK¤ä */
             if(a<b)duB=0;
             break;
      case 8:if(hset[0]%4>gset[0]%4)duB=1; /* ¨â¤è³£¬O¦Pªá¶¶ */
             if(hset[0]%4<gset[0]%4)duB=0;
             if(hset[0]%4==gset[0]%4){
               i=12;x=0;
               do{
                 if(hc[i]>gc[i]){duB=1;x=1;};
                 if(hc[i]<gc[i]){duB=0;x=1;};
                 i--;if(i<0){duB=1;x=1;};
               }while(x==0);
             }
             break;
    }
  }
  return 2*duA+duB;
}

print_hostcard(card,x,log) /* x ¬°¨â±iªº²Õ¦X key */
int card[7],x;
char *log;
{
  char *kind[9]={"¯QÀs","³æ­F","¨ß­F","¤T±ø","¶¶¤l","¦Pªá","¸¬Äª",
                 "ÅK¤ä","¬h¤B"};
  char *poker[52]={"¢±","¢±","¢±","¢±","¢²","¢²","¢²","¢²",
                   "¢³","¢³","¢³","¢³","¢´","¢´","¢´","¢´","¢µ","¢µ","¢µ","¢µ",
                   "¢¶","¢¶","¢¶","¢¶","¢·","¢·","¢·","¢·","¢¸","¢¸","¢¸","¢¸",
                   "10","10","10","10","¢Ø","¢Ø","¢Ø","¢Ø","¢ß","¢ß","¢ß","¢ß",
                   "¢Ù","¢Ù","¢Ù","¢Ù","¢Ï","¢Ï","¢Ï","¢Ï"};
  int i,j,k=0,tmp,tmp2,set[6];
  for(i=1;i<6;i++){move(5+i,0);clrtoeol();}
  for(i=0;i<6;i++){
    for(j=i+1;j<7;j++){
    if(x==k){tmp=i;tmp2=j;};
    k++;
    }
  }
  print_Scard(card[tmp],3,0);
  print_Scard(card[tmp2],3,4);
  j=0;
  for(i=0;i<7;i++){
    if(i!=tmp&&i!=tmp2){
      print_Scard(card[i],3,16+j*4);
      set[j]=card[i];
      j++;
    }
  }
  set[5]=5;
  move(7,4);
  if(card[tmp]/4==card[tmp2]/4) x=1;
  prints("[1;44;33m   %s%s   [m  ¢x  ¢x  [1;44;33m         %s         [m"
       ,poker[card[tmp]],x==1?"­F":poker[card[tmp2]]
       ,kind[find_all(set)]);
  sprintf(log,"%s%s%s",poker[card[tmp]],x==1?"­F":poker[card[tmp2]],
       kind[find_all(set)]);
}


int find_host(h) /* ¶Ç¦^¨â±iªº²Õ¦X key */
int h[7];
{
  int i,j,k,x=0,z=0,result[21]={0},set[6]={0},first[2],tmp=0,tmp2=0;
  for(i=0;i<6;i++){
    for(j=i+1;j<7;j++){
      first[0]=h[i];first[1]=h[j];
      x=0;
      for(k=0;k<7;k++){
        if(i!=k&&j!=k){set[x]=h[k];x++;}
      }
    set[5]=5;
    result[z]=score(first,set);
    z++;
    }
  }
  for(i=0;i<21;i++)if(result[i]>=tmp){tmp=result[i];tmp2=i;};
  return tmp2;
}

int score(first,set)  /* ¦^¶Ç¤À¨â°ô«áªºµû¤À(AI), 
                         ¹q¸£·|§â 21 ºØµP«¬³£©î¥X¨Ó, ¨úµû¤À°ªªÌ */
int first[2],set[6];
{
  int i,z,card[13]={0},points=0;
  z=find_all(set);
  if(z==0){
    if(first[0]/4==first[1]/4)return 0;
    if(first[1]/4>=set[4]/4)return 0;    /* ­ËÀs */
  }
  if(z==1){
    for(i=0;i<5;i++)card[set[i]/4]++;
    for(i=0;i<13;i++)
      if(card[i]==2)
        if(first[0]/4==first[1]/4)
          if(first[0]/4>=i)return 0; /* ¨â½ä³£³æ­F¥B­ËÀs */
  }
  points=z+2; /* ²Ä¤G°ô¯QÀs´Nºâ¨â¤À, ¥H¤W»¼¼W */
  if(points>=5)points+=1; /* ²Ä¤G°ô­Y¦³¶¶¥H¤W¦A¥[¤@¤À */
  if(first[0]/4==first[1]/4)points+=3; /* ²Ä¤@½ä¦³­F¤À¼Æ¥[¤T */
  if(first[0]/4!=first[1]/4&&first[1]/4>=10)points++;
                                     /* ²Ä¤@½äµL­F¦³ Q ¥H¤W¥[¤@¤À */
  if(first[0]/4==12||first[1]/4==12)points+=1; /* ²Ä¤@½ä¦³ A ¤À¼Æ¦A¥[¤@ */
  return points;
}

int find_all(set)
int set[6];
{
  int i,a[9];     /* ¯QÀs, ­F , ¨ß­F, ¤T±ø, ¶¶, ¦Pªá, ­J¿c, ÅK¤ä, ¦Pªá¶¶ */
  a[0]=1;         /* a[0]  1    2     3     4    5    6     7     a[8]   */
  for(i=1;i<9;i++)a[i]=0;
  a[1]=find_pair(set);
  a[2]=find_tpair(set);
  switch(find_triple(set)){
    case 3: a[3]=1;break;
    case 4: a[7]=1;break;
  }
  a[4]=find_dragon(set);
  a[5]=find_flush(set);
  if(a[2]==1&&a[3]==1)a[6]=1; /* ¨ß­F + ¤T±ø = ­J¿c */
  if(a[4]==1&&a[5]==1)a[8]=1; /* ¦Pªá + ¶¶ = ¦Pªá¶¶ */
  for(i=8;i>=0;i--)if(a[i]==1)return i;
}

int print_Scard(int card,int x,int y)
{
  char *flower[4]={"¢Ñ","¢Ò","¢Ö","¢á"};
  char *poker[52]={"¢±","¢±","¢±","¢±","¢²","¢²","¢²","¢²",
                   "¢³","¢³","¢³","¢³","¢´","¢´","¢´","¢´","¢µ","¢µ","¢µ","¢µ",
                   "¢¶","¢¶","¢¶","¢¶","¢·","¢·","¢·","¢·","¢¸","¢¸","¢¸","¢¸",
                   "10","10","10","10","¢Ø","¢Ø","¢Ø","¢Ø","¢ß","¢ß","¢ß","¢ß",
                   "¢Ù","¢Ù","¢Ù","¢Ù","¢Ï","¢Ï","¢Ï","¢Ï"};

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
sort_card(set)
int set[6];
{
  int i,j,tmp;
  for(i=0;i<4;i++){
    for(j=0;j<(4-i);j++){
      if(set[j]>set[j+1]){tmp=set[j];set[j]=set[j+1];set[j+1]=tmp;}
    }
  }
}

int
find_pair(set)   /* ¦³ Pair ´N¶Ç¦^ 1 */
int set[6];
{
  int i,j;
  for(i=0;i<set[5]-1;i++){
    for(j=i+1;j<set[5];j++){
      if(set[j]/4==set[i]/4)return 1;
    }
  }
  return 0;
}

int
find_tpair(set)  /* Two Pair ¶Ç¦^ 1 */
int set[6];
{
  int i,j,k,z[13]={0};
  for(i=0;i<13;i++){
    for(j=0;j<5;j++){
      if(set[j]/4==i)z[i]++;
    }
  }
  k=0;
  for(i=0;i<13;i++){
    if(z[i]>=2)k++;
  }
  if(k==2)return 1;
  return 0;
}

int
find_triple(set)  /* ¤T±ø¶Ç¦^ 3, ÅK¤ä¶Ç¦^ 4 */
int set[6];
{
  int i,j,k;
  for (i=0;i<13;i++){
    k=0;
    for (j=0;j<5;j++){
      if (set[j]/4==i)k++;
    }
    if(k==4) return 4;
    if(k==3) return 3;
  }
  return 0;
}

int
find_dragon(set)        /* ¶¶¶Ç¦^ 1, §_«h¶Ç¦^ 0 */
int set[6];
{
  int i,test[6];
  for(i=0;i<5;i++)test[i]=set[i]/4;
  for(i=0;i<3;i++){
    if(test[i]+1!=test[i+1])return 0;
  }
  if(test[4]==12&&test[0]==0)return 1; /* A2345 ¶¶ */
  if(test[3]+1==test[4])return 1; /* ¤@¯ë¶¶ */
  return 0;
}

int
find_flush(set)         /* ¦Pªá¶Ç¦^ 1, §_«h¶Ç¦^ 0 */
int set[6];
{
  int i,test[6];
  for(i=0;i<5;i++)test[i]=set[i]%4;
  for(i=1;i<5;i++)if(test[0]!=test[i])return 0;
  return 1;
}
