#include <print>
#include <cassert>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
private:
    struct Event {
        int x;
        int h;
        int type; // 0 - open, 1 - close
    };
public:
    /*
        state:
            - events ([L, H] - open, [R, H] - close)
            - sweep x
            - active buildings (heights)
        Invariants:
            - active buildings change only on borders (L_i or R_i)
            - between two adjacent by X coordinate events active building are constant
            - countour of silhouette at X is max(active buildings)
   */
    vector<vector<int>> getSkyline(vector<vector<int>> const& buildings) {
        int n = (int)buildings.size();
        vector<Event> events;
        events.reserve(n << 1);
        for (int i = 0; i < n; ++i) {
            int l = buildings[i][0], r = buildings[i][1], h = buildings[i][2];
            events.push_back({l, h, 0});
            events.push_back({r, h, 1});
        }

        auto cmp = [](const Event& first, const Event& second) {
            if (first.x != second.x) {
                return first.x < second.x;
            } else if (first.type != second.type) {
                return first.type < second.type;
            }
            return first.h < second.h;
        };

        sort(events.begin(), events.end(), cmp);

        vector<vector<int>> ans;
        multiset<int> active;

        int m = (int)events.size();
        ans.reserve(m);
        active.insert(0);

        for (int i = 0; i < m;) {
            int x = events[i].x;
            while (i < m && events[i].x == x) {
                if (events[i].type == 0) {
                    active.insert(events[i].h);
                } else {
                    active.erase(active.find(events[i].h));
                }
                ++i;
            }
            int lvl = *active.rbegin();
            if (ans.empty() || ans.back()[1] != lvl) {
                ans.push_back({x, lvl});
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
    vector<vector<int>> res, want;

    want = {{2, 10}, {3, 15}, {7, 12}, {12, 0}, {15, 10}, {20, 8}, {24, 0}};
    res = s->getSkyline({{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}});
    println("res ={}\nwant={}", res, want);
    assert(res == want); println("ok");

    return 0;
}
