#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;
  // printf("%s\n", "hi");
  from_client = server_handshake( &to_client );
}
