#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK  1
#define NG -1

/**
 * @struct READ_ALLOC
 * @brief  list of string read from stdin
 */
typedef struct _read_alloc {
  char *line;
  struct _read_alloc *next;
} READ_ALLOC;

/**
 * @struct NODE
 * @brief  node for binary tree
 */
typedef struct _node {
  char *key;
  void *data;
  struct _node *left;
  struct _node *right;
} NODE;


READ_ALLOC *g_read_list = NULL;   //! List pointer to read data
READ_ALLOC *g_read_last  = NULL;  //! end of list
NODE       *g_root = NULL;        //! root of node

/*read from stdin */
char *readline();
int   add_read_alloc(char *line);
void  free_read_list();

/*node function*/
int   insert_node(NODE *node);
NODE *serch_node(char *key);
void  free_node(NODE *node);


/**
* @brief      serch node
* @param[in]  key : key for serching node
* @return     NODE* : if found by key, the node pointer
*/
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

/**
* @brief      insert a node into tree
* @param[in]  *node : node to be inserted
* @return     int : insertion result
*/
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

/**
* @brief      free node's memory
* @param[in]  *node : if node is NULL, free all node
* @return     void
*/
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


/**
* @brief      read string from stdin
* @param[in]  void
* @return     char* : one-line string
*/
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


/**
* @brief      add read list
* @param[in]  line : string from stdin
* @return     int : add result
*/
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


/**
* @brief      free read list
* @param[in]  void
* @return     void
*/
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

/**
* @brief      split string by one space
* @param[in]  str : string include spaces
* @return     char** : array of string after spliting
*/
char **split_string(
  char* str
)
{
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

/**
* @brief      main function
* @param[in]  void
* @return     int : 0
*/
int main()
{
    char *err = NULL;
    char *str = readline();
    int   val = strtol(str, &err, 10);

    if (*err != '\0') {
      goto l_end;
    }

    (void)val;

l_end:
    free_read_list();
    return 0;
}
