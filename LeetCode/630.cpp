#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <queue>
#include <vector>

using namespace std;

/*
 * Time: O(nlogn)
 * Space: O(n)
 */
class Solution {
public:
  int scheduleCourse(vector<vector<int>> &courses) {
    sort(courses.begin(), courses.end(),
         [](vector<int> const &a, vector<int> const &b) {
           if (a[1] != b[1])
             return a[1] < b[1];
           return a[0] < b[0];
         });

    int totalTime = 0;
    int n = (int)courses.size();
    priority_queue<int> heap; // max-heap
    for (auto const &course : courses) {
      int time = course[0];
      int deadline = course[1];
      totalTime += time;
      heap.push(time);
      if (totalTime > deadline) {
        totalTime -= heap.top();
        heap.pop();
      }
    }
    return (int)heap.size();
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
  vector<vector<int>> input;
  int res, want;

  want = 2;
  input = {{5, 5}, {4, 6}, {2, 6}};
  res = s->scheduleCourse(input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 2;
  input = {{1, 2}, {2, 3}};
  res = s->scheduleCourse(input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 3;
  input = {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};
  res = s->scheduleCourse(input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 1;
  input = {{1, 2}};
  res = s->scheduleCourse(input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 0;
  input = {{3, 2}, {4, 3}};
  res = s->scheduleCourse(input);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
