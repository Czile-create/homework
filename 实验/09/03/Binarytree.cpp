#ifndef _BINARYTREE_CPP_
#define _BINARYTREE_CPP_
#include "Binarytree.h"
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <stack>
#include <map>

template <typename T> Binarytree<T>::Binarytree(): p(nullptr), t(nullptr) {}
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
    t = nullptr;
}

template <typename T> template <typename InputIterator>
Binarytree<T>::Binarytree(
    InputIterator firstPre, 
    InputIterator lastPre,
    InputIterator firstInorder, 
    InputIterator lastInorder
) {
    p = nullptr;
    t = nullptr;
    __CreateTreeByNLRandLNR(firstPre, lastPre, firstInorder, lastInorder, p);
}

template <typename T> Binarytree<T>::Binarytree(const Binarytree &x) {
    p = __deepcopy(x.root());
    t = nullptr;
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
    erase(t);
    t = nullptr;
}

template <typename T> void Binarytree<T>::erase(
    Binarytreenode *& p
) {
    if (p == nullptr)
        return;
    erase(p -> left);
    erase(p -> right);
    delete p;
    p = nullptr;
}

template <typename T> void Binarytree<T>::erase(
    thrnode *& p
) {
    if (p == nullptr)
        return;
    if (!p -> ltag) erase(p -> left);
    if (!p -> rtag) erase(p -> right);
    delete p;
    p = nullptr;
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
    std::queue<Binarytreenode*> q;
    std::vector<T> ans;
    q.push(p);
    while (q.size()) {
        auto y = q.front();
        ans.push_back(y -> val);
        if (y -> left) q.push(y -> left);
        if (y -> right) q.push(y -> right);
        q.pop();
    }
    return ans;
}

template <typename T> std::string Binarytree<T>::info(std::string(*tostr)(const T&)) const noexcept {
    std::string ans;
    ans += "The number of the node in this tree is: " + std::to_string(size()) +".\n";
    ans += "The number of the leaf in this tree is: " + std::to_string(sizeOfLeaf()) + ".\n";
    ans += "The depth of the tree is: " + std::to_string(depth()) + ".\n";
    ans += "name\tdepth\tparents\tleftchild\trightchild\n";
    std::queue<std::pair<Binarytreenode*, int>> q;
    if (p) q.push(std::make_pair(p, 1));
    while (q.size()) {
        auto tmp = q.front().first;
        ans += tostr(tmp -> val) + "\t";
        ans += std::to_string(q.front().second) + "\t";
        ans += ((tmp -> parents) ? tostr(tmp -> parents -> val) 
                : "null") + "\t";
        ans += ((tmp -> left) ? tostr(tmp -> left -> val) 
                : "null") + "\t";
        ans += ((tmp -> right) ? tostr(tmp -> right -> val) 
                : "null") + "\n";
        if (tmp -> left) q.push(std::make_pair(tmp -> left, q.front().second + 1));
        if (tmp -> right) q.push(std::make_pair(tmp -> right, q.front().second + 1));
        q.pop();
    }
    return ans;
}

template <typename T> std::string Binarytree<T>::print(std::string(*tostr)(const T&)) const noexcept {
    return __print(p, 0, tostr);
}

template <typename T> std::string Binarytree<T>::__print(
    const Binarytreenode * p,
    const size_t depth, 
    std::string (*tostr) (const T&)
) const noexcept{
    if (p == nullptr) return "";
    std::string ans;
    for (int i = 0; i < int(depth) - 1; ++i)
        ans += "|     ";
    ans += (!depth) ? tostr(p -> val) + "\n" : "|---->" + tostr(p -> val) + "\n" ;
    ans += __print(p -> left, depth + 1, tostr);
    ans += __print(p -> right, depth + 1, tostr);
    return ans;
}

template <typename T> size_t Binarytree<T>::size() const noexcept {
    return BFS().size();
}

template <typename T> size_t Binarytree<T>::depth() const noexcept {
    if (p == nullptr) return 0;
    std::queue<std::pair<Binarytreenode*, int>> q;
    std::vector<int> t;
    if (p) q.push(std::make_pair(p, 1));
    while (q.size()) {
        auto tmp = q.front().first;
        t.push_back(q.front().second);
        if (tmp -> left) q.push(std::make_pair(tmp -> left, q.front().second + 1));
        if (tmp -> right) q.push(std::make_pair(tmp -> right, q.front().second + 1));
        q.pop();
    }
    return *std::max_element(t.begin(), t.end());
}

template <typename T> size_t Binarytree<T>::sizeOfLeaf() const noexcept {
    std::queue<Binarytreenode*> q;
    int ans = 0;
    if (p) q.push(p);
    while (q.size()) {
        auto tmp = q.front();
        if (tmp -> left) q.push(tmp -> left);
        if (tmp -> right) q.push(tmp -> right);
        if (!(tmp -> right || tmp -> left)) ++ans;
        q.pop();
    }
    return ans;
}

template <typename T> template <typename InputIterator> void Binarytree<T>::__CreateTreeByNLRandLNR(
    InputIterator firstPre, 
    InputIterator lastPre,
    InputIterator firstInorder, 
    InputIterator lastInorder, 
    Binarytreenode * &p
) {
    if (firstPre >= lastPre) return;
    p = new Binarytreenode(*firstPre);
    auto f = std::find(firstInorder, lastInorder, *firstPre);
    while (f != lastInorder && !_ismatch(
        std::vector<T>(firstPre + 1, firstPre + 1 + int(f - firstInorder)), 
        std::vector<T>(firstInorder, f)
    )) f = std::find(f + 1, lastInorder, *firstPre);
    if (f == lastInorder) throw "Invalid traversal to initialize the tree.\n";
    __CreateTreeByNLRandLNR (
        firstPre + 1,
        firstPre + 1 + int(f - firstInorder),
        firstInorder, 
        f, p->left 
    );
    __CreateTreeByNLRandLNR (
        firstPre + 1 + int(f - firstInorder),
        lastPre, 
        f + 1, 
        lastInorder, p->right 
    );
    if (p -> left) p -> left -> parents = p;
    if (p -> right) p -> right -> parents = p;
}

template <typename T> 
bool Binarytree<T>::_ismatch(std::vector<T> a, std::vector<T> b) {
    std::map<T, int> tmp;
    for (auto i: a) ++tmp[i];
    for (auto i: b) --tmp[i];
    for (auto &i: tmp) 
        if (i.second)
            return false;
    return true;
} 

template <typename T> void Binarytree<T>::_preorder(
    const Binarytreenode * p,
    thrnode *& y, thrnode *& pre
) noexcept {
    if (p == nullptr) return;
    y = new thrnode(p -> val);
    if (pre && pre -> rtag) pre -> right = y;
    y -> rtag = !(p -> right);
    y -> ltag = !(p -> left);
    if (y -> ltag) y -> left = pre;
    pre = y;
    _preorder(p -> left, y -> left, pre);
    _preorder(p -> right, y -> right, pre);
}

template <typename T> void Binarytree<T>::_inorder(
    const Binarytreenode * p,
    thrnode *& y, thrnode *& pre
) noexcept {
    if (p == nullptr) return;
    y = new thrnode(p -> val);
    _inorder(p -> left, y -> left, pre);
    if (pre && pre -> rtag) pre -> right = y;
    y -> rtag = !(p -> right);
    y -> ltag = !(p -> left);
    if (y -> ltag) y -> left = pre;
    pre = y;
    _inorder(p -> right, y -> right, pre);
}

template <typename T> void Binarytree<T>::_postorder(
    const Binarytreenode * p,
    thrnode *& y, thrnode *& pre
) noexcept {
    if (p == nullptr) return;
    y = new thrnode(p -> val);
    _postorder(p -> left, y -> left, pre);
    _postorder(p -> right, y -> right, pre);
    if (pre && pre -> rtag) pre -> right = y;
    y -> rtag = !(p -> right);
    y -> ltag = !(p -> left);
    if (y -> ltag) y -> left = pre;
    pre = y;
}

template <typename T> typename Binarytree<T>::thrnode * 
Binarytree<T>::getPreThrBiTree() noexcept {
    null = nullptr;
    _preorder(p, t, null);
    return t;
}

template <typename T> typename Binarytree<T>::thrnode * 
Binarytree<T>::getInThrBiTree() noexcept {
    null = nullptr;
    _inorder(p, t, null);
    return t;
}

template <typename T> typename Binarytree<T>::thrnode * 
Binarytree<T>::getPostThrBiTree() noexcept {
    null = nullptr;
    _inorder(p, t, null);
    return t;
}

template <typename T> typename Binarytree<T>::thrnode * 
Binarytree<T>::getBFSThrBiTree() noexcept {
    erase(t);
    if (p == nullptr) return t;
    std::vector<thrnode *> ans;
    std::queue<Binarytreenode *> tmp;
    auto i = 0;
    ans.push_back(new thrnode(p -> val));
    tmp.push(p);
    while (i < ans.size()) {
        auto _p = tmp.front();
        if (_p -> left) {
            ans.push_back(
                ans[i] -> left = new thrnode(_p -> left -> val)
            ); 
            tmp.push(_p -> left);
        } else {
            ans[i] -> ltag = 1;
            if (i) ans[i] -> left = ans[i - 1];
        }
        if (_p -> right) {
            ans.push_back(
                ans[i] -> right = new thrnode(_p -> right -> val)
            ); 
            tmp.push(_p -> right);
        } else {
            ans[i] -> rtag = 1;
            if (i != ans.size() - 1) ans[i] -> right = ans[i + 1];
        }
        ++i;
        tmp.pop();
    }
    return t = ans[0];
}

template <typename T> std::vector<T> Binarytree<T>::preorder() const noexcept {
    if (p == nullptr) return std::vector<T>();
    std::vector<T> ans;
    std::stack<std::pair<Binarytreenode *, int>> status;
    status.push(std::make_pair(p, 0));
    while (status.size()) {
        auto tmp = status.top().first;
        switch (status.top().second) {
            case 0: ++status.top().second;
                    ans.push_back(tmp -> val);
                    if (tmp -> left) status.push(std::make_pair(tmp -> left, 0));
                    break;
            case 1: ++status.top().second;
                    if (tmp -> right) status.push(std::make_pair(tmp -> right, 0));
                    break;
            default: status.pop();
        }
    }
    return ans;
}

template <typename T> std::vector<T> Binarytree<T>::inorder() const noexcept {
    if (p == nullptr) return std::vector<T>();
    std::vector<T> ans;
    std::stack<std::pair<Binarytreenode *, int>> status;
    status.push(std::make_pair(p, 0));
    while (status.size()) {
        auto tmp = status.top().first;
        switch (status.top().second) {
            case 0: ++status.top().second;
                    if (tmp -> left) status.push(std::make_pair(tmp -> left, 0));
                    break;
            case 1: ++status.top().second;
                    ans.push_back(tmp -> val);
                    if (tmp -> right) status.push(std::make_pair(tmp -> right, 0));
                    break;
            default: status.pop();
        }
    }
    return ans;
}

template <typename T> std::vector<T> Binarytree<T>::postorder() const noexcept {
    if (p == nullptr) return std::vector<T>();
    std::vector<T> ans;
    std::stack<std::pair<Binarytreenode *, int>> status;
    status.push(std::make_pair(p, 0));
    while (status.size()) {
        auto tmp = status.top().first;
        switch (status.top().second) {
            case 0: ++status.top().second;
                    if (tmp -> left) status.push(std::make_pair(tmp -> left, 0));
                    break;
            case 1: ++status.top().second;
                    if (tmp -> right) status.push(std::make_pair(tmp -> right, 0));
                    break;
            default: 
                    ans.push_back(tmp -> val);
                    status.pop();
        }
    }
    return ans;
}

#endif