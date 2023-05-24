# Walkthrough

## Reversing

```c
int main(void)
{
    long lVar1;
    int iVar2;
    undefined4 *puVar3;
    byte bVar4;
    uint local_a4;
    char local_a0 [128];
    __pid_t local_14;

    bVar4 = 0;
    local_14 = fork();
    puVar3 = (undefined4 *)local_a0;
    for (iVar2 = 32; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + (uint)bVar4 * -2 + 1;
    }
    local_a4 = 0;
    if (local_14 == 0) {
        prctl(1,1);
        ptrace(PTRACE_TRACEME,0,0,0);
        puts("Give me some shellcode, k");
        gets(local_a0);
    }
    else {
        do {
            wait(&local_a4);
            if (((local_a4 & 0x7f) == 0) || ('\0' < (char)(((byte)local_a4 & 0x7f) + 1) >> 1)) {
                puts("child is exiting...");
                return 0;
            }
            lVar1 = ptrace(PTRACE_PEEKUSER,local_14,0x2c,0);
        } while (lVar1 != 0xb);
        puts("no exec() for you");
        kill(local_14,9);
    }
    return 0;
}
```

This seems like the usual BOF, that `gets` is sus, but with a little twist,
it's executed on a child process, but that shouldn't be important.

The binary is `32` bits so it should be easier.

## Explotation

Let's start with the usual pattern payload to calculate the offset:
```bash
gdb -q ./level04

set follow-fork-mode child

r

# Input the pattern
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 1614]
0x41326641 in ?? ()
```

So, if the EIP is `0x41326641`, the offset is `156`.

Let's do the usual `offset + address of env with shellcode`, I'm not gonnna
explain it again since it's the usual, the point of this level was just the
child.

Or that was I though, but after receiving a `"no exec() for you` output
message, I notice something, this is the parent process code:
```c
do {
  wait(&local_a4);
  if (((local_a4 & 0x7f) == 0) || ('\0' < (char)(((byte)local_a4 & 0x7f) + 1) >> 1)) {
    puts("child is exiting...");
    return 0;
  }
  lVar1 = ptrace(PTRACE_PEEKUSER,local_14,0x2c,0); // This line
} while (lVar1 != 0xb);
puts("no exec() for you");
kill(local_14,9);
```

That line is tracing something from the user area of the `local_14` (child)
process, but what? `0x2c` is the offset of the value is been readed, so, if
that value is `0xb`, the `no exec()` error is thrown.


Note that:
`PTRACE_PEEKDATA` is for program data (e.g. variables) and code.
`PTRACE_PEEKUSER` is for things like register values and other debug info.

As defined on the linux source code, this is the [user area for linux 3.13](https://github.com/torvalds/linux/blob/v3.13/arch/x86/include/asm/user_32.h)
(you can check the kernel running with `uname -r`):
```c
struct user_regs_struct {
	unsigned long	bx; // 0
	unsigned long	cx; // 4
	unsigned long	dx; // 8
	unsigned long	si; // 12
	unsigned long	di; // 16
	unsigned long	bp; // 20
	unsigned long	ax; // 24
	unsigned long	ds; // 28
	unsigned long	es; // 32
	unsigned long	fs; // 36
	unsigned long	gs; // 40
	unsigned long	orig_ax; // 44
	unsigned long	ip; // 48
	unsigned long	cs; // 52
	unsigned long	flags; // 56
	unsigned long	sp; // 60
	unsigned long	ss; // 64
};
```

So, a `0x2c` (`44`), would be `orig_ax`, but what's this register?

[ORIG_AX](https://stackoverflow.com/questions/6468896/why-is-orig-eax-provided-in-addition-to-eax/6469069)
is quite a deep kernel thing, let's just say it saves the original `eax` when a
`syscall` is done, and what's in `eax` when we do `syscall`?, exactly, the
`syscall` code.

It seems like the code later checks if `orig_ax` is `11`, that means if it's
`execve`.

So... yead, we can't call `execve` in our shellcode, let's search for an
alternative in shell-storm.

We don't have a lot of alternatives, the easier one would be just
[reading a file](https://shell-storm.org/shellcode/files/shellcode-73.html).

As always, check the script in `./resources/exploit.py`.
