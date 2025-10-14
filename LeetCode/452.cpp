#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(nlogn)
 * Space: O(logn)
 */
class Solution {
public:
  int findMinArrowShots(vector<vector<int>> &points) {
    auto cmp = [](vector<int> const &a, vector<int> const &b) {
      return a[1] < b[1];
    };
    sort(points.begin(), points.end(), cmp);
    long long last_shot = LONG_MIN;
    int ans = 0;
    for (auto const &point : points) {
      if (last_shot >= point[0] * 1LL)
        continue;
      ++ans;
      last_shot = point[1] * 1LL;
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
  int want, res;

  input = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
  want = 2;
  res = s->findMinArrowShots(input);
  assert(res == want);
  println("ok");

  input = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
  want = 4;
  res = s->findMinArrowShots(input);
  assert(res == want);
  println("ok");

  input = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  want = 2;
  res = s->findMinArrowShots(input);
  assert(res == want);
  println("ok");

  return 0;
}
