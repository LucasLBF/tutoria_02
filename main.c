#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("/*** Starting parent process ***/\n");
  int pipeFileDescriptors[2];
  char message[20] = "Message from parent";
  char readMessage[20];
  int bytesWritten;
  int returnStatus = pipe(pipeFileDescriptors);

  if (returnStatus == -1) {
    printf("Failed to create pipe\n");
    return 1;
  }
  printf("Writing message to pipe...\n");
  bytesWritten = write(pipeFileDescriptors[1], message, sizeof(char) * 20);
  printf("Wrote %d bytes to pipe\n", bytesWritten);
  int pid = fork();
  // child process
  if (pid == 0) {
    printf("/*** Entering child process ***/\n");
    read(pipeFileDescriptors[0], readMessage, sizeof(char) * 20);
    printf("Reading message from pipe: %s\n", readMessage);
    printf("/*** Exiting child process ***/\n");
  } else { // parent process
    wait(NULL);
    printf("/*** Back to parent process ***/\n");
    printf("Quitting...\n");
    return 0;
  }
}
