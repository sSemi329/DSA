#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define NMAX 1001

/*
 * WHY AN ADJACENCY MATRIX HERE?
 *
 * We use this variant because it is simpler to write:
 *
 * - No vector<vector<int>>, no push_back, no passing the graph as a parameter
 * - "Is there an edge between x and y?" is a single check: a[x][y].
 * - Global arrays are zero-initialized, so there is nothing to set up.
 *
 * The price is efficiency: the matrix needs NMAX * NMAX cells of memory
 * and BFS costs O(n^2), because finding the neighbors of a node means
 * scanning a whole row. That is perfectly fine for small graphs
 * (n <= 1000), but for big or sparse graphs adjacency lists are better.
 */

// n, m = number of nodes and edges
// a    = adjacency matrix: a[x][y] == 1 means there is an edge between x and y
// viz  = viz[i] == 1 means node i was already discovered by the BFS
// All of them are global, so they start filled with 0.
int n, m, a[NMAX][NMAX], viz[NMAX];

void bfs(int node)
{
	// Queue of nodes whose neighbors we still have to explore.
	queue<int> q;

	// Start: mark the starting node as visited, put it in the queue, print it.
	viz[node] = 1;
	q.push(node);
	cout << node << " ";

	// Repeat until there are no more nodes to explore.
	while (!q.empty())
	{
		// Take the oldest node from the queue and remove it.
		int front = q.front();
		q.pop();

		// With a matrix, the neighbors of "front" are not stored in a list,
		// so we check every possible node i from 1 to n.
		for (int i = 1; i <= n; i++)
			// i is a neighbor if there is an edge front-i
			// and it has not been discovered yet.
			if (!viz[i] && a[front][i])
			{
				viz[i] = 1;        // mark it as discovered
				cout << i << " ";  // print it (this is its BFS visiting order)
				q.push(i);         // explore its neighbors later
			}
	}
}

int main()
{
	cin >> n >> m;

	// Read the edges. The graph is undirected, so an edge x-y is stored
	// in both directions: x is a neighbor of y, and y is a neighbor of x.
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >> y;
		a[x][y] = 1;
		a[y][x] = 1;
	}

	// Run BFS starting from node 1.
	// Only the nodes reachable from node 1 will be printed.
	bfs(1);
}