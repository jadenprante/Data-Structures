/*************************************************
* Author:          Jaden Prante
* File Name:       BSNode.h
* Date Created:    Apr 29th 2025
* Modifications:   Currenrly same date
*
* Class: BSNode
*
* Purpose: This class creates a dynamic one-dimensional array that can be
*          started at any base.
*
* Manager Functions:
*       BSNode() - Default Constructor
*       BSNode(const BSNode& other) - Copy Constructor
*       BSNode(BSNode&& other) noexcept - Move Constructor
*       BSNode& operator=(const BSNode& other) - Copy Assignment Operator
*       BSNode& operator=(BSNode&& other) noexcept - Move Assignment Operator
*       ~BSNode() - Deconstructor
*
* Methods:
*       BSNode* GetLeft() const;
*       BSNode* GetRight() const;
*       int GetHeight() const;
*       void SetLeft(BSNode* left);
*       void SetRight(BSNode* right);
*       void SetHeight(int height);
*
**************************************************/

#pragma once
template <typename T>
class BSTree;
template <typename T>
class BSNode {
public:
    BSNode();
    BSNode(T val);
    BSNode(const BSNode& other);
    BSNode(BSNode&& other) noexcept;
    BSNode& operator=(const BSNode& other);
    BSNode& operator=(BSNode&& other) noexcept;
    ~BSNode();
    BSNode* GetLeft() const;
    BSNode* GetRight() const;
    int GetHeight() const;
    void SetLeft(BSNode* left);
    void SetRight(BSNode* right);
    void SetHeight(int height);
private:
    T data;
    BSNode* m_left;
    BSNode* m_right;
    int m_height;
    friend class BSTree<T>;
};
//Default Constructor
/*************************************************
* Purpose: Is Default Constructor for BSNode
* 
* Precondtions: NA
* 
* Postconditions: NA
* 
**************************************************/
template<typename T>
inline BSNode<T>::BSNode() : m_left(nullptr), m_right(nullptr), m_height(0) 
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
inline BSNode<T>::BSNode(T val) : data(val), m_left(nullptr), m_right(nullptr), m_height(0) 
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
inline BSNode<T>::BSNode(const BSNode& other): data(other.data), m_left(other.m_left), m_right(other.m_right), m_height(other.m_height) 
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
inline BSNode<T>::BSNode(BSNode&& other) noexcept : data(std::move(other.data)), m_left(other.m_left), m_right(other.m_right), m_height(other.m_height) 
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
inline BSNode<T>& BSNode<T>::operator=(const BSNode& other) 
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
inline BSNode<T>& BSNode<T>::operator=(BSNode&& other) noexcept
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
inline BSNode<T>::~BSNode() 
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
inline BSNode<T>* BSNode<T>::GetLeft() const 
{
    return m_left;
}

template<typename T>
inline BSNode<T>* BSNode<T>::GetRight() const 
{
    return m_right;
}

template<typename T>
inline int BSNode<T>::GetHeight() const
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
inline void BSNode<T>::SetLeft(BSNode* left) 
{
    m_left = left;
}

template<typename T>
inline void BSNode<T>::SetRight(BSNode* right) 
{
    m_right = right;
}

template<typename T>
inline void BSNode<T>::SetHeight(int height) 
{
    m_height = height;
}
