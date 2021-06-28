#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

void readfile(map<int, int>&p, string s) {
    ifstream fin(s, ios::in);
    while (!fin.eof()) {
        int a, b, c;
        fin >> a >> b >> c;
        p[a]=c;
    }
    fin.close();
}

typedef struct major {
    string name, institute;
    bool isScience;
    int min[3];
    int avr[3];
} major;

vector<major> readmajor() {
    ifstream fin("data/major.mdb");
    vector<major> p;
    while (!fin.eof()) {
        major tmp;
        string s, t;
        getline(fin, s);
        s += "\t0\t0\t0\t0\t0\t0";
        stringstream str(s);
        str >> tmp.name >> tmp.institute;
        str >> t;
        tmp.isScience = (t == "理科");
        int a, b, c, d, e, f;
        str >> a >> b >> c >> d >> e >> f;
        tmp.min[0]=a, tmp.min[1]=c, tmp.min[2]=e;
        tmp.avr[0]=b, tmp.avr[1]=d, tmp.avr[2]=f;
        p.push_back(tmp);
    }
    fin.close();
    return p;
}

int main() {
    //分数 -> 排名 2018 - 2021
    array<map<int, int>, 4> rank;
    int MAX=3000000;

    readfile(rank[0], "data/2018.txt");
    readfile(rank[1], "data/2019.txt");
    readfile(rank[2], "data/2020.txt");
    readfile(rank[3], "data/2021.txt");
    auto major = readmajor();
    sort(major.begin(), major.end(), [](auto &i, auto &j) {
        if (i.isScience != j.isScience)
            return i.isScience;
        return accumulate(i.avr, i.avr+3, 0)/count_if(i.avr, i.avr+3, [](auto i){return i;}) > 
                accumulate(j.avr, j.avr+3, 0)/count_if(j.avr, j.avr+3, [](auto i){return i;});
    });
    ofstream fout("major.csv", ios::out);
    for (auto &i: major) {
        fout << i.name << ", " << i.institute << ", ";
        fout << (i.isScience ? "理科, ": "文科, ");
        for (auto j = 0; j < 3; ++j)
            fout << i.min[j] << ", " << i.avr[j] << ", ";
        if (i.isScience)
            for (auto j = 0; j < 3; ++j)
                fout << rank[j][i.min[j]] << ", " << rank[j][i.avr[j]] << ", ";
        fout << endl;
    }
    fout.close();

    int score, isScience;
    cout << "Input your score:\n>";
    cin >> score;
    cout << "Are you major in science?(1/0):\n";
    cin >> isScience;
    if (!isScience) {
        cerr << "Data missing" << endl;
        return 0;
    }
    cout << "Rank: " << rank[3][score + 1] << endl;
    cout << "Here are the major you should consider:\n";
    cout << "冲：\n";
    for (auto &i: major) {
        auto k = max(max(rank[0][i.min[0]], rank[1][i.min[1]]), rank[2][i.min[2]]);
        auto l = (rank[0][i.avr[0]]+rank[1][i.avr[1]]+rank[2][i.avr[2]])/count_if(i.avr, i.avr+3, [](auto i){return i;});
        if (i.isScience && k >= rank[3][score] && l < rank[3][score]) {
            cout << i.name << " " << i.institute << " ";
            for (auto j = 0; j < 3; ++j)
                cout << i.min[j] << " " << i.avr[j] << " ";
            for (auto j = 0; j < 3; ++j)
                cout << rank[j][i.min[j]] << " " << rank[j][i.avr[j]] << " ";
            cout << endl;
        }
    }
    cout << "稳：\n";
    for (auto &i: major) {
        auto l = (rank[0][i.avr[0]]+rank[1][i.avr[1]]+rank[2][i.avr[2]])/count_if(i.avr, i.avr+3, [](auto i){return i;});
        auto p = MAX;
        for (auto j = 0; j < 3; ++j)
            if (rank[j][i.avr[j]] && rank[j][i.avr[j]] < p)
                p = rank[j][i.avr[j]];
        if (i.isScience && l >= rank[3][score] && p < rank[3][score]) {
            cout << i.name << " " << i.institute << " ";
            for (auto j = 0; j < 3; ++j)
                cout << i.min[j] << " " << i.avr[j] << " ";
            for (auto j = 0; j < 3; ++j)
                cout << rank[j][i.min[j]] << " " << rank[j][i.avr[j]] << " ";
            cout << endl;
        }
    }
    cout << "保：\n";
    for (auto &i: major) {
        int p = MAX;
        for (auto j = 0; j < 3; ++j)
            if (rank[j][i.avr[j]] && rank[j][i.avr[j]] < p)
                p = rank[j][i.avr[j]];
        if (i.isScience && p >= rank[3][score]) {
            cout << i.name << " " << i.institute << " ";
            for (auto j = 0; j < 3; ++j)
                cout << i.min[j] << " " << i.avr[j] << " ";
            for (auto j = 0; j < 3; ++j)
                cout << rank[j][i.min[j]] << " " << rank[j][i.avr[j]] << " ";
            cout << endl;
        }
    }

    return 0;
}