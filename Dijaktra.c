#include <stdio.h>
#include <limits.h> // Used for INT_MAX for integer data type

#define MAX 100 // Maximum number of vertices

//Declaration
int graph[MAX][MAX];
int dist[MAX];
int visited[MAX];

// Min-Heap
int heap[MAX];
int heapSize = 0;

// Swap two elements Function
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Insert element into Min-Heap Function
void insert(int vertex)
{
    int i = ++heapSize;
    heap[i] = vertex;

    while (i > 1 && dist[heap[i]] < dist[heap[i / 2]]) //while looping 
    {
        swap(&heap[i], &heap[i / 2]); //Call to function swap two elements
        i = i / 2;
    }
}

// Delete minimum element Function
int deleteMin()
{
    int min = heap[1];
    heap[1] = heap[heapSize--];

    int i = 1;

    while (1)
    {
        int smallest = i;
        int left = 2 * i;
        int right = 2 * i + 1;

        if (left <= heapSize &&
            dist[heap[left]] < dist[heap[smallest]])
            smallest = left;

        if (right <= heapSize &&
            dist[heap[right]] < dist[heap[smallest]])
            smallest = right;

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return min;
}

// Dijkstra's Algorithm
void dijkstra(int n, int source)
{
    for (int i = 0; i < n; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    heapSize = 0;
    dist[source] = 0;

    insert(source); //Call to Function

    while (heapSize > 0)
    {
        int u = deleteMin(); //Call to function

        if (visited[u])
		{
            continue;
		}

        visited[u] = 1;

        for (int v = 0; v < n; v++)
        {
            if (graph[u][v] > 0 && !visited[v])
            {
                if (dist[u] != INT_MAX &&
                    dist[u] + graph[u][v] < dist[v])
                {
                    dist[v] = dist[u] + graph[u][v];
                    insert(v);
                }
            }
        }
    }

    printf("\nShortest distances from source %d:\n", source);

    for (int i = 0; i < n; i++)
    {
        if (dist[i] == INT_MAX)
		{
            printf("%d -> %d = INF\n", source, i);
		}
        else
		{
            printf("%d -> %d = %d\n", source, i, dist[i]);
		}
    }
}

// Main Function
int main()
{
	//Declaration
    int n, source;

	//Input any number of vertices
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
	//looping to input adjacency matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }
	//Input any source vertex
    printf("Enter source vertex: ");
    scanf("%d", &source);
	//Call to function
    dijkstra(n, source);

    return 0;
}
