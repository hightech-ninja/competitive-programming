#include <vector>
#include <cassert>
#include <print>

using namespace std;

void merge(vector<int>& nums, int l, int r, int mid) {
    vector<int> left(nums.begin() + l, nums.begin() + mid);
    vector<int> right(nums.begin() + mid, nums.begin() + r);

    int i = 0, j = 0, k = l;
    int n = (int)left.size();
    int m = (int)right.size();
    while (i < n && j < m) {
        if (left[i] < right[j]) {
            nums[k++] = left[i++];
        } else {
            nums[k++] = right[j++];
        }
    }
    while (i < n) {
        nums[k++] = left[i++];
    }
    while (j < n) {
        nums[k++] = right[j++];
    }
}

void merge_sort(vector<int>& nums, int l, int r) {
    if (l + 1 >= r) {
        return;
    }

    int m = (l + r) / 2;
    merge_sort(nums, l, m);
    merge_sort(nums, m, r);
    merge(nums, l, r, m);
}

void merge_sort(vector<int>& nums) {
    merge_sort(nums, 0, (int)nums.size());
}

int main() {
    vector<int> input, expected;

    input = {1, 2, 3, 4};
    expected = {1, 2, 3, 4};
    merge_sort(input);
    assert(input == expected);
    println("ok");

    input = {1, 2, 3, 4};
    expected = {1, 2, 3, 4};
    merge_sort(input);
    assert(input == expected);
    println("ok");

    input = {4, 3, 2, 1};
    expected = {1, 2, 3, 4};
    merge_sort(input);
    assert(input == expected);
    println("ok");

    input = {1, 3, 2, 4};
    expected = {1, 2, 3, 4};
    merge_sort(input);
    assert(input == expected);
    println("ok");

    input = {4, 1, 3, 2};
    expected = {1, 2, 3, 4};
    merge_sort(input);
    assert(input == expected);
    println("ok");

    return 0;
}
