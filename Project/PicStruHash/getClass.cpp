#include <bits/stdc++.h>
using namespace std;
class Pic {
    public:
        Pic(): visited(0) {}
        Pic(string s): name(s), visited(0) {}
        string name;
        bool visited;
        vector<Pic*> neighbor;
};

int main() {
    ifstream fin("picSimilar1.log", ios::in);
    ofstream fout("picClass.txt", ios::out);
    Pic piclist[3000];
    int i = 0;
    while (!fin.eof()) {
        string s;
        getline(fin, s);
        cout << s << endl;
        smatch sm;
        string filename1 = "", filename2 = "";
        if (regex_search(s.cbegin(), s.cend(), sm, regex("'(.*?)'")))
            filename1 = sm[1];
        if (regex_search(sm[0].second, s.cend(), sm, regex("'(.*?)'")))
            filename2 = sm[1];
        

        auto iter = find_if(piclist, piclist + i, [&filename1](auto x) {
            return x.name == filename1;
        });
        if (iter == piclist + i)
            piclist[i++].name = filename1;
        iter = find_if(piclist, piclist + i, [&filename2](auto x) {
            return x.name == filename2;
        });
        if (iter == piclist + i)
            piclist[i++].name = filename2;
        
        find_if(piclist, piclist + i, [&filename1](auto x) {
            return x.name == filename1;
        }) -> neighbor.push_back(find_if(piclist, piclist + i, [&filename2](auto x) {
            return x.name == filename2;
        }));
        find_if(piclist, piclist + i, [&filename2](auto x) {
            return x.name == filename2;
        }) -> neighbor.push_back(find_if(piclist, piclist + i, [&filename1](auto x) {
            return x.name == filename1;
        }));
    }
    int n = i, k = 0;
    i = 0;
    while (i != n) {
        if (piclist[i].visited == 0) {
            piclist[i].visited = 1;
            fout<<"Group "<<(++k)<<endl<<endl;
            queue<Pic*> q;
            q.push(piclist + i);
            while (q.size()) {
                auto iter = q.front();
                fout << iter -> name << endl;
                for (auto &j: iter -> neighbor)
                    if (j -> visited == 0) {
                        j -> visited = 1;
                        q.push(j);
                    }
                q.pop();
            }
        }
        i++;
    }
    fin.close();
    fout.close();
}