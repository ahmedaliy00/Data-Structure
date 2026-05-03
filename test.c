#include <stdio.h>
#include <stdlib.h>
#define size 80

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

typedef struct {
    float data[size];
    int top;
} FloatStack;

void float_push(FloatStack *s, float value) {
    if (s->top < size - 1)
        s->data[++(s->top)] = value;
    else
        printf("Error: stack overflow\n");
}

float float_pop(FloatStack *s) {
    if (s->top >= 0)
        return s->data[(s->top)--];
    printf("Error: stack underflow\n");
    return 0;
}

typedef struct {
    char data[size];
    int top;
} CharStack;

void char_push(CharStack *s, char value) {
    if (s->top < size - 1)
        s->data[++(s->top)] = value;
    else
        printf("Error: stack overflow\n");
}

char char_pop(CharStack *s) {
    if (s->top >= 0)
        return s->data[(s->top)--];
    return '\0';
}

char char_peek(CharStack *s) {
    if (s->top >= 0)
        return s->data[s->top];
    return '\0';
}
float  gitpow(float base,float exp)
{
    if(exp==0)
        return 1;
    else
    if(exp>0)
        return base*gitpow(base,exp-1);
    else
        return 1.00/gitpow(base,-exp);    /*if exp is negative */
}
float gitmod(float a,float b)
{
    if(b==0) {printf("Error: Modulo by zero\n"); return 0;}
    int quotient = (int)(a / b); /*if a==0 so quotient will be 0 and the result will be 0 as well */
    return a - b * quotient;     /*if a less than b, the result will be a */
}

float oprator(char c, float op1, float op2) {
    switch(c) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/':
            if (op2 != 0) return op1 / op2;
            printf("Error: division by zero\n");
            return 0;
        case '^': 
            return gitpow(op1, op2);
        case '%':
            return gitmod(op1, op2);
        default:
            printf("Error: unknown operator %c\n", c);
            return 0;
    }
}

float evalution(char ex[], FloatStack *stack) {
    int i = 0;
    while (ex[i] != '\0') {
        if (ex[i] == ' ') { i++; continue; }

        if (isDigit(ex[i])) {
            float num = 0;
            while (isDigit(ex[i]))
                num = num * 10 + (ex[i++] - '0');
            float_push(stack, num);
            continue;
        }

        if (precedence(ex[i]) > 0) {
            float op2 = float_pop(stack);
            float op1 = float_pop(stack);
            float_push(stack, oprator(ex[i], op1, op2));
        }
        i++;
    }
    return float_pop(stack);
}

void infixToPostfix(char code[], char output[]) {
    CharStack stack;
    stack.top = -1;
    int i = 0, j = 0;

    while (code[i] != '\0') {
        if (code[i] == ' ') { i++; continue; }

        if (isDigit(code[i]) || isAlpha(code[i])) {
            while (isDigit(code[i]) || isAlpha(code[i]))
                output[j++] = code[i++];
            output[j++] = ' ';
            continue;
        }

        if (code[i] == '(') {
            char_push(&stack, code[i++]);
            continue;
        }

        if (code[i] == ')') {
            if (stack.top == -1) {
                printf("Error\n");
                output[0] = '\0';
                return;
            }
            while (stack.top != -1 && char_peek(&stack) != '(') {
                output[j++] = char_pop(&stack);
                output[j++] = ' ';
            }
            char_pop(&stack); // pop the '('
            i++;
            continue;
        }

        if (precedence(code[i]) > 0) {
            while (stack.top != -1 &&
                   char_peek(&stack) != '(' &&
                   precedence(code[i]) <= precedence(char_peek(&stack))) {
                output[j++] = char_pop(&stack);
                output[j++] = ' ';
            }
            char_push(&stack, code[i++]);
        } else 
            i++;
    }

    while (stack.top != -1) {
        if (char_peek(&stack) == '(') {
            printf("Error: mismatched parentheses\n");
            output[0] ='\0';
            return;
        }
        output[j++] = char_pop(&stack);
        output[j++] = ' ';
    }

    if (j > 0 && output[j-1] == ' ') j--;
    output[j] = '\0';
}

int main() {
    FloatStack stack;
    stack.top = -1;

    char output[size * 2];
    char code[] = "(12/3)*(5+25%14)+9";
    infixToPostfix(code, output);
    printf("Postfix: %s\n", output);
    printf("Result = %f\n", evalution(output, &stack));

    return 0;
}