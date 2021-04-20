#include <iostream>
using namespace std;
int gcd(int a, int b) {
    if (!(a%b))
        return b;
    else
        return gcd(b, a%b);
}

int lcm(int a, int b) {
    return a*b/gcd(a, b);
}

int main() {
    int a, b;
    cin>>a>>b;
    cout<<"Greatest Common Divisor:\t"<<gcd(a, b)
        <<"\nLeast Common Multiple:\t\t"<<lcm(a, b)<<"\n";
    return 0;
}