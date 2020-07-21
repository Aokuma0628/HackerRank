#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK  1
#define NG -1

typedef struct _read_alloc {
  char *line;
  struct _read_alloc *next;
} READ_ALLOC;

READ_ALLOC *g_read_list = NULL;
READ_ALLOC *g_read_last  = NULL;

char *readline();
int   add_read_alloc(char *line);
void  free_read_list();
int   add_read_list(char *line);
int   factorial(int num);


int factorial(
  int num
)
{
  if (num > 1) {
    num = num * factorial(num - 1);
  }
  else {
    ;
  }
  return num;
}


int main()
{
    char *err;
    char *str = readline();
    int   val = strtol(str, &err, 10);
    if (*err != '\0') {
      exit(EXIT_FAILURE);
    }

    printf("%d\n", factorial(val));

    free_read_list();

    return 0;
}


char *readline(
  void
)
{
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
  if (add_read_alloc(data) != OK) {
    return NULL;
  }

  return data;
}


int add_read_alloc (
  char *line
)
{
  int ret = NG;
  READ_ALLOC *alloc = NULL;
  READ_ALLOC *last  = g_read_last;

  alloc = (READ_ALLOC*)calloc(1, sizeof(READ_ALLOC));
  if (!alloc) {
    return ret;
  }
  alloc->line = line;

  if (!g_read_list) {
    g_read_list = alloc;
    g_read_last  = alloc;
  }
  else {
    last->next = alloc;
    g_read_last = last->next;
  }

  ret = OK;
  return ret;
}

void free_read_list() {
  READ_ALLOC *list = g_read_list;
  READ_ALLOC *tmp  = NULL;

  while(list) {
    tmp = list->next;
    free(list->line);
    free(list);
    list = tmp;
  }

  return ;
}
