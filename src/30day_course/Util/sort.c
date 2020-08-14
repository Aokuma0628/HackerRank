#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK  1
#define NG -1

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
      }
    }
  }

  return OK;
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
