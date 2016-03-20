#include <stdio.h>

main()
{
  int pid, ppid;

  pid = getpid();
  ppid = getppid();

  printf("\n s === Потомок породился\n");
  printf(" s === SON PARAM: pid = %i, ppid = %i\n", pid, ppid);

  printf(" s === Потомок выполняется...\n");
  sleep(5);

  printf(" s === Вывод команды ps:\n");
  system("ps xf");

  printf(" s === Потомок выполнился и завершается\n");
  printf(" Чтобы выйти нажмите Ctrl+C...\n");
}

