#include <bits/stdc++.h>
using namespace std;

typedef map<pair<int, int>, double> matrix;

matrix operator+(const matrix &a, const matrix&b) {
    matrix ans;
    for (auto &i: a)
        ans[i.first] = i.second;
    for (auto &j: b)
        ans[j.first] += j.second;
    return ans;
}

matrix operator*(const matrix &a, const matrix& b) {
    matrix ans;
    for (auto &i: a)
        for (auto &j: b)
            ans[make_pair(i.first.first, j.first.second)] += i.second * j.second;
    return ans;
}

void print(matrix a) {
    for (auto &&i : a)
        cout<<i.first.first<<", "<<i.first.second<<": "<<i.second<<endl;
    cout<<endl;
}

int main() {
    matrix a, b;
    a[make_pair(1, 2)] = 2;
    b[make_pair(2, 3)] = 1;
    print(a);
    print(b);
    print(a+b);
    print(a*b);
    return 0;
}