#include <cassert>
#include <iostream>
#include <numeric>
#include <print>
#include <vector>

using namespace std;

/*
    Time: O(n)
    Space: O(1)

    Solution: Geometry view
        - answer is max subarray sum without circling - max Kadane's;
        - or sum of all - min subarray sum (with circling) - min Kadane's;
        - corner case: all negatives


 */
class Solution1 {
private:
  int maxSubarraySum(vector<int> const &nums) {
      int n = (int)nums.size();
      long long best = 0LL;
      long long bestSoFar = LLONG_MIN;
      for (int r = 0; r < n; ++r) {
          best = max(best + nums[r], (long long)nums[r]);
          bestSoFar = max(bestSoFar, best);
      }
      return (int)bestSoFar;
  }
  int minSubarraySum(vector<int> const &nums) {
      int n = (int)nums.size();
      long long best = 0LL;
      long long bestSoFar = LLONG_MAX;
      for (int r = 0; r < n; ++r) {
          best = min(best + nums[r], (long long)nums[r]);
          bestSoFar = min(bestSoFar, best);
      }
      return (int)bestSoFar;
  }

public:
  int maxSubarraySumCircular(vector<int> const &nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    int ansRegular = maxSubarraySum(nums);
    int ansCircular = sum - minSubarraySum(nums);
    if (ansRegular < 0) {
        return ansRegular;
    }
    return max(ansRegular, ansCircular);
  }
};

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

int main() {
  auto s = new Solution1;
  int res, want;

  want = 3;
  res = s->maxSubarraySumCircular({1, -2, 3, -2});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 10;
  res = s->maxSubarraySumCircular({5, -3, 5});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = -2;
  res = s->maxSubarraySumCircular({-3, -2, -3});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 0;
  res = s->maxSubarraySumCircular({0, -3, -2, -3, 0});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
