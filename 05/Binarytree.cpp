#ifndef _BINARYTREE_CPP_
#define _BINARYTREE_CPP_
#include "Binarytree.h"
#include <vector>
#include <iostream>
// using namespace Binarytree<T>;

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
            (*first == default_value) ? nullptr : new Binarytreenode(*first)
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

template <typename T> Binarytree<T>::Binarytree(const Binarytree &x) {
    *this = x;
}
template <typename T> Binarytree<T> & Binarytree<T>::operator=(const Binarytree &x) {
    clear();
    p = __deepcopy(x.root());
    return *this;
}
template <typename T> typename Binarytree<T>::Binarytreenode* Binarytree<T>::__deepcopy(
    const Binarytreenode *x
) const noexcept{
    if (x == nullptr)
        return nullptr;
    auto ans = new Binarytreenode(x -> val);
    ans -> left = __deepcopy(x -> left);
    ans -> right = __deepcopy(x -> right);
    if (ans -> left) ans -> left -> parents = ans;
    if (ans -> right) ans -> right -> parents = ans;
    return ans;
}

template <typename T> Binarytree<T>::~Binarytree() {
    clear();
}

template <typename T> void Binarytree<T>::clear() {
    erase(p);
}

template <typename T> typename Binarytree<T>::Binarytreenode* Binarytree<T>::erase(
    Binarytree<T>::Binarytreenode* p
) {
    if (p == nullptr)
        return nullptr;
    erase(p -> left);
    erase(p -> right);
    auto retval = p -> parents;
    delete p;
    return retval;
}



#endif