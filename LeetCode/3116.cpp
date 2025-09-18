#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(2^n * log(k * max(coins)))
 * Space: O(n), because of recursive dfs
//*/
/*
 * Solution: Binary search on answer
 *  - fn(val) = |<= values| can make from coins;
 *  - fn(val) calcuated with inclusion-exclusion principle;
 *  - binary search to find first fn(val) >= k;
 */
class Solution {
private:
  int gcd(long long a, long long b) {
    long long c;
    while (a % b != 0) {
      c = b;
      b = a % b;
      a = c;
    }
    return b;
  }

  long long lcm(long long a, long long b) { return a * b / gcd(a, b); }

  void dfs(vector<int> const &coins, long long &ans, long long val,
           long long lcm, int idx, int sign) {
    int n = (int)coins.size();
    long long nextLCM;
    for (int i = idx; i < n; ++i) {
      nextLCM = this->lcm(lcm, coins[i]);
      if (nextLCM <= val) {
        ans += val / nextLCM * sign;
        dfs(coins, ans, val, nextLCM, i + 1, -sign);
      }
    }
  }

  long long countLessOrEqual(vector<int> const &coins, long long val) {
    long long count = 0LL;
    dfs(coins, count, val, 1LL, 0, 1);
    return count;
  }

  // [l, r) half-opened
  long long search(vector<int> const &coins, long long l, long long r,
                   long long target) {

    // Inv1: i <  l: count(i) < target
    // Inv2: i >= r: count(i) >= target
    while (l < r) {
      long long m = l + (r - l) / 2;
      long long count = countLessOrEqual(coins, m);
      if (count < target) {
        l = m + 1;
      } else { // count >= target
        r = m;
      }
    }
    return l;
  }

public:
  long long findKthSmallest(vector<int> &coins, int k) {
    sort(coins.begin(), coins.end());
    long long mx = 1LL * k * coins.back();
    return search(coins, 1, mx + 1, k);
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
  long long res, want;
  vector<int> input;

  want = 4;
  input = {1, 2, 4, 6};
  res = s->findKthSmallest(input, 4);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 9;
  input = {3, 6, 9};
  res = s->findKthSmallest(input, 3);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 12;
  input = {5, 2};
  res = s->findKthSmallest(input, 7);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 2 * 1e9;
  input = {1};
  res = s->findKthSmallest(input, 2 * 1e9);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 2000000000;
  input = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23};
  res = s->findKthSmallest(input, 2 * 1e9);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
