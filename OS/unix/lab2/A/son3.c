#include <stdio.h>
#include <stdlib.h>

main()
{
  int pid, ppid;

  pid = getpid();
  ppid = getppid();

  printf(" s === Потомок породился\n");
  printf(" s === SON PARAM: pid = %i, ppid = %i\n", pid, ppid);

  printf(" s === Потомок завершается\n");
  exit(1);
}

