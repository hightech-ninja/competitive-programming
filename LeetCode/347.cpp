#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <unordered_map>
#include <vector>

using namespace std;

/*
    Time: O(n) - avg, O(n^2) worst-case
    Space: O(uniq)
 */
class Solution {
private:
  void make_swap(vector<int> &values, vector<int> &freqs, int i, int j) {
    swap(values[i], values[j]);
    swap(freqs[i], freqs[j]);
  }

  void quickSelect(vector<int> &values, vector<int> &freqs, int k) {
    int n = (int)values.size();
    int l = 0, r = n - 1;
    while (true) {
      int wall = l;         // partition border
      int pivot = freqs[r]; // last element
      for (int i = l; i < r; ++i)
        if (freqs[i] < pivot)
          make_swap(values, freqs, wall++, i);
      make_swap(values, freqs, wall, r); // put pivot on it's place

      int rank = wall;
      if (rank == k)
        return;
      else if (rank < k)
        l = rank + 1;
      else //  rank > k
        r = rank - 1;
    }
  }

public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
    unordered_map<int, int> freqsMap;
    for (int num : nums)
      freqsMap[num]++;
    vector<int> values, freqs;
    int uniq = freqsMap.size();
    values.reserve(uniq);
    freqs.reserve(uniq);
    for (auto it : freqsMap) {
      values.push_back(it.first);
      freqs.push_back(it.second);
    }

    quickSelect(values, freqs, uniq - k);
    values.erase(values.begin(), values.end() - k);
    return values;
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
  vector<int> input;
  vector<int> want, res;

  input = {3, 0, 1, 0};
  want = {0};
  res = s->topKFrequent(input, 1);
  sort(res.begin(), res.end());
  assert(res == want);
  println("ok");

  input = {1, 1, 1, 2, 2, 3};
  want = {1, 2};
  res = s->topKFrequent(input, 2);
  sort(res.begin(), res.end());
  assert(res == want);
  println("ok");

  input = {1};
  want = {1};
  res = s->topKFrequent(input, 1);
  sort(res.begin(), res.end());
  assert(res == want);
  println("ok");

  input = {1, 2, 1, 2, 1, 2, 3, 1, 3, 2};
  want = {1, 2};
  res = s->topKFrequent(input, 2);
  sort(res.begin(), res.end());
  assert(res == want);
  println("ok");

  return 0;
}
