#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>

namespace BST 
{
    template <typename T>

    class Tree
    {
        private:
            struct Node
            {
                T m_data;
                Node* m_left;
                Node* m_right;
                Node() : m_left(nullptr), m_right(nullptr) {}
            };
            Node* m_root = nullptr;
            void privateInsert(const T&, Node*);
            void privateDelete(const T&, Node*&);
            bool privateSearch(const T&, Node*) const;
            void privateInorder(Node*);
            void privatePreorder(Node*);
            void privatePostorder(Node*);
            T privateFindMin(Node*) const;
            T privateFindMax(Node*) const;
            T privateSuccessor(const T&, Node*) const;
            T privatePredecessor(const T&, Node*) const;
            unsigned long privateHeight(Node*) const;
            unsigned long privateSize(Node*) const;
            bool privateIsValidBST(Node*) const;
            void privateLevlOrder(Node*, unsigned long);
            void privateSerialize(Node*, T*&, unsigned long&) const;
        public:
            Tree();
            ~Tree();
            void Insert(const T&);
            void Delete(const T&);
            bool Search(const T&) const;
            void Inorder();
            void Preorder();
            void Postorder();
            T FindMin() const;
            T FindMax() const;
            T Successor(const T&) const;
            T Predecessor(const T&) const;
            unsigned long Height() const;
            unsigned long Size() const;
            bool IsValidBST() const;
            void LevlOrder();
            void Clear();
            T* Serialize() const;
            Tree Copy() const;
            void Update(const T&, const T&);
            void RangeQuery(const T&, const T&);
            T KthSmallest(unsigned long) const;
            T KthLargest(unsigned long) const;
    };
}
#include "binarySearchTree.cpp"
#endif