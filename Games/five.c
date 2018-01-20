/*  ¤­¤l´Ñµ{¦¡   Programmed by Birdman     */
/*  140.116.102.125 ³s¯]«z«¢«¢¤p¯¸         */
/*  ¦¨¤j¹q¾÷88¯Å                           */

#include "bbs.h"
#include <sys/socket.h>
#define black 1
#define white 2
#define FDATA "five"

int player,winner=0,quitf;
int px,py,hand,tdeadf,tlivef,livethree,threefour;
int chess[250][2]={0,0};
int playboard[15][15]={0,0};
char abcd[15]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'};

struct fiverec
{
    int id;
    char userid[IDLEN+1];
    char username[23];
    int fwin;
    int floss;
    int fscore;
};

int initial_board()
{
        int i,j,k,t_win,t_loss,t_score;
        FILE *fp;
        char fname[50];

        for(i=0;i<=14;i++)
         for(j=0;j<=14;j++)
           playboard[i][j]=0;

        setuserfile(fname, FDATA);
        if ((fp = fopen(fname, "r")) != NULL)
         {
           fscanf(fp,"%d  %d  %d",&t_win,&t_loss,&t_score);
           fclose(fp);
         }
/*        toprenju(t_win,t_loss,t_score);*/
        setutmpmode(FIVE);
        hand=1;
        winner=0;
        quitf=0;
        px=14;
        py=7;
        clear();
        move(0,0);
        outs("¢z¢s¢s¢s¢s¢s¢s¢s¢s¢s¢s¢s¢s¢s¢{15           ¤@¤H¦Û¤vª±ª©¥»
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t14
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t13
¢u¢q¢q¡Ï¢q¢q¢q¢q¢q¢q¢q¡Ï¢q¢q¢t12
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t11
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t10
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t9
¢u¢q¢q¢q¢q¢q¢q¡Ï¢q¢q¢q¢q¢q¢q¢t8
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t7
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t6
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t5
¢u¢q¢q¡Ï¢q¢q¢q¢q¢q¢q¢q¡Ï¢q¢q¢t4
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t3
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t2
¢|¢r¢r¢r¢r¢r¢r¢r¢r¢r¢r¢r¢r¢r¢}1         q:Â÷¶}       Ins:®¬´Ñ
 A B C D E F G H I J K L M N O");


        move(7,14);
        outs("¡´");
        move(10,40);
        outs("q:Â÷¶}");
        player=white;
        playboard[7][7]=black;
        chess[1][0]=14; /*¬ö¿ý©Ò¤U¦ì§}*/
        chess[1][1]=7;
         move(4,40);
         outs("²Ä 1¤â ¡´H 8");
        user_guide();
        do{
          if(player==1){
           move(b_lines-5,10);
           outs("¥Õ¤â¡³");
           move(20,0);
           outs("´«¶Â¤U");
           per_move(0);}
          else{
           move(b_lines-5,10);
           outs("¶Â¤â¡´");
           move(20,0);
           outs("´«¥Õ¤U");
           per_move(0);}
/*check if five*/
           tdeadf=tlivef=livethree=threefour=0;
            for(j=0;j<=10;j++)
             calvalue(px/2,j,px/2,j+1,px/2,j+2,px/2,j+3,px/2,j+4);
           for(i=0;i<=10;i++)/*¾î¦V*/
             calvalue(i,py,i+1,py,i+2,py,i+3,py,i+4,py);
           for(i=-4;i<=0;i++)/*±×¥k¤U*/
             calvalue(px/2+i,py+i,px/2+i+1,py+i+1,px/2+i+2,py+i+2,
                      px/2+i+3,py+i+3,px/2+i+4,py+i+4);
           for(i=-4;i<=0;i++)/*±×¥ª¤U*/
             calvalue(px/2-i,py+i,px/2-i-1,py+i+1,px/2-i-2,py+i+2,px/2-i-3,
                      py+i+3,px/2-i-4,py+i+4);

            for(j=0;j<=9;j++)
             callfour(px/2,j,px/2,j+1,px/2,j+2,px/2,j+3,px/2,j+4,px/2,j+5);
           for(i=0;i<=9;i++)/*¥|¾î¦V*/
             callfour(i,py,i+1,py,i+2,py,i+3,py,i+4,py,i+5,py);
           for(i=-5;i<=0;i++){/*¥|±×¥k¤U*/
             callfour(px/2+i,py+i,px/2+i+1,py+i+1,px/2+i+2,py+i+2,
                      px/2+i+3,py+i+3,px/2+i+4,py+i+4,px/2+i+5,py+i+5);
                            /*¥|±×¥ª¤U*/
             callfour(px/2-i,py+i,px/2-i-1,py+i+1,px/2-i-2,py+i+2,px/2-i-3,
                      py+i+3,px/2-i-4,py+i+4,px/2-i-5,py+i+5);
             }
           if(tlivef>=2 && winner==0)    bandhand(4);
           if(livethree>=2 && tlivef ==0) bandhand(3);
           if(threefour==black)          liveagogo(7);
           else if(threefour==white)     liveagogo(8);

          }while((!quitf) && (winner==0));

        pressanykey();
        return;
}

int user_guide()
{
        move(8,40);
        outs("¤W:¡ô¤U:¡õ     ¥ª:¡ö¥k:¡÷");
        move(9,40);
        outs("Space:¤U¤l     q:Â÷¶}");
        move(10,40);
        outs("t:°e°T®§");
        move(11,40);
        outs("¶Â¥ý¦³¸T¤â    ­n¦hª`·N!");
        return;

}

int per_move(int net)
{
        int ch,banf=0,x;
        char genbuf[5];

        move(py,px);
        do
        {
          switch (ch)
          {
             case 't':
             case Ctrl('R'): if (currutmp->msgs[0].last_pid) {
             show_last_call_in();
             my_write(currutmp->msgs[0].last_pid, "¤ô²y¥á¦^¥h¡G");
            /* refscreen = YEA;*/
              }
            break;

            case KEY_DOWN:
             py=py+1;
             if(py>14) py=0;
            break;

            case KEY_UP:
             py=py-1;
             if(py<0) py=14;
            break;

            case KEY_LEFT:
             px=px-1;
             if(px<0) px=28;
            break;

            case KEY_RIGHT:
             px=px+1;
             if(px>28) {px=0;px=px-1;}  /*·|¸õ®æ«¨*/
            break;

            case KEY_INS:
            case KEY_DEL:
            case '\177':

             if(hand==1 || net==1) break;
             px=chess[hand][0];
             py=chess[hand][1];
             move(py,px);
             outs("¢q");
             x=px/2;
             playboard[x][py]=0;
             hand-=1;
             if(player==black)
                player=white;
             else
                player=black;
             move(2,40);
             prints("²Ä %3d ¤â",hand);
            break;

            case 'q':
            case 'Q':
             quitf=1;
             getdata(b_lines - 1, 0, "±z½T©w­nÂ÷¶}¡iÃz¯º¤­¤l´Ñ¡j¶Ü(Y/N)¡H[N] ",
                genbuf, 2, LCECHO, 0);

             if (*genbuf != 'y')
              {
              quitf=0;
              move(b_lines-1,0);
              outs("                                                    ");
              }
             else
              return 0;
            break;

            default:
            break;
           }
          move(py,px);
          x=px/2;
          if(playboard[x][py]!=0)
              banf=1;
          else
              banf=0;
        }while(((ch=igetkey())!=' ') || (banf == 1 ));
        if((px%2)==1) px=px-1; /*¸Ñ¨Mnetterm¤£¦X°ÝÃD*/
        move(py,px);
        hand+=1;
        playboard[x][py]=player;
        if(player==black)
        {
         outs("¡´");
         player=white;
        }
        else
        {
         outs("¡³");
         player=black;
        }

        chess[hand][0]=px;
        chess[hand][1]=py;
           if(hand%2==0)
            move(((hand-1)%22)/2+4,54);
           else
            move(((hand-1)%21)/2+4,40);

           prints("²Ä%2d¤â %s%c%2d",hand,
             (hand%2==1)?"¡´":"¡³",abcd[px/2],15-py);

        return;
}

int calvalue(int x1,int y1,
             int x2,int y2,
             int x3,int y3,
             int x4,int y4,
             int x5,int y5)
{
        int n_black,n_white,empty,i,j,k;

        n_black=n_white=empty=0;

        if(x1<0||x2<0||x3<0||x4<0||x5<0||
           x1>14||x2>14||x3>14||x4>14||x5>14)    return;
        if(winner!=0) return;
        if(playboard[x2][y2]==0 || playboard[x3][y3]==0
           || playboard[x4][y4]==0)
           empty=1; /*check 10111«¬¦º¥|*/

        if(playboard[x1][y1]==black) n_black+=1;
        if(playboard[x1][y1]==white) n_white+=1;
        if(playboard[x2][y2]==black) n_black+=1;
        if(playboard[x2][y2]==white) n_white+=1;
        if(playboard[x3][y3]==black) n_black+=1;
        if(playboard[x3][y3]==white) n_white+=1;
        if(playboard[x4][y4]==black) n_black+=1;
        if(playboard[x4][y4]==white) n_white+=1;
        if(playboard[x5][y5]==black) n_black+=1;
        if(playboard[x5][y5]==white) n_white+=1;

        if(playboard[x1][y1]==0 && playboard[x5][y5]==0)
         {
                if(n_white==3 || n_black==3)
                 {
                   move(15,60);
                   outs("¡¿¬¡¤T!¡¿");
                  }
                 if(n_black==3)
                  livethree+=1;
          }

        if((n_white==4 || n_black==4) && (empty ==1))
         {
              bell();
              tdeadf+=1;
              move(15,60);
              outs("¡¿¤p¤ß!¦º¥|!¡¿");
              return;
         }

        if(n_black==5)
         { /*¦A±½³s¤»*/
           tlivef=-1;
           tdeadf=0;
           livethree=0;
           for(i=0;i<=14;i++)/*¥|Áa¦V*/
            for(j=0;j<=9;j++)
             callfour(i,j,i,j+1,i,j+2,i,j+3,i,j+4,i,j+5);
           for(i=0;i<=9;i++)/*¥|¾î¦V*/
            for(j=0;j<=14;j++)
             callfour(i,j,i+1,j,i+2,j,i+3,j,i+4,j,i+5,j);
           for(i=0;i<=9;i++)/*¥|±×¥k¤U*/
            for(j=0;j<=9;j++){
             callfour(i,j,i+1,j+1,i+2,j+2,i+3,j+3,i+4,j+4,i+5,j+5);
                            /*¥|±×¥ª¤U*/
             callfour(i,j+5,i+1,j+4,i+2,j+3,i+3,j+2,i+4,j+1,i+5,j);
             }
           if(winner==0)
           {
            bell();
            move(10,35);
            outs("[31m¢z¢w¢w¢w¢w¢{[m");
            move(11,35);
            outs("[31m¢x  [30;42m¶Â³Ó[m [31m ¢x[m");
            move(12,35);
            outs("[31m¢|¢w¢w¢w¢w¢}[m");
            igetkey();
            winner=black;
           }
          }
        if(n_white==5)
         {
           bell();
           move(10,35);
           outs("[33m¢z¢w¢w¢w¢w¢{[m");
           move(11,35);
           outs("[33m¢x[m  [30;42m¥Õ³Ó[m  [33m¢x[m");
           move(12,35);
           outs("[33m¢|¢w¢w¢w¢w¢}[m");
           winner=white;
           igetkey();
          }
        return;
}

int callfour(int x1,int y1,int x2,int y2,int x3,int y3,
             int x4,int y4,int x5,int y5,int x6,int y6)
{
        int n_black,n_white,dead,i,j,k;

        n_black=n_white=dead=0;

        if(x1<0||x2<0||x3<0||x4<0||x5<0||x6<0||
           x1>14||x2>14||x3>14||x4>14||x5>14||x6>14)    return;

        if(winner!=0) return;

        if((playboard[x1][y1]!=0 && playboard[x6][y6]==0)||
           (playboard[x1][y1]==0 && playboard[x6][y6]!=0))
         dead=1; /*check ¦º¥|*/

        if(playboard[x2][y2]==black) n_black+=1;
        if(playboard[x2][y2]==white) n_white+=1;
        if(playboard[x3][y3]==black) n_black+=1;
        if(playboard[x3][y3]==white) n_white+=1;
        if(playboard[x4][y4]==black) n_black+=1;
        if(playboard[x4][y4]==white) n_white+=1;
        if(playboard[x5][y5]==black) n_black+=1;
        if(playboard[x5][y5]==white) n_white+=1;

        if(playboard[x1][y1]==0 && playboard[x6][y6]==0 &&
          (playboard[x3][y3]==0 || playboard[x4][y4]==0))
        {
          if(n_black==3 || n_white==3)
           {
             move(15,60);
             outs("¡¿¬¡¤T!¡¿");
            }
           if(n_black==3)
           livethree+=1;
         }


        if(n_black==4)
         {
           if(playboard[x1][y1]== black && playboard[x6][y6]== black)
            bandhand(6);
           if(playboard[x1][y1]!=0 && playboard[x6][y6]!=0) return;
           bell();
           if(dead)
            {
              move(15,60);
              outs("¡¿¤p¤ß¦º¥|!¡¿");
              tdeadf+=1;
              tlivef+=1;/*¶Â¦º¥|°Õ*/
              threefour=0;
              return;
            }


           threefour=black; tlivef+=1; /*¬¡¥|¤]ºâÂù¥|*/
         }
        if(n_white==4)
         {
           if(playboard[x1][y1]!=0 && playboard[x6][y6]!=0) return;
           bell();
           if(dead)
            {
              move(15,60);
              tdeadf+=1;
              outs("¡¿¤p¤ß¦º¥|!¡¿");
              threefour=0;
              return;
            }

           threefour=white; tlivef+=1;

          }
        if(playboard[x1][y1]==black) n_black+=1;/*check ³s¤l*/
        if(playboard[x6][y6]==black) n_black+=1;

        if(n_black==5 && (playboard[x3][y3]==0 || playboard[x4][y4]==0 ||
           playboard[x5][y5]==0 || playboard[x2][y2]==0))
           tlivef-=1;/*¤»¯Ê¤@«¬*/

        if(n_black>=6)   bandhand(6);
        return;
}

int bandhand(int style)
{
        bell();
        if(style==3){
            move(10,35);
            outs("[31m¢z¶Â±Ñ¢w¢w¢w¢w¢w¢w¢{[m");
            move(11,35);
            outs("[31m¢x  [37;41m¶Â¸T¤âÂù¬¡¤T[m  [31m¢x[m");
            move(12,35);
            outs("[31m¢|¢w¢w¢w¢w¢w¢w¢w¢w¢}[m");
           }
        else if(style==4){
            move(10,35);
            outs("[31m¢z¶Â±Ñ¢w¢w¢w¢w¢w¢w¢{[m");
            move(11,35);
            outs("[31m¢x  [37;41m¶Â¸T¤âÂù  ¥|[m  [31m¢x[m");
            move(12,35);
            outs("[31m¢|¢w¢w¢w¢w¢w¢w¢w¢w¢}[m");
           }
        else {
            move(10,35);
            outs("[31m¢z¶Â±Ñ¢w¢w¢w¢w¢w¢w¢{[m");
            move(11,35);
            outs("[31m¢x  [37;41m¶Â¸T¤â³s¤»¤l[m  [31m¢x[m");
            move(12,35);
            outs("[31m¢|¢w¢w¢w¢w¢w¢w¢w¢w¢}[m");
           }

            igetkey();
            winner=white;
        return;
}

int liveagogo(int sk)
{
              move(15,60);
              outs("¡¿«z«¨¬¡¥|!¡¿");        

        return;
}


char save_page_requestor[40];

int five_pk(fd,first)
int fd;
int first;
{
        int cx, ch, cy,datac,fdone,x,y;
        char genbuf[100],data[9000],xy_po[5],genbuf1[20],x1[1],y1[1],done[1];
        user_info *opponent;
        char fname[50];
        int i,j,k,fway=1,banf=1,idone=0;
        int t_win,t_loss,t_score;
        FILE *fp;

        opponent=currutmp->destuip;

        currutmp->msgs[0].last_pid=opponent->pid;
        for(i=0;i<=14;i++)
         for(j=0;j<=14;j++)
           playboard[i][j]=0;

        setutmpmode(FIVE);/*ÀÉ®×³B²z*/
        setuserfile(fname, FDATA);
        if ((fp = fopen(fname, "r")) == NULL)
         {
           setuserfile(fname, FDATA);
           fp=fopen(fname,"w");
           fprintf(fp,"%d  %d  %d",0,0,0);
           fclose(fp);
           t_win=t_loss=t_score=0;
         }
        else
         {
           fscanf(fp,"%d  %d  %d",&t_win,&t_loss,&t_score);
           fclose(fp);
         }


        hand=1;
        winner=0;
        quitf=0;
        px=14;
        py=7;
        clear();

        move(0,0);
        outs("¢z¢s¢s¢s¢s¢s¢s¢s¢s¢s¢s¢s¢s¢s¢{15
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t14
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t13
¢u¢q¢q¡Ï¢q¢q¢q¢q¢q¢q¢q¡Ï¢q¢q¢t12
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t11
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t10
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t9
¢u¢q¢q¢q¢q¢q¢q¡Ï¢q¢q¢q¢q¢q¢q¢t8
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t7
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t6
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t5
¢u¢q¢q¡Ï¢q¢q¢q¢q¢q¢q¢q¡Ï¢q¢q¢t4
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t3
¢u¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢q¢t2
¢|¢r¢r¢r¢r¢r¢r¢r¢r¢r¢r¢r¢r¢r¢}1
 A B C D E F G H I J K L M N O");

        sprintf(genbuf, "%s(%s)", cuser.userid, cuser.username);
        user_guide();
        move(0,33);
        outs("[35;43m¡»¤­¤l´Ñ¹ï¾Ô¡»[30;42m  µ{¦¡:¦¨¤j¹q¾÷88¯Å Birdman  [m");
        if(first){
         move(1,33);
         prints("¶Â¡´¥ý¤â %s  ",genbuf);
         move(2,33);
         prints("VS¥Õ¡³¤â %s  ",save_page_requestor);
        }
        else{
         move(1,33);
         prints("¶Â¡´¥ý¤â %s  ",save_page_requestor);
         move(2,33);
         prints("VS¥Õ¡³¤â %s  ",genbuf);
        }

        add_io(fd, 0);

         move(15,40);
         if(first)
          outs("¡¹µ¥«Ý¹ï¤è¤U¤l¡¹");
         else
          outs("¡»²{¦b´«¦Û¤v¤U¡»");
         move(7,14);
         outs("¡´");
         player=white;
         playboard[7][7]=black;
         chess[1][0]=14; /*¬ö¿ý©Ò¤U¦ì§}*/
         chess[1][1]=7;
         move(4,40);
         outs("²Ä 1¤â ¡´H 8");

        if(!first) /*¶W©Ç!*/
         fdone=1;
        else fdone=0;/*¹ï¤â§¹¦¨*/

        do
        {
         ch=igetkey();

         if (ch == I_OTHERDATA)
          {
           datac = recv(fd, data, sizeof(data), 0);
           if (datac <= 0){
            move(13,30);
            outs("¡i [31;47m¹ï¤è§ë­°¤F...@_@[m ¡j");
            move(14,30);
            outs("¡i [31;47m¹ï¤è§ë­°¤F...@_@[m ¡j");
            move(12,30);
            outs("¡i [31;47m¹ï¤è§ë­°¤F...@_@[m ¡j");
            break;
           }
           i=atoi(data);
           cx=i/1000;   /*¸ÑÄ¶data¦¨´Ñ½L¸ê®Æ*/
           cy=(i%1000)/10;
           fdone=i%10;
           hand+=1;

           if(hand%2==0)
            move(((hand-1)%22)/2+4,54);
           else
            move(((hand-1)%21)/2+4,40);

           prints("²Ä%2d¤â %s%c%2d",hand,
             (player==black)?"¡´":"¡³",abcd[cx/2],15-cy);


           move(cy,cx);
           x=cx/2;
           playboard[x][cy]=player;
           if(player==black)
           {
            outs("¡´");
            player=white;
            }
           else
           {
            outs("¡³");
            player=black;
            }
              move(15,60);
              outs("              ");
           tdeadf=tlivef=livethree=threefour=0;
           for(j=0;j<=10;j++)
             calvalue(cx/2,j,cx/2,j+1,cx/2,j+2,cx/2,j+3,cx/2,j+4);
           for(i=0;i<=10;i++)/*¾î¦V*/
             calvalue(i,cy,i+1,cy,i+2,cy,i+3,cy,i+4,cy);
           for(i=-4;i<=0;i++)/*±×¥k¤U*/
             calvalue(cx/2+i,cy+i,cx/2+i+1,cy+i+1,cx/2+i+2,cy+i+2,
                      cx/2+i+3,cy+i+3,cx/2+i+4,cy+i+4);
           for(i=-4;i<=0;i++)/*±×¥ª¤U*/
             calvalue(cx/2-i,cy+i,cx/2-i-1,cy+i+1,cx/2-i-2,cy+i+2,cx/2-i-3,
                      cy+i+3,cx/2-i-4,cy+i+4);

            for(j=0;j<=9;j++)
             callfour(cx/2,j,cx/2,j+1,cx/2,j+2,cx/2,j+3,cx/2,j+4,cx/2,j+5);
           for(i=0;i<=9;i++)/*¥|¾î¦V*/
             callfour(i,cy,i+1,cy,i+2,cy,i+3,cy,i+4,cy,i+5,cy);
           for(i=-5;i<=0;i++){/*¥|±×¥k¤U*/
             callfour(cx/2+i,cy+i,cx/2+i+1,cy+i+1,cx/2+i+2,cy+i+2,
                      cx/2+i+3,cy+i+3,cx/2+i+4,cy+i+4,cx/2+i+5,cy+i+5);
                            /*¥|±×¥ª¤U*/
             callfour(cx/2-i,cy+i,cx/2-i-1,cy+i+1,cx/2-i-2,cy+i+2,cx/2-i-3,
                      cy+i+3,cx/2-i-4,cy+i+4,cx/2-i-5,cy+i+5);
             }

           if(tlivef>=2 && winner==0)    bandhand(4);
           if(livethree>=2 && tlivef ==0) bandhand(3);
           if(threefour==black)          liveagogo(7);/*§PÂ_¬¡¥|­n¤£­nª½±µÄ¹*/
           else if(threefour==white)     liveagogo(8);
          }
         else{
          if (ch == Ctrl('X')) {
                winner=1;
                genbuf1[0] = (char) ch;
                send(fd, genbuf1, -3, 0);
                 }
          if (ch =='t'){
              extern screenline* big_picture;
              screenline* screen0 = calloc(t_lines, sizeof(screenline));
              memcpy(screen0, big_picture, t_lines * sizeof(screenline));    
                add_io(0, 0);
                my_write(opponent->pid,"¿é¤J°T®§:");
                add_io( fd, 0);
              memcpy(big_picture, screen0, t_lines * sizeof(screenline));
              free(screen0);
              redoscr();          
                clrtoeol();
                continue;
          }
         }

         if(fdone==1)/*´«§Ú*/
         {

              move(15,40);
              outs("¡»²{¦b´«¦Û¤v¤U¡»");

           if(winner!=0) break;

           move(py,px);
          switch (ch)
          {

            case KEY_DOWN:
             py=py+1;
             if(py>14) py=0;
            break;

            case KEY_UP:
             py=py-1;
             if(py<0) py=14;
            break;

            case KEY_LEFT:
             px=px-1;
             if(px<0) px=28;
            break;

            case KEY_RIGHT:
             px=px+1;
             if(px>28) {px=0;px=px-1;}  /*·|¸õ®æ«¨*/
            break;

            case 'q':
            case 'Q':
             quitf=1;
             getdata(b_lines - 1, 0, "±z½T©w­nÂ÷¶}¶Ü¡H(¨S¤U§¹¶]±¼«Ü¨SÂ§»ª³á!!!)(Y/N)?[N] ",
                genbuf, 2, LCECHO, 0);

             if (*genbuf != 'y')
              {
              quitf=0;
              move(b_lines-1,0);
              outs("                                                    ");
              }
             else{
              quitf=1;
                genbuf1[0] = (char) ch;
                send(fd, genbuf1, -3, 0);
                }
            break;

            case ' ':
                if(banf==1) break;

                if((px%2)==1) px=px-1; /*¸Ñ¨Mnetterm¤£¦X°ÝÃD*/
                move(py,px);
                hand+=1;
                playboard[x][py]=player;
                if(player==black)
                 {
                  outs("¡´");
                  player=white;
                 }
                else
                {
                 outs("¡³");
                 player=black;
                }
                chess[hand][0]=px;
                chess[hand][1]=py;
           if(hand%2==0)
            move(((hand-1)%22)/2+4,54);
           else
            move(((hand-1)%21)/2+4,40);

           prints("²Ä%2d¤â %s%c%2d",hand,
             (hand%2==1)?"¡´":"¡³",abcd[px/2],15-py);
             idone=1;
            break;

            default:
            break;
           }
        move(py,px);
          x=px/2;
          if(playboard[x][py]!=0)
              banf=1;
          else
              banf=0;

        if(idone==1){
           switch(px){
                case 0:
                 xy_po[0]='0';
                 xy_po[1]='0';
                break;
                case 2:
                 xy_po[0]='0';
                 xy_po[1]='2';
                break;
                case 4:
                 xy_po[0]='0';
                 xy_po[1]='4';
                break;
                case 6:
                 xy_po[0]='0';
                 xy_po[1]='6';
                break;
                case 8:
                 xy_po[0]='0';
                 xy_po[1]='8';
                break;
                case 10:
                 xy_po[0]='1';
                 xy_po[1]='0';
                break;
                case 12:
                 xy_po[0]='1';
                 xy_po[1]='2';
                break;
                case 14:
                 xy_po[0]='1';
                 xy_po[1]='4';
                break;
                case 16:
                 xy_po[0]='1';
                 xy_po[1]='6';
                break;
                case 18:
                 xy_po[0]='1';
                 xy_po[1]='8';
                break;
                case 20:
                 xy_po[0]='2';
                 xy_po[1]='0';
                break;
                case 22:
                 xy_po[0]='2';
                 xy_po[1]='2';
                break;
                case 24:
                 xy_po[0]='2';
                 xy_po[1]='4';
                break;
                case 26:
                 xy_po[0]='2';
                 xy_po[1]='6';
                break;
                case 28:
                 xy_po[0]='2';
                 xy_po[1]='8';
                break;
               }
           switch(py){
                case 0:
                 xy_po[2]='0';
                 xy_po[3]='0';
                break;
                case 1:
                 xy_po[2]='0';
                 xy_po[3]='1';
                break;
                case 2:
                 xy_po[2]='0';
                 xy_po[3]='2';
                break;
                case 3:
                 xy_po[2]='0';
                 xy_po[3]='3';
                break;
                case 4:
                 xy_po[2]='0';
                 xy_po[3]='4';
                break;
                case 5:
                 xy_po[2]='0';
                 xy_po[3]='5';
                break;
                case 6:
                 xy_po[2]='0';
                 xy_po[3]='6';
                break;
                case 7:
                 xy_po[2]='0';
                 xy_po[3]='7';
                break;
                case 8:
                 xy_po[2]='0';
                 xy_po[3]='8';
                break;
                case 9:
                 xy_po[2]='0';
                 xy_po[3]='9';
                break;
                case 10:
                 xy_po[2]='1';
                 xy_po[3]='0';
                break;
                case 11:
                 xy_po[2]='1';
                 xy_po[3]='1';
                break;
                case 12:
                 xy_po[2]='1';
                 xy_po[3]='2';
                break;
                case 13:
                 xy_po[2]='1';
                 xy_po[3]='3';
                break;
                case 14:
                 xy_po[2]='1';
                 xy_po[3]='4';
                break;
               }
              fdone=0;
              xy_po[4]='1';
              if(send(fd,xy_po,strlen(xy_po),0)==-1)
                break;

              move(15,40);
              outs("¡¹µ¥«Ý¹ï¤è¤U¤l¡¹");
              f_display();

              move(15,60);
              outs("              ");

           tdeadf=tlivef=livethree=threefour=0;
            for(j=0;j<=10;j++)
             calvalue(px/2,j,px/2,j+1,px/2,j+2,px/2,j+3,px/2,j+4);
           for(i=0;i<=10;i++)/*¾î¦V*/
             calvalue(i,py,i+1,py,i+2,py,i+3,py,i+4,py);
           for(i=-4;i<=0;i++)/*±×¥k¤U*/
             calvalue(px/2+i,py+i,px/2+i+1,py+i+1,px/2+i+2,py+i+2,
                      px/2+i+3,py+i+3,px/2+i+4,py+i+4);
           for(i=-4;i<=0;i++)/*±×¥ª¤U*/
             calvalue(px/2-i,py+i,px/2-i-1,py+i+1,px/2-i-2,py+i+2,px/2-i-3,
                      py+i+3,px/2-i-4,py+i+4);

            for(j=0;j<=9;j++)
             callfour(px/2,j,px/2,j+1,px/2,j+2,px/2,j+3,px/2,j+4,px/2,j+5);
           for(i=0;i<=9;i++)/*¥|¾î¦V*/
             callfour(i,py,i+1,py,i+2,py,i+3,py,i+4,py,i+5,py);
           for(i=-5;i<=0;i++){/*¥|±×¥k¤U*/
             callfour(px/2+i,py+i,px/2+i+1,py+i+1,px/2+i+2,py+i+2,
                      px/2+i+3,py+i+3,px/2+i+4,py+i+4,px/2+i+5,py+i+5);
                            /*¥|±×¥ª¤U*/
             callfour(px/2-i,py+i,px/2-i-1,py+i+1,px/2-i-2,py+i+2,px/2-i-3,
                      py+i+3,px/2-i-4,py+i+4,px/2-i-5,py+i+5);
             }

           if(tlivef>=2 && winner==0)    bandhand(4);
           if(livethree>=2 && tlivef ==0) bandhand(3);
           if(threefour==black)          liveagogo(7);/*§PÂ_¬¡¥|­n¤£­nª½±µÄ¹*/
           else if(threefour==white)     liveagogo(8);

            }
           if(winner!=0){
           genbuf1[0] = (char) ch;
           if (send(fd, genbuf1, 1, 0) != 1)
              break; }
           idone=0;
         }
        }while((!quitf) && (winner==0));


   if(winner!=0 && quitf==0)
    {
        if(first && winner==black)
         {t_win+=1;t_score+=5;}
        else if( first && winner==white)
         {t_loss+=1;t_score+=1;}
        else if( !first && winner==black)
         {t_loss+=1;t_score+=1;}
        else if( !first && winner==white)
         {t_win+=1;t_score+=7;}
    }


   if ((fp = fopen(fname, "w")) == NULL)
     return;
    else{
     fprintf(fp,"%d  %d  %d",t_win,t_loss,t_score);
     fclose(fp);
     }

   quitf=0;
   add_io(0, 0);
   close(fd);
   pressanykey();
   return;
}
#define MAX_REVIEW 6
int
f_display()
{
  char buf[MAX_REVIEW][100],line=0,i,genbuf[100],x=1;
  FILE *fp;
  setuserfile(genbuf, fn_writelog);
  for(i=0;i<MAX_REVIEW;i++) buf[i][0]=0;
  if(fp=fopen(genbuf,"r"))
        {
         while(fgets(buf[line],99,fp))
               {
                        line = (line +1)%MAX_REVIEW;
               }
         line += MAX_REVIEW;
         move(16,0);
        outs(
"[33m¢w¢w¢w¢w¢w¢w¢w°T®§¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w[m");
         for(i=1;i<=MAX_REVIEW; i++)
          {
            move(i+16,0);
            clrtoeol();
            if(!buf[(line-i)%MAX_REVIEW][0]) break;
            outs(buf[(line-i)%MAX_REVIEW]);
          }
/*          move(i+1,0);
          outs(
"¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w"
*/          fclose(fp);
          return FULLUPDATE;
        }
  return DONOTHING;
}



