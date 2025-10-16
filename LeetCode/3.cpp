#include <cassert>
#include <iostream>
#include <print>
#include <unordered_map>

using namespace std;

/*
    Time: O(n)
    Space: O(n)
 */
class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    int n = (int)s.size();
    int ans = 0, l = 0;
    unordered_map<char, int> freqs;
    for (int r = 0; r < n; ++r) {
      if (freqs[s[r]] > 0) {
        while (l < r && s[l] != s[r]) {
          freqs[s[l]]--;
          ++l;
        }
        ++l;
      } else {
        freqs[s[r]]++;
      }
      ans = max(ans, r - l + 1);
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

  want = 3;
  res = s->lengthOfLongestSubstring("abcabcbb");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 1;
  res = s->lengthOfLongestSubstring("bbbbb");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
