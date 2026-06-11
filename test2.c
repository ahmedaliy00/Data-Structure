#include <stdio.h>
#include <stdlib.h>

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

    if ( expon > head->expon) {
        newNode->next = head;
        head = newNode;
        return head;
    }

    Node* cur = head;

    while (cur->next != NULL && cur->next->expon > expon)
        cur = cur->next;

    /* same exponent */
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

    /* insert in middle or end */
    newNode->next = cur->next;
    cur->next = newNode;

    return head;
}

/* print polynomial */
void printPoly(Node* head) {

    if (head == NULL) {
        printf("your have no polynomial yet\n");
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
    if (p1 == NULL&& p2 == NULL) {
        printf("you should insert at least one polynomial first\n");
        return NULL;
    }

    Node* result = NULL;

    Node* a = p1;
    Node* b = p2;

    while (a != NULL && b != NULL) {

        if (a->expon > b->expon) {
            result = insert(result, a->coef, a->expon);
            a = a->next;
        }

        else if (a->expon < b->expon) {
            result = insert(result, b->coef, b->expon);
            b = b->next;
        }

        else {
            result = insert(result,a->coef + b->coef,a->expon);
            a = a->next;
            b = b->next;
        }
    }

    while (a != NULL) {
        result = insert(result, a->coef, a->expon);
        a = a->next;
    }

    while (b != NULL) {
        result = insert(result, b->coef, b->expon);
        b = b->next;
    }

    return result;
}

/* multiplication */
Node* multiplyPoly(Node* p1, Node* p2) {
        if (p1 == NULL || p2 == NULL) {
            printf("you should insert both polynomials first\n");
            return NULL;
        }

    Node* result = NULL;

    Node* a = p1;

    while (a != NULL) {

        Node* b = p2;

        while (b != NULL) {

            float coef = a->coef * b->coef;
            int expon = a->expon + b->expon;

            result = insert(result, coef, expon);

            b = b->next;
        }

        a = a->next;
    }

    return result;
}

float getpow(float base, float exp) {

    if (exp == 0)
        return 1;

    else if (exp > 0)
        return base * getpow(base, exp - 1);

    else
        return 1.00 / base * getpow(base, exp + 1);
}
float evaluate(Node* head, int x) {
    if (head == NULL) {
        printf("you should insert a polynomial first\n");
        return 0;
    }

    float result = 0;

    Node* cur = head;

    while (cur != NULL) {

        result += cur->coef * getpow(x, cur->expon);

        cur = cur->next;
    }
    return result;
}
Node* createPoly(Node* poly ) {

    int n;
    printf("How many terms in the polynomial ?\n");
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
            poly1 = createPoly(poly1);

            printf("\nSecond Polynomial:\n");
            poly2 = createPoly(poly2);
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
            printf("Program Exiting.\n");
            break;
        default:
            printf("Invalid choice...try again\n");
        }
    } while (choice != 6);
    return 0;
}