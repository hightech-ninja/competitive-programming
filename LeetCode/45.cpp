#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(n)
 * Space: O(1)
 */
class Solution {
public:
  int jump(vector<int> const &nums) {
    int n = (int)nums.size();
    int target = n - 1;
    int ans = 0;
    int max_jump = 0;
    int must_jump_until = 0;
    for (int i = 0; i < target; ++i) {
      max_jump = max(max_jump, i + nums[i]);
      if (must_jump_until == i) {
        ++ans;
        must_jump_until = max_jump;
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
  int want, res;

  want = 2;
  res = s->jump({2, 3, 1, 1, 4});
  assert(res == want);
  println("ok");

  want = 2;
  res = s->jump({2, 3, 0, 1, 4});
  assert(res == want);
  println("ok");

  want = 0;
  res = s->jump({0});
  assert(res == want);
  println("ok");

  want = 3;
  res = s->jump({1, 1, 1, 1});
  assert(res == want);
  println("ok");

  want = 2;
  res = s->jump({2, 2, 2, 2, 2});
  assert(res == want);
  println("ok");

  want = 4;
  res = s->jump({1, 2, 1, 2, 1, 2, 1});
  assert(res == want);
  println("ok");

  return 0;
}
