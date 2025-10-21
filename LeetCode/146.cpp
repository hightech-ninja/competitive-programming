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
class LRUCache {
private:
  using value_t = pair<int, int>;
  using iter_t = list<value_t>::iterator;

  unordered_map<int, iter_t> _pos;
  list<value_t> _cache;
  int _capacity;

  void touch(iter_t it) { _cache.splice(_cache.begin(), _cache, it); }

public:
  LRUCache(int capacity) : _capacity(capacity) { _pos.reserve(_capacity); }

  int get(int key) {
    if (_pos.count(key) == 0)
      return -1;
    touch(_pos[key]);
    return _pos[key]->second;
  }

  void put(int key, int value) {
    if (_pos.count(key) > 0) {
      _pos[key]->second = value;
      touch(_pos[key]);
      return;
    }

    _pos[key] = _cache.emplace(_cache.begin(), key, value);

    if ((int)_cache.size() > _capacity) {
      int key = _cache.back().first;
      _pos.erase(key);
      _cache.pop_back();
    }
  }
};

auto init = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  return 0;
}();

void test1() {
  auto cache = new LRUCache(2);
  int got;
  cache->put(1, 1);
  cache->put(2, 2);
  got = cache->get(1);
  assert(got == 1);
  cache->put(3, 3);
  got = cache->get(2);
  assert(got == -1);
  cache->put(4, 4);
  got = cache->get(1);
  assert(got == -1);
  got = cache->get(3);
  assert(got == 3);
  got = cache->get(4);
  assert(got == 4);
}

void test2() {
  auto cache = new LRUCache(2);
  int got;
  cache->put(2, 1);
  cache->put(1, 2);
  got = cache->get(2);
  assert(got == 1);
  cache->put(4, 1);
  got = cache->get(1);
  assert(got == -1);
  got = cache->get(2);
  assert(got == 1);
}

int main() {
  test1();
  println("ok");

  test2();
  println("ok");

  return 0;
}
