#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(n^3)
 * Space O(n^2)
 */
class Solution {
private:
  // (l, r) - opened interval
  int maxCoins(vector<int> const &arr, vector<vector<int>> &memo, int l,
               int r) {
    if (l + 1 >= r) {
      return 0;
    }
    int &ans = memo[l][r];
    if (ans != -1)
      return ans;

    for (int i = l + 1; i < r; ++i) {
      int score = maxCoins(arr, memo, l, i) + maxCoins(arr, memo, i, r) +
                  arr[l] * arr[r] * arr[i];
      ans = max(ans, score);
    }
    return ans;
  }

public:
  int maxCoins(vector<int> const &nums) {
    int n = (int)nums.size();
    vector<int> arr(n + 2, 1);
    for (int i = 0; i < n; ++i)
      arr[i + 1] = nums[i];
    vector<vector<int>> memo(n + 2, vector<int>(n + 2, -1));
    return maxCoins(arr, memo, 0, n + 1);
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
  int want, res;

  want = 167;
  res = s->maxCoins({3, 1, 5, 8});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 10;
  res = s->maxCoins({1, 5});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
