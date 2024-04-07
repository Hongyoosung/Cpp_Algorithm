#include <vector>
#include <stack>
#include <iostream>

using namespace std;

void FillStack(int, vector<bool>&, vector<vector<int>>&, stack<int>&);
vector<vector<int>> Transpose(int, vector<vector<int>>);
void CollectConnectedComponents(int, vector<bool>&, vector<vector<int>>&, vector<int>&);

vector<vector<int>> Kosaraju(int V, vector<vector<int>> adj)
{
	vector<bool> visited(V, false);
	stack<int> stack;

	for (int i = 0; i < V; i++)
	{
		if (!visited[i])
			FillStack(i, visited, adj, stack);
	}

	vector<vector<int>> transposed = Transpose(V, adj);

	fill(visited.begin(), visited.end(), false);

	vector<vector<int>> connectedComponents;

	while (!stack.empty())
	{
		int node = stack.top();
		stack.pop();

		if (!visited[node])
		{
			vector<int> component;
			CollectConnectedComponents(node, visited, transposed, component);
			connectedComponents.push_back(component);
		}
	}

	return connectedComponents;
}

void FillStack(int node, vector<bool>& visited, vector<vector<int>>& adj, stack<int>& stack)
{
	visited[node] = true;

	for (auto next : adj[node])
	{
		if (!visited[next])
			FillStack(next, visited, adj, stack);
	}

	stack.push(node);
}

vector<vector<int>> Transpose(int V, vector<vector<int>> adj)
{
	vector<vector<int>> transposed(V);

	for (int i = 0; i < V; i++)
	{
		for (auto next : adj[i])
			transposed[next].push_back(i);
	}

	return transposed;
}

void CollectConnectedComponents(int node, vector<bool>& visited,
	vector<vector<int>>& adj, vector<int>& component)
{
	visited[node] = true;
	component.push_back(node);

	for (auto next : adj[node])
	{
		if (!visited[next])
			CollectConnectedComponents(next, visited, adj, component);
	}
}

int main()
{
	int V = 9;
	vector<vector<int>> adj =
	{
		{1, 3},
		{2, 4},
		{3, 5},
		{7},
		{2},
		{4, 6},
		{7, 2},
		{8},
		{3}
	};

	vector<vector<int>> connectedComponents = Kosaraju(V, adj);

	cout << "강한 연결 요소 개수: " << connectedComponents.size() << endl;

	for (auto& component : connectedComponents)
	{
		cout << "강한 연결 요소: ";
		for (auto node : component)
			cout << node << " ";
		cout << endl;
	}

	return 0;
}
