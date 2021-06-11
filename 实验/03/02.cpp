// Merge the queue

#include <bits/stdc++.h>
using namespace std;

template <class T>
queue<T> merge(vector<queue<T>> & p) {
    auto n = accumulate(p.begin(), p.end(), 0, [](int i, queue<T> j) {
        return i + j.size();
    });
    queue<T> ans;
    while (n) 
        for (auto & i: p) 
            if (i.size()) {
                ans.push(i.front());
                i.pop();
                --n;
            }
    return ans;
}

int main() {
    queue<int> p, q;
    for (int i=0; i<10; i++)
        p.push(i);
    for (int i=11; i<16; i++)
        q.push(i);
    vector<queue<int>> t;
    t.push_back(p);
    t.push_back(q);
    auto ans = merge(t);
    while (ans.size()) {
        cout<<ans.front()<<"\t";
        ans.pop();
    }
}