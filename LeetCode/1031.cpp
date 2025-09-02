#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
    Time: O(n)
    Space: O(1)
 */
class Solution {
private:
  int fixedOrder(vector<int> const &nums, int L,
                                   int R) {
    int n = (int)nums.size();
    long long sumL = 0, sumR = 0;
    long long bestL = LLONG_MIN;
    long long ans = LLONG_MIN;
    for (int r = 0; r < n; ++r) {
      int m = r - R; // end of L window
      int l = m - L; // start of L window (excluding)

      // Restore invariants:
      // 1. sumR = sum nums(m...r]
      // 2. sumL = sum nums(l...m]
      if (m >= 0) {
        sumR -= nums[m];
        sumL += nums[m];
      }
      sumR += nums[r];
      if (l >= 0)
        sumL -= nums[l];

      // Update answer with candidate:
      if (r >= L + R - 1) {
        bestL = max(bestL, sumL);
        ans = max(ans, bestL + sumR);
      }
    }
    return (int)ans;
  }

public:
  int maxSumTwoNoOverlap(vector<int> const &nums, int firstLen, int secondLen) {
    return max(fixedOrder(nums, firstLen, secondLen),
               fixedOrder(nums, secondLen, firstLen));
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

  want = 20;
  res = s->maxSumTwoNoOverlap({0, 6, 5, 2, 2, 5, 1, 9, 4}, 1, 2);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 29;
  res = s->maxSumTwoNoOverlap({3, 8, 1, 3, 2, 1, 8, 9, 0}, 3, 2);
  assert(res == want);
  println("ok");

  want = 31;
  res = s->maxSumTwoNoOverlap({2, 1, 5, 6, 0, 9, 5, 0, 3, 8}, 4, 3);
  assert(res == want);
  println("ok");

  return 0;
}
