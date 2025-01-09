#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;
  from_server = client_handshake( &to_server );
  char buff[HANDSHAKE_BUFFER_SIZE] = "";
  sprintf(buff, "%d", getpid());
  write(to_server, buff, HANDSHAKE_BUFFER_SIZE);
  while(1){
    write(to_server, buff, HANDSHAKE_BUFFER_SIZE);
    printf("sending [%s] to server\n", buff);
    char new[HANDSHAKE_BUFFER_SIZE] = "";
    int n = read(from_server, new, HANDSHAKE_BUFFER_SIZE);
    printf("from server: %s\n", new);
    sleep(1);
  }
}
