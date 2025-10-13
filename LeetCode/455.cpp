#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(nlogn + mlogm)
 * Space: O(logn + logm)
 */
class Solution {
public:
  int findContentChildren(vector<int> &g, vector<int> &s) {
    sort(s.begin(), s.end());
    sort(g.begin(), g.end());

    int c = 0, ans = 0;
    int n = (int)g.size();
    int m = (int)s.size();

    for (int i = 0; i < n; ++i) {
      while (c < m && s[c] < g[i])
        c++;
      if (c < m) {
        ans++;
        c++;
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
  vector<int> gin{}, sin{};
  int want, res;

  gin = {1, 2, 3};
  sin = {1, 1};
  want = 1;
  res = s->findContentChildren(gin, sin);
  assert(res == want);
  println("ok");

  gin = {1, 2};
  sin = {1, 2, 3};
  want = 2;
  res = s->findContentChildren(gin, sin);
  assert(res == want);
  println("ok");

  return 0;
}
