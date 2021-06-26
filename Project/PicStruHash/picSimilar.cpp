#include <bits/stdc++.h>
using namespace std;

map<string, uint64_t> readPicHash(string filename) {
    ifstream fin(filename, ios::in);
    string tmp1, tmp2;
    map<string, uint64_t> ans;
    while (!fin.eof()) {
        fin >> tmp1 >> tmp2;
        ans.insert(make_pair(tmp1.substr(2, tmp1.size() - 4), strtoull(tmp2.substr(0, tmp2.size() - 1).c_str(), NULL, 10)));
    }
    fin.close();
    return ans;
}

double getSimilar(uint64_t i, uint64_t j) {
    auto ans = 0;
    auto similar = i ^ j;
    while (similar != 0) {
        similar &= (similar - 1);
        ++ans;
    }
    return 1 - double(ans)/64;
}

void printSimilar(map<string, uint64_t> & p) {
    ofstream fout("picSimilar1.log", ios::out);
    for (auto &i: p)
        for (auto &j: p)
            if (i.first != j.first && getSimilar(i.second, j.second) > 0.9)
                fout << "'" << i.first << "' '" << j.first << "'\n";
    fout.close();
}

int main() {
    auto m = readPicHash("picHash.log");
    printSimilar(m);
    return 0;
}