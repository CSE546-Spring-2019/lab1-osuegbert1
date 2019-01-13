#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[]) {
  FILE *input, *output;
  unsigned char buffer[BUFFER_SIZE];
  int fileSize = 0, count = 0, itemsRead;
  int i, bufferOffset, validDataSize;
  char *inputFilename, *searchString, *outputFilename;
  unsigned char searchChar;
  int searchStringLength;

  // check input
  if (argc != 4) {
    printf("Usage: count <input-filename> <search-string> <output-filename>\n");
    return (-1);
  }
  inputFilename = argv[1];
  searchString = argv[2];
  outputFilename = argv[3];
  // open files
  if ((input = fopen(inputFilename, "rb")) == NULL) {
    perror("Error");
    printf("Could not open %s\n", inputFilename);
    return (-1);
  }
  if ((output = fopen(outputFilename, "w")) == NULL) {
    perror("Error");
    printf("Could not open %s\n", outputFilename);
    return (-1);
  }

  searchChar = *searchString & 0xff;
  searchStringLength = strlen(searchString);
  bufferOffset = 0;
  // read until EOF
  // use an offset for possible rollover from previous read
  while ((itemsRead = fread(&buffer[bufferOffset], 1, BUFFER_SIZE - bufferOffset, input)) > 0) {
    fileSize += itemsRead;
    validDataSize = bufferOffset + itemsRead;
    bufferOffset = 0;
    for (i = 0; i < validDataSize; i++) {
      if (buffer[i] == searchChar) { // check for starting char
        if (validDataSize - i >= searchStringLength) { // enough buffer for full match
          if (!memcmp(&buffer[i], searchString, searchStringLength)) {
            count++;
          }
        } else if (!memcmp(&buffer[i], searchString, validDataSize - i)) { // check for possible match that was cut off
          // move partial match to front of buffer
          bufferOffset = validDataSize - i;
          memmove(buffer, &buffer[i], bufferOffset);
          break;
        }
      }
    }
  }

  printf("Size of file is %i\n", fileSize);
  fprintf(output, "Size of file is %i\n", fileSize);
  printf("Number of matches = %i\n", count);
  fprintf(output, "Number of matches = %i\n", count);

  // close files
  if ((fclose(input)) != 0) {
    perror("Error");
    printf("Could not close %s\n", inputFilename);
  }
  if ((fclose(output)) != 0) {
    perror("Error");
    printf("Could not close %s\n", outputFilename);
  }
}