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
* @brief      Calculate the max bitwise operation(&, |, ^)
* @param[in]  n : Number of repetitions
* @param[in]  k : The max number
* @return     void
*/
void calculate_the_maximum(
  int n,
  int k
)
{
  int i = 0;
  int j = 0;
  int max_and = 0;
  int max_or  = 0;
  int max_xor = 0;

  for (i = 1; i < n; i++) {
    for (j = i + 1; j <= n; j++) {
      int tmp_and = 0;
      int tmp_or  = 0;
      int tmp_xor = 0;

      tmp_and = i & j;
      tmp_or  = i | j;
      tmp_xor = i ^ j;

      if (max_and < tmp_and && tmp_and < k) {
        max_and = tmp_and;
      }
      if (max_or < tmp_or && tmp_or < k) {
        max_or = tmp_or;
      }
      if (max_xor < tmp_xor && tmp_xor < k) {
        max_xor = tmp_xor;
      }
    }
  }
  printf("%d\n%d\n%d\n", max_and, max_or, max_xor);

  return ;
}

int main() {
    char *err = NULL;
    char *n_str = readline();
    char *k_str = readline();

    int n = strtol(n_str, &err, 10);
    if (*err != '\0') {
      return -1;
    }
    int k = strtol(k_str, &err, 10);
    if (*err != '\0') {
      return -1;
    }

    calculate_the_maximum(n, k);

    free_read_list();

    return 0;
}
