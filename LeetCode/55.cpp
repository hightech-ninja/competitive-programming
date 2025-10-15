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
  bool canJump(vector<int> const &nums) {
    int n = (int)nums.size();
    int max_dist = 0;
    for (int i = 0; i < n; ++i) {
      if (max_dist < i) {
        return false;
      }
      max_dist = max(max_dist, i + nums[i]);
    }

    return max_dist + 1 >= n;
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
  bool want, res;

  want = true;
  res = s->canJump({2, 3, 1, 1, 4});
  assert(res == want);
  println("ok");

  want = false;
  res = s->canJump({3, 2, 1, 0, 4});
  assert(res == want);
  println("ok");

  want = true;
  res = s->canJump({0});
  assert(res == want);
  println("ok");

  want = false;
  res = s->canJump({0, 1});
  assert(res == want);
  println("ok");

  want = true;
  res = s->canJump({1, 1, 1, 1});
  assert(res == want);
  println("ok");

  return 0;
}
