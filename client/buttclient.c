#include "csapp.h"

#pragma pack(1)
typedef struct {
  int secret;
  int type;
  char filename[80];
  int size;
  char file[];
} request;
#pragma pack(0)

int main(int argc, char **argv) 
{
  int clientfd, port;
  char *host, buf[MAXLINE];
  rio_t rio;

  request req;
  req.type = 0;
  req.size = 0;
  
  if (argc != 5) {
    fprintf(stderr, "usage: %s <host> <port> <secret> <file>\n", argv[0]);
    exit(0);
  }
  host = argv[1];
  port = atoi(argv[2]);
  req.secret = atoi(argv[3]);
  strcpy(req.filename, argv[4]);

  clientfd = Open_clientfd(host, port);
  Rio_readinitb(&rio, clientfd);

  Rio_writen(clientfd, &req, sizeof(request));
  
  Close(clientfd); //line:netp:echoclient:close
  exit(0);
}
