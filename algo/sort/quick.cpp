#include <vector>
#include <print>
#include <cassert>
#include <random>
#include <algorithm>

using namespace std;

// Gives O(n^2) for descending sorted array
[[maybe_unused]] int partition_last(vector<int>& nums, int l, int r) {
     /*
      Invariant:
         1. i <   wall => nums[i] <= pivot;
         2. i >=  wall => nums[i] >  pivot;
      */
    int wall = l, pivot = nums[r-1];
    for (int i = l; i+1 < r; ++i) {
        if (nums[i] <= pivot) {
            swap(nums[i], nums[wall]);
            ++wall;
        }
    }
    /*
     Invariant:
        3. At the end pivot stands on its sorted position;
     */
    swap(nums[wall], nums[r-1]);
    return wall;
}

// Gives O(n^2) for ascending sorted array
[[maybe_unused]] int partition_first(vector<int>& nums, int l, int r) {
    /*
     Invariant:
        1. i <= wall => nums[i] <= pivot;
        2. i > wall  => nums[i] >  pivot;
     */
    int wall = l, pivot = nums[l];
    for (int i = l + 1; i < r; ++i) {
        if (nums[i] <= pivot) {
            swap(nums[i], nums[++wall]);
        }
    }
    /*
     Invariant:
        3. At the end pivot stands on its sorted position;
     */
    swap(nums[l], nums[wall]);
    return wall;
}

int median_of_three(vector<int>& nums, int l, int r) {
    int mid = (l + r) / 2;
    if (nums[l] > nums[mid])
        swap(nums[l], nums[mid]); // nums[l] <= nums[mid]
    if (nums[mid] > nums[r])
        swap(nums[mid], nums[r]); // nums[mid] <= nums[r], but ^ can be broken
    if (nums[l] > nums[mid])
        swap(nums[l], nums[mid]);
    return mid;
}

// Gives O(n^2) in the worst case, but with low probability
// because median of first, middle and last elements is closer
// to the actual median value, then first or last element.
[[maybe_unused]] int partition_median(vector<int>& nums, int l, int r) {
    int mid = median_of_three(nums, l, r);
    int pivot = nums[mid];
    swap(nums[mid], nums[r-1]);

    int wall = l;
    /*
      1. i <  wall => nums[i] <= pivot
      2. i >= wall => nums[i] > pivot
     */
    for (int i = l; i + 1 < r; ++i) {
        if (nums[i] <= pivot) {
            swap(nums[wall], nums[i]);
            ++wall;
        }
    }
    // 3. put pivot on its sorted position
    swap(nums[wall], nums[r - 1]);
    return wall;
}

// Gives O(n^2) in the worst case, but with expotentially low probability
[[maybe_unused]] int partition_random(vector<int>& nums, int l, int r) {
    int pivot_idx = l + (rand() % (r-l));
    swap(nums[pivot_idx], nums[r - 1]);

    /*
     Invariants:
        1. i < wall => nums[i] <= pivot
        2. i >= wall => nums[i] > pivot
     */
    int pivot = nums[r - 1];
    int wall = l;
    for (int i = l; i+1 < r; ++i) {
        if (nums[i] <= pivot) {
            swap(nums[i], nums[wall]);
            wall++;
        }
    }
    /*
     Invariant:
        3. At the end pivot stands on its sorted position;
     */
    swap(nums[wall], nums[r-1]);
    return wall;
}

void quick_sort(vector<int>& nums, int l, int r) {
    if (l < r) {
        int mid = partition_median(nums, l, r);
        quick_sort(nums, l, mid);
        quick_sort(nums, mid+1, r);
    }
}

void quick_sort(vector<int>& nums) {
    quick_sort(nums, 0, (int)nums.size());
}

int main() {
    vector<int> input, expected;

    input = {1, 2, 3, 4};
    expected = {1, 2, 3, 4};
    quick_sort(input);
    assert(is_sorted(input.begin(), input.end()));
    println("ok");

    input = {1, 2, 3, 4};
    expected = {1, 2, 3, 4};
    quick_sort(input);
    assert(is_sorted(input.begin(), input.end()));
    println("ok");

    input = {4, 3, 2, 1};
    expected = {1, 2, 3, 4};
    quick_sort(input);
    assert(is_sorted(input.begin(), input.end()));
    println("ok");

    input = {1, 3, 2, 4};
    expected = {1, 2, 3, 4};
    quick_sort(input);
    assert(is_sorted(input.begin(), input.end()));
    println("ok");

    input = {4, 1, 3, 2};
    quick_sort(input);
    assert(is_sorted(input.begin(), input.end()));
    println("ok");

    {
        int tt = 1000, n = 100'000, min_val = 1, max_val = 1'000'000;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(min_val, max_val);
        input.resize(n);
        for (int t = 0; t < tt; ++t) {
            for (int& val : input) {
                val = dis(gen);
            }
        }
        quick_sort(input);
        assert(is_sorted(input.begin(), input.end()));
    }

    return 0;
}
