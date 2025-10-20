#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
    Time:  O(n)
    Space: O(n)
 */
class Solution {
public:
  vector<vector<int>> insert(vector<vector<int>> const &intervals,
                             vector<int> &newInterval) {
    int n = (int)intervals.size();
    int lastR = -1;
    for (int i = 0; i < n; ++i) {
      int l = intervals[i][0];
      int r = intervals[i][1];
      if (r < newInterval[0] || newInterval[1] < l)
        continue;
      newInterval[0] = min(newInterval[0], l);
      newInterval[1] = max(newInterval[1], r);
    }

    int i = 0;
    vector<vector<int>> ans;
    ans.reserve(n);

    while (i < n && intervals[i][1] < newInterval[0])
      ans.push_back(intervals[i++]);

    ans.push_back(newInterval);
    while (i < n && intervals[i][0] <= newInterval[1])
      i++;
    while (i < n && intervals[i][0] > newInterval[1])
      ans.push_back(intervals[i++]);

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
  vector<int> input;
  vector<vector<int>> want, res;

  input = {2, 5};
  want = {{1, 5}, {6, 9}};
  res = s->insert({{1, 3}, {6, 9}}, input);
  assert(res == want);
  println("ok");

  input = {4, 8};
  want = {{1, 2}, {3, 10}, {12, 16}};
  res = s->insert({{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}, input);
  assert(res == want);
  println("ok");

  return 0;
}
