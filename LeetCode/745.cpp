#include <cassert>
#include <iostream>
#include <print>
#include <string>
#include <vector>

using namespace std;

class Trie {
private:
  static const int ALPHA = 27;

  array<Trie *, ALPHA> children = {};
  int index = -1; // max index that comes through the vertex

public:
  void insert(string const &s, int idx) {
    index = max(index, idx);
    Trie *v = this;
    for (char ch : s) {
      int c = ch - 'a';
      if (v->children[c] == nullptr)
        v->children[c] = new Trie;
      v = v->children[c];
      v->index = max(v->index, idx);
    }
  }
  int search(string const &s) {
    Trie *v = this;
    for (char ch : s) {
      int c = ch - 'a';
      if (v->children[c] == nullptr)
        return -1;
      v = v->children[c];
    }
    return v->index;
  }
};

class WordFilter {
private:
  static const char SEP = '{';
  Trie trie;

public:
  WordFilter(vector<string> const &words) {
    int n = (int)words.size();
    for (int i = 0; i < n; ++i) {
      int m = (int)words[i].size();
      for (int j = 0; j <= m; ++j) {
        auto str = words[i].substr(j) + SEP + words[i];
        trie.insert(str, i);
      }
    }
  }

  int f(string pref, string suff) { return trie.search(suff + SEP + pref); }
};

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

int main() {
  auto wf = new WordFilter({"apple", "pie", "ant", "simple"});
  int res, want;

  want = 0;
  res = wf->f("a", "e");
  println("res ={}\nwant={}", res, want);
  assert(res == want);

  want = 3;
  res = wf->f("", "");
  println("res ={}\nwant={}", res, want);
  assert(res == want);

  want = 2;
  res = wf->f("a", "");
  println("res ={}\nwant={}", res, want);
  assert(res == want);

  want = 3;
  res = wf->f("", "le");
  println("res ={}\nwant={}", res, want);
  assert(res == want);

  want = 2;
  res = wf->f("", "t");
  println("res ={}\nwant={}", res, want);
  assert(res == want);

  want = -1;
  res = wf->f("x", "");
  println("res ={}\nwant={}", res, want);
  assert(res == want);

  want = -1;
  res = wf->f("", "y");
  println("res ={}\nwant={}", res, want);
  assert(res == want);

  return 0;
}
