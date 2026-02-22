#include <stdio.h>

typedef struct {
  char *text; // text line - array of chars
  struct LineNode *next;
  struct LineNode *prev;
} LineNode; // will hold line text and line links

typedef struct {
  LineNode *first;
  LineNode *last;
  int num_lines;
} Buffer; // data structure for holding text in memory

Buffer *buffer_create(void) {}

// line_create
// buffer_append_line
// buffer_display
// buffer_load_file
// buffer free
