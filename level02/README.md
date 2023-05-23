# Walkthrough

## Reversing

```c
int main(void)
{
    int iVar1;
    size_t sVar2;
    long lVar3;
    undefined8 *puVar4;
    char userpass [112];
    char pass [48];
    char username [96];
    int local_14;
    FILE *fpass;

    puVar4 = (undefined8 *)username;
    for (lVar3 = 12; lVar3 != 0; lVar3 = lVar3 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
    }
    *(undefined4 *)puVar4 = 0;
    puVar4 = (undefined8 *)pass;
    for (lVar3 = 5; lVar3 != 0; lVar3 = lVar3 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
    }
    *(undefined *)puVar4 = 0;
    puVar4 = (undefined8 *)userpass;
    for (lVar3 = 12; lVar3 != 0; lVar3 = lVar3 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
    }
    *(undefined4 *)puVar4 = 0;

    fpass = fopen("/home/users/level03/.pass","r");
    if (fpass == (FILE *)0x0) {
        fwrite("ERROR: failed to open password file\n",1,0x24,stderr);
        exit(1);
    }

    sVar2 = fread(pass,1,41,fpass);
    local_14 = (int)sVar2;
    sVar2 = strcspn(pass,"\n");
    pass[sVar2] = '\0';
    if (local_14 != 41) {
        fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
        fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
        exit(1);
    }
    fclose(fpass);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");
    printf("--[ Username: ");
    fgets(username,100,stdin);
    sVar2 = strcspn(username,"\n");
    username[sVar2] = '\0';
    printf("--[ Password: ");
    fgets(userpass,100,stdin);
    sVar2 = strcspn(userpass,"\n");
    userpass[sVar2] = '\0';
    puts("*****************************************");
    iVar1 = strncmp(pass,userpass,41);
    if (iVar1 == 0) {
        printf("Greetings, %s!\n",username);
        system("/bin/sh");
        return 0;
    }
    printf(username);
    puts(" does not have access!");
    exit(1);
}
```

It initializes 3 buffers with `0`s, and then opens the `.pass` file we need into
a `FILE` struct.

Then it asks for user and password, and to be able to compare you password with
the one in the `.pass` fie, it loads the file into a local variable.

So, we have the password in the stack... And not so much later, if we fail the
password, it prints our input user! (`printf(username)`), so this is another
format string vulnerability...

## Exploit

Since the binary does not have PIE, the `pass` buffer in which the password
is saved, will always be in the same location, so let's play a little with
the `printf` and discover where it's stored.

Just do some `%N$lx` (since it's a 64 bits binary), and print the memory.

By printing the memory and reversing it (it's little-endian, remember), we find
a string that seems like a flag.

*Look at the script in `./resources/exploit.sh`, of course this is automated,
I'm not bored enought to do it manually.*

Also, looking at the assembly, we can see that the password is between the
`username` we input, and the `password` we also input, so the script greps
this and output what's it's in between (the `.pass` file content).

Run `./resources/exploit.sh`.
