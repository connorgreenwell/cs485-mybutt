#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "requests.h"

size_t request_size(request* req) {
  return sizeof(request)
    + FNAME_MAX * sizeof(char)
    + sizeof(uint32_t)
    + sizeof(char) * req->size;
}

size_t response_size(response* resp) {
  return sizeof(response)
    + FNAME_MAX * sizeof(char)
    + sizeof(uint32_t)
    + sizeof(char) * resp->size;
}

int req_type_from_name(char* name) {
  if(strncmp(name, "get", 3) == 0) {
    return REQ_GET;
  } else if(strncmp(name, "put", 3) == 0) {
    return REQ_STORE;
  } else if(strncmp(name, "del", 3) == 0 ||
            strncmp(name, "rm", 2) == 0) {
    return REQ_DELETE;
  } else if(strncmp(name, "list", 4) == 0 ||
            strncmp(name, "ls", 2) == 0) {
    return REQ_LIST;
  }
  return -1;
}

char* req_name_from_type(int type) {
  switch(type) {
  case REQ_GET:
    return "get";
  case REQ_STORE:
    return "put";
  case REQ_DELETE:
    return "del";
  case REQ_LIST:
    return "list";
  default:
    return "unk";
  }
}
