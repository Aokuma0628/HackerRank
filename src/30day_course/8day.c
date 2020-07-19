#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define OK  1
#define NG -1

typedef struct _phone {
  char *name;
  int   number;
  struct _phone *next;
} PHONE;

typedef struct _alloc {
  void *mem;
  struct _alloc *next;
} ALLOC;

ALLOC *g_alloc_list =NULL;

char *readline();
void  free_list();

int main() {
  int     line_num     = 0;
  char   *line_num_str = NULL;
  char   *err          = NULL;
  PHONE  *list = NULL;
  int     i    = 0;
  int     j    = 0;
  int     k    = 0;
  int     ret  = NG;

  line_num_str = readline();
  if (!line_num_str) {
    goto l_exit;
  }

  line_num = strtol(line_num_str, &err, 10);
  if (*err != '\0') {
    goto l_exit;
  }

  for (; i < line_num; i++) {
    char *line  = NULL;
    char *num_p = NULL;
    char *err   = NULL;
    PHONE  *name_phone = NULL;
    PHONE  *tmp        = list;

    line = readline();
    if (!line) {
      goto l_exit;
    }

    num_p = strchr(line, ' ');
    if (!num_p) {
      goto l_exit;
    }
    *num_p = '\0';
    num_p++;

    name_phone = (PHONE*)calloc(1, sizeof(PHONE));
    if (!name_phone) {
      goto l_exit;
    }
    name_phone->name = line;
    name_phone->number = strtol(num_p, &err, 10);
    if (*err != '\0') {
      goto l_exit;
    }

    if (!list) {
      list = name_phone;
      continue;
    }

    while(tmp->next) {
      tmp = tmp->next;
    }
    tmp->next = name_phone;

  }

  for (; j < line_num; j++) {
    char  *s_name = NULL;
    PHONE *tmp2   = list;

    s_name = readline();
    if (!s_name) {
      goto l_exit;
    }

    while (tmp2) {
      if (strcmp(s_name, tmp2->name) == 0) {
        printf("%s=%d\n", s_name, tmp2->number);
        break;
      }
      tmp2 = tmp2->next;
      k++;
    }

    if (k >= line_num) {
      printf("Not found\n");
    }
    k = 0;
  }
  ret = OK;

l_exit:
  if (ret != OK) {
    printf("ret=NG\n");
  }
  free_list();

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

  if (!g_alloc_list) {
    g_alloc_list = list;
  }

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
