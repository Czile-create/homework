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
    
    auto i = 0, j = m - 1;
    while (i != m - 1 || j) {
        str += matrix[i][j];
        if (j == m - 1 && i == m - 1)
            i = 1, j = 0, str+=" ";
        else if (j == m - 1)
            j = m - i - 2, i = 0, str+=" ";
        else if (i == m - 1)
            i = m - j, j = 0, str+=" ";
        else 
            ++i, ++j;
    }

    auto tmp = str;
    reverse(tmp.begin(), tmp.end());
    str += " "+tmp;
    
    cout<<"Here are the words that match:\n";
    for (auto &i: dictionary)
        if (str.find(i) != string::npos)
            cout<<i<<endl;
    return 0;
}