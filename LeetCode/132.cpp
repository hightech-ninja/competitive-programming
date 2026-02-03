#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(n^4)
 * Space: O(n^2)
 */
class Solution {
private:
  static constexpr int INF = 1e9;

  vector<vector<int>> memo;

  bool isPalindrom(string const &s, int l, int r) {
    while (l < r) {
      if (s[l++] != s[--r])
        return false;
    }
    return true;
  }
  int minCut(string const &s, int l, int r) {
    int len = r - l;
    if (len <= 1 || isPalindrom(s, l, r))
      return 0;
    int &ans = memo[l][r];
    if (ans != INF)
      return ans;
    for (int i = l + 1; i < r; ++i)
      if (isPalindrom(s, l, i))
        ans = min(ans, 1 + minCut(s, i, r));
    return ans;
  }

public:
  int minCut(string const &s) {
    int n = (int)s.size();
    memo.assign(n + 1, vector<int>(n + 1, INF));
    return minCut(s, 0, n);
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
  int want, res;
  string input;

  input = "bb";
  want = 0;
  res = s->minCut(input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  input = "aab";
  want = 1;
  res = s->minCut(input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  input = "a";
  want = 0;
  res = s->minCut(input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  input = "ab";
  want = 1;
  res = s->minCut(input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
