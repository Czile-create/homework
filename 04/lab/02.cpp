#include <bits/stdc++.h>
using namespace std;

bool isMagicMatrix(vector<vector<int>> & p) {
    for (auto &i : p)
        if (i.size() != p.size())
            return false;
    
    auto sum = 0;
    for (auto i = 0; i < p.size(); ++i)
        sum += p[i][i];
    
    for (auto &i : p)
        if (accumulate(i.begin(), i.end(), 0) != sum)
            return false;
    for (auto i = 0; i < p.size(); ++i)
        if (accumulate(p.begin(), p.end(), 0, [&i](auto k, auto &j){
            return k + j[i];
        }) != sum)
            return false;
    for (auto i = 0; i < p.size(); ++i)
        sum -= p[i][p.size() - i - 1];
    return !sum;
}

vector<vector<int>> getMagicMatrix(int n) {
    if (n % 2 == 0)
        return vector<vector<int>>();
    vector<vector<int>> ans;
    for (auto i = 0; i < n; ++i) {
        ans.push_back(vector<int>());
        for (auto j = 0; j < n; ++j)
            ans.back().push_back(0);
    }

    unsigned i = n - 1, j = n / 2;
    ans[i][j] = 1;
    for (auto k = 2; k <= n * n; ++k)
        if (ans[(++i)%n][(++j)%n])
            ans[(i-=2)%n][(--j+n)%n] = k;
        else
            ans[i%n][j%n] = k;
    
    return ans;
}

int main() {
    vector<vector<int>> p(getMagicMatrix(7));
    for (auto &i: p) {
        for (auto &j : i)
            cout<<fixed<<setw(5)<<j<<" ";
        cout<<endl;
    }
    cout<<isMagicMatrix(p)<<endl;
    return 0;
}