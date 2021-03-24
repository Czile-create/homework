#ifndef _SETT_H_
#define _SETT_H_

#include "04.h"

template <class T>
class sett{
    public:
        // Constructor
        sett() {}
        // Destroys the set.
        ~sett() {}
        // Return a pointer that points to the first element in the set.
        denode<T>* begin() const noexcept {return p.begin();}
        // Return a pointer that points to the last element's next location in the set.
        denode<T>* end() const noexcept {return p.end();}
        // Return true if the size of the size is 0;
        bool empty() const noexcept {return p.empty();}
        // Return the size of the list
        unsigned size() const noexcept {return p.size();}
        // Sort the list by the cmp function
        void sort(bool(*cmp)(T&, T&) = [](T&a, T&b){return a<b;}) {p.sort(cmp);}
        // Insert the element in the location.
        // Return a pointer points to the new element.
        // NOTE: if the last element exists, this operate will delete the last element.
        void insert(const T&t) {if (p.find(t) == p.end()) p.insert(p.end(), t);}
        // Delete the element who has the value.
        // Return a pointer points to the next element.
        void erase(const T&t) {
            auto tmp = p.find(t);
            if (tmp != p.end())
                p.erase(tmp);
        }
        // Find the element by its value.
        // The second Pars is to find the nth element.
        // Return a pointer points to the value or return this.end().
        denode<T>* find(const T&t) {return p.find(t);}
        // Operator
        sett& operator*=(sett&t) {
            for (auto _t = p.begin(); _t != p.end();)
                if (t.find(_t -> val) == t.end())
                    _t = p.erase(_t);
                else
                    _t = _t -> next;
            return *this;
        }
        sett& operator+=(sett&t) {
            for (auto _t = t.begin(); _t != t.end(); _t = _t -> next)
                insert(_t->val);
            return *this;
        }
        sett& operator-=(sett&t) {
            for (auto _t = p.begin(); _t != p.end();)
                if (t.find(_t -> val) != t.end())
                    _t = p.erase(_t);
                else
                    _t = _t -> next;
            return *this;
        }
        // Print the set
        void print() {p.print();}
    private:
        delist<T> p;
};



#endif