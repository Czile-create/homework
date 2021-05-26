// #include "haffman-tree.h"

haffman_tree::haffman_tree(): _val(0), _weight(0), _left(nullptr), _right(nullptr), _father(nullptr) {}
haffman_tree::haffman_tree(wchar_t value): _val(value), _weight(0), _left(nullptr), _right(nullptr), _father(nullptr) {}
haffman_tree::haffman_tree(haffman_tree* a, haffman_tree* b):
_val(0), _weight(a->weight()+b->weight()), _left(a), _right(b), _father(nullptr) {
    a->getfather() = this;
    b->getfather() = this;
}
haffman_tree::haffman_tree(wchar_t value, unsigned long long w): 
_val(value), _weight(w), _left(nullptr), _right(nullptr), _father(nullptr) {}

bool haffman_tree::isleaf() const {
    if (_left==nullptr && _right==nullptr)
        return true;
    return false;
}

unsigned long long & haffman_tree::weight() {
    return _weight;
}

wchar_t & haffman_tree::val() {
    return _val;
}

bool haffman_tree::left() const {
    if (_left==nullptr)
        return false;
    return true;
}

bool haffman_tree::right() const {
    if (_right==nullptr)
        return false;
    return true;
}

bool haffman_tree::father() const {
    if (_father==nullptr)
        return false;
    return true;
}

haffman_tree * & haffman_tree::getleft() {
    return _left;
}

haffman_tree * & haffman_tree::getright() {
    return _right;
}

haffman_tree * & haffman_tree::getfather() {
    return _father;
}