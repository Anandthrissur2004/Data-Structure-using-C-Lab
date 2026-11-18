#include <stdio.h>

#define MAX 100 //Maximum value assigned to MAX

//Declaration
int graph[MAX][MAX];
int visited[MAX];
int n;

// DFS Traversal Function
void DFS(int vertex)
{
    visited[vertex] = 1; 
    printf("%d ", vertex);

    for (int i = 0; i < n; i++) 
    {
        if (graph[vertex][i] == 1 && !visited[i])
        {
            DFS(i);  //Calls DFS again for the unvisited adjacent vertex
        }
    }
}

// Cycle Detection (Undirected Graph) Function
int isCycle(int vertex, int parent)
{
    visited[vertex] = 1;

    for (int i = 0; i < n; i++)
    {
        if (graph[vertex][i] == 1)
        {
            if (!visited[i])
            {
                if (isCycle(i, vertex))
				{
                    return 1;
				}
            }
            else if (i != parent)
            {
                return 1;
            }
        }
    }
    return 0;
}

// Connectivity Checking Function
int isConnected()
{
    for (int i = 0; i < n; i++)
	{
        visited[i] = 0;
	}
    DFS(0); //Starts DFS traversal from vertex 0
	
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
		{
            return 0;
		}
    }

    return 1;
}

int main()
{
	//Declaration
    int edges, u, v, start;

	//Input any number of vertices
    printf("Enter number of vertices: ");
    scanf("%d", &n);

	//Input any number of edges
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    // Initialize graph
    for (int i = 0; i < n; i++)
	{
        for (int j = 0; j < n; j++)
		{
            graph[i][j] = 0; //[0,0,0,..]
		}
	}

	//Input any number u - v edges
    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &u, &v);
		//Adjacency Matrix
        graph[u][v] = 1;
        graph[v][u] = 1;
    }
	
	//Input starting vertex
    printf("Enter starting vertex: ");
    scanf("%d", &start);

    // DFS Traversal
    for (int i = 0; i < n; i++)
	{
        visited[i] = 0;
	}

    printf("\nDFS Traversal: ");
    DFS(start); //Call to function

    // Cycle Detection
    for (int i = 0; i < n; i++)
	{
        visited[i] = 0;
	}

    int cycle = 0;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            if (isCycle(i, -1)) //Calls the isCycle() function.
            {
                cycle = 1;
                break;
            }
        }
    }

    if (cycle)
	{
        printf("\nCycle detected.");
	}
    else
	{
        printf("\nNo cycle detected.");
	}

    // Connectivity Checking
    for (int i = 0; i < n; i++)
	{
        visited[i] = 0;
	}

    int connected = 1;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            if (i != 0)
            {
                connected = 0;
                break;
            }
            DFS(i);
        }
    }

    if (connected)
	{
        printf("\nGraph is connected.");
	}
    else
	{
        printf("\nGraph is not connected.");
	}

    return 0;
}
