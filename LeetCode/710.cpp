#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <random>
#include <vector>

using namespace std;

/*
    Time: O(mlogm + klogm), m = |blacklist|, k = |request|
    Space: O(logm)
 */
class Solution {
private:
  int _n;
  vector<int> _blacklist;

  int _available;
  mt19937 _gen;
  uniform_int_distribution<> _dis;

public:
  Solution(int n, vector<int> &blacklist)
      : _n(n), _blacklist(blacklist), _available(n - (int)blacklist.size()),
        _gen(random_device{}()), _dis(0, _available - 1) {
    sort(_blacklist.begin(), _blacklist.end());
  }

  int pick() {
    // select available point, 0-based
    int freePoint = _dis(_gen);
    // find first blacklist element that
    // covers freePoint via bin-search
    // freePoints(i) = blacklisted(i) - i - 1
    // fn(i) = freePoints(i) >= freePoint
    int m = (int)_blacklist.size();
    int l = 0, r = m;
    while (l < r) {
      int mid = l + (r - l) / 2;
      int freePoints = _blacklist[mid] - mid - 1;
      // for l'  < l: fn(l') < freePoint
      // for r' >= r: fn(r') >= freePoint
      if (freePoints >= freePoint) {
        r = mid;
      } else { // freePoints < freePoint
        l = mid + 1;
      }
    }

    return freePoint + l;
  }
};

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

int main() {
  vector<int> blacklist = {2, 3, 5};
  auto s = new Solution(7, blacklist);

  println("{}", s->pick());
  println("{}", s->pick());
  println("{}", s->pick());
  println("{}", s->pick());
  println("{}", s->pick());
  println("{}", s->pick());
  println("{}", s->pick());
  return 0;
}
