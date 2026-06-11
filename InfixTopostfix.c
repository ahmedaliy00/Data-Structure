#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 100

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
            return 1.00/base * gitpow(base,exp+1);    /*if exp is negative */
}
float gitmod(float a,float b)
{
    if(b==0) {printf("Error: Modulo by zero\n"); return 0;}
    int quotient = (int)(a / b); /*if a==0 so quotient will be 0 and the result will be 0 as well */
    return a - b * quotient;     /*if a less than b, the result will be a */
}
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
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

float evaluation(char ex[]) {
    FloatStack stack;
    stack.top = -1;
    int i = 0;
    while (ex[i] != '\0') {
        if (ex[i] == ' ') { i++; continue; }
        char  temp[size];
        int k = 0;
        if (isDigit(ex[i])|| ex[i] == '.' || ex[i] == '-' && (isDigit(ex[i+1]) || ex[i+1] == '.')) {
                // num = num * 10 + (ex[i++] - '0');      //This line is incorrect for floating-point numbers  I will use atof to solve this problem
                if (ex[i] == '-' ) {
                    temp[k++] = ex[i++];
                }
                while (isDigit(ex[i]) || ex[i] == '.'){
                    temp[k++] = ex[i++];
                }
            
             temp[k] = '\0';
            float_push(&stack, atof(temp));
            continue;
        }
        if (isAlpha(ex[i])) {
            printf("Error: invalid character %c\n", ex[i]);
            return 0;
        }

        if (precedence(ex[i]) > 0) {
            float op2 = float_pop(&stack);
            float op1 = float_pop(&stack);
            float_push(&stack, oprator(ex[i], op1, op2));
        }
        i++;
    }

    if (stack.top == 0) {
        float result = float_pop(&stack);
        return result;
    }else if (stack.top > 0) {
        printf("Error: too many operands\n");
        return 0;
    } else {
        printf("Error: no result on stack...failed calculation\n");
        return 0;
    }
}

int  infixToPostfix(char code[], char output[]) {
    CharStack stack;
    stack.top = -1;
    int i = 0, j = 0;
    int hasAlpha = 0;

    while (code[i] != '\0') {
        if (code[i] == ' '||code[i] == '\n') { i++; continue; }
        if ( isOperator(code[i])&& code[i] != '-' && (i == 0 || code[i-1] == '(' || isOperator(code[i-1]))){
              printf("Error: invalid character you should start with oprand \n");
              output[0] = '\0';
              return 0;
        }
        if (isDigit(code[i]) || isAlpha(code[i])||code[i] == '.' || code[i] == '-' && (i==0 || code[i-1] == '(' || isOperator(code[i-1]))) {
            if (code[i] == '-' ) {
                output[j++] = code[i++]; // include the negative sign
            }
            if (isAlpha(code[i])) hasAlpha = 1;
            while (isDigit(code[i]) || isAlpha(code[i]) || code[i] == '.'||code[i]== ' '){
                if (code[i]== ' ') {i++; continue;} // skip spaces within numbers
                output[j++] = code[i++];
            }
            output[j++] = ' ';
            continue;
        }

        if (code[i] == '(') {
            char_push(&stack, code[i++]);
            continue;
        }

        if (code[i] == ')') {
            if (stack.top == -1) {
                printf("Error: mismatched parentheses\n");
                output[0] = '\0';
                return 0;
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
            return 0;
        }
        output[j++] = char_pop(&stack);
        output[j++] = ' ';
    }

    if (j > 0 && output[j-1] == ' ') j--;
    output[j] = '\0';
    return hasAlpha;
}
int main()
{
    char code[size];
    char output[size * 2];
    int choice;
    int hasLetters;

    do {
        printf("\n1. Enter infix expression\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");

        while (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number: ");
            while (getchar() != '\n');
        }

        while (getchar() != '\n'); // remove newline aftrer scanf and before fgets

        if (choice == 1) {

            printf("Enter infix expression: ");
            fgets(code, sizeof(code), stdin);

            code[strcspn(code, "\n")] = '\0';

            hasLetters = infixToPostfix(code, output);

            if (hasLetters) {
                printf("Postfix: %s\n", output);
                printf("Evaluation skipped due to presence of variables.\n");
            }
            else if (output[0] == '\0')

                printf("Postfix conversion failed due to errors.\n");
            
            else {
                printf("Postfix: %s\n", output);
                printf("Final Result = %f\n", evaluation(output));
            }
        }
        else if (choice == 2)
            printf("Exiting...\n");

        else 
            printf("Invalid choice. Please enter 1 or 2.\n");

    } while (choice != 2);
    return 0;
}    