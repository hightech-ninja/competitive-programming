#include <print>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    int reversePairsBetween(vector<int> const& left, vector<int> const& right) {
        int ans = 0;
        int n = (int)left.size(), m = (int)right.size();
        int j = 0;
        for (int i = 0; i < n; ++i) {
            while (j < m && left[i] > 2LL * right[j]) {
                ++j;
            }
            ans += j;
        }
        return ans;
    }
    int merge(vector<int>& nums, int l, int r, int m) {
        vector<int> left(m - l), right(r - m);
        for (int i = l; i < m; ++i) {
            left[i-l] = nums[i];
        }
        for (int j = m; j < r; ++j) {
            right[j-m] = nums[j];
        }

        int between = reversePairsBetween(left, right);

        int i = 0, j = 0, k = l;
        while (i < (int)left.size() && j < (int)right.size()) {
            if (left[i] < right[j]) {
                nums[k++] = left[i];
                i++;
            } else {
                nums[k++] = right[j];
                j++;
            }
        }
        while (i < (int)left.size()) {
            nums[k++] = left[i];
            i++;
        }
        while (j < (int)right.size()) {
            nums[k++] = right[j];
            j++;
        }

        return between;
    }

    int reversePairs(vector<int>& nums, int l, int r) {
        if (l + 1 >= r) {
            return 0;
        }
        int m = l + (r - l) / 2;
        int left = reversePairs(nums, l, m);
        int right = reversePairs(nums, m, r);
        int between = merge(nums, l, r, m);
        return left + right + between;
    }
public:
    int reversePairs(vector<int> & nums) {
        return reversePairs(nums, 0, (int)nums.size());
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
    vector<int> input;
    int res, want;

    input = {1, 3, 2, 3, 1};
    res = s->reversePairs(input);
    want = 2;
    println("res= {}\nwant={}", res, want);
    assert(res == want); println("ok");

    input = {2, 4, 3, 5, 1};
    res = s->reversePairs(input);
    want = 3;
    println("res= {}\nwant={}", res, want);
    assert(res == want); println("ok");

    return 0;
}
