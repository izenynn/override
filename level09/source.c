#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void secret_backdoor(void)
{
	char local_88 [128];

	fgets(local_88, 128, stdin);
	system(local_88);
	return;
}

void set_username(char *param_1)
{
	char local_98 [128];
	int local_c;

	memset(local_98, 0, 128);
	puts(">: Enter your username");
	printf(">>: ");
	fgets(local_98, 128, stdin);
	for (local_c = 0; (local_c < 41 && *(local_98 + local_c) != '\0');
			local_c = local_c + 1) {
		param_1[local_c + 140] = *(local_98 + local_c);
	}
	printf(">: Welcome, %s",param_1 + 140);
	return;
}

void set_msg(char *param_1)

{
	char local_408[1024];

	memset(local_408, 0, 1024);
	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(local_408, 0x400, stdin);
	strncpy(param_1, local_408, (long)*(int *)(param_1 + 0xb4));
	return;
}

void handle_msg(void)
{
	char buff[184];

	buff[140] = '\0';
	buff[141] = '\0';
	buff[142] = '\0';
	buff[143] = '\0';
	buff[144] = '\0';
	buff[145] = '\0';
	buff[146] = '\0';
	buff[147] = '\0';
	buff[148] = '\0';
	buff[149] = '\0';
	buff[150] = '\0';
	buff[151] = '\0';
	buff[152] = '\0';
	buff[153] = '\0';
	buff[154] = '\0';
	buff[155] = '\0';
	buff[156] = '\0';
	buff[157] = '\0';
	buff[158] = '\0';
	buff[159] = '\0';
	buff[160] = '\0';
	buff[161] = '\0';
	buff[162] = '\0';
	buff[163] = '\0';
	buff[164] = '\0';
	buff[165] = '\0';
	buff[166] = '\0';
	buff[167] = '\0';
	buff[168] = '\0';
	buff[169] = '\0';
	buff[170] = '\0';
	buff[171] = '\0';
	buff[172] = '\0';
	buff[173] = '\0';
	buff[174] = '\0';
	buff[175] = '\0';
	buff[176] = '\0';
	buff[177] = '\0';
	buff[178] = '\0';
	buff[179] = '\0';
	buff[180] = 0x8c; // 140
	buff[181] = '\0';
	buff[182] = '\0';
	buff[183] = '\0';
	set_username(buff);
	set_msg(buff);
	puts(">: Msg sent!");
	return;
}

int main(void)
{
	puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~	v1337		|\n- -------------------------------------------");
	handle_msg();
	return 0;
}
