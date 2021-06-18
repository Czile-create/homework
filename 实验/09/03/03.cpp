#include <bits/stdc++.h>
#include "BalanceTree.h"
using namespace std;

int main() {
    int n = 10000;
    srand(time(0));
    BalanceTree t;
    for (auto i = 0; i < n; ++i) {
        t.push(rand());
        // cout << t.print([](const int &s){return to_string(s);})<<endl;
    }
    cout << t.depth() << endl;
    for (auto &i: t.inorder())
        cout << i << " ";
    cout << endl;
    return 0;
}