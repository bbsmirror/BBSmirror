/**************************/
/* ªÑ²¼Åo by dsyan 87.6.21 */
/**************************/

#include "bbs.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#define STOCK_SUM (3000)

struct st {
	char name[STOCK_SUM][12];
	char ud[21];
	unsigned long price[STOCK_SUM];
	unsigned int max_page;
	unsigned int max;
	unsigned int trans[STOCK_SUM];
};

static void
attach_err (shmkey, name)
	int shmkey;
	char *name;
{
	fprintf (stderr, "[%s error] key = %x\n", name, shmkey);
	exit (1);
}

static void *
attach_shm (shmkey, shmsize)
	int shmkey, shmsize;
{
	void *shmptr;
	int shmid;
	
	shmid = shmget (shmkey, shmsize, 0);
	if (shmid < 0) {
		shmid = shmget (shmkey, shmsize, IPC_CREAT | 0600);
		if (shmid < 0)
			attach_err (shmkey, "shmget");
		shmptr = (void *) shmat (shmid, NULL, 0);
		if (shmptr == (void *) -1)
			attach_err (shmkey, "shmat");
		memset (shmptr, 0, shmsize);
	}
	else {
		shmptr = (void *) shmat (shmid, NULL, 0);
		if (shmptr == (void *) -1)
			attach_err (shmkey, "shmat");
	}
	return shmptr;
}

unsigned int
p_stock ()
{
	char tmp[200], tp2[200];
	unsigned int money;
	unsigned int own[STOCK_SUM];
	unsigned int page = 0;
	unsigned int total = 0, t1, t2, ed;
	double double_total, double_price;
	struct st *stock;
	FILE *stock_file, *stock_game;
	
	if (stock == NULL)
		stock = (struct st *) attach_shm (5000, sizeof (*stock));
		
	// if(strcmp("dsyan", cuser.userid)) return 1;
	
	more ("etc/game/stock_wel", YEA);
	showtitle ("ªÑ¥«¤j¦ë", BoardName);
	setutmpmode (STOCK);
	sprintf (tmp, "home/%s/stock", cuser.userid);
	
	if (stock_file = fopen (tmp, "r"))
		for (total = 0; total < STOCK_SUM; total++)
			fscanf (stock_file, "%d\n", &own[total]);
	else {
		stock_file = fopen (tmp, "w");
		for (total = 0; total < STOCK_SUM; total++) {
			fprintf (stock_file, "%d\n", 0);
			own[total] = 0;
		}
	}
	fclose (stock_file);
	
	/* Åª¸ê®ÆÀÉ */
	
	if (stock_file = fopen ("etc/game/stock_now", "r")) {
		unsigned long tmpp;
		char tmpn[12];
		total = 0;
		t1 = 0;
		fgets (tmp, 150, stock_file);
		fgets (tmp, 150, stock_file);
		tmp[20] = 0;
		if (strcmp (tmp, stock -> ud)) {
			strcpy (stock -> ud, tmp);
			if (stock_game = fopen ("etc/game/stock_name", "r")) {
				while (fgets (stock -> name[t1], 12, stock_game)) {
					fgets (tmp, 12, stock_game);
					move (8, 8);
					prints ("%d <%s>", t1, stock -> name[t1]);
					t1++;
				}
				fclose (stock_game);
			}
			stock_game = fopen ("etc/game/stock_log", "a+");
			fprintf (stock_game, "[41m§ó·s¸ê®Æ [42m%s [m\n", stock -> ud);
			fclose (stock_game);
			stock_game = fopen ("etc/game/stock_name", "a+");
			while (fgets (tmp, 200, stock_file)) {
				if (tmp[0] != '|' || tmp[1] < '0' || tmp[1] > '9')
					continue;
				tmp[12] = 0;
				tmp[53] = 0;
				total++;
				tmpp = atof (tmp + 47) * 100;
				move (10, 10);
				prints ("tmpp = %d ", tmpp);
				strcpy (tmpn, tmp + 1);
				move (11, 11);
				prints ("tmpn = <%s> ", tmpn);
				for (t2 = 0; t2 < t1; t2++)
					if (!strcmp (tmpn, stock -> name[t2]))
						break;
				if (t2 == t1) {
					strcpy (stock -> name[t2], tmpn);
					fprintf (stock_game, "%s\n", tmpn);
					t1++;
				}
				stock -> price[t2] = tmpp;
			}
			fclose (stock_game);
			fclose (stock_file);
			stock -> max = total;
			stock -> max_page = total / 40;
			if (stock -> max_page % 40)
				stock -> max_page++;
		}
	}
	while (-1) {
		unsigned int i, r;
		time_t now = time(NULL);
		struct tm *ptime = localtime(&now);
		/* µe­±¥Dµ{¦¡ */
		move (1, 0);
		clrtobot ();
		prints ("[37;1;46m ½s¸¹ [42m ªÑ ²¼ ¦W ºÙ [43m »ù ®æ [45m «ù¦³±i¼Æ [m    [46;1m ½s¸¹ [42m ªÑ ²¼ ¦W ºÙ [43m »ù ®æ [45m «ù¦³±i¼Æ [m");
		for (i = 0; i < 20; i++) {
			clrtoeol();
			move (i + 2, 0);
			r = page * 40 + i;
			if (r + 1 <= stock -> max)
				prints (" %3d)  %11s%5d.%-2d %5d         ", r + 1, stock -> name[r], stock -> price[r] / 100, stock -> price[r] % 100, own[r]);
			r = page * 40 + i + 20;
			if (r + 1 <= stock -> max)
				prints ("%3d)  %11s%5d.%-2d %5d\n", r + 1, stock -> name[r], stock -> price[r] / 100, stock -> price[r] % 100, own[r]);
		}
		move (22, 0);
		prints ("[44mn:¤U­¶ p:¤W­¶ b:¶R s:½æ v:¬Ý e:­× q:¸õ¥X ª÷:%-8d %2d/%2d %20s[m", cuser.money, page + 1, stock -> max_page, stock -> ud);
		total = igetch ();
		switch (total) {
			case 'b':
				now = time (0);
				ptime = localtime (&now);
				if (ptime -> tm_hour > 7 && ptime -> tm_hour < 19) {
					move (23, 0);
					pressanykey("¥æ©ö®É¶¡¬°¨C¤Ñ±ß¤W¤CÂI¨ì¹j¤Ñ¦­¤W¤KÂI..");
					break;
				}
				move (23, 0);
				prints ("­n¶R¨º®a??(1-%d) ", stock -> max);
				getdata (23, 19, " ", tmp, 4, 1, 0);
				total = atoi (tmp);
				if (total < 1 || total > stock -> max) {
					pressanykey("¿é¤J¿ù»~");
					break;
				}
				double_price = stock -> price[total - 1] * 10;
				if (double_price == 0.0) {
					pressanykey("µLªkÁÊ¶R»ù®æµ¥©ó¹sªºªÑ²¼¡I");
					break;
				}
				else if(double_price >= 1000) {
					pressanykey("ºî¦X«ü¼ÆµLªkÁÊ¶R¡I");
					break;
				}
				else
					double_total = cuser.money / double_price;
				t2 = (unsigned int) double_total;
				move (23, 0);
				prints ("­n¶R´X±i??(0-%d) ", t2);
				getdata (23, 19, " ", tmp, 4, 1, 0);
				t1 = atoi (tmp);
				if (t1 > t2 || t1 < 1) {
					pressanykey("¿é¤J¿ù»~");
					break;
				}
				stock_game = fopen ("etc/game/stock_log", "a+");
				now = time (0);
				double_total = t1 * double_price * 1.007;
				sprintf (tmp, "[33;1m%s [36m%s[m ", Cdate (&now), cuser.userid);
				fprintf (stock_game, "%s [1;32m¶R¤F %s %d ±i.. [31m%d[m\n", tmp, stock -> name[total - 1], t1, (unsigned int) double_total);
				fclose (stock_game);
				sprintf (tp2, "/home/bbs/home/%s/stock_log", cuser.userid);
				stock_game = fopen (tp2, "a+");
				now = time (0);
				double_total = t1 * double_price * 1.007;
				fprintf (stock_game, "%s ¥H %f ªº»ù®æ¶R¤F %s %d ±i.. %d\n", Cdate (&now), (float) stock -> price[total - 1] / 100, stock -> name[total - 1], t1, (unsigned int) double_total);
				fclose (stock_game);
				double_total = t1 * double_price * 1.007;
				money = (unsigned int) double_total;
				demoney (money);
				own[total - 1] += t1;
				break;
			
			case 's':
				now = time (0);
				ptime = localtime (&now);
				if (ptime -> tm_hour > 7 && ptime -> tm_hour < 19) {
					move (23, 0);
					pressanykey("¥æ©ö®É¶¡¬°¨C¤Ñ±ß¤W¤CÂI¨ì¹j¤Ñ¦­¤W¤KÂI..");
					break;
				}
				move (23, 0);
				prints ("­n½æ¨º®a??(1-%d) ", stock -> max);
				getdata (23, 19, " ", tmp, 4, 1, 0);
				total = atoi (tmp);
				if (total < 1 || total > stock -> max || !own[total - 1]) {
					pressanykey("¿é¤J¿ù»~");
					break;
				}
				double_price = stock -> price[total - 1] * 10;
				move (23, 0);
				prints ("­n½æ´X±i??(0-%d) ", own[total - 1]);
				getdata (23, 19, " ", tmp, 4, 1, 0);
				t1 = atoi (tmp);
				if (t1 > own[total - 1] || t1 <= 0) {
					pressanykey("¿é¤J¿ù»~");
					break;
				}
				now = time (0);
				double_total = t1 * double_price * 0.993;
				stock_game = fopen ("etc/game/stock_log", "a+");
				sprintf (tmp, "[33;1m%s [36m%s[m ", Cdate (&now), cuser.userid);
				fprintf (stock_game, "%s [1;31m½æ¤F %s %d ±i.. [32m%d[m\n", tmp, stock -> name[total - 1], t1, (unsigned int) double_total);
				fclose (stock_game);
				sprintf (tp2, "/home/bbs/home/%s/stock_log", cuser.userid);
				stock_game = fopen (tp2, "a+");
				fprintf (stock_game, "%s ¥H %f ªº»ù®æ½æ¤F %s %d ±i.. %d\n", Cdate (&now), (float) stock -> price[total - 1] / 100, stock -> name[total - 1], t1, (unsigned int) double_total);
				fclose (stock_game);
				double_total = t1 * double_price * 0.993;
				money = (unsigned int) double_total;
				inmoney (money);
				own[total - 1] -= t1;
				break;
			
			case 'v':
				sprintf (tp2, "home/%s/stock_log", cuser.userid);
				more (tp2, YEA);
				showtitle ("ªÑ¥«¤j¦ë", BoardName);
				break;
			
			case 'e':
				sprintf (tp2, "home/%s/stock_log", cuser.userid);
				t2 = vedit (tp2, NA);
				showtitle ("ªÑ¥«¤j¦ë", BoardName);
				break;
			
			case 'p':
				if (page)
					page--;
				break;
		
			case 'n':
				if (page + 1 < stock -> max_page)
					page++;
				break;
		
			case 'q':
				sprintf (tmp, "home/%s/stock", cuser.userid);
				stock_file = fopen (tmp, "w");
				for (total = 0; total < STOCK_SUM; total++)
					fprintf (stock_file, "%d\n", own[total]);
				fclose (stock_file);
				return 1;
		
			default:
				break;
			
		}
	}
}
