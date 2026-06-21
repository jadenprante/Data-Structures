/*************************************************
* Author:          Jaden Prante
* File Name:       Graph.h
* Date Created:    May 25th 2025
* Modifications:   May 26th 2025
*                  Finished Traversal Methods
*
* Class: Graph
*
* Purpose: This class creates a graph
*
*
* Manager Functions:
*       Graph() - Default Constructor
*       Graph(const Graph& other) - Copy Constructor
*       Graph(Graph&& other) noexcept - Move Constructor
*       Graph& operator=(const Graph& other) - Copy Assignment Operator
*       Graph& operator=(Graph&& other) noexcept - Move Assignment Operator
*       ~Graph() - Deconstructor
*
* Methods:
*       void InsertVertex(const V& data);
*       void DeleteVertex(const V& data);
*       void InsertEdge(const V& from, const V& to, const E& edgeData, int weight);
*       void DeleteEdge(const V& from, const V& to);
*       void DepthFirst(void (*visit)(V data));
*       void BreadthFirst(void (*visit)(V data));
*       bool isEmpty() const;
*       Vertex<V, E>* FindVertex(const V& data);
*
**************************************************/

#pragma once;

#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <vector>
#include "Vertex.h"
#include "Edge.h"

using std::list;
using std::vector;
using std::queue;
using std::stack;


template <typename V, typename E>
class Graph {
public:
    Graph();
    Graph(const Graph& other);
    Graph(Graph&& other) noexcept;
    Graph& operator=(const Graph& other);
    Graph& operator=(Graph&& other) noexcept;
    ~Graph();
    void InsertVertex(const V& data);
    void DeleteVertex(const V& data);
    void InsertEdge(const V& from, const V& to, const E& edgeData, int weight);
    void DeleteEdge(const V& from, const V& to);
    void DepthFirst(void (*visit)(V data));
    void BreadthFirst(void (*visit)(V data));
    bool isEmpty() const;
private:
    list<Vertex<V, E>> vertices;
    Vertex<V, E>* FindVertex(const V& data);
};


// Constructor
/*************************************************
* Purpose: is construtor for graph
*
* Precondtions: NA
*
* Postconditions: NA
*
**************************************************/
template<typename V, typename E>
Graph<V, E>::Graph() 
{}

// Copy Constructor
/*************************************************
* Purpose: copies data
*
* Precondtions: graph data
*
* Postconditions: data is copied
*
**************************************************/
template<typename V, typename E>
Graph<V, E>::Graph(const Graph& other) : vertices(other.vertices)
{
    for (typename list<Vertex<V, E>>::iterator it = vertices.begin(); it != vertices.end(); it++)
    {
        Vertex<V, E>& vertexTemp = *it;
        list<Edge<V, E>>* tempList = &vertexTemp.edges;
        for (typename list<Edge<V, E>>::iterator edgeIt = tempList->begin(); edgeIt != tempList->end(); edgeIt++)
        {
            bool found = false;
            Edge<V, E>& edge_temp = *edgeIt;
            for (typename list<Vertex<V, E>>::iterator iter = vertices.begin(); it != vertices.end() && found != true; iter++)
            {
                Vertex<V, E>& temp = *iter;
                if (temp.data == edge_temp.destination->data)
                {
                    edge_temp.destination = &temp;
                    found = true;
                }
            }
        }
    }
}

// Move Constructor
/*************************************************
* Purpose: moves data
*
* Precondtions: graph data
*
* Postconditions: data is moved
*
**************************************************/
template<typename V, typename E>
Graph<V, E>::Graph(Graph&& other) noexcept 
{
    vertices = std::move(other.vertices);
}

// Copy Assignment Operator
/*************************************************
* Purpose: makes a deep copy of graph data
*
* Precondtions: graph data
*
* Postconditions: graph data is deep copied
*
**************************************************/
template<typename V, typename E>
Graph<V, E>& Graph<V, E>::operator=(const Graph& other) 
{
    if (this != &other)
    {
        vertices.clear();
        for (typename list<Vertex<V, E>>::iterator it = vertices.begin(); it != vertices.end(); it++)
        {
            Vertex<V, E>& vertexTemp = *it;
            list<Edge<V, E>>* tempList = &vertexTemp.edges;
            for (typename list<Edge<V, E>>::iterator edgeIt = tempList->begin(); edgeIt != tempList->end(); edgeIt++)
            {
                bool found = false;
                Edge<V, E>& edge_temp = *edgeIt;
                for (typename list<Vertex<V, E>>::iterator iter = vertices.begin(); it != vertices.end() && found != true; iter++)
                {
                    Vertex<V, E>& temp = *iter;
                    if (temp.data == edge_temp.destination->data)
                    {
                        edge_temp.destination = &temp;
                        found = true;
                    }
                }
            }
        }
    }
    return *this;
}

// Move Assignment Operator
/*************************************************
* Purpose: makes deep copy of move data
*
* Precondtions: graph data
*
* Postconditions: graph data is deep moved on right
*                 hand side
*
**************************************************/
template<typename V, typename E>
Graph<V, E>& Graph<V, E>::operator=(Graph&& other) noexcept 
{
    if (this != &other) 
    {
        vertices = std::move(other.vertices);
    }
    return *this;
}

// Destructor
/*************************************************
* Purpose: destroys graph data
*
* Precondtions: graph data
*
* Postconditions: data is deleted
*
**************************************************/
template<typename V, typename E>
Graph<V, E>::~Graph() 
{
    vertices.clear();
}

// Insert Vertex Function
/*************************************************
* Purpose: inserts vertex into graph
*
* Precondtions: vertecie contents
*
* Postconditions: vertex is added
*
**************************************************/
template<typename V, typename E>
void Graph<V, E>::InsertVertex(const V& data) 
{
    vertices.push_back(Vertex<V, E>(data));
}

// Delete Vertex Function
/*************************************************
* Purpose: deletes vertex into graph
*
* Precondtions: vertecie contents
*
* Postconditions: vertex is removed
*
**************************************************/
template<typename V, typename E>
void Graph<V, E>::DeleteVertex(const V& data) 
{
    typename list<Vertex<V, E>>::iterator it = vertices.begin();
    while (it != vertices.end()) 
    {
        bool erased = false;
        if (it->data == data)
        {
            it = vertices.erase(it);
            erased = true;
        }
        if (!erased)
        {
            typename list<Edge<V, E>>::iterator edgeIt = it->edges.begin();
            while (edgeIt != it->edges.end())
            {
                if (edgeIt->destination->data == data)
                {
                    edgeIt = it->edges.erase(edgeIt);
                }
                else 
                {
                    edgeIt++;
                }
            }
            it++;
        }
    }
}


// Insert Edge Function
/*************************************************
* Purpose: addes edge into vertex
*
* Precondtions: edge contents
*
* Postconditions: edge is added
*
**************************************************/
template<typename V, typename E>
void Graph<V, E>::InsertEdge(const V& from, const V& to, const E& edgeData, int weight) 
{
    Vertex<V, E>* vFrom = FindVertex(from);
    Vertex<V, E>* vTo = FindVertex(to);
    if (vFrom != nullptr && vTo != nullptr) 
    {
        vFrom->edges.push_back(Edge<V, E>(vTo, weight, edgeData));
    }
}

// Delete Edge Function
/*************************************************
* Purpose: deletes edge into vertex
*
* Precondtions: edge contents
*
* Postconditions: edge is removed
*
**************************************************/
template<typename V, typename E>
void Graph<V, E>::DeleteEdge(const V& from, const V& to) 
{
    Vertex<V, E>* vFrom = FindVertex(from);
    if (vFrom) 
    {
        typename list<Edge<V, E>>::iterator it = vFrom->edges.begin();
        while (it != vFrom->edges.end()) 
        {
            if (it->destination->data == to) 
            {
                it = vFrom->edges.erase(it);
            }
            else 
            {
                it++;
            }
        }
    }
}

// Depth Traverse Function
/*************************************************
* Purpose: traverses graph via depthfirst
*
* Precondtions: graph contents
*
* Postconditions: travereses through graph
*
**************************************************/
template<typename V, typename E>
void Graph<V, E>::DepthFirst(void (*visit)(V data)) 
{
    if (vertices.empty())
    {
        throw Exception("Graph is empty");
    }
    stack<Vertex<V, E>*> s;
    list<Vertex<V, E>*> visited;
    for (typename list<Vertex<V, E>>::iterator it = vertices.begin(); it != vertices.end(); ++it) 
    {
        bool alreadyVisited = false;
        for (Vertex<V, E>* v : visited) 
        {
            alreadyVisited = alreadyVisited || (v == &(*it));
        }
        if (!alreadyVisited) 
        {
            s.push(&(*it));
            while (!s.empty()) 
            {
                Vertex<V, E>* v = s.top();
                s.pop();
                bool visitedBefore = false;
                for (Vertex<V, E>* visitedV : visited) 
                {
                    visitedBefore = visitedBefore || (visitedV == v);
                }
                if (!visitedBefore) 
                {
                    visit(v->data);
                    visited.push_back(v);
                    for (typename list<Edge<V, E>>::iterator edgeIt = v->edges.begin(); edgeIt != v->edges.end(); ++edgeIt)
                    {
                        s.push(edgeIt->destination);
                    }
                }
            }
        }
    }
}


// Breadth First Traverse Function
/*************************************************
* Purpose: traverses graph via breadthfirst
*
* Precondtions: graph contents
*
* Postconditions: travereses through graph
*
**************************************************/
template<typename V, typename E>
void Graph<V, E>::BreadthFirst(void (*visit)(V data)) {
    if (vertices.empty())
    {
        throw Exception("Graph is empty");
    }
    queue<Vertex<V, E>*> q;
    list<Vertex<V, E>*> visited;
    for (typename list<Vertex<V, E>>::iterator it = vertices.begin(); it != vertices.end(); ++it) 
    {
        bool alreadyVisited = false;
        for (Vertex<V, E>* v : visited) 
        {
            alreadyVisited = alreadyVisited || (v == &(*it));
        }
        if (!alreadyVisited) 
        {
            q.push(&(*it));
            while (!q.empty()) 
            {
                Vertex<V, E>* v = q.front();
                q.pop();
                bool visitedBefore = false;
                for (Vertex<V, E>* visitedV : visited)
                {
                    visitedBefore = visitedBefore || (visitedV == v);
                }
                if (!visitedBefore) 
                {
                    visit(v->data);
                    visited.push_back(v);
                    for (typename list<Edge<V, E>>::iterator edgeIt = v->edges.begin(); edgeIt != v->edges.end(); ++edgeIt)
                    {
                        q.push(edgeIt->destination);
                    }
                }
            }
        }
    }
}


// isEmpty Function
/*************************************************
* Purpose: tests if graph is empty
*
* Precondtions: vertices data
*
* Postconditions: graph is empty
*
**************************************************/
template<typename V, typename E>
bool Graph<V, E>::isEmpty() const 
{
    return vertices.empty();
}

// Find Vertex Function
/*************************************************
* Purpose: finds vertex in graph
*
* Precondtions: vertex contents
*
* Postconditions: vertex is found
*
**************************************************/
template<typename V, typename E>
Vertex<V, E>* Graph<V, E>::FindVertex(const V& data) 
{
    for (typename list<Vertex<V, E>>::iterator it = vertices.begin(); it != vertices.end(); it++)
    {
        if (it->data == data) 
        {
            return &(*it);
        }
    }
    return nullptr;
}

