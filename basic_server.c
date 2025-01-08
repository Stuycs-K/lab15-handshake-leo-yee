#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;
  from_client = server_handshake( &to_client );
  char final[HANDSHAKE_BUFFER_SIZE];
  read(from_client, final, HANDSHAKE_BUFFER_SIZE);
  printf("%s\n", final);
}
