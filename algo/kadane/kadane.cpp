#include <functional>
#include <map>
#include <print>
#include <vector>

using namespace std;

[[maybe_unused]] int kadanes_geometry_view(vector<int> const &arr) {
  long long ans = LLONG_MIN;
  long long sum = 0LL, minPrefSum = 0LL;
  for (int i = 0; i < (int)arr.size(); ++i) {
    sum += arr[i];
    ans = max(ans, sum - minPrefSum);
    minPrefSum = min(minPrefSum, sum);
  }
  return ans;
}

[[maybe_unused]] int kadanes_dp_view(vector<int> const &arr) {
  long long best = 0;
  long long bestSoFar = arr[0];
  for (int i = 0; i < (int)arr.size(); ++i) {
    best = max(best + arr[i], (long long)arr[i]);
    bestSoFar = max(bestSoFar, best);
  }
  return bestSoFar;
}

int main() {
  map<string, function<int(vector<int> const &)>> solutions;

  solutions["Geometry view"] = kadanes_geometry_view;
  solutions["DP view"] = kadanes_dp_view;

  vector<pair<int, vector<int>>> tests{
      {5, {5}},
      {-5, {-5}},
      {3, {1, 2}},
      {-1, {-2, -1}},
      {0, {0, 0, 0}},
      {0, {-1, 0, -2, 0}},
      {6, {-2, 1, -3, 4, -1, 2, 1, -5, 4}},
      {3, {-1, 2, -1, 2, -1}},
      {5, {5, -1, -2}},
      {5, {-2, -1, 5}},
      {4, {2, -1, 2, -1, 2, -1}},
      {-2, {-8, -3, -6, -2, -5, -4}},
      {50, {10, -100, 20, 30}},
      {2, {-1, 2}},
      {3, {2, -1, 2}},
      {0, {-1, 0, 0, 0}},
      {100, {-5, -1, 100, -50, -1}},
      {101, {-2, 3, 5, -1, 4, -10, 100}},
  };

  for (auto s : solutions) {
    for (auto test : tests) {
      vector<int> input = test.second;
      int want = test.first;
      int got = s.second(input);
      if (want != got) {
        println("{} kadane's solution failed", s.first);
        println("input = {}", input);
        println("want = {}, got = {}", want, got);
        exit(1);
      }
    }
  }

  return 0;
}
