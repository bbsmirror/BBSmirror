/* Transfer Maple3 gem into firebird's one. */
/* Write by Magi.bbs@magic.twbbs.org */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/config.h"
#include "../include/struct.h"

#define BUFLEN       (255)

char           *theboard;

dowrite(char *curpath, char *dotdir, char *desc)
{
	int             numb = 1, fdDIR;
	char            nextdotdir[BUFLEN], buf[BUFLEN], cmdbuf[BUFLEN],
	                newpath[BUFLEN];
	HDR             gh;
	FILE           *fp;

	sprintf(buf, "%s/.Names", curpath);
	printf("Processing %s\n", buf);
	fp = fopen(buf, "w");
	fprintf(fp, "#\n# Title=%s\n#\n", desc);
	if (fdDIR = open(dotdir, O_RDONLY)) {
		while (read(fdDIR, &gh, sizeof(gh)) == sizeof(gh)) {
			if (gh.xname[0] != '@') {
				fprintf(fp, "Name=%s\n", gh.title);
				fprintf(fp, "Path=~/%s\n", gh.xname);
				fprintf(fp, "Numb=%d\n#\n", numb++);
				if (gh.xmode & GEM_FOLDER) {
					sprintf(nextdotdir, "%s/%c/%s", theboard, gh.xname[7], gh.xname);
					sprintf(newpath, "%s/%s", curpath, gh.xname);
					mkdir(newpath, 0755);
					dowrite(newpath, nextdotdir, gh.title);
				} else {
					sprintf(cmdbuf, "cp %s/%c/%s %s", theboard, gh.xname[7], gh.xname, curpath);
					system(cmdbuf);
				}
			}
		}
	}
	close(fdDIR);
	fclose(fp);
}

int 
main(int argc, char **argv)
{
	int             fdDIR;

	char            buf[BUFLEN], curpath[BUFLEN];

	if (argc == 2) {
		theboard = argv[1];
		sprintf(curpath, "fb_%s", argv[1]);
		mkdir(curpath, 0755);
		sprintf(buf, "%s/.DIR", argv[1]);
		dowrite(curpath, buf, argv[1]);
	} else {
		printf("gem2fb by Magi - run this program under ~bbs/gem/brd\n\n");
		printf("Usage: %s boardname\n", argv[0]);
	}
}
