#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK  1
#define NG -1
#define ROW 6
#define COL 6

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

/*hourglass function*/
int split_string_space(char *str, int num, char **split);
int calc_patern_sum(int hourglass[ROW][COL]);

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
* @brief      split string by space
* @param[in]  str : split target
* @param[in]  num : number of spaces
* @param[out] split : string array after spliting
* @return     int : split result
*/
int split_string_space(
  char   *str,
  int     num,
  char  **split
)
{
  int   i   = 0;
  char *tmp = str;

  if (!str || !split) {
    return NG;
  }

  while(1) {
    split[i] = tmp;
    while (*tmp != ' ' && *tmp != '\0') {
      tmp++;
    }

    i++;
    if(*tmp == '\0' || i >= num) {
      break;
    }

    *tmp = '\0';
    tmp++;
  }

  return OK;
}

/**
* @brief      calculate sum of patern
* @param[in]  hourglass : 6 x 6 matrix
* @return     int : calculation result
*/
int calc_patern_sum(
  int hourglass[ROW][COL]
)
{
  const int range = 3;
  int i   = 0;
  int j   = 0;
  int sum = -64;  //! -9x6=-63 > -64

  for (; i <= ROW - range; i++) {
    int tmp_sum = 0;
    for (j = 0; j <= COL -range; j++) {
      tmp_sum = hourglass[i][j] + hourglass[i][j+1] + hourglass[i][j+2]
                + hourglass[i+1][j+1]
                + hourglass[i+2][j] + hourglass[i+2][j+1] + hourglass[i+2][j+2];
      if (tmp_sum > sum) {
        sum = tmp_sum;
      }
    }
  }

  printf("%d\n", sum);

  return OK;
}


/**
* @brief      main function
* @param[in]  void
* @return     int : 0
*/
int main()
{
    int i = 0;
    int j = 0;
    int hourglass[ROW][COL];

    for (; i < ROW; i++) {
      memset(hourglass[i], 0, sizeof(int) * COL);
    }

    for (i = 0; i < ROW; i++) {
      char *str = readline();
      char *split[COL];

      memset(split, 0, sizeof(char*) * COL);
      if (split_string_space(str, COL, split) != OK) {
        goto l_end;
      }

      for (j = 0; j < COL; j++) {
        char *err = NULL;

        hourglass[i][j] = strtol(split[j], &err, 10);
        if (*err != '\0') {
          goto l_end;
        }
      }
    }
    calc_patern_sum(hourglass);

l_end:
    free_read_list();
    return 0;
}
