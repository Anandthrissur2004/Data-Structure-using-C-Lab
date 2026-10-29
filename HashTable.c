#include<stdio.h>
#include<stdlib.h>

#define SIZE 10 // Defines the hash table size as 10

/* =========================
   SEPARATE CHAINING
   ========================= */

typedef struct Node{
	int key;
	int value;
	struct Node *next;
}Node;

Node *chainTable[SIZE] = {NULL}; // Initialize all entries to NULL

/* =========================
   OPEN ADDRESSING
   ========================= */

typedef struct {
    int key;
    int value;
    int status;   // 0 = Empty, 1 = Occupied, 2 = Deleted
} Entry;

Entry openTable[SIZE]; // Create an array of 10 hash table entries

/* =========================
   HASH FUNCTION
   ========================= */

int hashFunction(int key)
{
    return key % SIZE;
}

/* =========================
   INITIALIZE OPEN TABLE
   ========================= */

void initializeOpenTable()
{
    int i;

    for (i = 0; i < SIZE; i++)
        openTable[i].status = 0;
}

/* =========================
   INSERT USING CHAINING
   ========================= */

void insertChaining(int key, int value)
{
    int index = hashFunction(key);

    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->key = key;  // Store the key in the new node
    newNode->value = value; // Store the value in the new node

    newNode->next = chainTable[index];
    chainTable[index] = newNode;

    printf("Key inserted using Separate Chaining at index %d.\n",
           index);
}

/* =========================
   SEARCH USING CHAINING
   ========================= */

int searchChaining(int key)
{
    int index = hashFunction(key);

    Node *temp = chainTable[index];

    while (temp != NULL)
    {
        if (temp->key == key)
        {
            printf("Key found!\n");
            printf("Key   : %d\n", temp->key);
            printf("Value : %d\n", temp->value);

            return 1;
        }

        temp = temp->next;
    }

    return 0;
}

/* =========================
   DELETE USING CHAINING
   ========================= */

int deleteChaining(int key)
{
    int index = hashFunction(key);

    Node *temp = chainTable[index];
    Node *prev = NULL;

    while (temp != NULL)
    {
        if (temp->key == key)
        {
            if (prev == NULL)
                chainTable[index] = temp->next;
            else
                prev->next = temp->next;

            free(temp);

            printf("Key deleted successfully.\n");

            return 1;
        }

        prev = temp;
        temp = temp->next;
    }

    return 0;
}

/* =========================
   INSERT USING OPEN ADDRESSING
   LINEAR PROBING
   ========================= */

int insertOpenAddressing(int key, int value, int startIndex)
{
    int index;
    int i;

    for (i = 0; i < SIZE; i++)
    {
        index = (startIndex + i) % SIZE;

        if (openTable[index].status != 1)
        {
            openTable[index].key = key;
            openTable[index].value = value;
            openTable[index].status = 1;

            printf("Key inserted using Open Addressing at index %d.\n",
                   index);

            return 1;
        }
    }

    printf("Hash table is full!\n");

    return 0;
}

/* =========================
   SEARCH USING OPEN ADDRESSING
   ========================= */

int searchOpenAddressing(int key)
{
    int startIndex = hashFunction(key);
    int index;
    int i;

    for (i = 0; i < SIZE; i++)
    {
        index = (startIndex + i) % SIZE;

        if (openTable[index].status == 0)
            return 0;

        if (openTable[index].status == 1 &&
            openTable[index].key == key)
        {
            printf("Key found!\n");
            printf("Key   : %d\n", openTable[index].key);
            printf("Value : %d\n", openTable[index].value);

            return 1;
        }
    }

    return 0;
}

/* =========================
   DELETE USING OPEN ADDRESSING
   ========================= */

int deleteOpenAddressing(int key)
{
    int startIndex = hashFunction(key);
    int index;
    int i;

    for (i = 0; i < SIZE; i++)
    {
        index = (startIndex + i) % SIZE;

        if (openTable[index].status == 0)
            return 0;

        if (openTable[index].status == 1 &&
            openTable[index].key == key)
        {
            openTable[index].status = 2;

            printf("Key deleted successfully.\n");

            return 1;
        }
    }

    return 0;
}

/* =========================
   INSERT OPERATION
   ========================= */

void insert()
{
    int key, value;
    int index;
    int choice;

    printf("\nEnter key: ");
    scanf("%d", &key);

    printf("Enter value: ");
    scanf("%d", &value);

    index = hashFunction(key);

    printf("Hash index = %d\n", index);

    /*
       First check if the position is completely empty.
       If so, insert directly.
    */

    if (openTable[index].status == 0 && chainTable[index] == NULL)
    {
        openTable[index].key = key;
        openTable[index].value = value;
        openTable[index].status = 1;

        printf("Key inserted at index %d.\n", index);

        return;
    }

    /*
       If position is occupied, collision occurs.
    */
    printf("\nCollision occurred at index %d!\n", index);

    printf("\nChoose collision resolution technique:\n");
    printf("1. Separate Chaining\n");
    printf("2. Open Addressing\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        insertChaining(key, value);
    }
    else if (choice == 2)
    {
        insertOpenAddressing(key, value, index);
    }
    else
    {
        printf("Invalid choice!\n");
    }
}

/* =========================
   SEARCH OPERATION
   ========================= */

void search()
{
    int key;

    printf("\nEnter key to search: ");
    scanf("%d", &key);

    /*
       Search in both structures.
       This allows the user to search without
       knowing which collision technique was used.
    */

    if (searchOpenAddressing(key))
        return;

    if (searchChaining(key))
        return;

    printf("Key not found.\n");
}

/* =========================
   DELETE OPERATION
   ========================= */

void deleteKey()
{
    int key;

    printf("\nEnter key to delete: ");
    scanf("%d", &key);

    /*
       Try Open Addressing first.
    */

    if (deleteOpenAddressing(key))
        return;

    /*
       If not found, try Separate Chaining.
    */

    if (deleteChaining(key))
        return;

    printf("Key not found.\n");
}

/* =========================
   MAIN FUNCTION
   ========================= */

int main()
{
    int choice;

    initializeOpenTable();

    while (1)
    {
        printf("\n=========================\n");
        printf("       HASH TABLE\n");
        printf("=========================\n");

        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Exit\n");

        printf("=========================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                insert();
                break;

            case 2:
                search();
                break;

            case 3:
                deleteKey();
                break;

            case 4:
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
