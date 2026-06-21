/*************************************************
* Author:          Jaden Prante
* File Name:       AVLTree.h
* Date Created:    May 2nd 2025
* Modifications:   Currenrly same date
*
* Class: BSTree
*
* Purpose: This class creates a dynamic one-dimensional array that can be
*          started at any base.
*
* Manager Functions:
*       AVLTree() - Default Constructor
*       AVLTree(const AVLTree& other) - Copy Constructor
*       AVLTree(AVLTree&& other) noexcept - Move Constructor
*       AVLTree& operator=(const AVLTree& other) - Copy Assignment Operator
*       AVLTree& operator=(AVLTree&& other) noexcept - Move Assignment Operator
*       ~AVLTree() - Deconstructor
*
* Methods:
*       void Insert(T data);
*       void Delete(T data);
*       void Purge();
*       int Height() const;
*       void InOrder(void (*visit)(T data));
*       void PreOrder(void (*visit)(T data));
*       void PostOrder(void (*visit)(T data));
*       void BreadthFirst(void (*visit)(T data));
*       AVLNode<T>* CopyTree(AVLNode<T>* node);
*       void DestroyTree(AVLNode<T>* node);
*       AVLNode<T>* InsertHelper(AVLNode<T>* node, T data);
*       AVLNode<T>* DeleteHelper(AVLNode<T>* node, T data);
*       int HeightHelper(AVLNode<T>* node) const;
*       void InOrderHelper(AVLNode<T>* node, void (*visit)(T data));
*       void PreOrderHelper(AVLNode<T>* node, void (*visit)(T data));
*       void PostOrderHelper(AVLNode<T>* node, void (*visit)(T data));
*       AVLNode<T>* RotateLeft(AVLNode<T>* node);
*       AVLNode<T>* RotateRight(AVLNode<T>* node);
*       AVLNode<T>* Balance(AVLNode<T>* node);
*       int GetBalanceFactor(AVLNode<T>* node);
*       void UpdateHeight(AVLNode<T>* node);
**************************************************/

#pragma once

#include "AVLNode.h"
#include <iostream>
#include <queue>

using std::cout;
using std::queue;


template <typename T>
class AVLTree {
public:
    AVLTree();
    AVLTree(const AVLTree& other);
    AVLTree(AVLTree&& other) noexcept;
    AVLTree& operator=(const AVLTree& other);
    AVLTree& operator=(AVLTree&& other) noexcept;
    ~AVLTree();
    void Insert(T data);
    void Delete(T data);
    void Purge();
    int Height() const;
    void InOrder(void (*visit)(T data));
    void PreOrder(void (*visit)(T data));
    void PostOrder(void (*visit)(T data));
    void BreadthFirst(void (*visit)(T data));

private:
    AVLNode<T>* root;
    AVLNode<T>* CopyTree(AVLNode<T>* node);
    void DestroyTree(AVLNode<T>* node);
    AVLNode<T>* InsertHelper(AVLNode<T>* node, T data);
    AVLNode<T>* DeleteHelper(AVLNode<T>* node, T data);
    int HeightHelper(AVLNode<T>* node) const;
    void InOrderHelper(AVLNode<T>* node, void (*visit)(T data));
    void PreOrderHelper(AVLNode<T>* node, void (*visit)(T data));
    void PostOrderHelper(AVLNode<T>* node, void (*visit)(T data));
    AVLNode<T>* RotateLeft(AVLNode<T>* node);
    AVLNode<T>* RotateRight(AVLNode<T>* node);
    AVLNode<T>* Balance(AVLNode<T>* node);
    int GetBalanceFactor(AVLNode<T>* node);
    void UpdateHeight(AVLNode<T>* node);  
};

// Constructor
/*************************************************
* Purpose: is default constructor
*
* Precondtions: NA
*
* Postconditions: NA
*
**************************************************/
template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) 
{}

// Copy Constructor
/*************************************************
* Purpose: Copies in the AVL Tree
*
* Precondtions: NA
*
* Postconditions: makes a copy
*
**************************************************/
template <typename T>
AVLTree<T>::AVLTree(const AVLTree& other) : root(nullptr) 
{
    root = CopyTree(other.root);
}

// Move Constructor
/*************************************************
* Purpose: move data in the AVL Tree
*
* Precondtions: data in tree
*
* Postconditions: data is moves
*
**************************************************/
template <typename T>
AVLTree<T>::AVLTree(AVLTree&& other) noexcept : root(other.root) 
{
    other.root = nullptr;
}

// Copy Assignment Operator
/*************************************************
* Purpose: deep copies data
*
* Precondtions: copy constructor
*
* Postconditions: data is deep copied
*
**************************************************/
template <typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree& other) {

    if (this != &other)
    {
        Purge();
        root = CopyTree(other.root);
    }
    return *this;
}

// Move Assignment Operator
/*************************************************
* Purpose: deep copies stuff in move
*
* Precondtions: move constructor
*
* Postconditions: data is deep copied
*
**************************************************/
template <typename T>
AVLTree<T>& AVLTree<T>::operator=(AVLTree&& other) noexcept
{
    if (this != &other) 
    {
        Purge();
        root = other.root;
        other.root = nullptr;
    }
    return *this;
}

// Destructor
/*************************************************
* Purpose: destroys data
*
* Precondtions: data
*
* Postconditions: data is removed
*
**************************************************/
template <typename T>
AVLTree<T>::~AVLTree()
{
    Purge();
}

// CopyTree function
/*************************************************
* Purpose: copies tree data
*
* Precondtions: root
*
* Postconditions: data is copied over
*
**************************************************/
template <typename T>
AVLNode<T>* AVLTree<T>::CopyTree(AVLNode<T>* node) 
{
    if (!node)
    {
        return nullptr;
    }
    AVLNode<T>* newNode = new AVLNode<T>(node->GetData());
    newNode->SetLeft(CopyTree(node->GetLeft()));
    newNode->SetRight(CopyTree(node->GetRight()));
    newNode->SetHeight(node->GetHeight());
    return newNode;
}

// Destroy Tree function
/*************************************************
* Purpose: Delets a node from tree
*
* Precondtions: node must be in tree
*
* Postconditions: node is deleted
*
**************************************************/
template <typename T>
void AVLTree<T>::DestroyTree(AVLNode<T>* node) {
    if (node) 
    {
        DestroyTree(node->GetLeft());
        DestroyTree(node->GetRight());
        delete node;
    }
}

// Purge function
/*************************************************
* Purpose: Purges from tree
*
* Precondtions: nodes are in tree
*
* Postconditions: data is purged
*
**************************************************/
template <typename T>

void AVLTree<T>::Purge() 
{
    DestroyTree(root);
    root = nullptr;
}

// Height function
/*************************************************
* Purpose: delcares height
*
* Precondtions: node data
*
* Postconditions: height is declared
*
**************************************************/
template <typename T>
int AVLTree<T>::Height() const 
{
    return HeightHelper(root);
}

// Height helper function
template <typename T>
int AVLTree<T>::HeightHelper(AVLNode<T>* node) const 
{
    if (node == nullptr) 
    {
        return -1;
    }
    return node->GetHeight();
}

// GetBalanceFactor function
/*************************************************
* Purpose: factors the balance 
*
* Precondtions: node data
*
* Postconditions: tree is factor balanced
*
**************************************************/
template <typename T>
int AVLTree<T>::GetBalanceFactor(AVLNode<T>* node) 
{
    if (!node)
    {
        return 0;
    }
    return HeightHelper(node->GetLeft()) - HeightHelper(node->GetRight());
}

// LeftRotation function
/*************************************************
* Purpose: rotates the nodes to the left
*
* Precondtions: node data
*
* Postconditions: nodes are rotated
*
**************************************************/
template <typename T>
AVLNode<T>* AVLTree<T>::RotateLeft(AVLNode<T>* node) 
{
    AVLNode<T>* newRoot = node->GetRight();
    node->SetRight(newRoot->GetLeft());
    newRoot->SetLeft(node);
    UpdateHeight(node);
    UpdateHeight(newRoot);
    return newRoot;
}

// RightRotation function
/*************************************************
* Purpose: rotates the nodes to the right
*
* Precondtions: node data
*
* Postconditions: nodes are rotated
*
**************************************************/
template <typename T>
AVLNode<T>* AVLTree<T>::RotateRight(AVLNode<T>* node) 
{
    AVLNode<T>* newRoot = node->GetLeft();
    node->SetLeft(newRoot->GetRight());
    newRoot->SetRight(node);
    UpdateHeight(node);
    UpdateHeight(newRoot);
    return newRoot;
}

// Balance function
/*************************************************
* Purpose: balances tree nodes
*
* Precondtions: node data
*
* Postconditions: tree is properly balanced
*
**************************************************/
template <typename T>
AVLNode<T>* AVLTree<T>::Balance(AVLNode<T>* node)
{
    if (!node)
    {
        return nullptr;
    }
    UpdateHeight(node);
    int balance = GetBalanceFactor(node);
    // Left heavy
    if (balance > 1) 
    {
        if (GetBalanceFactor(node->GetLeft()) < 0) 
        {
            node->SetLeft(RotateLeft(node->GetLeft()));
        }
        return RotateRight(node);
    }
    // Right heavy
    if (balance < -1) {
        if (GetBalanceFactor(node->GetRight()) > 0) 
        {
            node->SetRight(RotateRight(node->GetRight()));
        }
        return RotateLeft(node);
    }
    return node;
}

// Insert function
/*************************************************
* Purpose: inserts node into tree
*
* Precondtions: node data
*
* Postconditions: node is inserted
*
**************************************************/
template <typename T>
void AVLTree<T>::Insert(T data)
{
    root = InsertHelper(root, data);
}

template <typename T>
AVLNode<T>* AVLTree<T>::InsertHelper(AVLNode<T>* node, T data)
{
    if (!node) 
    {
        return new AVLNode<T>(data);
    }
    if (data < node->GetData())
    {
        node->SetLeft(InsertHelper(node->GetLeft(), data));
    }
    else if (data > node->GetData())
    {
        node->SetRight(InsertHelper(node->GetRight(), data));
    }
    else 
    {
        return node; // Duplicate values not allowed
    }
    UpdateHeight(node);
    return Balance(node);
}

// Delete function
/*************************************************
* Purpose: delets data from tree
*
* Precondtions: root data
*
* Postconditions: tree data is deleted
*
**************************************************/
template <typename T>
void AVLTree<T>::Delete(T data) 
{
    root = DeleteHelper(root, data);
}

template <typename T>
AVLNode<T>* AVLTree<T>::DeleteHelper(AVLNode<T>* node, T data) 
{
    if (!node)
    {
        return nullptr;
    }
    if (data < node->GetData()) 
    {
        node->SetLeft(DeleteHelper(node->GetLeft(), data));
    }
    else if (data > node->GetData())
    {
        node->SetRight(DeleteHelper(node->GetRight(), data));
    }
    else 
    {
        if (!node->GetLeft())
        {
            AVLNode<T>* rightChild = node->GetRight();
            delete node;
            return rightChild;
        }
        if (!node->GetRight())
        {
            AVLNode<T>* leftChild = node->GetLeft();
            delete node;
            return leftChild;
        }
        AVLNode<T>* minRight = node->GetRight();
        while (minRight->GetLeft())
        {
            minRight = minRight->GetLeft();
        }
        node->SetData(minRight->GetData());
        node->SetRight(DeleteHelper(node->GetRight(), minRight->GetData()));
    }
    return Balance(node);
}

// InOrder Traversal
/*************************************************
* Purpose: dispalys nodes with inorder trvaersal
*
* Precondtions: node data
*
* Postconditions: nodes are displayed in this trvaersal
*
**************************************************/
template <typename T>
void AVLTree<T>::InOrder(void (*visit)(T data))
{
    InOrderHelper(root, visit);
}

template <typename T>
void AVLTree<T>::InOrderHelper(AVLNode<T>* node, void (*visit)(T data))
{
    if (node) 
    {
        InOrderHelper(node->GetLeft(), visit);
        visit(node->GetData());
        InOrderHelper(node->GetRight(), visit);
    }
}

// PreOrder Traversal
/*************************************************
* Purpose: dispalys nodes with preorder trvaersal
*
* Precondtions: node data
*
* Postconditions: nodes are displayed in this trvaersal
*
**************************************************/
template <typename T>
void AVLTree<T>::PreOrder(void (*visit)(T data)) 
{
    PreOrderHelper(root, visit);
}

template <typename T>
void AVLTree<T>::PreOrderHelper(AVLNode<T>* node, void (*visit)(T data))
{
    if (node)
    {
        visit(node->GetData());
        PreOrderHelper(node->GetLeft(), visit);
        PreOrderHelper(node->GetRight(), visit);
    }
}

// PostOrder Traversal
/*************************************************
* Purpose: dispalys nodes with postorder trvaersal
*
* Precondtions: node data
*
* Postconditions: nodes are displayed in this trvaersal
* 
**************************************************/
template <typename T>
void AVLTree<T>::PostOrder(void (*visit)(T data)) 
{
    PostOrderHelper(root, visit);
}

template <typename T>
void AVLTree<T>::PostOrderHelper(AVLNode<T>* node, void (*visit)(T data))
{
    if (node)
    {
        PostOrderHelper(node->GetLeft(), visit);
        PostOrderHelper(node->GetRight(), visit);
        visit(node->GetData());
    }
}

// Breadth-First Traversal
/*************************************************
* Purpose: dispalys nodes with breadthfirst trvaersal
*
* Precondtions: node data
*
* Postconditions: nodes are displayed in this trvaersal
*
**************************************************/
template <typename T>
void AVLTree<T>::BreadthFirst(void (*visit)(T data)) 
{
    queue<AVLNode<T>*> q;
    q.push(root);
    while (!q.empty())
    {
        AVLNode<T>* node = q.front();
        q.pop();
        visit(node->GetData());
        if (node->GetLeft())
        {
            q.push(node->GetLeft());
        }
        if (node->GetRight()) 
        {
            q.push(node->GetRight()); 
        }
    }
}

// UpdateHeight function
/*************************************************
* Purpose: helps update height of function
*
* Precondtions: node data
*
* Postconditions: nodes are added, height is updated
*
**************************************************/
template <typename T>
void AVLTree<T>::UpdateHeight(AVLNode<T>* node) 
{
    if (node) 
    {
        int leftHeight = HeightHelper(node->GetLeft());
        int rightHeight = HeightHelper(node->GetRight());
        node->SetHeight(1 + std::max(leftHeight, rightHeight));
    }
}
