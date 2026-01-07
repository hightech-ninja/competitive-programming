#include <array>
#include <cassert>
#include <iostream>
#include <print>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

/*
 * Time: O(n^2 * logn)
 * Space: O(n^2)
 *
 * Solution:
 *  1. If (0, 0) -> (n, n) reachable with level L, then
 *     it's reachable with any L' >= L;
 *  2. For fixed L reachability can be found using BFS
 *     (move to neighbours with level <= L);
 *  3. So run binary search on the answer;
 */
class Solution {
private:
  using cell = pair<int, int>;

  const array<pair<int, int>, 4> _moves = {
      make_pair(-1, 0),
      make_pair(1, 0),
      make_pair(0, -1),
      make_pair(0, 1),
  };

  bool canReach(vector<vector<int>> const &grid, int lvl, cell start,
                cell target) {
    int n = (int)grid.size();
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    queue<cell> q;
    q.push(start);
    visited[start.first][start.second] = true;

    while (!q.empty()) {
      cell v = q.front();
      q.pop();

      if (v == target) {
        return true;
      }
      for (int i = 0; i < (int)_moves.size(); ++i) {
        cell u = {v.first + _moves[i].first, v.second + _moves[i].second};
        if (u.first < 0 || u.first >= n) {
          continue;
        }
        if (u.second < 0 || u.second >= n) {
          continue;
        }
        if (visited[u.first][u.second]) {
          continue;
        }
        if (grid[u.first][u.second] > lvl) {
          continue;
        }
        q.push(u);
        visited[u.first][u.second] = true;
      }
    }

    return false;
  }

  int find(vector<vector<int>> const &grid, int l, int r) {
    int n = (int)grid.size();
    while (l < r) {
      int lvl = l + (r - l) / 2;
      if (canReach(grid, lvl, {0, 0}, {n - 1, n - 1})) {
        r = lvl;
      } else { // can't reach destination with lvl
        l = lvl + 1;
      }
    }
    return l;
  }

public:
  int swimInWater(vector<vector<int>> const &grid) {
    int n = (int)grid.size();
    int lo = max(grid[0][0], grid[n - 1][n - 1]);
    int hi = n * n + 1;
    return find(grid, lo, hi);
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

  want = 3;
  res = s->swimInWater({{0, 2}, {1, 3}});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 16;
  res = s->swimInWater({{0, 1, 2, 3, 4},
                        {24, 23, 22, 21, 5},
                        {12, 13, 14, 15, 16},
                        {11, 17, 18, 19, 20},
                        {10, 9, 8, 7, 6}});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 3;
  res = s->swimInWater({{3, 2}, {0, 1}});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 3;
  res = s->swimInWater({{273, 62,  2,   385, 213, 360, 188, 158, 196, 100,
                         260, 323, 219, 348, 274, 175, 280, 130, 316, 36},
                        {66,  255, 233, 334, 265, 243, 303, 163, 294, 324,
                         205, 69,  131, 337, 110, 179, 380, 129, 295, 133},
                        {207, 313, 287, 183, 240, 127, 382, 341, 199, 104,
                         35,  85,  6,   321, 230, 308, 113, 90,  167, 257},
                        {262, 117, 155, 68,  189, 269, 355, 373, 248, 23,
                         21,  173, 186, 115, 29,  13,  52,  297, 390, 177},
                        {286, 9,   31,  44,  289, 11,  168, 93,  392, 318,
                         119, 156, 377, 330, 386, 276, 99,  388, 150, 153},
                        {227, 126, 225, 187, 370, 353, 345, 335, 165, 322,
                         53,  118, 343, 72,  218, 20,  88,  74,  82,  352},
                        {249, 191, 141, 306, 371, 203, 149, 91, 226, 393,
                         97,  367, 144, 159, 15,  206, 336, 83, 120, 49},
                        {399, 170, 394, 267, 14,  309, 310, 70,  283, 38,
                         258, 200, 326, 34,  395, 237, 368, 250, 384, 73},
                        {192, 37,  161, 361, 354, 328, 10,  376, 67,  256,
                         296, 350, 96,  48,  254, 140, 197, 95,  301, 383},
                        {190, 5,  362, 30,  333, 125, 229, 50,  300, 398,
                         314, 63, 94,  239, 266, 25,  28,  223, 40,  26},
                        {78,  178, 57,  282, 397, 195, 288, 224, 275, 128,
                         105, 142, 112, 80,  264, 4,   359, 311, 344, 181},
                        {148, 123, 107, 89,  293, 363, 54,  201, 143, 42,
                         272, 332, 116, 160, 0,   364, 252, 16,  245, 378},
                        {27, 182, 375, 312, 109, 290, 212, 244, 185, 242,
                         81, 291, 56,  241, 228, 64,  103, 172, 278, 65},
                        {236, 202, 391, 43,  114, 210, 12,  216, 71,  231,
                         372, 176, 147, 369, 108, 98,  124, 24,  194, 317},
                        {222, 86, 217, 339, 136, 76,  211, 358, 235, 132,
                         347, 32, 204, 75,  381, 162, 45,  138, 387, 299},
                        {77,  396, 351, 106, 285, 8,   151, 84,  379, 18,
                         220, 365, 134, 58,  307, 346, 154, 356, 22,  374},
                        {366, 259, 60,  1,   234, 281, 277, 279, 208, 47,
                         135, 41,  261, 102, 157, 325, 246, 137, 193, 357},
                        {59,  232, 7,  180, 284, 304, 268, 121, 319, 51,
                         302, 349, 33, 198, 292, 184, 92,  46,  79,  209},
                        {263, 152, 214, 111, 253, 169, 247, 270, 166, 331,
                         338, 340, 329, 61,  39,  389, 315, 17,  342, 101},
                        {221, 164, 305, 251, 298, 19,  139, 174, 215, 55,
                         320, 122, 238, 327, 146, 171, 145, 87,  3,   271}});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
