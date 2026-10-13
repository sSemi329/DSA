#include <iostream>
#include <vector>
using namespace std;

/*
 * DSU (Disjoint Set Union) with union by size.
 *
 * Every group of friends is a tree. The root of the tree represents the
 * whole group, and the root stores the size of the group.
 * Always attaching the smaller tree under the bigger one keeps every tree
 * at height O(log n), so each operation is fast.
 * 
 * In this code we solve a problem to show for what is DSU used
 * When we have q quarries and we want to do the union operation on 2 trees,
 * This Solution is very efficient and we make sure using the group_size vector
 * That we keep the lenghts of the trees in log(n)
 */

 // parent[i] = parent of node i in its tree (parent[i] == i means i is a root)
 // size[i]   = number of nodes in the tree rooted at i
 //             (only meaningful when i is a root)

vector<int> parent, group_size;

// Returns the root of the tree that contains node x.
// We climb from x upwards until we reach a node that is its own parent.
int find_root(int x)
{
	if (parent[x] == x)
		return x;
	return find_root(parent[x]);
}

// Merges the groups that contain x and y.
void unite(int x, int y)
{
	// Work with the roots, since they represent the groups.
	x = find_root(x);
	y = find_root(y);

	// If the roots are different, the nodes are in different groups.
	if (x != y)
	{
		// Make sure x is the root of the bigger tree.
		if (group_size[x] < group_size[y])
			swap(x, y);

		// Attach the smaller tree under the bigger one
		// and update the size of the new, merged group.
		parent[y] = x;
		group_size[x] += group_size[y];
	}
}

int main()
{
	// n       = number of people (nodes)
	// queries = number of operations to process
	int n, queries;
	cin >> n >> queries;

	parent.resize(n + 1);
	group_size.assign(n + 1, 1); // every group starts with exactly 1 person

	// At the beginning everyone is alone: each node is its own root.
	for (int i = 1; i <= n; i++)
		parent[i] = i;

	while (queries--)
	{
		int type;
		cin >> type;

		if (type == 1)
		{
			// Type 1: x and y become friends, so their groups are merged.
			int x, y;
			cin >> x >> y;
			unite(x, y);
		}
		else if (type == 2)
		{
			// Type 2: print how many people are in the group of z.
			// The size is stored in the root of the group.
			int z;
			cin >> z;
			cout << group_size[find_root(z)] << '\n';
		}
	}
}