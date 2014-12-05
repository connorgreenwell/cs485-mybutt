#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */

#include "requests.h"

void print_usage(char* name) {
    fprintf(stderr, "usage: %s <req_type> <host> <port> <secret> [<file>]\n", name);
    exit(0);
}

void handle_response(response* resp) {
  if (resp->status == RESP_ERROR) {
    printf("ERROR\n");
  }

  if (resp->size > 0) {
    printf("%s", resp->contents);
  }
}

int send_request(request* req, char* host, int port, response* resp) {
  int sock;
  int clientfd;

  if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    fprintf(stderr,"Failed to get socket\n");
    return -2;
  }

  struct sockaddr_in servAddr;
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = inet_addr(host);
  servAddr.sin_port = htons(port);

  if(connect(sock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0) {
    fprintf(stderr,"Failed to connect to server\n");
    return -3;
  }

  send(sock, req, request_size(req), 0);
  
  if (read(sock, resp, CONTENT_MAX) < 0) {
    close(sock);
    return -4;
  }

  handle_response(resp);

  close(sock);

  return 1;
}

int main(int argc, char **argv) {
  int port;
  char *host;
  FILE* fd;

  if (argc < 5) print_usage(argv[0]);

  request req;
  req.size = 0;
  req.type = req_type_from_name(argv[1]);

  host = argv[2];
  port = atoi(argv[3]);
  req.secret = atoi(argv[4]);

  if (req.type == REQ_LIST) {
    if (argc != 5) print_usage(argv[0]);
  } else {
    if (argc != 6) print_usage(argv[0]);
    strncpy(req.filename, argv[5], FNAME_MAX);
  }

  switch (req.type) {
    case REQ_STORE:
      fd = fopen(req.filename, "r");
      req.size = fread(req.contents, sizeof(char), CONTENT_MAX, fd);
      fclose(fd);
      break;
    case REQ_GET:
      break;
    case REQ_DELETE:
      break;
    case REQ_LIST:
      break;
  }
  
  response resp;

  if (send_request(&req, host, port, &resp) < 0) {
    exit(-5);
  }
 
  exit(1);
}
