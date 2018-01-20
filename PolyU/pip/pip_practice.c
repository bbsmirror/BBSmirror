/*---------------------------------------------------------------------------*/
/* 修行選單:念書 練武 修行                                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
#include <time.h>
#include "bbs.h"
#include "pip.h"
extern struct chicken d;
extern time_t start_time;
extern time_t lasttime;
#define getdata(a, b, c , d, e, f, g) getdata(a,b,c,d,e,f,NULL,g)

/*---------------------------------------------------------------------------*/
/* 修行選單:念書 練武 修行                                                   */
/* 資料庫                                                                    */
/*---------------------------------------------------------------------------*/
char *classrank[6]={"沒有","初級","中級","高級","進階","專業"};
int classmoney[11][2]={{ 0,  0},
		       {60,110},{70,120},{70,120},{80,130},{70,120},
		       {60,110},{90,140},{70,120},{70,120},{80,130}};		     
int classvariable[11][4]={
{0,0,0,0},
{5,5,4,4},{5,7,6,4},{5,7,6,4},{5,6,5,4},{7,5,4,6},
{7,5,4,6},{6,5,4,6},{6,6,5,4},{5,5,4,7},{7,5,4,7}};


char *classword[11][5]=
{
{"課名","成功\一","成功\二","失敗一","失敗二"},
 
{"自然科學","正在用功\讀書中..","我是聰明雞 cccc...",
            "這題怎麼看不懂咧..怪了","唸不完了 :~~~~~~"},
            
{"唐詩宋詞","床前明月光...疑是地上霜...","紅豆生南國..春來發幾枝..",
            "ㄟ..上課不要流口水","你還混喔..罰你背會唐詩三百首"},

{"神學教育","哈雷路亞  哈雷路亞","讓我們迎接天堂之門",
	    "ㄟ..你在幹嘛ㄚ? 還不好好唸","神學很嚴肅的..請好好學..:("},

{"軍學教育","孫子兵法是中國兵法書..","從軍報國，我要帶兵去打仗",
	    "什麼陣形ㄚ?混亂陣形?? @_@","你還以為你在玩三國志ㄚ?"},

{"劍道技術","看我的厲害  獨孤九劍....","我刺 我刺 我刺刺刺..",
	    "劍要拿穩一點啦..","你在刺地鼠ㄚ? 劍拿高一點"},

{"格鬥戰技","肌肉是肌肉  呼呼..","十八銅人行氣散..",
	    "腳再踢高一點啦...","拳頭怎麼這麼沒力ㄚ.."},

{"魔法教育","我變 我變 我變變變..","蛇膽+蟋蜴尾+鼠牙+蟾蜍=??",
	    "小心你的掃帚啦  不要亂揮..","ㄟ～口水不要流到水晶球上.."},

{"禮儀教育","要當隻有禮貌的雞...","歐嗨唷..ㄚ哩ㄚ豆..",
	    "怎麼學不會ㄚ??天呀..","走起路來沒走樣..天ㄚ.."},

{"繪畫技巧","很不錯唷..有美術天份..","這幅畫的顏色搭配的很好..",
	    "不要鬼畫符啦..要加油..","不要咬畫筆啦..壞壞小雞喔.."},

{"舞蹈技巧","你就像一隻天鵝喔..","舞蹈細胞很好喔..",
            "身體再柔軟一點..","拜託你優美一點..不要這麼粗魯.."}};
/*---------------------------------------------------------------------------*/
/* 修行選單:念書 練武 修行                                                   */
/* 函式庫                                                                    */
/*---------------------------------------------------------------------------*/

int pip_practice_classA()
{
/*  ├────┼──────────────────────┤*/
/*  │自然科學│智力 + 1~ 4 , 信仰 - 0~0 , 抗魔能力 - 0~0   │*/
/*  │        ├──────────────────────┤*/
/*  │        │智力 + 2~ 6 , 信仰 - 0~1 , 抗魔能力 - 0~1   │*/
/*  │        ├──────────────────────┤*/
/*  │        │智力 + 3~ 8 , 信仰 - 0~2 , 抗魔能力 - 0~1   │*/
/*  │        ├──────────────────────┤*/
/*  │        │智力 + 4~12 , 信仰 - 1~3 , 抗魔能力 - 0~1   │*/
/*  ├────┼──────────────────────┤*/
	int body,class;
	int change1,change2,change3,change4,change5;
	char inbuf[256];
     
	class=d.wisdom/200+1; /*科學*/
	if(class>5) class=5;

	body=pip_practice_function(1,class,11,12,&change1,&change2,&change3,&change4,&change5);
	if(body==0) return 0;      
	d.wisdom+=change4;
	if(body==1)
	{ 
		d.belief-=rand()%(2+class*2);
		d.mresist-=rand()%4;
	}
	else
	{
		d.belief-=rand()%(2+class*2);
		d.mresist-=rand()%3;      
	}
	pip_practice_gradeup(1,class,d.wisdom/200+1);
	if(d.belief<0)  d.belief=0;
	if(d.mresist<0) d.mresist=0;
	d.classA+=1;
	return 0;
}   

int pip_practice_classB()
{
/*  ├────┼──────────────────────┤*/
/*  │詩詞    │感受 + 1~1 , 智力 + 0~1 , 藝術修養 + 0~1    │*/
/*  │        │氣質 + 0~1                                  │*/
/*  │        ├──────────────────────┤*/
/*  │        │感受 + 1~2 , 智力 + 0~2 , 藝術修養 + 0~1    │*/
/*  │        │氣質 + 0~1                                  │*/
/*  │        ├──────────────────────┤*/
/*  │        │感受 + 1~4 , 智力 + 0~3 , 藝術修養 + 0~1    │*/
/*  │        │氣質 + 0~1                                  │*/
/*  │        ├──────────────────────┤*/
/*  │        │感受 + 2~5 , 智力 + 0~4 , 藝術修養 + 0~1    │*/
/*  │        │氣質 + 0~1                                  │*/
/*  ├────┼──────────────────────┤*/
	int body,class;
	int change1,change2,change3,change4,change5;
	char inbuf[256];
     
	class=(d.affect*2+d.wisdom+d.art*2+d.character)/400+1; /*詩詞*/
	if(class>5) class=5;
     
	body=pip_practice_function(2,class,21,21,&change1,&change2,&change3,&change4,&change5);
	if(body==0) return 0;            
	d.affect+=change3;
	if(body==1)
	{ 
		d.wisdom+=rand()%(class+3);
		d.character+=rand()%(class+3);
		d.art+=rand()%(class+3);
	}
	else
	{
		d.wisdom+=rand()%(class+2);
		d.character+=rand()%(class+2);
		d.art+=rand()%(class+2);      
	}
	body=(d.affect*2+d.wisdom+d.art*2+d.character)/400+1;
	pip_practice_gradeup(2,class,body);
	d.classB+=1;
	return 0;
}

int pip_practice_classC()
{
/*  ├────┼──────────────────────┤*/
/*  │神學    │智力 + 1~1 , 信仰 + 1~2 , 抗魔能力 + 0~1    │*/
/*  │        ├──────────────────────┤*/
/*  │        │智力 + 1~1 , 信仰 + 1~3 , 抗魔能力 + 0~1    │*/
/*  │        ├──────────────────────┤*/
/*  │        │智力 + 1~2 , 信仰 + 1~4 , 抗魔能力 + 0~1    │*/
/*  │        ├──────────────────────┤*/
/*  │        │智力 + 1~3 , 信仰 + 1~5 , 抗魔能力 + 0~1    │*/
/*  ├────┼──────────────────────┤*/
	int body,class;
	int change1,change2,change3,change4,change5;
	char inbuf[256];
     
	class=(d.belief*2+d.wisdom)/400+1; /*神學*/
	if(class>5) class=5;

	body=pip_practice_function(3,class,31,31,&change1,&change2,&change3,&change4,&change5);
	if(body==0) return 0;            
	d.wisdom+=change2;
	d.belief+=change3;
	if(body==1)
	{ 
		d.mresist+=rand()%5;
	}
	else
	{
		d.mresist+=rand()%3;
	}
	body=(d.belief*2+d.wisdom)/400+1;
	pip_practice_gradeup(3,class,body);
	d.classC+=1;
	return 0;        
}

int pip_practice_classD()
{    
/*  ├────┼──────────────────────┤*/
/*  │軍學    │智力 + 1~2 , 戰鬥技術 + 0~1 , 感受 - 0~1    │*/
/*  │        ├──────────────────────┤*/
/*  │        │智力 + 2~4 , 戰鬥技術 + 0~1 , 感受 - 0~1    │*/
/*  │        ├──────────────────────┤*/
/*  │        │智力 + 3~4 , 戰鬥技術 + 0~1 , 感受 - 0~1    │*/
/*  │        ├──────────────────────┤*/
/*  │        │智力 + 4~5 , 戰鬥技術 + 0~1 , 感受 - 0~1    │*/
/*  ├────┼──────────────────────┤*/
	int body,class;
	int change1,change2,change3,change4,change5;
	char inbuf[256];
     
	class=(d.hskill*2+d.wisdom)/400+1;
	if(class>5) class=5;
	body=pip_practice_function(4,class,41,41,&change1,&change2,&change3,&change4,&change5);
	if(body==0) return 0;            
	d.wisdom+=change2;
	if(body==1)
	{ 
		d.hskill+=rand()%3+4;
		d.affect-=rand()%3+6;
	}
	else
	{
		d.hskill+=rand()%3+2;
		d.affect-=rand()%3+6;
	}
	body=(d.hskill*2+d.wisdom)/400+1;
	pip_practice_gradeup(4,class,body);
	if(d.affect<0)  d.affect=0;
	d.classD+=1;
	return 0;    
}

int pip_practice_classE()
{ 
/*  ├────┼──────────────────────┤*/
/*  │劍術    │戰鬥技術 + 0~1 , 攻擊能力 + 1~1             │*/
/*  │        ├──────────────────────┤*/
/*  │        │戰鬥技術 + 0~1 , 攻擊能力 + 1~2             │*/
/*  │        ├──────────────────────┤*/
/*  │        │戰鬥技術 + 0~1 , 攻擊能力 + 1~3             │*/
/*  │        ├──────────────────────┤*/
/*  │        │戰鬥技術 + 0~1 , 攻擊能力 + 1~4             │*/
/*  ├────┼──────────────────────┤*/
	int body,class;
	int change1,change2,change3,change4,change5;
	char inbuf[256];
     
	class=(d.hskill+d.attack)/400+1;
	if(class>5) class=5;
     
	body=pip_practice_function(5,class,51,51,&change1,&change2,&change3,&change4,&change5);
	if(body==0) return 0;      
	d.speed+=rand()%3+2;
	d.hexp+=rand()%2+2;
	d.attack+=change4;
	if(body==1)
	{ 
		d.hskill+=rand()%3+5;
	}
	else
	{
		d.hskill+=rand()%3+3;
	}
	body=(d.hskill+d.attack)/400+1;
	pip_practice_gradeup(5,class,body);
	d.classE+=1;
	return 0;        
}

int pip_practice_classF()
{     
/*  ├────┼──────────────────────┤*/
/*  │格鬥術  │戰鬥技術 + 1~1 , 防禦能力 + 0~0             │*/
/*  │        ├──────────────────────┤*/
/*  │        │戰鬥技術 + 1~1 , 防禦能力 + 0~1             │*/
/*  │        ├──────────────────────┤*/
/*  │        │戰鬥技術 + 1~2 , 防禦能力 + 0~1             │*/
/*  │        ├──────────────────────┤*/
/*  │        │戰鬥技術 + 1~3 , 防禦能力 + 0~1             │*/
/*  ├────┼──────────────────────┤*/
	int body,class;
	int change1,change2,change3,change4,change5;
	char inbuf[256];
     
	class=(d.hskill+d.resist)/400+1;
	if(class>5) class=5;
     
	body=pip_practice_function(6,class,61,61,&change1,&change2,&change3,&change4,&change5);
	if(body==0) return 0;
	d.hexp+=rand()%2+2;
	d.speed+=rand()%3+2;
	d.resist+=change2;
	if(body==1)
	{ 
		d.hskill+=rand()%3+5;
	}
	else
	{
		d.hskill+=rand()%3+3;
	}
	body=(d.hskill+d.resist)/400+1;
	pip_practice_gradeup(6,class,body);
	d.classF+=1;
	return 0;             
}

int pip_practice_classG()
{     
/*  ├────┼──────────────────────┤*/
/*  │魔法    │魔法技術 + 1~1 , 魔法能力 + 0~2             │*/
/*  │        ├──────────────────────┤*/
/*  │        │魔法技術 + 1~2 , 魔法能力 + 0~3             │*/
/*  │        ├──────────────────────┤*/
/*  │        │魔法技術 + 1~3 , 魔法能力 + 0~4             │*/
/*  │        ├──────────────────────┤*/
/*  │        │魔法技術 + 2~4 , 魔法能力 + 0~5             │*/
/*  ├────┼──────────────────────┤*/
	int body,class;
	int change1,change2,change3,change4,change5;
	char inbuf[256];

	class=(d.mskill+d.maxmp)/400+1;
	if(class>5) class=5;

	body=pip_practice_function(7,class,71,72,&change1,&change2,&change3,&change4,&change5);
	if(body==0) return 0;     
	d.maxmp+=change3;
	d.mexp+=rand()%2+2;
	if(body==1)
	{ 
		d.mskill+=rand()%3+7;
	}
	else
	{
		d.mskill+=rand()%3+4;
	}
	
	body=(d.mskill+d.maxmp)/400+1;
	pip_practice_gradeup(7,class,body);	
	d.classG+=1;
	return 0;                  
}

int pip_practice_classH()
{     
/*  ├────┼──────────────────────┤*/
/*  │禮儀    │禮儀表現 + 1~1 , 氣質 + 1~1                 │*/
/*  │        ├──────────────────────┤*/
/*  │        │禮儀表現 + 1~2 , 氣質 + 1~2                 │*/
/*  │        ├──────────────────────┤*/
/*  │        │禮儀表現 + 1~3 , 氣質 + 1~3                 │*/
/*  │        ├──────────────────────┤*/
/*  │        │禮儀表現 + 2~4 , 氣質 + 1~4                 │*/
/*  ├────┼──────────────────────┤*/    
	int body,class;
	int change1,change2,change3,change4,change5;
	char inbuf[256];

	class=(d.manners*2+d.character)/400+1;
	if(class>5) class=5;
	
	body=pip_practice_function(8,class,0,0,&change1,&change2,&change3,&change4,&change5);
	if(body==0) return 0;     
	d.social+=rand()%2+2;
	d.manners+=change1+rand()%2;
	d.character+=change1+rand()%2;
	body=(d.character+d.manners)/400+1;
	pip_practice_gradeup(8,class,body);
	d.classH+=1;
	return 0;  
}

int pip_practice_classI()
{          
/*  ├────┼──────────────────────┤*/
/*  │繪畫    │藝術修養 + 1~1 , 感受 + 0~1                 │*/
/*  │        ├──────────────────────┤*/
/*  │        │藝術修養 + 1~2 , 感受 + 0~1                 │*/
/*  │        ├──────────────────────┤*/
/*  │        │藝術修養 + 1~3 , 感受 + 0~1                 │*/
/*  │        ├──────────────────────┤*/
/*  │        │藝術修養 + 2~4 , 感受 + 0~1                 │*/
/*  ├────┼──────────────────────┤*/
	int body,class;
	int change1,change2,change3,change4,change5;
	char inbuf[256];
     
	class=(d.art*2+d.character)/400+1;
	if(class>5) class=5;
     
	body=pip_practice_function(9,class,91,91,&change1,&change2,&change3,&change4,&change5);
	if(body==0) return 0;
	d.art+=change4;
	d.affect+=change2;
	body=(d.affect+d.art)/400+1;
	pip_practice_gradeup(9,class,body);
	d.classI+=1;
	return 0;        
}

int pip_practice_classJ()
{    
/*  ├────┼──────────────────────┤*/
/*  │舞蹈    │藝術修養 + 0~1 , 魅力 + 0~1 , 體力 + 1~1    │*/
/*  │        ├──────────────────────┤*/
/*  │        │藝術修養 + 1~1 , 魅力 + 0~1 , 體力 + 1~1    │*/
/*  │        ├──────────────────────┤*/
/*  │        │藝術修養 + 1~2 , 魅力 + 0~2 , 體力 + 1~1    │*/
/*  │        ├──────────────────────┤*/
/*  │        │藝術修養 + 1~3 , 魅力 + 1~2 , 體力 + 1~1    │*/
/*  └────┴──────────────────────┘*/
	int body,class;
	int change1,change2,change3,change4,change5;
	char inbuf[256];
     
	class=(d.art*2+d.charm)/400+1;
	if(class>5) class=5;

	body=pip_practice_function(10,class,0,0,&change1,&change2,&change3,&change4,&change5);
	if(body==0) return 0;
	d.art+=change2;
	d.maxhp+=rand()%3+2;
	if(body==1)
	{ 
		d.charm+=rand()%(4+class);
	}
	else if(body==2)
	{
		d.charm+=rand()%(2+class);
	}
	body=(d.art*2+d.charm)/400+1;
	pip_practice_gradeup(10,class,body);
	d.classJ+=1;
	return 0;            
}

/*傳入:課號 等級 生命 快樂 滿足 髒髒 傳回:變數12345 return:body*/
int
pip_practice_function(classnum,classgrade,pic1,pic2,change1,change2,change3,change4,change5)
int classnum,classgrade,pic1,pic2;
int *change1,*change2,*change3,*change4,*change5;
{
	int  a,b,body,health;
	char inbuf[256],ans[5];
	long smoney;

	/*錢的算法*/
	smoney=classgrade*classmoney[classnum][0]+classmoney[classnum][1];
	move(b_lines-2, 0);
	clrtoeol();
	sprintf(inbuf,"[%8s%4s課程]要花 $%d ,確定要嗎??[y/N]",classword[classnum][0],classrank[classgrade],smoney);
#ifdef MAPLE
	getdata(b_lines-2, 1,inbuf, ans, 2, 1, 0);
#else
        getdata(b_lines-2, 1,inbuf, ans, 2, DOECHO, YEA);
#endif  // END MAPLE
	if(ans[0]!='y' && ans[0]!='Y')  return 0;
	if(d.money<smoney)
	{
		pressanykey("很抱歉喔...你的錢不夠喔");
		return 0;
	}
	count_tired(4,5,"Y",100,1);
	d.money=d.money-smoney;
	/*成功與否的判斷*/
	health=d.hp*1/2+rand()%20 - d.tired;
	if(health>0) body=1;
	else body=2;

	a=rand()%3+2;
	b=(rand()%12+rand()%13)%2;
	d.hp-=rand()%(3+rand()%3)+classvariable[classnum][0];
	d.happy-=rand()%(3+rand()%3)+classvariable[classnum][1];
	d.satisfy-=rand()%(3+rand()%3)+classvariable[classnum][2];
	d.shit+=rand()%(3+rand()%3)+classvariable[classnum][3];
	*change1=rand()%a+2+classgrade*2/(body+1);	/* rand()%3+3 */
	*change2=rand()%a+4+classgrade*2/(body+1);	/* rand()%3+5 */
	*change3=rand()%a+5+classgrade*3/(body+1);	/* rand()%3+7 */
	*change4=rand()%a+7+classgrade*3/(body+1);	/* rand()%3+9 */
	*change5=rand()%a+9+classgrade*3/(body+1);	/* rand()%3+11 */
	if(rand()%2>0 && pic1>0)
		show_practice_pic(pic1);
	else if(pic2>0)
		show_practice_pic(pic2);
	pressanykey(classword[classnum][body+b]);
	return body;	
}

int pip_practice_gradeup(classnum,classgrade,data)
int classnum,classgrade,data;
{
	char inbuf[256];
	
	if((data==(classgrade+1)) && classgrade<5 )
	{
		sprintf(inbuf,"下次換上 [%8s%4s課程]",
		classword[classnum][0],classrank[classgrade+1]);        
		pressanykey(inbuf);
	}
	return 0;
}
