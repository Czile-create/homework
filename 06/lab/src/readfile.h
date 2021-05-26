#ifndef _READFILE_H_
#define _READFILE_H_
#include <bits/stdc++.h>
#include "process.h"
using namespace std;

map<char, unsigned long long> readfiles(vector<string> &);

heap make_heap(map<char, unsigned long long> &);

haffman_tree * make_tree(heap);

haffman_tree * make_unzip_tree(ifstream &);

#endif