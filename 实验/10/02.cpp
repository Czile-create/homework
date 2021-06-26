#include <bits/stdc++.h>
#ifdef __linux__
#include <unistd.h>
#include <sys/ioctl.h>
#endif
using namespace std;

template <typename T> 
double analyze (
    T _sort, 
    const int N,
    const double M,
    string s
) {
    cout << "Analyzing test "<< s << "...\t";
    cout << "Creating random list...\t";
    vector<int> ls;
    srand(time(0));
    for (auto i = 0; i < N; ++i)
        ls.push_back(rand());
    cout << "Done. ";
    cout << "\rAnalyzing test "<< s << "...\t Sorting...                      \t";
    auto clockBegin = clock();
    _sort(ls.begin(), ls.end());
    auto clockEnd = clock();
    cout << "\rAnalyzing test "<< s << "...\t Finish. Using " << double(clockEnd - clockBegin)/CLOCKS_PER_SEC << "s.  \rChecking if it's sorted... ";
    cout << ((is_sorted(ls.begin(), ls.end())) ? "\tTrue.\r" : "False.\r");
    for (auto i = 0; i < M; ++i)
        cout << " ";
    cout << "\r" << s << "\t: ( ";
    for (auto i = 0; i < min(1e-5*N/(double(clockEnd - clockBegin)/CLOCKS_PER_SEC), M); ++i)
        cout <<"+";
    for (auto i = min(1e-5*N/(double(clockEnd - clockBegin)/CLOCKS_PER_SEC) + 1, M); i < M; ++i)
        cout << " ";
    cout << ((is_sorted(ls.begin(), ls.end())) ? " ) True.  " : " ) False. ") << double(clockEnd - clockBegin)/CLOCKS_PER_SEC << " s\n";
    return double(clockEnd - clockBegin)/CLOCKS_PER_SEC;
}

template <class InputIterator>
void insertSort(InputIterator first, InputIterator last) {
    for (auto i = first + 1; i != last; ++i) {
        auto pos = upper_bound(first, i, *i);
        auto val = *i;
        for (auto j = i; j != pos; --j)
            *j = *(j-1);
        *pos = val;
    }
}

template <class InputIterator>
void shellSort(InputIterator first, InputIterator last) {
    for (auto gap = (last - first)/2; gap; gap/=2) 
        for (auto i = first + gap; i != last; ++i) {
            auto current = *i;
            auto j = i;
            for (; j - gap >= first && current < *(j - gap); j-=gap) 
                *j = *(j - gap);
            *j = current;
        }
}

template <class InputIterator>
void bubbleSort(InputIterator first, InputIterator last) {
    for (auto i = last - 1; i != first; --i) 
        for (auto j = first; j < i; ++j)
            if (*j > *(j+1))
                swap(*(j+1), *j);
}

template <class InputIterator>
void quickSort(InputIterator first, InputIterator last) {
    if (last - first < 2) return;
    InputIterator i = first + 1, j = last - 1;
    while(i < j) {
        while (i < j && *i < *first) ++i;
        while (i < j && *j > *first) --j;
        if (i < j) swap(*i, *j);
    }
    while (i >= first && *i > *first) --i;
    swap(*first, *i);
    quickSort(first, i);
    quickSort(i+1, last);
}

template <class InputIterator>
void selectSort(InputIterator first, InputIterator last) {
    for (auto i = first; i != last; ++i) 
        swap(*i, *min_element(i, last));
}

template <class InputIterator>
void heapSort(InputIterator first, InputIterator last) {
    priority_queue<int, vector<int>, greater<int>> heap(first, last);
    for (auto i = first; i != last; ++i) {
        *i = heap.top();
        heap.pop();
    }
}


template <class InputIterator>
void mergeSort(InputIterator first, InputIterator last) {
    if (last - first < 2) return;
    auto mid = (last - first) / 2;
    mergeSort(first, first + mid);
    mergeSort(first + mid, last);
    // thread tl(mergeSort<InputIterator>, first, first + mid);
    // thread tr(mergeSort<InputIterator>, first + mid, last);
    // tl.join();
    // tr.join();

    queue<int> tmp;
    for (InputIterator i = first, j = first + mid; i != first + mid || j != last; )
        tmp.push((j == last || i < first + mid && *i < *j) ? *(i++) : *(j++));
    for (auto i = first; tmp.size();) {
        *(i++) = tmp.front();
        tmp.pop();
    }
}

template <class InputIterator>
void radixSort(InputIterator first, InputIterator last) {
    for (int k = 8; !is_sorted(first, last); k += 8) {
        array<queue<int>, 256> tmp;
        for (auto i = first; i != last; ++i) 
            tmp[((*i) & ((1ull << k) - 1)) >> (k - 8)].push(*i);
        auto x = first;
        for (auto &i: tmp)
            while (i.size()) {
                *(x++) = i.front();
                i.pop();
            }
    }
}

int main() {
    int M = 80;
    #ifdef __linux__
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        M=w.ws_col - 40;
    #endif
    int N = 100000;
    cout << "Size of test: " << N << endl;
    analyze(insertSort<vector<int>::iterator>, N, M, "insertSort");
    analyze(shellSort<vector<int>::iterator>, N, M, "shellSort");
    // analyze(bubbleSort<vector<int>::iterator>, N, M, "bubbleSort");
    analyze(quickSort<vector<int>::iterator>, N, M, "quickSort");
    analyze(selectSort<vector<int>::iterator>, N, M, "selectSort");
    analyze(heapSort<vector<int>::iterator>, N, M, "heapSort");
    analyze(mergeSort<vector<int>::iterator>, N, M, "mergeSort");
    analyze(std::sort<vector<int>::iterator>, N, M, "std::sort");
    analyze(radixSort<vector<int>::iterator>, N, M, "radixSort");
    return 0;
}

/*
                                    ---------------------------------------------
                                    Which is the best algorithm to sort the data?
                                    ---------------------------------------------
czile@Czile:~/work/LinuxProgram/cpp/homework/实验/10$ cd "/home/czile/work/LinuxProgram/cpp/homework/实验/10"
czile@Czile:~/work/LinuxProgram/cpp/homework/实验/10$ ./"02" 
Size of test: 100
insertSort      : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 5e-06 s
shellSort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 4e-06 s
bubbleSort      : ( +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++          ) 1.1e-05 s
quickSort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 4e-06 s
selectSort      : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 8e-06 s
heapSort        : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 5e-06 s
mergeSort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++                                             ) 1.8e-05 s
std::sort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 3e-06 s
czile@Czile:~/work/LinuxProgram/cpp/homework/实验/10$ cd "/home/czile/work/LinuxProgram/cpp/homework/实验/10"
czile@Czile:~/work/LinuxProgram/cpp/homework/实验/10$ ./"02" 
Size of test: 1000
insertSort      : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 6.2e-05 s
shellSort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 5.5e-05 s
bubbleSort      : ( +++++++++++++++                                                                                      ) 0.000712 s
quickSort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 4.7e-05 s
selectSort      : ( +++++++++++++++++++                                                                                  ) 0.000551 s
heapSort        : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 6.4e-05 s
mergeSort       : ( ++++++++++++++++++++++++++++++++++++++++                                                             ) 0.000255 s
std::sort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 3.5e-05 s
czile@Czile:~/work/LinuxProgram/cpp/homework/实验/10$ cd "/home/czile/work/LinuxProgram/cpp/homework/实验/10"
czile@Czile:~/work/LinuxProgram/cpp/homework/实验/10$ ./"02" 
Size of test: 5000
insertSort      : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++       ) 0.000534 s
shellSort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 0.000349 s
bubbleSort      : ( +++                                                                                                  ) 0.022815 s
quickSort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 0.000304 s
selectSort      : ( ++++                                                                                                 ) 0.014055 s
heapSort        : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 0.000407 s
mergeSort       : ( ++++++++++++++++++++++++                                                                             ) 0.002163 s
std::sort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 0.000239 s
czile@Czile:~/work/LinuxProgram/cpp/homework/实验/10$ cd "/home/czile/work/LinuxProgram/cpp/homework/实验/10"
czile@Czile:~/work/LinuxProgram/cpp/homework/实验/10$ ./"02" 
Size of test: 10000
insertSort      : ( ++++++++++++++++++++++++++++++++++++++++++++++++++                                                   ) 0.002001 s
shellSort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 0.000934 s
bubbleSort      : ( +                                                                                                    ) 0.115122 s
quickSort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 0.000634 s
selectSort      : ( ++                                                                                                   ) 0.052196 s
heapSort        : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 0.000807 s
mergeSort       : ( ++++++++++++++++++++++++++++                                                                         ) 0.003659 s
std::sort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 0.000462 s
czile@Czile:~/work/LinuxProgram/cpp/homework/实验/10$ cd "/home/czile/work/LinuxProgram/cpp/homework/实验/10"
czile@Czile:~/work/LinuxProgram/cpp/homework/实验/10$ ./"02" 
Size of test: 50000
insertSort      : ( ++++++++++                                                                                           ) 0.05329 s
shellSort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++         ) 0.005448 s
bubbleSort      : ( +                                                                                                    ) 3.14193 s
quickSort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 0.003338 s
selectSort      : ( +                                                                                                    ) 1.09895 s
heapSort        : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 0.004635 s
mergeSort       : ( +++++++++++++++++++++++++                                                                            ) 0.020082 s
std::sort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 0.002539 s
czile@Czile:~/work/LinuxProgram/cpp/homework/实验/10$ cd "/home/czile/work/LinuxProgram/cpp/homework/实验/10"
czile@Czile:~/work/LinuxProgram/cpp/homework/实验/10$ ./"02" 
Size of test: 100000
insertSort      : ( +++++                                                                                                ) 0.221669 s
shellSort       : ( +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++          ) 0.011048 s
bubbleSort      : ( +                                                                                                    ) 12.8111 s
quickSort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 0.007365 s
selectSort      : ( +                                                                                                    ) 4.32872 s
heapSort        : ( +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  ) 0.010143 s
mergeSort       : ( +++++++++++++++++++++++++                                                                            ) 0.04099 s
std::sort       : ( ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ) 0.005867 s
*/