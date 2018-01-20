// conio.c written by Magi.bbs@tsunami.ml.org
//
// for porting my five chess from borland c to unix
//
// Date: 98/3/18

#include <termios.h>
static int bgcolor=30;
static int high=0;

void cputs(char *buf)
{
   printf("%s",buf);
}

void textcolor(int color)
{
   printf("\x1b[1;%d;%dm",bgcolor,color);
}

void textbackground(int color)
{
   bgcolor=color;
   printf("\x1b[%dm",color+10);
}  

void gotoxy(int x,int y)
{
   printf("\x1b[%d;%dH",y,x);
}

void clrscr()
{
   printf("\x1b[2J");
}

char readkey()
{
   char ch;
/*   read(0,&ch,1); */
   ch=getchar();
   return ch;
}   

struct termios termsave;

void initconio()
{
   struct termios term;
   
   tcgetattr(0,&termsave);
   term=termsave;
   term.c_lflag &=~(ECHO | ICANON);
   term.c_cc[VMIN]=1;
   term.c_cc[VTIME]=0;
   tcsetattr(0,TCSAFLUSH,&term); 
}   

void endconio()
{
   tcsetattr(0,TCSAFLUSH,&termsave);
}

void highv()
{
   high=1;
}

void lowv()
{
  high=0;
}
