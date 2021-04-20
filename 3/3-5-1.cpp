#include <bits/stdc++.h>
#include "D:\Work\LinuxProgram\cpp\homework\2\stl\cyclelist.h"

using namespace std;

template <class T>
class que {
    public:
        void push(const T& v) {
            p.insert(p.end(), v);
        }
        T pop() {
            auto t = p.end() -> next -> val;
            p.erase(p.end() -> next);
            return t;
        }
        void print() const {
            p.print();
        }
    private:
        cyclelist<T> p;
};

int main() {
    que<int> p;
    for (auto i=0; i<10; i++)
        p.push(i);
    p.print();
    for (auto i=0; i<5; i++)
        cout<<p.pop()<<" ";
    cout<<endl;
    for (auto i=9; i>0; i--)
        p.push(i);
    p.print();
    return 0;
}