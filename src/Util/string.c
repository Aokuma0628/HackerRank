#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define OK  1
#define NG -1


/**
* @brief      split string by in_delimiter to string
* @param[in]  str : split target
* @param[in]  num : number of string
* @param[in]  del : delimiter character
* @param[out] split : string array after spliting
* @return     int : split result
*/
int split_str2str(
  char   *str,
  int     num,
  char    del,
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
    while (*tmp != del && *tmp != '\0') {
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
