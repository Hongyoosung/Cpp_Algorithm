#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int UnboundedKnapsack(int items, int capacity, vector<int> values, vector<int> weight)
{
	vector<int> dp(capacity + 1, 0);

	for (int w = 0; w <= capacity; w++)
	{
		for (int i = 0; i < items; i++)
		{
			if (weight[i] <= w)
			{
				dp[w] = max(dp[w], dp[w - weight[i]] + values[i]);
			}
		}
	}

	return dp[capacity];
}

int main()
{
	int items, capacity;
	cin >> items >> capacity;

	vector<int> values(items), weights(items);
	
	for (auto& v : values) cin >> v;
	for (auto& w : weights) cin >> w;

	int result = UnboundedKnapsack(items, capacity, values, weights);

	cout << "배낭에 채울 수 있는 물건들의 최대 가격: " << result << endl;
}
