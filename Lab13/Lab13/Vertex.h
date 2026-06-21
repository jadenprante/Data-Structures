/*************************************************
* Author:          Jaden Prante
* File Name:       Vertex.h
* Date Created:    May 25th 2025
* Modifications:   Currenrly same date
*
* Class: Vertex
*
* Purpose: This class creates a vertex
*
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
    Vertex& operator=(const Vertex& other);
    Vertex& operator=(Vertex&& other) noexcept;
    ~Vertex();
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
Vertex<V, E>::Vertex(Vertex&& other) noexcept: data(std::move(other.data)), processed(other.processed), edges(std::move(other.edges)) 
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
Vertex<V, E>& Vertex<V, E>::operator=(const Vertex& other) 
{
    if (this != &other) 
    {
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
Vertex<V, E>& Vertex<V, E>::operator=(Vertex&& other) noexcept 
{
    if (this != &other) 
    {
        data = std::move(other.data);
        processed = other.processed;
        edges = std::move(other.edges);
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
