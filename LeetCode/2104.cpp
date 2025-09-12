#include <cassert>
#include <iostream>
#include <print>
#include <stack>
#include <vector>

using namespace std;

/*
 * Time: O(n)
 * Space: O(n)
 *
 * Solution:
 *  FEI ~= for each interval
 *  ans = sum(max - min) FEI = sum(max) FEI - sum(min) FEI
 *
 *  Both sub-problems can be solved with monotonic stack:
 *      1. sum(max): for every nums[m] calculate how many intervals for
 *          this element is minimal via NGE (strictly) and PGEQ (or equal);
 *      2. sum(min): for every nums[m] calculate how many intervals for
 *          this element is maximal via NLE (strictly) and PLEQ (or equal);
 *      3. contribution of nums[m]: (r - m) * (m - l) * nums[m];
 *      4. It's important to keep one border strict and the other not strict
 *          to avoid overlapping arrays contribution:
            sum(min):
 *          nums  = [ 1, 1, 1] (0-indexed)
 *          nge   = [ 3, 3, 3]
 *          pgeq  = [-1, 0, 1]
 *          contributions:
                    m=0 => L in [0], R in [0, 1, 2]
                    m=1 => L in [1], R in [1, 2]
                    m=2 => L in [2], R in [2, 2]
 *
 */
class Solution {
public:
  long long subArrayRanges(vector<int> const &nums) {
    int n = (int)nums.size();

    vector<int> nge(n, n), pgeq(n, -1);
    vector<int> nle(n, n), pleq(n, -1);

    {
      // non-inreasing: st[0] >= ... >= st[top]
      // NGE  view: stack keeps elements that waits for NGE
      // PGEQ view: stack keeps PGEQ candidates for the current element
      stack<int> st;
      for (int r = 0; r < n; ++r) {
        while (!st.empty() && nums[st.top()] < nums[r]) {
          nge[st.top()] = r;
          st.pop();
        }
        pgeq[r] = (st.empty() ? -1 : st.top());
        st.push(r);
      }
    }
    {
      // non-decreasing: st[0] <= ... <= st[top]
      // NLE  view: stack keeps elements that waits for NLE
      // PLEQ view: stack keeps PLEQ candidates for the current element
      stack<int> st;
      for (int r = 0; r < n; ++r) {
        while (!st.empty() && nums[st.top()] > nums[r]) {
          nle[st.top()] = r;
          st.pop();
        }
        pleq[r] = (st.empty() ? -1 : st.top());
        st.push(r);
      }
    }

    long long ans = 0LL;
    for (int m = 0; m < n; ++m) {
      long long maxL = pgeq[m], maxR = nge[m];
      long long minL = pleq[m], minR = nle[m];
      long long maxIntervals = 1LL * (maxR - m) * (m - maxL);
      long long minIntervals = 1LL * (minR - m) * (m - minL);
      ans += nums[m] * (maxIntervals - minIntervals);
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
  long long res, want;

  want = 4;
  res = s->subArrayRanges({1, 2, 3});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 4;
  res = s->subArrayRanges({1, 3, 3});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 59;
  res = s->subArrayRanges({4, -2, -3, 4, 1});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 0;
  res = s->subArrayRanges({1, 1, 1, 1});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 3;
  res = s->subArrayRanges({1, 1, 1, 2});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
