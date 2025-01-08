#include "pipe_networking.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("\n[server]: SIGINT");
    remove(WKP);
    exit(0);
  }
}
// int server_handshake(int *to_client) {
//   printf("%s\n", "start");
//   int from_client = server_setup();
//   int wk = from_client;
//   printf("[server]from client fd:%d\n", from_client);
//   char buffer[HANDSHAKE_BUFFER_SIZE];
//   read(from_client, buffer, HANDSHAKE_BUFFER_SIZE);
//   printf("[server]from client:%s\n", buffer);
//   int fd = open(buffer, O_WRONLY);
//   *to_client = fd;
//   write(fd, buffer, HANDSHAKE_BUFFER_SIZE);
//   char final[HANDSHAKE_BUFFER_SIZE];
//   read(wk, final, HANDSHAKE_BUFFER_SIZE);
//   printf("[server]from client:%s\n", final);
//   printf("%s\n", "handshake complete");
//   return wk;
// }

int main() {
  signal(SIGINT, sig_handler);
  while(1){
    int to_client;
    int from_client;
    //server
    mkfifo(WKP, 0666);
    from_client = open(WKP, O_RDONLY);
    remove(WKP);
    printf("[server] client connected\n");
    //subserver
    pid_t p = fork();
    if (p == 0){
      //handshake
      char hs[HANDSHAKE_BUFFER_SIZE];
      read(from_client, hs, HANDSHAKE_BUFFER_SIZE);
      int fd = open(hs, O_WRONLY);
      to_client = fd;
      write(fd, hs, HANDSHAKE_BUFFER_SIZE);
      char final[HANDSHAKE_BUFFER_SIZE];
      read(from_client, final, HANDSHAKE_BUFFER_SIZE);

      char buffer[HANDSHAKE_BUFFER_SIZE];
      while (read(from_client, buffer, sizeof(buffer)) > 0) {
        printf("[subserver %d]: %s\n", getpid(), buffer);
        sleep(1);
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
