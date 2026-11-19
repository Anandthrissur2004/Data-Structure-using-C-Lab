#include <stdio.h>

#define MAX 100  // Maximum number of elements

// Declaration
int arr[MAX];
int sumTree[4 * MAX];
int minTree[4 * MAX];
int n;

// Build Segment Tree Function
void build(int node, int start, int end)
{
    // Base condition: Leaf node
    if (start == end)
    {
        sumTree[node] = arr[start];
        minTree[node] = arr[start];
    }
    else
    {
        int mid = (start + end) / 2;

        // Recursively build left and right subtrees
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);

        // Calculate range sum
        sumTree[node] =
            sumTree[2 * node] + sumTree[2 * node + 1];

        // Find minimum value
        minTree[node] =
            (minTree[2 * node] < minTree[2 * node + 1])
            ? minTree[2 * node]
            : minTree[2 * node + 1];
    }
}

// Range Sum Query Function
int rangeSum(int node, int start, int end, int l, int r)
{
    // No overlap
    if (r < start || end < l)
        return 0;

    // Complete overlap
    if (l <= start && end <= r)
        return sumTree[node];

    // Partial overlap
    int mid = (start + end) / 2;

    return rangeSum(2 * node, start, mid, l, r)
         + rangeSum(2 * node + 1, mid + 1, end, l, r);
}

// Range Minimum Query Function
int rangeMin(int node, int start, int end, int l, int r)
{
    // No overlap
    if (r < start || end < l)
        return 999999;

    // Complete overlap
    if (l <= start && end <= r)
        return minTree[node];

    // Partial overlap
    int mid = (start + end) / 2;

    int left = rangeMin(2 * node, start, mid, l, r);
    int right = rangeMin(2 * node + 1, mid + 1, end, l, r);

    // Return minimum value
    return (left < right) ? left : right;
}

// Update Function
void update(int node, int start, int end, int index, int value)
{
    // Find the leaf node
    if (start == end)
    {
        arr[index] = value;
        sumTree[node] = value;
        minTree[node] = value;
    }
    else
    {
        int mid = (start + end) / 2;

        // Search left or right subtree
        if (index <= mid)
            update(2 * node, start, mid, index, value);
        else
            update(2 * node + 1, mid + 1, end, index, value);

        // Update sum and minimum values
        sumTree[node] =
            sumTree[2 * node] + sumTree[2 * node + 1];

        minTree[node] =
            (minTree[2 * node] < minTree[2 * node + 1])
            ? minTree[2 * node]
            : minTree[2 * node + 1];
    }
}

// Main Function
int main()
{
    int l, r, index, value;

    // Read number of elements
    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Read array elements
    printf("Enter array elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Build Segment Tree
    build(1, 0, n - 1);

    // Read query range
    printf("\nEnter range (l r): ");
    scanf("%d %d", &l, &r);

    if (l < 0 || r >= n || l > r)
    {
        printf("Invalid range\n");
        return 0;
    }

    // Display range sum
    printf("Range Sum = %d\n",
           rangeSum(1, 0, n - 1, l, r));

    // Display range minimum
    printf("Range Minimum = %d\n",
           rangeMin(1, 0, n - 1, l, r));

    // Read update index and value
    printf("\nEnter index and new value: ");
    scanf("%d %d", &index, &value);

    if (index < 0 || index >= n)
    {
        printf("Invalid index\n");
        return 0;
    }

    // Update array element
    update(1, 0, n - 1, index, value);

    printf("After Update:\n");

    // Display updated range sum
    printf("Range Sum = %d\n",
           rangeSum(1, 0, n - 1, l, r));

    // Display updated range minimum
    printf("Range Minimum = %d\n",
           rangeMin(1, 0, n - 1, l, r));

    return 0;
}
