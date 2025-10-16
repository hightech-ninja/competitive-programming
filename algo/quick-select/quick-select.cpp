#include <cassert>
#include <print>
#include <vector>

using namespace std;

int quick_select(vector<int> &arr, int k) {
  assert(k >= 0 && k < (int)arr.size());
  int l = 0, r = (int)arr.size() - 1;
  while (true) {
    int pivot = arr[r]; // last element
    int wall = l;       // partition border
    for (int i = l; i < r; ++i) {
      if (arr[i] < pivot) {
        swap(arr[wall++], arr[i]);
      }
    }
    swap(arr[wall], arr[r]); // put pivot on its position
    int rank = wall;
    if (rank == k)
      return pivot;
    else if (rank < k)
      l = rank + 1;
    else // rank > k
      r = rank - 1;
  }
}

int main() {
  vector<tuple<vector<int>, int, int>> tests{
      {{5}, 0, 5},                   // single element
      {{1, 2}, 0, 1},                // 2 elems, pick min
      {{1, 2}, 1, 2},                // 2 elems, pick max
      {{5, 4, 3, 2, 1}, 2, 3},       // reverse-sorted
      {{1, 2, 3, 4, 5}, 2, 3},       // already sorted
      {{7, 7, 7, 7}, 3, 7},          // all equal, upper boundary
      {{2, 1, 2, 1, 2, 1}, 3, 2},    // many duplicates (ties in the middle)
      {{-3, 10, 0, -3, 5}, 0, -3},   // negatives, min duplicated
      {{-3, 10, 0, -3, 5}, 2, 0},    // mixed signs, middle
      {{9, 9, 1, 9, 2, 9, 3}, 3, 9}, // pivot-value heavy duplicates
      {{4, 2, 5, 1, 3}, 4, 5},       // boundary: k = n - 1
      {{8, 4, 2, 6}, 1, 4},          // even lenght, lower median
      {{0, 0, 0, -1, 1}, 2, 0},      // zeros with signs
      {{2, 2, 2, 3, 1}, 2, 2},       // k falls inside a duplicate block
  };
  for (auto &[arr, k, want] : tests) {
    vector<int> input = arr;
    auto got = quick_select(arr, k);
    if (want != got) {
      println("arr={}\tk={}", input, k);
      println("want={}\ngot={}", want, got);
      exit(1);
    }
  }
  return 0;
}
