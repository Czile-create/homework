#include <bits/stdc++.h>
using namespace std;

template <class T>
class LinkedListNode {
    public:
        T val;
        LinkedListNode * next;
};

// This is an easy linkedlist.
template <class T>
class linkedlist {
    public:
        // Constructs and Destroys an linkedlist.
        linkedlist();
        ~linkedlist();
        // Insert an element in the position, return a pointer that points to the first of the newly inserted elements.
        LinkedListNode<T>* insert(LinkedListNode<T>* position, const T&val);
        // Delete an element in the position, return a pointer that points to the next element.
        // NOTE: we will NOT ensure whether the position is in the linkedlist or not!!
        LinkedListNode<T>* erase(LinkedListNode<T>* position);
        // If there are no element in the list, return true.
        bool empty() const noexcept {
            return (!_size);
        }
        // return the pointer that points to the first element.
        LinkedListNode<T>* begin() noexcept {
            return _first;
        }
        LinkedListNode<T>* end() noexcept {
            return _last;
        }
        // return the number of elements in the linkedlist.
        uint64_t size() const noexcept {
            return _size;
        }
        // Print the linkedlist.
        void print() const noexcept{
            for (auto p = _first; p != _last; p = p -> next)
                cout<<(p->val)<<" ";
            cout<<endl;
        }
        // reverse the element of the linkedlist
        void reverse();
        // sort the element of the linkedlist
        // NOTE: to use this function, you MUST write a funcion of the operator <
        void sort(bool(*cmp)(const T&a, const T&b));
    private:
        LinkedListNode<T>* _first, *_last;
        uint64_t _size;
        // Quick sort
        void _sort(LinkedListNode<T>* first, LinkedListNode<T>* last, bool(*cmp)(const T&a, const T&b));
};

template <class T>
linkedlist<T>::linkedlist() {
    _last = new LinkedListNode<T>;
    // This is to ensure the pointer is safe.
    _last->next = _last;
    _first = _last;
    _size = 0;
}

template <class T>
linkedlist<T>::~linkedlist() {
    while (!empty()) {
        erase(_first);
    }
    delete _first;
}

template <class T>
LinkedListNode<T>* linkedlist<T>::insert(LinkedListNode<T>* position, const T&val) {
    auto tmp = new LinkedListNode<T>;
    tmp -> val = position -> val;
    tmp -> next = position -> next;     //new a node, and make the position's be the node.
    position -> val = val;
    position -> next = tmp;
    if (position == _last) {
        _last = tmp;
        _last -> next = _last;
    }
    _size++;
    return position;
}

template <class T>
LinkedListNode<T>* linkedlist<T>::erase(LinkedListNode<T>* position) {
    if (position == _last)
        return _last;
    auto tmp = position -> next;
    position -> val = position -> next -> val;
    position -> next = position -> next -> next;
    delete tmp;
    if (tmp == _last) {
        _last = position;
        position -> next = _last;
    }
    _size--;
    return position;
}

template <class T>
void linkedlist<T>::reverse() {
    auto p = _last;
    for (auto i=0; i<_size; i++) {
        p = insert(p, _first->val);
        erase(_first);
    }
}

template <class T>
void linkedlist<T>::sort(bool(*cmp)(const T&a, const T&b)) {
    _sort(_first, _last, cmp);
}

template <class T>
void linkedlist<T>::_sort(LinkedListNode<T>* first, LinkedListNode<T>* last, bool(*cmp)(const T&a, const T&b)) {
    if (first == last)
        return;
    auto mid = first;
    for (auto p = first -> next; p != _last && p != last;)
        if (cmp(p->val, mid->val)) {
            first = insert(first, p->val);
            if (p->next == last)
                last = p = erase(p);
            else
                p = erase(p);
        }
        else
            p = p -> next;
    _sort(first, mid, cmp);
    _sort(mid->next, last->next, cmp);
}

int main() {
    srand(time(0));
    linkedlist<int> p;
    for (int i=0; i<10; i++)
        p.insert(p.end(), rand());
    p.print();
    p.reverse();
    p.print();
    p.sort([](const int &a, const int &b) {return a<b;});
    p.print();
    cout<<p.size()<<endl;
    return 0;
}