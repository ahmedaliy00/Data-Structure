#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 80

int top = -1;

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int isAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^' || c == '%') return 3;
    return 0;
}

void push(char stack[], char value) {
    if (top < size - 1) {
        top++;
        stack[top] = value;
    }
}

char pop(char stack[]) {
    if (top >= 0) return stack[top--];
    return '\0';
}

int main() {
    int j = 0, i = 0;
    char stack[size];
    char output[size] = "";
    char code[] = "(12/3)*(5+25-14)+9";

    for (i = 0; i < strlen(code); i++) {
        if (code[i] == ' ') continue;
        else if (isDigit(code[i]) || isAlpha(code[i])) {
            output[j++] = code[i];
        }
        else if (code[i] == '(') {
            push(stack, code[i]);
        }
        else if (code[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                output[j++] = pop(stack);
            }
            pop(stack); // remove '('
        }
        else {
            while (top != -1 && precedence(code[i]) <= precedence(stack[top])) {
                output[j++] = pop(stack);
            }
            push(stack, code[i]);
        }
    }

    while (top != -1) {
        output[j++] = pop(stack);
    }

    output[j] = '\0';
    printf("Postfix: %s\n", output);
    return 0;
}