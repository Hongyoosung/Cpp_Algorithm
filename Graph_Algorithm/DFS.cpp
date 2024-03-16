#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <stack>

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

	edge_map[1] = { {2, 0}, {5, 0} };
	edge_map[2] = { {1, 0}, {5, 0}, {4, 0} };
	edge_map[3] = { {4, 0}, {7, 0} };
	edge_map[4] = { {2, 0}, {3, 0}, {5, 0}, {6, 0}, {8, 0} };
	edge_map[5] = { {1, 0}, {2, 0}, {4, 0}, {8, 0} };
	edge_map[6] = { {4, 0}, {7, 0}, {8, 0} };
	edge_map[7] = { {3, 0}, {6, 0} };
	edge_map[8] = { {4, 0}, {5, 0}, {6, 0} };

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
auto depth_first_search(const Graph<T>& G, unsigned s)
{
	vector<unsigned> visit_order;
	stack<unsigned> S;
	set<unsigned> visited;

	S.push(s);

	// 스택이 빌 때까지 반복
	while (!S.empty())
	{
		auto v = S.top();
		S.pop();
		
		// 이미 방문한 정점이면 스킵
		if (visited.find(v) != visited.end())
			continue;

		// 정점 v를 방문
		visited.insert(v);
		visit_order.push_back(v);

		// 정점 v에 인접한 모든 정점을 스택에 추가
		auto edges = G.edges(v);
	
		for (auto e : edges)
		{
			if (visited.find(e.dst) == visited.end())
				S.push(e.dst);
		}
	}

	return visit_order;
}
 
int main()
{
	using T = unsigned;

	// 그래프 객체 생성
	auto G = create_reference_graph<T>();
	cout << "[입력 그래프]\n" << G << endl;

	// 1번 정점부터 BFS 실행 & 방문순서 출력
	cout << "[DFS 방문 순서]\n";

	auto bfs_visit_order = depth_first_search(G, 1);

	for (auto v : bfs_visit_order)
		cout << v << " ";
}
