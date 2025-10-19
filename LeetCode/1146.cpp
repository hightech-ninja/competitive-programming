#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
    Time: set, snap - O(1), get - O(logn)
    Space: O(n)
 */
class SnapshotArray {
private:
  vector<vector<pair<int, int>>> _timelines;
  int _snap_id;

public:
  SnapshotArray(int length) : _timelines(length), _snap_id(0) {
    for (int i = 0; i < length; ++i)
      _timelines[i].push_back({-1, 0});
  }

  void set(int index, int val) {
    if (_timelines[index].back().first == _snap_id)
      _timelines[index].back().second = val;
    else
      _timelines[index].push_back({_snap_id, val});
  }

  int snap() { return _snap_id++; }

  int get(int index, int snap_id) {
    int n = _timelines[index].size();
    auto it = upper_bound(_timelines[index].begin(), _timelines[index].end(),
                          make_pair(snap_id, INT_MAX));
    --it;
    return it->second;
  }
};

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

int main() {
  int snapId, value;
  auto obj = new SnapshotArray(3);

  obj->set(1, 6);
  obj->snap();
  obj->snap();
  obj->set(1, 19);
  obj->set(0, 4);
  value = obj->get(0, 1);
  assert(value == 0);

  return 0;
}
