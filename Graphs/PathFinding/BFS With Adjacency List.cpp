#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(int n, int node,vector<vector<int>>&a)
{
	vector<bool>viz(n + 1);
	queue<int>q;
	viz[node] = 1;
	q.push(node);
	cout << node << " ";
	while (!q.empty())
	{
		int front = q.front();
		q.pop();
		for(auto it:a[front])
			if (!viz[it])
			{
				viz[it] = 1;
				cout << it << " ";
				q.push(it);
			}
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>>a(n+1);
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >> y;
		a[x].push_back(y);
		a[y].push_back(x);
	}
	bfs(n,1,a);
}