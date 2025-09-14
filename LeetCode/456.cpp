#include <cassert>
#include <iostream>
#include <print>
#include <stack>
#include <vector>

using namespace std;

class Solution2 {
public:
  bool find132pattern(vector<int> const &nums) {
    int n = (int)nums.size();
    if (n < 3)
      return false;

    // Non-increasing
    // Indicies: st[0] > ... > st[top] (Right -> Left);
    // Values:   nums[st[0]] <= ... <= nums[st[top]];
    // View:     keeps j candidates, tracks largest k candidate during pops;
    stack<int> st;

    int j; // helper for more clear invariant
    int numsk = INT_MIN;
    for (int i = n - 1; i >= 0; --i) {
      if (nums[i] < numsk)
        return true;
      j = i;
      while (!st.empty() && nums[j] > nums[st.top()]) {
        numsk = nums[st.top()];
        st.pop();
      }
      st.push(j);
    }
    return false;
  }
};

/*
 * Time: O(n)
 * Space: O(n)
 */
class Solution1 {
public:
  bool find132pattern(vector<int> const &nums) {
    int n = (int)nums.size();
    if (n < 3)
      return false;

    // Decreasing: nums[st[0].second] > ... > nums[st[top].second];
    // Data: <prefix min, PSG>, maps to <nums[i], j> candidates;
    stack<pair<int, int>> st;
    int prefMin = INT_MAX;
    for (int k = 0; k < n; ++k) {
      while (!st.empty() && nums[st.top().second] <= nums[k]) {
        st.pop();
      }
      int numsi = (st.empty() ? INT_MAX : st.top().first);
      int j = (st.empty() ? -1 : st.top().second);
      if (j > 0 && numsi < nums[k]) {
        return true;
      }

      st.push({prefMin, k});
      prefMin = min(prefMin, nums[k]);
    }
    return false;
  }
};

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

int main() {
  auto s = new Solution2;
  bool res, want;

  want = false;
  res = s->find132pattern({1, 2, 3, 4});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = true;
  res = s->find132pattern({3, 1, 4, 2});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 3;
  res = s->find132pattern({-1, 3, 2, 0});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = true;
  res = s->find132pattern({1, 2, 3, 2});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = true;
  res = s->find132pattern({3, 5, 3, 4});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
