// AVL tree implementation with insertion, deletion, and balancing operations
#include <stdio.h>
#include <stdlib.h>

// Structure of an AVL tree node
typedef struct Node {
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

// Return the height of a node
int height(Node *node) {
    return (node == NULL) ? 0 : node->height;
}

// Return the larger value
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new node
Node *createNode(int key) {
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newNode->key = key;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Calculate the balance factor
int getBalance(Node *node) {
    if (node == NULL)
        return 0;

    return height(node->left) - height(node->right);
}

// Perform right rotation (LL case)
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *temp = x->right;

    x->right = y;
    y->left = temp;

    // Update the heights
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

// Perform left rotation (RR case)
Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *temp = y->left;

    y->left = x;
    x->right = temp;

    // Update the heights
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// Insert a key into the AVL tree
Node *insert(Node *root, int key) {
    if (root == NULL)
        return createNode(key);

    // Insert according to BST rules
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else {
        printf("Duplicate key not allowed.\n");
        return root;
    }

    // Update the height
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL case: right rotation
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // RR case: left rotation
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // LR case: left rotation, then right rotation
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL case: right rotation, then left rotation
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find the node with the smallest key
Node *minValueNode(Node *node) {
    Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

// Delete a key from the AVL tree
Node *deleteNode(Node *root, int key) {
    if (root == NULL)
        return NULL;

    // Find the key
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node has zero or one child
        if (root->left == NULL || root->right == NULL) {
            Node *temp = (root->left != NULL)
                         ? root->left : root->right;

            // Node has no children
            if (temp == NULL) {
                free(root);
                return NULL;
            }

            // Replace node with its child
            Node *oldRoot = root;
            root = temp;
            free(oldRoot);
        } else {
            // Node has two children
            // Find the smallest key in the right subtree
            Node *temp = minValueNode(root->right);

            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return NULL;

    // Update the height
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search for a key
Node *search(Node *root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

// Display nodes in ascending order
void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Display root, left subtree, then right subtree
void preorder(Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

// Main menu
int main(void) {
    Node *root = NULL;
    int choice, key;

    while (1) {
        printf("\n========================\n");
        printf("        AVL TREE\n");
        printf("========================\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Exit\n");
        printf("========================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                if (scanf("%d", &key) != 1)
                    goto input_error;

                if (search(root, key) != NULL) {
                    printf("Duplicate key not allowed.\n");
                } else {
                    root = insert(root, key);
                    printf("Key inserted successfully.\n");
                }
                break;

            case 2:
                printf("Enter key to delete: ");
                if (scanf("%d", &key) != 1)
                    goto input_error;

                if (search(root, key) == NULL) {
                    printf("Key not found.\n");
                } else {
                    root = deleteNode(root, key);
                    printf("Key deleted successfully.\n");
                }
                break;

            case 3:
                printf("Enter key to search: ");
                if (scanf("%d", &key) != 1)
                    goto input_error;

                if (search(root, key) != NULL)
                    printf("Key found.\n");
                else
                    printf("Key not found.\n");
                break;

            case 4:
                printf("Inorder traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Preorder traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    // Exit if the menu input is invalid
    return 0;

input_error:
    printf("Invalid input. Program terminated.\n");
    return 1;
}