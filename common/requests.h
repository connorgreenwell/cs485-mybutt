#include <stdint.h>
#include <stdlib.h>

#define FNAME_MAX 80
#define CONTENT_MAX 100*1024

#pragma pack(1)
typedef struct base_request_struct {
  int secret;
  int type;
} base_request;
#pragma pack(0)

#define REQ_STORE 0
#pragma pack(1)
typedef struct store_request_struct {
  base_request base;
  char filename[FNAME_MAX];
  uint32_t filesize;
  char contents[CONTENT_MAX];
} store_request;
#pragma pack(0)

size_t store_request_size(store_request* req) {
  return sizeof(base_request)
    + FNAME_MAX * sizeof(char)
    + sizeof(uint32_t)
    + sizeof(char) * req->filesize;
}
