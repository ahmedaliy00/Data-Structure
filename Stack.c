#include <stdio.h>
#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

// ============================================
//           Basic ADT Functions
// ============================================

void construct(Stack *s) {
    s->top = -1;
    for (int i = 0; i < MAX; i++)
        s->data[i] = -1;
}

int isEmpty(Stack *s) {
    return (s->top == -1);
}

int isFull(Stack *s) {
    return (s->top == MAX - 1);
}

void push(Stack *s, int val) {
    if (isFull(s)) { printf("Stack is full!\n"); return; }
    s->top++;
    s->data[s->top] = val;
}

int pop(Stack *s) {
    if (isEmpty(s)) { printf("Stack is empty!\n"); return -1; }
    int val = s->data[s->top];
    s->data[s->top] = -1;
    s->top--;
    return val;
}

int peek(Stack *s) {
    if (isEmpty(s)) { printf("Stack is empty!\n"); return -1; }
    return s->data[s->top];
}

// ============================================
//         display — using ADT only
// ============================================
void display(Stack *s) {
    if (isEmpty(s)) { printf("Stack is empty!\n"); return; }

    Stack temp;
    construct(&temp);

    printf("Stack (top -> bottom): ");

    // Step 1: pop from s → print → push in temp
    while (!isEmpty(s)) {
        int val = pop(s);
        printf("%d ", val);
        push(&temp, val);
    }
    printf("\n");

    // Step 2: restore s from temp
    while (!isEmpty(&temp))
        push(s, pop(&temp));
}

// ============================================
//         getSum — using ADT only
// ============================================
int getSum(Stack *s) {
    if (isEmpty(s)) return 0;

    Stack temp;
    construct(&temp);
    int total = 0;

    // Step 1: pop → add to total → push in temp
    while (!isEmpty(s)) {
        int val = pop(s);
        total += val;
        push(&temp, val);
    }

    // Step 2: restore s from temp
    while (!isEmpty(&temp))
        push(s, pop(&temp));

    return total;
}

// ============================================
//         count — using ADT only
// ============================================
int count(Stack *s) {
    if (isEmpty(s)) return 0;

    Stack temp;
    construct(&temp);
    int cnt = 0;

    // Step 1: pop → count → push in temp
    while (!isEmpty(s)) {
        push(&temp, pop(s));
        cnt++;
    }

    // Step 2: restore s from temp
    while (!isEmpty(&temp))
        push(s, pop(&temp));

    return cnt;
}

// ============================================
//         getAverage — using ADT only
// ============================================
float getAverage(Stack *s) {
    if (isEmpty(s)) return 0;
    // getSum و count بيحافظوا على s داخلياً
    return (float)getSum(s) / count(s);
}

// ============================================
//         getMin — using ADT only
// ============================================
int getMin(Stack *s) {
    if (isEmpty(s)) return -1;

    Stack temp;
    construct(&temp);

    // pop أول عنصر كـ initial min
    int val = pop(s);
    int min = val;
    push(&temp, val);

    // Step 1: pop → compare → push in temp
    while (!isEmpty(s)) {
        val = pop(s);
        if (val < min) min = val;
        push(&temp, val);
    }

    // Step 2: restore s from temp
    while (!isEmpty(&temp))
        push(s, pop(&temp));

    return min;
}

// ============================================
//         getMax — using ADT only
// ============================================
int getMax(Stack *s) {
    if (isEmpty(s)) return -1;

    Stack temp;
    construct(&temp);

    int val = pop(s);
    int max = val;
    push(&temp, val);

    // Step 1: pop → compare → push in temp
    while (!isEmpty(s)) {
        val = pop(s);
        if (val > max) max = val;
        push(&temp, val);
    }

    // Step 2: restore s from temp
    while (!isEmpty(&temp))
        push(s, pop(&temp));

    return max;
}

// ============================================
//         search — using ADT only
// ============================================
int search(Stack *s, int target) {
    if (isEmpty(s)) return 0;

    Stack temp;
    construct(&temp);
    int found = 0;

    // Step 1: pop → check → push in temp
    while (!isEmpty(s)) {
        int val = pop(s);
        if (val == target) found = 1;
        push(&temp, val);
    }

    // Step 2: restore s from temp
    while (!isEmpty(&temp))
        push(s, pop(&temp));

    return found;
}

// ============================================
//   reverse — using ADT only
// ============================================
void reverse(Stack *s) {
    if (isEmpty(s)) return;

    Stack temp;
    construct(&temp);

    // Step 1: pop من s → push في temp (temp معكوسة)
    while (!isEmpty(s))
        push(&temp, pop(s));

    // Step 2: pop من temp → push في s (s رجعت معكوسة ✅)
    while (!isEmpty(&temp))
        push(s, pop(&temp));
}

// ============================================
//                   Main
// ============================================
int main() {
    Stack s;
    construct(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    push(&s, 40);
    push(&s, 50);

    display(&s);
    // Stack (top -> bottom): 50 40 30 20 10

    printf("Peek:      %d\n",   peek(&s));        // 50
    printf("Count:     %d\n",   count(&s));       // 5
    printf("Sum:       %d\n",   getSum(&s));      // 150
    printf("Average:   %.1f\n", getAverage(&s));  // 30.0
    printf("Min:       %d\n",   getMin(&s));      // 10
    printf("Max:       %d\n",   getMax(&s));      // 50
    printf("Search 30: %s\n",   search(&s, 30) ? "Found" : "Not Found");
    printf("Search 99: %s\n",   search(&s, 99) ? "Found" : "Not Found");

    printf("\nPop: %d\n", pop(&s));               // 50
    display(&s);
    // Stack (top -> bottom): 40 30 20 10

    reverse(&s);
    printf("After reverse: ");
    display(&s);
    // Stack (top -> bottom): 10 20 30 40

    return 0;
}