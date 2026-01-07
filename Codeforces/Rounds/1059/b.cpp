#include <algorithm>
#include <iostream>
#include <print>
#include <string>

using namespace std;

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    int n;
    string s;
    cin >> n >> s;

    bool palindrom = true;
    for (int i = 0; i < (n + 1) / 2; ++i) {
      if (s[i] != s[n - i - 1]) {
        palindrom = false;
        break;
      }
    }
    if (palindrom) {
      println("0\n");
      continue;
    }

    int zeros = 0, ones = 0;
    for (char c : s) {
      if (c == '0')
        ++zeros;
      else if (c == '1')
        ++ones;
    }

    int k = min(zeros, ones);
    int target = (zeros < ones ? '0' : '1');
    println("{}", k);
    for (int i = 0; i < n; ++i)
      if (s[i] == target)
        print("{} ", i+1);
    println();
  }
  return 0;
}

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();
