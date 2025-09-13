#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(n)
 * Space: O(n)
 *
 * Solution:
 *  1. Calculat each wizard's personal contribution
 *  2. For each wizard find intervals it contributes to:
 *      - (previous-less-equal; next-strictly-greater) -> min is that wizard
 *  3. Let's say, we have (l, r) interval for m:
 *      - calculate sum of intervals from (l, r) through m;
 *      - each interval consist of left (l, m) and right (m, r) parts;
 *      - left parts contributes as (suffix sums on (l, m)) * (r - m);
 *      - right parts contributes as (prefix sums on (m, r) * (m - l));
 */
class Solution {
private:
  static const long long modulo = 1e9 + 7;

  vector<long long> pref, suf;
  vector<long long> ppref, ssuf;

  void init(vector<int> const &strength, int n) {
    pref.resize(n + 1, 0);
    ppref.resize(n + 1, 0);
    suf.resize(n + 1, 0);
    ssuf.resize(n + 1, 0);

    for (int i = 0, j; i < n; ++i) {
      j = n - i - 1;
      pref[i + 1] = (pref[i] + strength[i]);
      suf[j] = (suf[j + 1] + strength[j]);
    }
    for (int i = 1, j; i <= n; ++i) {
      j = n - i;
      ppref[i] = (ppref[i - 1] + pref[i]);
      ssuf[j] = (ssuf[j + 1] + suf[j]);
    }
  }

  long long all_prefs_sum(int l, int r) {
    return (ppref[r] - ppref[l] - 1LL * (r - l) * pref[l]) % modulo;
  }
  long long all_sufs_sum(int l, int r) {
    return (ssuf[l] - ssuf[r] - 1LL * (r - l) * suf[r]) % modulo;
  }

  long long sum_interval_through_mid(int l, int r, int m, int val) {
    return ((all_sufs_sum(l + 1, m) * (r - m) % modulo) +
            (all_prefs_sum(m + 1, r) * (m - l) % modulo) +
            (1LL * val * (r - m) * (m - l)) % modulo) %
           modulo;
  }

public:
  int totalStrength(vector<int> const &strength) {
    int n = (int)strength.size();
    init(strength, n);

    long long ans = 0LL, sub = 0LL;

    // non-decreasing: st[0] <= ... <= st[top]
    // track (previous less or equal) and (next strictly less)
    //
    // NSL  view: stack keeps elements that still waits for NSL;
    // PLEQ view: stack keeps "live" elements (PLE(st[i]) = st[i-1]), that are
    //      finilized when less element found;
    vector<int> st;
    st.reserve(n);
    for (int r = 0; r < n; ++r) {
      while (!st.empty() && strength[st.back()] > strength[r]) {
        // NSL(m) = r, PLEQ(m) = l
        int m = st.back();
        st.pop_back();
        int l = (st.empty() ? -1 : st.back());
        sub = strength[m] * sum_interval_through_mid(l, r, m, strength[m]);
        ans += sub % modulo;
        ans %= modulo;
      }
      st.push_back(r);
    }

    // finilize survivors
    int nn = (int)st.size();
    for (int i = 0; i < nn; ++i) {
      int m = st[i], r = n;
      int l = (i > 0 ? st[i - 1] : -1);
      sub = strength[m] * sum_interval_through_mid(l, r, m, strength[m]);
      ans += sub % modulo;
      ans %= modulo;
    }

    return (int)ans;
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

  want = 44;
  res = s->totalStrength({1, 3, 1, 2});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 213;
  res = s->totalStrength({5, 4, 6});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
