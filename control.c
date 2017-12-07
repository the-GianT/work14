#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#define KEY 1247

int main(int argc, char *argv[])
{
  int fd = 0; // will hold file descriptor for semaphore

  if (strncmp(argv[1], "-c", 2) == 0) {
    if (argc == 2) {
      printf("Error: must specify the value to which to set the semaphore (e.g. control -c 4).\n");
    } else if (argc == 3) {
      fd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
      if (fd == -1) {
	printf("%s\n", strerror(errno));
	// exit(EXIT_FAILURE);
	// return 1;
      } else if (semctl(fd, 0, SETVAL, (int)strtol(argv[2], NULL, 10)) == -1) {
	printf("%s\n", strerror(errno));
	// exit(EXIT_FAILURE);
	// return 1;
      } else {
	printf("semaphore created: %d\n", fd);
      }
    } else {
      printf("Error: expected two arguments, but received %d.\n", argc - 1);
    }
  } else if (strncmp(argv[1], "-v", 2) == 0) {
    int semval = 0;
    
    if (argc == 2) {
      fd = semget(KEY, 0, 0);
      if (fd == -1) {
	printf("%s\n", strerror(errno));
	// exit(EXIT_FAILURE);
	// return 1;
      } else {
	semval = semctl(fd, 0, GETVAL);
	if (semval == -1) {
	  printf("%s\n", strerror(errno));
	  // exit(EXIT_FAILURE);
	  // return 1;
	}
      }
      
      printf("semaphore value: %d\n", semval);
    } else {
      printf("Error: expected one argument, but received %d.\n", argc - 1);
    }
  } else if (strncmp(argv[1], "-r", 2) == 0) {
    if (argc == 2) {
      fd = semget(KEY, 0, 0);
      if (fd == -1) {
	printf("%s\n", strerror(errno));
      } else if (semctl(fd, 0, IPC_RMID) == -1) {
	printf("%s\n", strerror(errno));
	// exit(EXIT_FAILURE);
	// return 1;
      } else {
	printf("semaphore removed\n");
      }
      
    } else {
      printf("Error: expected one argument, but received %d.\n", argc - 1);
    } // end if statement
  } // end if statement
  
  return 0;
}
