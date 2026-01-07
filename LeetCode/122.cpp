#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(n)
 * Space: O(1)
 */
class Solution1 {
public:
  int maxProfit(vector<int> const &prices) {
    int n = (int)prices.size();
    int profit = 0, i = 0;
    while (i + 1 < n) {
      while (i + 1 < n && prices[i] >= prices[i + 1])
        i++;
      int buy = i;

      while (i + 1 < n && prices[i] <= prices[i + 1])
        ++i;
      int sell = i;

      profit += prices[sell] - prices[buy];
    }

    return profit;
  }
};

/*
 * Time: O(n)
 * Space: O(1)
 */
class Solution2 {
public:
  int maxProfit(vector<int> const &prices) {
    int n = (int)prices.size();
    int profit = 0;
    for (int i = 1; i < n; ++i) {
      if (prices[i - 1] < prices[i])
        profit += prices[i] - prices[i - 1];
    }
    return profit;
  }
};

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

int main() {
  auto s = new Solution2;
  int want, res;

  want = 7;
  res = s->maxProfit({7, 1, 5, 3, 6, 4});
  assert(res == want);
  println("ok");

  want = 4;
  res = s->maxProfit({1, 2, 3, 4, 5});
  assert(res == want);
  println("ok");

  want = 0;
  res = s->maxProfit({7, 6, 4, 3, 2, 1});
  assert(res == want);
  println("ok");

  want = 0;
  res = s->maxProfit({2, 1});
  assert(res == want);
  println("ok");

  return 0;
}
