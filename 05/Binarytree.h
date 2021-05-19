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
            T && default_value
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
        *   0 p -> parents
        *   1 p -> leftchild
        *   2 p -> rightchild
        * @retval Return the root in p, and the new node.
        */
        Binarytreenode* insert(
            const Binarytreenode * p,
            const T && val, 
            const int _pos
        );

        // @brief erase the tree whose root is p
        // @retval return p -> parents if possible
        Binarytreenode* erase(Binarytreenode *p);

        /*
        * @brief Get the pointer that points to the root.
        * @retval a pointer that points to the root.
        */
        Binarytreenode* root() const noexcept {return p;}

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
        * @brief Get the postorder traversal of the tree.
        * @retval Return a vector of the template class that contains the postorder traversal.
        */
        std::vector<T> Postorder() const noexcept;

        /*
        * @brief Get the BFS traversal of the tree.
        * @retval Return a vector of the template class that contains the BFS traversal.
        */
        std::vector<T> BFS() const noexcept;

        /* 
        * @brief Return the info of the tree.
        * @retval The info of the tree.
        */
        std::string info() const noexcept;

        /*
        * @brief print the struct of the tree in a brief way.
        * @retval Return a string that contains the tree struct.
        */
        std::string print() const noexcept;

        /* 
        * @retval Return the number of node of the tree.
        */
        size_t size() const noexcept;

        /*
        * @retval Return the deaph of the tree.
        */
        size_t deaph() const noexcept;

        /* 
        * @retval Return the number of the leaf node.
        */
        size_t sizeOfLeaf() const noexcept;
    private:
        // @brief a function that help the constructor to construct the tree.
        template <typename InputIterator>
        void __CreateTreeByNLRandLNR(
            InputIterator firstPre, 
            InputIterator lastPre,
            InputIterator firstInorder, 
            InputIterator lastInorder
        );

        // @brief a function that help the copy constructor.
        Binarytreenode * __deepcopy(const Binarytreenode *x) const noexcept;
        Binarytreenode * p;
};

#include "Binarytree.cpp"

#endif