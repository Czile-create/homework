#include "readfile.h"
#include <bits/stdc++.h>
using namespace std;

map<char, unsigned long long> readfiles(vector<string> & filelist) {
    map<char, unsigned long long> charmap;
    for (auto filename: filelist) {
        ifstream fin(filename, ios::in|ios::binary);                       //二进制打开文件
        if (fin.is_open() == false) {                               //若不存在
            cout<<"ERROR: \""<<filename<<"\" do NOT exists!"<<endl;
            exit(1);
        }
        char tmp;
        while (!fin.eof()) {
            tmp = fin.get();
            auto it = charmap.find(tmp);                            //在字典中寻找tmp
            if (it != charmap.end())
                it->second++;
            else 
                charmap[tmp]=1;
        }
        fin.close();
    }
    return charmap;
}

heap make_heap(map<char, unsigned long long> & charmap) {
    heap h;
    for (auto i: charmap) {
        haffman_tree * tmp = new haffman_tree(i.first, i.second);
        h.push(tmp);
    }
    return h;
}

haffman_tree * make_tree(heap h) {
    if (h.empty())
        return NULL;

    while (h.size()>1) {
        haffman_tree * tmp1 = h.front();
        h.pop();
        haffman_tree * tmp2 = h.front();
        h.pop();
        haffman_tree * tmp = new haffman_tree(tmp1, tmp2);
        h.push(tmp);
    }
    
    return h.front();
}

haffman_tree * make_unzip_tree(ifstream &fin) {
    char ch;
    haffman_tree * tree = new haffman_tree;
    ch = fin.get();
    while (ch != '\"') {
        fin.get();
        label1:
        char c;
        haffman_tree * tmp = tree;
        while ((c = fin.get()) != '\n')
            if (c == '0') {
                if (tmp->left() == false)
                    tmp->getleft() = new haffman_tree;
                tmp = tmp->getleft();
            } else {
                if (tmp->right() == false)
                    tmp->getright() = new haffman_tree;
                tmp = tmp->getright();
            }
        tmp->val()=ch;
        ch = fin.get();
    }
    if (fin.get() == ' ')
        goto label1;
    return tree;
}
