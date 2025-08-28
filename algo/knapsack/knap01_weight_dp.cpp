#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

struct Item {
  int weight;
  int value;
};

long long knap01_max_value_1d(const vector<Item> &items, int W) {
  vector<long long> dp(W + 1, 0);

  for (const auto &item : items) {
    for (int w = W; w >= item.weight; --w) {
      dp[w] = max(dp[w], dp[w - item.weight] + item.value);
    }
  }

  return *max_element(dp.begin(), dp.end());
}

int main() {
  const int W = 10;
  const vector<Item> items = {
      {6, 30},
      {3, 14},
      {4, 16},
      {2, 9},
  };

  long long res = knap01_max_value_1d(items, W);
  assert(res == 46);
  return 0;
}
