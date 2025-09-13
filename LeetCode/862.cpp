#include <cassert>
#include <deque>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(n)
 * Space: O(n)
 *
 * Solution: reframe to prefix sums, then run monotonic deque
 *
 * non-decreasing: pref(dq[front]) < ... < pref(dq[back]);
 * view: keep L candidates (concentrated in the tail);
 * dominance: i < j and pref[i] >= pref[j], then for any future r
 *            j is better than i, because (pref[r] - pref[j]) is
 *            at least as good as (pref[r] - pref[i]) and j closer;
 */
class Solution {
public:
  int shortestSubarray(vector<int> const &nums, int k) {
    int n = (int)nums.size();
    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) {
      pref[i + 1] = pref[i] + nums[i];
    }

    deque<int> dq;
    int ans = INT_MAX;
    for (int r = 0; r <= n; ++r) {
      while (!dq.empty() && pref[r] - pref[dq.front()] >= k) {
        ans = min(ans, r - dq.front());
        dq.pop_front();
      }
      while (!dq.empty() && pref[dq.back()] >= pref[r]) {
        dq.pop_back();
      }
      dq.push_back(r);
    }

    return ans == INT_MAX ? -1 : ans;
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
  int res, want;

  want = 1;
  res = s->shortestSubarray({1}, 1);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = -1;
  res = s->shortestSubarray({1, 2}, 4);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 3;
  res = s->shortestSubarray({2, -1, 2}, 3);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 1;
  res = s->shortestSubarray({1, 0, 1, 0, 1, 0, 1}, 1);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
