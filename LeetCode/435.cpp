#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time:  O(nlogn)
 * Space: O(logn)
 */
class Solution {
public:
  int eraseOverlapIntervals(vector<vector<int>> &intervals) {
    auto cmp = [](vector<int> const &a, vector<int> const &b) -> bool {
      return a[1] < b[1];
    };
    sort(intervals.begin(), intervals.end(), cmp);
    int rm = 0, lastR = INT_MIN;
    for (auto const &interval : intervals) {
      int l = interval[0];
      int r = interval[1];
      if (lastR > l) // intersects with last taken
        rm++;
      else // lastR <= l // don't intersects with last taken, new last interval
        lastR = r;
    }
    return rm;
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
  vector<vector<int>> input;
  int want, res;

  input = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
  want = 1;
  res = s->eraseOverlapIntervals(input);
  assert(res == want);
  println("ok");

  input = {{1, 2}, {1, 2}, {1, 2}};
  want = 2;
  res = s->eraseOverlapIntervals(input);
  assert(res == want);
  println("ok");

  input = {{1, 2}, {2, 3}};
  want = 0;
  res = s->eraseOverlapIntervals(input);
  assert(res == want);
  println("ok");

  return 0;
}
