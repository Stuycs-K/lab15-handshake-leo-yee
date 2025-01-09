#include "pipe_networking.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("\n[%d]: SIGINT\n", getpid());
    remove(WKP);
    exit(0);
  }
}

int main() {
  signal(SIGINT, sig_handler);
  printf("waiting for connection...\n");
  while(1){
    int to_client;
    int from_client;
    //server
    mkfifo(WKP, 0666);
    from_client = open(WKP, O_RDONLY);
    remove(WKP);
    printf("[server] new client connected\n");
    //subserver
    pid_t p = fork();
    if (p == 0){
      //handshake
      char hs[HANDSHAKE_BUFFER_SIZE] = "";
      read(from_client, hs, HANDSHAKE_BUFFER_SIZE);
      int fd = open(hs, O_WRONLY);
      to_client = fd;
      write(fd, hs, HANDSHAKE_BUFFER_SIZE);
      char final[HANDSHAKE_BUFFER_SIZE] = "";
      read(from_client, final, HANDSHAKE_BUFFER_SIZE);

      char buffer[HANDSHAKE_BUFFER_SIZE] = "";
      int b = read(from_client, buffer, 4);
      // printf("%d\n", b);
      int n = 0;
      while (read(from_client, buffer, sizeof(buffer)) > 0) {
        printf("[subserver %d]: %s\n", getpid(), buffer);
        write(to_client, buffer, HANDSHAKE_BUFFER_SIZE);
        sscanf(buffer, "%d", &n);
        n += 1;
        char new[HANDSHAKE_BUFFER_SIZE] = "";
        sprintf(new, "%d", n);
        write(to_client, new, sizeof(new));
        printf("sending to client: %s\n", new);
      }

      printf("[subserver %d] client disconnected\n", getpid());
      close(from_client);
      close(to_client);
      exit(0);
    }
    else{
      close(from_client);
    }
  }
}
