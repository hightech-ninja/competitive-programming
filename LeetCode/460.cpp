#include <cassert>
#include <iostream>
#include <list>
#include <print>
#include <unordered_map>

using namespace std;

/*
    Time:  O(1) amortized
    Space: O(n)
 */
class LFUCache {
private:
  using value_t = pair<int, int>; // <key, value>
  using list_t = list<value_t>;
  using iter_t = list_t::iterator;
  using pos_t = pair<int, iter_t>; // <freq, pos>

  unordered_map<int, pos_t> _pos;      // key -> list position
  unordered_map<int, list_t> _buckets; // freq -> list
  int _minFreq;
  int _size;
  int _cap;

  void touch(int key) {
    int freq = _pos[key].first;
    auto it = _pos[key].second;
    _buckets[freq + 1].splice(_buckets[freq + 1].begin(), _buckets[freq], it);
    _pos[key].first = freq + 1;
    if (_minFreq == freq && _buckets[freq].size() == 0) {
      _minFreq = freq + 1;
    }
  }

public:
  LFUCache(int capacity) : _minFreq(0), _size(0), _cap(capacity) {
    _pos.reserve(capacity);
  }

  int get(int key) {
    if (_pos.count(key) == 0) {
      return -1;
    }
    touch(key);
    return _pos[key].second->second;
  }

  void put(int key, int value) {
    if (_pos.count(key) > 0) {
      _pos[key].second->second = value;
      touch(key);
      return;
    }

    if (_size == _cap) {
      int key = _buckets[_minFreq].back().first;
      _pos.erase(key);
      _buckets[_minFreq].pop_back();
    }

    _pos[key] = {1, _buckets[1].emplace(_buckets[1].begin(), key, value)};
    _minFreq = 1;
    _size = min(_size + 1, _cap);
  }
};

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

void test1() {
  auto cache = new LFUCache(2);
  int got;
  cache->put(1, 1);
  cache->put(2, 2);
  got = cache->get(1);
  assert(got == 1);
  cache->put(3, 3);
  got = cache->get(2);
  assert(got == -1);
  got = cache->get(3);
  assert(got == 3);
  cache->put(4, 4);
  got = cache->get(1);
  assert(got == -1);
  got = cache->get(3);
  assert(got == 3);
  got = cache->get(4);
  assert(got == 4);
}

int main() {
  test1();
  println("ok");

  return 0;
}
