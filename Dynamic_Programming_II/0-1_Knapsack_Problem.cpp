#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Knapsack_01(int items, int capacity, vector<int>& values, vector<int>& weights) 
{
	vector<vector<int>> dp(items + 1, vector<int>(capacity + 1, 0));

	// 타뷸레이션 기법
	for (int i = 1; i <= items; i++)
	{
		int currentWeight = weights[i - 1];
		int currentValue = values[i - 1];

		for (int totalWeight = 1; totalWeight <= capacity; totalWeight++)
		{
			if (currentWeight > totalWeight)
			{
				dp[i][totalWeight] = dp[i - 1][totalWeight];
			}
			else
			{
				dp[i][totalWeight] = max(dp[i - 1][totalWeight], 
					dp[i - 1][totalWeight - currentWeight] + currentValue);
			}
		}
	}

	return dp[items][capacity];
}

int main()
{
	int items, capacity;
	cin >> items >> capacity;

	vector<int> values(items), weights(items);

	for (auto& v : values) cin >> v;
	for (auto& w : weights) cin >> w;

	int result = Knapsack_01(items, capacity, values, weights);

	cout << "배낭에 채울 수 있는 물건들의 최대 가격: " << result << endl;
}
