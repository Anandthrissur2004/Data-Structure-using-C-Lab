#include <stdio.h>

#define MAX 100

int parent[MAX];
int rank[MAX];

// Initialize each element as a separate set
void initialize(int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Find with path compression
int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

// Union by rank
void unionSet(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY)
    {
        printf("Already in the same set.\n");
        return;
    }

    if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY])
        parent[rootY] = rootX;
    else
    {
        parent[rootY] = rootX;
        rank[rootX]++;
    }

    printf("Union successful.\n");
}

// Input a set using { }
void inputSet(int set[], int *count, int n)
{
    char ch;
    int x;

    *count = 0;

    printf("Enter set (example: {0, 1, 2}): ");

    scanf(" %c", &ch);

    if (ch != '{')
    {
        printf("Invalid input. Use { }.\n");
        return;
    }

    while (1)
    {
        if (scanf(" %d", &x) != 1)
        {
            printf("Invalid input.\n");
            return;
        }

        if (x < 0 || x >= n)
        {
            printf("Element %d is out of range.\n", x);
            return;
        }

        if (*count >= n)
        {
            printf("Too many elements.\n");
            return;
        }

        set[(*count)++] = x;

        scanf(" %c", &ch);

        if (ch == '}')
            break;

        if (ch != ',')
        {
            printf("Invalid separator. Use commas.\n");
            return;
        }
    }

    printf("Set input successful.\n");
}

// Merge all elements in the entered set
void mergeInputSet(int set[], int count)
{
    for (int i = 1; i < count; i++)
        unionSet(set[0], set[i]);
}

// Display all disjoint sets using { }
void display(int n)
{
    int printed[MAX] = {0};

    printf("\nDisjoint Sets:\n");

    for (int i = 0; i < n; i++)
    {
        int root = find(i);

        if (!printed[root])
        {
            printf("{");

            int first = 1;

            for (int j = 0; j < n; j++)
            {
                if (find(j) == root)
                {
                    if (!first)
                        printf(", ");

                    printf("%d", j);
                    first = 0;
                }
            }

            printf("}\n");
            printed[root] = 1;
        }
    }
}

// Check connectivity
void connected(int x, int y)
{
    if (find(x) == find(y))
        printf("%d and %d are connected.\n", x, y);
    else
        printf("%d and %d are not connected.\n", x, y);
}

int main()
{
    int n, choice, x, y;
    int set[MAX], count;

    printf("Enter number of elements (1-100): ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of elements.\n");
        return 1;
    }

    initialize(n);

    do
    {
        printf("\n--- DISJOINT SET UNION ---\n");
        printf("1. Input Set { }\n");
        printf("2. Union Two Elements\n");
        printf("3. Check Connectivity\n");
        printf("4. Display Sets\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                inputSet(set, &count, n);
                if (count > 0)
                    mergeInputSet(set, count);
                break;

            case 2:
                printf("Enter two elements: ");
                scanf("%d %d", &x, &y);

                if (x < 0 || x >= n || y < 0 || y >= n)
                    printf("Invalid elements.\n");
                else
                    unionSet(x, y);
                break;

            case 3:
                printf("Enter two elements: ");
                scanf("%d %d", &x, &y);

                if (x < 0 || x >= n || y < 0 || y >= n)
                    printf("Invalid elements.\n");
                else
                    connected(x, y);
                break;

            case 4:
                display(n);
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 5);

    return 0;
}
