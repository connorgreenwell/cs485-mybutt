#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */

#include "storage.h"

#define MAXPENDING 5

void serve(int, int);

int main(int argc, char **argv) {
  int listenfd, connfd, port, secret_key;
  socklen_t clientlen;
  struct sockaddr_in clientaddr;
  struct sockaddr_in servaddr;

  if (argc != 3) {
    fprintf(stderr, "usage: %s <port> <secret_key>\n", argv[0]);
    exit(0);
  }

  port = atoi(argv[1]);
  secret_key = atoi(argv[2]);

  if((listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    fprintf(stderr, "Could not obtain socket\n");
    exit(-1);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
    fprintf(stderr, "Could not bind to port\n");
    exit(-2);
  }

  if(listen(listenfd, MAXPENDING) < 0) {
    fprintf(stderr, "listen(...) call failed\n");
    exit(-4);
  }

  init_storage();

  while (1) {
    clientlen = sizeof(clientaddr);
    if((connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen)) < 0) {
      fprintf(stderr, "accept(...) call failed\n");
      exit(-3);
    }

    serve(connfd, secret_key);
    close(connfd);
  }
  exit(0);
}
