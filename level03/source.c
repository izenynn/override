#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int decrypt(int n)
{
	char s[] = "Q}|u`sfg~sf{}|a3"; // Remember is little-endian!
	int len;
	int ret;

	len = strlen(s);
	for (int i = 0; i < len; ++i)
		s[i] = n ^ s[i];

	if (strncmp(s, "Congratulations!", 0x11) == 0)
		ret = system("/bin/sh");
	else
		ret = puts("\nInvalid Password");
	
	return ret;
}

void test(int userpass, int pass)
{
	int res = pass - userpass; // 4 bytes

	switch (res) {
	case 0x1:
	case 0x2:
	case 0x3:
	case 0x4:
	case 0x5:
	case 0x6:
	case 0x7:
	case 0x8:
	case 0x9:
	case 0x10:
	case 0x11:
	case 0x12:
	case 0x13:
	case 0x14:
	case 0x15:
		decrypt(res);
		break;
	default:
		res = rand();
		decrypt(res);
		break;
	}
}

int main(void)
{
	unsigned int seed;
	int n;

	seed = time((time_t *)0x0);
	srand(seed);
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");
	scanf("%d", n);
	test(n, 322424845);

	return 0;
}
