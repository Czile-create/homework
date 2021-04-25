#include <vector>
#include <iostream>
using namespace std;

template <class RandomAccessIterator>
void reverse(RandomAccessIterator first, RandomAccessIterator last) {
    while (first != last && first < --last) 
        swap(*(first++), *last);
} 

int main() {
    vector<int> p;
    for (int i=0; i<1; i++)
        p.insert(p.end(), i);

    reverse(p.begin(), p.end());
    for (int i=0; i<1; i++)
        cout<<p[i]<<" ";
    return 0;
}