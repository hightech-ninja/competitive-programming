#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
    Time: O(n) - avg, O(n^2) worst-case
    Space: O(1)
 */
class Solution {
public:
  int quickSelect(vector<int> &nums, int k) {
    int l = 0, r = (int)nums.size() - 1;
    while (true) {
      swap(nums[l + (rand() % (r - l + 1))], nums[r]);
      int pivot = nums[r];
      int lt = l, gt = r;
      for (int i = l; i <= gt;) {
        if (nums[i] < pivot) {
          swap(nums[lt++], nums[i++]);
        } else if (nums[i] > pivot) {
          swap(nums[i], nums[gt--]);
        } else {
          ++i;
        }
      }

      if (k < lt)
        r = lt - 1;
      else if (k > gt)
        l = gt + 1;
      else
        return nums[k];
    }
  }

  int findKthLargest(vector<int> &nums, int k) {
    return quickSelect(nums, (int)nums.size() - k);
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
  int want, res;

  input = {3, 2, 1, 5, 6, 4};
  want = 5;
  res = s->findKthLargest(input, 2);
  assert(res == want);
  println("ok");

  input = {3, 2, 3, 1, 2, 4, 5, 5, 6};
  want = 4;
  res = s->findKthLargest(input, 4);
  assert(res == want);
  println("ok");

  return 0;
}
