#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "requests.h"

void log_req(store_request* req, bool success) {
  printf("Secret Key = %d\n", req->base.secret);
  printf("Request Type = %s\n", req_name_from_type(req->base.type));
  if(req->base.type == REQ_LIST) {
    printf("Filename = NONE\n");
  } else {
    printf("Filename = %s\n", req->filename);
  }

  if(success) {
    printf("Operation Status = success\n");
  } else {
    printf("Operation Status = error\n");
  }
  printf("--------------------------\n");
}

void serve(int connfd, int secret) {
  size_t n;
  bool success;

  base_request base_req;
  store_request store_req;

  while((n = recv(connfd, &store_req, sizeof(store_request), 0)) != 0) {
    switch(base_req.type) {
    case REQ_STORE:
      break;
    case REQ_DELETE:
      break;
    case REQ_LIST:
      break;
    case REQ_GET:
      break;
    }
    log_req(&store_req, success);
    success = false;
  }
}
