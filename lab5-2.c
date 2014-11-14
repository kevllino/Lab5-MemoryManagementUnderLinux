#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define KEY 4567
#define KEY2 4568
#define KEY3 4569
#define KEY4 4570
#define KEY5 4571
#define PERMS 0660

int main(int argc, char **argv)
{
  int a = 6, b = 5, c = 4, d = 3, e = 2, f = 1;
  int id;
  int id2;
  int id3;
  int id4;
  int id5;
  int *ptr;
  int *ptr2;
  int *ptr3;
  int *ptr4;
  int *ptr5;

  id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS);
  id2 = shmget(KEY2, sizeof(int), IPC_CREAT | PERMS);
  id3 = shmget(KEY3, sizeof(int), IPC_CREAT | PERMS);
  id4 = shmget(KEY4, sizeof(int), IPC_CREAT | PERMS);
  id5 = shmget(KEY5, sizeof(int), IPC_CREAT | PERMS);

  ptr = (int *) shmat(id, NULL, 0);
  ptr2 = (int *) shmat(id2, NULL, 0);
  ptr3 = (int *) shmat(id3, NULL, 0);
  ptr4 = (int *) shmat(id4, NULL, 0);
  ptr5 = (int *) shmat(id5, NULL, 0);

  if (fork() == 0)
  {
    if (fork() == 0)
    {
      *ptr = a + b;
      exit(0);
    }
    else
    {
      *ptr2 = c - d;

      wait(NULL);
      
      *ptr5 = *ptr * (*ptr2);

      exit(0);
    }
  }
  else
  {
    *ptr3 = e + f;

    wait(NULL);
    *ptr4 = *ptr5 + *ptr3;
    printf("%d * %d + %d  = %d\n", *ptr, *ptr2, *ptr3, *ptr4);

    shmctl(id, IPC_RMID, NULL);
    shmctl(id2, IPC_RMID, NULL);
    shmctl(id3, IPC_RMID, NULL);
    shmctl(id4, IPC_RMID, NULL);
    shmctl(id5, IPC_RMID, NULL);
  }
}
