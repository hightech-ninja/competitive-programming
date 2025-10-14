#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(nlogn)
 * Space: O(logn)
 */
class Solution {
public:
  int findLongestChain(vector<vector<int>> &pairs) {
    auto cmp = [](vector<int> const &a, vector<int> const &b) {
      return a[1] < b[1];
    };
    sort(pairs.begin(), pairs.end(), cmp);

    int ans = 0;
    int last_chain = INT_MIN;
    for (auto const &p : pairs) {
      if (last_chain >= p[0])
        continue;
      ++ans;
      last_chain = p[1];
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
  int want, res;

  input = {{1, 2}, {2, 3}, {3, 4}};
  want = 2;
  res = s->findLongestChain(input);
  assert(res == want);
  println("ok");

  input = {{1, 2}, {7, 8}, {4, 5}};
  want = 3;
  res = s->findLongestChain(input);
  assert(res == want);
  println("ok");

  input = {{1, 2}};
  want = 1;
  res = s->findLongestChain(input);
  assert(res == want);
  println("ok");

  return 0;
}
