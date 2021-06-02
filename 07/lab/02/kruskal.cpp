#include <bits/stdc++.h>
using namespace std;

const unsigned sizeOfCity = 11;

int getfather(vector<int> & father, int i) {
    while (father[i] != i)
        i = father[i];
    return i;
}

int main () {
    int edge[sizeOfCity][sizeOfCity];
    vector<pair<pair<int, int>, int>> edgeList;
    vector<string> city;
    vector<int> father = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ifstream fin("data.mdb");

    // reading data
    for (auto i = 0; i < sizeOfCity; ++i) {
        city.push_back("");
        fin >> city.back();
        for (auto j = 0; j < sizeOfCity; ++j)
            fin >> edge[i][j];
    }

    // cleaning data
    for (auto i = 0; i < sizeOfCity; ++i) 
        for (auto j = i; j < sizeOfCity; ++j) {
            edge[i][j] = edge[j][i] = (edge[i][j] + edge[j][i]) / 2;
            edgeList.push_back(make_pair(make_pair(i, j), edge[i][j]));
        }
    
    vector<pair<int, int>> ans;
    sort(edgeList.begin(), edgeList.end(), [](auto &i, auto &j) {
        return i.second < j.second;
    });

    for (auto &i: edgeList) 
        if (getfather(father, i.first.first) != 
            getfather(father, i.first.second)
        ) {
            ans.push_back(make_pair(i.first.first, i.first.second));
            father[getfather(father, i.first.first)] = 
                father[getfather(father, i.first.second)];
        }

    for (auto &i: ans)
        cout<< city[i.first] <<" "<<city[i.second]<<" "<<edge[i.first][i.second]<<endl;
    return 0;
}