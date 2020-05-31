/*************************************************************************
 * uncompress.c --- uncompress msgpack file				 *
 *	      by Samson Chen, Apr 16, 1994				 *
 *************************************************************************/

#include "../host/pbbs.h"
#include "global.h"
#include "../host/dbf.h"



/*
	uncompress_post --- (as the name)
*/
uncompress_post(cpack)
	char *cpack;	/*compressed packing filename*/
{
	char line[1024];
	char buf[MAX_BUF];
	char dot=FALSE;
	int n, p, ret;
	char cr_lf[3];
	int buf_cnt;
	char unzip_exe[128];
	FILE *shell;
	char got_post;
	char message_id[256];

	sprintf(cr_lf, "%c%c", 13, 10);

	/*uncompressing*/
	sprintf(unzip_exe, "%s %s", UNZIP, cpack);
	shell=popen(unzip_exe, "r");

	/*get the unprocessed message*/

	got_post=TRUE;

	while( fgets(line, 1023, shell) )
	{
		if(got_post)
		{
		  /*first line (Message-ID: )*/
		  got_post=FALSE;

		  buf[0]=0;
		  buf_cnt=0;

		  strcpy(message_id, line+12);
		  strip_nl(message_id);

		  continue;
		}

		strcat(buf, line);
		if( strlen(line)==3 && line[0]=='.' )
		{
			got_post=TRUE;

			/*here we got the total message for processing*/
			if( debug_mode )
			{
				printf("(uncompress.c)get transfer->\n");
				printf("%s<<<end of message>>>\n", buf);
			}

			/*strip the double dots(..) at the beginning of a line*/
			ret=strlen(buf);
			for(n=0; n<ret; n++)
			{
				if( buf[n]=='.' )
				  if( buf[n-1]==10 )
				  {
				    for(p=n; p<ret; p++)
					buf[p]=buf[p+1];
				    ret--;
				  }
			}

			/*now we got the processed message*/
			if( debug_mode ){
				printf("\n(uncompress.c) get processed message->\n");
				printf("%s<<<end of processed message>>>\n", buf);
			}

			/**************************************/
			/*check mid from DBZ and parse message*/
			/**************************************/
			if( !query_mid(message_id, NULL) )
			  cp_parse_news(buf);
		}

	}/*end while*/

	pclose(shell);
	unlink(cpack);
	do_log(3, "uncompress msg for %s ok", client_site);
}
/*end of sendme*/


cp_parse_news(msg)
	char *msg;	/*message body*/
{
	char buf[2047];
	char m_path[512];
	char from[256];
	char newsgroup[1024];
	char subject[256];
	char control[256];
	char message_id[256];
	char date[32];
	char organization[256];
	char reply_to[256];
	char toss_group[80], toss_gp[1536];
	char line[2048];
	char *toss_p;
	int toss_r;
	char *point;
	char head=TRUE;
	int n,p;
	char mail_path[80];
	char mfile[90], rfile[90];
	int msgfile, recfile;
	struct msgrec mr;
	int test;
	int total_msg;
	int scan_order;
	int fp;
	char get_control_message=FALSE;
	char this_is_control_cancel=FALSE;


	reset_alarm();

	/*initial*/
	m_path[0]=0;
	from[0]=0;
	newsgroup[0]=0;
	subject[0]=0;
	control[0]=0;
	message_id[0]=0;
	date[0]=0;
	organization[0]=0;
	reply_to[0]=0;

	point=msg;
	n=0;
	p=0;

	do
	{
	  /*maybe wrong message format*/
	  if( p>=strlen(msg) )
	  {
		do_log(8, "message error from %s", client_site);
		return(FALSE);
	  }

	  /*find a line*/
	  for(p=n;p<strlen(msg);p++)
		if( msg[p]==13 ) break;

	  /*CR-LF-CR-LF appeared, head field finished*/
	  if( n==p )
	  {
		head=FALSE;
		continue;
	  }

	  /*cut a line*/
	  strncpy(buf, msg+n, p-n);
	  if( (p-n)>=2047 )
	    buf[2046]=0;
	  else
	    buf[p-n]=0;

	  /*determine field*/
	  switch( parse_field(buf) )
	  {
	  case PATH:
		nstrcpy(m_path, buf+6, 512);
		break;

	  case FROM:
		nstrcpy(from, buf+6, 256);
		break;

	  case NEWSGROUP:
		nstrcpy(newsgroup, buf+12, 1024);
		break;

	  case SUBJECT:
		nstrcpy(subject, buf+9, 256);
		break;

	  case CONTROL:
		nstrcpy(control, buf+9, 256);
		break;

	  case MID:
		nstrcpy(message_id, buf+12, 256);
		break;

	  case DATE:
		nstrcpy(date, buf+6, 32);
		break;

	  case ORGANIZATION:
		nstrcpy(organization, buf+14, 256);
		break;

	  case REPLY_TO:
		nstrcpy(reply_to, buf+10, 256);
		break;
	  }

	  n=p+2;  /*skip CR-LF*/

	}while(head);

	if( debug_mode )
	{
		printf("\n(sendme.c) parse message head as follows...\n");
		printf("Path: %s\n",m_path);
		printf("From: %s\n", from);
		printf("Newsgroups: %s\n", newsgroup);
		printf("Subject: %s\n", subject);
		if( strlen(control) )
			printf("Control: %s\n", control);
		printf("Message-ID: %s\n", message_id);
		printf("Data: %s\n", date);
		printf("Organization: %s\n", organization);
		if( strlen(reply_to) )
			printf("Reply-To: %s\n", reply_to);
	}

	/*processing mail path*/
	if( check_mpath(m_path, STATION_ID) )
	{
		do_log(9, "message LOOP found at %s group from %s mid %s", newsgroup, client_site, message_id);
		return(FALSE);
	}
	else
	{
		sprintf(line, "%s!%s", STATION_ID, m_path);
		nstrcpy(m_path, line, 512);
	}


	/*************************************************/
	/*check subject field if this is a cancel message*/

	if( strlen(control) )
	{
	  if(debug_mode)printf("(sendme.c)cmsg %s at %s\n", control, newsgroup);
	  if( !strncmp(control, "cancel ", 7) )
	  {
		do_log(1, "%s %s", client_site, subject); /*log cancel signal*/
		get_control_cancel=TRUE;
		this_is_control_cancel=TRUE;
	  }

	  /*dup cmsg to 'controlmsg' internal group*/
	  get_control_message=TRUE;
	}

	/*************************************************/


	/*take the message body*/
	n+=2;	/*skip first cr-lf*/

	for(p=n; p<=strlen(msg); p++)
		msg[p-n]=msg[p];

	msg[p-n]=0;
	/*------------------------*/

	do_log(0, "%s send a post to %s", client_site, newsgroup);

	if( strlen(from)==0 || strlen(newsgroup)==0 || strlen(message_id)==0 )
	{
		do_log(6, "head of a post from %s was wrong", client_site);
		return(FALSE);
	}

	/*********/
	/*tossing*/
	/*********/

	/*for cross-post*/
	memset(toss_gp, 0, 1536);
	nstrcpy(toss_gp, newsgroup, 1024);
	if(this_is_control_cancel)
	  strcat(toss_gp, ",cancelmsg");
	else if(get_control_message)
	  strcat(toss_gp, ",controlmsg");
	toss_p=toss_gp;

	while( (toss_r=next_comma(toss_p)) != 0)
	{
	toss_p[toss_r]=0;
	nstrcpy(toss_group, toss_p, 80);
	if( debug_mode ) printf("(sendme.c)toss_group-> %s\n", toss_group);

	if( !get_mpath(mail_path, toss_group) )
	{
		toss_p+=toss_r+1;
		continue;
	}

	sprintf(mfile, "%s/messages", mail_path);
	sprintf(rfile, "%s/records", mail_path);

	if( !file_exist(mfile) )
	{
		test=open( mfile, O_WRONLY | O_APPEND | O_CREAT, S_IWUSR | S_IRUSR);
		if( test<0 )
		{
			do_log(9, "%s open error!?", mfile);
			toss_p+=toss_r+1;
			continue;
		}
		else
			close(test);
	}

	if( !file_exist(rfile) )
	{
		test=open( rfile, O_WRONLY | O_APPEND | O_CREAT, S_IWUSR | S_IRUSR);
		if( test<0 )
		{
			do_log(9, "%s open error!?", rfile);
			toss_p+=toss_r+1;
			continue;
		}
		else
			close(test);
	}

	/***************************************************************/
	/*APPEND to msg file*/

	msgfile=open(mfile, O_WRONLY | O_APPEND);
	recfile=open(rfile, O_WRONLY | O_APPEND);

	if( msgfile<0 )
	{
		do_log(9, "%s open error!?", mfile);
		toss_p+=toss_r+1;
		continue;
	}

	if( recfile<0 )
	{
		do_log(9, "%s open error!?", rfile);
		toss_p+=toss_r+1;
		continue;
	}

	flock(msgfile, LOCK_EX);	/*exclusive lock*/
	flock(recfile, LOCK_EX);	/*exclusive lock*/

	lseek(msgfile, 0, SEEK_END);
	mr.offset=file_length(msgfile);
	nstrcpy(mr.subject, subject, 60);
	mr.packed=' ';
	/*if control cancel, the post in controlmsg should be mark 'C'*/
	/*for batch canceling					      */
	if( this_is_control_cancel && !strcmp(toss_group, "controlmsg") )
	  mr.delete_mark='C';
	else
	  mr.delete_mark=' ';

	sprintf(buf, "Path: %s%c%c", m_path, 13, 10);
		write(msgfile, buf, strlen(buf) );
	sprintf(buf, "From: %s%c%c", from, 13, 10);
		write(msgfile, buf, strlen(buf) );
	sprintf(buf, "Newsgroups: %s%c%c", newsgroup, 13, 10);
		write(msgfile, buf, strlen(buf) );
	sprintf(buf, "Subject: %s%c%c", subject, 13, 10);
		write(msgfile, buf, strlen(buf) );

	if( strlen(control) )
	{
	sprintf(buf, "Control: %s%c%c", control, 13, 10);
		write(msgfile, buf, strlen(buf) );
	}

	sprintf(buf, "Message-ID: %s%c%c", message_id, 13, 10);
		write(msgfile, buf, strlen(buf) );
	sprintf(buf, "Date: %s%c%c", date, 13, 10);
		write(msgfile, buf, strlen(buf) );
	sprintf(buf, "Organization: %s%c%c", organization, 13, 10);
		write(msgfile, buf, strlen(buf) );

	if( strlen(reply_to) )
	{
	sprintf(buf, "Reply-To: %s%c%c", reply_to, 13, 10);
		write(msgfile, buf, strlen(buf) );
	}

	/*write first cr-lf to seperate head from msg body*/
	sprintf(buf, "%c%c", 13, 10);
	write(msgfile, buf, 2);

	write(msgfile, msg, strlen(msg) );

	lseek(msgfile, 0, SEEK_END);
	mr.length=file_length(msgfile)-mr.offset;

	write(recfile, &mr, sizeof(mr) );

	/*add mid to DBZ server*/
	sprintf(line, "%d", (file_length(recfile)/sizeof(struct msgrec)) );
	add_mid(message_id, line);

	flock(msgfile, LOCK_UN);	/*unlock*/
	flock(recfile, LOCK_UN);	/*unlock*/

	close(msgfile);
	close(recfile);

	do_log(3, "get post to %s from %s", toss_group, client_site);

	toss_p+=toss_r+1;

	}/*end while(toss_r=next_comma())*/

	return(TRUE);

}
/*end of parse_news*/
