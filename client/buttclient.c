#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */

#include "requests.h"

int main(int argc, char **argv)
{
  int clientfd, port;
  char *host;
  int sock;

  store_request req;
  req.base.type = REQ_STORE;
  req.filesize = 0;

  if (argc != 5) {
    fprintf(stderr, "usage: %s <host> <port> <secret> <file>\n", argv[0]);
    exit(0);
  }

  host = argv[1];
  port = atoi(argv[2]);
  req.base.secret = atoi(argv[3]);
  strncpy(req.filename, argv[4], FNAME_MAX);

  if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Failed to get socket\n");
    exit(-2);
  }

  struct sockaddr_in servAddr;
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = inet_addr(host);
  servAddr.sin_port = htons(port);

  if(connect(sock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0) {
    printf("Failed to connect to server\n");
    exit(-3);
  }

  send(sock, &req, store_request_size(&req), 0);

  close(sock);

  exit(0);
}
