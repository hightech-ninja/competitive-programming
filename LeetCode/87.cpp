#include <cassert>
#include <iostream>
#include <print>
#include <unordered_map>

using namespace std;

/*
 * Time: O(n^5), but can be improved to O(n^4)
 * Space: O(n^3)
 */
class Solution {
private:
  bool isScramble(string const &s1, string const &s2,
                  unordered_map<string, bool> &memo) {
    if (s1.size() == 1)
      return s1 == s2;
    if (s1 == s2)
      return true;

    string key = s1 + "#" + s2;
    if (auto it = memo.find(key); it != memo.end())
      return it->second;

    int n = (int)s1.size();

    bool ans = false;
    for (int i = 1; i < n; ++i) {
      if (isScramble(s1.substr(0, i), s2.substr(0, i), memo) &&
          isScramble(s1.substr(i), s2.substr(i), memo)) {
        ans = true;
        break;
      }
      if (isScramble(s1.substr(0, i), s2.substr(n - i), memo) &&
          isScramble(s1.substr(i), s2.substr(0, n - i), memo)) {
        ans = true;
        break;
      }
    }

    memo[key] = ans;
    return ans;
  }

public:
  bool isScramble(string const &s1, string const &s2) {
    unordered_map<string, bool> memo;
    return isScramble(s1, s2, memo);
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
  bool want, res;

  want = true;
  res = s->isScramble("great", "rgeat");
  assert(res == want);
  println("ok");

  want = false;
  res = s->isScramble("abcde", "caebd");
  assert(res == want);
  println("ok");

  want = true;
  res = s->isScramble("a", "a");
  assert(res == want);
  println("ok");

  want = true;
  res = s->isScramble("abcdefghijklmnopq", "efghijklmnopqcadb");
  assert(res == want);
  println("ok");

  return 0;
}
