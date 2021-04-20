#include <bits/stdc++.h>
using namespace std;

// move the element of an integer range, 
// making the range follow the rule like this:
// odd_number, odd_number, ... not_odd_number, not_odd_number, ... 
template <class RandomAccessIterator>
void fun (RandomAccessIterator first, RandomAccessIterator last) {
    while (first < last) {
        for (; first < last && (*first) % 2; first++);
        for (last--; first < last && (*last) % 2 == 0; last--);
        if (first < last)
            swap(*first, *last);
    }
}

// To test a fun(range) whether or not follow the rule. 
template  <class RandomAccessIterator>
bool test (RandomAccessIterator first, RandomAccessIterator last) {
    for (; first < last && (*first) % 2; first++);
    for (last--; first < last && (*last) % 2 == 0; last--);
    if (first != last)
        return false;
    return true;
}

int main() {
    srand(time(0));
    for (auto k=0; k<100; k++) {
        vector<int> p;
        for (auto i=0; i<10; i++)
            p.push_back(rand());
        fun(p.begin(), p.end());
        if (!test(p.begin(), p.end())) {
            for (auto j=0; j<10; j++)
                cerr<<p[j]<<" ";
            cerr<<endl;
        }
    }
    return 0;
}