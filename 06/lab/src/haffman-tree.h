#ifndef _HAFFMAN_TREE_H_
#define _HAFFMAN_TREE_H_

class haffman_tree {
    public:
        inline haffman_tree();
        inline haffman_tree(wchar_t value);
        inline haffman_tree(haffman_tree*, haffman_tree*);
        inline haffman_tree(wchar_t value, unsigned long long w);
        inline bool isleaf() const;                                // return true if the tree is leaf
        inline unsigned long long & weight();                      // return weight of the tree
        inline wchar_t & val();                                    // return the _val of the tree if it's leaf, else return 0
        inline bool left() const;                                  // return true if the tree have left subtree
        inline bool right() const;                                 // return true if the tree have right subtree
        inline bool father() const;                                // return true if the tree have father
        inline haffman_tree * & getleft();                         // get the pointer of the left subtree if exists, else return nullptr
        inline haffman_tree * & getright();                        // get the pointer of the right subtree if exists, else return nullptr
        inline haffman_tree * & getfather();                          // get the pointer of its father if exists, else return nullptr
    private:
        wchar_t _val;
        unsigned long long _weight;
        haffman_tree * _left, *_right, *_father;
};
#include "haffman-tree.cpp"

#endif
