#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK  1
#define NG -1
#define BINARY_NUMBER 25  //! 10^6 < 2^24

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

/*binary*/
int calc_binary(int *binary, int val);
int count_consecutive(int *binary, int *cnt);


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
* @brief      calc binary from value
* @param[in]  val : decimal number
* @param[out] binary : binary array
* @return     int : calc result
*/
int calc_binary(
  int *binary,
  int val
)
{
  int i = 0;

  if (!binary || val == 0) {
    return NG;
  }

  for (i = 1; i <= BINARY_NUMBER; i++) {
    binary[BINARY_NUMBER - i] = val % 2;
    val = val / 2;
  }

  return OK;
}

/**
* @brief      count consecutive 1
* @param[in]  binary : count target
* @param[out] cnt : count number
* @return     int : count result
*/
int count_consecutive(
  int *binary,
  int *cnt
)
{
  int cons = 0;
  int tmp  = 0;
  int i    = 0;

  if (!binary || !cnt) {
    return NG;
  }

  for (; i < BINARY_NUMBER; i++) {
    if (1 == binary[i]) {
      tmp++;
    }
    else {
      tmp = 0;
    }

    if (tmp > cons) {
      cons = tmp;
    }
  }
  *cnt = cons;

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
    char *str = readline();
    int   val = strtol(str, &err, 10);
    int   binary[BINARY_NUMBER];
    int   cnt = 0;

    memset(binary, 0, sizeof(int) * BINARY_NUMBER);

    if (*err != '\0') {
      goto l_end;
    }

    if (calc_binary(binary, val) != OK) {
      goto l_end;
    }

    if (count_consecutive(binary, &cnt) != OK) {
      goto l_end;
    }
    printf("%d\n", cnt);
l_end:
    free_read_list();
    return 0;
}
