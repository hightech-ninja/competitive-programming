#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Time: O(n)
 * Space: O(1)
 */
class Solution {
public:
  bool lemonadeChange(vector<int> const &bills) {
    int fives = 0;
    int tens = 0;
    for (int bill : bills) {
      if (bill == 5) {
        fives++;
      } else if (bill == 10) {
        tens++;
      }

      int ret = bill - 5;
      if (ret == 5) { // bill = 10
        if (fives == 0)
          return false;
        fives--;
      } else if (ret == 15) { // bill = 20
        if (tens > 0 && fives > 0) {
          tens--;
          fives--;
        } else if (fives > 2) {
          fives -= 3;
        } else {
          return false;
        }
      }
    }
    return true;
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
  bool want, res;

  want = true;
  res = s->lemonadeChange({5, 5, 5, 10, 20});
  assert(res == want);
  println("ok");

  want = false;
  res = s->lemonadeChange({5, 5, 10, 10, 20});
  assert(res == want);
  println("ok");

  return 0;
}
