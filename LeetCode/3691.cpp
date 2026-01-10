#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <print>
#include <queue>
#include <vector>

using namespace std;

template <size_t N> constexpr array<size_t, N + 1> make_lg() {
  array<size_t, N + 1> lg{};
  for (size_t i = 2; i <= N; ++i)
    lg[i] = lg[i / 2] + 1;
  return lg;
}

constexpr size_t MAX_N = 50'000;
constexpr auto lg = make_lg<MAX_N>();

template <class T> class SparseTable {
public:
  using operation_t = function<T(T const &, T const &)>;

private:
  operation_t _op;
  vector<vector<T>> _table; // = _op[i, i+2^k)

  template <class It> void init(It first, It last) {
    size_t n = distance(first, last);
    if (n == 0) {
      _table.clear();
      return;
    }

    size_t K = lg[n] + 1;
    _table.resize(K, vector<T>(n, T{}));
    copy(first, last, _table[0].begin());

    for (size_t k = 1; k < K; ++k) {
      size_t half = 1 << (k - 1);
      size_t m = n - (1 << k) + 1;
      for (size_t i = 0; i < m; ++i)
        _table[k][i] = _op(_table[k - 1][i], _table[k - 1][i + half]);
    }
  }

public:
  SparseTable() = default;

  template <class It>
  explicit SparseTable(operation_t op, It first, It last) : _op(op) {
    init(first, last);
  }

  // get result of operation_t on [l, r)
  T get(T l, T r) const {
    int len = r - l;
    int k = lg[len];
    return _op(_table[k][l], _table[k][r - (1 << k)]);
  }
};

/*
 * Time: O(NlogN + Klog(N^2))
 * Space: O(NlogN)
 */
class Solution {
private:
  template <class T> using max_heap = priority_queue<T>;

public:
  long long maxTotalValue(vector<int> const &nums, int k) {
    SparseTable<int> mn([](int a, int b) { return min(a, b); }, nums.cbegin(),
                        nums.cend());
    SparseTable<int> mx([](int a, int b) { return max(a, b); }, nums.cbegin(),
                        nums.cend());
    auto value = [&](pair<int, int> interval) {
      return mx.get(interval.first, interval.second) -
             mn.get(interval.first, interval.second);
    };
    auto less = [&value](pair<int, int> const &a, pair<int, int> const &b) {
      return value(a) < value(b);
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(less)>
        max_heap(less);
    int n = (int)nums.size();
    for (int l = 0; l < n; ++l)
      max_heap.push({l, n});

    long long ans = 0;
    while (k-- > 0 && !max_heap.empty()) {
      auto interval = max_heap.top();
      max_heap.pop();
      ans += value(interval);

      if (interval.second - interval.first > 1)
        max_heap.push({interval.first, interval.second - 1});
    }
    return ans;
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
  vector<int> nums;
  int res, want;

  want = 4;
  res = s->maxTotalValue({1, 3, 2}, 2);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = 12;
  res = s->maxTotalValue({4, 2, 5, 1}, 3);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
