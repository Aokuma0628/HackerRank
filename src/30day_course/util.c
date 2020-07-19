#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK  1
#define NG -1

typedef struct _read_alloc {
  void *mem;
  struct _read_alloc *next;
} READ_ALLOC;

typedef struct _node {
  char *key;
  void *data;
  struct _node *left;
  struct _node *right;
} NODE;

READ_ALLOC *g_read_list = NULL;
NODE       *g_root = NULL;


int insert_node(NODE *node);
NODE *serch_node(void *key);
void free_node();
char *readline();
void  free_read_list();

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

NODE *serch_node(
  char *key
)
{
  NODE *pos    = g_root;
  int   result = 0;

  while (pos) {
    result = strcmp(key, pos->key);
    if (result == 0) {
      return pos;
    }
    else if (result < 0) {
      pos = pos->left;
    }
    else {
      pos = pos->right;
    }
  }

  return NULL;
}

int insert_node(
  NODE *node
)
{
  NODE *pos = g_root;
  NODE *pre  = NULL;

  if (!node) {
    return NG;
  }

  if (!pos) {
    g_root = node;
    return OK;
  }

  while (pos) {
    pre = pos;
    if (strcmp(node->key, pos->key) < 0) {
      pos = pos->left;
      if (!pos) {
        pre->left = node;
      }
    }
    else {
      pos = pos->right;
      if (!pos) {
        pre->right = node;
      }
    }
  }
  return OK;
}

void free_node (
  NODE *node
)
{
  if (!node) {
    node = g_root;
  }

  if (!node) {
    return ;
  }

  if (node->left) {
    free_node(node->left);
  }
  if (node->right) {
    free_node(node->right);
  }

  free(node);
  return ;

  }



char *readline(
  void
)
{
  size_t alloc_length = 1024;
  size_t data_length  = 0;
  char  *data         = (char *)malloc(alloc_length);
  READ_ALLOC *alloc = NULL;
  READ_ALLOC *list = g_read_list;

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

  alloc = (READ_ALLOC*)calloc(1, sizeof(READ_ALLOC));
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

void read_free_list() {
  READ_ALLOC *list = g_read_list;
  READ_ALLOC *tmp  = NULL;

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
