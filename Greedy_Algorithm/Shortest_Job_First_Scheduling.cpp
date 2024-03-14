#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;


// 대기시간을 구하는 함수 생성, 일처리 시간 벡터를 인자로 받는다.
template<typename T>
auto compute_waitingt_times(vector<T>& service_times)
{
	// 대기시간 벡터 생성, 그림 5-2의 B i
	vector<T> W(service_times.size()):
	
	W[0] = 0; // 첫 번째 사람의 대기시간은 0이다.

	// 
	for (auto i = 1; i < service_times.size(); i++)
		W[i] = W[i - 1] + service_times[i - 1];

	return W;
}


// 벡터 출력 함수
template<typename T>
void print_vector(vector<T>& v)
{
	for (auto& i : v)
	{
		// 다음에 출력될 내용의 최소 폭(길이)을 2로 설정. 지정된 값의 폭보다 작을 경우
		// 남는 공간에 여백을 채워 출력
		cout.width(2); 
		cout << i << " ";
	}
	cout << endl;
}


// 메인 함수에서 사용할 함수, 처리시간을 인자로 받아 대기시간을 구한 후 평균 대기시간을 출력한다.
template<typename T>
void compute_and_print_waiting_times(vector<T>& service_times)
{
	auto waiting_times = compute_waiting_times<int>(service_times);

	cout << "- 처리시간: ";
	print_vector<T>(service_times);

	cout << "- 대기시간: ";
	print_vector<T>(waiting_times);

	// 벡터의 요소를 모두 더하는 함수 accumulate, 합산 범위 시작과 끝, 그리고 합산 시작 초기 값을 인자로 받는다.
	auto ave_waiting_times = accumulate(waiting_times.begin(), waiting_times.end(), 0.0)
													 / waiting_times.size();

	cout << "- 평균 대기시간: " << ave_waiting_times;

	cout << endl;
}

int main(int argc, char* argv[])
{
	vector<int> service_times {8, 1, 2, 4, 9, 2, 3, 5};

	cout << "[처음 일 처리시간 & 대기시간]" << endl;

	// 처음 순서의 처리시간, 대기시간, 평균 대기시간을 출력
	compute_and_print_waiting_times<int>(service_times);

	// 일 처리시간을 오름차순으로 정렬
	sort(service_times.begin(), service_times.end());

	cout << endl;

	cout << "[정렬 후 일 처리시간 & 대기시간]" << endl;

	compute_and_prin_waiting_times<int>(service_times);
}
