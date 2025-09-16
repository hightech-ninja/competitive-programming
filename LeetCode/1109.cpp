#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(n)
 * Space: O(n)
 * Solution:
 *  - each interval contributes: +X on [L, R];
 *  - can track step-function deltas for each [L, R];
 *  - actual value at X = deltas prefix sum [0, X];
 */
class Solution {
public:
  vector<int> corpFlightBookings(vector<vector<int>> const &bookings, int n) {
    vector<int> diff(n + 1, 0);
    int l, r, count;
    int m = (int)bookings.size();
    for (int i = 0; i < m; ++i) {
      // [l, r) half-opened, 0-indexed
      l = bookings[i][0] - 1;
      r = bookings[i][1];
      count = bookings[i][2];
      diff[l] += count;
      diff[r] -= count;
    }

    // convert to actual values via prefix sums
    for (int i = 1; i < n; ++i)
      diff[i] += diff[i - 1];

    diff.resize(n);
    return diff;
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

  want = {10, 55, 45, 25, 25};
  res = s->corpFlightBookings({{1, 2, 10}, {2, 3, 20}, {2, 5, 25}}, 5);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {10, 25};
  res = s->corpFlightBookings({{1, 2, 10}, {2, 2, 15}}, 2);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
