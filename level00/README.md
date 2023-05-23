# Walkthrough

## Reversing

```c
int main(void)
{
    int buff[4];

    puts("***********************************");
    puts("* \t     -Level00 -\t\t  *");
    puts("***********************************");
    printf("Password:");
    __isoc99_scanf("%d", buff);
    if (buff[0] != 5276) {
        puts("\nInvalid Password!");
    }
    else {
        puts("\nAuthenticated!");
        system("/bin/sh");
    }
    return (int)(buff[0] != 5276);
}
```

Pretty simple binary, I don't need to explain, right?

## Explotation

Just to make sure, compile the `../resources/getsize.c` program to find out
the size of the built-in types in the system.

This program reads an `int` and just compares it with `5276`, if it's true,
it gives a shell, so just execute and input `5276`.

One liner:
```bash
echo "5276" > /tmp/payload; cat /tmp/payload - | ./level00; rm -f /tmp/payload
```

In every excercise that's possible I will also include a script in
`./resources/exploit.sh`, to automate the explotatin completely, go check it
out!

*Note: the flag is on `/home/users/levelXX/.pass`.*
