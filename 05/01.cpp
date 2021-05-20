#include <bits/stdc++.h>
#include "Binarytree.h"

using namespace std;

int main() {
    vector<int> p = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Binarytree<int> t(p.begin(), p.end(), 0);
    // t.insert(t.root()->right -> right, 9, 0);
    auto j = t.Preorder();
    auto k = t.Inorder();
    Binarytree<int> test(j.begin(), j.end(), k.begin(), k.end());
    cout<<test.info([](auto i) {return to_string(i);});
    cout<<test.print([](auto i) {return to_string(i);});
    auto f = t.getBFSThrBiTree();
    queue<Binarytree<int>::thrnode*> q;
    if (f != nullptr) q.push(f);
    while (q.size()) {
        auto tmp = q.front();
        if (tmp -> ltag == 0) q.push(tmp -> left);
        if (tmp -> rtag == 0) q.push(tmp -> right);
        printf("%d\t%d\t%d\t%d\t%d\n", tmp -> val, tmp -> ltag, tmp -> rtag, 
            (tmp -> left)?(tmp -> left -> val):0, 
            (tmp -> right)?(tmp -> right -> val):0
        );
        q.pop();
    }
    return 0;
}