#include <cassert>
#include <functional>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
    Time: O(n)
    Space: O(1)
 */
class Solution {
private:
  void
  quickSelect(vector<vector<int>> &costs, int k,
              function<bool(vector<int> const &, vector<int> const &)> less) {
    int l = 0, r = (int)costs.size() - 1;
    while (true) {
      int pivot = r; // last element
      int wall = l;  // partition index
      for (int j = l; j < r; ++j) {
        if (less(costs[j], costs[r])) {
          swap(costs[wall++], costs[j]);
        }
      }
      swap(costs[wall], costs[pivot]); // put pivot at its final place
      int rank = wall;
      if (k == rank) {
        return;
      } else if (k < rank) {
        r = rank - 1;
      } else {
        l = rank + 1;
      }
    }
  }

public:
  int twoCitySchedCost(vector<vector<int>> &costs) {
    int n = (int)costs.size() >> 1;
    auto cmp = [](vector<int> const &first, vector<int> const &second) {
      return (first[0] - first[1]) < (second[0] - second[1]);
    };
    quickSelect(costs, n, cmp);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans += costs[i][0];
    }
    for (int i = n; i < 2 * n; ++i) {
      ans += costs[i][1];
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
  int res, want;

  input = {{10, 20}, {30, 200}, {400, 50}, {30, 20}};
  want = 110;
  res = s->twoCitySchedCost(input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  input = {{259, 770}, {448, 54},  {926, 667},
           {184, 139}, {840, 118}, {577, 469}};
  want = 1859;
  res = s->twoCitySchedCost(input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  input = {{515, 563}, {451, 713}, {537, 709}, {343, 819},
           {855, 779}, {457, 60},  {650, 359}, {631, 42}};
  want = 3086;
  res = s->twoCitySchedCost(input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
