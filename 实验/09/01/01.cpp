#include <bits/stdc++.h>
using namespace std;
const int N = 10000;
bool find(array<list<uint64_t>, N> &hashList, const uint64_t num, ofstream& fout) {
    auto location = num % N;
    if (find(hashList[location].begin(), hashList[location].end(), num) != hashList[location].end())
        return false;
    hashList[location].push_back(num);
    fout << setfill('0') << setw(10) << num << endl;
    return true;
}

int main() {
    srand(time(0));
    ofstream fout("Ans.mdb", ios::out);
    array<list<uint64_t>, N> hashList;
    for (auto i = 0; i < 10000; ++i) {
        uint64_t num = 0;
        do {
            num = 0;
            for (auto j = 0; j < 10; ++j)
                num = num * 10 + rand() % 10;               
        } while (!find(hashList, num, fout));
    }
    fout.close();
    return 0;
}