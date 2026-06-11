#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int print(int n)
{
    if (n == 0)
        return 0;
    print(n - 1);
    printf("%d ", n);
}
int sum (int n)
{
    if (n == 10)
        return 10;
    return n + sum(n +1);
}
int fib(int n) {
    if (n==1 || n==2)
        return 1;
    return fib(n - 1) + fib(n - 2);

}
int mod (int a, int b) {
    if (b == 0) {
        printf("Error: division by zero\n");
        return -1; // Return -1 to indicate an error
    }
    if (a < b)
        return a;
    return mod(a - b, b);
}
int GCD(int a, int b) {
    if (b == 0)
        return a;
    return GCD(b, a % b);
}
int countDigits(int n) {
    if (n == 0)
        return 0;
    return 1+  countDigits(n / 10);
}
int reversenum(int n, int rev) {
    if (n == 0)
        return rev;
    return reversenum(n / 10, rev * 10 + n % 10);
}
int dp[100];
int fibDP(int n) {
    if (n<=2)
        return 1;
    if (dp[n] != -1)
        return dp[n];
    dp[n] = fibDP(n - 1) + fibDP(n - 2);
    return dp[n];
}
// int main()
// {
//     // int n = 5;
//     // print(n);
//     // printf("\n");
//     // printf("Sum: %d\n", sum(n));
//     // printf("Fibonacci: %d\n", fib(n));
//     // int a = 1362358, b = 5;
//     // int count = 0;
//     // int result = mod(a, b);
//     // printf("Modulus: %d\n", result);
//     // printf("GCD: %d\n", GCD(a, b));
//     // printf("Number of digits in %d: %d\n", a, countDigits(a));
//     // int x = 10;
//     // printf("x*2= %d\n", x >> 1);
//     for (int i = 0; i < 100; i++) {
//         dp[i] = -1;
//     }
//     int n = 10;
//     printf("Fibonacci with DP: %d\n", fibDP(n));
//     return 0;


// }

// Recursive function to solve Tower of Hanoi
// n    = number of disks to move
// from = source peg
// to   = destination peg
// aux  = auxiliary (helper) peg
void hanoi(int n, char A, char C, char B) {
    
    // Base case: only one disk left, move it directly
    if (n == 1) {
        printf("Move disk 1 from %c -> %c\n", A, C);
        return;
    }

    // Step 1: move the top (n-1) disks from source to auxiliary
    hanoi(n - 1, A, B, C);

    // Step 2: move the largest disk from source to destination
    printf("Move disk %d from %c -> %c\n", n, A, C);

    // Step 3: move the (n-1) disks from auxiliary to destination
    hanoi(n - 1, B, C, A);
}

int main() {
    int n = 3; // number of disks

    printf("Tower of Hanoi with %d disks:\n", n);
    printf("================================\n");

    // Start: move all disks from peg A to peg C, using peg B as helper
    hanoi(n, 'A', 'C', 'B');

    return 0;
}