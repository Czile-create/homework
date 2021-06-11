#include <bits/stdc++.h>
#include "Binarytree.h"

using namespace std;

int main() {
    string tmp = "-+/a*ef##b-##########cd########";
    Binarytree<char> opera(tmp.begin(), tmp.end(), '#');
    cout<<opera.info([](const char& c) {
        string s = "";
        return s += c;
    });
    return 0;
}