#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  // printf("%s\n", "hi");
  int from_client;
  mkfifo(WKP, 0666);
  from_client = open(WKP, O_RDONLY);
  remove(WKP);

  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  printf("%s\n", "start");
  int from_client = server_setup();
  int wk = from_client;
  printf("[server]from client fd:%d\n", from_client);
  char buffer[HANDSHAKE_BUFFER_SIZE];
  read(from_client, buffer, HANDSHAKE_BUFFER_SIZE);
  printf("[server]from client:%s\n", buffer);
  int fd = open(buffer, O_WRONLY);
  *to_client = fd;
  write(fd, buffer, HANDSHAKE_BUFFER_SIZE);
  char final[HANDSHAKE_BUFFER_SIZE];
  read(wk, final, HANDSHAKE_BUFFER_SIZE);
  printf("[server]from client:%s\n", final);


  printf("%s\n", "handshake complete");
  return wk;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;
  char buffer[HANDSHAKE_BUFFER_SIZE];
  char pip[HANDSHAKE_BUFFER_SIZE];
  sprintf(pip, "%d", getpid());
  printf("[client] pipe:%s\n", pip);
  mkfifo(pip, 0666);
  int fd = open(WKP, O_WRONLY);
  int wk = fd;
  *to_server = wk;
  write(fd, pip, HANDSHAKE_BUFFER_SIZE);
  fd = open(pip, O_RDONLY);
  //blocks
  remove(pip);
  read(fd, buffer, HANDSHAKE_BUFFER_SIZE);
  printf("[client]from server:%s\n", buffer);
  // sscanf(buffer,"%d", &from_server);
  // fd = open(pip, O_WRONLY);
  // char n[HANDSHAKE_BUFFER_SIZE];
  write(wk, "ack", HANDSHAKE_BUFFER_SIZE);
  // read(fd, n, HANDSHAKE_BUFFER_SIZE);
  // printf("%s\n", n);
  return fd;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}
