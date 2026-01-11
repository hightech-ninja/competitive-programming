#include <array>
#include <functional>
#include <initializer_list>
#include <print>

using namespace std;

template <size_t N> consteval array<size_t, N + 1> make_lg() {
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

  SparseTable(operation_t op, initializer_list<T> list) : _op(op) {
    init(list.begin(), list.end());
  }

  // get result of operation on [l, r)
  T get(T l, T r) const {
    int len = r - l;
    int k = lg[len];
    return _op(_table[k][l], _table[k][r - (1 << k)]);
  }
};
