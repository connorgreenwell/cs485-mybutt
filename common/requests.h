#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define FNAME_MAX 80
#define CONTENT_MAX 100*1024

#define REQ_GET 0
#define REQ_STORE 1
#define REQ_DELETE 2
#define REQ_LIST 3

#pragma pack(1)
typedef struct request_struct {
  int secret;
  int type;
  char filename[FNAME_MAX];
  uint32_t size;
  char contents[CONTENT_MAX];
} request;
#pragma pack(0)

size_t store_request_size(request* req) {
  return sizeof(request)
    + FNAME_MAX * sizeof(char)
    + sizeof(uint32_t)
    + sizeof(char) * req->size;
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
