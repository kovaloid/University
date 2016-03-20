#include <stdio.h>
#include <unistd.h>

main()
{
  int pid, ppid, status;

  pid = getpid();
  ppid = getppid();
  printf(" f === Родитель породился\n");
  printf(" f === FATHER PARAM: pid = %i, ppid = %i\n", pid, ppid);

  printf(" f === Родитель порождает потомка\n");
  if (fork() == 0) execl("son3", "son3", NULL);

  printf(" f === Родитель выполняется...\n");
  sleep(5);

  printf(" f === Вывод команды ps:\n");
  system("ps xf");

  printf(" f === Завершаем работу родителя\n");
}
