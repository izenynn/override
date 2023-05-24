# Walkthrough

## Reversing

```c
int auth(char *username,uint userpass)
{
    size_t len;
    int ret;
    long isTraced;
    int i;
    uint pass;

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
    uint userpass;
    char username [32];

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

```

The `main` function is pretty simple, it asks for a `login`, and saves it into
a buffer, nothing is susceptible about BOF here. Then it also asks for a
`password` and calls the `auth` function with both `login` and `password` as
parameters.

If the `auth` function returns `0`, then the shell executes, so we'll need an
input that achieves that.

The `auth` function is the funny one.

This function checks that the length of the `username` is greater or equal
than `6`.

Then, the program checks if a character of the `username` is lower that `32`
(`' '`).

## Explotation

The binary has `NX` enabled so, no shellcode execution, nor that we'll need it,
we have a `system("/bin/sh")` already in the binary.

And it's a 32 bits binary again, I though `override` will have more complex
techniques like `ROP`, `ret2lbic`, etc. or at least more `x64` bits binaries,
but does not seems like it.

So far we know that the `username` needs a len of `6` at least, and can't have
spaces.

Let's input a random `username`, and with the debugger get the `serial` for
that user, so we can run it later with a good serial.

The only thing to notice here is that `ptrace`, we'll need to skip that
instruction.

```bash
gdb -q ./level06

# Place a breakpoint on `ptrace`
b *auth+109

# Before continuing let's place another bp on the `userpass == pass`, so
# the `pass` uint is already generated, and we can print it
b *auth+286

r

# Let's enter the input
-> Enter Login: yamato
-> Enter Serial: 42

# We reached the bp, let's jump the `else` (of the `ptrace` condition)
jump *0x080487ed

# Print pass (it's located on `ebp-0x14`, and it's `4` bytes, so `ebp-0x10`)
p *(int *)($ebp-0x10)
$1 = 6232827
```

Now, just run the program with the appropiate input, here's a python one-liner:
```bash
cat <(python -c "print 'yamato\n' + '6232827\n'") - | ./level06
```
