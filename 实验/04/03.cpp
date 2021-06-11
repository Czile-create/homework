#include <bits/stdc++.h>
using namespace std;

int asn(const string &&p, const string &&t, int k) {
    vector<vector<int>> dp(p.size() + 1, vector<int>(t.size() + 1, 0));
    auto j = 0;
    for (auto &i: dp) 
        i[0] = j++;
    for (j = 1; j <= t.size(); ++j) {
        for (auto i = 1; i <= p.size(); ++i)
            dp[i][j] = (p[i] == t[j]) ? min(
                min(dp[i-1][j-1], dp[i-1][j] + 1), dp[i][j-1]+1
            ) : min(
                min(dp[i-1][j-1]+1, dp[i-1][j]+1), dp[i][j-1]+1
            );
        if (dp[p.size()][j] <= k)
            return j;
    }
    return -1;
}

int main() {
    cout<<asn("approximatly", "aproxiomally", 3)<<endl;
    return 0;
}