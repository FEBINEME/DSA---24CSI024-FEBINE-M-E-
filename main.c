// You are using GCC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int key;
    char code[32];
    int height;
    struct Node *left;
    struct Node *right;
};

int height(struct Node *root) {
    if (root == NULL)
        return 0;
    return root->height;
}

int max(int a, int b) {
    return a > b ? a : b;
}

struct Node* createNode(int key, char code[]) {
    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->key = key;
    strcpy(newNode->code, code);
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

int balance(struct Node *root) {
    if (root == NULL)
        return 0;

    return height(root->left) - height(root->right);
}

struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

struct Node* insert(struct Node *root, int key, char code[]) {
    if (root == NULL)
        return createNode(key, code);

    if (key < root->key)
        root->left = insert(root->left, key, code);
    else
        root->right = insert(root->right, key, code);

    root->height = 1 + max(height(root->left), height(root->right));

    int b = balance(root);

    if (b > 1 && key < root->left->key)
        return rightRotate(root);

    if (b < -1 && key > root->right->key)
        return leftRotate(root);

    if (b > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node* deleteMin(struct Node *root) {
    if (root == NULL)
        return NULL;

    if (root->left == NULL) {
        struct Node *temp = root->right;
        free(root);
        return temp;
    }

    root->left = deleteMin(root->left);

    root->height = 1 + max(height(root->left), height(root->right));

    int b = balance(root);

    if (b > 1 && balance(root->left) >= 0)
        return rightRotate(root);

    if (b > 1 && balance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && balance(root->right) <= 0)
        return leftRotate(root);

    if (b < -1 && balance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(struct Node *root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d %s\n", root->key, root->code);
    inorder(root->right);
}

int main() {
    int n;
    int key;
    char code[32];

    struct Node *root = NULL;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %s", &key, code);
        root = insert(root, key, code);
    }

    printf("In-order traversal before deletion:\n");
    inorder(root);

    root = deleteMin(root);

    printf("In-order traversal after deletion:\n");
    inorder(root);

    return 0;
}