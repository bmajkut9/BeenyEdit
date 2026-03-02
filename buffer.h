#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LineNode {
  char *text; // 
  struct LineNode *next;
  struct LineNode *prev;
} LineNode; // will hold line text and line links

typedef struct Buffer {
  LineNode *first;
  LineNode *last;
  int num_lines;
} Buffer; // data structure for holding text in memory

Buffer *buffer_create(void) {
  Buffer *bufferPtr = malloc(sizeof(Buffer)); //struct Buffer *bufferPtr = (struct Buffer*)malloc(sizeof(struct Buffer));
  if (bufferPtr == NULL) perror("couldn't create buffer");
  bufferPtr->first = NULL; //*bufferPtr[1] = NULL;
  bufferPtr->last = NULL;
  bufferPtr->num_lines = 0;

  return bufferPtr;
}

LineNode *line_create(LineNode* nextPtr, LineNode* prevPtr, char* textPtr) {
  LineNode *lineNodePtr = malloc(sizeof(LineNode));
  if (lineNodePtr == NULL) perror("couldn't create buffer");
  lineNodePtr->next = nextPtr;
  lineNodePtr->prev = prevPtr;
  
  
  lineNodePtr->text = malloc(strlen(textPtr) + 1);
  /*
  for (int i = 0; i <= strlen(textPtr); i++) { 
    lineNodePtr->text[i] = textPtr[i];
  } 
  */
  strcpy(lineNodePtr->text, textPtr);

  return lineNodePtr;
}

void buffer_append_line(Buffer* bufferPtr, char* lineStartPtr) {
  LineNode *lineNodePtr = line_create(NULL, bufferPtr->last, lineStartPtr);
  if (bufferPtr->first == NULL) {
    bufferPtr->first = lineNodePtr;
  } else { // because if head isn't null, that means at least tail = head
    bufferPtr->last->next = lineNodePtr;
  }
  bufferPtr->last = lineNodePtr;
  bufferPtr->num_lines++;
}

void buffer_display(Buffer *bufferPtr) {
  LineNode* curr = bufferPtr->first;
  for (int i = 0; i < bufferPtr->num_lines; i++) {
    printf("%3d | %s", i+1, curr->text);
    curr = curr->next;
  }
}

Buffer *buffer_load_file(char* fileName) {
  FILE* filePtr = fopen(fileName, "r");
  char buffer[1024];
  char* line;

  Buffer* bufferPtr = buffer_create();

  while(fgets(buffer, sizeof(buffer), filePtr) != NULL) {
    int len = strlen(buffer);
    buffer_append_line(bufferPtr, buffer); 
  }

  return bufferPtr;
}

void buffer_free(Buffer* bufferPtr) {
  // free char arrays
  // free linenode structs
  // free buffer

  LineNode* head = bufferPtr->first;
  LineNode* curr = head;
  LineNode* temp;
  while (curr != NULL) {
    temp = curr->next;
    free(curr->text);
    free(curr);
    curr = temp; 
  }

  free(bufferPtr);

}

