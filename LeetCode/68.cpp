#include <cassert>
#include <iostream>
#include <iterator>
#include <print>
#include <string>
#include <vector>

using namespace std;

/*
 * Time:
 * Space:
 * Solution:
 */
class Solution {
private:
  template <class It> int wordsLength(It from, It to) {
    int ans = 0;
    while (from != to) {
      ans += (*from).size();
      ++from;
    }
    return ans;
  }
  template <class It> string justifyEvenly(It from, It to, int maxWidth) {
    int buckets = distance(from, to) - 1;
    if (buckets == 0) {
      return justifyLeft(from, to, maxWidth);
    }

    int words = wordsLength(from, to);
    int free = maxWidth - words;
    int bucketSize = free / buckets;
    int border = free % buckets;

    string res;
    res.reserve(maxWidth);

    int bucket = 0;
    for (; from != to; ++from, ++bucket) {
      res += *from;
      if (bucket < buckets)
        res += string(bucketSize + (bucket < border), ' ');
    }

    return res;
  }
  template <class It> string justifyLeft(It from, It to, int maxWidth) {
    string res;
    res.reserve(maxWidth);
    for (; from != to; ++from) {
      res += *from;
      if (next(from) != to)
        res += ' ';
    }
    res += string(maxWidth - (int)res.size(), ' ');
    return res;
  }

public:
  vector<string> fullJustify(vector<string> const &words, int maxWidth) {
    int n = (int)words.size();

    // 1. partition
    vector<int> pos;
    pos.reserve(n);
    int i = 0;
    while (i < n) {
      int minLen = 0, wordsLen = 0;
      int j = i;
      while (i < n) {
        wordsLen += words[i].size();
        minLen = wordsLen + i - j;
        if (minLen > maxWidth)
          break;
        i++;
      }

      pos.push_back(i);
    }

    // 2. justify lines
    int m = (int)pos.size();
    vector<string> ans;
    ans.reserve(m);
    auto from = words.begin();
    auto to = words.begin();
    for (int i = 0; i < m; from = to, ++i) {
      int delta = pos[i] - (i == 0 ? 0 : pos[i - 1]);
      advance(to, delta);
      if (i + 1 == m)
        ans.push_back(justifyLeft(from, to, maxWidth));
      else
        ans.push_back(justifyEvenly(from, to, maxWidth));
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
  vector<string> res, want;

  //       This   is   an
  want = {"This    is    an", "example  of text", "justification.  "};
  res = s->fullJustify(
      {"This", "is", "an", "example", "of", "text", "justification."}, 16);
  println("res ={}\nwant={}", res, want);
  assert(res == want);
  println("ok");

  want = {
      "What   must   be",
      "acknowledgment  ",
      "shall be        ",
  };
  res = s->fullJustify({"What", "must", "be", "acknowledgment", "shall", "be"},
                       16);
  println("res ={}\nwant={}", res, want);
  // assert(res == want);
  println("ok");

  want = {
      "Science  is  what we", "understand      well", "enough to explain to",
      "a  computer.  Art is", "everything  else  we", "do                  ",
  };
  res = s->fullJustify({"Science", "is", "what", "we", "understand", "well",
                        "enough", "to", "explain", "to", "a", "computer.",
                        "Art", "is", "everything", "else", "we", "do"},
                       20);
  println("res ={}\nwant={}", res, want);
  // assert(res == want);
  println("ok");

  return 0;
}
