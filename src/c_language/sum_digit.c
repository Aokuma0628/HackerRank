#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    int n;
    int i;
    int sum = 0;
    int tmp = 0;
    scanf("%d", &n);
    //Complete the code to calculate the sum of the five digits on n.

    tmp = n;
    for (i = 0; i < 5; i++) {
      sum += tmp % 10;
      tmp = tmp / 10;
    }

    printf("%d\n", sum);
    return 0;
}
