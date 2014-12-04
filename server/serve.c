#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "requests.h"

void serve(int connfd, int secret) {
  size_t n;

  base_request base_req;
  store_request store_req;

  while(recv(connfd, &base_req, sizeof(base_request), MSG_PEEK) != 0) {
    switch(base_req.type) {
      case REQ_STORE:
        n = recv(connfd, &store_req, sizeof(store_request), 0);
        printf("server received %d bytes\n", (int)n);
        printf("sec: %d type: %d filename: %s\n", store_req.base.secret, store_req.base.type, store_req.filename);
        break;
    }
  }

  /* while((n = recv(&connfd, &req, sizeof(base_request), 0)) != 0) { //line:netp:echo:eof */
  /*   printf("server received %d bytes\n", (int)n); */
  /*   printf("sec: %d type: %d filename: %s\n", req.secret, req.type, req.filename); */
  /* } */
}
