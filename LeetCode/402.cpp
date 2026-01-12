#include <cassert>
#include <iostream>
#include <print>
#include <string>

using namespace std;

/*
 * Time: O(n + k)
 * Space: O(n)
 */
class Solution {
public:
  string removeKdigits(string num, int k) {
    int n = (int)num.size();
    string stack; // values: non-decreasing
    stack.reserve(n);
    for (int r = 0; r < n; ++r) {
      while (k > 0 && !stack.empty() && stack.back() > num[r]) {
        stack.pop_back();
        k--;
      }
      stack.push_back(num[r]);
    }
    while (k > 0 && !stack.empty()) {
      stack.pop_back();
      k--;
    }

    // skip leading zeros
    int s = (int)stack.size();
    int first = 0;
    while (first < s && stack[first] == '0') {
      ++first;
    }

    if (first == s) {
      return "0";
    }

    return stack.substr(first);
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

  want = "1219";
  res = s->removeKdigits("1432219", 3);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = "200";
  res = s->removeKdigits("10200", 1);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = "0";
  res = s->removeKdigits("10", 2);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
