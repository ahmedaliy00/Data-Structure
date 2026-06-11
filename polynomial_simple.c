// #include <stdio.h>
// #include <stdlib.h>

// #define SIZE 80

// /* ── Node ── */
// typedef struct Node {
//     float        coef;
//     int          expon;
//     struct Node *next;
// } Node;

// Node* insert(Node *head, float coef, int expon) {
//     if (coef == 0) return head;

//     /* allocate new node */
//     Node *newNode = (Node*)malloc(sizeof(Node));
//     newNode->coef  = coef;
//     newNode->expon = expon;
//     newNode->next  = NULL;

//     /* insert at head */
//     if (head == NULL || expon > head->expon) {
//         newNode->next = head;
//         return newNode;
//     }

//     /* find position */
//     Node *cur = head;
//     while (cur->next != NULL && cur->next->expon > expon)
//         cur = cur->next;

//     if (cur->expon == expon) { /* duplicate exponent at current node */
//         cur->coef += coef;
//         free(newNode);
//         return head;
//     }
//     /* duplicate exponent: merge */
//     if (cur->next != NULL && cur->next->expon == expon) {
//         cur->next->coef += coef;
//         free(newNode);
//         return head;
//     }

//     newNode->next = cur->next;
//     cur->next = newNode;
//     return head;
// }

// /* ══════════════════════════════════════════
//    PRINT
//    A(x) = 3x^14 + 2x^8 + 1
// ══════════════════════════════════════════ */

// void printPoly(Node *head, char name) {
//     if (head == NULL) {
//         printf("%c(x) = 0\n", name);
//         return;
//     }

//     printf("%c(x) = ", name);
//     Node *cur   = head;
//     int   first = 1;

//     while (cur != NULL) {
//         float c = cur->coef;
//         int   e = cur->expon;

//         /* sign */
//         if (first) {
//             if (c < 0) printf("-");
//             first = 0;
//         } else {
//             printf(c < 0 ? " - " : " + ");
//         }

//         float abs_c = c < 0 ? -c : c;

//         /* coefficient + variable */
//         if (e == 0) {
//             printf("%.4g", abs_c);
//         } else if (abs_c != 1.0) {
//             printf("%.4gx", abs_c);
//             if (e != 1) printf("^%d", e);
//         } else {
//             printf("x");
//             if (e != 1) printf("^%d", e);
//         }

//         cur = cur->next;
//     }
//     printf("\n");
// }

// /* ══════════════════════════════════════════
//    ADD
// ══════════════════════════════════════════ */

// Node* addPoly(Node *a, Node *b) {
//     Node *result = NULL;

//     while (a != NULL && b != NULL) {
//         if (a->expon > b->expon) {
//             result = insert(result, a->coef, a->expon);
//             a = a->next;
//         } else if (b->expon > a->expon) {
//             result = insert(result, b->coef, b->expon);
//             b = b->next;
//         } else {
//             result = insert(result, a->coef + b->coef, a->expon);
//             a = a->next;
//             b = b->next;
//         }
//     }

//     while (a != NULL) { result = insert(result, a->coef, a->expon); a = a->next; }
//     while (b != NULL) { result = insert(result, b->coef, b->expon); b = b->next; }

//     return result;
// }

// /* ══════════════════════════════════════════
//    MULTIPLY
// ══════════════════════════════════════════ */

// Node* multiplyPoly(Node *a, Node *b) {
//     Node *result = NULL;
//     Node *ta     = a;

//     while (ta != NULL) {
//         Node *tb = b;
//         while (tb != NULL) {
//             result = insert(result, ta->coef * tb->coef, ta->expon + tb->expon);
//             tb = tb->next;
//         }
//         ta = ta->next;
//     }

//     return result;
// }

// /* ══════════════════════════════════════════
//    EVALUATE  at x = val
// ══════════════════════════════════════════ */

// float evaluatePoly(Node *head, float val) {
//     float result = 0;
//     Node *cur    = head;

//     while (cur != NULL) {
//         /* compute val^expon manually */
//         float power = 1;
//         int   i;
//         for (i = 0; i < cur->expon; i++)
//             power *= val;

//         result += cur->coef * power;
//         cur = cur->next;
//     }

//     return result;
// }

// /* ══════════════════════════════════════════
//    FREE
// ══════════════════════════════════════════ */

// void freePoly(Node *head) {
//     Node *cur = head;
//     while (cur != NULL) {
//         Node *next = cur->next;
//         free(cur);
//         cur = next;
//     }
// }

// int main() {
//     Node *A = NULL;
//     Node *B = NULL;

//     /* A(x) = 3x^14 + 2x^8 + 1 */
//     A = insert(A, 3,  14);
//     A = insert(A, 2,   8);
//     A = insert(A, 1,   0);

//     /* B(x) = 5x^8 + 4x^3 + 7 */
//     B = insert(B, 5,  8);
//     B = insert(B, 4,  3);
//     B = insert(B, 7,  0);

//     printPoly(A, 'A');
//     printPoly(B, 'B');

//     Node *S = addPoly(A, B);
//     printf("\nSummation:\n");
//     printPoly(S, 'S');

//     Node *M = multiplyPoly(A, B);
//     printf("\nMultiplication:\n");
//     printPoly(M, 'M');

//     float x    = 2.0;
//     float eval = evaluatePoly(A, x);
//     printf("\nA(%.0f) = %.6g\n", x, eval);


//     freePoly(A);
//     freePoly(B);
//     freePoly(S);
//     freePoly(M);

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    float coef;
    int expon;
    struct Node* next;
} Node;

/* insert sorted */
Node* insert(Node* head, float coef, int expon) {

    if (coef == 0)
        return head;

    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->coef = coef;
    newNode->expon = expon;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return head;
    }

    if (expon > head->expon) {
        newNode->next = head;
        return newNode;
    }

    Node* cur = head;

    while (cur->next != NULL && cur->next->expon > expon)
        cur = cur->next;

    if (cur->expon == expon) {
        cur->coef += coef;
        free(newNode);
        return head;
    }

    if (cur->next != NULL && cur->next->expon == expon) {
        cur->next->coef += coef;
        free(newNode);
        return head;
    }

    newNode->next = cur->next;
    cur->next = newNode;

    return head;
}

/* print polynomial */
void printPoly(Node* head) {

    if (head == NULL) {
        printf("0\n");
        return;
    }

    Node* cur = head;

    while (cur != NULL) {

        if (cur->coef > 0 && cur != head)
            printf(" + ");

        if (cur->coef < 0)
            printf(" - ");

        float value = cur->coef;

        if (value < 0)
            value *= -1;

        if (cur->expon == 0)
            printf("%.0f", value);

        else if (cur->expon == 1)
            printf("%.0fx", value);

        else
            printf("%.0fx^%d", value, cur->expon);

        cur = cur->next;
    }

    printf("\n");
}

/* addition */
Node* addPoly(Node* p1, Node* p2) {

    Node* result = NULL;

    while (p1 != NULL) {
        result = insert(result, p1->coef, p1->expon);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        result = insert(result, p2->coef, p2->expon);
        p2 = p2->next;
    }

    return result;
}

/* multiplication */
Node* multiplyPoly(Node* p1, Node* p2) {

    Node* result = NULL;

    Node* a = p1;

    while (a != NULL) {

        Node* b = p2;

        while (b != NULL) {

            result = insert(result,
                            a->coef * b->coef,
                            a->expon + b->expon);

            b = b->next;
        }

        a = a->next;
    }

    return result;
}

/* evaluate */
float evaluate(Node* head, int x) {

    float result = 0;

    while (head != NULL) {

        result += head->coef * pow(x, head->expon);

        head = head->next;
    }

    return result;
}

/* input polynomial */
Node* createPoly() {

    Node* poly = NULL;

    int n;

    printf("How many terms ?\n");

    while (scanf("%d", &n) != 1) {
        printf("Invalid input. Please enter a number: ");

        while (getchar() != '\n');
    }

    for (int i = 0; i < n; i++) {

        float coef;
        int expon;

        printf("Enter coefficient and exponent of term %d :\n", i + 1);

        while (scanf("%f %d", &coef, &expon) != 2) {

            printf("Invalid input. Please enter again: ");

            while (getchar() != '\n');
        }

        poly = insert(poly, coef, expon);
    }

    return poly;
}

/* menu */
void menu() {

    printf("\n===== Polynomial Menu =====\n");

    printf("1. Insert polynomial\n");
    printf("2. Print polynomials\n");
    printf("3. Add polynomials\n");
    printf("4. Multiply polynomials\n");
    printf("5. Evaluate polynomial\n");
    printf("6. Exit\n");
}

int main() {

    Node* poly1 = NULL;
    Node* poly2 = NULL;

    int choice;

    do {

        menu();

        printf("Enter your choice : ");

        while (scanf("%d", &choice) != 1) {

            printf("Invalid input. Please enter a number: ");

            while (getchar() != '\n');
        }

        switch (choice) {

        case 1:

            printf("\nFirst Polynomial:\n");
            poly1 = createPoly();

            printf("\nSecond Polynomial:\n");
            poly2 = createPoly();

            break;

        case 2:

            printf("\nPolynomial 1:\n");
            printPoly(poly1);

            printf("\nPolynomial 2:\n");
            printPoly(poly2);

            break;

        case 3: {

            Node* sum = addPoly(poly1, poly2);

            printf("\nResult of Addition:\n");
            printPoly(sum);

            break;
        }

        case 4: {

            Node* mult = multiplyPoly(poly1, poly2);

            printf("\nResult of Multiplication:\n");
            printPoly(mult);

            break;
        }

        case 5: {

            int x;

            printf("Enter x value : ");

            while (scanf("%d", &x) != 1) {

                printf("Invalid input. Please enter a number: ");

                while (getchar() != '\n');
            }

            printf("\nResult = %.2f\n", evaluate(poly1, x));

            break;
        }

        case 6:

            printf("Program ended.\n");
            break;

        default:

            printf("Invalid choice.\n");
        }

    } while (choice != 6);

    return 0;
}