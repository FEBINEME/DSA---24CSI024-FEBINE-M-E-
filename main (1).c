// You are using GCC
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
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

struct Node* createNode(int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
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

struct Node* insert(struct Node *root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && data < root->left->data)
        return rightRotate(root);

    if (balance < -1 && data > root->right->data)
        return leftRotate(root);

    if (balance > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && data < root->right->data) {
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

struct Node* deleteNode(struct Node *root, int data) {
    if (root == NULL)
        return NULL;

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = deleteNode(root->right, data);
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
                *root = *temp;
                free(temp);
            }
        }
        else {
            struct Node *temp = minValueNode(root->right);

            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
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

void inorder(struct Node *root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main() {
    int n, m;
    struct Node *root = NULL;

    scanf("%d", &n);

    int values[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &values[i]);

    int duplicates = 0;

    for (int i = 0; i < n; i++) {
        int before = 0;

        for (int j = 0; j < i; j++) {
            if (values[j] == values[i]) {
                before = 1;
                break;
            }
        }

        if (before)
            duplicates++;
        else
            root = insert(root, values[i]);
    }

    printf("AVL Tree after removing duplicates: ");
    inorder(root);
    printf("\n");

    printf("Total number of duplicates: %d\n", duplicates);

    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int value;
        scanf("%d", &value);
        root = deleteNode(root, value);
    }

    printf("AVL Tree after deletions: ");
    inorder(root);
    printf("\n");

    return 0;
}