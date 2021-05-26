#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <bits/stdc++.h>
#include "haffman-tree.h"
#include "heap.h"
using namespace std;


map<wchar_t, string> translate(haffman_tree *);
void PrintString(map<wchar_t, string> &charmap, vector<string> &filelist, string output_file_name);
void unzip(wifstream &, haffman_tree *);
// template <class T>
// void printbybit(ofstream & fout, const T& ob);

// 这里先实现单一文件输出
// TODO: 多文件处理
// string & getPrintString(map<wchar_t, string>&, vector<string>&, string&);

// void print(string &, vector<string> &, string &);

#endif