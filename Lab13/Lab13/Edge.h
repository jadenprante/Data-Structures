/*************************************************
* Author:          Jaden Prante
* File Name:       Edge.h
* Date Created:    May 25th 2025
* Modifications:   Currenrly same date
*
* Class: Edge
*
* Purpose: This class creates a Edge
*
*
* Manager Functions:
*       Edge() - Default Constructor
*       Edge(const Edge& other) - Copy Constructor
*       Edge(Edge&& other) noexcept - Move Constructor
*       Edge& operator=(const Edge& other) - Copy Assignment Operator
*       Edge& operator=(Edge&& other) noexcept - Move Assignment Operator
*       ~Edge() - Deconstructor
*
**************************************************/


#pragma once
#include "Vertex.h"

template <typename V, typename E>
class Vertex;

template <typename V, typename E>
class Edge {
public:
    Edge();
    Edge(Vertex<V, E>* dest, int w, const E& value);
    Edge(const Edge& other);
    Edge(Edge&& other) noexcept;
    Edge& operator=(const Edge& other);
    Edge& operator=(Edge&& other) noexcept;
    ~Edge();
    Vertex<V, E>* destination;
    int weight;
    E data;
};

// Default constructor
/*************************************************
* Purpose: is construtor for edge
*
* Precondtions: NA
*
* Postconditions: NA
*
**************************************************/
template<typename V, typename E>
Edge<V, E>::Edge() : destination(nullptr), weight(0), data(E()) 
{}

// Parameterized constructor
/*************************************************
* Purpose: is construtor for edge
*
* Precondtions: NA
*
* Postconditions: data members are altered
*
**************************************************/
template<typename V, typename E>
Edge<V, E>::Edge(Vertex<V, E>* dest, int w, const E& value) : destination(dest), weight(w), data(value) 
{}

// Copy constructor
/*************************************************
* Purpose: copies data
*
* Precondtions: edge data
*
* Postconditions: data is copied
*
**************************************************/
template<typename V, typename E>
Edge<V, E>::Edge(const Edge& other) : destination(other.destination), weight(other.weight), data(other.data) 
{}

// Move constructor
/*************************************************
* Purpose: moves data
*
* Precondtions: edge data
*
* Postconditions: data is moved
*
**************************************************/
template<typename V, typename E>
Edge<V, E>::Edge(Edge&& other) noexcept : destination(other.destination), weight(other.weight), data(std::move(other.data)) 
{
    other.destination = nullptr;
    other.weight = 0;
}

// Copy assignment operator
/*************************************************
* Purpose: makes a deep copy of edge data
*
* Precondtions: edge data
*
* Postconditions: edge data is deep copied
*
**************************************************/
template<typename V, typename E>
Edge<V, E>& Edge<V, E>::operator=(const Edge& other) 
{
    if (this != &other)
    {
        destination = other.destination;
        weight = other.weight;
        data = other.data;
    }
    return *this;
}

// Move assignment operator
/*************************************************
* Purpose: makes deep copy of move data
*
* Precondtions: edge data
*
* Postconditions: edge data is deep moved on right
*                 hand side
*
**************************************************/
template<typename V, typename E>
Edge<V, E>& Edge<V, E>::operator=(Edge&& other) noexcept 
{
    if (this != &other) 
    {
        destination = other.destination;
        weight = other.weight;
        data = std::move(other.data);
        other.destination = nullptr;
        other.weight = 0;
    }
    return *this;
}

// Destructor
/*************************************************
* Purpose: destroys edge data
*
* Precondtions: edge data
*
* Postconditions: data is deleted
*
**************************************************/
template<typename V, typename E>
Edge<V, E>::~Edge() 
{
    destination = nullptr;
}