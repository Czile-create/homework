# 第五次上机作业

本上机作业包含以下内容：

- [x]    Binarytree();                                           


- [x]    Binarytree(
            InputIterator first,
            InputIterator last,
            const T & default_value
         );                                                      


- [x]    Binarytree(
            InputIterator firstPre, 
            InputIterator lastPre,
            InputIterator firstInorder, 
            InputIterator lastInorder
         );                                                      

- [x]    Binarytree(const Binarytree &x);      
- [x]    ~Binarytree();
- [x]    Binarytree& operator=(const Binarytree&x);
- [x]    void clear();

- [x]    Binarytreenode* insert(
            Binarytreenode * p,
            const T & val, 
            const int _pos
         );     
- [x]    Binarytreenode* erase(Binarytreenode * &p);
- [x]    Binarytreenode* root() const noexcept {return p;}
- [x]    std::vector<T> Preorder() const noexcept;
- [x]    std::vector<T> Inorder() const noexcept;
- [x]    std::vector<T> Postorder() const noexcept;
- [x]    std::vector<T> BFS() const noexcept;
- [x]    std::string info() const noexcept;
- [x]    std::string print() const noexcept;
- [x]    size_t size() const noexcept;
- [x]    size_t deaph() const noexcept;
- [x]    size_t sizeOfLeaf() const noexcept;

- [x]    void __CreateTreeByNLRandLNR(
            InputIterator firstPre, 
            InputIterator lastPre,
            InputIterator firstInorder, 
            InputIterator lastInorder
         );

- [x]    Binarytreenode * __deepcopy(const Binarytreenode *x) const noexcept;
- [x]    std::vector<T> __preorder(const Binarytreenode *x) const noexcept;
- [x]    std::vector<T> __inorder(const Binarytreenode *x) const noexcept;
- [x]    std::vector<T> __postorder(const Binarytreenode *x) const noexcept;

