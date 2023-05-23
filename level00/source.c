#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int buff[4];

	puts("***********************************");
	puts("* \t     -Level00 -\t\t  *");
	puts("***********************************");
	printf("Password:");
	scanf("%d", buff);
	if (buff[0] != 5276) {
		puts("\nInvalid Password!");
	}
	else {
		puts("\nAuthenticated!");
		system("/bin/sh");
	}
	return (int)(buff[0] != 5276);
}
