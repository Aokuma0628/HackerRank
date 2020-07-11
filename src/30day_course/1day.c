#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int i = 4;
    double d = 4.0;
    char s[] = "HackerRank ";

#define NUMLEN 10
#define STRLEN 256

  char in_i[NUMLEN];
  char in_d[NUMLEN];
  char in_s[STRLEN];
  int out_i = 0;
  double out_d = 0.0;
  char out_s[STRLEN];
  char *err = NULL;

  /*input from stdin*/
  if (fgets(in_i, NUMLEN - 1, stdin)) {
    out_i = (int)strtol(in_i, &err, 10);
    if (*err == 0) {
      printf("err=%s",err);
      goto l_end;
    }
  }
  if (fgets(in_d, NUMLEN - 1, stdin)) {
    out_d = strtod(in_d, &err);
    if (*err == 0) {
      printf("err=%s",err);
      goto l_end;
    }
  }
  if (fgets(in_s, STRLEN - 1, stdin)) {
    ;
  }

  /*sum*/
  out_i = out_i + i;
  out_d = out_d + d;
  snprintf(out_s, STRLEN - 1, "%s%s", s, in_s);

  printf("%d\n", out_i);
  printf("%.1lf\n", out_d);
  printf("%s\n", out_s);

l_end:
    return 0;
}
