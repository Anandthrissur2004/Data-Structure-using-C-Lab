
#include <stdio.h>
#include <limits.h>  // Used for INT_MAX

#define MAX 100      // Maximum number of vertices

// Global declarations
int graph[MAX][MAX];             
int key[MAX];                    
int parent[MAX];                 
int visited[MAX];                

int heap[MAX];                   
int position[MAX];              
int heapSize = 0;               

// Swap function
void swap(int *a, int *b)
{
    int temp = *a;               // Store first value
    *a = *b;                     // Assign second value to first
    *b = temp;                   // Assign temporary value to second
}

// Heapify function
void heapify(int i)
{
    int smallest = i;            // Assume current node is smallest
    int left = 2 * i + 1;        // Find left child
    int right = 2 * i + 2;       // Find right child

    // Check whether left child is smaller
    if (left < heapSize &&
        key[heap[left]] < key[heap[smallest]])
        smallest = left;

    // Check whether right child is smaller
    if (right < heapSize &&
        key[heap[right]] < key[heap[smallest]])
        smallest = right;

    // If smallest is not the current node
    if (smallest != i)
    {
        int a = heap[i];
        int b = heap[smallest];

        swap(&heap[i], &heap[smallest]); // Swap elements

        position[a] = smallest;          // Update position
        position[b] = i;                 // Update position

        heapify(smallest);               //Call to function for Recursively heapify
    }
}

// Insert function
void insert(int vertex)
{
    int i = heapSize;              // Find next available position

    heap[heapSize] = vertex;       // Insert vertex into heap
    position[vertex] = heapSize;   // Store its position
    heapSize++;                    // Increase heap size

    // Move the vertex upward to maintain Min Heap
    while (i > 0 &&
           key[heap[i]] < key[heap[(i - 1) / 2]])
    {
        int a = heap[i];
        int b = heap[(i - 1) / 2];

        swap(&heap[i], &heap[(i - 1) / 2]);

        position[a] = (i - 1) / 2; // Update position
        position[b] = i;           // Update position

        i = (i - 1) / 2;           // Move to parent
    }
}

// Extract minimum function
int extractMin()
{
    int min = heap[0];             // Get smallest vertex

    position[min] = -1;            // Mark as removed

    heapSize--;                     // Decrease heap size

    // Replace root with last element
    if (heapSize > 0)
    {
        heap[0] = heap[heapSize];
        position[heap[0]] = 0;

        heapify(0);                 // Restore Min Heap property
    }

    return min;                     // Return minimum vertex
}

// Decrease key function
void decreaseKey(int vertex, int newKey)
{
    int i = position[vertex];       // Get vertex position

    key[vertex] = newKey;           // Update key value

    // Move vertex upward if necessary
    while (i > 0 &&
           key[heap[i]] < key[heap[(i - 1) / 2]])
    {
        int a = heap[i];
        int b = heap[(i - 1) / 2];

        swap(&heap[i], &heap[(i - 1) / 2]);

        position[a] = (i - 1) / 2; // Update position
        position[b] = i;           // Update position

        i = (i - 1) / 2;           // Move to parent
    }
}

// Main function
int main()
{
    int n, totalCost = 0;           // Number of vertices and MST cost
    int count = 0;                  // Counts visited vertices

    // Input number of vertices
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Input adjacency matrix
    printf("Enter adjacency matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("G[%d][%d]:", i, j);
            scanf("%d", &graph[i][j]);
        }
    }

    // Initialize arrays
    for (int i = 0; i < n; i++)
    {
        key[i] = INT_MAX;           // Initialize key to infinity
        parent[i] = -1;             // No parent initially
        visited[i] = 0;             // Mark all vertices unvisited
        position[i] = -1;           // Not present in heap
    }

    // Select vertex 0 as starting vertex
    key[0] = 0;
    insert(0);                      // Insert vertex 0 into Min Heap

    // Prim's Algorithm
    while (heapSize > 0)
    {
        int u = extractMin();       // Extract minimum vertex

        if (visited[u])             // Check whether already visited
            continue;

        visited[u] = 1;             // Mark vertex as visited
        count++;                    // Increase visited count

        // Check all adjacent vertices
        for (int v = 0; v < n; v++)
        {
            // Check edge, visited status and minimum weight
            if (graph[u][v] > 0 &&
                !visited[v] &&
                graph[u][v] < key[v])
            {
                parent[v] = u;      // Update parent vertex

                // If vertex is not in heap
                if (position[v] == -1)
                {
                    key[v] = graph[u][v]; // Update key
                    insert(v);            // Insert into Min Heap
                }
                else
                {
                    // Update existing vertex priority
                    decreaseKey(v, graph[u][v]);
                }
            }
        }
    }

    // Display Minimum Spanning Tree
    if (count != n)
    {
        printf("\nMinimum Spanning Tree does not exist.\n");
    }
    else
    {
        printf("\nEdges in Minimum Spanning Tree:\n");

        // Print MST edges and calculate total cost
        for (int i = 1; i < n; i++)
        {
            printf("%d - %d : %d\n",parent[i], i, key[i]);

            totalCost += key[i];    // Add edge weight
        }

        printf("\nMinimum Cost = %d\n", totalCost);
    }

    return 0;              
}
