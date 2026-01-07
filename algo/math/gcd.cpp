#include <numeric>
#include <print>
#include <random>
#include <string>
#include <vector>

// Core property: Euclid recurrence - gcd(a, b) = gcd(b, a%b).
//
// Notes:
//  - returns non-negative GCD
//  - Works for any signed/unsigned integers
int gcd(int a, int b) {
  a = abs(a);
  b = abs(b);
  // if a < b, first iteration swaps a, b; otherwise, a and b decreasing,
  // and loop finishes when b reaches zero.
  while (b != 0) {
    int c = a % b;
    a = b;
    b = c;
  }
  return a;
}

static void require(bool ok, std::string msg) {
  if (!ok) {
    std::println("TEST FAILED: {}", msg);
    std::abort();
  }
}

static void check_pair(int a, int b) {
  int g = gcd(a, b);

  int std_g = std::gcd(a, b);
  require(g == std_g, "matches std::gcd");
  require(gcd(a, b) == gcd(b, a), "symmetry - gcd(a,b) == gcd(b,a)");

  if (g == 0) {
    require(a == 0 && b == 0, "g==0 only for (0,0)");
  } else {
    require(a % g == 0, "g divides a");
    require(b % g == 0, "g divides b");
  }

  if (b != 0) {
    require(g == gcd(b, a % b), "Euclid recurrence gcd(a,b) == gcd(b,a%b)");
  }
}

int main() {
  // 1) Hand-picked edge cases / classics
  {
    const std::vector<std::pair<std::int64_t, std::int64_t>> cases = {
        {0, 0},
        {0, 1},
        {1, 0},
        {0, 42},
        {42, 0},
        {1, 1},
        {2, 1},
        {1, 2},
        {6, 4},
        {54, 24},
        {48, 18},
        {17, 31},  // coprime primes
        {97, 97},  // equal primes
        {-12, 18}, // negatives
        {12, -18},
        {-12, -18},
        {7, 0},
        {0, -7},

        // Large-ish values
        {1'000'000'007, 1'000'000'009}, // coprime (typically)
        // {9'223'372'036'854'775'807LL, 1},   // LLONG_MAX with 1
        // {9'223'372'036'854'775'807LL, 3},   // LLONG_MAX with small
    };

    for (auto [a, b] : cases)
      check_pair(a, b);
  }

  // 2) Adversarial structured cases: consecutive Fibonacci numbers
  // Euclid takes many iterations here.
  {
    int f1 = 1, f2 = 1;
    for (int i = 0; i < 47; ++i) {
      check_pair(f1, f2);
      int f3 = f1 + f2;
      f1 = f2;
      f2 = f3;
    }
  }

  // 3) Random property-based tests (deterministic seed)
  {
    std::mt19937_64 rng(0xC0FFEE);
    std::uniform_int_distribution<int> dist(-1'000'000'000, 1'000'000'000);

    for (int it = 0; it < 50'000; ++it) {
      int a = dist(rng);
      int b = dist(rng);
      check_pair(a, b);
    }
  }

  std::println("All tests passed.");
  return 0;
}
