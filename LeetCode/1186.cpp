#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
    Time: O(n)
    Space: O(1)

    Solution:
        - Kadane's algorithm extended to 2D, influenced by DP view;
        - second dimension 0/1 - how many drops done;
        - notice we still need only last two states, so O(1) memory;
 */
class [[maybe_unused]] Solution2 {
public:
  int maximumSum(vector<int> const &arr) {
    int n = (int)arr.size();
    long long keep = arr[0], drop = 0LL;
    long long ans = arr[0];
    for (int r = 1; r < n; ++r) {
      drop = max(keep, drop + arr[r]);
      keep = max(keep + arr[r], (long long)arr[r]);
      ans = max(ans, keep);
      ans = max(ans, drop);
    }
    return (int)ans;
  }
};

/*
    Time: O(n)
    Space: O(n)

    Solution:
        Kadane's algorithm for prefix and suffix, influenced by geometry view
 */
class [[maybe_unused]] Solution1 {
public:
  int maximumSum(vector<int> const &arr) {
    int n = (int)arr.size();
    vector<long long> rightMax(n, 0), leftMax(n, 0);

    // Inv: r - fixed, then rightMax[r] = max sum among intervals [l..r]
    long long sum = 0LL, sumMin = 0LL;
    for (int i = 0; i < n; ++i) {
      sum += arr[i];
      rightMax[i] = sum - sumMin;
      sumMin = min(sumMin, sum);
    }

    // Inv: l - fixed, then leftMax[l] = max sum among intervals [l..r]
    sum = 0LL, sumMin = 0LL;
    for (int i = n - 1; i >= 0; --i) {
      sum += (long long)arr[i];
      leftMax[i] = sum - sumMin;
      sumMin = min(sumMin, sum);
    }

    long long ans = LLONG_MIN;
    for (int mid = 0; mid < n; ++mid) {
      ans = max(ans, leftMax[mid] + rightMax[mid] - arr[mid]);
      if (mid > 0 && mid + 1 < n) {
        ans = max(ans, rightMax[mid - 1] + leftMax[mid + 1]);
      }
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
  auto s = new Solution2;
  int res, want;

  want = 4;
  res = s->maximumSum({1, -2, 0, 3});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 3;
  res = s->maximumSum({1, -2, -2, 3});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = -1;
  res = s->maximumSum({-1, -1, -1, -1});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 7;
  res = s->maximumSum({1, -4, -5, -2, 5, 0, -1, 2});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
