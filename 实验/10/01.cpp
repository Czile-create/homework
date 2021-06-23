#include <bits/stdc++.h>
using namespace std;

template <const size_t _size, const int _default>
class hash1 {
    public:
        hash1() {
            for (auto &i: p)
                i = _default;
            success = 0;
            size = 0;
        }
        void push(const int val) {
            auto tmp = 1;
            auto pos = hash(val);
            while (p[pos % _size] != _default && p[pos % _size] != val)
                ++pos, ++tmp;
            if (p[pos % _size] == val)
                return;
            p[pos % _size] = val;
            success += tmp;
            ++size;
        }
        string info() {
            auto fail = 0;
            for (auto i = 0; i < 11; ++i) 
                fail += _fail(i);
            return to_string(double(success)/size) + " " + to_string(double(fail)/11);
        }
        void print() {
            for (auto i = 0; i < _size; ++i)
                cout << p[i] << " ";
            cout << endl;
        }
    private:
        int success, size;
        int hash(const int val) {
            return val % 11;
        }
        int _fail(int pos) {
            if (p[pos] == _default)
                return 1;
            auto ans = 1;
            for (auto i = pos + 1; i != pos && p[i] != _default; i = (i + 1)%_size)
                ++ans;
            return ans + 1;
        }
        array<int, _size> p;
};

template <const int _size, const int _default>
class hash2 {
    public:
        hash2() {
            for (auto &i: p)
                i = _default;
            success = 0;
            size = 0;
        }
        void push(const int val) {
            auto tmp = 1;
            auto pos = hash(val);
            while (p[pos % _size] != _default && p[pos % _size] != val) 
                pos = nextpos(hash(val), tmp++);
            if (p[pos % _size] == val)
                return;
            p[pos % _size] = val;
            success += tmp;
            ++size;
        }
        string info() {
            auto fail = 0;
            for (auto i = 0; i < 11; ++i) 
                fail += _fail(i);
            return to_string(double(success)/size) + " " + to_string(double(fail)/11);
        }
        void print() {
            for (auto i = 0; i < _size; ++i)
                cout << p[i] << " ";
            cout << endl;
        }
    private:
        int success, size;
        int hash(const int val) {
            return val % 11;
        }
        int _fail(int pos) {
            if (p[pos] == _default)
                return 1;
            auto ans = 1;
            for (auto i = (pos + 1)%_size; i != pos && p[i] != _default; i = nextpos(pos, ans++));
            return ans;
        }
        int nextpos(int pos, int time) {
            return ((pos + (time%2*2-1)*((time+1)/2)*((time+1)/2))%_size+_size)%_size;
        }
        array<int, _size> p;
};

template <const int _size>
class hash3 {
    public:
        hash3() {
            success = 0;
            size = 0;
        }
        void push(const int val) {
            auto tmp = 1;
            auto pos = hash(val);
            if (find(p[pos].begin(), p[pos].end(), val)!=p[pos].end())
                return;
            p[pos].push_back(val);
            success += p[pos].size();
            ++size;
        }
        string info() {
            auto fail = 0;
            for (auto i = 0; i < 11; ++i) 
                fail += _fail(i);
            return to_string(double(success)/size) + " " + to_string(double(fail)/11);
        }
        void print() {
            for (auto i = 0; i < _size; ++i) {
                for (auto &j: p[i])
                    cout << j << " ";
                cout << endl;
            }
        }
    private:
        int success, size;
        int hash(const int val) {
            return val % 11;
        }
        int _fail(int pos) {
            return p[pos].size();
        }
        array<list<int>, _size> p;
};

int main() {
    vector<int> p = {47, 7, 29, 11, 16, 92, 22, 8, 3};
    hash3<12> h;
    for (auto &i: p)
        h.push(i);
    h.print();
    cout << h.info() << endl;
}