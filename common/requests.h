#ifndef _BUTT_REQUESTS_H_
#define _BUTT_REQUESTS_H_

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

#pragma pack(1)
typedef struct response_struct {
} response;
#pragma pack(0)

size_t store_request_size(request* req);
int req_type_from_name(char* name);
char* req_name_from_type(int type);

#endif
