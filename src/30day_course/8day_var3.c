#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK  1
#define NG -1

typedef struct _read_alloc {
  char *line;
  struct _read_alloc *next;
} READ_ALLOC;

typedef struct _node {
  char *key;
  int   data;
  struct _node *left;
  struct _node *right;
} NODE;


READ_ALLOC *g_read_list = NULL;
READ_ALLOC *g_read_last  = NULL;
NODE       *g_root = NULL;


int   insert_node(NODE *node);
NODE *search_node(char *key);
void  free_node(NODE *node);
char *readline();
int   add_read_alloc(char *line);
void  free_read_list();
int   add_read_list(char *line);

int get_name_phone(int line_num);
int search_phone(int line_num);


int search_phone(
  int line_num
)
{
  int ret = NG;
  int i  = 0;

  for (; i < line_num; i++) {
    char *name = NULL;
    NODE *node = NULL;

    name = readline();
    if (!name) {
      goto l_exit;
    }

    node = search_node(name);

    if (node) {
      printf("%s=%d\n", name, node->data);
    }
    else {
      printf("Not found\n");
    }
  }

l_exit:
  ret = OK;
  return ret;
}



int get_name_phone(
  int line_num
)
{
  int ret = NG;
  int i   = 0;

  for (; i < line_num; i++) {
    char *line   = NULL;
    char *num_p  = NULL;
    char *err    = NULL;
    NODE *name_phone = NULL;

    line = readline();
    if (!line) {
      goto l_exit;
    }

    num_p = strchr(line, ' ');
    if (!num_p) {
      goto l_exit;
    }
    *num_p = '\0';

    name_phone = (NODE*)calloc(1, sizeof(NODE));
    if (!name_phone) {
      goto l_exit;
    }
    name_phone->key   = line;
    name_phone->data = strtol(++num_p, &err, 10);
    if (*err != '\0') {
      goto l_exit;
    }
    if (insert_node(name_phone) != OK) {
      goto l_exit;
    }
  }
    ret = OK;
l_exit:
  return ret;
}

int main()
{
    char   *err          = NULL;
    int     line_num     = 0;
    char   *line_num_str = NULL;
    int     ret          = NG;

    line_num_str = readline();
    if (!line_num_str) {
      goto l_exit;
    }

    line_num = strtol(line_num_str, &err, 10);
    if (*err != '\0') {
      goto l_exit;
    }

    if (get_name_phone(line_num) != OK) {
      goto l_exit;
    }

    if (search_phone(line_num) != OK) {
      goto l_exit;
    }

    ret = OK;

  l_exit:
    if (ret != OK) {
      printf("ret=NG\n");
    }
    free_node(NULL);
    free_read_list();

    return 0;
}



NODE *search_node(
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
  NODE *pos  = g_root;
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
    g_read_list  = alloc;
    g_read_last  = alloc;
  }
  else {
    last->next  = alloc;
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
