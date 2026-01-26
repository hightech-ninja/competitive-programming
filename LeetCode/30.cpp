#include <algorithm>
#include <cassert>
#include <iostream>
#include <print>
#include <unordered_map>
#include <vector>

using namespace std;

/*
 * Time: O(N * K + M * K^2)
 * Space: O(M * K)
 *
 */
class Solution {
private:
  void findSubstring(const string &s, vector<string> const &words, int start,
                     unordered_map<string_view, int> const &target,
                     vector<int> &pos) {
    int n = (int)s.size();
    int m = (int)words.size();
    int k = (int)words[0].size();
    int windowSize = m * k;

    unordered_map<string_view, int> freq = target;
    int deficit = freq.size();
    for (int i = start; i + k <= n; i += k) {
      // drop last word
      if (i >= start + windowSize) {
        // first word before the sliding window
        string_view prevWord(s.data() + i - windowSize, (size_t)k);
        if (freq.contains(prevWord)) {
          freq[prevWord]++;
          if (freq[prevWord] == 0)
            deficit--;
          if (freq[prevWord] == 1)
            deficit++;
        }
      }
      // include current word
      string_view word(s.data() + i, (size_t)k);
      if (freq.contains(word)) {
        freq[word]--;
        if (freq[word] == 0)
          deficit--;
        else if (freq[word] == -1)
          deficit++;
      }
      if (deficit == 0)
        pos.push_back(i - windowSize + k);
    }
  }

public:
  vector<int> findSubstring(string const &s, vector<string> const &words) {
    int k = (int)words[0].size();

    unordered_map<string_view, int> freq;
    for (string const &word : words) {
      freq[word]++;
    }

    vector<int> pos;
    for (int i = 0; i < k; ++i)
      findSubstring(s, words, i, freq, pos);
    return pos;
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
  vector<int> res, want;

  want = {13};
  res = s->findSubstring("lingmindraboofooowingdingbarrwingmonkeypoundcake",
                         {"fooo", "barr", "ding", "wing"});
  sort(res.begin(), res.end());
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {8};
  res = s->findSubstring("wordgoodgoodgoodbestword",
                         {"word", "good", "best", "good"});
  sort(res.begin(), res.end());
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {8};
  res = s->findSubstring("wordgoodgoodgoodbestword",
                         {"word", "good", "best", "good"});
  sort(res.begin(), res.end());
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {8};
  res = s->findSubstring("wordgoodgoodgoodbestword",
                         {"word", "good", "best", "good"});
  sort(res.begin(), res.end());
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {8};
  res = s->findSubstring("wordgoodgoodgoodbestword",
                         {"word", "good", "best", "good"});
  sort(res.begin(), res.end());
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {8};
  res = s->findSubstring("wordgoodgoodgoodbestword",
                         {"word", "good", "best", "good"});
  sort(res.begin(), res.end());
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {8};
  res = s->findSubstring("wordgoodgoodgoodbestword",
                         {"word", "good", "best", "good"});
  sort(res.begin(), res.end());
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {8};
  res = s->findSubstring("wordgoodgoodgoodbestword",
                         {"word", "good", "best", "good"});
  sort(res.begin(), res.end());
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {};
  res = s->findSubstring("wordgoodgoodgoodbestword",
                         {"word", "good", "best", "word"});
  sort(res.begin(), res.end());
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {0, 9};
  res = s->findSubstring("barfoothefoobarman", {"foo", "bar"});
  sort(res.begin(), res.end());
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {6, 9, 12};
  res = s->findSubstring("barfoofoobarthefoobarman", {"bar", "foo", "the"});
  sort(res.begin(), res.end());
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {0};
  res = s->findSubstring("barfoothe", {"bar", "foo", "the"});
  sort(res.begin(), res.end());
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  return 0;
}
