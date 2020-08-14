#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

#define OK 1
#define NG 0

char* readline();
char** split_string(char*);

/**
* @brief      Regular expression string checking
* @param[in]  pattern : Regular expression search string
* @param[in]  target  : Search target string
* @return     int     : match result
*/
int check_string_match(
  const char  *pattern,
  char        *target
)
{
  regex_t preg;
  int ret = NG;

  if (regcomp(&preg, pattern,
        REG_EXTENDED | REG_NOSUB | REG_NEWLINE) != 0) {
    return ret;
  }

  if (regexec(&preg, target, 0, NULL, 0) != 0) {
    ret = NG;
  }
  else {
    ret = OK;
  }
  regfree(&preg);

  return ret;
}

/**
* @brief      bubble_sort_str
* @param[in]  array : sort target
* @param[in]  num   : array length
* @return     int   : sort result
*/
int bubble_sort_str(
  char **array,
  int  num
)
{
  int i   = 0;

  if (!array) {
    return NG;
  }

  for (; i < num; i++)  {
    int j = 0;
    for (; j < (num - i - 1); j++) {
      if (strcmp(array[j], array[j + 1]) > 0) {
          char *tmp = array[j];
          array[j] = array[j + 1];
          array[j + 1] = tmp;
      }
    }
  }

  return OK;
}


int main()
{
    char* N_endptr;
    char* N_str = readline();
    int N = strtol(N_str, &N_endptr, 10);
    const char *pattern = "@gmail.com$";
    int matchCount = 0;
    int i = 0;

    if (N_endptr == N_str || *N_endptr != '\0') { exit(EXIT_FAILURE); }

    char **nameArray = (char**)malloc(sizeof(char*) * N);


    for (int N_itr = 0; N_itr < N; N_itr++) {
        char** firstNameEmailID = split_string(readline());
        char* firstName = firstNameEmailID[0];
        char* emailID = firstNameEmailID[1];

        if (check_string_match(pattern, emailID)  != OK) {
          continue;
        }
        else {
          nameArray[matchCount] = firstName;
          matchCount++;
        }
    }

    if (bubble_sort_str(nameArray, matchCount) != OK) {
      return 0;
    }

    for (; i < matchCount; i++) {
      printf("%s\n", nameArray[i]);
      free(nameArray[i]);
    }

    if (nameArray) {
      free(nameArray);
    }

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
