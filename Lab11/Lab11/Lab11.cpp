/*************************************************************
* Author:			Jaden Prante
* Filename:			Lab06.cpp
* Date Created:		May 2nd 2025
* Modifications:	NA
*
* 
* Lab/Assignment: Lab 11 - AVL Trees
*
* Overview:
* This lab goes AVL Trees
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
#include "AVLTree.h"  
// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };
const int NUM_NAMES = 15;
const int NUM_SIZE = 10;
const int NUM_EXTRACT = 4;
// Test function declaration
bool TestDefaultConstructor();
bool TestCopyConstructor();
bool TestMoveConstructor();
bool TestCopyAssignment();
bool TestMoveAssignment();
bool TestDestructor();
bool TestInsertSingle();
bool TestInsertMultiple();
bool TestInsertWithBalancing();
bool TestDeleteLeaf();
bool TestDeleteNodeWithOneChild();
bool TestDeleteNodeWithTwoChildren();
bool TestInOrderTraversal();
bool TestPreOrderTraversal();
bool TestPostOrderTraversal();
bool TestBreadthFirstTraversal();
bool TestEmptyTreeHeight();
bool TestSingleNodeHeight();
bool TestBalancedTreeHeight();
bool TestPurge();

// Array of test functions
FunctionPointer test_functions[] = { TestDefaultConstructor, TestCopyConstructor, TestMoveConstructor,
	TestCopyAssignment, TestMoveAssignment, TestDestructor,
	TestInsertSingle, TestInsertMultiple, TestInsertWithBalancing,
	TestDeleteLeaf, TestDeleteNodeWithOneChild, TestDeleteNodeWithTwoChildren,
	TestInOrderTraversal, TestPreOrderTraversal, TestPostOrderTraversal,
	TestBreadthFirstTraversal, TestEmptyTreeHeight, TestSingleNodeHeight,
	TestBalancedTreeHeight, TestPurge
};
int main()
{
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
	return 0;
}

void PrintData(int data) {
    cout << data << " ";
}

bool TestDefaultConstructor() {
    cout << "AVLTree Default Constructor Test ";
    AVLTree<int> tree;
    return tree.Height() == -1; // Empty tree should have height -1
}

bool TestCopyConstructor() {
    cout << "AVLTree Copy Constructor Test ";
    AVLTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    AVLTree<int> copyTree(tree);
    return copyTree.Height() == tree.Height();
}

bool TestMoveConstructor() {
    cout << "AVLTree Move Constructor Test ";
    AVLTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);

    AVLTree<int> movedTree(std::move(tree));
    return movedTree.Height() == 1 && tree.Height() == -1;
}

bool TestCopyAssignment() {
    cout << "AVLTree Copy Assignment Operator Test ";
    AVLTree<int> tree1;
    tree1.Insert(10);
    tree1.Insert(5);
    tree1.Insert(15);
    AVLTree<int> tree2;
    tree2 = tree1;
    return tree2.Height() == tree1.Height();
}

bool TestMoveAssignment() {
    cout << "AVLTree Move Assignment Operator Test ";
    AVLTree<int> tree1;
    tree1.Insert(10);
    tree1.Insert(5);
    tree1.Insert(15);
    AVLTree<int> tree2;
    tree2 = std::move(tree1);
    return tree2.Height() == 1 && tree1.Height() == -1;
}

bool TestDestructor() {
    cout << "AVLTree Destructor Test ";
    AVLTree<int>* tree = new AVLTree<int>();
    tree->Insert(10);
    tree->Insert(5);
    tree->Insert(15);
    delete tree; // Should not cause a memory leak
    return true; // No runtime errors indicate success
}

bool TestInsertSingle() {
    cout << "AVLTree Single Insert Test ";
    AVLTree<int> tree;
    tree.Insert(10);
    return tree.Height() == 0;
}

bool TestInsertMultiple() {
    cout << "AVLTree Multiple Insert Test ";
    AVLTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    return tree.Height() == 1;
}

bool TestInsertWithBalancing() {
    cout << "AVLTree Insert WIth Balancing Test ";
    AVLTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(1); // Unbalanced, should rotate right
    return tree.Height() == 1;
}

bool TestDeleteLeaf() {
    cout << "AVLTree Delete Leaf Test ";
    AVLTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Delete(5);
    return tree.Height() == 0;
}

bool TestDeleteNodeWithOneChild() {
    cout << "AVLTree Delete Node With One Child Test ";
    AVLTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(1);
    tree.Delete(5);
    return tree.Height() == 1;
}

bool TestDeleteNodeWithTwoChildren() {
    cout << "AVLTree Delete Node With Two Children Test ";
    AVLTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    tree.Delete(10);
    return tree.Height() == 1;
}

bool TestInOrderTraversal() {
    AVLTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    cout << "Testing Expected InOrder: 5 10 15 | Got: ";
    tree.InOrder(PrintData);
    return true;
}

bool TestPreOrderTraversal() {
    AVLTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    cout << "Testing Expected PreOrder: 10 5 15 | Got: ";
    tree.PreOrder(PrintData);
    return true;
}

bool TestPostOrderTraversal() {
    AVLTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    cout << "Testing Expected PostOrder: 5 15 10 | Got: ";
    tree.PostOrder(PrintData);
    return true;
}

bool TestBreadthFirstTraversal() {
    AVLTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    cout << "Testing Expected BreadthFirst: 10 5 15 | Got: ";
    tree.BreadthFirst(PrintData);
    return true;
}

bool TestEmptyTreeHeight() {
    cout << "AVLTree Empty Tree Height Test ";
    AVLTree<int> tree;
    return tree.Height() == -1;
}

bool TestSingleNodeHeight() {
    cout << "AVLTree Single Node Height Test ";
    AVLTree<int> tree;
    tree.Insert(10);
    return tree.Height() == 0;
}

bool TestBalancedTreeHeight() {
    cout << "AVLTree Balanced Tree Height Test ";
    AVLTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    tree.Insert(3);
    tree.Insert(7);
    tree.Insert(12);
    tree.Insert(18);
    return tree.Height() == 2;
}

bool TestPurge() {
    cout << "AVLTree Purge Test ";
    AVLTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    tree.Purge();
    return tree.Height() == -1;
}


