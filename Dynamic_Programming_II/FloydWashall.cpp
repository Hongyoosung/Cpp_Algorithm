#include <vector>
#include <iostream>

using namespace std;

const int UNKNOWN = 1e9;

vector<vector<int>> FloydWarsall(int V, vector<vector<int>> weight)
{
	// 모든 정점 쌍 거리를 저장할 distance 배열
	vector<vector<int>> distance(V, vector<int>(V, UNKNOWN));

	// 가중치 및 자기 자신의 거리 초기화
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			distance[i][j] = weight[i][j];
		}

		distance[i][i] = 0;
	}

	// 플로이드-워셜 알고리즘
	for (int mid = 0; mid < V; mid++)
	{
		for (int start = 0; start < V; start++)
		{
			for (int end = 0; end < V; end++)
			{
				if (distance[start][mid] != UNKNOWN && distance[mid][end] != UNKNOWN)
				{
					distance[start][end] = min(distance[start][end], distance[start][mid] + distance[mid][end]);
				}
			}
		}
	}
	
	for (int i = 0; i < V; i++)
	{
		// 자기 자신으로의 거리가 0보다 작으면 음수 가중치 사이클이 있는 것으로 판단
		if (distance[i][i] < 0)
		{
			return {};
		}
	}

	return distance;
}

int main()
{
	int V, E;
	cin >> V >> E;

	vector<vector<int>> weight(V, vector<int>(V, UNKNOWN));

	// 엣지 정보 입력
	for (int i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		weight[u][v] = w;
	}

	vector<vector<int>> distance = FloydWarsall(V, weight);

	if (distance.empty())
	{
		cout << "음수 가중치 사이클이 존재합니다." << endl;
		return 0;
	}

	// 결과 출력
	for (int i = 0; i < V; i++)
	{
		cout << i << endl;

		for (int j = 0; j < V; j++)
		{
			cout << "\t" << j << ": ";

			(distance[i][j] == UNKNOWN) ? cout << "_" << endl : cout << distance[i][j] << endl;
		}
	}
}
