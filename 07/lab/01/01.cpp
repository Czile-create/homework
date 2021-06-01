#include <bits/stdc++.h>
using namespace std;
#define graph vector<vector<int>>
graph readfile(const string & filename) {
    ifstream fin(filename, ios::in);
    if (!fin.is_open())
        throw "Not such file or directory"
    auto n = 0;
    graph ans;
    fin >> n;
    for (auto i = 0; i < n; ++i) {
        ans.push_back(vector<int>());
        for (auto j = 0; j < n; ++j) {
            ans.back().push_back(0);
            fin >> ans.back().back();
        }
    }
    fin.close();
    return ans;
}

vector<int> DFS(
    graph & edge, 
    int start, 
    vector<bool> & status
) {
    if (start >= edge.size() || start < 0)
        throw "Invalid parameter in DFS.";
    vector<int> ans = {start};
    status[start] = 1;
    for (auto i = 0; i < edge[start].size(); ++i)
        if (edge[start][i] && !status[i]) {
            auto tmp = DFS(edge, i, status);
            ans.insert(ans.end(), tmp.begin(), tmp.end());
        }
    return ans;
}

vector<int> BFS(
    graph & edge, 
    int start, 
    vector<bool> & status
) {
    if (start >= edge.size() || start < 0)
        throw "Invalid parameter in BFS.";
    vector<int> ans = {start};
    status[start] = 1;
    auto i = 0;
    while (i < ans.size()) {
        for (auto j = 0; j < edge.size(); ++j)
            if (edge[ans[i]][j] && !status[j]) {
                status[j] = 1;
                ans.push_back(j);
            }
        ++i;
    }
    return ans;
}

void print(const vector<int> & p, const string & name) {
    cout<<name<<": ";
    for (auto &i : p)
        cout << i <<" ";
    cout<<endl;
}

void printInfo(graph & edge, int start) {
    cout<<"The info of node are as follows:\n"
        <<"Out-degere: "
        <<accumulate(
            edge[start].begin(), 
            edge[start].end(), 
            0, 
            [] (auto init, auto &i) {
                return init + bool(i);
            })
        <<"\nIn-degree: "
        <<accumulate(
            edge.begin(),
            edge.end(),
            0, 
            [&start](auto init, auto &i) {
                return init + bool(i[start]);
            }
        ) << endl;
    cout << "Out edge: ";
    for (auto i = 0; i < edge.size(); ++i) 
        if (edge[start][i])
            cout<<i<<" ";
    cout << "\nIn edge: ";
    for (auto i = 0; i < edge.size(); ++i)
        if (edge[i][start])
            cout<<i<<" ";
    cout << endl;
}

int main() {
    try {
        graph edge = readfile("data.mdb");
    } catch (const char * c) {
        cerr << c;
    }
    vector<bool> status(edge.size(), 0);
    auto k = 0;
    cout << "Input the order of the node you want to know...\n> ";
    cin >> k;
    try {
        print(DFS(edge, k, status), "DFS");
        fill(status.begin(), status.end(), 0);
        print(BFS(edge, k, status), "BFS");
        printInfo(edge, k);
    } catch (const char *c) {
        cerr << c;
    }
    return 0;
}