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
 *  - for each element calculate # sub-arrays, such that this element is
 *    minimal;
 *  - for arr[m]:
 *      - find arr[r] - next strictly less element;
 *      - find arr[l] - previous less or equal element;
 *      - arr[m] contributes: (m - l) * (r - m) * arr[m];
 *  - both NLE and PLEQ could be found via non-decreasing monotonic stack;
 *  - keep in mind that for duplicates:
 *      - search for strictly less for both next/previous gives overlapped
 *        intervals;
 *      - search for less or equal for both next/previous excludes some
 *        intervals;
 */
class Solution {
private:
  static const long long modulo = (long long)(1e9 + 7);

public:
  int sumSubarrayMins(vector<int> const &arr) {
    int n = (int)arr.size();
    long long ans = 0LL;

    vector<int> nle(n, n), pleq(n, -1);
    // non-decreasing;
    // NLE  view: keep elements that have not found NLE yet;
    // PLEQ view: keep candidates PLEQ for the current element;
    stack<int> st;
    for (int r = 0; r < n; ++r) {
      while (!st.empty() && arr[st.top()] > arr[r]) {
        nle[st.top()] = r;
        st.pop();
      }
      pleq[r] = (st.empty() ? -1 : st.top());
      st.push(r);
    }

    for (int mid = 0; mid < n; ++mid) {
      int l = pleq[mid];
      int r = nle[mid];
      ans += (long long)arr[mid] * (mid - l) * (r - mid);
      ans %= modulo;
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
  auto s = new Solution;
  int res, want;

  want = 17;
  res = s->sumSubarrayMins({3, 1, 2, 4});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 444;
  res = s->sumSubarrayMins({11, 81, 94, 43, 3});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 6;
  res = s->sumSubarrayMins({1, 1, 1});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
