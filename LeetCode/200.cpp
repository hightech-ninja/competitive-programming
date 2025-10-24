#include <array>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
    Time: O(mn)
    Space: O(mn)
 */
class Solution {
private:
array<pair<int, int>, 4> moves{make_pair(-1, 0), make_pair(0, -1),
                               make_pair(0, 1), make_pair(1, 0)};

  void visit(vector<vector<char>> &grid, int m, int n, int u, int v) {
    if (grid[u][v] != '1')
      return;
    grid[u][v] = '0';
    for (int i = 0; i < 4; ++i) {
      int nextU = u + moves[i].first;
      int nextV = v + moves[i].second;
      if (nextU < 0 || nextV < 0 || nextU >= m || nextV >= n)
        continue;
      if (grid[nextU][nextV] == '1')
        visit(grid, m, n, nextU, nextV);
    }
  }

public:
  int numIslands(vector<vector<char>> &grid) {
    int m = (int)grid.size();
    int n = (int)grid[0].size();
    int islands = 0;
    for (int u = 0; u < m; ++u) {
      for (int v = 0; v < n; ++v) {
        if (grid[u][v] == '1') {
          ++islands;
          visit(grid, m, n, u, v);
        }
      }
    }
    return islands;
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
  int res, want;

  want = 1;
  input = {{'1', '1', '1', '1', '0'},
           {'1', '1', '0', '1', '0'},
           {'1', '1', '0', '0', '0'},
           {'0', '0', '0', '0', '0'}};
  res = s->numIslands(input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 3;
  input = {{'1', '1', '0', '0', '0'},
           {'1', '1', '0', '0', '0'},
           {'0', '0', '1', '0', '0'},
           {'0', '0', '0', '1', '1'}};
  res = s->numIslands(input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
