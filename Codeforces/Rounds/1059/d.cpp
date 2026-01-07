#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <ranges>
#include <vector>

using namespace std;

int l_ans, r_ans;
vector<int> p, a;

void read_test(int n) {
  a.resize(n, 0);
  p.resize(n, 0);
  for (int i = 0; i < n; ++i) {
    cin >> p[i];
    a[i] = p[i];
  }
  cin >> l_ans >> r_ans;
  --l_ans;
  --r_ans;
  for (int i = l_ans; i <= r_ans; ++i)
    a[i]++;
}

void query(int type, int l, int r, int &res) {
#ifdef HACK
  res = 0;
  for (int i = l - 1; i < r; ++i) {
    if (type == 1) {
      res += p[i];
    } else {
      res += a[i];
    }
  }
#else
  println("{} {} {}", type, l, r);
  cout.flush();
  cin >> res;
#endif
}

int main() {
  auto predicate = [](int idx, int val) {
    int res1, res2;
    query(1, 1, idx + 1, res1);
    query(2, 1, idx + 1, res2);
    return res2 - res1 < val;
  };

  int t;
  cin >> t;

  while (t-- > 0) {
    int n;
    cin >> n;

#ifdef HACK
    read_test(n);
#endif
    int target = 1;
    auto rng = views::iota(0, n);
    auto it = ranges::lower_bound(rng, target, predicate);
    int ll = (it == rng.end() ? n : *it);

    int total;
    query(2, 1, n, total);
    int len = total - n * (n + 1) / 2;
    int rr = ll + len - 1;
    println("! {} {}", ll + 1, rr + 1);
#ifdef HACK
    assert(ll == l_ans);
    assert(rr == r_ans);
#endif
  }
  return 0;
}
