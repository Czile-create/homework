#include <bits/stdc++.h>
#include "linkedlist.h"
#include "cyclelist.h"
using namespace std;

int main() {
    srand(time(0));
    linkedlist<char> p;
    for (auto i=0; i<30; i++) 
        p.insert(p.end(), rand() % 127);
    try {
        cyclelist<char> q[3];
        for (auto z = p.begin(); z != p.end(); z = z -> next) {
            if (z -> val >= '0' && z -> val <= '9')
                q[0].insert(q[0].begin(), z -> val);
            else if (z -> val >= 'a' && z -> val <= 'z' || z -> val >= 'A' && z -> val <= 'Z')
                q[1].insert(q[1].begin(), z -> val);
            else
                q[2].insert(q[2].begin(), z -> val);
        }
        q[0].print();
        q[1].print();
        q[2].print();
    } catch (const char * e) {
        cout<<e<<endl;
    }

    return 0;
}