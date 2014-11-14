#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define KEY 4567
#define KEY2 4568
#define KEY3 4569
#define PERMS 0660

int main(int argc, char **argv)
{
  int a = 4, b = 3, c = 2, d = 1;
  int id;
  int id2;
  int id3;
  int *ptr;
  int *ptr2;
  int *ptr3;

  id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS);
  id2 = shmget(KEY2, sizeof(int), IPC_CREAT | PERMS);
  id3 = shmget(KEY3, sizeof(int), IPC_CREAT | PERMS);

  ptr = (int *) shmat(id, NULL, 0);
  ptr2 = (int *) shmat(id2, NULL, 0);
  ptr3 = (int *) shmat(id3, NULL, 0);

  if (fork() == 0)
  {
    *ptr = a + b;
    exit(0);
  }
  else
  {
    *ptr2 = c + d;

    wait(NULL);

    *ptr3 = *ptr - *ptr2;
    printf("%d - %d = %d\n", *ptr, *ptr2, *ptr3);
    shmctl(id, IPC_RMID, NULL);
    shmctl(id2, IPC_RMID, NULL);
    shmctl(id3, IPC_RMID, NULL);
  }
}
