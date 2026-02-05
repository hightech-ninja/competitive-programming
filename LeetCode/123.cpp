#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(n)
 * Space: O(n)
 */
class Solution {
public:
  int maxProfit(vector<int> const &prices) {
    int n = (int)prices.size();


    vector<int> suff(n + 1, 0);
    int maxPrice = prices[n - 1];
    for (int i = n - 1; i >= 0; --i) {
        maxPrice = max(maxPrice, prices[i]);
        suff[i] = maxPrice - prices[i];
    }

    for (int i = n - 1; i >= 0; --i) {
        suff[i] = max(suff[i], suff[i + 1]);
    }

    int ans = 0;
    int minPrice = prices[0];
    for (int i = 0; i < n; ++i) {
        minPrice = min(minPrice, prices[i]);
        int pref_i = prices[i] - minPrice;
        ans = max(ans, pref_i + suff[i + 1]);
    }
    return ans;
  }
};

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

int main() {
  auto s = new Solution;
  int want, res;

  want = 6;
  res = s->maxProfit({3, 3, 5, 0, 0, 3, 1, 4});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 4;
  res = s->maxProfit({1, 2, 3, 4, 5});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 0;
  res = s->maxProfit({7, 6, 4, 3, 1});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
