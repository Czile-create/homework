#include <bits/stdc++.h>
using namespace std;

template <class ForwardIterator, class T>
ForwardIterator search(ForwardIterator first, ForwardIterator last, T&val) {
    if (first == last)
        return last;
    auto mid = first + distance(first, last)/2;
    if (val == *mid)
        return mid;
    auto tmp = first;
    if (val < *mid) {
        tmp = search(first, mid, val);
        if (tmp != mid)
            return tmp;
        return last;
    } else return search(mid+1, last, val);
}

int main() {
    srand(time(0));
    vector<int> p;
    for (auto i = 0; i < 10000; ++i)
        p.push_back(rand());
    sort(p.begin(), p.end());
    auto tmp = 0;
    do {
        tmp = rand();
        cout << "Finding " << tmp <<" ...\n";
    } while (search(p.begin(), p.end(), tmp) == p.end());
    cout << "Successful\n";
    return 0;
}