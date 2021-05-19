#include <bits/stdc++.h>
#include "Binarytree.h"

using namespace std;

int main() {
    vector<int> p = {1, 2, 3, 4, 5, 6, 7, 8};
    Binarytree<int> t(p.begin(), p.end(), 0);
    t.insert(t.root()->right -> right, 9, 0);
    auto j = t.BFS();
    for (auto i: j)
        cerr<<i<<" ";
    Binarytree<int> test(t);
    return 0;
}