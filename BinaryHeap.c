#include <stdio.h>

#define MAX 100 // Maximum number of vertices

//Declaration
int heap[MAX];
int size = 0;
int isMin;

// Swap two elements
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Check heap property
int compare(int a, int b)
{
    if (isMin)
	{
        return a < b;
	}
    else
	{
        return a > b;
	}
}

// Heapify operation
void heapify(int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size &&
        compare(heap[left], heap[smallest]))
    {
        smallest = left;
    }

    if (right < size &&
        compare(heap[right], heap[smallest]))
    {
        smallest = right;
    }

    if (smallest != i)
    {
        swap(&heap[i], &heap[smallest]);
        heapify(smallest);
    }
}

// Build Heap
void buildHeap()
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(i); //Call to function for heapify again
    }

    printf("Heap created successfully!\n");
}

// Insertion
void insert(int value)
{
    if (size == MAX) //Compare equal size and MAX
    {
        printf("Heap is full!\n");
        return;
    }

    int i = size;
    heap[size++] = value;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (compare(heap[i], heap[parent]))
        {
            swap(&heap[i], &heap[parent]); //Call to function
            i = parent;
        }
        else
		{
            break;
		}
    }

    printf("Element inserted successfully!\n");
}

// Deletion Function
void deleteRoot()
{
    if (size == 0)
    {
        printf("Heap is empty!\n");
        return;
    }

    printf("Deleted element: %d\n", heap[0]);

    heap[0] = heap[size - 1];
    size--;

    if (size > 0)
	{
        heapify(0); //Call to function
	}
}

// Display Heap
void display()
{
    if (size == 0)
    {
        printf("Heap is empty!\n");
        return;
    }

    printf("Heap elements: ");

    for (int i = 0; i < size; i++)
    {
        printf("%d ", heap[i]);
    }

    printf("\n");
}

// Main Function
int main()
{
	//Declaration
    int choice, value, n;

    printf("1. Min-Heap\n");
    printf("2. Max-Heap\n");
    printf("Enter heap type: ");
    scanf("%d", &isMin);

    if (isMin == 1)
	{
        isMin = 1;
	}
    else if (isMin == 2)
	{
        isMin = 0;
	}
    else
    {
        printf("Invalid heap type!\n");
        return 0;
    }

    while (1)
    {
        printf("\n--- HEAP OPERATIONS ---\n");
        printf("1. Insert\n");
        printf("2. Delete Root\n");
        printf("3. Heapify (Build Heap)\n");
        printf("4. Display\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insert(value); //Call to function
                break;

            case 2:
                deleteRoot(); //Call to function
                break;

            case 3:
                printf("Enter number of elements: ");
                scanf("%d", &n);

                if (n < 0 || n > MAX)
                {
                    printf("Invalid size!\n");
                    break;
                }

                size = n;

                printf("Enter elements:\n");

                for (int i = 0; i < size; i++)
                {
                    scanf("%d", &heap[i]);
                }

                buildHeap(); //Call to function
                break;

            case 4:
                display(); //Call to function
                break;

            case 5:
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
