#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    vector<double> p;
    const int M = 10000, N = 1000000;
    srand(time(0));
    for (unsigned i = 0; i < N; i++)
        p.push_back(rand() % M);
    cout<<"Average:\t"<<accumulate(p.begin(), p.end(), 0.0)/p.size()<<endl;
    sort(p.begin(), p.end());
    cout<<"Min:\t\t"<<*p.begin()<<"\nMax:\t\t"<<*(p.end() - 1)<<endl;
    cout<<"Median:\t\t"<<double(p[p.size() / 2] + p[p.size() / 2 + !(p.size() % 2)]) / 2<<endl;
    return 0;
}