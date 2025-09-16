#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(n)
 * Space: O(n)
 * Solution:
 *  - there are N rotated intervals;
 *  - each element compared with N indicies [0...N);
 *  - nums[i] >= i will be true on (N - nums[i]) intervals total;
 *  - each element contributes +1 on two intervals for K:
 *      - before wrap: [0, dt), dt = max(0, i - nums[i] + 1);
 *      - after  wrap: [i + 1, i'), length = total - dt;
 *  - this can be solved via prefix sums;

            k:   0
         nums: [{2, 4, 1, 3, 0}, 2, 4, 1, 3, 0]
         idxs: [ 0, 1, 2, 3, 4|  -, -, -, -, -]
         ans : [ 0, 0, 1, 1, 1|  -, -, -, -, -]

            k:   1
         nums: [ 2,{4, 1, 3, 0| 2}, 4, 1, 3, 0]
         idxs: [ -, 0, 1, 2, 3| 4,  -, -, -, -]
         ans : [ -, 0, 1, 0, 1| 1,  -, -, -, -]

            k:   2
         nums: [ 2, 4,{1, 3, 0| 2, 4}, 1, 3, 0]
         idxs: [ -, -, 0, 1, 2| 3, 4,  -, -, -]
         ans : [ -, -, 0, 0, 1| 1, 1,  -, -, -]

            k:   3
         nums: [ 2, 4, 1,{3, 0| 2, 4, 1}, 3, 0]
         idxs: [ -, -, -, 0, 1| 2, 3, 4,  -, -]
         ans : [ -, -, -, 0, 1| 1, 0, 1,  -, -]

            k:   4
         nums: [ 2, 4, 1, 3,{0| 2, 4, 1, 3}, 0]
         idxs: [ -, -, -, -, 0| 1, 2, 3, 4,  -]
         ans : [ -, -, -, -, 1| 0, 0, 1, 1,  -]
 */
class Solution {
private:
  void inc(vector<int> &diff, int l, int r) {
    if (l == r)
      return;
    diff[l]++;
    diff[r]--;
  }

public:
  int bestRotation(vector<int> const &nums) {
    int n = (int)nums.size();
    vector<int> diff(n + 1, 0);
    int l, r, dt, total;
    for (int i = 0; i < n; ++i) {
      total = n - nums[i];
      dt = max(0, i - nums[i] + 1);
      inc(diff, 0, dt);
      inc(diff, i + 1, i + 1 + total - dt);
    }

    int psum = 0, best = -1, ans;
    for (int k = 0; k < n; ++k) {
      psum += diff[k];
      if (best < psum) {
        best = psum;
        ans = k;
      }
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
  int res, want;

  want = 0;
  res = s->bestRotation({2, 4, 1, 3, 0});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 3;
  res = s->bestRotation({2, 3, 1, 4, 0});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 0;
  res = s->bestRotation({1, 3, 0, 2, 4});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
