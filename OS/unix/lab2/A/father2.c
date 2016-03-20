#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

main()
{
  int pid, ppid, status;

  pid = getpid();
  ppid = getppid();
  printf(" f === Родитель породился\n");
  printf(" f === FATHER PARAM: pid = %i, ppid = %i\n", pid, ppid);

  printf(" f === Родитель порождает потомка\n");
  if (fork() == 0) execl("son2", "son2", NULL);

  printf(" f === Завершаем работу родителя\n");
  exit(1);
}
