#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define NMAX 1001

int n, m, a[NMAX][NMAX],viz[NMAX];

void bfs(int node)
{
	queue<int>q;
	viz[node] = 1;
	q.push(node);
	cout<<node<<" ";
	while (!q.empty())
	{
		int front = q.front();
		q.pop();
		for(int i=1;i<=n;i++)
			if (!viz[i] && a[front][i])
			{
				viz[i] = 1;
				cout << i << " ";
				q.push(i);
			}
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >> y;
		a[x][y] = 1;
		a[y][x] = 1;
	}
	bfs(1);
}