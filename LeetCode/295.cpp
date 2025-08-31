#include <print>
#include <cassert>
#include <iostream>
#include <set>

using namespace std;

class MedianFinder {
private:
    multiset<int> lo, hi;

    void rebalance() {
        int target = ((int)lo.size() + (int)hi.size() + 1) / 2;
        while (lo.size() < target) {
            auto it = hi.begin();
            lo.insert(*it);
            hi.erase(it);
        }
        while (lo.size() > target) {
            auto it = prev(lo.end());
            hi.insert(*it);
            lo.erase(it);
        }
    }
public:
    MedianFinder() : lo{}, hi{} {}

    void addNum(int num) {
        if (lo.empty() || num <= *lo.rbegin()) {
            lo.insert(num);
        } else {
            hi.insert(num);
        }
        rebalance();
    }

    double findMedian() {
        int size = (int)lo.size() + (int)hi.size();
        if (size & 1) {
            return *lo.rbegin();
        } else {
            return (*lo.rbegin() + *hi.begin()) / 2.0;
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
    auto s = new MedianFinder;
    int res;

    s->addNum(1);
    s->addNum(2);

    res = s->findMedian();
    assert(res == 1.5);

    s->addNum(3);

    res = s->findMedian();
    assert(res == 2.0);
}

int main() {
    auto s = new MedianFinder;

    return 0;
}
