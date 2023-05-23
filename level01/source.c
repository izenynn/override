#include <stdio.h>
#include <string.h>

char a_user_name[100];

int verify_user_name(void)
{
	puts("verifying username....\n");
	return strncmp(a_user_name, "dat_wil", 7);
}

int verify_user_pass(char *pass)
{
	return strncmp(pass, "admin", 5);
}

int main(void)
{
	int ret;
	char buff[64];

	bzero(buff, 64);
	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(a_user_name,256,stdin);
	ret = verify_user_name();
	if (ret == 0) {
		puts("Enter Password: ");
		fgets(buff,100,stdin);
		ret = verify_user_pass(buff);
		if ((ret == 0) || (ret != 0)) {
			puts("nope, incorrect password...\n");
			ret = 1;
		}
		else {
			ret = 0;
		}
	}
	else {
		puts("nope, incorrect username...\n");
		ret = 1;
	}
	return ret;
}
