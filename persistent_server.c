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

int main() {
  signal(SIGINT, sig_handler);
  while(1){
    int to_client;
    int from_client;
    from_client = server_handshake( &to_client );
    char final[HANDSHAKE_BUFFER_SIZE];
    while(read(from_client, final, HANDSHAKE_BUFFER_SIZE)){
      printf("from client: %s\n", final);
    }
    printf("%s\n \n", "disconnected");
    close(from_client);
    close(to_client);
  }
}
