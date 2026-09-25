// You are using GCC
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
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

struct Node* createNode(int key) {
    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->key = key;
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
    struct Node *temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

struct Node* insert(struct Node *root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;

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

int main() {
    struct Node *root = NULL;
    int key;

    while (scanf("%d", &key) == 1 && key != -1) {
        root = insert(root, key);
    }

    printf("Height of the AVL tree: %d\n", height(root));

    return 0;
}