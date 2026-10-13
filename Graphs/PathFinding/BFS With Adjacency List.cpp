#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
 * WHY ADJACENCY LISTS INSTEAD OF AN ADJACENCY MATRIX
 *
 * - Memory: a matrix always needs n*n cells, even if the graph has very few
 *   edges. A list only stores the edges that actually exist, so it uses
 *   O(n + m) memory. For n = 100000 a matrix is impossible (10^10 cells),
 *   while a list is tiny if m is small.
 *
 * - Speed of BFS: with a matrix, finding the neighbors of a node means
 *   scanning a whole row of n cells, so BFS costs O(n^2). With lists we
 *   only walk through the real neighbors, so BFS costs O(n + m).
 *
 * - The matrix still wins when you need to check "is there an edge between
 *   x and y?" in O(1), or when the graph is very dense (m close to n^2).
 *   For traversals like BFS on a sparse graph, lists are the better choice.
 */

// n    = number of nodes
// node = starting node
// a    = adjacency list: a[x] holds all neighbors of x
void bfs(int n, int node, vector<vector<int>>& a)
{
	// viz[i] tells us whether node i was already discovered.
	vector<bool> viz(n + 1);

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

		// Look at every neighbor of this node.
		for (auto it : a[front])
			// If the neighbor has not been discovered yet
			if (!viz[it])
			{
				viz[it] = 1;       // mark it as discovered
				cout << it << " "; // print it (this is its BFS visiting order)
				q.push(it);        // explore its neighbors later
			}
	}
}

int main()
{
	// n = number of nodes, m = number of edges
	int n, m;
	cin >> n >> m;

	// Adjacency list: n + 1 vectors so indices 1..n are valid (index 0 unused).
	vector<vector<int>> a(n + 1);

	// Read the edges. The graph is undirected, so each edge x-y is stored
	// in both directions: y is a neighbor of x, and x is a neighbor of y.
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >> y;
		a[x].push_back(y);
		a[y].push_back(x);
	}

	// Run BFS starting from node 1.
	// Only the nodes reachable from node 1 will be printed.
	bfs(n, 1, a);
}