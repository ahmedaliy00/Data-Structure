#include <stdio.h>
#include <stdlib.h>
int count (int n)
{
    if (n == 0)
        return 0;
    count(n - 1);
    printf("%d ", n);
}
int main() {
    int n = 10;
    count (n);
    return 0;
}