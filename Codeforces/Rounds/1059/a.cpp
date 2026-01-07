#include <iostream>
#include <print>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int t;
  cin >> t;
  for (int tt = 0; tt < t; ++tt) {
    int n;
    cin >> n;
    vector<int> a(n, 0);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    println("{}", *max_element(a.begin(), a.end()));
  }
  return 0;
}

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();
