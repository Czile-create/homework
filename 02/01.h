#ifndef _CLIST_HPP_
#define _CLIST_HPP_

#include <iostream>
#include <algorithm>

// This is an easy contiguous list
template <class T, unsigned N>
class clist {
    public:
        // Constructor
        clist();
        // Constructor a contiguous list from an interator.
        template <class RandomAccessIterator>
        clist(RandomAccessIterator, RandomAccessIterator);
        // Destroys the contiguous list.
        ~clist();
        // Return a pointer that points to the first element in the range.
        T* begin() const noexcept;
        // Return a pointer that points to the last element's next location in the range.
        T* end() const noexcept;
        // Return the element in the list.
        // If the position is out of range, return *this.end() and throw an error.
        T& operator[](unsigned);
        // Return the max_size in the list
        unsigned size() const noexcept;
        // Sort the list by the cmp function
        void sort(bool(*cmp)(T&, T&) = [](T&a, T&b){return a<b;});
        // Insert the element in the location.
        // Return a pointer points to the new element.
        // NOTE: if the last element exists, this operate will delete the last element.
        T* insert(T*, const T&);
        // Delete the element in the location.
        // Return a pointer points to the next element.
        T* erase(T*);
        // Find the element by its value.
        // The second Pars is to find the nth element.
        // Return a pointer points to the value or return this.end().
        T* find(const T&, unsigned=1);
        // Print the list in the screen.
        void print();
    private:
        T* p;
};

template<class T, unsigned N>
clist<T, N>::clist() {
    p = new T[N+1];
}

template <class T, unsigned N>
template <class RandomAccessIterator>
clist<T, N>::clist(RandomAccessIterator first, RandomAccessIterator end) {
    for (auto i=0; i<N && first != end; i++, first++)
        p[i] = *first;
}

template<class T, unsigned N>
clist<T, N>::~clist() {
    delete [] p;
}

template <class T, unsigned N>
T* clist<T, N>::begin() const noexcept {
    return p;
}

template <class T, unsigned N>
T* clist<T, N>::end() const noexcept {
    return p+N;
}

template <class T, unsigned N>
T& clist<T, N>::operator[] (unsigned k) {
    if (k < 0 || k >= N) {
        throw "In clist::operator[]: the index is out of range.\n";
        return p[N+1];
    }
    return p[k];
}


template <class T, unsigned N>
unsigned clist<T, N>::size() const noexcept {
    return N;
}

template <class T, unsigned N>
void clist<T, N>::sort(bool(*cmp)(T&, T&)) {
    std::sort(p, p+N, cmp);
}

template <class T, unsigned N>
T* clist<T, N>::insert(T* p, const T& val) {
    for (auto z = p; z != this->p+N; z++)
        *z = *(z - 1);
    *p = val;
    return p;
}

template <class T, unsigned N>
T* clist<T, N>::erase(T* p) {
    for (auto z = p; z != this->p+N-1; z++)
        *z = *(z + 1);
    return p;
}

template <class T, unsigned N>
T* clist<T, N>::find(const T& val, unsigned k) {
    if (!k)
        return p+N;
    auto t = p;
    for (; t != p+N && k;k && (t++))
        if (*t == val)
            k--;
    return t;
}

template <class T, unsigned N>
void clist<T, N>::print() {
    for (auto t = p; t != p + N; t++)
        std::cout<<*t<<" ";
    std::cout<<std::endl;
}
#endif