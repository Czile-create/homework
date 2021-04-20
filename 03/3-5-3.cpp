#include <bits/stdc++.h>
#include "D:\Work\LinuxProgram\cpp\homework\2\stl\clist.h"

using namespace std;

template <class T, unsigned n>
class que {
    public:
        que(): flag(0u), first(0u), last(0u) {}
        bool push(T& v) {
            if ((first == last) && flag) {
                return 1;
            } else {
                cout<<first<<", "<<last<<endl;
                p[last] = v;
                last = (last + 1) % n;
                flag = 1;
                return 0;
            }
        }
        T pop() {
            if (flag) {
                auto tmp = p[first];
                first = (first + 1) % n;
                if (first == last)
                    flag = 0;
                return tmp;
            }
            return T();
        }
        void print() {
            if (flag) {
                auto t = first + 1;
                cout<<p[first]<<" ";
                for (; t != last; t = (t+1) % n) 
                    cout<<p[t]<<" ";
            }
            cout<<endl;
        }
    private:
        clist<T, n> p;
        unsigned first, last;
        bool flag; 
};


int main() {
    que<int, 10> p;
    for (auto i=0; i<8; i++)
        p.push(i);
    p.print();
    p.pop();
    p.print();
    for (auto i=2; i<6; i++)
        p.push(i);
    p.print();
    for (auto i=0; i<100; i++)
        p.pop();
    p.print();
}