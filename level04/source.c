#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <signal.h>

int main(void)
{
	long lVar1;
	int iVar2;
	int *puVar3;
	int local_a4;
	char local_a0[128];
	pid_t pid;

	pid = fork();
	puVar3 = (int *)local_a0;
	for (iVar2 = 32; iVar2 != 0; iVar2 = iVar2 + -1) {
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	local_a4 = 0;
	if (pid == 0) {
		prctl(1,1);
		ptrace(PTRACE_TRACEME,0,0,0);
		puts("Give me some shellcode, k");
		gets(local_a0);
	} else {
		do {
			wait(&local_a4);
			if (WIFEXITED(local_a4)) {
				puts("child is exiting...");
				return 0;
			}
			lVar1 = ptrace(PTRACE_PEEKUSER,pid,0x2c,0);
		} while (lVar1 != 0xb);
		puts("no exec() for you");
		kill(pid,9);
	}
	return 0;
}
