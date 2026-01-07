#include <numeric>
#include <print>
#include <string>
#include <vector>
#include <random>

int gcd(int a, int b) {
  a = abs(a);
  b = abs(b);
  while (b != 0) {
    int c = a % b;
    a = b;
    b = c;
  }
  return a;
}

// Core property: LCM(a,b) = a * b / gcd(a, b)
int lcm(int a, int b) {
  if (a == 0 || b == 0)
    return 0;
  a = abs(a);
  b = abs(b);
  return a / gcd(a, b) * b;
}

static void require(bool ok, std::string msg) {
  if (!ok) {
    std::println("TEST FAILED: {}", msg);
    std::abort();
  }
}

static void check_pair(int a, int b) {
  const int g = gcd(a, b);
  const int L = lcm(a, b);

  require(g == std::gcd(a, b), "gcd matches std::gcd");
  require(L == std::lcm(a, b), "lcm matches std::lcm");
  require(L >= 0, "lcm is non-negative");
  require(lcm(a, b) == lcm(b, a), "symmetry - lcm(a,b) == lcm(b,a)");

  // Zero rules
  if (a == 0 || b == 0) {
    require(L == 0, "lcm(a,0) == 0 and lcm(0,b) == 0");
    return; // other divisibility properties are trivial/degenerate
  }

  // Divisibility: L is a multiple of both |a| and |b|
  require(L % std::abs(a) == 0, "lcm divisible by |a|");
  require(L % std::abs(b) == 0, "lcm divisible by |b|");

  // Fundamental relation (when representable): gcd(a,b) * lcm(a,b) == |a*b|
  {
    int aa = std::abs(a);
    int bb = std::abs(b);
    int left = (long long)g * (long long)L;
    int right = aa * bb;
    require(left == right, "gcd*lcm == |a*b|");
  }
}

int main() {
  // 1) Hand-picked rich cases (signs, zeros, coprimes, composites)
  {
    const std::vector<std::pair<int, int>> cases = {
        {0, 0},
        {0, 1},
        {1, 0},
        {0, -7},
        {-7, 0},

        {1, 1},
        {2, 3},
        {6, 4},   // lcm=12
        {21, 6},  // lcm=42
        {12, 18}, // lcm=36

        {-2, 3},  // lcm=6
        {2, -3},  // lcm=6
        {-2, -3}, // lcm=6
        {-6, 4},  // lcm=12
        {6, -4},  // lcm=12
        {-6, -4}, // lcm=12

        {17, 31}, // coprime
        {97, 97}, // equal primes

        // Near sqrt(INT_MAX) to stress overflow boundaries safely.
        {46340, 46340},
        {46340, 46339}, // coprime-ish; lcm close to product, still fits int
        {-46340, 46339},
    };

    for (auto [a, b] : cases)
      check_pair(a, b);
  }

  // 2) Structured adversarial-ish cases: consecutive Fibonacci numbers (often
  // coprime) Keep them within safe int range and product range by limiting
  // size.
  {
    int f1 = 1, f2 = 1;
    for (int i = 0; i < 22; ++i) {
      check_pair(f1, f2);
      int f3 = f1 + f2;
      f1 = f2;
      f2 = f3;
    }
  }

  // 3) Deterministic random property tests within safe range
  // Range chosen so |a*b| <= INT_MAX (approx), hence lcm also fits.
  {
    std::mt19937 rng(0xC0FFEE);
    std::uniform_int_distribution<int> dist(-46340, 46340);

    for (int it = 0; it < 50'000; ++it) {
      int a = dist(rng);
      int b = dist(rng);
      check_pair(a, b);
    }
  }

  std::println("All tests passed.");
  return 0;
}
