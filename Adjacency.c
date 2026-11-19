#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Maximum number of vertices

// Declaration of Adjacency Matrix
int matrix[MAX][MAX];

// Structure for Adjacency List
struct Node
{
    int vertex;
    struct Node *next;
};

// Array of linked lists
struct Node *list[MAX];

int n;

// Add Edge using Adjacency Matrix
void addMatrixEdge(int u, int v)
{
    matrix[u][v] = 1;
    matrix[v][u] = 1;
}

// Add Edge using Adjacency List
void addListEdge(int u, int v)
{
    struct Node *newNode;

    // Create node for vertex v
    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = list[u];
    list[u] = newNode;

    // Create node for vertex u
    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->vertex = u;
    newNode->next = list[v];
    list[v] = newNode;
}

// Display Adjacency Matrix Function
void displayMatrix()
{
    printf("\nAdjacency Matrix:\n");

    // Traverse rows and columns
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Display Adjacency List Function
void displayList()
{
    printf("\nAdjacency List:\n");

    // Traverse each linked list
    for (int i = 0; i < n; i++)
    {
        struct Node *temp = list[i];

        printf("%d -> ", i);

        while (temp != NULL)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }

        printf("NULL\n");
    }
}

// Main Function
int main()
{
    int edges, u, v;

    // Read number of vertices
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of vertices\n");
        return 0;
    }

    // Initialize adjacency list
    for (int i = 0; i < n; i++)
        list[i] = NULL;

    // Read number of edges
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v):\n");

    // Read and insert edges
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &u, &v);

        // Check valid vertices
        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            printf("Invalid edge\n");
            i--;
            continue;
        }

        // Insert edge in both representations
		//Call to Function
        addMatrixEdge(u, v);
        addListEdge(u, v);
    }

    // Display graph representations
	//Call to Function
    displayMatrix();
    displayList();

    return 0;
}
