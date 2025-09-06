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
 *      find next strictly greater element, but save distance
 *      rather then index -> non-icreasing monotonic stack
 */
class Solution {
public:
  vector<int> dailyTemperatures(vector<int> const &temperatures) {
    /*
        Dry-run:
          t: [73, 74, 75,   71,     69,   72, 76,   73]
        ans: [ 1,  1,  4,    2,      1,    1,  0,    0]
         st: [0]  [1] [2] [2,3] [2,3,4] [2,5] [6] [6,7]
          r:  0    1   2     3       4     5   6     7
     */
    int n = (int)temperatures.size();
    vector<int> ans(n, 0);
    stack<int> st;
    for (int r = 0; r < n; ++r) {
      while (!st.empty() && temperatures[st.top()] < temperatures[r]) {
        int l = st.top();
        st.pop();
        ans[l] = r - l;
      }
      st.push(r);
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
  vector<int> res, want;

  want = {1, 1, 4, 2, 1, 1, 0, 0};
  res = s->dailyTemperatures({73, 74, 75, 71, 69, 72, 76, 73});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {1, 1, 1, 0};
  res = s->dailyTemperatures({30, 40, 50, 60});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {1, 1, 0};
  res = s->dailyTemperatures({30, 60, 90});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
