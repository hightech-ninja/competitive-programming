#include <cassert>
#include <iostream>
#include <map>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(M * N)
 * Space: O(M * N)
 */
class Solution {
private:
  bool ans(string const &s, string const &p, int i, int j,
           map<pair<int, int>, bool> &memo) {
    if (j == 0)
      return i == 0;
    if (memo.contains({i, j}))
      return memo[{i, j}];
    bool res = false;
    if (i >= 1 && (s[i - 1] == p[j - 1] || p[j - 1] == '.')) {
      res = ans(s, p, i - 1, j - 1, memo);
    } else if (j >= 2 && p[j - 2] == '.' && p[j - 1] == '*') {
      for (int ii = 0; ii <= i; ++ii) {
        if (ans(s, p, ii, j - 2, memo)) {
          res = true;
          break;
        }
      }
    } else if (j >= 2 && p[j - 1] == '*') {
      char sym = p[j - 2];
      int start = i; // 1-based
      while (start > 0 && s[start - 1] == sym)
        --start;
      for (int ii = start; ii <= i; ++ii) {
        if (ans(s, p, ii, j - 2, memo)) {
          res = true;
          break;
        }
      }
    }

    memo[{i, j}] = res;
    return res;
  }

public:
  bool isMatch(string s, string p) {
    map<pair<int, int>, bool> memo;
    return ans(s, p, s.size(), p.size(), memo);
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
  vector<int> nums, indices;
  int res, want;

  want = false;
  res = s->isMatch("aa", "a");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = true;
  res = s->isMatch("aa", "a*");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = false;
  res = s->isMatch("ab", "a");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = true;
  res = s->isMatch("aa", ".*");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = false;
  res = s->isMatch("cb", ".a");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = true;
  res = s->isMatch("x", ".");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = false;
  res = s->isMatch("xx", ".");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = true;
  res = s->isMatch("", "x*");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = true;
  res = s->isMatch("", ".*");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = true;
  res = s->isMatch("aa", "a*a");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
