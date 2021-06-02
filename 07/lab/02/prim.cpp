#include <bits/stdc++.h>
using namespace std;

const unsigned sizeOfCity = 11;

int main () {
    int edge[sizeOfCity][sizeOfCity];
    vector<string> city;
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
        for (auto j = i; j < sizeOfCity; ++j) 
            edge[i][j] = edge[j][i] = (edge[i][j] + edge[j][i]) / 2;
    
    // prim
    set<int> searched = {0};
    set<int> tosearch = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<pair<int, int>> ans;
    while (tosearch.size()) {
        auto minEdge = make_pair(*searched.begin(), *tosearch.begin());
        for (auto &i: searched)
            for (auto &j: tosearch)
                if (edge[i][j] < edge[minEdge.first][minEdge.second])
                    minEdge = make_pair(i, j);
        ans.push_back(minEdge);
        tosearch.erase(tosearch.find(minEdge.second));
        searched.insert(minEdge.second);
    } 

    for (auto &i: ans)
        cout<< city[i.first] <<" "<<city[i.second]<<" "<<edge[i.first][i.second]<<endl;
    return 0;
}