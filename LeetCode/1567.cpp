#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(n)
 * Space: O(1)
 *
 * Thoughts:
 *  - need two states for fixed r;
 *  - max len for positive product ending at r - pos;
 *  - max len for negative product ending at r - neg;
 *
 * Try DP:
 *  - base: pos = neg = 0;
 *  - new number nums[r] = 0 -> pos = neg = 0;
 *  - nums[r] > 0 (positive) => pos++, neg++ (if had negatives);
 *  - nums[r] < 0 (negative) => pos++, neg++ (if had negatives) + swap roles;
 *  - ans = global max (pos);
 */
class Solution {
public:
  int getMaxLen(vector<int> const &nums) {
    int pos = 0, neg = 0;
    int best = 0;
    for (int r = 0; r < (int)nums.size(); ++r) {
      if (nums[r] == 0) {
        pos = neg = 0;
        continue;
      }
      if (nums[r] > 0) {
        pos = pos + 1;
        neg = (neg ? neg + 1 : 0);
      } else {
        int prevPos = pos;
        int prevNeg = neg;
        pos = (prevNeg ? prevNeg + 1 : 0);
        neg = prevPos + 1;
      }
      best = max(best, pos);
    }
    return best;
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

  want = 4;
  res = s->getMaxLen({1, -2, -3, 4});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 3;
  res = s->getMaxLen({0, 1, -2, -3, -4});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 2;
  res = s->getMaxLen({-1, -2, -3, 0, 1});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
