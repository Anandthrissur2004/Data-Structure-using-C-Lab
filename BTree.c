#include <stdio.h>
#include <stdlib.h>

#define M 4  // Order of the B-Tree

// Structure of a B-Tree node
typedef struct BTreeNode {
    int keys[M - 1];       // Store keys in the node
    struct BTreeNode *child[M]; // Store child pointers
    int n;                 // Number of keys
    int leaf;              // 1 = leaf, 0 = internal node
} BTreeNode;

BTreeNode *root = NULL;  // Initially, the tree is empty

// Create a new node
BTreeNode *createNode(int leaf) {
    BTreeNode *node = calloc(1, sizeof(BTreeNode));

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    node->leaf = leaf;
    return node;
}

// Split a full child node
void splitChild(BTreeNode *parent, int i) {
    BTreeNode *y = parent->child[i];
    BTreeNode *z = createNode(y->leaf);

    int mid = (M - 1) / 2;
    int j;

    // Find the number of keys for the new node
    z->n = M - 2 - mid;

    // Copy the larger keys into the new node
    for (j = 0; j < z->n; j++)
        z->keys[j] = y->keys[mid + 1 + j];

    // Copy child pointers if it is not a leaf
    if (!y->leaf) {
        for (j = 0; j <= z->n; j++)
            z->child[j] = y->child[mid + 1 + j];
    }

    // Keep the smaller keys in the original node
    y->n = mid;

    // Make space in the parent for the new child and key
    for (j = parent->n; j > i; j--) {
        parent->child[j + 1] = parent->child[j];
        parent->keys[j] = parent->keys[j - 1];
    }

    // Add the new child and middle key to the parent
    parent->child[i + 1] = z;
    parent->keys[i] = y->keys[mid];
    parent->n++;
}

// Insert a key into a node that is not full
void insertNonFull(BTreeNode *node, int key) {
    int i = node->n - 1;

    // Insert the key into a leaf node
    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->n++;
    } else {
        // Find the correct child for the key
        while (i >= 0 && key < node->keys[i])
            i--;

        i++;

        // Split the child if it is full
        if (node->child[i]->n == M - 1) {
            splitChild(node, i);

            if (key > node->keys[i])
                i++;
        }

        // Insert the key into the correct child
        insertNonFull(node->child[i], key);
    }
}

// Insert a key into the B-Tree
void insert(int key) {
    // Create the root if the tree is empty
    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = key;
        root->n = 1;
        return;
    }

    // Split the root if it is full
    if (root->n == M - 1) {
        BTreeNode *newRoot = createNode(0);

        newRoot->child[0] = root;
        root = newRoot;

        splitChild(newRoot, 0);
    }

    // Insert the key into a non-full node
    insertNonFull(root, key);
}

// Display all keys in sorted order
void traverse(BTreeNode *node) {
    int i;

    if (node == NULL)
        return;

    // Visit children and keys in order
    for (i = 0; i < node->n; i++) {
        if (!node->leaf)
            traverse(node->child[i]);

        printf("%d ", node->keys[i]);
    }

    // Visit the last child
    if (!node->leaf)
        traverse(node->child[i]);
}

// Main function
int main(void) {
    int choice, key;

    // Display the menu repeatedly
    while (1) {
        printf("\n====================\n");
        printf("     B-TREE\n");
        printf("====================\n");
        printf("1. Insert\n");
        printf("2. Traversal\n");
        printf("3. Exit\n");
        printf("====================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                printf("Enter key: ");

                if (scanf("%d", &key) != 1) {
                    printf("Invalid input.\n");
                    return 1;
                }

                insert(key);
                printf("Key inserted successfully.\n");
                break;

            case 2:
                printf("B-Tree traversal: ");
                traverse(root);
                printf("\n");
                break;

            case 3:
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}