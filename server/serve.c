#include "csapp.h"

#pragma pack(1)
struct request {
  int secret;
  int type;
  char filename[80];
  int size;
  //char* file;
};
#pragma pack(0)

void serve(int connfd, int secret) {
  size_t n; 
  char buf[MAXLINE]; 
  rio_t rio;

  struct request req;

  Rio_readinitb(&rio, connfd);
  while((n = Rio_readnb(&rio, &req, sizeof(struct request))) != 0) { //line:netp:echo:eof
    printf("server received %d bytes\n", (int)n);
    printf("sec: %d type: %d filename: %s\n", req.secret, req.type, req.filename);
  }
}
