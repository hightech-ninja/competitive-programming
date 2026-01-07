#include <cassert>
#include <iostream>
#include <print>

using namespace std;

/*
 * Time: O(log_2(n) * log_5(n)) = O(log^2(n))
 * Space: O(1)
 *
 * Solution:
 *  1. zero appears only when 2 and 5 multipliers match in factorization
 *  2. Let n! = 2^x * 5^y * rest (factorization)
 *  3. Then x >= y, f(n) = y
 *  4. Let g(n) = y - meaning power of 5 in factorization of n!
 *  5. g(n) = n/5 + n/5^2 + n/5^3 + ...
 *  5. The answer is either 0 or 5:
 *      - zero if n doesn't exists: g(n) = k
 *      - otherwise, n exists: g(n) = k, but g(n+5) > g(n)
 *  6. g(n) monotonically non-decreasing function
 *  7. Run binary search on n to find lowest n: g(n) >= k
 *  8. Decide final answer based on (5)
 */
class Solution {
private:
  using int64 = long long;

  static const int64 max_k = 1'000'000'000LL;

  // g(n)
  int64 getFiveFactor(int64 n) {
    int64 ans = 0LL;
    while (n > 0LL) {
      ans += n / 5LL;
      n /= 5LL;
    }
    return ans;
  }

  int64 find(int k, int64 l, int64 r) {
    // Inv1: any n < l => g(n) <  k
    // Inv2: any n >= r => g(n) >= k

    while (l < r) {
      int64 n = l + (r - l) / 2;
      if (getFiveFactor(n) >= k) {
        r = n;
      } else {
        l = n + 1;
      }
    }
    // l == r
    return l;
  }

public:
  int preimageSizeFZF(int k) {
    int64 n = find(k, 0, 5LL * max_k);
    return getFiveFactor(n) == k ? 5 : 0;
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

  want = 5;
  res = s->preimageSizeFZF(0);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 0;
  res = s->preimageSizeFZF(5);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 5;
  res = s->preimageSizeFZF(3);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 5;
  res = s->preimageSizeFZF(1'000'000'000);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
