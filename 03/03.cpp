// Greedy algorithm

#include <bits/stdc++.h>
using namespace std;

template <class T>
class que: public queue<T> {
public:
    int num;
};

template <class T>
bool cmp(que<T>& i, que<T> &j) {
    return i.back() > j.back();
}

void rearrange(queue<int> &p, unsigned k) {
    auto q = new que<int>[k+1];
    for (auto i=0; i<=k; i++) 
        q[i].num = i;
    auto n = p.size();
    while (p.size()) {
        sort(q, q+k, [] (auto &i, auto &j) {
            return i.size() && j.size() && i.back() > j.back();
        });
        auto tmp = find_if(q, q+k, [&p](auto& z) {return !z.size() || z.back() < p.front();});
        if (tmp == q+k && q[k].size() && q[k].front() + 1 != p.front()) {
            cerr<<"CANNOT REARRANGE!!\n";
            return;
        }
        // cout<<2;
        tmp -> push(p.front());
        p.pop();
        printf("Let %d from %d to %d\n", tmp -> back(), -1, tmp -> num);
    }
    while (n - q[k].size()) {
        sort(q, q+k, [](auto &i, auto &j) {
            return !j.size() || i.size() && i.front() < j.front();
        });
        q[k].push(q[0].front());
        q[0].pop();
        printf("Let %d from %d to %d\n", q[k].back(), q[0].num, k);
    }
}

int main() {
    queue<int> p;
    p.push(1);
    p.push(4);
    p.push(2);
    p.push(5);
    p.push(3);
    p.push(6);
    p.push(7);
    rearrange(p, 3);
    return 0;
}