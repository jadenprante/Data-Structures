/*************************************************
* Author:          Jaden Prante
* File Name:       Edge.h
* Date Created:    May 26th 2025
* Modifications:   Currently same date
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
class Graph;

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
    Vertex<V, E>* GetDestination() const;
    int GetWeight() const;
    E GetData() const;

private:
    Vertex<V, E>* destination;
    int weight;
    E data;
    friend class Vertex<V, E>;
    friend class Graph<V, E>;
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
Edge<V, E>::Edge(const Edge& other)
    : destination(other.destination), weight(other.weight), data(other.data)
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
Edge<V, E>::~Edge() = default; 

// Getter Functions 
/*************************************************
* Purpose: Get edge data, destinations and weight
*
* Precondtions: data member contents
*
* Postconditions: getters are set
*
**************************************************/
template<typename V, typename E>
Vertex<V, E>* Edge<V, E>::GetDestination() const
{
    return destination;
}

template<typename V, typename E> 
int Edge<V, E>::GetWeight() const
{
    return weight;
}

template<typename V, typename E>  
E Edge<V, E>::GetData() const
{
    return data;
}
