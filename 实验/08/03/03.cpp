#include <bits/stdc++.h>
using namespace std;
typedef struct Activity {
    vector<pair<int, int>> prepare, todo;
    long long tmp, Earlist_Start_Time, Latest_Start_Time, name;
    Activity() : Earlist_Start_Time(unsigned(-1)), Latest_Start_Time(unsigned(-1)) {}
} Activity;

void _TopoSort(Activity * first, Activity * last) {
    if (first == last)
        return;
    sort(first, last, [](auto &i, auto &j) {
        return i.tmp < j.tmp;
    });
    for (auto &i: first -> todo)
        --find_if(first, last, [i](auto &j){
            return i.first == j.name;
        }) -> tmp;
    _TopoSort(first + 1, last);
}

void TopoSort(Activity * first, Activity * last) {
    for (auto i = first; i != last; ++i)
        i -> tmp = i -> prepare.size();
    _TopoSort(first, last);
}

int main() {
    ifstream fin("03.mdb", ios::in);
    int n, m;
    fin >> n >> m;
    Activity * activityList = new Activity[n + 1];
    for (auto i = 0; i < n; ++i)
        activityList[i].name = i + 1;
    for (auto i = 0; i < m; ++i) {
        int a, b, c;
        fin >> a >> b >> c;
        activityList[a - 1].todo.push_back(make_pair(b, c));
        activityList[b - 1].prepare.push_back(make_pair(a, c));
    }
    TopoSort(activityList, activityList + n);
    activityList[0].Earlist_Start_Time = activityList[0].Latest_Start_Time = 0;
    for (auto i = 1; i < n; ++i) {
        auto t = max_element(
            activityList[i].prepare.begin(), 
            activityList[i].prepare.end(), 
            [activityList, n](auto &j, auto &k) {
                return find_if(activityList, activityList + n, [&j](auto &l){
                    return j.first == l.name;
                }) -> Earlist_Start_Time + j.second < find_if(activityList, activityList + n, [&k](auto &l){
                    return k.first == l.name;
                }) -> Earlist_Start_Time + k.second;
            }
        );
        activityList[i].Earlist_Start_Time = find_if(
            activityList, 
            activityList + n, 
            [&t](auto &j) {
                return t -> first == j.name;
            }
        ) -> Earlist_Start_Time + t -> second;
    }
    activityList[n - 1].Latest_Start_Time = activityList[n - 1].Earlist_Start_Time;
    for (auto i = n - 2; i >= 0; --i) {
        auto t = min_element(
            activityList[i].todo.begin(), 
            activityList[i].todo.end(), 
            [activityList, n](auto &j, auto &k) {
                return find_if(activityList, activityList + n, [&j](auto &l){
                    return j.first == l.name;
                }) -> Latest_Start_Time - j.second < find_if(activityList, activityList + n, [&k](auto &l){
                    return k.first == l.name;
                }) -> Latest_Start_Time - k.second;
            }   
        );
        activityList[i].Latest_Start_Time = find_if(
            activityList, 
            activityList + n, 
            [&t](auto &j) {
                return t -> first == j.name;
            }
        ) -> Latest_Start_Time - t -> second;
    }
    for (auto i = 0; i < n; ++i)
        if (activityList[i].Earlist_Start_Time == activityList[i].Latest_Start_Time)
            cout << activityList[i].name << "\t";
    cout << endl;
    auto i = 1;
    while (i != n) {
        cout << i << " -> ";
        auto t = find_if(activityList, activityList + n, [&i](auto &j) {
            return i == j.name;
        });
        for (auto j: t -> todo) {
            auto l = find_if(activityList, activityList + n, [&j](auto &k) {
                return j.first == k.name;
            });
            if (l -> Earlist_Start_Time == l -> Latest_Start_Time && t -> Earlist_Start_Time + j.second == l -> Earlist_Start_Time)
                i = l -> name;
        }
    }
    cout << n << endl;
    return 0;
}