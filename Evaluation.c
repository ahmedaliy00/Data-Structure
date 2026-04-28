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

float oprator(char c, float op1, float op2) {
    float result;  
    switch(c) {
        case '+':
            result = op1 + op2;
            return result;
        case '-':
            result = op1 - op2;
            return result;
        case '/':
            if (op2 != 0)
                result = op1 / op2;
            else
                printf("Error: division by zero\n");
            return result;
        case '*':
            result = op1 * op2;
            return result;
        default:
            printf("Error: unknown operator\n");
    }
    return 0;
}

void push(float stack[], float value) {
    if (top < size - 1) {
        top++;
        stack[top] = value;
    }
}

float pop(float stack[]) {
    if (top >= 0) return stack[top--];
    return 0;
}

float evalution(char ex[], float stack[]) {
    for (int i = 0; i < strlen(ex); i++) {
        if (isDigit(ex[i]))
            push(stack, ex[i] - '0');
        else {
            float op2 = pop(stack);
            float op1 = pop(stack);
            float result = oprator(ex[i], op1, op2);
            push(stack, result);
        }
    }
    float final_result = pop(stack); 
    return final_result;
}

int main() {
    float stack[size];
    char code[] = "372/+5-";
    printf("Result = %f\n", evalution(code, stack));
    return 0;
}