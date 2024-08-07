#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

const int UNKNOWN = 1e9;

int V, E;
vector<vector<int>> adj;
vector<vector<int>> weight;

map<pair<int, int>, int> memo;

int ShortestPath_Memoization(int depth, int node, vector<vector<int>>& adj, vector<vector<int>>& weight)
{
	// 맵에 키가 있는지 확인
	if (memo.find({ node, depth }) != memo.end())
	{
		return memo[{node, depth}];
	}

	memo[{node, depth}] = UNKNOWN;

	// 인접한 엣지에 대한 반복
	for (auto next : adj[node])
	{
		int w = weight[node][next];
		int dist = ShortestPath_Memoization(depth - 1, next, adj, weight) + w;

		memo[{node, depth}] = min(memo[{node, depth}], dist);
	}

	return memo[{node, depth}];
}

vector<int> SingleSourceShortestPaths(int source)
{
	vector<vector<int>> adj_t(V);
	vector<vector<int>> weight_t(V, vector<int>(V, UNKNOWN));

	memo.clear();

	for (int i = 0; i < V; i++)
	{
		// 전치 그래프 생성
		for (auto j : adj[i])
		{
			adj_t[j].push_back(i);
			weight_t[j][i] = weight[i][j];
		}

		// 기저조건 - 시작 정점에서 자기 자신까지의 최단 거리는 항상 0
		memo[{source, i}] = 0;

		if (i != source)
		{
			// V-1 반복 후 소스 이외의 노드에 도달한 경우
			// 경로가 존재하지 않음
			memo[{i, 0}] = UNKNOWN;
		}
	}

	vector<int> distance(V);

	for (int i = 0; i < V; i++)
	{
		distance[i] = ShortestPath_Memoization(V - 1, i, adj_t, weight_t);
	}

	return distance;
}



int main()
{
	cin >> V >> E;

	weight.resize(V, vector<int>(V, UNKNOWN));
	adj.resize(V);

	for (int i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back(v);
		weight[u][v] = w;
	}

	vector<vector<int>> paths(V);
	
	for (int i = 0; i < V; i++)
	{
		paths[i] = SingleSourceShortestPaths(i);
	}

	cout << "각 정점 사이의 최단 거리: " << endl;

	for (int i = 0; i < V; i++)
	{
		cout << i << ": ";

		for (int j = 0; j < V; j++)
		{
			(paths[i][j] == UNKNOWN) ? cout << "- " : cout << paths[i][j] << " ";
		}

		cout << endl;
	}
}
