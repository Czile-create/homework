#include <bits/stdc++.h>
#include "Binarytree.h"

using namespace std;

int main() {
    vector<int> p = {1, 2, 3, 4, 5, 6, 7, 8};
    Binarytree<int> t(p.begin(), p.end(), 0);
    Binarytree<int> test(t);
    cerr<<1;
    return 0;
}