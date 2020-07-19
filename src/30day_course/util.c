#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _alloc {
  void *mem;
  struct _alloc *next;
} ALLOC;

ALLOC *g_alloc_list =NULL;

char *readline();
void  free_list();

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
  ALLOC *alloc = NULL;
  ALLOC *list = g_alloc_list;

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

  alloc = (ALLOC*)calloc(1, sizeof(ALLOC));
  if (!alloc) {
    return NULL;
  }
  alloc->mem = data;
  while(list) {
    list = list->next;
  }
  list = alloc;

  return data;
}

void free_list() {
  ALLOC *list = g_alloc_list;
  ALLOC *tmp  = NULL;

  while(list) {
    tmp = list->next;
    free(list);
    list = tmp;
  }

  return ;
}

char **split_string(char* str) {
  char **splits = NULL;
  char  *token  = strtok(str, " ");
  int    spaces = 0;

  while (token) {
    splits = (char **)realloc(splits, sizeof(char*) * ++spaces);
    if (!splits) {
      return splits;
    }

    splits[spaces - 1] = token;
    token = strtok(NULL, " ");
  }

  return splits;
}
