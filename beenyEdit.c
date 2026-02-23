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
  FILE *fileptr;

  if ((fileptr = fopen(filename, "r")) == NULL) { // fopen returns pointer to FILE struct
    // Inside fopen, it does something like:
    // char *ptr = filename;  // ptr = 0x1000
    // while (*ptr != '\0') {
    //     // Read *ptr (the character at that address)
    //     ptr++;  // Move to next character
    // }

    perror("File content null");
    return 1;
  }

  char buffer[1024];
  int lineCount = 0;
  while (fgets(buffer, sizeof(buffer), fileptr) != NULL) {
    lineCount++;
  }

  rewind(fileptr);

  char **linePtrs = malloc(lineCount * sizeof(char *));
  if (linePtrs == NULL) {
    perror("Couldn't allocate linePtrs");
    fclose(fileptr);
    return 1;
  }

  for (int i = 0; i < lineCount; i++) {
    fgets(buffer, sizeof(buffer),
          fileptr); // puts line into buffer just from call

    int len = strlen(buffer);
    char *lineArr = malloc((len + 1) * sizeof(char));
    if (lineArr == NULL) {
      perror("line memory allocation failed");
      fclose(fileptr);
      return 1;
    }

    for (int j = 0; j <= len; j++) { // null terminator is included in buffer
      lineArr[j] = buffer[j];
    }

    linePtrs[i] = lineArr; // value of lineArr is actually &lineArr[0]
  }

  for (int i = 0; i < lineCount; i++) {
    printf("%3d | %s", i + 1,
           linePtrs[i]); // i think \n would be included in the char array
  }






  for (int i = 0; i < lineCount; i++) {
    free(linePtrs[i]);
  }
  free(linePtrs);

  fclose(fileptr);
  return 0;
}
