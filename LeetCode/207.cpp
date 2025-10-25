#include <cassert>
#include <iostream>
#include <print>
#include <unordered_map>
#include <vector>

using namespace std;

/*
    Time: O(v + e)
    Space: O(v + e)
 */
class Solution {
private:
  bool visit(unordered_map<int, vector<int>> &neibs, vector<int> &color,
             int u) {
    if (color[u] >= 2)
      return false;
    if (color[u] == 1)
      return true;
    color[u] = 1;
    for (int v : neibs[u]) {
      if (visit(neibs, color, v)) {
        return true;
      }
    }
    color[u] = 2;
    return false;
  }

public:
  bool canFinish(int numCourses, vector<vector<int>> const &prerequisites) {
    unordered_map<int, vector<int>> neibs;
    neibs.reserve(numCourses);
    for (auto &edge : prerequisites) {
      neibs[edge[1]].push_back(edge[0]);
    }

    vector<int> color(numCourses, 0);
    for (int u = 0; u < numCourses; ++u) {
      if (visit(neibs, color, u)) {
        return false;
      }
    }
    return true;
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
  bool res, want;

  want = false;
  res = s->canFinish(2, {{1, 0}, {0, 1}});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = true;
  res = s->canFinish(2, {{1, 0}});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
