#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *readline();
void  separateblank(char *target, char **str1, char **str2);

int main(
  void
)
{
  char *int_str = NULL;
  char *flt_str = NULL;

  int_str = readline();
  if (int_str) {
    char *str_p1 = NULL;
    char *str_p2 = NULL;

    separateblank(int_str, &str_p1, &str_p2);
  }

  flt_str = readline();



  return 0;
}

void  separateblank(
  char *target,
  char **str_p1,
  char **str_p2
)
{
while(*target != '\0') {
  
}

  return ;
}


char *readline(
  void
)
{
  size_t alloc_length = 256;
  size_t data_length  = 0;
  char*  data         = (char *)malloc(alloc_length);

  if (!data) {
    return NULL;
  }

  while (1) {
      char* cursor = data + data_length;
      char* line   = fgets(cursor, alloc_length - data_length, stdin);
      /*malloc null check*/
      if (!line) {
        break;
      }

      data_length += strlen(cursor);
      /*check if read one sentence*/
      if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
        break;
      }

      /*when one sentence length is longer than alloc_length */
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

  /*Making the just data size*/
  data = (char *)realloc(data, data_length);

  return data;
}
