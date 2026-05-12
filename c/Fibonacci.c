#include <stdio.h>
#include <stdlib.h>

int main() {
    int n0 = 0;
    int n1 = 1;
    int n = 32;
    int r;
    for(int i=2;i<=n;++i) {
        r = n0+n1;
        n0 = n1;
        n1 = r;
    }
    printf("Fibonacci(32) = %d\n", r);
    exit(0);
}