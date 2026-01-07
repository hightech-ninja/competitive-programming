#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private:
  ListNode *move(ListNode *head, int steps) {
    while (head != nullptr && steps > 0) {
      head = head->next;
      steps--;
    }
    return head;
  }

public:
  bool hasCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;

    do {
      slow = move(slow, 1);
      fast = move(fast, 2);
    } while (fast != nullptr && slow != fast);

    return fast != nullptr;
  }
};

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

ListNode *makeCycledList(vector<int> const &vals, int pos) {
  auto root = new ListNode(vals[0]);
  auto cur = root;
  for (int i = 1; i < (int)vals.size(); ++i) {
    cur->next = new ListNode(vals[i]);
    cur = cur->next;
  }
  if (pos == -1) {
    return root;
  }

  auto last = cur;
  cur = root;
  for (int i = 0; i < pos; ++i) {
    cur = cur->next;
  }
  last->next = cur;
  return root;
}

int main() {
  auto s = new Solution;
  ListNode *input;
  bool res, want;

  input = makeCycledList({3, 2, 0, -4}, 1);
  want = true;
  res = s->hasCycle(input);
  assert(res == want);
  println("ok");

  input = makeCycledList({1, 2}, 0);
  want = true;
  res = s->hasCycle(input);
  assert(res == want);
  println("ok");

  input = makeCycledList({1}, -1);
  want = false;
  res = s->hasCycle(input);
  assert(res == want);
  println("ok");

  return 0;
}
