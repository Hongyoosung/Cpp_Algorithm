#include <vector>
#include <iostream>
#include <climits>

using namespace std;

struct Edge
{
	int src;    // 출발 정점 ID
	int dst;    // 도착 정점 ID
	int weight; // 가중치
};

const int UNKNOWN = INT_MAX; // 무한대 값으로 초기화

vector<int> BellmanFord(vector<Edge>& edges, int V, int start)
{
	vector<int> dist(V, UNKNOWN); // 최단 거리 저장
	dist[start] = 0;		      // 시작 정점의 거리는 0

	// 최단 거리 갱신, (V - 1)번 반복
	for (int i = 0; i < V - 1; i++)
	{
		// 전체 엣지 순회
		for (Edge& edge : edges)
		{
			// 엣지의 시작 정점의 거리 값이 UNKNWON이면 스킵
			if (dist[edge.src] == UNKNOWN)
			{
				continue;
			}

			// 인접한 정점의 거리 값이 새로운 경로에 의한 거리 값보다 크면	갱신
			if (dist[edge.dst] > dist[edge.src] + edge.weight)
			{
				dist[edge.dst] = dist[edge.src] + edge.weight;
			}
		}
	}

	return dist;
}

int main()
{
	int V = 5; // 정점의 개수
	vector<Edge> edges; // 엣지 정보

	vector<vector<int>> edge_map  // {시작 정점, 목표 정점, 가중치}
	{
		{0, 1, 3},
		{1, 2, 5},
		{1, 3, 10},
		{3, 2, -7},
		{2, 4, 2}
	};

	// 엣지 정보 초기화
	for (auto& e : edge_map)
	{
		edges.emplace_back(Edge{ e[0], e[1], e[2] });
	}

	int start = 0; // 시작 정점
	vector<int> dist = BellmanFord(edges, V, start);

	cout << "[" << start << "번 정점으로부터 최소 거리]" << endl;

	// 최단 거리 출력
	for (int i = 0; i < dist.size(); i++)
	{
		if( dist[i] == UNKNOWN)
			cout << i << "번 정점: 방문 불가" << endl;
		else
			cout << i << "번 정점: " << dist[i] << endl;
	}

	return 0;
}

