#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void clear_stdin(void)
{
	int c;

	do {
		c = getchar();
		if ((char)c == '\n') {
			return;
		}
	} while ((char)c != -1);
	return;
}

int get_unum(void)
{
	int local_10 [3];

	local_10[0] = 0;
	fflush(stdout);
	scanf("%u",local_10);
	clear_stdin();
	return local_10[0];
}

int read_number(int *param_1)
{
	int iVar1;

	printf(" Index: ");
	iVar1 = get_unum();
	printf(" Number at data[%u] is %u\n",iVar1,*(int *)(iVar1 * 4 + param_1));
	return 0;
}

int store_number(int *param_1)
{
	unsigned int uVar1;
	unsigned int uVar2;
	int uVar3;

	printf(" Number: ");
	uVar1 = get_unum();
	printf(" Index: ");
	uVar2 = get_unum();
	if ((uVar2 % 3 == 0) || (uVar1 >> 0x18 == 0xb7)) {
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		uVar3 = 1;
	}
	else {
		*(unsigned int *)(uVar2 * 4 + param_1) = uVar1;
		uVar3 = 0;
	}
	return uVar3;
}

int main(int argc, char *argv[], char *envp[])
{
	int ret;
	char buff[20];
	int storage[100];
	char **envp_ptr;
	char **argv_ptr;

	memset(storage, 0, 100 * sizeof(int));
	argv_ptr = argv;
	envp_ptr = envp;
	while (*argv_ptr) {
		memset(*argv_ptr, 0, strlen(*argv_ptr));
		argv_ptr++;
	}
	while (*envp_ptr) {
		memset(*envp_ptr, 0, strlen(*envp_ptr));
		envp_ptr++;
	}

	puts("----------------------------------------------------\n  Welcome to wil\'s crappy number stora ge service!   \n----------------------------------------------------\n Commands:                                           \n    store - store a number into the data storage    \n    read   - read a number from the data storage     \n    quit  - exit the program                         \n----------------------------------------------------\n   wil has reserved some storage :>                  \n----------------------------------------------------\n");

	do {
		ret = 1;
		printf("Input command: ");
		fgets(buff, 20, stdin);
		buff[strlen(buff) - 1] = '\0';
		if (strncmp(buff, "store", 5) == 0) {
			ret = store_number(storage);
		} else if (strncmp(buff, "read", 4) == 0) {
			ret = read_number(storage);
		} else if (strncmp(buff, "quit", 4) == 0) {
			break;
		}
		if (ret == 0) {
			printf(" Completed %s command successfully\n", buff);
		} else {
			printf(" Failed to do %s command\n", buff);
		}
	} while (1);

	return 0;
}
