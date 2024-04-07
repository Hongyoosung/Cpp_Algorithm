#include <vector>  // 벡터 라이브러리 포함
#include <stack>   // 스택 라이브러리 포함
#include <iostream> // 입출력 라이브러리 포함

using namespace std;  // std 네임스페이스 사용

// FillStack 함수: 주어진 정점에서 출발하여 DFS 탐색을 수행하고 스택에 삽입
void FillStack(int node, vector<bool>& visited, vector<vector<int>>& adj, stack<int>& stack) {
  visited[node] = true;  // 방문 완료 표시

  // 연결된 모든 노드를 탐색
  for (auto next : adj[node]) {
    if (!visited[next]) {
      FillStack(next, visited, adj, stack);  // 재귀적으로 연결된 노드 탐색
    }
  }

  // DFS 탐색 종료 후 스택에 현재 노드 삽입 (역순으로 탐색 결과 담김)
  stack.push(node);
}

// Transpose 함수: 그래프의 전치 행렬 생성
vector<vector<int>> Transpose(int V, vector<vector<int>> adj) {
  vector<vector<int>> transposed(V);  // 전치 행렬 초기화 (V x V 크기)

  // 원본 그래프를 순회하면서 연결 정보를 반대로 저장
  for (int i = 0; i < V; i++) {
    for (auto next : adj[i]) {
      transposed[next].push_back(i);
    }
  }

  return transposed;
}

// CollectConnectedComponents 함수: 전치 행렬을 이용하여 DFS 탐색으로 연결 요소 추출
void CollectConnectedComponents(int node, vector<bool>& visited, vector<vector<int>>& adj, vector<int>& component) {
  visited[node] = true;  // 방문 완료 표시
  component.push_back(node);  // 현재 노드를 연결 요소에 추가

  // 연결된 모든 노드를 탐색
  for (auto next : adj[node]) {
    if (!visited[next]) {
      CollectConnectedComponents(next, visited, adj, component);  // 재귀적으로 연결된 노드 탐색
    }
  }
}

// Kosaraju 알고리즘: 강한 연결 요소 계산
vector<vector<int>> Kosaraju(int V, vector<vector<int>> adj) {
  vector<bool> visited(V, false);  // 방문 여부 표시 벡터 초기화
  stack<int> stack;                // 깊이 우선 탐색 수행 시 사용하는 스택

  // 첫 번째 DFS 탐색: 각 정점에서 출발하여 DFS 수행 후 스택에 역순으로 정점 삽입
  for (int i = 0; i < V; i++) {
    if (!visited[i]) {
      FillStack(i, visited, adj, stack);
    }
  }

  // 전치 행렬 생성
  vector<vector<int>> transposed = Transpose(V, adj);

  // 방문 여부 표시 벡터 초기화 (두 번째 DFS 실행을 위해)
  fill(visited.begin(), visited.end(), false);

  vector<vector<int>> connectedComponents;  // 강한 연결 요소를 저장할 벡터

  // 스택이 비어있지 않을 때까지 반복
  while (!stack.empty()) {
    int node = stack.top();  // 스택에서 상단 노드 pop
    stack.pop();

    if (!visited[node]) {
      vector<int> component;  // 현재 연결 요소를 저장할 벡터
      CollectConnectedComponents(node, visited, transposed, component);
      connectedComponents.push_back(component);  // 찾은 연결 요소를 결과 벡터에 추가
    }
  }

  return connectedComponents;
}

int main() {
  int V = 9;  // 그래프의 정점 개수

  // 예시 그래프 (유향 그래프)
  vector<vector<int>> adj = {
    {1, 3},
    {2, 4},
    {3, 5},
    {7},
    {2},
    {4, 6},
    {7
}
