#include <bits/stdc++.h>
#include "Binarytree.h"

using namespace std;

int main() {
    vector<int> p = {1, 2, 3, 4, 5, 6, 7, 8};
    Binarytree<int> t(p.begin(), p.end(), 0);
    t.insert(t.root()->right -> right, 9, 0);
    auto j = t.Preorder();
    auto k = t.Inorder();
    Binarytree<int> test(j.begin(), j.end(), k.begin(), k.end());
    cout<<test.print([](auto i) {return to_string(i);});
    // auto f = test.getPreThrBiTree();
    return 0;
}