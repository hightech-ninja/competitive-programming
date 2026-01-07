#include <cassert>
#include <print>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  int subarraySum(vector<int> const &nums, int k) {
    int sum = 0, target = 0;
    int ans = 0;
    unordered_map<int, int> counts;
    counts[0] = 1;
    for (int r = 0; r < (int)nums.size(); ++r) {
      sum += nums[r];
      target = sum - k;
      ans += counts[target];
      counts[sum]++;
    }
    return ans;
  }
};

int main() {
  auto s = new Solution;
  int res;

  res = s->subarraySum({1, 1, 1}, 2);
  println("res={}", res);
  assert(res == 2);
  println("ok");

  res = s->subarraySum({1, 2, 3}, 3);
  println("res={}", res);
  assert(res == 2);
  println("ok");

  return 0;
}
