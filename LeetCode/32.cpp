#include <cassert>
#include <iostream>
#include <print>
#include <stack>

using namespace std;

/*
 * Time: O(n)
 * Space: O(n)
 * Solution:
 *  Think about standard "stack" solution for "is valid paranthesis" task.
 *  Let's modify it: when unmatched ")" reached it becomes new "guard".
 */
class Solution {
public:
  int longestValidParentheses(string s) {
    int n = (int)s.size();
    stack<int> st;
    st.push(-1);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i] == '(') {
        st.push(i);
        continue;
      }
      st.pop();
      if (st.empty()) {
        st.push(i);
      } else {
        ans = max(ans, i - st.top());
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

  want = 2;
  res = s->longestValidParentheses("()(()");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 0;
  res = s->longestValidParentheses(")(");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 2;
  res = s->longestValidParentheses("(()");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 4;
  res = s->longestValidParentheses(")()())");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 0;
  res = s->longestValidParentheses("))))");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 0;
  res = s->longestValidParentheses("((((");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 2;
  res = s->longestValidParentheses("())");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
