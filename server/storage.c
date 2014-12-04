#include <stdbool.h>
#include <string.h>

#include "requests.h"
#include "storage.h"

file files[NUM_FILES];

void init_storage() {
  for(int i = 0; i < NUM_FILES; i++) {
    files[i].used = false;
  }
}

int find_index(char* name) {
  for(int i = 0; i < NUM_FILES; i++) {
    if(files[i].used && strcmp(files[i].name, name) == 0) {
      return i;
    }
  }
  return -1;
}

int find_unused_index() {
  for(int i = 0; i < NUM_FILES; i++) {
    if(!files[i].used) return i;
  }
  return -1;
}

bool store_file(char* name, char* contents, size_t content_size) {
  int index = find_index(name);
  if(index == -1) {
    index = find_unused_index();
    if(index == -1) {
      return false;             /* nowhere to store it */
    }
  }

  files[index].used = true;
  files[index].size = content_size;
  strncpy(files[index].name, name, FNAME_MAX);
  memcpy(files[index].contents, contents, content_size);
  return true;
}

bool delete_file(char* name) {
  int index = find_index(name);
  if(index == -1) {
    return false;
  } else {
    files[index].used = false;
    return true;
  }
}

bool get_file(char* name, file* f) {
  int index = find_index(name);
  if(index == -1) {
    f = NULL;
    return false;
  } else {
    *f = files[index];
    return true;
  }
}
