#include <cassert>
#include <iostream>
#include <print>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
  int trap(vector<int> const &height) {
    stack<int> st;
    int n = (int)height.size();
    int ans = 0;
    for (int r = 0; r < n; ++r) {
      while (!st.empty() && height[st.top()] <= height[r]) {
        int bottom = st.top();
        st.pop();
        if (st.empty()) {
          break;
        }
        int l = st.top();
        int lvl = min(height[l], height[r]);
        int width = r - l - 1;
        ans += width * (lvl - height[bottom]);
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
  int res, want;

  want = 6;
  res = s->trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1});
  println("res= {}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 9;
  res = s->trap({4, 2, 0, 3, 2, 5});
  println("res= {}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
