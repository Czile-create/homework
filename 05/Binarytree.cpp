#ifndef _BINARYTREE_CPP_
#define _BINARYTREE_CPP_
#include "Binarytree.h"
#include <vector>

template <typename T> Binarytree<T>::Binarytree(): p(nullptr) {}
template <typename T> template <typename InputIterator>
Binarytree<T>::Binarytree(
    InputIterator first,
    InputIterator last,
    T && default_value
) {
    std::vector<Binarytreenode*> tmp;
    for (; first != last; ++first) {
        tmp.push_back(
            (*first == default_value) ? nullptr : new Binarytreenode
        );
        if (tmp.back() && tmp.size() > 1) {
            auto &y = tmp[tmp.size()/2 - 1];
            if (y == nullptr)
                throw "Invalid exception";
            tmp.back()->parents = y;
            if (y == tmp[(tmp.size()+1)/2 - 1])
                y -> left = tmp.back();
            else
                y -> right = tmp.back();
            tmp.back()->val = *first;
        }
    }
    p = tmp.front();
}

template <typename T> template <typename InputIterator>
Binarytree<T>::Binarytree(
    InputIterator firstPre, 
    InputIterator lastPre,
    InputIterator firstInorder, 
    InputIterator lastInorder
) {
    __CreateTreeByNLRandLNR(firstPre, lastPre, firstInorder, lastInorder);
}



#endif