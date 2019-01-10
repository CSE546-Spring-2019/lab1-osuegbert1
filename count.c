#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
  int fileSize = 0, occurances = 0;
  FILE* input;
  FILE* output;

  if(argc != 3){
    printf("Usage: count <input-filename> <search-string> <output-filename>\n");
    return(-1);
  }
  if((input = fopen(argv[0], "rb")) == NULL){
    perror("Error");
    printf("Could not open %s\n", argv[0]);
    return(-1);
  }
  if((output = fopen(argv[2], "wb")) == NULL){
    perror("Error");
    printf("Could not open %s\n", argv[2]);
    return(-1);
  }


  //close files
  if((fclose(input)) != 0){
    perror("Error");
    printf("Could not close %s\n", argv[0]);
  }
  if((fclose(output)) != 0){
    perror("Error");
    printf("Could not close %s\n", argv[2]);
  }
}