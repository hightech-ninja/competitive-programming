#include <cassert>
#include <iostream>
#include <print>
#include <queue>
#include <vector>

using namespace std;

/*
 * Time: O(nlogn)
 * Space: O(n)
 */
class Solution {
public:
  int minRefuelStops(int target, int startFuel,
                     vector<vector<int>> const &stations) {
    int n = (int)stations.size();
    priority_queue<int> maxHeap;
    int maxDistance = startFuel;
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
      int pos = (i < n ? stations[i][0] : target);
      int fuel = (i < n ? stations[i][1] : 0);
      while (maxDistance < pos) {
        if (maxHeap.empty()) {
          return -1;
        }
        maxDistance += maxHeap.top();
        maxHeap.pop();
        ++ans;
      }
      if (i < n) {
        maxHeap.push(fuel);
      }
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
  int want, res;

  want = 0;
  res = s->minRefuelStops(1, 1, {});
  assert(res == want);
  println("ok");

  want = -1;
  res = s->minRefuelStops(100, 1, {{10, 100}});
  assert(res == want);
  println("ok");

  want = 2;
  res = s->minRefuelStops(100, 10, {{10, 60}, {20, 30}, {30, 30}, {60, 40}});
  assert(res == want);
  println("ok");

  return 0;
}
