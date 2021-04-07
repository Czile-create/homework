// To find the value of the expression

#include <bits/stdc++.h>
using namespace std;

double ans(string s) {
    // erase the space " "
    s = regex_replace(s, regex("\\s"), "");                                 
    smatch ex;

    // process the operator ()
    while (regex_search(s.cbegin(), s.cend(), ex, regex("\\((.*?)\\)"))) {           
        auto t = string(ex[0].first+1, ex[0].second-1);
        s.replace(s.find(ex[0]), ex[0].length(), to_string(ans(t)));
    }

    // To check if the expreesion is true.
    // NOTE: Not finished.
    if (!regex_match(s, regex("(\\d|\\+|-|\\*|/|\\.)*")))
        throw "Expression Error!\n";

    // process the operator [*/]
    while (regex_search(s.cbegin(), s.cend(), ex, regex("(\\d+(\\.\\d+)?)([\\*/])(\\d+(\\.\\d+)?)"))) {
        smatch s1, s2, s3;
        regex_search(ex[0].first, ex[0].second, s1, regex("\\d+(\\.\\d+)?"));   // first number
        regex_search(s1[0].second, ex[0].second, s2, regex("\\*|/"));           // operator
        regex_search(s2[0].second, ex[0].second, s3, regex("\\d+(\\.\\d+)?"));  // second number
        if (s2[0] == "*")
            s.replace(s.find(ex[0]), ex[0].length(), to_string(stod(s1[0])*stod(s3[0])));
        else
            s.replace(s.find(ex[0]), ex[0].length(), to_string(stod(s1[0])/stod(s3[0])));
    }

    // process the operator [+-]
    while (regex_search(s.cbegin(), s.cend(), ex, regex("(\\d+(\\.\\d+)?)([\\+-])(\\d+(\\.\\d+)?)"))) {
        smatch s1, s2, s3;
        regex_search(ex[0].first, ex[0].second, s1, regex("\\d+(\\.\\d+)?"));   // first number
        regex_search(s1[0].second, ex[0].second, s2, regex("\\+|-"));           // operator
        regex_search(s2[0].second, ex[0].second, s3, regex("\\d+(\\.\\d+)?"));  // second number
        if (s2[0] == "+")
            s.replace(s.find(ex[0]), ex[0].length(), to_string(stod(s1[0])+stod(s3[0])));
        else
            s.replace(s.find(ex[0]), ex[0].length(), to_string(stod(s1[0])-stod(s3[0])));
    }

    return stod(s);
}

int main() {
    string s;
    getline(cin, s);
    cout<<ans(s);
    return 0;
}