#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <print>
#include <string>

using namespace std;

/*
 * Time: O(logn) with max_len^2 hidden constant
 * Space: O(1)
 * Solution:
 *  - So k always exists: worst case k = n - 1;
 *  - Let's say n base k has length m: n=k^0+...k^(m-1)
 *  - N is fixed, so higher m => lower k;
 *  - From the task limits => m <= 60
 *  - Bruteforce m from [60..2]
 *  - For fixed m you can run bin-search on k
 *  - Search for first k: n <= k^0+...+k^(m-1)
 *  - First equality means lowest answer
 */
class Solution {
private:
  using uint64 = unsigned long long;

  // max length of n base k
  static const int max_length = 60;

  bool check(uint64 n, uint64 k, int m) {
    uint64 nn = 0ULL;
    uint64 sum = 1ULL;
    for (int i = 0; i < m; ++i) {
      nn += sum;
      sum *= k;
    }
    return nn == n;
  }

  uint64 findK(uint64 n, int m, uint64 l, uint64 r) {
    // Inv1: k <  l => n >  k_0 + ... + k^(m-1)
    // Inv2: k >= r => n <= k_0 + ... + k^(m-1)
    while (l < r) {
      uint64 k = l + (r - l) / 2ULL;
      uint64 sum = 1ULL, nn = 0ULL;
      for (int i = 0; i < m; ++i) {
        nn += sum;
        sum *= k;
      }
      if (n <= nn) {
        r = k;
      } else {
        l = k + 1;
      }
    }
    // l == r
    return l;
  }

public:
  string smallestGoodBase(string n) {
    uint64 nn = stoull(n);
    for (int m = max_length; m > 1; --m) {
      // Formula is good, but doubles has ~hundreds error rate
      // for the task limits (n <= 10^18), so this code is fragile.
      // And it increases with lower m.
      uint64 max_k = min(nn, uint64(floor(pow(nn, 1.0 / (m - 1.0)))) + 1);
      // To pass the task, I used the simplest hack: we know
      // the exact upper limit for m=2. Better solution would
      // be to use integer_root(nn, m - 1) using binary search.
      if (m == 2) {
        max_k = nn - 1;
      }
      uint64 k = findK(nn, m, 2ULL, max_k);
      // println("{} <= {}x[1...1]_{}\n", n, m, k);
      if (check(nn, k, m)) {
        return to_string(k);
      }
    }
    return "unreachable";
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

  res = s->smallestGoodBase("13");
  want = "3";
  println("res={}; want={}", res, want);
  assert(res == want);

  res = s->smallestGoodBase("4681");
  want = "8";
  println("res={}; want={}", res, want);
  assert(res == want);

  res = s->smallestGoodBase("1000000000000000000");
  want = "999999999999999999";
  println("res={}; want={}", res, want);
  assert(res == want);

  res = s->smallestGoodBase("3");
  want = "2";
  println("res={}; want={}", res, want);
  assert(res == want);

  res = s->smallestGoodBase("727004545306745403");
  want = "727004545306745402";
  println("res={}; want={}", res, want);
  assert(res == want);
  return 0;
}
