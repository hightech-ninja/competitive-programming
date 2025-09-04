#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

class Solution {
public:
  int maxProduct(vector<int> const &nums) {
    int n = (int)nums.size();
    long long smallest = nums[0];
    long long largest = nums[0];
    long long bestSoFar = nums[0];
    for (int r = 1; r < n; ++r) {
        array<long long, 3> candidates{nums[r], nums[r] * smallest, nums[r] * largest};
        smallest = *min_element(candidates.begin(), candidates.end());
        largest = *max_element(candidates.begin(), candidates.end());
        bestSoFar = max(bestSoFar, largest);
    }
    return (int)bestSoFar;
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

  want = 8;
  res = s->maxProduct({0, 2, -2, -2});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 6;
  res = s->maxProduct({2, 3, -2, 4});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 0;
  res = s->maxProduct({-2, 0, -1});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
