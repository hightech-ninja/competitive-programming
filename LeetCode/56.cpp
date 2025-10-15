#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(nlogn)
 * Space: O(n)
 */
class Solution {
public:
  vector<vector<int>> merge(vector<vector<int>> &intervals) {
    auto cmp = [](vector<int> const &a, vector<int> const &b) {
      return a[0] < b[0];
    };
    sort(intervals.begin(), intervals.end(), cmp);

    vector<vector<int>> ans;
    ans.reserve(intervals.size());
    ans.push_back(intervals[0]);
    for (auto const& interval : intervals) {
        if (ans.back()[1] < interval[0]) {
            ans.push_back(interval);
            continue;
        }
        ans.back()[1] = max(ans.back()[1], interval[1]);
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
  vector<vector<int>> input;
  vector<vector<int>> want, res;

  input = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
  want = {{1, 6}, {8, 10}, {15, 18}};
  res = s->merge(input);
  assert(res == want);
  println("ok");

  input = {{1, 4}, {4, 5}};
  want = {{1, 5}};
  res = s->merge(input);
  assert(res == want);
  println("ok");

  input = {{4, 7}, {1, 4}};
  want = {{1, 7}};
  res = s->merge(input);
  assert(res == want);
  println("ok");

  input = {{1, 7}};
  want = {{1, 7}};
  res = s->merge(input);
  assert(res == want);
  println("ok");

  input = {{1, 4}, {0, 4}};
  want = {{0, 4}};
  res = s->merge(input);
  assert(res == want);
  println("ok");

  input = {{1, 4}, {2, 3}};
  want = {{1, 4}};
  res = s->merge(input);
  assert(res == want);
  println("ok");

  input = {{1, 2}, {3, 4}, {1, 6}};
  want = {{1, 6}};
  res = s->merge(input);
  assert(res == want);
  println("ok");

  input = {{2, 3}, {4, 5}, {6, 7}, {8, 9}, {1, 10}};
  want = {{1, 10}};
  res = s->merge(input);
  assert(res == want);
  println("ok");

  return 0;
}
