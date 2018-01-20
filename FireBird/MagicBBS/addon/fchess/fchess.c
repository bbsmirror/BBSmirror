#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include "fchess.h"
#include "conio.c"

#define UP    'A'
#define DOWN  'B'
#define LEFT  'D'
#define RIGHT 'C'
#define ENTER 10
#define SPACE 32
#define True  1
#define False 0

void clchess(int ix,int iy);
void moveo(void);
void movec(void);
void initchess(void);
int checkwin(char);
int check4(char);
int check3(char);
int check2(char);
int checkf(char);
void swaphelp(void);
void dispwin(void);
char chess[19][19];
char flag=BLACK;
unsigned char ch,ix=0,iy=0;
int is_one=True;
void think(void);
void showboard();


char main(void)
 {
 
	 srand(30321);
	 initconio();
	 clrscr();
	 printf("\n(1) ©M¹q¸£¤U  (2) ¦Û¤vª±\n");
	 ch=readkey();
	 if (ch=='2')
		 {is_one=False;}
	 initchess();

	 while ((ch = readkey()) != 'Q' && ch != 'q')
	  {
	        lowv();
	        textbackground(BLUE);
		  switch (ch)
			{
			case UP:
				if (iy > 0)
				{
				  if (chess[ix][iy-1]!=1)
				  {
				   if (chess[ix][iy]==1) clchess(ix,iy);
				  else {textcolor(chess[ix][iy]);gotoxy(ix*2+1,iy+1);cputs("¡´");}
										iy--; moveo();
										break;
									  }
								  if (chess[ix][iy]==1) clchess(ix,iy);
									 else {textcolor(chess[ix][iy]);gotoxy(ix*2+1,iy+1);cputs("¡´");}
								iy--;movec();
								}
								break;
			case DOWN:
								if (iy < 18)
								{
								  if (chess[ix][iy+1]!=1)
									  {
									  if (chess[ix][iy]==1)clchess(ix,iy);
										 else {textcolor(chess[ix][iy]);gotoxy(ix*2+1,iy+1);cputs("¡´");}
									  iy++;moveo();
									  break;
									  }
								if (chess[ix][iy]==1) clchess(ix,iy);
									 else {textcolor(chess[ix][iy]);gotoxy(ix*2+1,iy+1);cputs("¡´");}
								iy++;movec();
								}
								break;
			case LEFT:
								if (ix > 0)
								{
								  if (chess[ix-1][iy]!=1)
												 {
								  if (chess[ix][iy]==1) clchess(ix,iy);
									 else {textcolor(chess[ix][iy]);gotoxy(ix*2+1,iy+1);cputs("¡´");}
												 ix--;moveo();
												 break;
												 }
								if (chess[ix][iy]==1) clchess(ix,iy);
									 else {textcolor(chess[ix][iy]);gotoxy(ix*2+1,iy+1);cputs("¡´");}
								ix--;movec();
								}
								break;
			case RIGHT:
								if (ix < 18)
								{
								  if (chess[ix+1][iy]!=1)
												 {
								  if (chess[ix][iy]==1) clchess(ix,iy);
									 else {textcolor(chess[ix][iy]);gotoxy(ix*2+1,iy+1);cputs("¡´");}
												 ix++;moveo();
												 break;
												 }
								if (chess[ix][iy]==1) clchess(ix,iy);
									 else {textcolor(chess[ix][iy]);gotoxy(ix*2+1,iy+1);cputs("¡´");}
								ix++;movec();
								}
								break;
			case 'R':
			case 'r':
									 initchess();
									 flag=BLACK;
									 ix=0;
									 iy=0;
						break;
			case ENTER:
			case SPACE:
				if (!is_one)
				  if (chess[ix][iy]==1)
					  {
								chess[ix][iy]=flag;
								swaphelp();
								textcolor(flag);
								textbackground(BLUE);
								gotoxy(ix*2+1,iy+1);
								cputs("¡´");
								if (checkwin(flag))
									{
									 dispwin();
									 initchess();
									 flag=BLACK;
									 ix=0;
									 iy=0;
									  break;
									}
								flag = (flag==WHITE) ? BLACK : WHITE;
					  }
					else
					  {
					  }
			  else
				 { if (chess[ix][iy]==1)
					  {
								chess[ix][iy]=flag;
								swaphelp();
								textcolor(flag);
								textbackground(BLUE);
								gotoxy(ix*2+1,iy+1);
								cputs("¡´");
								if (checkwin(flag))
									{
									 dispwin();
									 initchess();
									 flag=BLACK;
									 ix=0;
									 iy=0;
									  break;
									}
								flag = (flag==WHITE) ? BLACK : WHITE;
								think();
								chess[ix][iy]=flag;
								swaphelp();
								textcolor(flag);
								textbackground(BLUE);
								gotoxy(ix*2+1,iy+1);
								cputs("¡´");
								if (checkwin(flag))
									{
									 dispwin();
									 initchess();
									 flag=BLACK;
									 ix=0;
									 iy=0;
									  break;
									}
								flag = (flag==WHITE) ? BLACK : WHITE;
					  }
					else
					  {
					  }       }

					break;

			}
	  }
	  textcolor(WHITE);
	  textbackground(BLACK);
	  clrscr();
	  puts("FiveChess V2.00 Copyright by James Hsiao 1996.");
	  puts("¤­¤l´Ñ¹CÀ¸  ª©¥»¡G2.00¯  §¹¦¨¤é´Á:02/24/96");
	  puts("ÁÂÁÂ±z¨Ï¥Î¥»µ{¦¡¡I");
	  endconio();
	  return(1);
 }

void clchess(register ix,register iy)
{
        highv();
	if (ix==0 && iy ==0)
		{
		 gotoxy(1,1);
		 textcolor(YELLOW);
		 textbackground(BLUE);
		 cputs("ùÝ");
		}
	else if (ix==0 && iy ==18)
		{
		 gotoxy(1,19);
		 textcolor(YELLOW);
		 textbackground(BLUE);
		 cputs("ùã");
		}
	else if (ix==18 && iy ==0)
		{
		 gotoxy(37,1);
		 textcolor(YELLOW);
		 textbackground(BLUE);
		 cputs("ùß");
		}
	else if (ix==18 && iy ==18)
		{
		 gotoxy(37,19);
		 textcolor(YELLOW);
		 textbackground(BLUE);
		 cputs("ùå");
		}
	else if (ix == 0 && iy > 0 && iy < 18)
		{
		 gotoxy(ix*2+1,iy+1);
		 textcolor(YELLOW);
		 textbackground(BLUE);
		 cputs("ùò");
		}
	else if (ix == 18 && iy > 0 && iy < 18)
		{
		 gotoxy(ix*2+1,iy+1);
		 textcolor(YELLOW);
		 textbackground(BLUE);
		 cputs("ùô");
		}
	else if (iy == 0 && ix > 0 && ix < 18)
		{
		 gotoxy(ix*2+1,iy+1);
		 textcolor(YELLOW);
		 textbackground(BLUE);
		 cputs("ùç");
		}
	else if (iy == 18 && ix > 0 && ix < 18)
		{
		 gotoxy(ix*2+1,iy+1);
		 textcolor(YELLOW);
		 textbackground(BLUE);
		 cputs("ùí");
		}
	else
		{
		 gotoxy(ix*2+1,iy+1);
		 textcolor(WHITE);
		 textbackground(BLUE);
		 cputs("¢q");
		}
}

void initchess(void)
{
  register x,y;
  
  clrscr();
  showboard();
  
  for (x=0;x<=18;x++)
		for (y=0;y<=18;y++)
			{  chess[x][y] = 1;
			   clchess(x,y); }
}

int checkwin(char who)
{
  register x,y;
  for (x=0;x<=14;x++)
		for (y=0;y<=14;y++)
				 if((who==chess[x][y]
				  && who==chess[x+1][y]
				  && who==chess[x+2][y]
				  && who==chess[x+3][y]
				  && who==chess[x+4][y])
								 ||
					 (who==chess[x][y]
				  && who==chess[x][y+1]
				  && who==chess[x][y+2]
				  && who==chess[x][y+3]
				  && who==chess[x][y+4])
								 ||
					 (who==chess[x][y]
				  && who==chess[x+1][y+1]
				  && who==chess[x+2][y+2]
				  && who==chess[x+3][y+3]
				  && who==chess[x+4][y+4])
				  )
					return (1);
  for (y=0;y<=14;y++)
	for (x=15;x<=18;x++)
				 if((who==chess[x][y]
				  && who==chess[x][y+1]
				  && who==chess[x][y+2]
				  && who==chess[x][y+3]
				  && who==chess[x][y+4])
				  )
					return (1);
  for (x=0;x<=14;x++)
	for (y=15;y<=18;y++)
				 if((who==chess[x][y]
				  && who==chess[x+1][y]
				  && who==chess[x+2][y]
				  && who==chess[x+3][y]
				  && who==chess[x+4][y])
				  )
					return (1);
  for (x=4;x<=18;x++)
	for (y=0;y<=14;y++)
				 if((who==chess[x][y]
				  && who==chess[x-1][y+1]
				  && who==chess[x-2][y+2]
				  && who==chess[x-3][y+3]
				  && who==chess[x-4][y+4])
				  )
					return (1);

  return (0);
}

void swaphelp(void)
{
  if (flag!=BLACK)
	  {
		gotoxy(9,21);
		cputs("¶Â¤è");
	  }
  else
	  {
		gotoxy(9,21);
		cputs("¥Õ¤è");
	  }
}

void dispwin(void)
{
	 gotoxy(23,20);
  if (flag==BLACK)
	  {
		textcolor(BLACK);
		textbackground(CYAN);
		gotoxy(1,21);
		cputs("¶Â¤è³Ó§Q¡I¥ôÀ£¤@ÁäÄ~Äò¡I");
		readkey();
	  }
  else
	  {
		textcolor(WHITE);
		textbackground(CYAN);
		gotoxy(1,21);
		cputs("¥Õ¤è³Ó§Q¡I¥ôÀ£¤@ÁäÄ~Äò¡I");
		readkey();
	  }
}

void moveo(void)
{
				textcolor(chess[ix][iy]);
				gotoxy(ix*2+1,iy+1);
				cputs("¡ò");
}

void movec(void)
{
                                textcolor(LIGHT);
                                textcolor(GREEN);
				textbackground(BLUE);
				gotoxy(ix*2+1,iy+1);
				cputs("¡ò");
}

void think(void)
{
  char manc;
  register x,y;
  char chessbak[19][19];
  ix=20;
  iy=20;
  manc = (flag==WHITE) ? BLACK : WHITE;

  for (x=0;x<=18;x++)
	 for (y=0;y<=18;y++)
	  chessbak[x][y]=chess[x][y];
  for (x=0;x<=18;x++)
		for (y=0;y<=18;y++)
			 if (chess[x][y]==1)
			  { chess[x][y]=flag;
				 if (checkwin(flag))
					 {ix=x;iy=y;goto ok;} else {chess[x][y]=1;}}
if (ix==20)
  for (x=0;x<=18;x++)
		for (y=0;y<=18;y++)
			 if (chess[x][y]==1)
			  { chess[x][y]=manc;
				 if (checkwin(manc))
					 {ix=x;iy=y;goto ok;} else {chess[x][y]=1;}}
if (ix==20)
  for (x=0;x<=18;x++)
		for (y=0;y<=18;y++)
			 if (chess[x][y]==1)
			  { chess[x][y]=flag;
				 if (check4(flag))
					 {ix=x;iy=y;goto ok;} else {chess[x][y]=1;}}

if (ix==20)
  for (x=0;x<=18;x++)
		for (y=0;y<=18;y++)
			 if (chess[x][y]==1)
			 {chess[x][y]=manc;
				if (check4(manc))
					{ix=x;iy=y;goto ok;} else {chess[x][y]=1;}}
if (ix==20)
  for (x=0;x<=18;x++)
		for (y=0;y<=18;y++)
			 if (chess[x][y]==1)
			 {chess[x][y]=flag;
				if (checkf(flag))
					{ix=x;iy=y;goto ok;} else {chess[x][y]=1;}}

if (ix==20)
  for (x=0;x<=18;x++)
		for (y=0;y<=18;y++)
			 if (chess[x][y]==1)
			 {chess[x][y]=flag;
				if (check3(flag))
					{ix=x;iy=y;goto ok;} else {chess[x][y]=1;}}

if (ix==20)
  for (x=0;x<=18;x++)
		for (y=0;y<=18;y++)
			 if (chess[x][y]==1)
			 {chess[x][y]=manc;
				if (check3(manc))
					{ix=x;iy=y;goto ok;} else {chess[x][y]=1;}}
if (ix==20)
  for (x=0;x<=18;x++)
		for (y=0;y<=18;y++)
			 if (chess[x][y]==1)
			 {chess[x][y]=flag;
				if (check2(flag))
					{ix=x;iy=y;goto ok;} else {chess[x][y]=1;}}
if (ix==20)
  for (x=0;x<=18;x++)
		for (y=0;y<=18;y++)
			 if (chess[x][y]==1)
			 {chess[x][y]=manc;
				if (check2(manc))
					{ix=x;iy=y;goto ok;} else {chess[x][y]=1;}}

if (ix==20)
{
loop:
ix=random() % 18;
iy=random() % 18;
 if (chessbak[ix][iy]!=1)
	 goto loop;
}
ok:
  for (x=0;x<=18;x++)
	 for (y=0;y<=18;y++)
	  chess[x][y]=chessbak[x][y];
}
int check4(char who)
{
  register x,y;
  for (x=0;x<=13;x++)
		for (y=0;y<=13;y++)
			  { if(chess[x][y]==1)
					 if(chess[x+1][y]==who)
					 if(chess[x+2][y]==who)
					 if(chess[x+3][y]==who)
					 if(chess[x+4][y]==who)
					 if(chess[x+5][y]==1)
							return (1);
				 if(chess[x][y]==1)
					 if(chess[x][y+1]==who)
					 if(chess[x][y+2]==who)
					 if(chess[x][y+3]==who)
					 if(chess[x][y+4]==who)
					 if(chess[x][y+5]==1)
							return (1);
				 if(chess[x][y]==1)
					 if(chess[x+1][y+1]==who)
					 if(chess[x+2][y+2]==who)
					 if(chess[x+3][y+3]==who)
					 if(chess[x+4][y+4]==who)
					 if(chess[x+5][y+5]==1)
							return (1);}

  for (y=0;y<=13;y++)
	for (x=14;x<=18;x++)
				 if(chess[x][y]==1)
					 if(chess[x][y+1]==who)
					 if(chess[x][y+2]==who)
					 if(chess[x][y+3]==who)
					 if(chess[x][y+4]==who)
					 if(chess[x][y+5]==1)
							return (1);

  for (x=0;x<=13;x++)
	for (y=14;y<=18;y++)
				 if(chess[x][y]==1)
					 if(chess[x+1][y]==who)
					 if(chess[x+2][y]==who)
					 if(chess[x+3][y]==who)
					 if(chess[x+4][y]==who)
					 if(chess[x+5][y]==1)
					return (1);

  for (x=5;x<=18;x++)
	for (y=0;y<=13;y++)
				 if(chess[x][y]==1)
				  if(who==chess[x-1][y+1])
				  if(who==chess[x-2][y+2])
				  if(who==chess[x-3][y+3])
				  if(who==chess[x-4][y+4])
				  if(chess[x-5][y+5]==1)
					return (1);

  return (0);
}
int check3(char who)
{
  register x,y;
  for (x=0;x<=14;x++)
		for (y=0;y<=14;y++)
			  { if(chess[x][y]==1)
					 if(chess[x+1][y]==who)
					 if(chess[x+2][y]==who)
					 if(chess[x+3][y]==who)
					 if(chess[x+4][y]==1)
							return (1);
				 if(chess[x][y]==1)
					 if(chess[x][y+1]==who)
					 if(chess[x][y+2]==who)
					 if(chess[x][y+3]==who)
					 if(chess[x][y+4]==1)
							return (1);
				 if(chess[x][y]==1)
					 if(chess[x+1][y+1]==who)
					 if(chess[x+2][y+2]==who)
					 if(chess[x+3][y+3]==who)
					 if(chess[x+4][y+4]==1)
							return (1);}

  for (y=0;y<=14;y++)
	for (x=15;x<=18;x++)
				 if(chess[x][y]==1)
					 if(chess[x][y+1]==who)
					 if(chess[x][y+2]==who)
					 if(chess[x][y+3]==who)
					 if(chess[x][y+4]==1)
							return (1);

  for (x=0;x<=14;x++)
	for (y=15;y<=18;y++)
				 if(chess[x][y]==1)
					 if(chess[x+1][y]==who)
					 if(chess[x+2][y]==who)
					 if(chess[x+3][y]==who)
					 if(chess[x+4][y]==1)
					return (1);

  for (x=4;x<=18;x++)
	for (y=0;y<=14;y++)
				 if(chess[x][y]==1)
				  if(who==chess[x-1][y+1])
				  if(who==chess[x-2][y+2])
				  if(who==chess[x-3][y+3])
				  if(chess[x-4][y+4]==1)
					return (1);

  return (0);
}

int check2(char who)
{
  register x,y;
  for (x=0;x<=15;x++)
		for (y=0;y<=15;y++)
			  { if(chess[x][y]==1)
					 if(chess[x+1][y]==who)
					 if(chess[x+2][y]==who)
					 if(chess[x+3][y]==1)
							return (1);
				 if(chess[x][y]==1)
					 if(chess[x][y+1]==who)
					 if(chess[x][y+2]==who)
					 if(chess[x][y+3]==1)
							return (1);
				 if(chess[x][y]==1)
					 if(chess[x+1][y+1]==who)
					 if(chess[x+2][y+2]==who)
					 if(chess[x+3][y+3]==1)
							return (1);}

  for (y=0;y<=15;y++)
	for (x=16;x<=18;x++)
				 if(chess[x][y]==1)
					 if(chess[x][y+1]==who)
					 if(chess[x][y+2]==who)
					 if(chess[x][y+3]==1)
							return (1);

  for (x=0;x<=15;x++)
	for (y=16;y<=18;y++)
				 if(chess[x][y]==1)
					 if(chess[x+1][y]==who)
					 if(chess[x+2][y]==who)
					 if(chess[x+3][y]==1)
					return (1);

  for (x=3;x<=18;x++)
	for (y=0;y<=15;y++)
				 if(chess[x][y]==1)
				  if(who==chess[x-1][y+1])
				  if(who==chess[x-2][y+2])
				  if(chess[x-3][y+3]==1)
					return (1);

  return (0);
}

int checkf(char who)
{
  register x,y;
  for (x=0;x<=14;x++)
		for (y=0;y<=14;y++)
				 if((who*4+1==chess[x][y]+ chess[x+1][y] + chess[x+2][y]
				  + chess[x+3][y]+ chess[x+4][y])
								 ||
					 (who*4+1==chess[x][y]+chess[x][y+1]+chess[x][y+2]
					 +chess[x][y+3]+chess[x][y+4])
								 ||
					 (who*4+1==chess[x][y]+chess[x+1][y+1]+chess[x+2][y+2]
					  +chess[x+3][y+3]+chess[x+4][y+4]))
					return (1);
  for (y=0;y<=14;y++)
	for (x=15;x<=18;x++)
				 if((who*4+1==chess[x][y]
				  +chess[x][y+1]
				  +chess[x][y+2]
				  +chess[x][y+3]
				  +chess[x][y+4])
				  )
					return (1);
  for (x=0;x<=14;x++)
	for (y=15;y<=18;y++)
				 if((who*4+1==chess[x][y]
				  +chess[x+1][y]
				  +chess[x+2][y]
				  +chess[x+3][y]
				  +chess[x+4][y])
				  )
					return (1);
  for (x=4;x<=18;x++)
	for (y=0;y<=14;y++)
				 if((who*4+1==chess[x][y]
				  +chess[x-1][y+1]
				  +chess[x-2][y+2]
				  +chess[x-3][y+3]
				  +chess[x-4][y+4])
				  )
					return (1);

  return (0);
}

void showboard()
{
   FILE *fp;
   char buf[255];
   if(!(fp=fopen("fchess.ans","r")))
      {  printf("Error opening fchess.ans\n");
         exit(-1);
      }
   while(fgets(buf,255,fp)!=NULL)
       printf("%s",buf);
}
