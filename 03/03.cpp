// Greedy algorithm

#include <bits/stdc++.h>
using namespace std;

template <class T>
class que: public queue<T> {
public:
    int num;    // 缓冲轨道编号
};

// 有K个缓冲轨道，一个出轨，并且不保留原有信息
void rearrange(vector<int> &p, unsigned k) {
    // 检测车厢的最后是否有序，若有序可将其保留于入轨中最后集中搬运到出轨
    auto t = is_sorted_until(p.begin(), p.end(), [] (auto &i, auto &j) {
        return i > j;
    }) - p.begin();

    // 预处理
    auto q = new que<int>[k+1];
    for (auto i=0; i<=k; i++) 
        q[i].num = i;
    auto n = p.size();

    // 处理前面n - t - 1的车厢
    while (p.size() - t - 1) {
        // 按照尾元素排序缓冲轨道，寻找最好的入轨方案
        sort(q, q+k, [] (auto &i, auto &j) {
            return i.size() && j.size() && i.back() > j.back();
        });
        auto tmp = find_if(q, q+k, [&p](auto& z) {return !z.size() || z.back() < p.front();});
        
        // 找不到一条轨道，可以容纳最新的车厢，退出
        if (tmp == q+k && q[k].size() && q[k].front() + 1 != p.front()) 
            throw exception("CANNOT REARRANGE!!\n");

        // 否则取出该车厢，插入到该轨道，并输出信息
        tmp -> push(p.front());
        p.erase(p.begin());
        printf("Let %d from %d to %d\n", tmp -> back(), -1, tmp -> num);
    }

    // 接下来是对个缓冲轨的车厢搬运到出轨中
    while (n - q[k].size() - p.size()) {
        // 按队首元素排序并取出
        sort(q, q+k, [](auto &i, auto &j) {
            return i.size() ? !j.size() || i.front() < j.front() : 0;
        });
        q[k].push(q[0].front());
        q[0].pop();
        printf("Let %d from %d to %d\n", q[k].back(), q[0].num, k);
    }

    // 将入轨中的有序车厢直接搬运到出轨中
    while (p.size()) {
        printf("Let %d from %d to %d\n", p.front(), -1, k);
        p.erase(p.begin());
    }
}

int main() {
    vector<int> p;
    p.push_back(1);
    p.push_back(4);
    p.push_back(2);
    p.push_back(5);
    p.push_back(3);
    p.push_back(6);
    p.push_back(7);
    rearrange(p, 2);
    return 0;
}