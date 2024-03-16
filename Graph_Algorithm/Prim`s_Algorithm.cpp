#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <limits>

using namespace std;

template <typename T>
struct Edge
{
	unsigned src; // 출발 정점
	unsigned dst; // 도착 정점
	T weight;     // 가중치
};

template <typename T>
class Graph
{
public:
	// N개의 정점으로 구성된 그래프
	Graph(unsigned N) : V(N) {}

	// 그래프의 정점 개수 반환
	auto vertices() const { return V; }

	// 전체 엣지 리스트 반환
	auto& edges() const { return edge_list; }

	// 정점 v에서 나가는 모든 엣지 반환
	auto edges(unsigned v) const
	{
		vector<Edge<T>> edges_from_v;
		for (auto& e : edge_list)
		{
			if (e.src == v)
				edges_from_v.emplace_back(e);
		}

		return edges_from_v;
	}

	void add_edge(Edge<T> e)
	{
		// 엣지 양 끝 정점 ID가 유효한지 검사
		if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
			edge_list.emplace_back(e);
		else
			cerr << "Error: invalid edge\n";
	}

	// 표준 출력 스트림 지원
	template <typename U>
	friend ostream& operator<<(ostream& os, const Graph<U>& G);

private:
	unsigned V; // 정점 개수
	vector<Edge<T>> edge_list; // 엣지 리스트
};

// 그래프 출력 함수
template <typename U>
ostream& operator<<(ostream& os, const Graph<U>& G)
{
	for (unsigned i = 1; i <= G.vertices(); ++i)
	{
		os << i << ":\t";

		auto edges = G.edges(i);

		for (auto& e : edges)
			os << e.dst << "(" << e.weight << ")\t";
		os << endl;
	}

	return os;
}

template <typename T>
auto create_reference_graph()
{
	Graph<T> G(8);

	map<unsigned, vector<pair<unsigned, T>>> edge_map;

	edge_map[1] = { {2, 2}, {5, 3} };
	edge_map[2] = { {1, 2}, {5, 5}, {4, 1} };
	edge_map[3] = { {4, 2}, {7, 3} };
	edge_map[4] = { {2, 1}, {3, 2}, {5, 2}, {6, 4}, {8, 5} };
	edge_map[5] = { {1, 3}, {2, 5}, {4, 2}, {8, 3} };
	edge_map[6] = { {4, 4}, {7, 4}, {8, 1} };
	edge_map[7] = { {3, 3}, {6, 4} };
	edge_map[8] = { {4, 5}, {5, 4}, {6, 1} };

	for (auto& i : edge_map)
	{
		for (auto& j : i.second)
		{
			G.add_edge(Edge<T>{ i.first, j.first, j.second});
		}
	}

	return G;
}

template <typename T>
struct Label
{
	unsigned ID; // 정점 ID
	T distance;  // 시작점으로부터의 거리

	// Label 객체 비교 함수
	inline bool operator> (const Label<T>& I) const
	{
		return this->distance > I.distance;
	}
};

// 프림 알고리즘
template <typename T>
auto prim_MST(const Graph<T>& G, unsigned src)
{
	// 최소 신장 트리
	vector<unsigned> MST;

	// 정점 방문 여부
	vector<bool> visited(G.vertices() + 1, false);

	// 우선순위 큐
	priority_queue<Label<T>, vector<Label<T>>, greater<Label<T>>> PQ;

	// 시작 정점을 우선순위 큐에 삽입
	PQ.push({ src, 0 });

	while (!PQ.empty())
	{
		// 우선순위 큐에서 최소 거리 Label 추출
		auto label = PQ.top();
		PQ.pop();

		// 방문한 정점이면 건너뛰기
		if (visited[label.ID])
			continue;

		// 정점 방문 처리
		visited[label.ID] = true;

		// 최소 신장 트리에 정점 추가
		MST.push_back(label.ID);

		// 현재 정점에서 나가는 모든 엣지를 우선순위 큐에 삽입
		for (auto& e : G.edges(label.ID))
		{
			if (!visited[e.dst])
				PQ.push({ e.dst, e.weight });
		}
	}

	return MST;
}

 
int main()
{
	using T = unsigned;

	// 그래프 객체 생성
	auto G = create_reference_graph<T>();
	cout << "[입력 그래프]\n" << G << endl;

	auto MST = prim_MST(G, 1);

	cout << "[최소 신장 트리]\n";
	for (auto& v : MST)
		cout << v << " ";
	cout << endl;
}
