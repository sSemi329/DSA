/*
PROBLEM STATEMENT
---------------------------------------------------------------------
Given an array of n numbers a[1..n] and m operations of two types:
  1 x y  -> set a[x] = y            (point update)
  2 x y  -> print a[x] + a[x+1] + ... + a[y]   (range sum query)

WHY A SEGMENT TREE INSTEAD OF JUST SCANNING THE ARRAY?
---------------------------------------------------------------------
Option 1: plain array
  - update: a[x] = y             -> O(1)   (fast)
  - query: scan x..y             -> O(n)   (slow)
  With n, m ~ 10^5, the worst case is 10^5 * 10^5 = 10^10 operations.
  Far too slow, we exceed the time limit.

Option 2: prefix sums (prefix[i] = a[1] + ... + a[i])
  - query: prefix[y] - prefix[x-1]  -> O(1)   (fast)
  - update: changing a[x] breaks prefix[x..n],
			so they must be recomputed         -> O(n)   (slow)

Each option is fast for one operation and slow for the other.
When updates and queries are mixed, one of them always slows us down.

Option 3: segment tree
  - update: O(log n)
  - query:  O(log n)
  Both are fast. Total: O((n + m) * log n).

THE IDEA: each node stores the sum of an interval.
  - The root stores the sum of [1, n].
  - Its children store the sums of the halves [1, mid] and [mid+1, n], etc.
  - The leaves store a single element each.

  Query: any interval [x, y] decomposes into at most ~2*log n nodes
  whose sums are already computed, so we just add them up.
  Update: only the corresponding leaf and its ~log n ancestors change
  (the leaf -> root path); the rest of the tree stays the same.

Example for a = [5, 3, 8, 2]:
			  [1,4]=18
			/          \
	   [1,2]=8        [3,4]=10
	   /     \         /     \
	[1,1]=5 [2,2]=3 [3,3]=8 [4,4]=2
  Sum over [2,4] = node [2,2] + node [3,4] = 3 + 10 = 13
  (only 2 nodes added, instead of 3 elements).

We store the tree in an array in the following way: first n positions is the array,
and after that, n+1 represents the sum of elements 1 and 2, n+2 the sum of 3 and 4 and so on 
*/

#include <iostream>
#include <vector>
using namespace std;

int n, m, a[100010];   
long long tree[400010];  // the tree; 4*n slots so a tree over n elements always fits
// tree[node] = sum of the elements in the node's interval
// children of node are 2*node (left) and 2*node+1 (right)

// node = current node, [left, right] = interval covered by the node
void build(int node, int left, int right)
{
	if (left == right)
	{
		// Leaf: the interval has a single element, so the sum is that element
		tree[node] = a[left];
	}
	else
	{
		int mid = (right + left) / 2;      

		build(2 * node, left, mid);    
		build(2 * node + 1, mid + 1, right);

		// Interval sum = sum of the left half + sum of the right half
		tree[node] = tree[2 * node] + tree[2 * node + 1];
	}
}

// Sets a[poz] = newval and updates the tree.
// Cost O(log n): exactly one node is visited on each level.
void update(int node, int left, int right, int poz, int newval)
{
	if (left == right)
	{
		// Reached the leaf corresponding to position poz: change it
		tree[node] = newval;
	}
	else
	{
		int mid = (left + right) / 2;

		// Descend only into the half that contains position poz
		if (poz > mid)
			update(2 * node + 1, mid + 1, right, poz, newval);
		else
			update(2 * node, left, mid, poz, newval);

		// On the way back from the recursion, recompute this node's sum from its two children.
		// This updates every node on the leaf -> root path.
		tree[node] = tree[2 * node] + tree[2 * node + 1];
	}
}

// Cost O(log n): on each level at most 2 partially-overlapping nodes are expanded.
long long querry(int node, int left, int right, int qleft, int qright)
{
	// Case 1: the node's interval is COMPLETELY inside the query
	if (left >= qleft && right <= qright)
		return tree[node];

	// Case 2: the node's interval is COMPLETELY outside the query
	if (qright < left || right < qleft)
		return 0;

	// Case 3: partial overlap
	// split the problem: ask both children and add their results
	else
	{
		int mid = (left + right) / 2;

		return querry(2 * node, left, mid, qleft, qright)
			+ querry(2 * node + 1, mid + 1, right, qleft, qright);
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	build(1, 1, n);   // the root (node 1) covers the whole interval [1, n]

	while (m--)
	{
		int op, x, y;
		cin >> op >> x >> y;

		if (op == 1)
		{
			a[x] = y;                 // optional, the tree already holds the value
			update(1, 1, n, x, y);
		}
		else
		{
			cout << querry(1, 1, n, x, y) << '\n';
		}
	}
}