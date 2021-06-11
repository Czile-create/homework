#include <bits/stdc++.h>
#include "Binarytree.h"
#include <queue>

using namespace std;

void print(Binarytree<char>::thrnode * f) {
    queue<Binarytree<char>::thrnode*> q;
    if (f != nullptr) q.push(f);
    while (q.size()) {
        auto tmp = q.front();
        if (tmp -> ltag == 0) q.push(tmp -> left);
        if (tmp -> rtag == 0) q.push(tmp -> right);
        printf("%c\t%d\t%d\t%c\t%c\n", tmp -> val, tmp -> ltag, tmp -> rtag, 
            (tmp -> left)?(tmp -> left -> val):0, 
            (tmp -> right)?(tmp -> right -> val):0
        );
        q.pop();
    } 
    cout<<endl;
}

int main() {
    string tmp = "-+/a*ef##b-##########cd########";
    Binarytree<char> opera(tmp.begin(), tmp.end(), '#');
    print(opera.getPreThrBiTree());
    print(opera.getInThrBiTree());
    print(opera.getPostThrBiTree());
    print(opera.getBFSThrBiTree());
    return 0;
}