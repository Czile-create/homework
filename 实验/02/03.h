#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>

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
        // Constructs a linkedlist.
        linkedlist();
        // Constructor a linkedlist from an interator.
        template <class RandomAccessIterator>
        linkedlist(RandomAccessIterator, RandomAccessIterator);
        // Destroys the linkedlist
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
                std::cout<<(p->val)<<" ";
            std::cout<<std::endl;
        }
        // reverse the element of the linkedlist
        void reverse();
        // sort the element of the linkedlist
        // NOTE: to use this function, you MUST write a funcion of the operator <
        void sort(bool(*cmp)(T&a, T&b)=[](T&a, T&b) {return a<b;});
        // Find the element by its value.
        // The second Pars is to find the nth element.
        // Return a pointer points to the value or return this.end().
        LinkedListNode<T>* find(const T&, unsigned=1);
        // Return the element in the list.
        // If the position is out of range, return *this.end() and throw an error.
        T& operator[](unsigned);
    private:
        LinkedListNode<T>* _first, *_last;
        uint64_t _size;
        // Quick sort
        void _sort(LinkedListNode<T>* first, LinkedListNode<T>* last, bool(*cmp)(T&a, T&b));
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
template <class RandomAccessIterator>
linkedlist<T>::linkedlist(RandomAccessIterator first, RandomAccessIterator end) {
    for (auto i=0; first != end; first++)
        insert(_last, *first);
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
void linkedlist<T>::sort(bool(*cmp)(T&a, T&b)) {
    _sort(_first, _last, cmp);
}

template <class T>
void linkedlist<T>::_sort(LinkedListNode<T>* first, LinkedListNode<T>* last, bool(*cmp)(T&a, T&b)) {
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

template <class T>
LinkedListNode<T>* linkedlist<T>::find(const T& val, unsigned k) {
    if (!k)
        return _last;
    auto p = _first;
    for (; p != _last && k;k && (p = p -> next))
        if (p->val == val)
            k--;
    return p;
}

template <class T>
T& linkedlist<T>::operator[] (unsigned k) {
    if (k < 0 || k >= _size) {
        throw "In delist::operator[]: the index is out of range.\n";
        return _last -> val;
    }
    auto p = _first;
    for (unsigned i=0; i<k; i++)
        p = p -> next;
    return p -> val;
}

#endif