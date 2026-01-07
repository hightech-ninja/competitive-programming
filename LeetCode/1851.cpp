#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <set>
#include <vector>

using namespace std;

/*
    Time: O((n+q)log(n))
    Space: O(n+q)
 */
class Solution {
private:
  struct Event {
    int x;
    int idx;  // index of query or interval
    int type; // 0 - open, 1 - query, 2 - close
  };

public:
  vector<int> minInterval(vector<vector<int>> const &intervals,
                          vector<int> const &queries) {
    int n = (int)intervals.size();
    int m = (int)queries.size();
    vector<Event> events;
    events.reserve(2 * n + m);
    for (int i = 0; i < n; ++i) {
      int l = intervals[i][0];
      int r = intervals[i][1];
      events.push_back({l, i, 0});
      events.push_back({r, i, 2});
    }
    for (int i = 0; i < m; ++i) {
      int pos = queries[i];
      events.push_back({pos, i, 1});
    }
    sort(events.begin(), events.end(),
         [](Event const &first, Event const &second) {
           if (first.x != second.x) {
             return first.x < second.x;
           } else {
             return first.type < second.type;
           }
         });

    auto len = [&intervals](int i) {
      return intervals[i][1] - intervals[i][0] + 1;
    };
    set<pair<int, int>> active;
    int k = (int)events.size();
    vector<int> ans(m, -1);
    for (int i = 0; i < k;) {
      int x = events[i].x;
      while (i < k && events[i].x == x && events[i].type == 0) {
        int idx = events[i].idx;
        active.insert({len(idx), idx});
        ++i;
      }
      while (i < k && events[i].x == x && events[i].type == 1) {
        if (!active.empty()) {
          ans[events[i].idx] = active.begin()->first;
        }
        ++i;
      }
      while (i < k && events[i].x == x && events[i].type == 2) {
        int idx = events[i].idx;
        active.erase(active.find({len(idx), idx}));
        ++i;
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
  vector<int> res, want;

  want = {3, 3, 1, 4};
  res = s->minInterval({{1, 4}, {2, 4}, {3, 6}, {4, 4}}, {2, 3, 4, 5});
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {2, -1, 4, 6};
  res = s->minInterval({{2, 3}, {2, 5}, {1, 8}, {20, 25}}, {2, 19, 5, 22});
  assert(res == want);
  println("ok");

  return 0;
}
