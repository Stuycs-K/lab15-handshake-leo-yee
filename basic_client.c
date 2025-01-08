#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;
  from_server = client_handshake( &to_server );
  char buff[HANDSHAKE_BUFFER_SIZE];
  sprintf(buff, "%d", getpid());
  while(1){
    write(to_server, buff, HANDSHAKE_BUFFER_SIZE);
    printf("sending [%s] to server_setup\n", buff);
    sleep(1);
  }
}
