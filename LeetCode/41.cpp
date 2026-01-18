#include <algorithm>
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
private:
  void markSeen(vector<int> &nums, int i) {
    int val = abs(nums[i]);
    if (nums[val - 1] > 0)
      nums[val - 1] *= -1;
  }
  bool isSeen(vector<int> &nums, int val) { return nums[val - 1] < 0; }

public:
  int firstMissingPositive(vector<int> &nums) {
    if (int cnt = count(nums.begin(), nums.end(), 1); cnt == 0)
      return 1;

    int n = (int)nums.size();
    for (int i = 0; i < n; ++i) {
      if (nums[i] > 0 && nums[i] <= n)
        continue;
      nums[i] = 1;
    }

    for (int i = 0; i < n; ++i) {
      markSeen(nums, i);
    }
    for (int x = 1; x <= n; ++x) {
      if (!isSeen(nums, x))
        return x;
    }
    return n + 1;
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

  vector<int> nums;
  int res, want;

  nums = {1, 2, 0};
  want = 3;
  res = s->firstMissingPositive(nums);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  nums = {3, 4, -1, 1};
  want = 2;
  res = s->firstMissingPositive(nums);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  nums = {7, 8, 9, 11, 12};
  want = 1;
  res = s->firstMissingPositive(nums);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  nums = {5, 4, 3, 2, 1};
  want = 6;
  res = s->firstMissingPositive(nums);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  nums = {1, 3, 5, 2, 4, 6};
  want = 7;
  res = s->firstMissingPositive(nums);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
