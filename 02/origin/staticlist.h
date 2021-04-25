#ifndef _STATICLIST_H_
#define _STATICLIST_H_

#include <algorithm>
#include <iostream>

template <class T>
class staticlistnode {
    public:
        T val;
        unsigned next;
};


// define a static linkedlist of type T, with _nlist linkedlist, and totally _size elements.
template <class T, unsigned _nlist, unsigned _size> 
class staticlist {
    public:
        // Constructor of the static chain.
        staticlist();
        // Destroys the static chain.
        ~staticlist();
        // Insert the element in the position.
        // Return the position of the element.
        // Para: first is the position, second is the value, third is the nlistth list=0.
        unsigned insert(unsigned, const T&, unsigned nlist = 0);
        // Delete the element in the position.
        // Return the position of the next element.
        // If return _size, it's to show that the length of the list is not enough.
        unsigned erase(unsigned);
        // Return the position of the first element of the kth linkedlist.
        unsigned begin(unsigned) const;
        // Return the position of the last + 1 element of all the linkedlist.
        unsigned end() const noexcept;
        // Print all the list in the screen.
        void print();
    private:
        unsigned *_first, _last, _free;
        staticlistnode<T> *p;
};

template <class T, unsigned _nlist, unsigned _size> 
staticlist<T, _nlist, _size>::staticlist() {
    if (_size < _nlist) {
        throw "In class staticlist<T, _nlist, _size>: _size cannot smaller than _nlist.";
        return;
    }
    _first = new unsigned[_nlist];
    p = new staticlistnode<T>[_size + 1];
    for (unsigned i=0; i<_nlist; i++) {
        _first[i] = _size;
        p[i].next = i + 1;
    }
    for (unsigned i=_nlist; i<_size; i++)
        p[i].next = i + 1;
    p[_size].next = _size;
    _last = _size;
    _free = 0;
}

template <class T, unsigned _nlist, unsigned _size> 
staticlist<T, _nlist, _size>::~staticlist() {
    delete [] _first;
    delete [] p;
}

template <class T, unsigned _nlist, unsigned _size> 
unsigned staticlist<T, _nlist, _size>::insert(unsigned pos, const T& val, unsigned nlist) {
    if (_free == _last || pos > _last || nlist >= _nlist) {
        throw "In class staticlist<T, _nlist, _nsize>::insert: The length of the list is not enough.\n";
        return _last;
    }
    
    if (pos == _last) {                 // If the insert position is the end of the list
        auto tmp = _first[nlist];      
        if (tmp == _last) {             // If the list has 0 element.
            _first[nlist] = _free;
            _free = p[_free].next;
            tmp = _first[nlist];
            p[tmp].next = _size;
            p[tmp].val = val;
            return tmp;
        }
        for (; p[tmp].next != _last; tmp = p[tmp].next);
        p[tmp].next = _free;
        p[_free].val = val;
        _free = p[_free].next;
        p[p[tmp].next].next = _last;
        return p[tmp].next;
    }
    auto tmp = _free;
    _free = p[tmp].next;
    p[tmp].val = p[pos].val;
    p[tmp].next = p[pos].next;
    p[pos].val = val;
    p[pos].next = tmp;
    return pos;
}

template <class T, unsigned _nlist, unsigned _size> 
unsigned staticlist<T, _nlist, _size>::erase(unsigned pos) {
    if (pos >= _last)
        return _last;
    p[pos].val = p[p[pos].next].val;
    p[pos].next = p[p[pos].next].next;
    p[p[pos].next] = _free;
    _free = p[pos].next;
    return pos;
}

template <class T, unsigned _nlist, unsigned _size>
unsigned staticlist<T, _nlist, _size>::begin(unsigned t) const{
    if (t>=_nlist) {
        throw "In staticlist<T, _nlist, _nsize>::begin(unsigned): NOT such linked list.\n";
        return _last;
    }
    return _first[t];
}

template <class T, unsigned _nlist, unsigned _size>
unsigned staticlist<T, _nlist, _size>::end() const noexcept {
    return _last;
}

template <class T, unsigned _nlist, unsigned _size>
void staticlist<T, _nlist, _size>::print() {
    for (auto i = 0; i < _nlist; i++) {
        for (auto j = _first[i]; j != _last; j = p[j].next) 
            std::cout<<p[j].val<<" ";
        std::cout<<std::endl;
    }
}

#endif