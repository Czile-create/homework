#include <bits/stdc++.h>
using namespace std;

template <class ForwardIterator, class T>
ForwardIterator search(ForwardIterator first, ForwardIterator last, T&val) {
    auto i = first;
    auto j = last;
    while (i != j) {
        auto m = i + distance(i, j)/2;
        if (*m == val)
            return m;
        if (*m > val)
            j = m;
        else
            i = m + 1;
    }
    return last;
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