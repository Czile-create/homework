#include <iostream>
using namespace std;
class Time {
    public:
        Time() {} 
        Time(int yy, int mm, int dd): y(yy), m(mm), d(dd) {issafe();}
        void setTime(int yy, int mm, int dd);
        friend uint64_t operator-(const Time & t1, const Time & t2);
    private:
        // 判断是否是闰年
        int isLeap() const;
        int y, m, d;
        void issafe();
};

void Time::setTime(int yy, int mm, int dd) {
    y = yy;
    m = mm;
    d = dd;
    issafe();
}
int Time::isLeap() const{
    return (y % 4 == 0) && (y % 100 != 0 || y % 400 == 0);
}
void Time::issafe() {
    // 每个月的天数
    int numofdays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeap())
        numofdays[2] ++;
    if (m<1 || m>12 || d<1 || d>numofdays[m])
        throw "An Error occured when reset the time.";
}

// 计算两个日期相差的天数
uint64_t operator-(const Time & t1, const Time & t2) {

    // 如果是更早的日期减去更晚的日期，则调换次序
    if (t1.y < t2.y)
        return t2-t1;
    if (t1.y == t2.y && t1.m < t2.m)
        return t2-t1;
    if (t1.y == t2.y && t1.m == t2.m && t1.d<t2.d)
        return t2-t1;
    
    // 每个月的天数
    int numofdays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // 如果是同一年
    if (t1.y == t2.y)
        // 如果是同一个月
        if (t1.m == t2.m)
            return t1.d - t2.d;
        // 如果并非是同一个月
        else {
            auto ans = (numofdays[t2.m] - t2.d + t1.d + (t2.isLeap() && t2.m == 2));
            for (unsigned i = t2.m + 1; i < t1.m; i++)
                ans += numofdays[i];
            return ans + (t2.isLeap() && t2.m == 1 && t1.m > 2);
        }

    // 如果并非是同一年
    else {
        auto ans = numofdays[t2.m] - t2.d + t1.d + (t2.isLeap() && t2.m == 2);
        for (unsigned i = t2.m + 1; i < 13; i++)
            ans += numofdays[i];
        for (unsigned i = 1; i < t1.m; i++)
            ans += numofdays[i];
        if (t2.m == 1)
            ans += t2.isLeap();
        if (t1.m > 2)
            ans += t1.isLeap();
        for (auto i = t2.y + 1; i < t1.y; i++)
            if (Time(i, 1, 1).isLeap())
                ans += 366;
            else
                ans += 365;
        return ans;
    }
}

int main() {
    try {
        cout<<Time(1906, 1, 31) - Time(2020, 3, 2)<<endl;
    } catch (const char* s) {
        cerr<<s<<endl;
        exit(1);
    }
}