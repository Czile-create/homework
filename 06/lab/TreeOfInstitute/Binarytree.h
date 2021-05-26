#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_
#include <string>
#include <vector>

template <class T>
class Binarytree {
    public:
        typedef struct Binarytreenode {
            Binarytreenode * parents, * left, * right;
            T val;
            Binarytreenode(T _val):
                parents(nullptr), left(nullptr), right(nullptr), val(_val){}
        } Binarytreenode;

        typedef struct thrnode {
            thrnode *left, *right;
            bool ltag, rtag;
            T val;
            thrnode (T _val): left(nullptr), right(nullptr), val(_val), ltag(0), rtag(0) {}
        }thrnode;

        // (Constructor)
        Binarytree();                                           //default

        /*
        * @brief Create tree by range.
        * @param first,last Input iterators to the initial and final positions in a range. 
        * @param default_value The value that represents the node doesn't exist.
        * @retval null
        */ 
        template<typename InputIterator>
        Binarytree(
            InputIterator first,
            InputIterator last,
            const T & default_value
        );                                                      //range(1)

        /*
        * @brief Create tree by preorder traversal and in-order traversal.
        * @param firstPre,lastPre Input iterators to the initial and final positions in the range of the Preorder traversal.
        * @param firstInorder,lastInorder Input iterators to the initial and final positions in the range of the In-order traversal.
        * @retval NULL
        */
        template <typename InputIterator>
        Binarytree(
            InputIterator firstPre, 
            InputIterator lastPre,
            InputIterator firstInorder, 
            InputIterator lastInorder
        );                                                      //range(2)

        /*
        * @brief Constructs a container with a copy of each of the elements in x, in the same order.
        * @param x The binarytree to copy.
        * @retval NULL
        */
        Binarytree(const Binarytree &x);

        // /*
        // * @brief Constructs a container with a copy of node.
        // * @param x The node of the root
        // */
        // Binarytree(const Binarytreenode &x);

        // (Destructor)
        ~Binarytree();

        /* 
        * @brief Copies all the elements from x into the container. The container preserves its current allocator, which is used to allocate storage in case of reallocation.
        * @param x The binarytree to copy.
        * @retval *this
        */
        Binarytree& operator=(const Binarytree&x);

        /*
        * @brief clear the tree and free all the space that alloced.
        */
        void clear();

        /*
        * @brief insert an node at the specific position.
        * @param p The pointer that points to the position that to process.
        * @param val The value to insert
        * @param[in] pos The position to insert, You can choose: 
        *   false: p -> leftchild
        *   true : p -> rightchild
        * @retval Return the root of the new node.
        */
        Binarytreenode* insert(
            Binarytreenode * p,
            const T & val, 
            const int _pos
        );

        // @brief erase the tree whose root is p
        void erase(Binarytreenode *& p);
        void erase(thrnode *& p);

        /*
        * @brief Get the pointer that points to the root.
        * @retval a pointer that points to the root.
        */
        Binarytreenode* &root() noexcept {return p;}

        /*
        * @brief Get the preorder traversal of the tree.
        * @retval Return a vector of the template class that contains the preorder traversal.
        */
        std::vector<T> Preorder() const noexcept;

        /*
        * @brief Get the in-order traversal of the tree.
        * @retval Return a vector of the template class that contains the in-order traversal.
        */
        std::vector<T> Inorder() const noexcept;

        /*
        * @brief Get the postorder traversal of the tree in a non recursive way.
        * @retval Return a vector of the template class that contains the postorder traversal.
        */
        std::vector<T> Postorder() const noexcept;

        /*
        * @brief Get the preorder traversal of the tree in a non recursive way.
        * @retval Return a vector of the template class that contains the preorder traversal.
        */
        std::vector<T> preorder() const noexcept;

        /*
        * @brief Get the in-order traversal of the tree in a non recursive way.
        * @retval Return a vector of the template class that contains the in-order traversal.
        */
        std::vector<T> inorder() const noexcept;

        /*
        * @brief Get the postorder traversal of the tree.
        * @retval Return a vector of the template class that contains the postorder traversal.
        */
        std::vector<T> postorder() const noexcept;

        /*
        * @brief Get the BFS traversal of the tree.
        * @retval Return a vector of the template class that contains the BFS traversal.
        */
        std::vector<T> BFS() const noexcept;

        /* 
        * @brief Return the info of the tree.
        * @param string(*tostr)(const T&) a function that convert T to string.
        * @retval The info of the tree.
        */
        std::string info(std::string(*tostr)(const T&)) const noexcept;

        /*
        * @brief print the struct of the tree in a brief way.
        * @retval Return a string that contains the tree struct.
        */
        std::string print(std::string(*tostr)(const T&)) const noexcept;

        /* 
        * @retval Return the number of node of the tree.
        */
        size_t size() const noexcept;

        /*
        * @retval Return the deaph of the tree.
        */
        size_t depth() const noexcept;

        /* 
        * @retval Return the number of the leaf node.
        */
        size_t sizeOfLeaf() const noexcept;
        
        // @brief get ThrBinarytree in Preorder traversal
        // @retval a pointer that points to the root node of the Thrtree.
        thrnode* getPreThrBiTree() noexcept;
        // @brief get ThrBinarytree in Inorder traversal
        // @retval a pointer that points to the root node of the Thrtree.
        thrnode* getInThrBiTree() noexcept;
        // @brief get ThrBinarytree in Postorder traversal
        // @retval a pointer that points to the root node of the Thrtree.
        thrnode* getPostThrBiTree() noexcept;
        // @brief get ThrBinarytree in BFS traversal
        // @retval a pointer that points to the root node of the Thrtree.
        thrnode* getBFSThrBiTree() noexcept;


    private:
        // @brief a function that help the constructor to construct the tree.
        template <typename InputIterator>
        void __CreateTreeByNLRandLNR(
            InputIterator firstPre, 
            InputIterator lastPre,
            InputIterator firstInorder, 
            InputIterator lastInorder, 
            Binarytreenode * &p
        );

        // @brief a function that help the copy constructor.
        Binarytreenode * __deepcopy(const Binarytreenode *x) const noexcept;
        // @brief a function that help preorder traversal.
        std::vector<T> __preorder(const Binarytreenode *x) const noexcept;
        // @brief a function that help inorder traversal.
        std::vector<T> __inorder(const Binarytreenode *x) const noexcept;
        // @brief a function that help postorder traversal.
        std::vector<T> __postorder(const Binarytreenode *x) const noexcept;
        // @brief a function that help get preorder traversal ThrBinarytree.
        void _preorder(const Binarytreenode *x, thrnode *& y, thrnode *&z) noexcept;
        // @brief a function that help get inorder traversal ThrBinarytree.
        void _inorder(const Binarytreenode *x, thrnode *& y, thrnode *&z) noexcept;
        // @brief a function that help get postorder traversal ThrBinarytree.
        void _postorder(const Binarytreenode *x, thrnode *& y, thrnode *&z) noexcept;
        // @brief a function that help print tree.
        std::string __print(
            const Binarytreenode *x, 
            const size_t depth,
            std::string(*tostr)(const T&)
        ) const noexcept;

        // @brief a function that help find the two vector is match.
        bool _ismatch(std::vector<T> a, std::vector<T> b);
        
        Binarytreenode * p;
        thrnode * t;
        thrnode* null;
};

#include "Binarytree.cpp"

#endif