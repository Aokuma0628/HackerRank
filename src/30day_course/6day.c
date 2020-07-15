#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <sysexits.h>

char *readline();

int main() {

  char *endptr  = NULL;
  char *num_str = NULL;
  int   cnt     = 0;
  int   base    = 10;

  num_str = readline();
  if (!num_str) {
    exit(EXIT_FAILURE);
  }

  cnt = strtol(num_str, &endptr, base);
  if (*endptr != '\0') {
    exit(EXIT_FAILURE);
  }

  int i = 0;
  for (; i < cnt; i++) {
    char  *input   = NULL;
    char  *pt      = NULL;
    size_t length = 10000;
    char   even_str[length];
    char   odd_str[length];

    input = readline();
    if (!input) {
      goto l_end;
    }

    memset(even_str, 0, length);
    memset(odd_str,  0, length);

    pt = input;
    int even_idx = 0;
    int odd_idx = 0;
    while(*pt != '\0') {
      if (even_idx == odd_idx) {
        even_str[even_idx] = *pt;
        even_idx++;
      }
      else {
        odd_str[odd_idx] = *pt;
        odd_idx++;
      }
      pt++;
    }

    printf("%s", even_str);
    printf(" %s\n", odd_str);

    if (input) {
      free(input);
    }
  }

l_end:
  if (num_str) {
    free(num_str);
  }

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
