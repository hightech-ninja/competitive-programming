#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 *  Time: O(n(logn + logm)), m = max - min = max delta
 *  Space: O(1)
 */
class Solution {
private:
  int countLessOrEqual(vector<int> const &nums, int dist) {
    int n = (int)nums.size();
    int l = 0, ans = 0;
    for (int r = 0; r < n; ++r) {
      while (l < r && nums[r] - nums[l] > dist)
        l++;
      ans += (r - l);
    }
    return ans;
  }
  int search(vector<int> const &nums, int l, int r, int target) {
    int it = 0;
    // Inv1: i <  l: cnt < target
    // Inv2: i >= r: cnt >= target
    while (l < r) {
      int m = l + (r - l) / 2;
      int cnt = countLessOrEqual(nums, m);
      if (cnt < target) {
        l = m + 1;
      } else { // cnt >= target
        r = m;
      }
    }
    return l;
  }

public:
  int smallestDistancePair(vector<int> &nums, int k) {
    sort(nums.begin(), nums.end());
    int l = 0, r = nums.back() - nums.front() + 1;
    return search(nums, l, r, k);
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
  vector<int> input;
  int res, want;

  want = 0;
  input = {1, 3, 1};
  res = s->smallestDistancePair(input, 1);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 0;
  input = {1, 1, 1};
  res = s->smallestDistancePair(input, 2);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 5;
  input = {1, 6, 1};
  res = s->smallestDistancePair(input, 3);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
