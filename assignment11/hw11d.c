// name: Tian Huang
// email: huang.tian2@northeastern.edu

#include <stdio.h>

int d[20];

long long int dp(int n) {

    // Add your code here

    if (n == 0) {
        return 1;
    }

    if (n == 1) {
        return 2;
    }

    if (d[n] != -1) {
        return d[n];
    }

    d[n] = 3 * dp(n-2) + 2 * dp(n-1);
    for (int j = n-3; j >=0; j -= 1) {
        d[n] += 2 * dp(j);
    }

    return d[n];
}

int main(void) {
    int n;
    for (int i = 0; i <= 20; i++) {
        d[i] = -1;
    }
    printf("Enter a number n: ");
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
