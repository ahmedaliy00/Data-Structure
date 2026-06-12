#include <stdio.h>
#define MAX 100

typedef struct {
    int data[MAX];
    int front;
    int rear;
} Queue;

// ============================================
//           Basic ADT Functions
// ============================================

void construct(Queue *q) {
    q->front = -1;
    q->rear  = -1;
    for (int i = 0; i < MAX; i++)
        q->data[i] = -1;
}

int isEmpty(Queue *q) {
    return (q->front == -1);
}

int isFull(Queue *q) {
    return (q->rear == MAX - 1);
}

void enqueue(Queue *q, int val) {
    if (isFull(q)) { printf("Queue is full!\n"); return; }
    if (isEmpty(q)) q->front = 0;
    q->rear++;
    q->data[q->rear] = val;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) { printf("Queue is empty!\n"); return -1; }
    int val = q->data[q->front];
    q->data[q->front] = -1;
    if (q->front == q->rear) { q->front = -1; q->rear = -1; }
    else q->front++;
    return val;
}

int peek(Queue *q) {
    if (isEmpty(q)) { printf("Queue is empty!\n"); return -1; }
    return q->data[q->front];
}

// ============================================
//         display — using ADT only
// ============================================
void display(Queue *q) {
    if (isEmpty(q)) { printf("Queue is empty!\n"); return; }

    Queue temp;
    construct(&temp);

    printf("Queue (front -> rear): ");

    // Step 1: dequeue from q → print → enqueue in temp
    while (!isEmpty(q)) {
        int val = dequeue(q);
        printf("%d ", val);
        enqueue(&temp, val);
    }
    printf("\n");

    // Step 2: restore q from temp
    while (!isEmpty(&temp))
        enqueue(q, dequeue(&temp));
}

// ============================================
//         getSum — using ADT only
// ============================================
int getSum(Queue *q) {
    if (isEmpty(q)) return 0;

    Queue temp;
    construct(&temp);
    int total = 0;

    // Step 1: dequeue → add to total → enqueue in temp
    while (!isEmpty(q)) {
        int val = dequeue(q);
        total += val;
        enqueue(&temp, val);
    }

    // Step 2: restore q from temp
    while (!isEmpty(&temp))
        enqueue(q, dequeue(&temp));

    return total;
}

// ============================================
//         count — using ADT only
// ============================================
int count(Queue *q) {
    if (isEmpty(q)) return 0;

    Queue temp;
    construct(&temp);
    int cnt = 0;

    // Step 1: dequeue → count → enqueue in temp
    while (!isEmpty(q)) {
        enqueue(&temp, dequeue(q));
        cnt++;
    }

    // Step 2: restore q from temp
    while (!isEmpty(&temp))
        enqueue(q, dequeue(&temp));

    return cnt;
}

// ============================================
//         getAverage — using ADT only
// ============================================
float getAverage(Queue *q) {
    if (isEmpty(q)) return 0;
    // getSum و count بيحافظوا على q داخلياً
    return (float)getSum(q) / count(q);
}

// ============================================
//         getMin — using ADT only
// ============================================
int getMin(Queue *q) {
    if (isEmpty(q)) return -1;

    Queue temp;
    construct(&temp);

    // dequeue أول عنصر كـ initial min
    int val = dequeue(q);
    int min = val;
    enqueue(&temp, val);

    // Step 1: dequeue → compare → enqueue in temp
    while (!isEmpty(q)) {
        val = dequeue(q);
        if (val < min) min = val;
        enqueue(&temp, val);
    }

    // Step 2: restore q from temp
    while (!isEmpty(&temp))
        enqueue(q, dequeue(&temp));

    return min;
}

// ============================================
//         getMax — using ADT only
// ============================================
int getMax(Queue *q) {
    if (isEmpty(q)) return -1;

    Queue temp;
    construct(&temp);

    int val = dequeue(q);
    int max = val;
    enqueue(&temp, val);

    // Step 1: dequeue → compare → enqueue in temp
    while (!isEmpty(q)) {
        val = dequeue(q);
        if (val > max) max = val;
        enqueue(&temp, val);
    }

    // Step 2: restore q from temp
    while (!isEmpty(&temp))
        enqueue(q, dequeue(&temp));

    return max;
}

// ============================================
//         search — using ADT only
// ============================================
int search(Queue *q, int target) {
    if (isEmpty(q)) return 0;

    Queue temp;
    construct(&temp);
    int found = 0;

    // Step 1: dequeue → check → enqueue in temp
    while (!isEmpty(q)) {
        int val = dequeue(q);
        if (val == target) found = 1;
        enqueue(&temp, val);
    }

    // Step 2: restore q from temp
    while (!isEmpty(&temp))
        enqueue(q, dequeue(&temp));

    return found;
}

// ============================================
//   reverse — محتاج Stack عشان يعكس فعلاً ✅
// ============================================
void reverse(Queue *q) {
    if (isEmpty(q)) return;

    int stack[MAX];
    int top = -1;

    // Step 1: dequeue من q → push في stack
    while (!isEmpty(q))
        stack[++top] = dequeue(q);

    // Step 2: pop من stack → enqueue في q (معكوسة ✅)
    while (top >= 0)
        enqueue(q, stack[top--]);
}

// ============================================
//                   Main
// ============================================
int main() {
    Queue q;
    construct(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    display(&q);
    // Queue (front -> rear): 10 20 30 40 50

    printf("Peek:      %d\n",   peek(&q));        // 10
    printf("Count:     %d\n",   count(&q));       // 5
    printf("Sum:       %d\n",   getSum(&q));      // 150
    printf("Average:   %.1f\n", getAverage(&q));  // 30.0
    printf("Min:       %d\n",   getMin(&q));      // 10
    printf("Max:       %d\n",   getMax(&q));      // 50
    printf("Search 30: %s\n",   search(&q, 30) ? "Found" : "Not Found");
    printf("Search 99: %s\n",   search(&q, 99) ? "Found" : "Not Found");

    printf("\nDequeue: %d\n", dequeue(&q));        // 10
    display(&q);
    // Queue (front -> rear): 20 30 40 50

    reverse(&q);
    printf("After reverse: ");
    display(&q);
    // Queue (front -> rear): 50 40 30 20

    return 0;
}
// ============================================circulat ===================================================
// #include <stdio.h>
// #define MAX 5  // صغّلنا الحجم عشان نشوف الـ circular بوضوح

// typedef struct {
//     int data[MAX];
//     int front;
//     int rear;
//     int size;  // عداد العناصر الموجودة فعلاً
// } Queue;

// // ============================================
// //           Basic ADT Functions
// // ============================================

// void construct(Queue *q) {
//     q->front = 0;
//     q->rear  = 0;
//     q->size  = 0;
//     for (int i = 0; i < MAX; i++)
//         q->data[i] = -1;
// }

// int isEmpty(Queue *q) {
//     return (q->size == 0);
// }

// int isFull(Queue *q) {
//     return (q->size == MAX);
// }

// void enqueue(Queue *q, int val) {
//     if (isFull(q)) { printf("Queue is full!\n"); return; }
//     q->data[q->rear] = val;
//     q->rear = (q->rear + 1) % MAX;   // ← الـ circular magic
//     q->size++;
// }

// int dequeue(Queue *q) {
//     if (isEmpty(q)) { printf("Queue is empty!\n"); return -1; }
//     int val = q->data[q->front];
//     q->data[q->front] = -1;
//     q->front = (q->front + 1) % MAX; // ← الـ circular magic
//     q->size--;
//     return val;
// }

// int peek(Queue *q) {
//     if (isEmpty(q)) { printf("Queue is empty!\n"); return -1; }
//     return q->data[q->front];
// }

// // ============================================
// //         display — using ADT only
// // ============================================
// void display(Queue *q) {
//     if (isEmpty(q)) { printf("Queue is empty!\n"); return; }

//     Queue temp;
//     construct(&temp);

//     printf("Queue (front -> rear): ");

//     // Step 1: dequeue from q → print → enqueue in temp
//     while (!isEmpty(q)) {
//         int val = dequeue(q);
//         printf("%d ", val);
//         enqueue(&temp, val);
//     }
//     printf("\n");

//     // Step 2: restore q from temp
//     while (!isEmpty(&temp))
//         enqueue(q, dequeue(&temp));
// }

// // ============================================
// //         getSum — using ADT only
// // ============================================
// int getSum(Queue *q) {
//     if (isEmpty(q)) return 0;

//     Queue temp;
//     construct(&temp);
//     int total = 0;

//     // Step 1: dequeue → add to total → enqueue in temp
//     while (!isEmpty(q)) {
//         int val = dequeue(q);
//         total += val;
//         enqueue(&temp, val);
//     }

//     // Step 2: restore q from temp
//     while (!isEmpty(&temp))
//         enqueue(q, dequeue(&temp));

//     return total;
// }

// // ============================================
// //         count — using ADT only
// // ============================================
// int count(Queue *q) {
//     // size بيحفظ العدد دايماً — مش محتاج temp
//     return q->size;
// }

// // ============================================
// //         getAverage — using ADT only
// // ============================================
// float getAverage(Queue *q) {
//     if (isEmpty(q)) return 0;
//     return (float)getSum(q) / count(q);
// }

// // ============================================
// //         getMin — using ADT only
// // ============================================
// int getMin(Queue *q) {
//     if (isEmpty(q)) return -1;

//     Queue temp;
//     construct(&temp);

//     int val = dequeue(q);
//     int min = val;
//     enqueue(&temp, val);

//     // Step 1: dequeue → compare → enqueue in temp
//     while (!isEmpty(q)) {
//         val = dequeue(q);
//         if (val < min) min = val;
//         enqueue(&temp, val);
//     }

//     // Step 2: restore q from temp
//     while (!isEmpty(&temp))
//         enqueue(q, dequeue(&temp));

//     return min;
// }

// // ============================================
// //         getMax — using ADT only
// // ============================================
// int getMax(Queue *q) {
//     if (isEmpty(q)) return -1;

//     Queue temp;
//     construct(&temp);

//     int val = dequeue(q);
//     int max = val;
//     enqueue(&temp, val);

//     // Step 1: dequeue → compare → enqueue in temp
//     while (!isEmpty(q)) {
//         val = dequeue(q);
//         if (val > max) max = val;
//         enqueue(&temp, val);
//     }

//     // Step 2: restore q from temp
//     while (!isEmpty(&temp))
//         enqueue(q, dequeue(&temp));

//     return max;
// }

// // ============================================
// //         search — using ADT only
// // ============================================
// int search(Queue *q, int target) {
//     if (isEmpty(q)) return 0;

//     Queue temp;
//     construct(&temp);
//     int found = 0;

//     // Step 1: dequeue → check → enqueue in temp
//     while (!isEmpty(q)) {
//         int val = dequeue(q);
//         if (val == target) found = 1;
//         enqueue(&temp, val);
//     }

//     // Step 2: restore q from temp
//     while (!isEmpty(&temp))
//         enqueue(q, dequeue(&temp));

//     return found;
// }

// // ============================================
// //   reverse — محتاج Stack عشان يعكس فعلاً
// // ============================================
// void reverse(Queue *q) {
//     if (isEmpty(q)) return;

//     int stack[MAX];
//     int top = -1;

//     // Step 1: dequeue من q → push في stack
//     while (!isEmpty(q))
//         stack[++top] = dequeue(q);

//     // Step 2: pop من stack → enqueue في q (معكوسة ✅)
//     while (top >= 0)
//         enqueue(q, stack[top--]);
// }

// // ============================================
// //         printRaw — تطبع الـ array كما هي
// //         عشان نشوف الـ circular بوضوح
// // ============================================
// void printRaw(Queue *q) {
//     printf("Raw array: [ ");
//     for (int i = 0; i < MAX; i++)
//         printf("%d ", q->data[i]);
//     printf("]  front=%d  rear=%d  size=%d\n",
//            q->front, q->rear, q->size);
// }

// // ============================================
// //                   Main
// // ============================================
// int main() {

//     Queue q;
//     construct(&q);

//     // --- enqueue 5 عناصر (الـ array اتملت) ---
//     enqueue(&q, 10);
//     enqueue(&q, 20);
//     enqueue(&q, 30);
//     enqueue(&q, 40);
//     enqueue(&q, 50);

//     display(&q);
//     printRaw(&q);
//     // Raw array: [ 10 20 30 40 50 ]  front=0  rear=0  size=5

//     // --- dequeue 2 عناصر من الأمام ---
//     printf("\nDequeue: %d\n", dequeue(&q));   // 10
//     printf("Dequeue: %d\n",   dequeue(&q));   // 20
//     printRaw(&q);
//     // Raw array: [ -1 -1 30 40 50 ]  front=2  rear=0  size=3

//     // --- enqueue تاني → rear هيلف من الأول (circular!) ---
//     enqueue(&q, 60);
//     enqueue(&q, 70);
//     printRaw(&q);
//     // Raw array: [ 60 70 30 40 50 ]  front=2  rear=2  size=5
//     //             ↑↑ اتكتبوا في الأماكن الفاضية في الأول!

//     display(&q);
//     // Queue (front -> rear): 30 40 50 60 70

//     printf("\nPeek:      %d\n",   peek(&q));        // 30
//     printf("Count:     %d\n",     count(&q));       // 5
//     printf("Sum:       %d\n",     getSum(&q));      // 200
//     printf("Average:   %.1f\n",   getAverage(&q));  // 40.0
//     printf("Min:       %d\n",     getMin(&q));      // 30
//     printf("Max:       %d\n",     getMax(&q));      // 70
//     printf("Search 50: %s\n",     search(&q, 50) ? "Found" : "Not Found");
//     printf("Search 99: %s\n",     search(&q, 99) ? "Found" : "Not Found");

//     reverse(&q);
//     printf("\nAfter reverse: ");
//     display(&q);
//     // Queue (front -> rear): 70 60 50 40 30

//     return 0;
// }