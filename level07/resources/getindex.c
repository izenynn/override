#include <stdio.h>

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

int main(void)
{
	unsigned int index;

	printf("Index we need: 114\n");
	while (1) {
		fflush(stdout);
		scanf("%u", &index);
		clear_stdin();
		printf("Index: %u\n", (unsigned int)(index * 4) / 4);
	}

	return 0;
}
