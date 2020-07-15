#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

int main()
{
    char *endptr;
    char *str = readline();
    int val = strtol(str, &endptr, 10);

    if (*endptr != '\0') {
      exit(EXIT_FAILURE);
    }

    (void)val;

    return 0;
}

char *readline() {
  size_t alloc_length = 1024;
  size_t data_length  = 0;
  char  *data         = (char *)malloc(alloc_length);

  while (1) {
    char *cursor = data + data_length;
    char *line   = fgets(cursor, alloc_length - data_length, stdin);
    if (!line) {
      break;
    }

    data_length += strlen(cursor);

    if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
      break;
    }

    size_t new_length = alloc_length << 1;
    data = (char *)realloc(data, new_length);

    if (!data) {
      break;
    }

    alloc_length = new_length;
  }

  if (data[data_length - 1] == '\n') {
    data[data_length - 1] = '\0';
  }

  data = (char *)realloc(data, data_length);

  return data;
}
