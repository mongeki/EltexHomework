#include <stdio.h>

int main() {
  FILE *f = fopen("output.txt", "w+");
  if (f == NULL) {
    printf("Can't open file\n");
    return -1;
  }
  fprintf(f, "String from file");
  int length = ftell(f);
  fseek(f, -1, SEEK_CUR);
  while (length > 0) {
    printf("%c", fgetc(f));
    fseek(f, -2, SEEK_CUR);
    --length;
  }
  printf("\n");
  fclose(f);
  return 0;
}
