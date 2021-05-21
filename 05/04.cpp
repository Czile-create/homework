#include <bits/stdc++.h>
#include "Binarytree.h"

using namespace std;

int main() {
    string pre = "-+a*b-cd/ef", in = "a+b*c-d-e/f";
    Binarytree<char> opera(pre.begin(), pre.end(), in.begin(), in.end());
    cout<<opera.print([](const char& c) {
        string s = "";
        return s += c;
    });
    return 0;
}