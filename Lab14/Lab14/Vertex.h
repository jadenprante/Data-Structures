/*************************************************
* Author:          Jaden Prante
* File Name:       Vertex.h
* Date Created:    May 26th 2025
* Modifications:   May 29th 2025
*                  Fixed Assigment Operators to
*                  function accordingly, added getters
*                  and set processed functions
*
* Class: Vertex
*
* Purpose: This class creates a vertex
*
* Manager Functions:
*       Vertex() - Default Constructor
*       Vertex(const Vertex& other) - Copy Constructor
*       Vertex(Vertex&& other) noexcept - Move Constructor
*       Vertex& operator=(const Vertex& other) - Copy Assignment Operator
*       Vertex& operator=(Vertex&& other) noexcept - Move Assignment Operator
*       ~Vertex() - Deconstructor
*
**************************************************/


#pragma once

#include <iostream>
#include "Edge.h"
#include <list>

using std::list;

template <typename V, typename E>
class Vertex {
public:
    Vertex();
    Vertex(const V& value);
    Vertex(const Vertex& other);
    Vertex(Vertex&& other) noexcept;
    Vertex& operator=(const Vertex< V, E>& other);
    Vertex& operator=(Vertex< V, E>&& other) noexcept;
    ~Vertex();
    V GetDataVertex() const;
    bool GetProcessed() const;
    list<Edge<V, E>> GetEdge();
    void SetData(const V& value);
    void SetProcessed(bool processed);
    void AddEdge(const Edge<V, E>& edge);
private:
    V data;
    bool processed;
    list<Edge<V, E>> edges;
};


// Default constructor
/*************************************************
* Purpose: is construtor for vertex
*
* Precondtions: NA
*
* Postconditions: NA
*
**************************************************/
template<typename V, typename E>
Vertex<V, E>::Vertex() : data(V()), processed(false), edges()
{}

// Parameterized constructor
/*************************************************
* Purpose: is construtor for vertex
*
* Precondtions: NA
*
* Postconditions: data members are altered
*
**************************************************/
template<typename V, typename E>
Vertex<V, E>::Vertex(const V& value) : data(value), processed(false), edges()
{}

// Copy constructor
/*************************************************
* Purpose: copies data
*
* Precondtions: vertex data
*
* Postconditions: data is copied
*
**************************************************/
template<typename V, typename E>
Vertex<V, E>::Vertex(const Vertex& other)
    : data(other.data), processed(other.processed), edges(other.edges)
{}

// Move constructor
/*************************************************
* Purpose: moves data
*
* Precondtions: vertex data
*
* Postconditions: data is moved
*
**************************************************/
template<typename V, typename E>
Vertex<V, E>::Vertex(Vertex&& other) noexcept : data(std::move(other.data)), processed(other.processed), edges(std::move(other.edges))
{}

// Copy assignment operator
/*************************************************
* Purpose: makes a deep copy of vertex data
*
* Precondtions: vertex data
*
* Postconditions: vertex data is deep copied
*
**************************************************/
template<typename V, typename E>
Vertex<V, E>& Vertex<V, E>::operator=(const Vertex < V, E>& other)
{
    if (this != &other)
    {
        edges.clear();
        data = other.data;
        processed = other.processed;
        edges = other.edges;
    }
    return *this;
}

// Move assignment operator
/*************************************************
* Purpose: makes deep copy of move data
*
* Precondtions: vertex data
*
* Postconditions: vertex data is deep moved on right
*                 hand side
*
**************************************************/
template<typename V, typename E>
Vertex<V, E>& Vertex<V, E>::operator=(Vertex < V, E>&& other) noexcept
{
    if (this != &other)
    {
        edges.clear();
        edges = std::move(other.edges);
        data = other.data;
        other.data = V();
        processed = other.m_processed;
        other.processed = false;
    }
    return *this;
}

// Destructor
/*************************************************
* Purpose: destroys vertex data
*
* Precondtions: vertex data
*
* Postconditions: data is deleted
*
**************************************************/
template<typename V, typename E>
Vertex<V, E>::~Vertex()
{
    edges.clear();
}

// Getter Functions 
/*************************************************
* Purpose: Get vertex data, egde and processed data
*
* Precondtions: data member contents
*
* Postconditions: getters are set
*
**************************************************/
template<typename V, typename E>
V Vertex<V, E>::GetDataVertex() const
{
    return data;
}

template<typename V, typename E>
list<Edge<V, E>> Vertex<V, E>::GetEdge()
{
    return edges;
}

template<typename V, typename E>
bool Vertex<V, E>::GetProcessed() const
{
    return processed;
}

// Set Processed Function
/*************************************************
* Purpose: Sets the processed data memeber
*
* Precondtions: processed
*
* Postconditions: processed is set
*
**************************************************/
template<typename V, typename E>
void Vertex<V, E>::SetData(const V& value)
{
    data = value;
}

template<typename V, typename E>
void Vertex<V, E>::SetProcessed(bool processed2)
{
    processed = processed2;
}

template<typename V, typename E>
void Vertex<V, E>::AddEdge(const Edge<V, E>& edge) 
{
    edges.push_back(edge);
}