#include <cassert>
#include <iostream>
#include <print>

using namespace std;

/*
 * Time: O((n+m)log(nm))
 * Space: O(1)
 * Solution: Binary search on answer
 *  - fn(val) = numbers in matrix <= val;
 *  - binary search on [1, n * m] to find first fn(val) >= k;
 */
class Solution {
private:
  int countLessEqual(int m, int n, int val) {
    int ans = 0, j = n;
    for (int i = 1; i <= m; ++i) {
      while (j >= 1 && i * j > val)
        j--;
      ans += j;
    }
    return ans;
  }

  // [l, r) - half-opened
  int search(int m, int n, int l, int r, int target) {
    // Inv1: i <  l: count(i) <  target
    // Inv2: i >= r: count(i) >= target
    while (l < r) {
      int mid = l + (r - l) / 2;
      int cnt = countLessEqual(m, n, mid);
      if (cnt < target) {
        l = mid + 1;
      } else { // cnt >= target
        r = mid;
      }
    }
    return l;
  }

public:
  int findKthNumber(int m, int n, int k) {
    if (m > n)
      swap(m, n);
    return search(m, n, 1, m * n + 1, k);
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
  res = s->findKthNumber(3, 3, 5);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 6;
  res = s->findKthNumber(2, 3, 6);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 9;
  res = s->findKthNumber(3, 3, 9);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 1;
  res = s->findKthNumber(3, 3, 1);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 6;
  res = s->findKthNumber(3, 3, 8);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
