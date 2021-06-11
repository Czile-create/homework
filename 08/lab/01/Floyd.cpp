#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("01.mdb", ios::in);
    int n, m;
    vector<string> cityList;
    fin >> n;
    for (auto i=0; i<n; ++i) { 
        string s;
        fin >> s;
        cityList.push_back(s);
    }
    vector<vector<long long>> Dis(n, vector<long long>(n, unsigned(-1)));
    vector<vector<string>> Path(n, vector<string>(n, "NA"));
    for (auto i = 0; i < n; ++i) {
        Dis[i][i] = 0;
        Path[i][i] = cityList[i];
    }
    fin >> m;
    for (auto i=0; i<m; ++i) {
        int j, k, l;
        fin >> j >> k >> l;
        Dis[j][k] = l;
    }
    for (auto k = 0; k < n; ++k)
        for (auto i = 0; i < n; ++i)
            for (auto j = 0; j < n; ++j)
                if (Dis[i][j] > Dis[i][k] + Dis[k][j]) {
                    Dis[i][j] = Dis[i][k] + Dis[k][j];
                    Path[i][j] = cityList[k];
                }
    for (auto i = 0; i < n; ++i) {
        cout << cityList[i] << ":\t";
        for (auto j = 0; j < n; ++j)
            cout << ((Dis[i][j] == unsigned(-1)) ? "NA" : to_string(Dis[i][j])) << "\t";
        cout << endl;
    }
    cout << endl;
    for (auto i = 0; i < n; ++i) {
        cout << cityList[i] <<":\t";
        for (auto j = 0; j < n; ++j)
            cout << Path[i][j] << "\t";
        cout << endl;
    }
    fin.close();
    return 0;
}