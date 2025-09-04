#include <limits>
#include <vector>
#include <cassert>
#include <queue>
#include <print>

using namespace std;

class Solution {
public:
    // O(nlogn) time, O(n) space - heap
    int constrainedSubsetSum_heap(vector<int>const & nums, int k) {
        priority_queue<pair<int,int>> maxHeap;
        int n = (int)nums.size();
        int ans = numeric_limits<int>::min();
        int state = 0, prev = 0;
        for (int i = 0; i < n; ++i) {
            int j = i - k;
            while(!maxHeap.empty() && maxHeap.top().second < j) {
                maxHeap.pop();
            }
            prev = maxHeap.empty() ? 0 : maxHeap.top().first;
            state = nums[i] + prev;
            maxHeap.push({state, i});
            ans = max(ans, state);
        }
        return ans;
    }

    // O(n) time, O(k) space - monotonic deque, extends heap solution
    // by noticing that we always need only max over window
    int constrainedSubsetSum(vector<int>const & nums, int k) {
        // front.first > back.first - decreasing states
        // front.second < back.second - increasing indexes
        deque<pair<int, int>> dq;
        int ans = INT_MIN, prev = 0, state = 0;
        for (int i = 0; i < (int)nums.size(); ++i) {
            while (!dq.empty() && dq.front().second < i - k) {
                dq.pop_front();
            }
            prev = (dq.empty() ? 0 : dq.front().first);
            state = max(prev, 0) + nums[i];
            ans = max(ans, state);
            while (!dq.empty() && dq.back().first <= state) {
                dq.pop_back();
            }
            dq.push_back({state, i});
        }
        return ans;
    }
};

int main() {
    auto s = new Solution();
    int res;

    res = s->constrainedSubsetSum({10, 2, -10, 5, 20}, 2);
    println("res={}", res);
    assert(res == 37); println("ok");

    res = s->constrainedSubsetSum({-1, -2, -3}, 1);
    println("res={}", res);
    assert(res == -1);println("ok");

    res = s->constrainedSubsetSum({10, -2, -10, -5, 20}, 2);
    println("res={}", res);
    assert(res == 23); println("ok");

    res = s->constrainedSubsetSum({-5266, 4019, 7336, -3681, -5767}, 2);
    println("res={}", res);
    assert(res == 11355); println("ok");
}
