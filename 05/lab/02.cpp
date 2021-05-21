#include <bits/stdc++.h>
#include "Binarytree.h"

using namespace std;

void print(const vector<char> & p) {
    for (auto &i : p)
        cout<<i<<" ";
    cout<<endl;
}

int main() {
    string tmp = "-+/a*ef##b-##########cd########";
    Binarytree<char> opera(tmp.begin(), tmp.end(), '#');
    print(opera.Preorder());
    print(opera.Inorder());
    print(opera.Postorder());
    print(opera.BFS());
    print(opera.preorder());
    print(opera.inorder());
    print(opera.postorder());
    return 0;
}