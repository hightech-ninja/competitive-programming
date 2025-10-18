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
public:
  int rob(vector<int> const &nums) {
    int n = (int)nums.size();
    if (n == 1)
      return nums[0];

    int cur;
    int prev1 = 0;
    int prev2 = 0;
    int ansExcludeLast = 0;
    for (int i = 0; i + 1 < n; ++i) {
      cur = max(prev1, prev2 + nums[i]);
      prev2 = prev1;
      prev1 = cur;
      ansExcludeLast = max(ansExcludeLast, cur);
    }

    prev1 = 0;
    prev2 = 0;
    int ansExcludeFirst = 0;
    for (int i = 1; i < n; ++i) {
      cur = max(prev1, prev2 + nums[i]);
      prev2 = prev1;
      prev1 = cur;
      ansExcludeFirst = max(ansExcludeFirst, cur);
    }
    return max(ansExcludeFirst, ansExcludeLast);
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
  res = s->rob({2, 3, 2});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 4;
  res = s->rob({1, 2, 3, 1});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 7;
  res = s->rob({2, 7});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 7;
  res = s->rob({7, 2});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 7;
  res = s->rob({7});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 3;
  res = s->rob({0, 1, 0, 0, 1, 0, 1});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
