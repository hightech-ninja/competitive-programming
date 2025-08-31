#include <cassert>
#include <iostream>
#include <print>
#include <queue>
#include <vector>

using namespace std;

/*
    Time: O(nm log(nm))
    Space: O(nm)

    Intuitive:
        Imagine that height map is gradually sinking into a bucket of water (level by level).
        Water fill areas starting from the border. As the water level rises, the islands fill up
        and the water overflows the partitions. Water start filling area from the smallest border
        cell.
    Facts:
        1. Water can outflow only through border cells;
        2. It escapes along the path with the lowest border cell;
    Solution:
        1. Multi-source Dijkstra, starting from all border cells
        2. On each step take lowest by height cell and finalize it;
        3. Push (left, right, top, bottom) neighbours;
        4. To finalize cell, keep highest level seen so far;
*/


class Solution {
private:
    static constexpr int moves[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    using State = tuple<int, int, int>; // height, row, column
public:
    int trapRainWater(vector<vector<int>> &heightMap) {
        priority_queue<State, vector<State>, greater<State>> pq; // min-heap
        int n = (int)heightMap.size();
        int m = (int)heightMap[0].size();
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (r == 0 || r == n - 1 || c == 0 || c == m - 1) {
                    pq.push({heightMap[r][c], r, c});
                    heightMap[r][c] = -1;
                }
            }
        }

        int maxLvl = 0, ans = 0;
        while (!pq.empty()) {
            auto [height, r, c] = pq.top(); pq.pop();
            maxLvl = max(maxLvl, height);
            ans += max(0, (maxLvl - height));

            int nr, nc;
            for (auto const& mv : moves) {
                nr = r + mv[0];
                nc = c + mv[1];
                if (nr < 0 || nr >= n)
                    continue;
                if (nc < 0 || nc >= m)
                    continue;
                if (heightMap[nr][nc] == -1)
                    continue;
                int lvl = heightMap[nr][nc];
                pq.push({lvl, nr, nc});
                heightMap[nr][nc] = -1;
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
  vector<vector<int>> input;
  int res, want;

  input = {
      {1, 4, 3, 1, 3, 2},
      {3, 2, 1, 3, 2, 4},
      {2, 3, 3, 2, 3, 1},
  };
  want = 4;
  res = s->trapRainWater(input);
  println("res= {}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  input = {{3, 3, 3, 3, 3},
           {3, 2, 2, 2, 3},
           {3, 2, 1, 2, 3},
           {3, 2, 2, 2, 3},
           {3, 3, 3, 3, 3},
  };
  want = 10;
  res = s->trapRainWater(input);
  println("res= {}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
