#include <cassert>
#include <iostream>
#include <numeric>
#include <print>
#include <queue>
#include <vector>

using namespace std;

/*
 * Time: O(nlog^2(n))
 * Space: O(n)
 */
class Solution {
private:
  template <class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

  bool canMarkAll(vector<int> const &nums, vector<int> const &indices, int s) {
    int n = (int)nums.size();

    // first[t] = i => i first occurrence on indices[1..s]
    vector<int> first(s, -1);
    vector<bool> seen(n, false);
    for (int t = 0; t < s; ++t) {
      int i = indices[t] - 1; // 0-based
      if (nums[i] > 0 && !seen[i]) {
        seen[i] = true;
        first[t] = i;
      }
    }

    int marks = 0;
    min_heap<int> min_heap{};
    int64_t heap_sum = 0LL;
    for (int t = s - 1; t >= 0; --t) {
      int i = first[t];
      if (i == -1) {
        // not first occurrence,
        // reserve second t for mark
        marks++;
        continue;
      }

      // first occurrence,
      // nums[i] becomes "reset" candidate
      min_heap.push(nums[i]);
      heap_sum += nums[i];

      if (marks > 0) {
        // have reserved "mark", so can spend
        // second t as "reset to zero" operation
        --marks;
        continue;
      }

      // can't use secont t as "set =0",
      // because there are no future mark slot

      // 1. discard one "reset" candidate
      // 2. use secont t as mark slot
      heap_sum -= min_heap.top();
      min_heap.pop();
      marks++;
    }

    // 1. if nums[i] marked via decrements => ops += nums[i] decs + 1 mark
    //    = (nums[i] + 1) total
    // 2. if nums[i] marked via reset => ops += 1 reset + 1 mark = 2 total
    // 3. start with ops = sum(nums[i]) decs + n marks (no resets)
    // 4. flip element to reset: ops += 1 - nums[i]
    // 5. flip all elements from heap costs: ops += heap.size() - heapSum
    // 6. must be: total <= s
    int64_t sum = accumulate(nums.begin(), nums.end(), 0LL);
    int64_t total = (sum - heap_sum) + (int64_t)n + (int64_t)min_heap.size();
    return total <= s;
  }

  int search(vector<int> const &nums, vector<int> const &indices, int l,
             int r) {
    // Inv1: s <  l => can't mark all
    // Inv2: s >= r =>  can  mark all
    while (l < r) {
      int s = l + (r - l) / 2;
      if (canMarkAll(nums, indices, s)) {
        r = s;
      } else {
        l = s + 1;
      }
    }
    return l;
  }

public:
  int earliestSecondToMarkIndices(vector<int> const &nums,
                                  vector<int> const &indices) {
    int n = (int)nums.size();
    int m = (int)indices.size();
    if (!canMarkAll(nums, indices, m))
      return -1;
    int s = search(nums, indices, n, m);
    return s;
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
  vector<int> nums, indices;
  int res, want;

  nums = {0, 0, 3, 0};
  indices = {2, 2, 2, 2, 2, 2, 3, 1};
  want = 7;
  res = s->earliestSecondToMarkIndices(nums, indices);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  nums = {0, 2};
  indices = {1, 1, 2, 2, 1};
  want = 4;
  res = s->earliestSecondToMarkIndices(nums, indices);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  nums = {3, 2, 3};
  indices = {1, 3, 2, 2, 2, 2, 3};
  want = 6;
  res = s->earliestSecondToMarkIndices(nums, indices);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  nums = {0, 0, 1, 2};
  indices = {1, 2, 1, 2, 1, 2, 1, 2};
  want = 7;
  res = s->earliestSecondToMarkIndices(nums, indices);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  nums = {1, 2, 3};
  indices = {1, 2, 3};
  want = -1;
  res = s->earliestSecondToMarkIndices(nums, indices);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  nums = {0, 0, 0};
  indices = {1};
  want = -1;
  res = s->earliestSecondToMarkIndices(nums, indices);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  nums = {2, 0, 0};
  indices = {1};
  want = -1;
  res = s->earliestSecondToMarkIndices(nums, indices);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  nums = {2, 0, 0};
  indices = {2};
  want = -1;
  res = s->earliestSecondToMarkIndices(nums, indices);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  nums = {10, 10, 9};
  indices = {1};
  want = -1;
  res = s->earliestSecondToMarkIndices(nums, indices);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
