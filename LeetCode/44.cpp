#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(n+m)
 * Space: O(1)
 */
class Solution {
public:
  bool isMatch(string s, string p) {
    int n = (int)s.size(), i = 0;
    int m = (int)p.size(), j = 0;
    int star = -1, match = 0;
    while (i < n) {
      // s[0..i) matches p[0..j)

      if (j < m && (s[i] == p[j] || p[j] == '?')) {
        // last indices matches
        i++, j++;
      } else if (j < m && p[j] == '*') {
        // record last star and start tracking matching
        match = i;
        star = j++;
      } else if (star != -1) {
        j = star + 1;
        i = ++match;
      } else {
        return false;
      }
    }

    while (j < m && p[j] == '*')
      ++j;

    return j == m;
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
  res = s->isMatch("", "?");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = true;
  res = s->isMatch("", "*");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = false;
  res = s->isMatch("aa", "a");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = true;
  res = s->isMatch("aa", "*");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = false;
  res = s->isMatch("cb", "?a");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = true;
  res = s->isMatch("x", "?");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = false;
  res = s->isMatch("xx", "?");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
