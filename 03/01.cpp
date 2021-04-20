// Reverse the stack

#include <bits/stdc++.h>
using namespace std;

template <class T>
void reverse(stack<T> & t) {
    queue<T> q;
    while (t.size()) {
        q.push(t.top());
        t.pop();
    }
    while (q.size()) {
        t.push(q.front());
        q.pop();
    }
}

int main() {
    stack<int> p;
    for (int i=0; i<10; i++)
        p.push(i);
    reverse(p);
    while (p.size()) {
        cout<<p.top()<<"\t";
        p.pop();
    }
    return 0;
}