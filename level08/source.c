#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/*void log_wrapper(FILE *param_1,char *param_2,char *param_3)
{
	char cVar1;
	size_t sVar2;
	unsigned long uVar3;
	unsigned long uVar4;
	char *pcVar5;
	FILE *local_120;
	char local_118 [264];

	local_120 = param_1;
	strcpy(local_118,param_2);
	uVar3 = 0xffffffffffffffff;
	pcVar5 = local_118;
	do {
		if (uVar3 == 0) break;
		uVar3 = uVar3 - 1;
		cVar1 = *pcVar5;
		pcVar5 = pcVar5 + 1;
	} while (cVar1 != '\0');
	uVar4 = 0xffffffffffffffff;
	pcVar5 = local_118;
	do {
		if (uVar4 == 0) break;
		uVar4 = uVar4 - 1;
		cVar1 = *pcVar5;
		pcVar5 = pcVar5 + 1;
	} while (cVar1 != '\0');
	snprintf(local_118 + (~uVar4 - 1),0xfe - (~uVar3 - 1),param_3);
	sVar2 = strcspn(local_118,"\n");
	local_118[sVar2] = '\0';
	fprintf(local_120,"LOG: %s\n",local_118);

	return;
}*/

void log_wrapper(FILE *s, char *msg, char *file)
{
	char buff[264];

	strcpy(buff, msg);
	snprintf(buff + strlen(buff), 0xfe - strlen(buff), file);
	buff[strcspn(buff, "\n")] = '\0';
	fprintf(s, "LOG: %s\n", buff);
}

int main(int argc,char **argv)
{
	char cVar1;
	int __fd;
	int iVar3;
	FILE *flog;
	FILE *__stream;
	char local_79;
	char dir [8];

	local_79 = -1;
	if (argc != 2) {
		printf("Usage: %s filename\n",*argv);
	}
	flog = fopen("./backups/.log","w");
	if (flog == (FILE *)0x0) {
		printf("ERROR: Failed to open %s\n","./backups/.log");
		exit(1);
	}
	log_wrapper(flog,"Starting back up: ",argv[1]);
	__stream = fopen(argv[1],"r");
	if (__stream == (FILE *)0x0) {
		printf("ERROR: Failed to open %s\n",argv[1]);
		exit(1);
	}
	dir[0] = '.';
	dir[1] = '/';
	dir[2] = 'b';
	dir[3] = 'a';
	dir[4] = 'c';
	dir[5] = 'k';
	dir[6] = 'u';
	dir[7] = 'p';
	strncat(dir, argv[1], strlen(argv[1]));
	__fd = open(dir, 0xc1, 0x1b0);
	if (__fd < 0) {
		printf("ERROR: Failed to open %s%s\n","./backups/", argv[1]);
		exit(1);
	}
	while( 1 ) {
		iVar3 = fgetc(__stream);
		local_79 = (char)iVar3;
		if (local_79 == -1) break;
		write(__fd, &local_79, 1);
	}
	log_wrapper(flog, "Finished back up ", argv[1]);
	fclose(__stream);
	close(__fd);
	return 0;
}
