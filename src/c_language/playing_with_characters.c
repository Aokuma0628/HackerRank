#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *readline();

int main()
{
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */

  char *ch  = NULL;
  char *s   = NULL;
  char *sen = NULL;

  ch  = readline();
  s   = readline();
  sen = readline();

  if (ch) {
    printf("%s\n", ch);
    free(ch);
  }
  if (s) {
    printf("%s\n", s);
    free(s);
  }
  if (sen) {
    printf("%s\n", sen);
    free(sen);
  }

  return 0;
}

char *readline() {
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
