#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ptrace.h>

int auth(char *username, unsigned int userpass)
{
	size_t len;
	int ret;
	long isTraced;
	int i;
	unsigned int pass;

	len = strcspn(username,"\n");
	username[len] = '\0';
	len = strnlen(username,32);
	if ((int)len < 6) {
	  ret = 1;
	} else {
		isTraced = ptrace(PTRACE_TRACEME);
		if (isTraced == -1) {
			puts("\x1b[32m.---------------------------.");
			puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
			puts("\x1b[32m\'---------------------------\'");
			ret = 1;
		} else {
			pass = ((int)username[3] ^ 4919U) + 6221293;
			for (i = 0; i < (int)len; i = i + 1) {
				if (username[i] < ' ') {
					return 1;
				}
				pass = pass + ((int)username[i] ^ pass) % 1337;
			}
			if (userpass == pass) {
				ret = 0;
			} else {
				ret = 1;
			}
		}
	}
	return ret;
}

int main(int argc,char **argv)
{
	int isAuth;
	unsigned int userpass;
	char username[32];

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(username,32,stdin);
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	scanf("%u", &userpass);
	isAuth = auth(username,userpass);
	if (isAuth == 0) {
		puts("Authenticated!");
		system("/bin/sh");
	}
	return (int)(isAuth != 0);
}
