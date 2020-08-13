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
* @brief      Input date from stdin
* @param[out]  act_date : Actual return date
* @param[out]  exp_date : Expected return date
* @return     int : Input result
*/
int input_date(
  int *act_date,
  int *exp_date
)
{
  char *act_str = readline();
  char *exp_str = readline();

  if (!act_date || !exp_date) {
    return NG;
  }

  if (split_str2int(act_str, 3, ' ', act_date) != OK) {
    return NG;
  }
  if (split_str2int(exp_str, 3, ' ', exp_date) != OK) {
    return NG;
  }

  return OK;
}

/**
* @brief      Calculate fine according to the return date
* @param[in]  act_date : Actual return date
* @param[in]  exp_date : Expected return date
* @param[out] fine     : Fine according to the return date
* @return     int      : Calculate result
*/
int calculate_fine(
  int *act_date,
  int *exp_date,
  int *fine
)
{
  const int y = 2;
  const int m = 1;
  const int d = 0;
  const int y_fine = 10000;
  const int m_fine = 500;
  const int d_fine = 15;

  if (!act_date || !exp_date || !fine) {
    return NG;
  }

  if (act_date[y] > exp_date[y]) {
    *fine = y_fine;
  }
  else if (act_date[m] > exp_date[m]  && act_date[y] == exp_date[y]) {
    *fine = m_fine * (act_date[m] - exp_date[m]);
  }
  else if (act_date[d] > exp_date[d] && act_date[m] == exp_date[m]) {
    *fine = d_fine * (act_date[d] - exp_date[d]);
  }
  else {
    *fine = 0;
  }

  return OK;
}

int main() {
  int act_date[3];
  int exp_date[3];
  int fine;

  if (input_date(act_date, exp_date) != OK) {
    return 0;
  }

  if (calculate_fine(act_date, exp_date, &fine) != OK) {
    return 0;
  }

  printf("%d\n", fine);
  free_read_list();
  return 0;
}
