#include <stdio.h>

#define MAX 100 //Maximum value assigned to MAX

// Structure to store an edge
struct Edge
{
    int u, v, weight;
};

struct Edge edges[MAX]; //This statement creates an array of structures to store graph edges.

//Declaration
int parent[MAX];
int rank[MAX];

// Find the parent of a vertex
int find(int x)
{
    if (parent[x] != x)
	{
        parent[x] = find(parent[x]);
	}

    return parent[x];
}

// Union of two sets Function
void unionSet(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) //Compare equal rootX and rootY
	{
        return;
	}

    if (rank[rootX] < rank[rootY])
	{
        parent[rootX] = rootY;
	}
    else if (rank[rootX] > rank[rootY])
	{
        parent[rootY] = rootX;
	}
    else
    {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

//Main Function
int main()
{
	//Declaration
    int n, e;
    int totalCost = 0;
    int mstEdges = 0;

	//Input number of verices 'n'
    printf("Enter number of vertices: ");
    scanf("%d", &n);

	//Input number of edges
    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Input edges (u, v and weight)
    printf("Enter edges (u v weight):\n");
    for (int i = 0; i < e; i++) //looping to edges
    {
        scanf("%d %d %d",
              &edges[i].u,
              &edges[i].v,
              &edges[i].weight);
    }

    // Initialize Disjoint Set
    for (int i = 0; i < n; i++) //looping to vertices
    {
        parent[i] = i;
        rank[i] = 0;
    }

    // Sort edges in ascending order of weight
    for (int i = 0; i < e - 1; i++)
    {
        for (int j = 0; j < e - i - 1; j++)
        {
            if (edges[j].weight > edges[j + 1].weight)
            {
                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Kruskal's Algorithm
    printf("\nEdges in Minimum Spanning Tree:\n");

    for (int i = 0; i < e && mstEdges < n - 1; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;

        int rootU = find(u);
        int rootV = find(v);

        // Check whether adding edge creates a cycle
        if (rootU != rootV)
        {
            printf("%d - %d : %d\n",
                   u, v, edges[i].weight);

            unionSet(rootU, rootV); //Call to Function

            totalCost += edges[i].weight; //Total cost
            mstEdges++;
        }
    }

    if (mstEdges == n - 1)
    {
        printf("\nMinimum Cost = %d\n", totalCost);
    }
    else
    {
        printf("\nMinimum Spanning Tree does not exist.\n");
    }

    return 0;
}