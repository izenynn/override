#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int i;
	int len;
	int orig_len;
	int elems;
	unsigned int *p;

	if (argc != 3) {
		printf("Usage: %s SHELLCODE LENGTH\n", argv[0]);
		return 1;
	}

	orig_len = atoi(argv[2]);
	if (orig_len % sizeof(unsigned int) != 0) {
		len = orig_len + (sizeof(unsigned int) - (orig_len % sizeof(unsigned int)));
	} else {
		len = orig_len;
	}
	elems = len / 4;

	p = malloc(len);
	memcpy(p, argv[1], orig_len);
	memset(p + orig_len, 0, len - orig_len);

	for (i = 0; i < elems; ++i) {
		printf("%u\n", *(p + i));
	}

	free(p);
	return 0;
}
