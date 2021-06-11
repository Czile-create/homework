#include <bits/stdc++.h>
using namespace std;

typedef struct City {
    string name;
    long long Distance;
    vector<City>::iterator father;
    vector<pair<vector<City>::iterator, int>> neighbors;
    City(string s): 
        name(s), Distance(unsigned(-1)) {}
} City;

struct cmp {
    bool operator() (
        const vector<City>::iterator &i, 
        const vector<City>::iterator &j
    )const {
        return i -> Distance > j -> Distance;
    }
};

int main() {
    ifstream fin("01.mdb", ios::in);
    int n, m;
    vector<City> cityList;
    fin >> n;
    for (auto i=0; i<n; ++i) { 
        string s;
        fin >> s;
        cityList.push_back(City(s));
    }
    auto j = 0;
    for (auto &i: cityList)
        i.father = cityList.begin() + j++;
    fin >> m;
    for (auto i=0; i<m; ++i) {
        int j, k, l;
        fin >> j >> k >> l;
        cityList[j].neighbors.push_back(make_pair(cityList.begin() + k, l));
    }
    cityList[1].Distance = 0;
    priority_queue<
        vector<City>::iterator, 
        vector<vector<City>::iterator>, 
        cmp
    > que;
    cityList[1].Distance = 0;
    for (auto i = cityList.begin(); i != cityList.end(); ++i)
        que.push(i);
    while (que.size()) {
        auto top = que.top();
        for (auto &i: top -> neighbors)
            if (top -> Distance + i.second < (i.first) -> Distance) {
                (i.first) -> Distance = top -> Distance + i.second;
                (i.first) -> father = top;
            }
        que.pop();
    }
    for (auto &i: cityList)
        cout << i.name << " " << i.father -> name << " " << ((i.Distance == unsigned(-1)) ? "NA" : to_string(i.Distance)) << endl;
    fin.close();
    return 0;
}