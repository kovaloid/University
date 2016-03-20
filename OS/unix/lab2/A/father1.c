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
  if (fork() == 0) execl("son1", "son1", NULL);

  printf(" f === Блокируем родителя пока не завершится потомок\n");
  wait(&status);
  printf(" f === Завершаем работу родителя\n");
}
