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

int getBalance(struct Node *root) {
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

    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node* minValueNode(struct Node *root) {
    struct Node *current = root;

    while (current->left != NULL)
        current = current->left;

    return current;
}

struct Node* deleteNode(struct Node *root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {
        if (root->left == NULL || root->right == NULL) {
            struct Node *temp;

            if (root->left != NULL)
                temp = root->left;
            else
                temp = root->right;

            if (temp == NULL) {
                free(root);
                return NULL;
            }
            else {
                struct Node *old = root;
                root = temp;
                free(old);
            }
        }
        else {
            struct Node *temp = minValueNode(root->right);

            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preorder(struct Node *root) {
    if (root == NULL)
        return;

    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

int main() {
    struct Node *root = NULL;
    int n, key, d;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        root = insert(root, key);
    }

    scanf("%d", &d);

    printf("Preorder of AVL tree\n");
    preorder(root);
    printf("\n");

    root = deleteNode(root, d);

    printf("Preorder after deletion of the element\n");
    preorder(root);
    printf("\n");

    return 0;
}