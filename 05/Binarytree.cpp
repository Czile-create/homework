#ifndef _BINARYTREE_CPP_
#define _BINARYTREE_CPP_
#include "Binarytree.h"
#include <vector>
#include <iostream>
#include <queue>
#include <string>
// using namespace Binarytree<T>;

template <typename T> Binarytree<T>::Binarytree(): p(nullptr) {}
template <typename T> template <typename InputIterator>
Binarytree<T>::Binarytree(
    InputIterator first,
    InputIterator last,
    const T & default_value
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
    p = nullptr;
    clear();
    p = __deepcopy(x.root());
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
    p = nullptr;
}

template <typename T> void Binarytree<T>::erase(
    Binarytree<T>::Binarytreenode* p
) {
    if (p == nullptr)
        return;
    erase(p -> left);
    erase(p -> right);
    delete p;
}

template <typename T> typename Binarytree<T>::Binarytreenode* Binarytree<T>::insert(
    Binarytreenode * p,
    const T & val, 
    const int _pos
) {
    if (p == nullptr)
        throw "Invalid position to insert.(-1)";
    switch (_pos) {
        case 0:  if (p -> left) throw "Invalid position to insert.(0)";
            p -> left = new Binarytreenode(val);
            p -> left -> parents = p;
            break;
        case 1:  if (p -> right) throw "Invalid position to insert.(1)";
            p -> right = new Binarytreenode(val);
            p -> right -> parents = p;
            break;
        default: throw "Invalid position to insert. (-1)";
    }
    return p;
}

template <typename T> std::vector<T> Binarytree<T>::Preorder() const noexcept {
    return __preorder(p);
}

template <typename T> std::vector<T> Binarytree<T>::Inorder() const noexcept {
    return __inorder(p);
}

template <typename T> std::vector<T> Binarytree<T>::Postorder() const noexcept {
    return __postorder(p);
}

template <typename T> std::vector<T> Binarytree<T>::__preorder(
    const Binarytreenode * p
) const noexcept {
    if (p == nullptr) return std::vector<T>();
    std::vector<T> ans = {p -> val};
    auto tmp = __preorder(p -> left);
    ans.insert(ans.end(), tmp.begin(), tmp.end());
    tmp = __preorder(p -> right);
    ans.insert(ans.end(), tmp.begin(), tmp.end());
    return ans;
}

template <typename T> std::vector<T> Binarytree<T>::__inorder(
    const Binarytreenode * p
) const noexcept {
    if (p == nullptr) return std::vector<T>();
    auto ans = __inorder(p -> left);
    ans.push_back(p -> val);
    auto tmp = __inorder(p -> right);
    ans.insert(ans.end(), tmp.begin(), tmp.end());
    return ans;
}

template <typename T> std::vector<T> Binarytree<T>::__postorder(
    const Binarytreenode * p
) const noexcept {
    if (p == nullptr) return std::vector<T>();
    auto ans = __postorder(p -> left);
    auto tmp = __postorder(p -> right);
    ans.insert(ans.end(), tmp.begin(), tmp.end());
    ans.push_back(p -> val);
    return ans;
}

template <typename T> std::vector<T> Binarytree<T>::BFS() const noexcept {
    if (p == nullptr) return std::vector<T>();
    std::queue<T> q;
    std::vector<T> ans;
    q.push(p);
    while (q.size()) {
        auto y = q.top();
        ans.push_back(y -> val);
        if (y -> left) q.push(y -> left);
        if (y -> right) q.push(y -> right);
    }
    return ans;
}

template <typename T> std::string Binarytree<T>::info() const noexcept {
    auto ans;
    ans += "The number of the node in this tree is: " + size() +".\n";
    ans += "The number of the leaf in this tree is: " + sizeOfLeaf() + ".\n";
    ans += "The depth of the tree is: " + depth() + ".\n";
    // @todo
}

#endif