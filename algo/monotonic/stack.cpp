#include <cassert>
#include <print>
#include <stack>
#include <vector>

using namespace std;

/*
NGE via monotonic stack (decreasing by value):

Intuition:
  - We scan left->right and keep a stack of indices whose NGE is unknown.
  - When a new value a[i] arrives and a[i] > a[stack.top()],
    it "finalizes" (resolves) the NGE for that top immediately:
    the current i is the nearest greater to the right for that popped index.

Invariants:
  - Indices on stack are strictly increasing (older at bottom, newer at top).
  - Values are non-increasing bottom->top: a[st[0]] >= ... >= a[st.top()].
  - Stack holds exactly the indices whose NGE is not yet determined.

Update rule at i:
  - While stack not empty and a[stack.top()] < a[i]:
      ans[stack.top()] = i;  // finalization happens DURING the pop
      stack.pop();
  - Push i.

Notes:
  - Equality policy: use '<' for strict NGE; use '<=' for next greater-or-equal.
  - After the scan, any remaining indices never found a greater → ans = -1.
  - Complexity: each index is pushed once and popped at most once -> O(n).
*/

vector<int> next_greater_element(vector<int> const &nums) {
  int n = (int)nums.size();
  vector<int> nge(n, -1);
  stack<int> st;
  for (int r = 0; r < n; ++r) {
    while (!st.empty() && nums[st.top()] < nums[r]) {
      int l = st.top();
      st.pop();
      nge[l] = r;
    }
    st.push(r);
  }
  return nge;
}

/*
PLE via monotonic stack (increasing by value):

Intuition:
  - For each a[i], we want its nearest smaller on the left.
  - Maintain a stack of indices with strictly increasing values.
    Any value >= a[i] is infeasible to be "previous less" for i,
    so we pop until only a strictly smaller remains.
  - Only AFTER the popping loop ends do we finalize PLE[i] as the current stack
top.

Invariants:
  - Indices on stack are strictly increasing (older at bottom, newer at top).
  - Values are strictly increasing bottom->top: a[st[0]] < ... < a[st.top()].
  - The stack stores feasible candidates that could serve as "previous less"
    for some future index; popped entries were invalidated by the current a[i].

Update rule at i:
  - While stack not empty and a[stack.top()] >= a[i]:
      stack.pop();            // prune infeasible (not strictly less than a[i])
  - PLE[i] = (stack.empty() ? -1 : stack.top());  // finalization happens AFTER
popping
  - Push i.

Notes:
  - Equality policy: for strict PLE (<) use '>=', for PLE-or-equal (<=) use '>'.
  - Popped elements are NOT being finalized here; we only finalize the CURRENT
i.
  - Remaining stack entries simply didn’t encounter a smaller-to-the-right that
would pop them.
  - Complexity: each index is pushed once and popped at most once -> O(n).
*/

vector<int> prev_less_element(vector<int> const &nums) {
  int n = (int)nums.size();
  vector<int> ple(n, -1);
  stack<int> st;
  for (int r = 0; r < n; ++r) {
    while (!st.empty() && nums[st.top()] >= nums[r]) {
      st.pop();
    }
    int l = (st.empty() ? -1 : st.top());
    ple[r] = l;
    st.push(r);
  }
  return ple;
}

int main() {
  vector<pair<vector<int>, vector<int>>> tests;

  println("Next Greater Element...");
  tests = {
      {{1, 2, 3, 4}, {1, 2, 3, -1}},
      {{4, 3, 2, 1}, {-1, -1, -1, -1}},
      {{5, 5, 5}, {-1, -1, -1}},
      {{7}, {-1}},
      {{2, 6, 4, 8}, {1, 3, 3, -1}},
      {{2, 2, 3, 2, 4}, {2, 2, 4, 4, -1}},
      {{2, 1, 1, 1, 3}, {4, 4, 4, 4, -1}},
      {{5, 1, 5, 1, 5}, {-1, 2, -1, 4, -1}},
      {{-1, -3, 0, -2, 2}, {2, 2, 4, 4, -1}},
      {{2, 5, 3, 1, 6}, {1, 4, 4, 4, -1}},
      {{3, 3, 4}, {2, 2, -1}},
      {{2, 3, 3}, {1, -1, -1}},
  };
  for (auto const &test : tests) {
    auto [nums, want] = test;
    auto got = next_greater_element(nums);
    if (want != got) {
      println("nums:\t{}", nums);
      println("want:\t{}", want);
      println("got:\t{}", got);
      assert(false);
    }
  }
  println("OK");

  println("Previous Less Element...");
  tests = {
      {{1, 2, 3, 4}, {-1, 0, 1, 2}},
      {{4, 3, 2, 1}, {-1, -1, -1, -1}},
      {{5, 5, 5}, {-1, -1, -1}},
      {{7}, {-1}},
      {{2, 6, 4, 8}, {-1, 0, 0, 2}},
      {{2, 2, 3, 2, 4}, {-1, -1, 1, -1, 3}},
      {{2, 1, 1, 1, 3}, {-1, -1, -1, -1, 3}},
      {{5, 1, 5, 1, 5}, {-1, -1, 1, -1, 3}},
      {{-1, -3, 0, -2, 2}, {-1, -1, 1, 1, 3}},
      {{2, 5, 3, 1, 6}, {-1, 0, 0, -1, 3}},
      {{3, 3, 4}, {-1, -1, 1}},
      {{2, 3, 3}, {-1, 0, 0}},
  };
  for (auto const &test : tests) {
    auto [nums, want] = test;
    auto got = prev_less_element(nums);
    if (want != got) {
      println("nums:\t{}", nums);
      println("want:\t{}", want);
      println("got:\t{}", got);
      assert(false);
    }
  }
  println("OK");

  return 0;
}
