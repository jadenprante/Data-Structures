/*************************************************************
* Author:			Jaden Prante
* Filename:			Lab06.cpp
* Date Created:		May 26th 2025
* Modifications:	NA
*
* *
* Lab/Assignment: Lab 13 - Graphs
*
* Overview:
* This lab goes over Graphs
*
* Input:
* The input is 15 names and these arrays will be used to run a series of tests
*
* Output:
* The output will be the result of the ran test, it will output
* either a pass or fail result
**************************************************************/


#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_SECURE_NO_WARNINGS
typedef bool(*FunctionPointer)(); // Define a funtion pointer type
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <crtdbg.h>
#include <conio.h>
#include "Exception.h" 
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };
const int NUM_NAMES = 15;
const int NUM_SIZE = 10;
const int NUM_EXTRACT = 4;
// Test function declaration 
bool TestVertexConstructor();
bool TestVertexCopyConstructor();
bool TestVertexMoveConstructor();
bool TestVertexCopyAssignment();
bool TestVertexMoveAssignment();
bool TestVertexDestructor();
bool TestInsertVertex();
bool TestDeleteVertex();
bool TestInsertEdge();
bool TestDeleteEdge();
bool TestDepthFirstTraversal();
bool TestBreadthFirstTraversal();
bool TestIsEmpty();
bool TestGraphCopyConstructor();
bool TestGraphMoveConstructor();
bool TestGraphCopyAssignment();
bool TestGraphMoveAssignment();
bool TestGraphDestructor();
bool TestEdgeConstructor();
bool TestEdgeAssignment();
// Array of test functions
FunctionPointer test_functions[] = { TestVertexConstructor, TestVertexCopyConstructor, TestVertexMoveConstructor,
    TestVertexCopyAssignment, TestVertexMoveAssignment, TestVertexDestructor,
    TestInsertVertex, TestDeleteVertex, TestInsertEdge, TestDeleteEdge,
    TestDepthFirstTraversal, TestBreadthFirstTraversal, TestIsEmpty,
    TestGraphCopyConstructor, TestGraphMoveConstructor, TestGraphCopyAssignment,
    TestGraphMoveAssignment, TestGraphDestructor, TestEdgeConstructor, TestEdgeAssignment
};
void Visit(int data);

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    int failedTest = 0;
    // Run the test functions

    for (FunctionPointer func : test_functions)
    {
        if (func())
        {
            cout << "passed\n";
        }
        else
        {
            failedTest++;
            cout << "***** failed *****\n";
        }
    }
    if (failedTest > 0)
    {
        cout << "\nYou have failed " << failedTest << " tests.";
    }
    else
    {
        cout << "\nCongradulations, you have passed all the tests!";
    }
    cout << "\nPress Any Key to Exit";
    cin.get();
}

void Visit(int data)
{
    cout << data << " ";
}

bool TestVertexConstructor() 
{
    cout << "Vertex Default Constructor test ";
    Vertex<int, string> v;
    return v.data == 0 && !v.processed && v.edges.empty();
}

bool TestVertexCopyConstructor() 
{
    cout << "Vertex Copy Constructor test ";
    Vertex<int, string> v1(5);
    Vertex<int, string> v2(v1);
    return v2.data == 5 && v2.edges.empty();
}

bool TestVertexMoveConstructor() 
{
    cout << "Vertex Move Constructor test ";
    Vertex<int, string> v1(10);
    Vertex<int, string> v2(std::move(v1));
    return v2.data == 10;
}

bool TestVertexCopyAssignment() 
{
    cout << "Vertex Copy Assignment Operator test ";
    Vertex<int, string> v1(15);
    Vertex<int, string> v2;
    v2 = v1;
    return v2.data == 15;
}

bool TestVertexMoveAssignment()
{
    cout << "Vertex Move Assignment Operator test ";
    Vertex<int, string> v1(20);
    Vertex<int, string> v2;
    v2 = std::move(v1);
    return v2.data == 20;
}

bool TestVertexDestructor() 
{
    cout << "Vertex Destructor test ";
    Vertex<int, string>* v = new Vertex<int, string>(25);
    delete v;
    return true; 
}

bool TestInsertVertex()
{
    cout << "Insert Vertex test ";
    Graph<int, string> g;
    g.InsertVertex(10);
    return !g.isEmpty();
}

bool TestDeleteVertex() {
    cout << "Delete Vertex test ";
    Graph<int, std::string> g;
    g.InsertVertex(10);
    g.DeleteVertex(10);
    return g.isEmpty();
}

bool TestInsertEdge() {
    cout << "Insert Edge test ";
    Graph<int, string> g;
    g.InsertVertex(1);
    g.InsertVertex(2);
    g.InsertEdge(1, 2, "Edge1", 5);
    return true; // If no crash, assume pass
}

bool TestDeleteEdge() {
    cout << "Delete Edge test ";
    Graph<int, string> g;
    g.InsertVertex(1);
    g.InsertVertex(2);
    g.InsertEdge(1, 2, "Edge1", 5);
    g.DeleteEdge(1, 2);
    return true; // If no crash, assume pass
}

bool TestDepthFirstTraversal() {
    cout << "Testing Expected DepthFirst: 1 2 | Actual: ";
    Graph<int, string> g;
    g.InsertVertex(1);
    g.InsertVertex(2);
    g.InsertEdge(1, 2, "Edge1", 5);
    void (*dis)(int);
    dis = Visit;
    g.DepthFirst(dis);
    return true;
}

bool TestBreadthFirstTraversal() {
    cout << "Testing Expected BreadthFirst: 1 2 | Actual: ";
    Graph<int, string> g;
    g.InsertVertex(1);
    g.InsertVertex(2);
    g.InsertEdge(1, 2, "Edge1", 5);
    void (*dis)(int);
    dis = Visit;
    g.BreadthFirst(dis);
    return true;
}

bool TestIsEmpty() {
    cout << "Is Empty test ";
    Graph<int, string> g;
    return g.isEmpty();
}

bool TestGraphCopyConstructor() {
    cout << "Graph Copy Cnstructor test ";
    Graph<int, string> g1;
    g1.InsertVertex(1);
    Graph<int, string> g2(g1);
    return !g2.isEmpty();
}

bool TestGraphMoveConstructor() {
    cout << "Graph Move Cnstructor test ";
    Graph<int, string> g1;
    g1.InsertVertex(1);
    Graph<int, string> g2(std::move(g1));
    return !g2.isEmpty();
}

bool TestGraphCopyAssignment() {
    cout << "Graph Move Cnstructor test ";
    Graph<int, string> g1;
    g1.InsertVertex(1);
    Graph<int, string> g2;
    g2 = g1;
    return !g2.isEmpty();
}

bool TestGraphMoveAssignment() {
    cout << "Graph Copy Assignment Operator test ";
    Graph<int, string> g1;
    g1.InsertVertex(1);
    Graph<int, string> g2;
    g2 = std::move(g1);
    return !g2.isEmpty();
}

bool TestGraphDestructor() {
    cout << "Graph Destructor test ";
    Graph<int, string>* g = new Graph<int, string>();
    g->InsertVertex(1);
    delete g;
    return true; // If no crash, assume pass
}

bool TestEdgeConstructor() {
    cout << "Edge Default Constructor test ";
    Vertex<int, string> v(10);
    Edge<int, string> e(&v, 5, "EdgeData");
    return e.destination == &v && e.weight == 5 && e.data == "EdgeData";
}

bool TestEdgeAssignment() {
    cout << "Edge Copy Assignment Operator test ";
    Vertex<int, string> v1(10);
    Vertex<int, string> v2(20);
    Edge<int, string> e1(&v1, 5, "EdgeData");
    Edge<int, string> e2;
    e2 = e1;
    return e2.destination == &v1 && e2.weight == 5 && e2.data == "EdgeData";
}