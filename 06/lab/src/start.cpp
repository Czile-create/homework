#include "start.h"
#include <bits/stdc++.h>
using namespace std;
void _zip(int argc, char * argv[]) {
    vector<string> filenamelist;
    for (int i=2; i<argc-2; i++)
        filenamelist.push_back(string(argv[i]));
    cout<<"Reading files..."<<endl;
    map<char, unsigned long long> frequency = readfiles(filenamelist);
    heap tmp_heap = make_heap(frequency);
    cout<<"Analyzing..."<<endl;
    haffman_tree * tree = make_tree(tmp_heap);
    map<char, string> codetable = translate(tree);
    cout<<"Writing files..."<<endl;
    PrintString(codetable, filenamelist, argv[argc-1]);
}

void _unzip(string filename) {
    ifstream fin(filename, ios::in|ios::binary);
    if (fin.is_open() == false) {                               //若不存在
        cout<<"ERROR: \""<<filename<<"\" do NOT exists!"<<endl;
        exit(1);
    }
    haffman_tree * tree = make_unzip_tree(fin);
    unzip(fin, tree);
}