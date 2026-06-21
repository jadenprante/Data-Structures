/*************************************************************
* Author:			Jaden Prante
* Filename:			Lab14.cpp
* Date Created:		Mar 7th 2025
* Modifications:	NA
*
* *
* Lab/Assignment: Lab 14 - Dijkstra's Algorthim
*
* Overview:
* This lab goes over Dijkstra's Algorthim 
*
* Input:
* You will be asked to input a starting location and an ending location 
* (Enter Locations from the assign13.txt file)
*
* Output:
* The output will be The Shortest Path between the two locations
* followed by the miles it will take to get there, and the time in 
* hours and minutes to get there
**************************************************************/


#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include "Exception.h"
#include "Graph.h"

using std::ifstream;
using std::stack;
using std::string;
using std::vector;

using std::printf;
using std::cout;
using std::cin;
using std::endl;

void Display(const string& data);
void DataInput(Graph<string, string>& graph);
void Dijkstra(const string& from, const string& to, Graph<string, string>& graph);

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Graph<string, string> graph;
    DataInput(graph);
    string from, to;
    bool turn = true;
    cout << "Type 'Exit' to leave the program." << endl;
    while (turn)
    {
        cout << "Enter starting location: ";
        getline(cin, from);
        if (from == "Exit" || to == "Exit")
        {
            turn = false;
        }
        else
        {
            cout << "Enter destination: ";
            getline(cin, to);
            if (from == "Exit" || to == "Exit")
            {
                turn = false;
            }
            else
            {
                try
                {
                    Dijkstra(from, to, graph);
                }
                catch(Exception)
                {
                }
            }
        }
    }
    return 0;
}

// Display method
/*************************************************
* Purpose: is display method
*
* Precondtions: Dijkstra contents
*
* Postconditions: output is displayed
*
**************************************************/
void Display(const string& data)
{
    cout << data << endl;
}

// DataInput Function
/*************************************************
* Purpose: Detects data input
*
* Precondtions: Dijkstra contents and file contents
*
* Postconditions: data is inputed
*
**************************************************/
void DataInput(Graph<string, string>& graph) 
{
    ifstream fin("assign13.txt");
    if (!fin) 
    {
        throw Exception("Unable to open file: assign13.txt");
    }
    string from, to, edge, weightString;
    int weight;
    while (getline(fin, from, ',') && getline(fin, to, ',') && getline(fin, edge, ',') && getline(fin, weightString, '\n'))
    {
        weight = stoi(weightString); 
        graph.InsertVertex(from);
        graph.InsertVertex(to);
        graph.InsertEdge(from, to, edge, weight);
        graph.InsertEdge(to, from, edge, weight);  
    }
    fin.close();
}

// Dijkstra's Algorthim
/*************************************************
* Purpose: Algorith to find shortest path between locations
*
* Precondtions: Dijkstra contents and file contents
*
* Postconditions: will output shortest path
*
**************************************************/
void Dijkstra(const string& from, const string& to, Graph<string, string>& graph) 
{
    stack<string> path_stack;
    vector<Vertex<string, string>*> vertices;
    graph.SetVectors(vertices);
    if (vertices.empty()) 
    {
        cout << "Error: Graph is empty!\n";
        throw Exception("Graph is empty");
    }
    vector<int> distances(vertices.size(), -1);
    vector<string> predecessors(vertices.size(), "");
    int startIndex = -1;
    bool found = false;
    for (size_t i = 0; i < vertices.size() && !found; i++) 
    {
        if (vertices[i]->GetDataVertex() == from) 
        {
            startIndex = static_cast<int>(i);
            found = true;
        }
    }
    if (!found) 
    {
        cout << "Error: Starting location not found!\n";
        throw Exception("No Starting Location");
    }
    distances[startIndex] = 0;
    bool processedAll = false;
    while (!processedAll) {
        int currentIndex = -1;
        int minDistance = -1;
        for (size_t i = 0; i < vertices.size(); i++) {
            if (!vertices[i]->GetProcessed() && distances[i] != -1) 
            {
                if (minDistance == -1 || distances[i] < minDistance) 
                {
                    minDistance = distances[i];
                    currentIndex = static_cast<int>(i);
                }
            }
        }
        if (currentIndex == -1) 
        {
            processedAll = true;
        }
        else 
        {
            vertices[currentIndex]->SetProcessed(true);
            list<Edge<string, string>> edges = vertices[currentIndex]->GetEdge();
            typename list<Edge<string, string>>::iterator it;
            for (it = edges.begin(); it != edges.end(); it++) 
            {
                Edge<string, string>& edge = *it;
                Vertex<string, string>* dest = edge.GetDestination();
                int destIndex = -1;
                typename vector<Vertex<string, string>*>::iterator vIt;
                for (vIt = vertices.begin(); vIt != vertices.end() && destIndex == -1; vIt++) 
                {
                    if ((*vIt)->GetDataVertex() == dest->GetDataVertex()) 
                    {
                        destIndex = static_cast<int>(distance(vertices.begin(), vIt));
                    }
                }
                if (destIndex != -1 && !vertices[destIndex]->GetProcessed()) 
                {
                    int newDist = distances[currentIndex] + edge.GetWeight();
                    if (distances[destIndex] == -1 || newDist < distances[destIndex]) 
                    {
                        distances[destIndex] = newDist;
                        predecessors[destIndex] = vertices[currentIndex]->GetDataVertex();
                    }
                }
            }
            processedAll = true;
            for (size_t i = 0; i < vertices.size(); i++) 
            {
                if (!vertices[i]->GetProcessed())
                {
                    processedAll = false;
                }
            }
        }
    }
    for (size_t i = 0; i < vertices.size(); i++) 
    {
        vertices[i]->SetProcessed(false);
    }
    int endIndex = -1;
    found = false;
    for (size_t i = 0; i < vertices.size() && !found; i++) 
    {
        if (vertices[i]->GetDataVertex() == to) 
        {
            endIndex = static_cast<int>(i);
            found = true;
        }
    }
    if (!found || distances[endIndex] == -1)
    {
        cout << "Error: No path found from " << from << " to " << to << ".\n";
        throw Exception("Inaccurate path");
    }
    int totalDistance = distances[endIndex];
    string step = to;
    while (!step.empty()) 
    {
        path_stack.push(step);
        found = false;
        for (size_t i = 0; i < vertices.size() && !found; i++) 
        {
            if (vertices[i]->GetDataVertex() == step) 
            {
                step = predecessors[i];
                found = true;
            }
        }
    }
    stack<string> path_stack2 = path_stack;
    float minutes = 0;
    while (!path_stack.empty()) 
    {
        string current = path_stack.top();
        path_stack.pop();
        if (!path_stack.empty()) 
        {
            string next = path_stack.top();
            typename vector<Vertex<string, string>*>::iterator vIt;
            for (vIt = vertices.begin(); vIt != vertices.end(); vIt++) 
            {
                if ((*vIt)->GetDataVertex() == current) 
                {
                    list<Edge<string, string>> edges = (*vIt)->GetEdge();
                    typename list<Edge<string, string>>::iterator edgeIt;
                    found = false;
                    for (edgeIt = edges.begin(); edgeIt != edges.end() && !found; edgeIt++) 
                    {
                        if (edgeIt->GetDestination()->GetDataVertex() == next) 
                        {
                            float speed = (edgeIt->GetData() == "I-5") ? 65 : 55;
                            minutes += (edgeIt->GetWeight() * 60) / speed;
                            found = true;
                        }
                    }
                }
            }
        }
    }
    int hours = minutes / 60;
    minutes = floor(minutes - (hours * 60));
    cout << "\nShortest Path from " << from << " to " << to << ":\n";
    while (!path_stack2.empty()) 
    {
        cout << path_stack2.top();
        path_stack2.pop();
        if (!path_stack2.empty()) 
        {
            cout << " -> ";
        }
    }
    cout << endl;
    cout << "\nTotal Distance: " << totalDistance << " miles";
    cout << "\nEstimated Time: " << hours << " hrs " << minutes << " mins\n";
    cout << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << endl;
}

