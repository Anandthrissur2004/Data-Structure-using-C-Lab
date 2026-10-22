
#include <stdio.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX];
int parent[MAX];
int distance[MAX];
int queue[MAX];

int front = 0, rear = -1;

void BFS(int n, int source)
{
    int i, u, v;

    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
        distance[i] = -1;
    }

    front = 0;
    rear = -1;

    visited[source] = 1;
    distance[source] = 0;
    queue[++rear] = source;

    printf("\nBFS Traversal: ");

    while (front <= rear)
    {
        u = queue[front++];
        printf("%d ", u);

        for (v = 0; v < n; v++)
        {
            if (graph[u][v] == 1 && !visited[v])
            {
                visited[v] = 1;
                parent[v] = u;
                distance[v] = distance[u] + 1;
                queue[++rear] = v;
            }
        }
    }

    printf("\n");

    printf("\nShortest Paths from %d:\n", source);

    for (i = 0; i < n; i++)
    {
        if (distance[i] == -1)
        {
            printf("Vertex %d: Not reachable\n", i);
        }
        else
        {
            int path[MAX], count = 0;
            int current = i;

            while (current != -1)
            {
                path[count++] = current;
                current = parent[current];
            }

            printf("Vertex %d: ", i);

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

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    if (edges < 0 || edges > n * (n - 1) / 2)
    {
        printf("Invalid number of edges for an undirected graph.\n");
        return 1;
    }

    printf("Enter edges (u v):\n");

    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            printf("Invalid vertex.\n");
            return 1;
        }

        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    printf("Enter source vertex: ");
    scanf("%d", &source);

    if (source < 0 || source >= n)
    {
        printf("Invalid source vertex.\n");
        return 1;
    }

    BFS(n, source);

    return 0;
}
