#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define KEY 4567
#define PERMS 0660

int main(int argc, char **argv)
{
  int id;
  int i;
  int *ptr;

  system("ipcs -m"); // Lists all shared memory.

  id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS); // Creates shared memory.

  system("ipcs -m"); // Lists shared memory again, will show newly-created shared memory.

  ptr = (int *) shmat(id, NULL, 0); // Sets ptr to point to location in shared memory.

  *ptr = 54; // Sets value in shared memory space.
  i = 54;  // Sets value in unshared memory space.

  if (fork() == 0) // Forks, enters child process.
  {
    (*ptr)++; // Increments value in shared memory.
    i++;  // Increments value in unshared memory.
    printf("Value of *ptr = %d\nValue of i = %d\n", *ptr, i); // Prints out the same value for both.
    exit(0);
  }
  else
  {
    wait(NULL);
    printf("Value of *ptr = %d\nValue of i = %d\n", *ptr, i); // Prints out incremented *ptr and unchanged i values.
    shmctl(id, IPC_RMID, NULL); // Closes shared memory.
  }
}
