#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Complete the following function.

int find_nth_term(int n, int a, int b, int c) {
  //Write your code here.
  int sum = a + b + c;
  int i = 4;
  int pre1 = sum;
  int pre2 = c;
  int pre3 = b;

  for (; i < n; i++) {
    sum = pre1 + pre2 + pre3;
    pre1 = sum;
    pre2 = pre1;
    pre3 = pre2;
  }
  return sum;
}

int main() {
    int n, a, b, c;

    scanf("%d %d %d %d", &n, &a, &b, &c);
    int ans = find_nth_term(n, a, b, c);

    printf("%d", ans);
    return 0;
}
