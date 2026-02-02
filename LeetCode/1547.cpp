#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(m^3)
 * Space: O(m^2)
 */
class Solution {
private:
  static constexpr int INF = 1e9;

  vector<vector<int>> memo;

  int minCost(vector<int> const &cuts, int l, int r) {
    if (l + 1 >= r)
      return 0;
    int &ans = memo[l][r];
    if (ans != INF)
      return ans;
    for (int p = l + 1; p < r; ++p) {
      int left = minCost(cuts, l, p);
      int right = minCost(cuts, p, r);
      ans = min(ans, left + right + cuts[r] - cuts[l]);
    }
    return ans;
  }

public:
  int minCost(int n, vector<int> &cuts) {
    cuts.insert(cuts.begin(), 0);
    cuts.push_back(n);
    sort(cuts.begin(), cuts.end());
    int m = (int)cuts.size();
    memo.assign(m, vector<int>(m, INF));
    return minCost(cuts, 0, m - 1);
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
  vector<int> input;
  int want, res;

  input = {1, 3, 4, 5};
  want = 16;
  res = s->minCost(7, input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  input = {5, 6, 1, 4, 2};
  want = 22;
  res = s->minCost(9, input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
