#include <bits/stdc++.h>
using namespace std;

template <class T>
class LinkedListNode {
    public:
        T val;
        LinkedListNode * next;
};

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
            if (_size != 0)
                return false;
            return true;
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
        void print() const {
            for (auto p = _first; p != _last; p = p -> next)
                cout<<(p->val)<<" ";
            cout<<endl;
        }
    private:
        LinkedListNode<T>* _first, _last;
        uint64_t _size;
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
    if (!empty())
        erase(_first);
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
    position -> val = position -> next -> val;
    position -> next = position -> next -> next;
    delete position -> next;
    if (position -> next == _last) {
        _last = position;
        position -> next = _last;
    }
    _size--;
    return position;
}

int main() {
    linkedlist<int> p;
    for (int i=0; i<10; i++)
        p.insert(p.begin(), i);
    p.print();
    return 0;
}