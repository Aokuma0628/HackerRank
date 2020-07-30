#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK  1
#define NG -1
#define INPUT_NUM 2

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
* @brief      split integer by a space
* @param[in]  str split target
* @param[out] val[INPUT_NUM] separated numbers are stored
* @return     int split result
*/
int split_integer(
  char *str,
  int   val[INPUT_NUM]
)
{
  int   tmp_val = 0;
  int   i       = 0;
  char *tmp_str = str;
  char *err     = NULL;

  if (!str || !val) {
    return NG;
  }

  for (; i < INPUT_NUM - 1; i++) {
    char *space = NULL;

    tmp_val = strtol(tmp_str, &space, 10);
    if (*space != ' ') {
      return NG;
    }
    val[i] = tmp_val;
    tmp_str = space++;
  }

  tmp_val = strtol(tmp_str, &err, 10);
  if (*err != '\0' && *err != '\n') {
    return NG;
  }
  val[INPUT_NUM - 1] = tmp_val;

  return OK;
}


/**
* @brief      split float by a space
* @param[in]  str split target
* @param[out] val[INPUT_NUM] separated numbers are stored
* @return     int split result
*/
int split_float(
  char *str,
  float val[INPUT_NUM]
)
{
  float tmp_val = 0;
  int   i       = 0;
  char *tmp_str = str;
  char *err     = NULL;

  if (!str || !val) {
    return NG;
  }

  for (; i < INPUT_NUM - 1; i++) {
    char *space = NULL;

    tmp_val = strtold(tmp_str, &space);
    if (*space != ' ') {
      return NG;
    }
    val[i] = tmp_val;
    tmp_str = space++;
  }

  tmp_val = strtod(tmp_str, &err);
  if (*err != '\0' && *err != '\n') {
    return NG;
  }
  val[INPUT_NUM - 1] = tmp_val;

  return OK;
}


/**
* @brief      main function
* @param[in]  void
* @return     int : 0
*/
int main()
{
  int   val_int[INPUT_NUM];
  float val_flt[INPUT_NUM];
  char *str_int = readline();
  char *str_flt = readline();

   if (split_integer(str_int, val_int) != OK) {
     goto l_end;
   }
   if (split_float(str_flt, val_flt) != OK) {
     goto l_end;
   }

   printf("%d %d\n",
          val_int[0] + val_int[1],
          val_int[0] - val_int[1]);
   printf("%.1f %.1f\n",
          val_flt[0] + val_flt[1],
          val_flt[0] - val_flt[1]);

l_end:
  free_read_list();
  return 0;
}
