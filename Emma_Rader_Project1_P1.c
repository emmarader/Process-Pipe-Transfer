// Emma Rader. Project 1

// C program to demonstrate use of fork() and pipe()

// Header files
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// main function
int main() {

  // store both pipe ends
  int fd[2];

  // initialize array
  int a[] = {3, 8, 12, 21, 1, 7, 23, 18, 15, 10};
  pid_t p;

  // check pipe values
  if (pipe(fd) == -1) {
    fprintf(stderr, "Pipe Failed");
    return 1;
  }

  // check fork value
  p = fork();

  if (p < 0) {
    fprintf(stderr, "fork Failed");
    return 1;
  }

  // Child process
  else if (p == 0) {

    // Close reading end of first pipe
    close(fd[0]);

    int val = 0;
    for (int i = 0; i < 5; i++) {
      val += a[i];
    }

    // Write value to end of first pipe
    write(fd[1], &val, sizeof(val));

    printf("Sum value from child process: %d\n", val);

    close(fd[1]);

  }

  // Parent process
  else {
    // Close writing end of first pipe
    close(fd[1]);

    int sumx = 0;
    for (int i = 5; i < 10; i++) {
      sumx += a[i];
    }
    printf("Sum value from parent process: %d\n", sumx);

    // Wait for child to finish
    wait(NULL);

    int val;

    // Read val to end of pipe
    read(fd[0], &val, sizeof(val));
    sumx += val;

    printf("Total sum value: %d\n", sumx);
    close(fd[0]);
  }
}