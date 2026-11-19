#include <stdio.h>

#define MAX 100  // Maximum number of vertices

// Global declarations
int graph[MAX][MAX];
int visited[MAX];
int stack[MAX];
int indegree[MAX];
int queue[MAX];

int n;
int top = -1;

// DFS Function
void DFS(int vertex)
{
    visited[vertex] = 1;  // Mark vertex as visited

    // Visit all adjacent vertices
    for (int i = 0; i < n; i++)
    {
        if (graph[vertex][i] == 1 && !visited[i])
        {
            DFS(i);  // Recursive DFS call
        }
    }

    // Push vertex after visiting all adjacent vertices
    stack[++top] = vertex;
}

// Topological Sorting using DFS
void topologicalDFS()
{
    // Initialize visited array
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    top = -1;

    // Start DFS from every unvisited vertex
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            DFS(i);
        }
    }

    // Display topological order by popping stack
    printf("\nTopological Order using DFS: ");

    while (top >= 0)
    {
        printf("%d ", stack[top--]);
    }
}

// Topological Sorting using BFS (Kahn's Algorithm)
void topologicalBFS()
{
    int front = 0, rear = -1;
    int count = 0;

    // Calculate indegree of each vertex
    for (int i = 0; i < n; i++)
    {
        indegree[i] = 0;

        for (int j = 0; j < n; j++)
        {
            if (graph[j][i] == 1)
            {
                indegree[i]++;
            }
        }
    }

    // Insert vertices with indegree 0 into queue
    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            queue[++rear] = i;
        }
    }

    printf("\nTopological Order using BFS: ");

    // Process queue until it becomes empty
    while (front <= rear)
    {
        int vertex = queue[front++];

        printf("%d ", vertex);
        count++;

        // Visit all adjacent vertices
        for (int i = 0; i < n; i++)
        {
            if (graph[vertex][i] == 1)
            {
                indegree[i]--;  // Decrease indegree

                // Insert vertex when indegree becomes 0
                if (indegree[i] == 0)
                {
                    queue[++rear] = i;
                }
            }
        }
    }

    // Check whether graph contains a cycle
    if (count != n)
    {
        printf("\nGraph contains a cycle.");
        printf("\nTopological sorting is not possible.");
    }
}

// Main Function
int main()
{
    int edges, u, v;

    // Read number of vertices
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Validate number of vertices
    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of vertices.");
        return 0;
    }

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            graph[i][j] = 0;
        }
    }

    // Read number of edges
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter directed edges (u v):\n");

    // Read directed edges
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &u, &v);

        // Check valid vertex numbers
        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            printf("Invalid edge. Enter again.\n");
            i--;
            continue;
        }

        // Add directed edge u -> v
        graph[u][v] = 1;
    }

    // Call DFS and BFS methods
    topologicalDFS();
    topologicalBFS();

    return 0;
}
