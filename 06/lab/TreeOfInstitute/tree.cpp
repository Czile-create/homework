#include <bits/stdc++.h>
#include "Binarytree.h"
using namespace std;

int main() {
    ifstream fin("database", ios::in);
    Binarytree<string> t;
    t.root() = new Binarytree<string>::Binarytreenode("SYSU");
    auto pre = t.root();
    while (!fin.eof()) {
        string s;
        getline(fin, s);
        if (s == "")
            continue;
        auto x = t.root();
        if (s[0] != '-')
            x = pre;
        if (x -> left) {
            x = x -> left;
            while (x -> right)
                x = x -> right;
            t.insert(x, s, 1);
        } else t.insert(x, s, 0);
        if (s[0] == '-')
            pre = (x -> right) ? x -> right : x -> left;
    }
    fin.close();
    auto x = t.preorder();
    for (auto &i : x) 
        cout<<i<<endl;
    return 0;
}