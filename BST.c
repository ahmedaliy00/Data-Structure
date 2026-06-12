#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);
    else 
        return search(root->right, key);
    
}

Node* findMin(Node* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, int value) {
    if (root == NULL) return root;

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // case 1: no children
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // case 2:have one child
        else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // case 3: have two children

        // by copying 

        // Node* temp = findMin(root->right);
        // root->data = temp->data;
        // root->right = deleteNode(root->right, temp->data);
        // return root;

        // by merging
        Node * tempR = root->right;
        Node *tempL = root->left;
        Node *po = tempR;
        if(po->left == NULL){
            po->left = tempL;
            free(root);
            return po;
        }
        while(po->left->left != NULL)
            po = po->left;
        Node *newroot = po->left;
        po->left = newroot->right;
        newroot->left = tempL;
        newroot->right = tempR;
        free(root);
        return newroot;    
        }
        
    }

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}


int main() {
    Node* root = NULL;

    root = insert(root, 50);
    insert(root, 30);
    insert(root, 120);
    insert(root, 20);
    insert(root, 309);
    insert(root, 60);
    insert(root, 80);
    insert(root, 40);

    printf("Preorder Traversal: ");
    preorder(root);
    printf("\n");

    // Search
    Node* found = search(root, 40);
    if (found != NULL)
        printf("Found 40\n");
    else
        printf("Not Found\n");

    // Delete
    root = deleteNode(root, 50);

    printf("After Deletion: ");
    inorder(root);
    printf("\n");

    return 0;
}
 