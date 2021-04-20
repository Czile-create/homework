#ifndef _DELST_H_
#define _DELST_H_

#include <iostream>

template <class T>
class denode {
    public:
        denode * front, * next;
        T val;
};

template <class T>
class delist {
    public:
        // Constructor
        delist();
        // Constructor a linkedlist from an interator.
        template <class RandomAccessIterator>
        delist(RandomAccessIterator, RandomAccessIterator);
        // Destroys the linkedlist list.
        ~delist();
        // Return a pointer that points to the first element in the range.
        denode<T>* begin() const noexcept;
        // Return a pointer that points to the last element's next location in the range.
        denode<T>* end() const noexcept;
        // Return true if the size of the list is 0;
        bool empty() const noexcept;
        // Return the element in the list.
        // If the position is out of range, return *this.end() and throw an error.
        T& operator[](unsigned);
        // Return the size of the list
        unsigned size() const noexcept;
        // Sort the list by the cmp function
        void sort(bool(*cmp)(T&, T&) = [](T&a, T&b){return a<b;});
        // Insert the element in the location.
        // Return a pointer points to the new element.
        // NOTE: if the last element exists, this operate will delete the last element.
        denode<T>* insert(denode<T>*, const T&);
        // Delete the element in the location.
        // Return a pointer points to the next element.
        denode<T>* erase(denode<T>*);
        // Find the element by its value.
        // The second Pars is to find the nth element.
        // Return a pointer points to the value or return this.end().
        denode<T>* find(const T&, unsigned=1);
        // Print the list in the screen.
        void print();
    private:
        denode<T>* _first, *_last;
        unsigned _size;
        void _sort(denode<T>* first, denode<T>* last, bool(*cmp)(T&a, T&b) = [](T&a, T&b) {return a<b;});
};

template<class T>
delist<T>::delist() {
    _first = _last = new denode<T>;
    _last -> front = _first;
    // To ensure the pointer of the last element is safe.
    _last -> next = _last;
    _size = 0;
}

template <class T>
template <class RandomAccessIterator>
delist<T>::delist(RandomAccessIterator first, RandomAccessIterator end) {
    for (auto i=0; first != end; first++)
        insert(_last, *first);
}

template<class T>
delist<T>::~delist() {
    while (_size)
        erase(_first);
    delete _last;
}

template <class T>
bool delist<T>::empty() const noexcept{
    return !_size;
}

template <class T>
denode<T>* delist<T>::begin() const noexcept {
    return _first;
}

template <class T>
denode<T>* delist<T>::end() const noexcept {
    return _last;
}

template <class T>
T& delist<T>::operator[] (unsigned k) {
    if (k < 0 || k >= _size) {
        throw "In delist::operator[]: the index is out of range.\n";
        return _last -> val;
    }
    auto p = _first;
    for (unsigned i=0; i<k; i++)
        p = p -> next;
    return p -> val;
}


template <class T>
unsigned delist<T>::size() const noexcept {
    return _size;
}

template <class T>
void delist<T>::sort(bool(*cmp)(T&a, T&b)) {
    _sort(_first, _last, cmp);
}

template <class T>
void delist<T>::_sort(denode<T>* first, denode<T>* last, bool(*cmp)(T&a, T&b)) {
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
denode<T>* delist<T>::insert(denode<T>* p, const T& val) {
    _size++;
    if (p == _first) {
        _first = new denode<T>;
        _first -> val = val;
        _first -> next = p;
        p -> front = _first;
        return _first;
    }
    auto tmp = p -> front;
    tmp -> next = new denode<T>;
    tmp -> next -> front = tmp;
    tmp -> next -> val = val;
    tmp -> next -> next = p;
    p -> front = tmp -> next;
    return tmp -> next;
}

template <class T>
denode<T>* delist<T>::erase(denode<T>* p) {
    if (p == _first) {
        _first = p -> next;
        delete p;
        _size--;
        return _first;
    }
    if (p == _last) 
        return _last;
    auto tmp = p->front;
    tmp -> next = p -> next;
    tmp -> next -> front = tmp;
    delete p;
    _size--;
    return tmp -> next;
}

template <class T>
denode<T>* delist<T>::find(const T& val, unsigned k) {
    if (!k)
        return _last;
    auto p = _first;
    for (; p != _last && k; k && (p = p -> next))
        if (p->val == val)
            k--;
    return p;
}

template <class T>
void delist<T>::print() {
    for (auto p = _first; p != _last; p = p -> next)
        std::cout<<p->val<<" ";
    std::cout<<std::endl;
}

#endif