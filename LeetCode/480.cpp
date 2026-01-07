#include <cassert>
#include <print>
#include <set>
#include <vector>

using namespace std;

class Solution {
private:
  /*
   * Inv1: lo <= hi
   * Inv2: |lo| = ceil(k/2), |hi| = floor(k/2)
   */
  multiset<int> lo, hi;

  void init() {
    lo.clear();
    hi.clear();
  }
  void rebalance(int k) {
    int size = (int)lo.size() + (int)hi.size();
    int loSize = (k + 1) / 2;
    if (size < loSize) {
      // insufficient size
      return;
    }
    while ((int)lo.size() > loSize) {
      auto it = prev(lo.end());
      hi.insert(*it);
      lo.erase(it);
    }
    while ((int)lo.size() < loSize) {
      auto it = hi.begin();
      lo.insert(*it);
      hi.erase(it);
    }
  }
  void erase(int val, int k) {
    if (!lo.empty() && val <= *lo.rbegin()) {
      lo.erase(lo.find(val));
    } else {
      hi.erase(hi.find(val));
    }
    rebalance(k);
  }
  void insert(int val, int k) {
    if (lo.empty() || val <= *lo.rbegin()) {
      lo.insert(val);
    } else {
      hi.insert(val);
    }
    rebalance(k);
  }
  double median(int k) {
    if (k & 1) {
      return (double)*lo.rbegin();
    }
    return ((double)*lo.rbegin() + (double)*hi.begin()) / 2.0;
  }

public:
  vector<double> medianSlidingWindow(vector<int> const &nums, int k) {
    init();
    int n = (int)nums.size();
    vector<double> ans;
    ans.reserve(n - k + 1);
    for (int i = 0; i + 1 < k; ++i) {
      insert(nums[i], k);
    }
    for (int i = k - 1; i < n; ++i) {
      insert(nums[i], k);
      ans.push_back(median(k));
      erase(nums[i - k + 1], k);
    }
    return ans;
  }
};

int main() {
  auto s = new Solution;
  vector<double> res, expected;

  res = s->medianSlidingWindow({1, 3, -1, -3, 5, 3, 6, 7}, 3);
  expected = {1.0, -1.0, -1.0, 3.0, 5.0, 6};
  println("res={}; expected={}", res, expected);
  assert(res == expected);
  println("ok");

  res = s->medianSlidingWindow({1, 2, 3, 4, 2, 3, 1, 4, 2}, 3);
  expected = {2.0, 3.0, 3.0, 3.0, 2.0, 3.0, 2.0};
  println("res={}; expected={}", res, expected);
  assert(res == expected);
  println("ok");

  return 0;
}
