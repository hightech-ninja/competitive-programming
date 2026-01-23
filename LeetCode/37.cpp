#include <array>
#include <bit>
#include <cassert>
#include <cctype>
#include <iostream>
#include <print>
#include <stdexcept>
#include <vector>

using namespace std;

/*
 * Time:
 * Space:
 */
class Solution {
private:
  static const int N = 9;
  static const int FULL = (1 << N) - 1;

  // Used to determine next cell to be solved
  struct PickMe {
    int r;
    int c;
    uint32_t candidates; // candidates mask
    int cardinality;     // candidates count
  };

  struct State {
    array<array<int, N>, N> board = {};
    // in-use digits by column
    array<uint32_t, N> cols = {};
    // in-use digits by row
    array<uint32_t, N> rows = {};
    // in-use digits by block
    array<uint32_t, N> blocks = {};

    State(vector<vector<char>> const &board) {
      for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
          if (!isdigit(board[r][c]))
            continue;
          int d = board[r][c] - '0';
          int b = blockId(r, c);
          int m = digitMask(d);

          this->board[r][c] = d;
          this->cols[c] |= m;
          this->rows[r] |= m;
          this->blocks[b] |= m;
        }
      }
    }

    bool solved() {
      for (int i = 0; i < N; ++i)
        if (rows[i] != FULL || cols[i] != FULL || blocks[i] != FULL)
          return false;
      return true;
    }

    int blockId(int r, int c) { return (r / 3) * 3 + (c / 3); }

    uint32_t digitMask(int d) { return 1 << (d - 1); }

    uint32_t candidates(int r, int c) {
      uint32_t used = cols[c] | rows[r] | blocks[blockId(r, c)];
      return ~used & FULL;
    }

    bool place(int r, int c, int d) {
      uint32_t m = digitMask(d);
      int b = blockId(r, c);
      if (cols[c] & m || rows[r] & m || blocks[b] & m)
        return false;
      board[r][c] = d;
      cols[c] |= m;
      rows[r] |= m;
      blocks[b] |= m;
      return true;
    }
  };

  void propagate(State &state) {
    // 1. solve naked singles
    for (int r = 0; r < N; ++r) {
      for (int c = 0; c < N; ++c) {
        if (state.board[r][c] != 0)
          continue;
        uint32_t mask = state.candidates(r, c);
        if (mask > 0 && popcount(mask) == 1) {
          int d = countr_zero(mask) + 1;
          state.place(r, c, d);
        }
      }
    }
    // 2. next can solve hidden singles or just let DFS to work
  }

  bool dfs(State &state) {
    propagate(state);
    if (state.solved())
      return true;

    PickMe pick = {
        .cardinality = N + 1,
    };
    for (int r = 0; r < N; ++r) {
      for (int c = 0; c < N; ++c) {
        if (state.board[r][c] != 0)
          continue;
        uint32_t candidates = state.candidates(r, c);
        int cardinality = popcount(candidates);
        if (pick.cardinality > cardinality) {
          pick.cardinality = cardinality;
          pick.candidates = candidates;
          pick.r = r;
          pick.c = c;
        }
      }
    }
    for (uint32_t mask = pick.candidates; mask > 0; mask &= mask - 1) {
      int d = countr_zero(mask) + 1;
      State next = state;
      if (next.place(pick.r, pick.c, d) && dfs(next)) {
        state = next;
        return true;
      }
    }

    return false;
  }

public:
  void solveSudoku(vector<vector<char>> &board) {
    State state(board);
    if (!dfs(state)) {
      throw std::runtime_error("no solution");
    }
    for (int r = 0; r < N; ++r)
      for (int c = 0; c < N; ++c)
        if (!isdigit(board[r][c]))
          board[r][c] = state.board[r][c] + '0';
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

  input = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
           {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
           {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
           {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
           {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
           {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
           {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
           {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
           {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  s->solveSudoku(input);
  for (auto &row : input)
    println("{}", row);
  println();

  input = {{'.', '.', '9', '7', '4', '8', '.', '.', '.'},
           {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
           {'.', '2', '.', '1', '.', '9', '.', '.', '.'},
           {'.', '.', '7', '.', '.', '.', '2', '4', '.'},
           {'.', '6', '4', '.', '1', '.', '5', '9', '.'},
           {'.', '9', '8', '.', '.', '.', '3', '.', '.'},
           {'.', '.', '.', '8', '.', '3', '.', '2', '.'},
           {'.', '.', '.', '.', '.', '.', '.', '.', '6'},
           {'.', '.', '.', '2', '7', '5', '9', '.', '.'}};

  s->solveSudoku(input);
  for (auto &row : input)
    println("{}", row);
  println();

  return 0;
}
