// Greedy algorithm

#include <bits/stdc++.h>
using namespace std;

template <class T>
class que: public queue<T> {
public:
    int num;
};

void rearrange(vector<int> &p, unsigned k) {
    auto t = is_sorted_until(p.begin(), p.end(), [] (auto &i, auto &j) {
        return i > j;
    }) - p.begin();
    auto q = new que<int>[k+1];
    for (auto i=0; i<=k; i++) 
        q[i].num = i;
    auto n = p.size();
    while (p.size() - t - 1) {
        sort(q, q+k, [] (auto &i, auto &j) {
            return i.size() && j.size() && i.back() > j.back();
        });
        auto tmp = find_if(q, q+k, [&p](auto& z) {return !z.size() || z.back() < p.front();});
        if (tmp == q+k && q[k].size() && q[k].front() + 1 != p.front()) {
            cerr<<"CANNOT REARRANGE!!\n";
            return;
        }
        tmp -> push(p.front());
        p.erase(p.begin());
        printf("Let %d from %d to %d\n", tmp -> back(), -1, tmp -> num);
    }
    while (n - q[k].size() - p.size()) {
        sort(q, q+k, [](auto &i, auto &j) {
            return i.size() ? !j.size() || i.front() < j.front() : 0;
        });
        q[k].push(q[0].front());
        q[0].pop();
        printf("Let %d from %d to %d\n", q[k].back(), q[0].num, k);
    }
    while (p.size()) {
        printf("Let %d from %d to %d\n", p.front(), -1, k);
        p.erase(p.begin());
    }
}

int main() {
    vector<int> p;
    p.push_back(1);
    p.push_back(4);
    p.push_back(2);
    p.push_back(5);
    p.push_back(3);
    p.push_back(6);
    p.push_back(7);
    rearrange(p, 2);
    return 0;
}