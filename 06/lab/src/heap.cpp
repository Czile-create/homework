// #include "heap.h"

void heap::up(unsigned n) {
    if (n==0) return;
    unsigned k=(n-1)/2;
    if (lst[n]->weight()<lst[k]->weight()) {
        std::swap(lst[n], lst[k]);
        up(k);
    }
}

void heap::down(unsigned n) {
    unsigned k=2*(n+1)-1;
    if (lst.size()<=k) return;
    if (lst.size()>k+1 && lst[k+1]->weight()<lst[k]->weight())
        k++;
    if (lst[n]->weight()>lst[k]->weight()) {
        std::swap(lst[n],lst[k]);
        down(k);
    }
}

void heap::push(haffman_tree * v) {
    lst.push_back(v);
    up(lst.size()-1);
}

void heap::pop() {
    if (lst.size()==0)
        return;
    if (lst.size()==1)
        lst.pop_back();
    else {
        lst[0]=lst[lst.size()-1];
        lst.pop_back();
        down(0);
    }
}

haffman_tree * & heap::front() {
    return lst[0];
}

bool heap::empty() const{
    return lst.empty();
}

inline unsigned heap::size() const {
    return lst.size();
}