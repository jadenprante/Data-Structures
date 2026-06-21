/*************************************************
* Author:          Jaden Prante
* File Name:       BSTree.h
* Date Created:    May 1st 2025
* Modifications:   May 2nd 2025
*                  All traversals (besides breadth-first)
*                  have been redone to have
*                  if statements for a node going 
*                  left or right, redid delete function to 
*                  properly delete nodes
*                  May 10th 2025
*                  Fixed InOrder, PostOrder and DestroyTree
*                  functions, and added error checking in
*                  BreadthFirst function
*                  May 11th 2025
*                  Traversal functions now error check if it 
*                  can't visit the tree
*
* Class: BSTree
*
* Purpose: This class creates a dynamic one-dimensional array that can be
*          started at any base.
*
* Manager Functions:
*       BSTree() - Default Constructor
*       BSTree(const BSTree& other) - Copy Constructor
*       BSTree(BSTree&& other) noexcept - Move Constructor
*       BSTree& operator=(const BSTree& other) - Copy Assignment Operator
*       BSTree& operator=(BSTree&& other) noexcept - Move Assignment Operator
*       ~BSTree() - Deconstructor
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
*       void Visit(T data);
*       BSNode<T>* CopyTree(BSNode<T>* node);
*       void DestroyTree(BSNode<T>* node);
*       BSNode<T>* InsertHelper(BSNode<T>* node, T data);
*       BSNode<T>* DeleteHelper(BSNode<T>* node, T data);
*       int HeightHelper(BSNode<T>* node) const;
*       void InOrderHelper(BSNode<T>* node, void (*visit)(T data));
*       void PreOrderHelper(BSNode<T>* node, void (*visit)(T data));
*       void PostOrderHelper(BSNode<T>* node, void (*visit)(T data));
*
**************************************************/

#pragma once

#include "BSNode.h"
#include "Exception.h"
#include <iostream>
#include <queue>

using std::cout;
using std::queue;

template <typename T>
class BSTree {
public:
    BSTree();
    BSTree(const BSTree& other);
    BSTree(BSTree&& other) noexcept;
    BSTree& operator=(const BSTree& other);
    BSTree& operator=(BSTree&& other) noexcept;
    ~BSTree();
    void Insert(T data);
    void Delete(T data);
    void Purge();
    int Height() const;
    void InOrder(void (*visit)(T data));
    void PreOrder(void (*visit)(T data));
    void PostOrder(void (*visit)(T data));
    void BreadthFirst(void (*visit)(T data));
    
private:
    BSNode<T>* root;
    BSNode<T>* CopyTree(BSNode<T>* node);
    void PurgeHelper(BSNode<T>* node);
    BSNode<T>* InsertHelper(BSNode<T>* node, T data);
    BSNode<T>* DeleteHelper(BSNode<T>* node, T data);
    int HeightHelper(BSNode<T>* node) const;
    void InOrderHelper(BSNode<T>* node, void (*visit)(T data));
    void PreOrderHelper(BSNode<T>* node, void (*visit)(T data));
    void PostOrderHelper(BSNode<T>* node, void (*visit)(T data));
};

// Default Constructor
/*************************************************
* Purpose: Is Default Constructor for BSTree
*
* Precondtions: NA
*
* Postconditions: NA
*
**************************************************/
template<typename T>
BSTree<T>::BSTree() : root(nullptr) 
{}

// Copy Constructor
/*************************************************
* Purpose: Creates a copy of BSTree
*
* Precondtions: root data
*
* Postconditions: root data is copied
*
**************************************************/
template<typename T>
BSTree<T>::BSTree(const BSTree& other) 
{
    root = CopyTree(other.root);
}

// Move Constructor
/*************************************************
* Purpose: Moves the BSTree
*
* Precondtions: root data
*
* Postconditions: root data is moved
*
**************************************************/
template<typename T>
BSTree<T>::BSTree(BSTree&& other) noexcept : root(other.root) 
{
    other.root = nullptr;
}

// Copy Assignment Operator
/*************************************************
* Purpose: Makes a deep copy of a BSTree
*
* Precondtions: root data
*
* Postconditions: root data is deep copied
*
**************************************************/
template<typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree& other) 
{
    if (this != &other) 
    {
        Purge();
        root = CopyTree(other.root);
    }
    return *this;
}

// Move Assignment Operator
/*************************************************
* Purpose: Makes a deep copy of a BSTree and 
*          moves it to the right hand side
*
* Precondtions: root data
*
* Postconditions: root data is deep copied and 
*                 moved to the right hand side
*
**************************************************/
template<typename T>
BSTree<T>& BSTree<T>::operator=(BSTree&& other) noexcept 
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
* Purpose: Is destructor for BSTree
*
* Precondtions: root data
*
* Postconditions: root data is deleted
*
**************************************************/
template<typename T>
BSTree<T>::~BSTree()
{
    Purge();
}

// CopyTree Function
/*************************************************
* Purpose: This function copies a tree
*
* Precondtions: Existing tree
*
* Postconditions: Another tree is copied
*
**************************************************/
template<typename T>
BSNode<T>* BSTree<T>::CopyTree(BSNode<T>* node) 
{
    if (!node)
    {
        return nullptr;
    }
    BSNode<T>* newNode = new BSNode<T>(node->data);
    newNode->SetLeft(CopyTree(node->GetLeft()));
    newNode->SetRight(CopyTree(node->GetRight()));
    return newNode;
}

// Purge Function
/*************************************************
* Purpose: Deletes a tree
*
* Precondtions: Tree data
*
* Postconditions: tree is deleted
*
**************************************************/
template<typename T>
void BSTree<T>::Purge()
{
    PurgeHelper(root);
    root = nullptr;
}

// DestroyTree Function
/*************************************************
* Purpose: Destroys a tree
*
* Precondtions: Existing tree
*
* Postconditions: Tree is deleted
*
**************************************************/
template<typename T>
void BSTree<T>::PurgeHelper(BSNode<T>* node) 
{
    if (node) 
    {
        if (node->GetLeft() != nullptr)
        {
            PurgeHelper(node->GetLeft());
        }
        if (node->GetRight() != nullptr)
        {
            PurgeHelper(node->GetRight());
        }
        delete node;
    }
}

// Insert function
/*************************************************
* Purpose: Inserts a node into the tree
*
* Precondtions: calls the Helper function
*
* Postconditions: A node is insereted into the tree
*
**************************************************/
template<typename T>
void BSTree<T>::Insert(T data) 
{
    root = InsertHelper(root, data);
}

// InsertHelper Function
/*************************************************
* Purpose: The helper function for insert
*
* Precondtions: tree and node data
*
* Postconditions: Helps insert a node into the tree
*
**************************************************/
template<typename T>
BSNode<T>* BSTree<T>::InsertHelper(BSNode<T>* node, T data)
{
    if (!node) 
    {
        return new BSNode<T>(data);
    }
    if (data < node->data)
    { 
        node->SetLeft(InsertHelper(node->GetLeft(), data));
    }
    else if (data > node->data)
    {
        node->SetRight(InsertHelper(node->GetRight(), data));
    }
    return node;
}

// Delete function
/*************************************************
* Purpose: Deletes a node from the tree
*
* Precondtions: calls the Helper function
*
* Postconditions: A node is deleted from the tree
*
**************************************************/
template<typename T>
void BSTree<T>::Delete(T data) 
{
    root = DeleteHelper(root, data);
}

// DeleteHelper Function
/*************************************************
* Purpose: The helper function for delete
*
* Precondtions: tree and node data
*
* Postconditions: Helps delete a node from the tree
*
**************************************************/
template<typename T>
BSNode<T>* BSTree<T>::DeleteHelper(BSNode<T>* node, T data)
{
    if (!node)
    {
        throw Exception("Node not found for deletion");
    }
    if (data < node->data)
    {
        node->SetLeft(DeleteHelper(node->GetLeft(), data));
    }
    else if (data > node->data)
    {
        node->SetRight(DeleteHelper(node->GetRight(), data));
    }
    else 
    {
        if (!node->GetLeft())
        {
            BSNode<T>* rightChild = node->GetRight();
            delete node;
            return rightChild;
        }
        if (!node->GetRight())
        {
            BSNode<T>* leftChild = node->GetLeft();
            delete node;
            return leftChild;
        }
        BSNode<T>* successor = node->GetRight();
        while (successor->GetLeft())
        {
            successor = successor->GetLeft();
        }
        node->data = successor->data;
        node->SetRight(DeleteHelper(node->GetRight(), successor->data));
    }
    return node;
}


// Height function
/*************************************************
* Purpose: Creates the height of the tree
*
* Precondtions: calls the Helper function
*
* Postconditions: Height of tree is created
*
**************************************************/
template<typename T>
int BSTree<T>::Height() const 
{
    return HeightHelper(root);
}

// HeightHelper Function
/*************************************************
* Purpose: Helper function for height
*
* Precondtions: Tree and node data
*
* Postconditions: Helps create height of tree
*
**************************************************/
template<typename T>
int BSTree<T>::HeightHelper(BSNode<T>* node) const
{
    if (!node)
    {
        return -1;
    }
    return 1 + std::max(HeightHelper(node->GetLeft()), HeightHelper(node->GetRight()));
}

// In-order traversal
/*************************************************
* Purpose: Traverses into the tree in order
*
* Precondtions: Calls the helper function
*
* Postconditions: Tree is traversed in order
*
**************************************************/
template<typename T>
void BSTree<T>::InOrder(void (*visit)(T data)) 
{
    InOrderHelper(root, visit);
}

// In-order helper function
/*************************************************
* Purpose: Helps traverse the tree in order
*
* Precondtions: Tree and node data
*
* Postconditions: Helped tree traverse in order
*
**************************************************/
template<typename T>
void BSTree<T>::InOrderHelper(BSNode<T>* node, void (*visit)(T data))
{
    if (!visit)
    {
        throw Exception("Can't Traverse Here");
    }
    if (node != nullptr)
    {
        if (node->GetLeft())
        {
            InOrderHelper(node->GetLeft(), visit);
        }
        visit(node->data);
        if (node->GetRight())
        {
            InOrderHelper(node->GetRight(), visit);
        }
    }
}

// Pre-order traversal
/*************************************************
* Purpose: Traverses into the tree pre order
*
* Precondtions: Calls the helper function
*
* Postconditions: Tree is traversed pre order
*
**************************************************/
template<typename T>
void BSTree<T>::PreOrder(void (*visit)(T data)) 
{
    if (root)
    { 
        PreOrderHelper(root, visit); 
    }
}

// Pre-order helper function
/*************************************************
* Purpose: Helps traverse the tree pre order
*
* Precondtions: Tree and node data
*
* Postconditions: Helped tree traverse pre order
*
**************************************************/
template<typename T>
void BSTree<T>::PreOrderHelper(BSNode<T>* node, void (*visit)(T data)) 
{
    if (!visit)
    {
        throw Exception("Can't Traverse Here");
    }
    if (node != nullptr)
    {
        visit(node->data);
        if (node->GetLeft())
        {
            PreOrderHelper(node->GetLeft(), visit);
        }
        if (node->GetRight())
        {
            PreOrderHelper(node->GetRight(), visit);
        }
    }
}

// Post-order traversal
/*************************************************
* Purpose: Traverses into the tree post order
*
* Precondtions: Calls the helper function
*
* Postconditions: Tree is traversed post order
*
**************************************************/
template<typename T>
void BSTree<T>::PostOrder(void (*visit)(T data))
{
    if (root)
    {
        PostOrderHelper(root, visit);
    }
}

// Post-order helper function
/*************************************************
* Purpose: Helps traverse the tree post order
*
* Precondtions: Tree and node data
*
* Postconditions: Helped tree traverse post order
*
**************************************************/
template<typename T>
inline void BSTree<T>::PostOrderHelper(BSNode<T>* node, void (*visit)(T data)) 
{
    if (!visit)
    {
        throw Exception("Can't Traverse Here");
    }
    if (node != nullptr)
    {
        if (node->GetLeft())
        {
            PostOrderHelper(node->GetLeft(), visit);
        }
        if (node->GetRight())
        {
            PostOrderHelper(node->GetRight(), visit);
        }
        visit(node->data);
    }
}

// Breadth-first traversal
/*************************************************
* Purpose: Traverses into the tree breadth first
*
* Precondtions: Calls the helper function
*
* Postconditions: Tree is traversed breadth first
*
**************************************************/
template<typename T>
inline void BSTree<T>::BreadthFirst(void(*visit)(T data))
{
    if (!root)
    {
        throw Exception("Not a root");
    }
    queue<BSNode<T>*> q;
    q.push(root);
    while (!q.empty()) 
    {
        BSNode<T>* node = q.front();
        q.pop();
        visit(node->data);
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


