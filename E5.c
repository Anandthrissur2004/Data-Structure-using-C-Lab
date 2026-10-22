
#include <stdio.h>
#include <stdlib.h>

#define M 4  /* Order of the B-Tree */

typedef struct BTreeNode {
    int keys[M - 1];
    struct BTreeNode *child[M];
    int n;       /* Number of keys */
    int leaf;    /* 1 if leaf, 0 otherwise */
} BTreeNode;

BTreeNode *root = NULL;

/* Create a new node */
BTreeNode *createNode(int leaf) {
    BTreeNode *node = calloc(1, sizeof(BTreeNode));

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    node->leaf = leaf;
    return node;
}

/* Split a full child */
void splitChild(BTreeNode *parent, int i) {
    BTreeNode *y = parent->child[i];
    BTreeNode *z = createNode(y->leaf);

    int mid = (M - 1) / 2;
    int j;

    z->n = M - 2 - mid;

    /* Copy keys to the new node */
    for (j = 0; j < z->n; j++)
        z->keys[j] = y->keys[mid + 1 + j];

    /* Copy child pointers */
    if (!y->leaf) {
        for (j = 0; j <= z->n; j++)
            z->child[j] = y->child[mid + 1 + j];
    }

    y->n = mid;

    /* Shift parent keys and child pointers */
    for (j = parent->n; j > i; j--) {
        parent->child[j + 1] = parent->child[j];
        parent->keys[j] = parent->keys[j - 1];
    }

    parent->child[i + 1] = z;
    parent->keys[i] = y->keys[mid];
    parent->n++;
}

/* Insert into a non-full node */
void insertNonFull(BTreeNode *node, int key) {
    int i = node->n - 1;

    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->n++;
    } else {
        while (i >= 0 && key < node->keys[i])
            i--;

        i++;

        if (node->child[i]->n == M - 1) {
            splitChild(node, i);

            if (key > node->keys[i])
                i++;
        }

        insertNonFull(node->child[i], key);
    }
}

/* Insert a key into the B-Tree */
void insert(int key) {
    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = key;
        root->n = 1;
        return;
    }

    if (root->n == M - 1) {
        BTreeNode *newRoot = createNode(0);

        newRoot->child[0] = root;
        root = newRoot;

        splitChild(newRoot, 0);
    }

    insertNonFull(root, key);
}

/* Display the B-Tree in sorted order */
void traverse(BTreeNode *node) {
    int i;

    if (node == NULL)
        return;

    for (i = 0; i < node->n; i++) {
        if (!node->leaf)
            traverse(node->child[i]);

        printf("%d ", node->keys[i]);
    }

    if (!node->leaf)
        traverse(node->child[i]);
}

/* Main function */
int main(void) {
    int choice, key;

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
