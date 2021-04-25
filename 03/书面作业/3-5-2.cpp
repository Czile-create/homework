#include <bits/stdc++.h>
#include "D:\Work\LinuxProgram\cpp\homework\2\stl\cyclelist.h"
using namespace std;    

template <class T>
void reVal(stack<T> & t) {
    cyclelist<T> q;
    auto p = q.begin();
    while (t.size()) {
        if (t.size() % 2)
            p = q.insert(p, t.top()) -> next;
        else 
            q.insert(q.end(), t.top());
        t.pop();
    }
    t.reverse();
    t.push(p -> val);
    for (auto tmp = p -> next; tmp != p; tmp = tmp -> next == q.end() ? tmp -> next -> next : tmp -> next)
        t.push(tmp -> val);
}

int main() {
    stack<int> p;
    for (unsigned i = 1; i <= 10; i++)
        p.push(i);
    reVal(p);
    for (; p.size(); p.pop())
        cout<<p.top()<<" ";
    cout<<endl;
    return 0;
}