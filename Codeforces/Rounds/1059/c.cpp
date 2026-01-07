#include <bitset>
#include <iostream>
#include <print>

using namespace std;

int main() {
  int t;
  cin >> t;
  for (; t > 0; t--) {
    int a, b;
    cin >> a >> b;
    if (a == b) {
      println("0");
      continue;
    }

    bitset<32> aa(a), bb(b);
    int pos_a = 0;
    for (int i = 31; i >= 0; --i) {
      if (aa.test(i)) {
        pos_a = i;
        break;
      }
    }
    int pos_b = 0;
    for (int i = 31; i >= 0; --i) {
      if (bb.test(i)) {
        pos_b = i;
        break;
      }
    }
    if (pos_a < pos_b) {
      println("-1");
      continue;
    }

    bitset<32> x1 = aa ^ bb;
    if (bb.test(pos_a)) {
      println("1");
      println("{}", x1.to_ulong());
    } else {
      x1.set(pos_a, false);
      unsigned long long x2 = 1LL << pos_a;
      println("2");
      println("{} {}", x1.to_ulong(), x2);
    }
  }
  return 0;
}

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();
