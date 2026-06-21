/*************************************************
* Author:          Jaden Prante
* File Name:       AVLNode.h
* Date Created:    May 2nd 2025
* Modifications:   Currenrly same date
*
* Class: BSTree
*
* Purpose: This class creates a dynamic one-dimensional array that can be
*          started at any base.
*
* Manager Functions:
*       AVLNode() - Default Constructor
*       AVLNode(const AVLNode& other) - Copy Constructor
*       AVLNode(AVLNode&& other) noexcept - Move Constructor
*       AVLNode& operator=(const AVLNode& other) - Copy Assignment Operator
*       AVLNode& operator=(AVLNode&& other) noexcept - Move Assignment Operator
*       ~AVLNode() - Deconstructor
*
* Methods:
*       AVLNode* GetLeft() const;
*       AVLNode* GetRight() const;
*       int GetHeight() const;
*       void SetLeft(AVLNode* left);
*       void SetRight(AVLNode* right);
*       void SetHeight(int height);
*
**************************************************/

#pragma once
template <typename T>
class AVLTree;
template <typename T>
class AVLNode {
public:
    AVLNode();
    AVLNode(T val);
    AVLNode(const AVLNode& other);
    AVLNode(AVLNode&& other) noexcept;
    AVLNode& operator=(const AVLNode& other);
    AVLNode& operator=(AVLNode&& other) noexcept;
    ~AVLNode();
    AVLNode* GetLeft() const;
    AVLNode* GetRight() const;
    T GetData() const;
    int GetHeight() const;
    void SetLeft(AVLNode* left);
    void SetRight(AVLNode* right);
    void SetHeight(int height);
    void SetData(T data);
private:
    T data;
    AVLNode* m_left;
    AVLNode* m_right;
    int m_height;
    friend class AVLTree<T>;
};
//Default Constructor
/*************************************************
* Purpose: Is Default Constructor for AVLNode
*
* Precondtions: NA
*
* Postconditions: NA
*
**************************************************/
template<typename T>
inline AVLNode<T>::AVLNode() : m_left(nullptr), m_right(nullptr), m_height(0)
{}

//Constructor with Parameters
/*************************************************
* Purpose: Construtor with Parameters
*
* Precondtions: NA
*
* Postconditions: Node data members are set
*
**************************************************/
template<typename T>
inline AVLNode<T>::AVLNode(T val) : data(val), m_left(nullptr), m_right(nullptr), m_height(0)
{}

//Copy Constructor
/*************************************************
*Purpose: Creates a copy of a node
*
*Precondition: Called when a class object is created
*              based on another object value
*
*Postcondistion: New object would be created based
*                on another object value
*
**************************************************/
template<typename T>
inline AVLNode<T>::AVLNode(const AVLNode& other) : data(other.data), m_left(other.m_left), m_right(other.m_right), m_height(other.m_height)
{}

//Move Constructor
/*************************************************
* Purpose: Moves a copy of a node
*
* Precondtions: Node data
*
* Postconditions: Node data is moved to the
*                 right hand side
*
**************************************************/
template<typename T>
inline AVLNode<T>::AVLNode(AVLNode&& other) noexcept : data(std::move(other.data)), m_left(other.m_left), m_right(other.m_right), m_height(other.m_height)
{
    other.m_left = nullptr;
    other.m_right = nullptr;
}

// Copy Assignment Operator
/*************************************************
* Purpose: Makes a deep of a node
*
* Precondtions: Node data
*
* Postconditions: Node data is deep copied
*
**************************************************/
template<typename T>
inline AVLNode<T>& AVLNode<T>::operator=(const AVLNode& other)
{
    if (this != &other)
    {
        data = other.data;
        m_left = other.m_left;
        m_right = other.m_right;
        m_height = other.m_height;
    }
    return *this;
}

// Move Assignment Operator
/*************************************************
* Purpose: Makes a deep copy and moves a node
*
* Precondtions: Node data
*
* Postconditions: Node data is copied and moved
*                 to the right hand side
*
**************************************************/
template<typename T>
inline AVLNode<T>& AVLNode<T>::operator=(AVLNode&& other) noexcept
{
    if (this != &other)
    {
        data = std::move(other.data);
        m_left = other.m_left;
        m_right = other.m_right;
        m_height = other.m_height;
        other.m_left = nullptr;
        other.m_right = nullptr;
    }
    return *this;
}

// Destructor
/*************************************************
* Purpose: Is destructor for the node
*
* Precondtions: Node data
*
* Postconditions: Node data is deleted
*
**************************************************/
template<typename T>
inline AVLNode<T>::~AVLNode()
{
    m_left = nullptr;
    m_right = nullptr;
    m_height = 0;
}

// Getter Functions
/*************************************************
* Purpose: Gets the left, and right node, along with
*          height of tree
*
* Precondtions: Node and tree data
*
* Postconditions: Node data and tree height are
*                 acquired
*
**************************************************/
template<typename T>
inline AVLNode<T>* AVLNode<T>::GetLeft() const
{
    return m_left;
}

template<typename T>
inline AVLNode<T>* AVLNode<T>::GetRight() const
{
    return m_right;
}

template<typename T>
inline T AVLNode<T>::GetData() const
{
    return data;
}

template<typename T>
inline int AVLNode<T>::GetHeight() const
{
    return m_height;
}

// Setter Functions
/*************************************************
* Purpose: Sets the left, and right node, along with
*          height of tree
*
* Precondtions: Node and tree data obtained
*
* Postconditions: Node data and tree height are
*                 set
*
**************************************************/
template<typename T>
inline void AVLNode<T>::SetLeft(AVLNode* left)
{
    m_left = left;
}

template<typename T>
inline void AVLNode<T>::SetRight(AVLNode* right)
{
    m_right = right;
}

template<typename T>
inline void AVLNode<T>::SetHeight(int height)
{
    m_height = height;
}

template<typename T>
inline void AVLNode<T>::SetData(T data2)
{
    data = data2;
}
