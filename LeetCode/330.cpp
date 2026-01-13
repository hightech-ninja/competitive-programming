#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time:  O(ans + nums.length)
 * Space: O(1)
 */
class Solution {
public:
  int minPatches(vector<int> const &nums, int n) {
    int i = 0, ans = 0, len = (int)nums.size();
    int64_t hi = 0LL;
    while (hi < (int64_t)n) {
      if (i < len && nums[i] <= hi + 1) {
        hi += nums[i];
        i++;
      } else { // i >= len || nums[i] > hi + 1
        hi += hi + 1;
        ans++;
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

  want = 1;
  res = s->minPatches({1, 3}, 6);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 2;
  res = s->minPatches({1, 5, 10}, 20);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 0;
  res = s->minPatches({1}, 1);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
