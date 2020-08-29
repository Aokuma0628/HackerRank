#ifndef _STRING_H
#define _STRING_H

int split_str2str(char *str, int num, char del, char **split);
int split_str2int(char *str, int num, char del, int *split);
int check_string_match(const char *pattern, char *target);

#endif
