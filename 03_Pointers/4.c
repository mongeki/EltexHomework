#include <stdio.h>
#include <stdlib.h>

char* strstr(const char* str, const char* sub);

int main() {
  char str[30];
  char sub[30];
  scanf("%s", str);
  scanf("%s", sub);
  char* ptr = strstr(str, sub);
  printf("%p\n", ptr);
  exit(EXIT_SUCCESS);
}

char* strstr(const char* str, const char* sub) {
  if (*sub == '\0') {
    return (char*)str;
  }
  for (; *str; ++str) {
    if (*(str) == *sub) {
      char* ptr = strstr(str + 1, sub + 1);
      return (ptr) ? ptr - 1 : NULL;
    }
  }
  return NULL;
}
