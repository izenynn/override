# Walkthrough

## Reversing

```c
int decrypt(EVP_PKEY_CTX *ctx,uchar *out,size_t *outlen,uchar *in,size_t inlen)
{
    char cVar1;
    uint uVar2;
    int iVar3;
    undefined4 *puVar4;
    byte *pbVar5;
    int in_GS_OFFSET;
    bool bVar6;
    bool bVar7;
    uint local_2c;
    undefined4 local_21;
    undefined4 local_1d;
    undefined4 local_19;
    undefined4 local_15;
    undefined local_11;
    int local_10;

    local_10 = *(int *)(in_GS_OFFSET + 0x14);
    local_21 = 0x757c7d51;
    local_1d = 0x67667360;
    local_19 = 0x7b66737e;
    local_15 = 0x33617c7d;
    local_11 = 0;
    uVar2 = 0xffffffff;
    puVar4 = &local_21;
    do {
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        cVar1 = *(char *)puVar4;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
    } while (cVar1 != '\0');
    local_2c = 0;
    while( true ) {
        bVar6 = local_2c < ~uVar2 - 1;
        bVar7 = local_2c == ~uVar2 - 1;
        if (!bVar6) break;
        *(byte *)((int)&local_21 + local_2c) = (byte)ctx ^ *(byte *)((int)&local_21 + local_2c);
        local_2c = local_2c + 1;
    }
    iVar3 = 0x11;
    puVar4 = &local_21;
    pbVar5 = (byte *)"Congratulations!";
    do {
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        bVar6 = *(byte *)puVar4 < *pbVar5;
        bVar7 = *(byte *)puVar4 == *pbVar5;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
        pbVar5 = pbVar5 + 1;
    } while (bVar7);
    if ((!bVar6 && !bVar7) == bVar6) {
        iVar3 = system("/bin/sh");
    }
    else {
        iVar3 = puts("\nInvalid Password");
    }
    if (local_10 == *(int *)(in_GS_OFFSET + 20)) {
        return iVar3;
    }
    __stack_chk_fail();
}

void test(int param_1,int param_2)
{
    EVP_PKEY_CTX *pEVar1;
    uchar *in_stack_ffffffd8;
    size_t *in_stack_ffffffdc;
    uchar *in_stack_ffffffe0;
    size_t in_stack_ffffffe4;

    pEVar1 = (EVP_PKEY_CTX *)(param_2 - param_1);
    switch(pEVar1) {
    default:
        pEVar1 = (EVP_PKEY_CTX *)rand();
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        break;
    case (EVP_PKEY_CTX *)0x1:
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        break;
    case (EVP_PKEY_CTX *)0x2:
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        break;
    case (EVP_PKEY_CTX *)0x3:
        jdecrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        jbreak;
    case (EVP_PKEY_CTX *)0x4:
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        break;
    case (EVP_PKEY_CTX *)0x5:
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        break;
    case (EVP_PKEY_CTX *)0x6:
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        break;
    case (EVP_PKEY_CTX *)0x7:
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        break;
    case (EVP_PKEY_CTX *)0x8:
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        break;
    case (EVP_PKEY_CTX *)0x9:
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        break;
    case (EVP_PKEY_CTX *)0x10:
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        break;
    case (EVP_PKEY_CTX *)0x11:
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        break;
    case (EVP_PKEY_CTX *)0x12:
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        break;
    case (EVP_PKEY_CTX *)0x13:
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        break;
    case (EVP_PKEY_CTX *)0x14:
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
        break;
    case (EVP_PKEY_CTX *)0x15:
        decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    }
    return;
}

int main(void)
{
    uint __seed;
    int iStack_14;

    __seed = time((time_t *)0x0);
    srand(__seed);
    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");
    printf("Password:");
    __isoc99_scanf("%d", iStack_14);
    test(iStack_14,322424845);
    return 0;
}
```

Okey... I start te realize why this project is after `rainfall`, it seemed
esay initially...

What we have here is a very fun program that asks for a number, and then calls
a `test` function passing our number and `322424845`.

This `test` function, then substracts our number from `322424845`, and if the
number is between `0x15` and `0x10`, or `0x9` and `0x1`, it will call the
`decrypt` function with the result of the substraction. Notice that if the
result is not in range, it will call `decrypt` with a random generated number,
that way we won't have control over what argument pass to `decrypt`, so it's
probably best to input a number for a fixed case.

Then, `decrypt` function will perform a `XOR` operation, on our number and the
string `""`, to then perform a `strncmp` with the string `"Congratulations!"`.

If it success, it will execute `/bin/sh`.

So, in short, we need to find a suitable input that when passed through this
mess, results in the string `"Congratulations!"`, and the shell gets executed.

What we know so far is that the input number must be in a certain range, at
least we can assume that, because it wouldn't make sense to bruteforce this
until the `rand` returns a valid number.

*Note: the binary also has 2 other functions but they are never called.*

## Explotation

Bruteforce, the range is `0x1 - 0x15`, in decimal `1 - 21`, so let's just
bruteforce all possibilites. Since the `decrypt` function prints
`Invalid Password` in case we fail, we can just create a script that keeps
trying if it reads that string.

Check the script at `./resources/exploit.py`.

Run it, and get the flag!
