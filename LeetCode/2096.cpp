#include <cassert>
#include <iostream>
#include <print>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

/*
    Time: O(n)
    Space: O(h)
 */
class Solution {
private:
  bool findPath(TreeNode *root, int target, string &path) {
    if (root == nullptr) {
      return false;
    }
    if (root->val == target) {
      return true;
    }

    path.push_back('L');
    if (findPath(root->left, target, path)) {
      return true;
    }
    path[path.size() - 1] = 'R';
    if (findPath(root->right, target, path)) {
      return true;
    }
    path.pop_back();
    return false;
  }

public:
  string getDirections(TreeNode *root, int startValue, int destValue) {
    string pathToStart, pathToDest;
    findPath(root, startValue, pathToStart);
    findPath(root, destValue, pathToDest);

    int pos = 0;
    int m = (int)pathToStart.size();
    int k = (int)pathToDest.size();
    while (pos < m && pos < k && pathToStart[pos] == pathToDest[pos]) {
      ++pos;
    }
    pathToStart.erase(0, pos);
    pathToStart.assign(pathToStart.length(), 'U');
    pathToDest.erase(0, pos);
    return pathToStart + pathToDest;
  }
};

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

TreeNode *test1() {
  return new TreeNode(5, new TreeNode(1, new TreeNode(3), nullptr),
                      new TreeNode(2, new TreeNode(6), new TreeNode(4)));
}

TreeNode *test2() { return new TreeNode(2, new TreeNode(1), nullptr); }

int main() {
  auto s = new Solution;
  string res, want;

  want = "UURL";
  res = s->getDirections(test1(), 3, 6);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = "L";
  res = s->getDirections(test2(), 2, 1);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
