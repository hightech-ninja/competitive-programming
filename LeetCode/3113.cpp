#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <unordered_map>
#include <vector>

using namespace std;

/*
 * Time: O(nlogn)
 * Space: O(n)
 *
 * Solution:
 *  - monotonick stack to find previous strictly greater
 *  - pre-computed list of increasing positions for each value
      with binary-search to find count of nums[r] on (prev(r), r]
      interval.
 */
class Solution {
public:
  long long numberOfSubarrays(vector<int> &nums) {
    int n = (int)nums.size();
    vector<int> prev(n, -1); // previous strictly greater

    // indices: stack[0] < ...  < stack[top]
    // values :  nums[^] > ...  >    nums[^]
    vector<int> stack;
    stack.reserve(n);

    unordered_map<int, vector<int>> pos;
    for (int r = 0; r < n; ++r) {
      while (!stack.empty() && nums[stack.back()] <= nums[r]) {
        stack.pop_back();
      }
      // nums[stack[top]] > nums[r]
      int l = (stack.empty() ? -1 : stack.back());
      prev[r] = l;
      stack.push_back(r);
      pos[nums[r]].push_back(r);
    }

    long long ans = 0LL;
    for (int r = 0; r < n; ++r) {
      // # of  val on [l, r] contribues to answer
      int val = nums[r];
      int l = prev[r] + 1;
      // sorted val's indices
      vector<int> const &_pos = pos[val];
      int to = (int)(upper_bound(_pos.begin(), _pos.end(), r) -
                     _pos.begin()); // first >  r
      int from = (int)(lower_bound(_pos.begin(), _pos.end(), l) -
                       _pos.begin()); // first >= l

      ans += to - from;
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
  vector<int> nums;
  int res, want;

  nums = {1, 4, 3, 3, 2};
  want = 6;
  res = s->numberOfSubarrays(nums);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  nums = {3, 3, 3};
  want = 6;
  res = s->numberOfSubarrays(nums);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  nums = {1};
  want = 1;
  res = s->numberOfSubarrays(nums);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
