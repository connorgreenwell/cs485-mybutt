#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */

#include "requests.h"

int main(int argc, char **argv) {
  int port;
  char *host;
  FILE* fd;

  request req;
  req.size = 0;

  if (argc != 6) {
    fprintf(stderr, "usage: %s <req_type> <host> <port> <secret> [<file>]\n", argv[0]);
    exit(0);
  }

  req.type = req_type_from_name(argv[1]);
  host = argv[2];
  port = atoi(argv[3]);
  req.secret = atoi(argv[4]);
  
  if (req.type != REQ_LIST) {
    strncpy(req.filename, argv[5], FNAME_MAX);
  }

  switch (req.type) {
    case REQ_STORE:
      fd = fopen(req.filename, "r");
      req.size = fread(req.contents, sizeof(char), CONTENT_MAX, fd);
      close(fd);
      break;
    case REQ_GET: 
      break;
    case REQ_DELETE: 
      break;
    case REQ_LIST: 
      break;
  }

  send_request(&req, host, port);
  exit(0);
}

int send_request(request* req, char* host, int port) {
  int sock;
  int clientfd;

  if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    fprintf(stderr,"Failed to get socket\n");
    exit(-2);
  }

  struct sockaddr_in servAddr;
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = inet_addr(host);
  servAddr.sin_port = htons(port);

  if(connect(sock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0) {
    fprintf(stderr,"Failed to connect to server\n");
    exit(-3);
  }

  send(sock, req, store_request_size(req), 0);

  close(sock);

  exit(0);
}
