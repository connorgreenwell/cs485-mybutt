#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "requests.h"
#include "storage.h"

void log_req(request* req, bool success) {
  printf("Secret Key = %d\n", req->secret);
  printf("Request Type = %s\n", req_name_from_type(req->type));
  if(req->type == REQ_LIST) {
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


void file_into_response(file* f, response* res) {

}

void serve(int connfd, int secret) {
  size_t n;
  bool success;

  request req;
  response resp;

  resp.status = RESP_OK;
  resp.size = 0;
  
  if((n = recv(connfd, &req, sizeof(request), 0)) != 0) {
    switch(req.type) {
    case REQ_STORE:
      success = store_file(req.filename, req.contents, req.size);
      break;
    case REQ_DELETE:
      success = delete_file(req.filename);
      break;
    case REQ_LIST:
      success = true;
      list_files(&resp);
      break;
    case REQ_GET:
      success = get_file(req.filename, &resp);
      break;
    }
    
    if (!success) {
      resp.status = RESP_ERROR;
    }
    
    log_req(&req, success);
    
    send(connfd, &resp, response_size(&resp), 0);
    
    success = false;
  }
}
