#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(n)
 * Space: O(n)
 * Solution:
 *      DP + monotonic queue
 * Notes:
 *      Generalizable to m intervals;
 *      Time: O(nm)
 *      Space: O(nm)
 */
class Solution {
private:
  static const int intervals = 3;

  vector<int> psum;

  void init(vector<int> const &nums, int n) {
    psum.resize(n + 1, 0);
    for (int i = 0; i < n; ++i) {
      psum[i + 1] = psum[i] + nums[i];
    }
  }

  int sum(int l, int r) { return psum[r] - psum[l]; }

public:
  vector<int> maxSumOfThreeSubarrays(vector<int> const &nums, int k) {
    int n = (int)nums.size();
    init(nums, n);

    // dp[i][r] - max sum of (i + 1) intervals, with rightmost = [r - k, r)
    // dp[i][r] = sum[r - k, r) + max(dp[i-1][1...r-k+1])
    array<vector<int>, intervals> dp;
    dp.fill(vector<int>(n + 1, INT_MIN));

    // prev[i][r] - previous interval's R that contributes to the dp[i][r]
    array<vector<int>, intervals> prev;
    prev.fill(vector<int>(n + 1, -1));

    // deq[i] tracks max(dp[i][1..r-k+1])
    array<deque<int>, intervals - 1> deq;
    for (int r = k; r <= n; ++r) {
      int l = r - k;

      dp[0][r] = sum(l, r);
      prev[0][r] = r;

      for (int i = 0; i < (int)deq.size(); ++i) {
        if (!deq[i].empty()) {
          dp[i + 1][r] = dp[i][deq[i].front()] + sum(l, r);
          prev[i + 1][r] = deq[i].front();
        }
      }

      // [l2, r2) becomes available for future intervals
      int r2 = l + 1;
      int l2 = r2 - k;
      for (int i = 0; i < (int)deq.size(); ++i) {
        if (l2 >= i * k) {
          while (!deq[i].empty() && dp[i][deq[i].back()] < dp[i][r2]) {
            deq[i].pop_back();
          }
          deq[i].push_back(r2);
        }
      }
    }

    vector<int> ans(intervals);
    int last = intervals - 1;
    int lo = intervals * k;
    auto it = max_element(dp[last].begin() + lo, dp[last].end());
    int startR = (it - dp[last].begin());
    for (int i = intervals - 1, r = startR; i >= 0; --i) {
      ans[i] = r - k;
      r = prev[i][r];
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
  vector<int> res, want;

  want = {0, 3, 5};
  res = s->maxSumOfThreeSubarrays({1, 2, 1, 2, 6, 7, 5, 1}, 2);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {0, 2, 4};
  res = s->maxSumOfThreeSubarrays({1, 2, 1, 2, 1, 2, 1, 2, 1}, 2);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
