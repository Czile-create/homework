#include <bits/stdc++.h>
#include "process.h"
using namespace std;

map<wchar_t, string> translate(haffman_tree * t) {
    queue<pair<haffman_tree *, string>> lst;
    map<wchar_t, string> ans;
    lst.push(make_pair(t, ""));
    while (lst.empty() == false) {
        haffman_tree * tmp = lst.front().first;
        if (tmp->left())
            lst.push(make_pair(tmp->getleft(), lst.front().second + "0"));
        if (tmp->right())
            lst.push(make_pair(tmp->getright(), lst.front().second + "1"));
        if (tmp->isleaf())
            ans[tmp->val()]=lst.front().second;
        lst.pop();
    }
    return ans;
}

// Output rule:
// char1 key1
// char2 key2
// ...
// "filename1" extra0num length1
// content 1
// "filename2" extra0num length2
// content2
// ......

void PrintString(map<wchar_t, string> & charmap, vector<string> & filelist, string output_file_name) {
    ofstream fout(output_file_name, ios::binary | ios::out);
    for (auto ch: charmap)
        fout<<char(ch.first)<<" "<<ch.second<<endl;       //输出对应法则
    map<string, unsigned long long> codelength;
    for (auto filename:filelist) {                  //找出每个文件的编码长度
        wifstream fin(filename, ios::binary);
        unsigned long long length=0;
        wchar_t tmp;
        while ((tmp = fin.get()) != wchar_t(-1))
            length += charmap[tmp].length();
        codelength[filename]=length;
    }
    for (auto filename:filelist) {
        wifstream fin(filename, ios::binary);           //处理该文件
        if (filename==filelist[0])
            fout<<'\"'<<filename[0]<<filename<<'\"'<<" ";           //输出该文件的文件名
        else 
            fout<<'\"'<<filename<<'\"'<<" ";
        string buffer="";
        for (unsigned i=0; i<8-codelength[filename]%8; i++) //补充位数
            buffer += "0";
        if (8-codelength[filename]%8 != 8)
            fout<<8-codelength[filename]%8<<" ";
        else {
            fout<<0<<" ";
            buffer = "";
        }
        fout<<(codelength[filename]+buffer.size())/8<<endl;
        wchar_t tmp;
        while ((tmp = fin.get()) != wchar_t(-1)) {
            buffer += charmap[tmp];
            while (buffer.size()>=8) {
                char t=buffer[0]-48;
                for (unsigned i=1; i<8; i++)
                    if (buffer[i]-48)
                        t = (t << 1) + 1;
                    else
                        t = t << 1;
                fout<<t;
                buffer.erase(buffer.begin(), buffer.begin()+8);
            }
        }
    }
}

void unzip(wifstream & fin, haffman_tree * tree) {
    char ch;
    while ((ch = fin.get()) != -1) {
        string outputname;                  //预处理文件名、补充编码
        for (; ch != '\"'; ch = fin.get())
            outputname += ch;
        // cerr<<outputname;
        wofstream fout(outputname, ios::out|ios::binary);
        fin.get();
        ch = fin.get();
        unsigned long long codelength;
        fin>>codelength;
        fin.get();
        haffman_tree * tmp = tree;
        for (unsigned long long i=0; i<codelength; i++) {
            char c = fin.get();
            for (unsigned j=0; j<8; j++) {
                if (ch != '0') {
                    ch--;
                    continue;
                }
                unsigned way = (c >> (7 - j)) & 1;
                if (way)
                    tmp = tmp -> getright();
                else
                    tmp = tmp -> getleft();
                if (tmp->isleaf()) {
                    fout<<tmp->val();
                    // cerr<<char(tmp->val());
                    tmp = tree;
                }
            }
        }
        fin.get();
        fout.close();
    }
}