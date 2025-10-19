#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
    Time: O(n)
    Space: O(n)
 */
class Solution {
public:
  vector<int> productExceptSelf(vector<int> &nums) {
    int n = (int)nums.size();
    vector<int> sufs(n, 1);

    sufs[n - 1] = nums[n - 1];
    int suf = 1;
    for (int i = n - 1; i >= 0; --i) {
      sufs[i] = suf;
      suf *= nums[i];
    }

    int pref = 1, temp;
    for (int i = 0; i < n; ++i) {
      temp = nums[i];
      nums[i] = pref;
      pref *= temp;
    }

    for (int i = 0; i < n; ++i) {
      nums[i] *= sufs[i];
    }

    return nums;
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
  vector<int> input;
  vector<int> want, res;

  input = {1, 2, 3, 4};
  want = {24, 12, 8, 6};
  res = s->productExceptSelf(input);
  assert(res == want);
  println("ok");

  input = {-1, 1, 0, -3, 3};
  want = {0, 0, 9, 0, 0};
  res = s->productExceptSelf(input);
  assert(res == want);
  println("ok");

  return 0;
}
