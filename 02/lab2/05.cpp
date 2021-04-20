#include <bits/stdc++.h>
#include "03.h"

using namespace std;

class node {
    public:
        double a;
        int e;
};

class poly {
    public:
        void print() {
            for (auto i = p.begin(); i != p.end(); i = i->next)
                printf("(%.2f, %d) ", i->val.a, i->val.e);
            printf("\n");
        }
        void push(double a, int e) {
            node tmp;
            tmp.a = a;
            tmp.e = e;
            p.insert(p.end(), tmp);
        }
        poly & operator += (poly & t) {
            for (auto i = t.p.begin(); i != t.p.end(); i = i -> next)
                p.insert(p.end(), i -> val);
            merge();
            return *this;
        }
        poly & operator -= (poly & t) {
            for (auto i = t.p.begin(); i != t.p.end(); i = i -> next) {
                auto tmp = i -> val;
                tmp.a *= -1;
                p.insert(p.end(), tmp);
            }
            merge();
            return *this;
        }
        poly & operator *= (poly & t) {
            poly ans;
            for (auto i = p.begin(); i != p.end(); i = i -> next)
                for (auto j = t.p.begin(); j != t.p.end(); j = j -> next) {
                    node tmp;
                    tmp.a = i->val.a * j->val.a;
                    tmp.e = i->val.e + j->val.e;
                    ans.push(tmp.a, tmp.e);
                }
            while (!p.empty())
                p.erase(p.begin());
            for (auto i = ans.p.begin(); i != ans.p.end(); i = i -> next)
                p.insert(p.end(), i->val);
            merge();
            return *this;
        }
    private:
        linkedlist<node> p;
        void merge() {
            p.sort([](node & a, node & b) {
                return a.e < b.e;
            });
            auto i = p.begin();
            for (; i->next != p.end();) {
                if (i -> val.e == i -> next -> val.e || i -> val.a == 0) {
                    i -> next -> val.a += i -> val.a;
                    i = p.erase(i);
                }
                else
                    i = i -> next;
            }
            if (i -> val.a == 0)
                p.erase(i);
        }
};

int main() {
    poly a, b;
    for (auto i = 0; i < 3; i++)
        a.push(rand()%10, rand()%10);
    for (auto i = 0; i < 3; i++)
        b.push(rand()%10, rand()%10);
    a.print();
    b.print();
    (a*=b).print();
    return 0;
}