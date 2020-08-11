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

READ_ALLOC *g_read_list = NULL;   //! List pointer to read data
READ_ALLOC *g_read_last  = NULL;  //! end of list

/*read from stdin */
char *readline();
int   add_read_alloc(char *line);
void  free_read_list();



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
* @brief      split string by in_delimiter to integer
* @param[in]  str : split target
* @param[in]  num : number of delimiter
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
* @brief      bubble_sort
* @param[in]  array : sort target
* @param[in]  num   : array length
* @return     int   : sort result
*/
int bubble_sort(
  int *array,
  int  num
)
{
  int i   = 0;
  int cnt = 0;  //! 20day val

  if (!array) {
    return NG;
  }

  for (; i < num; i++)  {
    int j = 0;
    for (; j < (num - i - 1); j++) {
      if (array[j] > array[j + 1]) {
          int tmp = array[j];
          array[j] = array[j + 1];
          array[j + 1] = tmp;
          cnt++;
      }
    }
  }

  //! 20day process
  printf("Array is sorted in %d swaps.\n", cnt);

  return OK;
}


/**
* @brief      main function
* @param[in]  void
* @return     int : 0
*/
int main()
{
    char *err = NULL;
    char *n_s = readline();
    char *a_s = readline();
    int  *array   = NULL;
    const int del = ' ';


    const int n = strtol(n_s, &err, 10);
    if (*err != '\0') {
      goto l_end;
    }

    array = (int*)calloc(1, sizeof(int)*n);
    if (!array) {
      goto l_end;
    }
    if (split_str2int(a_s, n, del, array) != OK) {
      goto l_end;
    }

    if (bubble_sort(array, n) != OK) {
      goto l_end;
    }

    printf("First Element: %d\n", array[0]);
    printf("Last Element: %d\n", array[n - 1]);

l_end:
    free_read_list();
    if (array) {
      free(array);
    }
    return 0;
}
