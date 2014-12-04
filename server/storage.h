#ifndef _BUTT_STORAGE_H_
#define _BUTT_STORAGE_H_

#include <stdlib.h>
#include <stdbool.h>

#include "requests.h"

typedef struct file_struct {
  bool used;
  char name[FNAME_MAX];
  char contents[CONTENT_MAX];
  size_t size;
} file;

#define NUM_FILES 1000

void init_storage();
int find_index(char*);
int find_unused_index();
bool get_file(char*, file*);
bool store_file(char*, char*, size_t);
bool delete_file(char*);

#endif
