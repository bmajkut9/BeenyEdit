#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>", argv[0]);
  }

  char *filename =
      argv[1]; // filename and argv[1] are pointers to the start of the char
               // array for given arg, this is good because most functions
               // expect a pointer and will automatically iterate through memory
               // until hitting the null terminator

  Buffer *fileBuffer = buffer_load_file(filename);
  buffer_display(fileBuffer);
  buffer_free(fileBuffer);
  return 0;
}
