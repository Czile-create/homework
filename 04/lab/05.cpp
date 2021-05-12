#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cout<<"Input the number of words in dictionary...\n>";
    cin >> n;
    vector<string> dictionary, matrix;
    for (auto i = 0; i < n; ++i) {
        cout<<"Input the word:\n>";
        dictionary.push_back(string());
        cin>>dictionary.back();
    }
    cout<<"Input the size of the matrix:\n>";
    cin >> m;
    for (auto i = 0; i < m; ++i) {
        cout<<"Input the first line of matrix\n>";
        matrix.push_back(string());
        cin>>matrix.back();
    }

    string str;
    str = accumulate(matrix.begin(), matrix.end(), str, [](auto i, auto j) {
        return i + " " + j + " ";
    });

    for (auto i = 0; i < m; ++i, str+=" ")
        str = accumulate(matrix.begin(), matrix.end(), str, [&i](auto j, string& k){
            return j + k[i];
        });

    // str = str + reverse_copy(str.begin(), str.end(), str);
    
    cout<<"Here are the words that match:\n";
    for (auto &i: dictionary)
        if (str.find(i) != string::npos)
            cout<<i<<endl;
    return 0;
}