#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define DEBUG 1
#if DEBUG
#define PRINT(x) cout << x
#else
#define PRINT(x)
#endif

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
		PRINT("부분집합의 원소 개수: " << size << endl);

		for (auto subset : allSubsets[size])
		{
			PRINT("\t{ ");

			int sum = 0;
			for (auto number : subset)
			{
				sum += number;
				PRINT(number << " ");
			}

			PRINT("} = " << sum << endl);

			if (sum == target)
			{
				return true;
			}
		}
	}

	return false;
}

int main()
{
	vector<int> set = { 13, 79, 45, 29 };
	
	int target = 10000;

	bool found = SubsetSum_BruteForce(set, target);

	if (found)
	{
		cout << "부분집합의 합이 " << target << "인 경우가 있습니다." << endl;
	}
	else
	{
		cout << "부분집합의 합이 " << target << "인 경우가 없습니다." << endl;
	}
}
