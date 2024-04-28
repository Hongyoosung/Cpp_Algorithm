#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iomanip>

using namespace std;

#define DEBUG 1
#if DEBUG
#define PRINT(x) cout << x
#else
#define PRINT(x)
#endif

const int UNKNOWN = INT_MAX;

bool SubsetSum_Memoization(vector<int>& set, int sum, int i, vector<vector<int>>& memo)
{
	// 만약 현재 부분집합의 합이 target과 같다면
	if (sum == 0)
	{
		return true;
	}

	// 만약 현재 부분집합의 합이 target보다 크거나 집합의 끝에 도달했다면
	if (i == set.size() || set[i] > sum)
	{
		return false;
	};

	// 만약 memo[i][sum]이 계산되었다면 이를 반환
	if (memo[i][sum] != UNKNOWN)
	{
		return memo[i][sum];
	}

	// Case 1: sum에서 set[i]를 빼서 재귀 호출(i번째 원소를 부분집합에 추가)
	// Case 2: sum을 그대로 전달하여 재귀 호출(i번째 원소를 부분집합에 추가하지 않음)

	return memo[i][sum] = SubsetSum_Memoization(set, sum - set[i], i + 1, memo)
		|| SubsetSum_Memoization(set, sum, i + 1, memo);
}

bool SubsetSum_Backtracking(vector<int>& set, int sum, int i)
{
	// 만약 현재 부분집합의 합이 target과 같다면
	if (sum == 0)
	{
		return true;
	}

	// 만약 현재 부분집합의 합이 target보다 크거나 집합의 끝에 도달했다면
	if (i == set.size() || set[i] > sum)
	{
		return false;
	}

	// Case 1: sum에서 set[i]를 빼서 재귀 호출(i번째 원소를 부분집합에 추가)
	// Case 2: sum을 그대로 전달하여 재귀 호출(i번째 원소를 부분집합에 추가하지 않음)

	return SubsetSum_Backtracking(set, sum - set[i], i + 1)
		|| SubsetSum_Backtracking(set, sum, i + 1);
}

void GetAllSubsets(vector<int> set, vector<int> subset, int index,
	vector<vector<vector<int>>>& allSubsets) 
{
	// 집합 set의 끝에 다다른 경우
	if (index == set.size())
	{
		// 부분집합 크기를 인덱스로 사용하여 부분집합을 allSubsets에 추가
		allSubsets[subset.size()].push_back(subset);
		return;
	}

	// 원소를 추가하지 않고 재귀호출
	GetAllSubsets(set, subset, index + 1, allSubsets);

	// 원소를 부분집합에 추가한 후 재귀호출
	subset.push_back(set[index]);
	GetAllSubsets(set, subset, index + 1, allSubsets);
}

bool SubsetSum_BruteForce(vector<int> set, int target)
{
	vector<vector<vector<int>>> allSubsets(set.size() + 1);

	// 모든 부분집합을 구함
	GetAllSubsets(set, {}, 0, allSubsets);

	// 부분집합의 합이 target인 경우가 있는지 확인
	for (int size = 0; size <= set.size(); size++)
	{
		
		for (auto subset : allSubsets[size])
		{
			

			int sum = 0;
			for (auto number : subset)
			{
				sum += number;
				
			}

			

			if (sum == target)
			{
				return true;
			}
		}
	}

	return false;
}

void GetTime(clock_t& timer, string type)
{
	// 현재 시간에서 timer를 빼서 경과 시간을 계산
	timer = clock() - timer;

	// 화면에 경과 시간 출력
	cout << type << "방법 경과 시간: ";
	cout << fixed << setprecision(5) << (float)timer / CLOCKS_PER_SEC << endl;

	// timer를 현재 시간으로 설정
	timer = clock();
}

vector<string> types =
{
	"Burete Force",
	"Backtracking",
	"Memoization",
	"Tabulation"
};

int main()
{
	vector<int> set = {16, 1058, 22, 13, 46, 55, 3, 92, 47, 7,
						98, 367, 807, 106, 333, 85, 577, 9, 3059};

	int target = 6799;
	int tests = 3;

	sort(set.begin(), set.end());
	
	for (int i = 0; i < tests; i++)
	{
		bool found = false;

		clock_t timer = clock();

		switch (i)
		{
		case 0:
			found = SubsetSum_BruteForce(set, target);
			break;

		case 1:
			found = SubsetSum_Backtracking(set, target, 0);
			break;
		case 2:
		{
			// 메모이제이션 테이블 초기화
			vector<vector<int>> memo(set.size(), vector<int>(target + 1, UNKNOWN));
			found = SubsetSum_Memoization(set, target, 0, memo);
			break;
		}
		}

		if (found)
		{
			cout << "부분집합의 합이 " << target << "인 경우가 있습니다." << endl;
		}
		else
		{
			cout << "부분집합의 합이 " << target << "인 경우가 없습니다." << endl;
		}

		GetTime(timer, types[i]);
		cout << endl;
	}
}
