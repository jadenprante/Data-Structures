/*************************************************************
* Author:			Jaden Prante
* Filename:			Lab10.cpp
* Date Created:		May 2nd 2025
* Modifications:	May 11th 2025
*					Uses TA Test code
*
* 
* Lab/Assignment: Lab 10 - Binary Search Tree
*
* Overview:
* This lab goes Binary search trees
*
* Input:
* The input is 15 names and these arrays will be used to run a series of tests
*
* Output:
* The output will be the result of the ran test, it will output
* either a pass or fail result
**************************************************************/

#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a funtion pointer type

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;

#include <crtdbg.h>
#include <conio.h>
#include "BSTree.h"

int traversal_array[10];
int traversal_count = 0;

const int DATA[] = { 4, 7, 9, 0, 2, 1, 5, 3, 8, 6 };
const int NUM_INTS = 10;

const int IN_ORDER_DATA[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const int PRE_ORDER_DATA[] = { 4, 0, 2, 1, 3, 7, 5, 6, 9, 8 };
const int POST_ORDER_DATA[] = { 1, 3, 2, 0, 6, 5, 8, 9, 7, 4 };
const int BREADTH_FIRST[] = { 4, 0, 7, 2, 5, 9, 1, 3, 6, 8 };
const int BLANK_ARRAY[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const int DELETE_6[] = { 0, 1, 2, 3, 4, 5, 7, 8, 9 };


// Test function declaration
bool test_in_order_traversal();
bool test_pre_order_traversal();
bool test_post_order_traversal();
bool test_breadth_first_traversal();
bool test_copy_ctor();
bool test_op_eql();
bool test_purge();
bool test_valid_delete();
bool test_invalid_delete();


// Array of test functions
FunctionPointer test_functions[] = { test_in_order_traversal,
test_pre_order_traversal,
test_post_order_traversal,
test_breadth_first_traversal,
test_copy_ctor,
test_op_eql,
test_purge,
test_valid_delete,
test_invalid_delete };

// Function that is passed to node for visitor pattern
template <typename T>
void add_data(T node)
{
	traversal_array[traversal_count++] = node;
}

int main()
{
	bool tests_passed;

	// Run the test functions
	for (FunctionPointer func : test_functions)
	{
		if (func())
		{
			cout << "passed\n";
		}
		else
		{
			cout << "***** failed *****\n";
		}
	}

	cout << "\nPress Any Key to Exit";
	cin.get();
}

bool test_in_order_traversal()
{
	memset(traversal_array, 0, sizeof(traversal_array));
	BSTree<int> test_tree;
	bool pass = true;

	for (int i = 0; i < NUM_INTS; i++)
	{
		test_tree.Insert(DATA[i]);
	}

	test_tree.InOrder(add_data);

	for (int i = 0; i < NUM_INTS && pass; i++)
	{
		if (traversal_array[i] != IN_ORDER_DATA[i])
			pass = false;
	}

	traversal_count = 0;

	cout << "InOrder traversal test ";

	return pass;
}

bool test_pre_order_traversal()
{
	memset(traversal_array, 0, sizeof(traversal_array));
	BSTree<int> test_tree;
	bool pass = true;

	for (int i = 0; i < NUM_INTS; i++)
	{
		test_tree.Insert(DATA[i]);
	}

	test_tree.PreOrder(add_data);

	for (int i = 0; i < NUM_INTS && pass; i++)
	{
		if (traversal_array[i] != PRE_ORDER_DATA[i])
			pass = false;
	}

	traversal_count = 0;

	cout << "Pre order traversal test ";

	return pass;
}

bool test_post_order_traversal()
{
	memset(traversal_array, 0, sizeof(traversal_array));
	BSTree<int> test_tree;
	bool pass = true;

	for (int i = 0; i < NUM_INTS; i++)
	{
		test_tree.Insert(DATA[i]);
	}

	test_tree.PostOrder(add_data);

	for (int i = 0; i < NUM_INTS && pass; i++)
	{
		if (traversal_array[i] != POST_ORDER_DATA[i])
			pass = false;
	}

	traversal_count = 0;

	cout << "Post order traversal test ";

	return pass;
}

bool test_breadth_first_traversal()
{
	memset(traversal_array, 0, sizeof(traversal_array));
	BSTree<int> test_tree;
	bool pass = true;

	for (int i = 0; i < NUM_INTS; i++)
	{
		test_tree.Insert(DATA[i]);
	}

	test_tree.BreadthFirst(add_data);

	for (int i = 0; i < NUM_INTS && pass; i++)
	{
		if (traversal_array[i] != BREADTH_FIRST[i])
			pass = false;
	}

	traversal_count = 0;

	cout << "Breadth first traversal test ";

	return pass;
}

bool test_copy_ctor()
{
	memset(traversal_array, 0, sizeof(traversal_array));
	BSTree<int> test_tree;
	bool pass = true;

	for (int i = 0; i < NUM_INTS; i++)
	{
		test_tree.Insert(DATA[i]);
	}

	BSTree<int> cpy_tree(test_tree);

	cpy_tree.InOrder(add_data);

	for (int i = 0; i < NUM_INTS && pass; i++)
	{
		if (traversal_array[i] != IN_ORDER_DATA[i])
			pass = false;
	}

	traversal_count = 0;

	cout << "Copy ctor test ";

	return pass;
}

bool test_op_eql()
{
	memset(traversal_array, 0, sizeof(traversal_array));
	BSTree<int> test_tree;
	BSTree<int> cpy_tree;
	bool pass = true;

	for (int i = 0; i < NUM_INTS; i++)
	{
		test_tree.Insert(DATA[i]);
	}

	cpy_tree = test_tree;

	cpy_tree.InOrder(add_data);

	for (int i = 0; i < NUM_INTS && pass; i++)
	{
		if (traversal_array[i] != IN_ORDER_DATA[i])
			pass = false;
	}

	traversal_count = 0;

	cout << "Op eql test ";

	return pass;
}

bool test_purge()
{
	memset(traversal_array, 0, sizeof(traversal_array));
	BSTree<int> test_tree;
	bool pass = true;

	for (int i = 0; i < NUM_INTS; i++)
	{
		test_tree.Insert(DATA[i]);
	}

	test_tree.Purge();
	test_tree.InOrder(add_data);

	for (int i = 0; i < NUM_INTS && pass; i++)
	{
		if (traversal_array[i] != BLANK_ARRAY[i])
			pass = false;
	}

	traversal_count = 0;

	cout << "Purge test ";

	return pass;
}

bool test_valid_delete()
{
	memset(traversal_array, 0, sizeof(traversal_array));
	BSTree<int> test_tree;
	bool pass = true;

	for (int i = 0; i < NUM_INTS; i++)
	{
		test_tree.Insert(DATA[i]);
	}

	test_tree.Delete(6);
	test_tree.InOrder(add_data);

	for (int i = 0; i < NUM_INTS && pass; i++)
	{
		if (traversal_array[i] != DELETE_6[i])
			pass = false;
	}

	traversal_count = 0;

	cout << "Valid delete test ";

	return pass;
}

bool test_invalid_delete()
{
	memset(traversal_array, 0, sizeof(traversal_array));
	BSTree<int> test_tree;
	bool pass = false;

	for (int i = 0; i < NUM_INTS; i++)
	{
		test_tree.Insert(DATA[i]);
	}

	try
	{
		test_tree.Delete(100);
	}
	catch (Exception msg)
	{
		pass = true;
	}

	cout << "Invalid delete test ";

	return pass;
};
