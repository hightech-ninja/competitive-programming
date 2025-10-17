#include <cassert>
#include <iostream>
#include <print>
#include <unordered_map>

using namespace std;

/*
    Time:
    Space:
 */
class Solution {
private:
  unordered_map<char, int> freqs(string const &t) {
    unordered_map<char, int> ans;
    for (char c : t) {
      ans[c]++;
    }
    return ans;
  }

public:
  string minWindow(string s, string t) {
    int pos = 0, length = INT_MAX;
    unordered_map<char, int> target = freqs(t);

    int deficit = (int)target.size();
    int l = 0, n = (int)s.size();
    unordered_map<char, int> freq;
    for (int r = 0; r < n; ++r) {
      freq[s[r]]++;
      if (target[s[r]] != 0 && freq[s[r]] == target[s[r]])
        deficit--;
      while (deficit == 0) {
        if (length > r - l + 1) {
          pos = l;
          length = r - l + 1;
        }
        freq[s[l]]--;
        if (target[s[l]] != 0 && freq[s[l]] < target[s[l]])
          deficit++;
        l++;
      }
    }
    if (length == INT_MAX) {
      return "";
    }
    return s.substr(pos, length);
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
  string res, want;

  want = "BANC";
  res = s->minWindow("ADOBECODEBANC", "ABC");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = "a";
  res = s->minWindow("a", "a");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = "";
  res = s->minWindow("a", "aa");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = "abbbbbcdd";
  res = s->minWindow("aaaaaaaaaaaabbbbbcdd", "abcdd");
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
