#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

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

READ_ALLOC *g_read_list = NULL;   //! List pointer to read data
READ_ALLOC *g_read_last  = NULL;  //! end of list

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
* @brief      split string by in_delimiter to integer
* @param[in]  str : split target
* @param[in]  num : number of string
* @param[in]  del : delimiter character
* @param[out] split : integer array after spliting
* @return     int : split result
*/
int split_str2int(
  char   *str,
  int     num,
  char    del,
  int    *split
)
{
  int   i   = 0;
  char *tmp = str;
  char *end = NULL;

  if (!str || !split) {
    return NG;
  }

  while(1) {
    int val = strtol(tmp, &end, 10);
    if ((*end != del) && (*end != '\0')) {
      return NG;
    }
    split[i] = val;

    i++;
    if(*end == '\0' || i >= num) {
      break;
    }

    tmp = end;
    tmp++;
    end = NULL;
  }

  return OK;
}

/**
* @brief      Print pattern
* @param[in]  n : Input number
* @return     void
*/
void print_pattern(
  int n
)
{
  int i = 0;
  int j = 0;
  int *array = (int *)calloc(1, sizeof(int) * (n - 1));
  if (!array) {
    return;
  }

  for (; i < n; i++) {
    for (j = 0; j < n - 1; j++) {
      array[j] = j > i ? n - i : n - j;
      printf("%d ", array[j]);
    }

    printf("%d ", n - i);

    for (j = n - 2; j >= 0; j--) {
      printf("%d ", array[j]);
    }
    printf("\n");
  }

  for (i = n - 2; i >= 0; i--) {
    for (j = 0; j < n - 1; j++) {
      array[j] = j > i ? n - i : n - j;
      printf("%d ", array[j]);
    }

    printf("%d ", n - i);

    for (j = n - 2; j >= 0; j--) {
      printf("%d ", array[j]);
    }
    printf("\n");
  }

  return ;
}

int main() {
    char *err = NULL;
    char *n_str = readline();
    int n = strtol(n_str, &err, 10);
    if (*err != '\0') {
      return -1;
    }

    print_pattern(n);

    free_read_list();

    return 0;
}
