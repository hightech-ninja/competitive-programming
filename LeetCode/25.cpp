#include <cassert>
#include <iostream>
#include <print>
#include <vector>

using namespace std;

/*
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
 * Time: O(n)
 * Space: O(groups) = O(n/k)
 */
class Solution {
private:
  int length(ListNode *node) {
    int len = 0;
    while (node != nullptr) {
      len++;
      node = node->next;
    }
    return len;
  }

  ListNode *next(ListNode *node, int steps) {
    while (steps-- > 0 && node != nullptr) {
      node = node->next;
    }
    return node;
  }

  void reverse(ListNode *from, ListNode *to) {
    ListNode *prev, *next;
    while (from != to) {
      next = from->next;
      from->next = prev;
      prev = from;
      from = next;
    }
  }

  ListNode *reverseKGroup(ListNode *head, int k, int length) {
    if (length < k) {
      return head;
    }
    // [head, tail] is first group of size k
    auto tail = next(head, k - 1);
    auto nextGroupHead = tail->next;
    reverse(head, nextGroupHead);
    head->next = reverseKGroup(nextGroupHead, k, length - k);
    return tail;
  }

public:
  ListNode *reverseKGroup(ListNode *head, int k) {
    return reverseKGroup(head, k, length(head));
  }
};

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

ListNode *toList(vector<int> const &nums) {
  auto root = new ListNode;
  auto node = root;
  for (int num : nums) {
    node->next = new ListNode(num);
    node = node->next;
  }
  return root->next;
}

vector<int> toVector(ListNode *root) {
  vector<int> res;
  while (root != nullptr) {
    res.push_back(root->val);
    root = root->next;
  }
  return res;
}

bool isEqual(ListNode *root, vector<int> const &nums) {
  for (int num : nums) {
    if (root->val != num)
      return false;
    root = root->next;
  }
  return true;
}

int main() {
  auto s = new Solution;
  ListNode *res;
  vector<int> want;

  want = {2, 1, 4, 3, 5};
  res = s->reverseKGroup(toList({1, 2, 3, 4, 5}), 2);
  println("res = {}\nwant={}", toVector(res), want);
  assert(isEqual(res, want));
  println("ok");

  want = {3, 2, 1, 4, 5};
  res = s->reverseKGroup(toList({1, 2, 3, 4, 5}), 3);
  println("res = {}\nwant={}", toVector(res), want);
  assert(isEqual(res, want));
  println("ok");

  want = {1, 2, 3, 4, 5};
  res = s->reverseKGroup(toList({1, 2, 3, 4, 5}), 1);
  println("res = {}\nwant={}", toVector(res), want);
  assert(isEqual(res, want));
  println("ok");

  want = {5, 4, 3, 2, 1};
  res = s->reverseKGroup(toList({1, 2, 3, 4, 5}), 5);
  println("res = {}\nwant={}", toVector(res), want);
  assert(isEqual(res, want));
  println("ok");

  return 0;
}
