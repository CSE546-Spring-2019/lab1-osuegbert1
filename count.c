#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[]) {
  FILE *input, *output;
  unsigned char buffer[BUFFER_SIZE];
  int fileSize = 0, count = 0, itemsRead;
  int i;
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
  while ((itemsRead = fread(buffer, 1, BUFFER_SIZE, input)) > 0) {
    fileSize += itemsRead;
    for (i = 0; i < itemsRead; i++) {
      if (buffer[i] == searchChar &&
          !memcmp(&buffer[i], searchString, searchStringLength)) {
        count++;
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