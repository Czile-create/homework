#include <bits/stdc++.h>
using namespace std;

string lock(const string&s, const unsigned key) {
    string ans = "";
    for (auto &i: s)
        if (i >= 'A' && i <= 'Z')
            ans += (i - 'A' + key) % 26 + 'A';
        else if (i >= 'a' && i <= 'z')
            ans += (i - 'a' + key) % 26 + 'a';
        else
            ans += i;
    return ans;
}

string unlock(const string&s, const unsigned key) {
    string ans = "";
    for (auto &i: s) {
        if (i >= 'A' && i <= 'Z')
            ans += (i - 'A' + 26 - key) % 26 + 'A';
        else if (i >= 'a' && i <= 'z')
            ans += (i - 'a' + 26 - key) % 26 + 'a';
        else
            ans += i;
    }
    return ans;
}

void try_to_unlock(const string &s) {
    for (int i = 0; i < 26; i++)
        cout<<"Key "<<i<<": "<<unlock(s, i)<<endl;
}

int main() {
    string s = "Hello World!\n";
    try_to_unlock(lock(s, 24));
    return 0;
}