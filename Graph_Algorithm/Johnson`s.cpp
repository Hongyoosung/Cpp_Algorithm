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

// 최소 거리 값을 갖는 정점 번호를 반환
int GetMinDistance(vector<int>& dist, vector<bool>& visited)
{
	int min = UNKNOWN;
	int minIdx = -1;

	for (int i = 0; i < dist.size(); i++)
	{
		if (!visited[i] && dist[i] <= min)
		{
			min = dist[i];
			minIdx = i;
		}
	}

	return minIdx;
}

bool HasNegativeCycle(const vector<Edge>& edges, vector<int> dist)
{
	for (auto& e : edges)
	{
		if (dist[e.src] == UNKNOWN)
			continue;

		if (dist[e.src] + e.weight < dist[e.dst])
			return true;
	}

	return false;
}

vector<int> BellmanFord(vector<Edge>& edges, int V)
{
	vector<int> dist(V + 1, UNKNOWN); // 최단 거리 저장, 더미 정점 추가
	
	int s = V;

	for (int i = 0; i < V; i++)
	{
		edges.push_back(Edge{ s, i, 0 });
	}

	dist[s] = 0;

	// 정점 개수가 V+1개이므로 V번 반복
	for (int i = 0; i < V; i++)
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

	// 음수 사이클 존재 여부 확인
	if (HasNegativeCycle(edges, dist))
	{
		cout << "음수 사이클이 존재합니다." << endl;
		return {};
	}

	return dist;
}


vector<int> Dijkstra(vector<Edge> edges, int V, int start)
{
	vector<int> dist(V, UNKNOWN); // 최단 거리 저장
	vector<bool> visited(V, false); // 방문 여부 저장

	dist[start] = 0; // 시작 정점의 거리는 0

	for (int i = 0; i < V - 1; i++)
	{
		// 방문하지 않은 정점 중에서 최소 거리 정점을 찾음
		int curr = GetMinDistance(dist, visited);

		visited[curr] = true; // 최소 거리 정점 방문 처리

		for (auto& e : edges)
		{
			// 인접한 정점만 고려
			if(e.src != curr)
				continue;

			// 이미 방문했으면 무시
			if(visited[e.dst])
				continue;

			// 새로운 경로가 더 짧으면 업데이트
			if(dist[curr] != UNKNOWN && dist[e.dst] > dist[curr] + e.weight)
				dist[e.dst] = dist[curr] + e.weight;
		}
	}

	return dist;
}


void Johnson(vector<Edge> edges, int V)
{
	// 더미 정점을 추가한 그래프에서 최단 거리를 계산
	vector<int> h = BellmanFord(edges, V);

	if(h.empty())
		return;

	// 엣지 가중치 재설정
	for (auto& e : edges)
	{
		e.weight += h[e.src] - h[e.dst];
	}

	// 모든 정점들 사이의 최단 거리를 저장
	vector<vector<int>> shortest(V);

	for (int i = 0; i < V; i++)
	{
		shortest[i] = Dijkstra(edges, V, i);
	}

	// 가중치 변환 수식을 역으로 적용하여 최단 거리를 출력
	for (int i = 0; i < V; i++)
	{
		cout << i << ":\n";

		for (int j = 0; j < V; j++)
		{
			if (shortest[i][j] != UNKNOWN)
			{
				shortest[i][j] += h[j] - h[i];

				cout << "\t" << j << ": " << shortest[i][j] << endl;
			}
		}
	}
}

int main()
{
	int V = 5;			// 정점의 개수
	vector<Edge> edges; // 엣지 정보

	vector<vector<int>> edge_map  // {시작 정점, 목표 정점, 가중치}
	{
		{0, 1, -7},
		{1, 2, -2},
		{2, 0, 10},
		{0, 3, -5},
		{0, 4, 2},
		{3, 4, 4},
	};

	// 엣지 정보 초기화
	for (auto& e : edge_map)
	{
		edges.emplace_back(Edge{ e[0], e[1], e[2] });
	}

	Johnson(edges, V);

	return 0;
}

