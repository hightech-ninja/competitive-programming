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
 *  - element i can see NGE(i);
 *  - element i can't see after NGE(i);
 *  - notice that PGE(i) always can see i'th element;
 */
class Solution {
public:
  vector<int> canSeePersonsCount(vector<int> const &heights) {
    int n = (int)heights.size();
    vector<int> st;
    st.reserve(n);

    vector<int> ans(n, 0);
    for (int r = 0; r < n; ++r) {
      while (!st.empty() && heights[st.back()] < heights[r]) {
          // st.back() can see r, can't see after r
          ans[st.back()]++; st.pop_back();
          if (!st.empty()) {
              // new st.back() can see prev st.back(), maybe more
              ans[st.back()]++;
          }
      }
      st.push_back(r);
    }

    // finlize survivors: st[i] can see st[i+1]
    n = (int)st.size() - 1;
    for (int i = 0; i < n; ++i) {
      ans[st[i]]++;
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

  want = {3, 1, 2, 1, 1, 0};
  res = s->canSeePersonsCount({10, 6, 8, 5, 11, 9});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {4, 1, 1, 1, 0};
  res = s->canSeePersonsCount({5, 1, 2, 3, 10});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {1, 1, 1, 0};
  res = s->canSeePersonsCount({1, 2, 3, 4});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {1, 1, 1, 0};
  res = s->canSeePersonsCount({4, 3, 2, 1});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {4, 1, 1, 1, 0};
  res = s->canSeePersonsCount({5, 1, 2, 3, 4});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {2, 2, 2, 1, 0};
  res = s->canSeePersonsCount({5, 3, 2, 1, 4});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
