#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int iVar1;
	size_t sVar2;
	long lVar3;
	size_t *puVar4;
	char userpass[112];
	char pass[48];
	char username[96];
	int local_14;
	FILE *fpass;

	memset(username, '\0', 96);
	memset(userpass, '\0', 112);
	memset(pass, '\0', 48);

	fpass = fopen("/home/users/level03/.pass","r");
	if (fpass == NULL) {
		fwrite("ERROR: failed to open password file\n", 1, 0x24, stderr);
		exit(1);
	}
	
	sVar2 = fread(pass, 1, 41, fpass);
	local_14 = (int)sVar2;
	sVar2 = strcspn(pass,"\n");
	pass[sVar2] = '\0';
	if (local_14 != 41) {
		fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
		fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
		exit(1);
	}
	fclose(fpass);

	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	printf("--[ Username: ");
	fgets(username,100,stdin);
	sVar2 = strcspn(username,"\n");
	username[sVar2] = '\0';
	printf("--[ Password: ");
	fgets(userpass,100,stdin);
	sVar2 = strcspn(userpass,"\n");
	userpass[sVar2] = '\0';
	puts("*****************************************");
	iVar1 = strncmp(pass,userpass,41);
	if (iVar1 == 0) {
		printf("Greetings, %s!\n",username);
		system("/bin/sh");
		return 0;
	}
	printf(username);
	puts(" does not have access!");

	exit(1);
}
