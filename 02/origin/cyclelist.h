#ifndef _cyclelist_H_
#define _cyclelist_H_

#include <iostream>

template <class T>
class cyclelistNode {
    public:
        T val;
        cyclelistNode * next;
};

// This is an easy cyclelist.
template <class T>
class cyclelist {
    public:
        // Constructs a cyclelist.
        cyclelist();
        // Constructor a cyclelist from an interator.
        template <class RandomAccessIterator>
        cyclelist(RandomAccessIterator, RandomAccessIterator);
        // Destroys the cyclelist
        ~cyclelist();
        // Insert an element in the position, return a pointer that points to the first of the newly inserted elements.
        cyclelistNode<T>* insert(cyclelistNode<T>* position, const T&val);
        // Delete an element in the position, return a pointer that points to the next element.
        // NOTE: we will NOT ensure whether the position is in the cyclelist or not!!
        cyclelistNode<T>* erase(cyclelistNode<T>* position);
        // If there are no element in the list, return true.
        bool empty() const noexcept {
            return (!_size);
        }
        // return the pointer that points to the first element.
        cyclelistNode<T>* begin() noexcept {
            return _first;
        }
        cyclelistNode<T>* end() noexcept {
            return _last;
        }
        // return the number of elements in the cyclelist.
        uint64_t size() const noexcept {
            return _size;
        }
        // Print the cyclelist.
        void print() const noexcept{
            for (auto p = _first; p != _last; p = p -> next)
                std::cout<<(p->val)<<" ";
            std::cout<<std::endl;
        }
        // reverse the element of the cyclelist
        void reverse();
        // sort the element of the cyclelist
        // NOTE: to use this function, you MUST write a funcion of the operator <
        void sort(bool(*cmp)(T&a, T&b)=[](T&a, T&b) {return a<b;});
        // Find the element by its value.
        // The second Pars is to find the nth element.
        // Return a pointer points to the value or return this.end().
        cyclelistNode<T>* find(const T&, unsigned=1);
        // Return the element in the list.
        // If the position is out of range, return *this.end() and throw an error.
        T& operator[](unsigned);
    private:
        cyclelistNode<T>* _first, *_last;
        uint64_t _size;
        // Quick sort
        void _sort(cyclelistNode<T>* first, cyclelistNode<T>* last, bool(*cmp)(T&a, T&b));
};

template <class T>
cyclelist<T>::cyclelist() {
    _last = new cyclelistNode<T>;
    // This is to ensure the pointer is safe.
    _last->next = _first;
    _first = _last;
    _size = 0;
}

template <class T>
template <class RandomAccessIterator>
cyclelist<T>::cyclelist(RandomAccessIterator first, RandomAccessIterator end) {
    for (auto i=0; first != end; first++)
        insert(_last, *first);
}

template <class T>
cyclelist<T>::~cyclelist() {
    while (!empty()) {
        erase(_first);
    }
    delete _first;
}

template <class T>
cyclelistNode<T>* cyclelist<T>::insert(cyclelistNode<T>* position, const T&val) {
    auto tmp = new cyclelistNode<T>;
    tmp -> val = position -> val;
    tmp -> next = position -> next;     //new a node, and make the position's be the node.
    position -> val = val;
    position -> next = tmp;
    if (position == _last) {
        _last = tmp;
        _last -> next = _first;
    }
    _size++;
    return position;
}

template <class T>
cyclelistNode<T>* cyclelist<T>::erase(cyclelistNode<T>* position) {
    if (position == _last)
        return _last;
    auto tmp = position -> next;
    position -> val = position -> next -> val;
    position -> next = position -> next -> next;
    delete tmp;
    if (tmp == _last) {
        _last = position;
        position -> next = _first;
    }
    _size--;
    return position;
}

template <class T>
void cyclelist<T>::reverse() {
    auto p = _last;
    for (auto i=0; i<_size; i++) {
        p = insert(p, _first->val);
        erase(_first);
    }
}

template <class T>
void cyclelist<T>::sort(bool(*cmp)(T&a, T&b)) {
    _sort(_first, _last, cmp);
}

template <class T>
void cyclelist<T>::_sort(cyclelistNode<T>* first, cyclelistNode<T>* last, bool(*cmp)(T&a, T&b)) {
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
cyclelistNode<T>* cyclelist<T>::find(const T& val, unsigned k) {
    if (!k)
        return _last;
    auto p = _first;
    for (; p != _last && k;k && (p = p -> next))
        if (p->val == val)
            k--;
    return p;
}

template <class T>
T& cyclelist<T>::operator[] (unsigned k) {
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