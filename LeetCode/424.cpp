#include <print>
#include <cassert>
#include <string>
#include <iostream>

using namespace std;

class Solution {
private:
    static const int alphaLen = 26;
    static const char firstLetter = 'A';
public:
    int characterReplacement(string s, int k) {
        array<int, alphaLen> freq{};
        int ans = 0;
        auto isValid = [&freq, k](int l, int r) {
            int len = r - l + 1;
            int maxFreq = *max_element(freq.begin(), freq.end());
            return len - maxFreq <= k;
        };
        for (int l = 0, r = 0; r < (int)s.size(); ++r) {
            freq[s[r] - firstLetter]++;
            while (l < r && !isValid(l, r)) {
                freq[s[l] - firstLetter]--;
                l++;
            }
            ans = max(ans, r - l + 1);
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
    int res;

    res = s->characterReplacement("ABAB", 2);
    println("res={}", res);
    assert(res == 4); println("ok");

    res = s->characterReplacement("AABABBA", 1);
    println("res={}", res);
    assert(res == 4); println("ok");

    res = s->characterReplacement("BBAACDAEAA", 3);
    println("res={}", res);
    assert(res == 8); println("ok");

    return 0;
}
