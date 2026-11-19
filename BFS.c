// Breadth-first search traversal with shortest paths in an undirected graph
#include <stdio.h>

#define MAX 100  // Maximum number of vertices

int graph[MAX][MAX];  // Adjacency matrix
int visited[MAX];     // Marks visited vertices
int parent[MAX];      // Stores parent of each vertex
int distance[MAX];    // Stores distance from source
int queue[MAX];       // Queue for BFS

int front = 0, rear = -1;

// Perform BFS and find shortest paths
void BFS(int n, int source)
{
    int i, u, v;

    // Initialize all vertices
    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
        distance[i] = -1;
    }

    // Reset the queue
    front = 0;
    rear = -1;

    // Add the source vertex to the queue
    visited[source] = 1;
    distance[source] = 0;
    queue[++rear] = source;

    printf("\nBFS Traversal: ");

    // Continue until the queue is empty
    while (front <= rear)
    {
        u = queue[front++];  // Remove the front vertex
        printf("%d ", u);

        // Check all adjacent vertices
        for (v = 0; v < n; v++)
        {
            if (graph[u][v] == 1 && !visited[v])
            {
                visited[v] = 1;  // Mark as visited
                parent[v] = u;   // Store parent
                distance[v] = distance[u] + 1;

                queue[++rear] = v;  // Add to queue
            }
        }
    }

    printf("\n");

    // Display shortest paths from the source
    printf("\nShortest Paths from %d:\n", source);

    for (i = 0; i < n; i++)
    {
        // Check whether the vertex is reachable
        if (distance[i] == -1)
        {
            printf("Vertex %d: Not reachable\n", i);
        }
        else
        {
            int path[MAX], count = 0;
            int current = i;

            // Trace the path using parent values
            while (current != -1)
            {
                path[count++] = current;
                current = parent[current];
            }

            printf("Vertex %d: ", i);

            // Print the path in the correct order
            for (int j = count - 1; j >= 0; j--)
            {
                printf("%d", path[j]);

                if (j > 0)
                    printf(" -> ");
            }

            printf(" (Distance = %d)\n", distance[i]);
        }
    }
}

int main()
{
    int n, edges, u, v, source;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Validate the number of vertices
    if (n < 1 || n > MAX)
    {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    // Initialize the adjacency matrix to zero
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    // Validate the number of edges for an undirected simple graph
    if (edges < 0 || edges > n * (n - 1) / 2)
    {
        printf("Invalid number of edges for an undirected graph.\n");
        return 1;
    }

    printf("Enter edges (u v):\n");

    // Read the edges
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &u, &v);

        // Check whether the vertices are valid
        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            printf("Invalid vertex.\n");
            return 1;
        }

        // Add the edge in both directions
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    printf("Enter source vertex: ");
    scanf("%d", &source);

    // Validate the source vertex
    if (source < 0 || source >= n)
    {
        printf("Invalid source vertex.\n");
        return 1;
    }

    BFS(n, source);  // Call the BFS function

    return 0;
}