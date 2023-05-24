#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char cVar1;
	unsigned int uVar2;
	char *pcVar3;
	char buff [100];
	unsigned int i;

	fgets(buff,100,stdin);
	i = 0;
	do {
		uVar2 = 0xffffffff;
		pcVar3 = buff;
		do {
			if (uVar2 == 0) break;
			uVar2 = uVar2 - 1;
			cVar1 = *pcVar3;
			pcVar3 = pcVar3 + 1;
		} while (cVar1 != '\0');
		if (~uVar2 - 1 <= i) {
			printf(buff); // FMT String Vuln
			exit(0);
		}
		if (('@' < buff[i]) && (buff[i] < '[')) {
			buff[i] = buff[i] ^ 32;
		}
		i = i + 1;
	} while( 1 );

	return 0;
}
