#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <print>

using namespace std;

/*
 * Time: O(log n) - for unbounded n, O(1) for LeetCode constraints
 * Space: O(1)
 */
class Solution {
private:
  static const int maxPow = 31; // signed int (-2^31, 2^31]
  static const int digits = 10;

  array<int, digits> getFreqs(int n) {
    array<int, digits> freqs{};
    while (n > 0) {
      int digit = n % 10;
      n /= 10;
      freqs[digit]++;
    }
    return freqs;
  }

public:
  bool reorderedPowerOf2(int n) {
    array<int, maxPow> pows{1};
    for (int i = 1; i < maxPow; ++i) {
      pows[i] = pows[i - 1] * 2;
    }

    array<array<int, digits>, maxPow> freqs;
    for (int i = 0; i < maxPow; ++i) {
      freqs[i] = getFreqs(pows[i]);
    }

    auto target = getFreqs(n);
    auto it = find(freqs.begin(), freqs.end(), target);
    return it != freqs.end();
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
  bool res, want;

  want = true;
  res = s->reorderedPowerOf2(1);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = false;
  res = s->reorderedPowerOf2(10);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = true;
  res = s->reorderedPowerOf2(1240);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
