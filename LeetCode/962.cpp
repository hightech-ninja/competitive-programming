#include <cassert>
#include <iostream>
#include <print>
#include <stack>
#include <vector>

using namespace std;

/*
 * Time: O(n)
 * Space: O(n)
 *
 * Solution:
 *  1. Run left->right for-loop and build strictly decreasing stack, no pops;
 *  2. Those are candidates for L border;
 *  3. Run right->left for-loop and finilize R candidates;
 *  4. This time can pop, because of dominance:
 *      - Pop until stack.top() <= nums[r];
 *      - Any r' < r that is also >= stack.top() can't be answer;
 */
class Solution {
public:
  int maxWidthRamp(vector<int> const &nums) {
    int n = (int)nums.size();
    int ans = 0;
    stack<int> st;
    st.push(0);
    for (int l = 1; l < n; ++l) {
      if (nums[st.top()] > nums[l]) {
        st.push(l);
      }
    }
    for (int r = n - 1; r >= 0 && !st.empty(); --r) {
      while (!st.empty() && nums[st.top()] <= nums[r]) {
          int l = st.top(); st.pop();
          ans = max(ans, r - l);
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

  want = 4;
  res = s->maxWidthRamp({6, 0, 8, 2, 1, 5});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 7;
  res = s->maxWidthRamp({9, 8, 1, 0, 1, 9, 4, 0, 4, 1});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 4;
  res = s->maxWidthRamp({1, 1, 1, 1, 1});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 5;
  res = s->maxWidthRamp({3, 2, 1, 1, 2, 3});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 5;
  res = s->maxWidthRamp({1, 2, 3, 3, 2, 1});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
