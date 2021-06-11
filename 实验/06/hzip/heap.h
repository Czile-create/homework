#ifndef _HEAP_H_
#define _HEAP_H_
#include <bits/stdc++.h>
#include "haffman-tree.h"

class heap {
    public:
        inline void push(haffman_tree*);
        inline void pop();
        inline haffman_tree * & front();
        inline bool empty() const;
        inline unsigned size() const;
    private:
        std::vector<haffman_tree*> lst;
        inline void up(unsigned);
        inline void down(unsigned);
};

#include "heap.cpp"

#endif