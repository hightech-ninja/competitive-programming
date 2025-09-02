#include <cassert>
#include <queue>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
    Time: O(n)
    Space: O(k)

    State:
        - sweep l from [0 to n)
        - active: [r - k, r] with all r <= l
            active flip intervals, covering l
    Invariants:
        Inv1:
            - after processing [0..l): active.size() gives parity of flips
            - so current value after applying that flips is known;
        Inv2: Left to write commitment
            - after processing [0..l) the last chance to flip 0 to 1 is to
              make flip of [l..l+k), because it is last covering interval
    Solution:
        1. sweep + Greedy
        2. if l > n - k and actual value 0, then answer is -1

 */
class Solution {
public:
  int minKBitFlips(vector<int> const &nums, int k) {
    int n = (int)nums.size();
    queue<int> active;
    int ans = 0;

    for (int l = 0; l < n; ++l) {
      if (!active.empty() && active.front() <= l)
        active.pop();
      int bit = nums[l] ^ (active.size() & 1);
      if (bit)
        continue;
      if (l > n - k)
        return -1;
      int r = l + k;
      active.push(r);
      ++ans;
    }

    return ans;
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

  want = 2;
  res = s->minKBitFlips({0, 1, 0}, 1);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = -1;
  res = s->minKBitFlips({1, 1, 0}, 2);
  assert(res == want);
  println("ok");

  return 0;
}
