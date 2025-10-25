#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
    Time: O(v + e)
    Space: O(v + e)
 */
class Solution {
private:
  bool dfs(int v, vector<vector<int>> &neibs, vector<int> &color,
           vector<int> &order) {
    if (color[v] >= 2)
      // visited, no cycle
      return false;
    if (color[v] == 1)
      // visited, cycle
      return true;

    // color[v]: 0 (new) -> 1 (processing)
    color[v] = 1;

    for (int u : neibs[v])
      if (dfs(u, neibs, color, order))
        // found cycle
        return true;

    // completed
    color[v] = 2;
    order.push_back(v);

    // no cycle
    return false;
  }

public:
  vector<int> findOrder(int numCourses,
                        vector<vector<int>> const &prerequisites) {
    vector<vector<int>> neibs(numCourses, vector<int>{});
    for (vector<int> const &edge : prerequisites) {
      neibs[edge[1]].push_back(edge[0]);
    }
    vector<int> order;
    order.reserve(numCourses);
    vector<int> color(numCourses, 0);
    for (int v = 0; v < numCourses; ++v)
      if (dfs(v, neibs, color, order))
        return {};
    reverse(order.begin(), order.end());
    return order;
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
  vector<vector<char>> input;
  vector<int> res, want;

  want = {0, 1};
  res = s->findOrder(2, {{1, 0}});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {0, 2, 1, 3};
  res = s->findOrder(4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
