#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(k * n^3)
 * Space: O(k * n^2)
 */
class Solution {
private:
  static constexpr int INF = 1e9;

  vector<vector<vector<int>>> memo;
  vector<int> pref;
  int k;

  void init(vector<int> const &stones, int K) {
    k = K;
    int n = (int)stones.size();
    pref.assign(n + 1, 0);
    for (int i = 0; i < n; ++i)
      pref[i + 1] = pref[i] + stones[i];
    memo.assign(n + 1, vector<vector<int>>(n + 1, vector<int>(k + 1, -1)));
  }

  int sum(int l, int r) { return pref[r] - pref[l]; }

  int mergeStones(vector<int> const &stones, int l, int r, int m) {
    int len = r - l;
    if (len == 1)
      return m == 1 ? 0 : INF;
    if ((len - m) % (k - 1) != 0)
      return INF;
    if (m == 1) {
      int constK = mergeStones(stones, l, r, k);
      return constK == INF ? INF : constK + sum(l, r);
    }

    if (memo[l][r][m] != -1)
      return memo[l][r][m];
    int ans = INF;
    for (int p = l + 1; p < r; p += (k - 1)) {
      int left = mergeStones(stones, l, p, 1);
      if (left == INF)
        continue;
      int right = mergeStones(stones, p, r, m - 1);
      if (right == INF)
        continue;
      ans = min(ans, left + right);
    }
    memo[l][r][m] = ans;
    return ans;
  }

public:
  int mergeStones(vector<int> const &stones, int k) {
    int n = (int)stones.size();
    init(stones, k);
    int res = mergeStones(stones, 0, n, 1);
    return res == INF ? -1 : res;
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

  want = 20;
  res = s->mergeStones({3, 2, 4, 1}, 2);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = -1;
  res = s->mergeStones({3, 2, 4, 1}, 3);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 25;
  res = s->mergeStones({3, 5, 1, 2, 6}, 3);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
