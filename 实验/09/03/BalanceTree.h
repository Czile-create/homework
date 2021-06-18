#ifndef _BALANCETREE_H_
#define _BALANCETREE_H_
#include "Binarytree.h"

//demo
class BalanceTree: public Binarytree<int> {
    public:
        void push(int val);
        Binarytree<int>::Binarytreenode* find();
    private:
        size_t _depth(Binarytreenode * p) {
            Binarytree tmp;
            tmp.root() = __deepcopy(p);
            return tmp.depth();
        }
        void __push(Binarytreenode * &p, int val);
        Binarytreenode * LL(Binarytreenode *);
        Binarytreenode * LR(Binarytreenode *);
        Binarytreenode * RL(Binarytreenode *);
        Binarytreenode * RR(Binarytreenode *);
};

void BalanceTree::push(int val) {
    __push(root(), val);
}
Binarytree<int>::Binarytreenode* BalanceTree::LL(Binarytree<int>::Binarytreenode *p) {
    auto tmp = p -> left;
    p -> left = tmp -> right;
    tmp -> right = p;
    return p = tmp;
}
Binarytree<int>::Binarytreenode* BalanceTree::RR(Binarytree<int>::Binarytreenode *p) {
    auto tmp = p -> right;
    p -> right = tmp -> left;
    tmp -> left = p;
    return p = tmp;
}
Binarytree<int>::Binarytreenode* BalanceTree::LR(Binarytree<int>::Binarytreenode *p) {
    RR(p -> left);
    return LL(p);
}
Binarytree<int>::Binarytreenode* BalanceTree::RL(Binarytree<int>::Binarytreenode *p) {
    LL(p -> right);
    return RR(p);
}

void BalanceTree::__push(Binarytreenode *&p, int val) {
    // std::cerr << val << std::endl;
    if (p == nullptr)
        p = new Binarytreenode(val);
    else if (p -> val >= val) {
        __push(p -> left, val);
        if (int(_depth(p -> left)) - int(_depth(p -> right)) > 1)
            p = (p -> left -> val >= val) ? LL(p) : LR(p);
    } else if (p -> val < val) {
        __push(p -> right, val);
        if (int(_depth(p -> right)) - int(_depth(p -> left)) > 1)
            p = (p -> right -> val < val) ? RR(p) : RL(p);
    }
}
#endif