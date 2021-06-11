#include <bits/stdc++.h>
using namespace std;

typedef struct course {
    string code, name;
    vector<string> prepare;
    course(string & a, string & b): code(a), name(b) {}
} course;

int main() {
    ifstream fin("02.mdb", ios::in);
    vector<course> c;
    int n;
    fin >> n;
    for (auto i = 0; i < n; ++i) {
        string a, b;
        int m;
        fin >> a >> b >> m;
        c.push_back(course(a, b));
        for (auto j = 0; j < m; ++j) {
            fin >> a;
            c.back().prepare.push_back(a);
        }
    }
    while (c.size()) {
        sort(c.begin(), c.end(), [](auto &i, auto &j) {
            return i.prepare.size() > j.prepare.size();
        });
        if ((c.end() - 1) -> prepare.size() != 0) {
            throw "Invalid Data";
            exit(0);
        }
        auto k = c.size() - 1;
        for (; k != -1 && c[k].prepare.size() == 0; cout << c[k--].name << " ");
        for (; c.size() != k + 1;) {
            for (auto &i: c) {
                auto j = find(i.prepare.begin(), i.prepare.end(), (c.end() - 1) -> code);
                if (j != i.prepare.end())
                    i.prepare.erase(j);
            }
            c.pop_back();
        }
        cout << endl;
    }
    fin.close();
    return 0;
}