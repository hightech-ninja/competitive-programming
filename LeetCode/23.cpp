#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
 * Time: O(nlogk)
 * Space: O(n) = # of merges
 */
class Solution {
private:
  ListNode *merge(ListNode *left, ListNode *right) {
    auto cur = new ListNode;
    auto root = cur;

    while (left != nullptr && right != nullptr) {
      if (left->val < right->val) {
        cur->next = left;
        left = left->next;
      } else {
        cur->next = right;
        right = right->next;
      }
      cur = cur->next;
    }
    if (left != nullptr) {
      cur->next = left;
    }
    if (right != nullptr) {
      cur->next = right;
    }

    return root->next;
  }
  ListNode *kWayMerge(vector<ListNode *> lists, int l, int r) {
    if (l == r)
      return nullptr;
    if (l + 1 == r)
      return lists[l];
    int mid = l + (r - l) / 2;
    auto left = kWayMerge(lists, l, mid);
    auto right = kWayMerge(lists, mid, r);
    return merge(left, right);
  }

public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    return kWayMerge(lists, 0, (int)lists.size());
  }
};

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

ListNode *makeList(vector<int> const &values) {
  auto list = new ListNode;
  auto root = list;
  for (int val : values) {
    list->next = new ListNode;
    list = list->next;
    list->val = val;
  }
  return root->next;
}

bool equal(ListNode *first, ListNode *second) {
  while (first != nullptr && second != nullptr) {
    if (first->val != second->val) {
      return false;
    }
    first = first->next;
    second = second->next;
  }
  return first == nullptr && second == nullptr;
}

int main() {
  auto s = new Solution;
  vector<ListNode *> input;
  ListNode *res, *want;

  want = makeList({1, 1, 2, 3, 4, 4, 5, 6});
  input = {makeList({1, 4, 5}), makeList({1, 3, 4}), makeList({2, 6})};
  res = s->mergeKLists(input);
  assert(equal(res, want));
  println("ok");

  want = nullptr;
  input = {};
  res = s->mergeKLists(input);
  assert(equal(res, want));
  println("ok");

  want = nullptr;
  input = {makeList({})};
  res = s->mergeKLists(input);
  assert(equal(res, want));
  println("ok");

  return 0;
}
