/*************************************************************
* Author:			Jaden Prante
* Filename:			Lab06.cpp
* Date Created:		Apr 19th 2025
* Modifications:	NA
*
* *\
* Lab/Assignment: Lab 6 – Stack Array Implementation
*
* Overview:
* This lab assignment deals with the uses of 2D arrays
* and revolving arounf their rows nd columns
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
#include "Stack.h"
#include "Exception.h"

const int TEST_DATA[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

const char* STATES[] = { "Alabama", "Alaska", "Arizona", "Arkansas", "California",
"Colorado", "Connecticut", "Delaware", "Florida", "Georgia", "Hawaii", "Idaho",
"Illinois", "Indiana", "Iowa", "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland",
"Massachusetts", "Michigan", "Minnesota", "Mississippi", "Missouri", "Montana",
"Nebraska", "Nevada", "New Hampshire", "New Jersey", "New Mexico", "New York",
"North Carolina", "North Dakota", "Ohio", "Oklahoma", "Oregon" };

const int NUM_STATES = 36;
const int NUM_INTS = 10;

// Test function declaration
bool test_Push_full_list();
bool test_Pop_empty_list();
bool test_Peek_empty_list();
bool test_Push_Pop_data();
bool test_copy_ctor();
bool test_op_eql();
bool test_is_empty();
bool test_is_full();
bool test_Peek();
bool test_size_getter();
bool test_Push_full_list_complex();
bool test_Pop_empty_list_complex();
bool test_Peek_empty_list_complex();
bool test_Push_Pop_data_complex();
bool test_copy_ctor_complex();
bool test_op_eql_complex();
bool test_is_empty_complex();
bool test_is_full_complex();
bool test_Peek_complex();
bool test_size_getter_complex();

// Array of test functions
FunctionPointer test_functions[] = { test_Push_full_list, test_Pop_empty_list, test_Peek_empty_list,
test_Push_Pop_data, test_copy_ctor, test_op_eql, test_is_empty, test_is_full, test_Peek,
test_size_getter, test_Push_full_list_complex, test_Pop_empty_list_complex,
test_Peek_empty_list_complex, test_Push_Pop_data_complex, test_copy_ctor_complex,
test_op_eql, test_is_empty_complex, test_is_full_complex, test_Peek_complex,
test_size_getter_complex };

int main()
{
	bool tests_passed;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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

bool test_Push_full_list()
{
	bool pass = false;
	Stack<int> test_stack;
	try
	{
		test_stack.Push(1);
	}
	catch (Exception& except)
	{
		pass = true;
	}
	cout << "Push full list test ";
	return pass;
}

bool test_Pop_empty_list()
{
	bool pass = false;
	Stack<int> test_stack;
	try
	{
		test_stack.Pop();
	}
	catch (Exception& except)
	{
		pass = true;
	}
	cout << "Pop empty list test ";
	return pass;
}

bool test_Peek_empty_list()
{
	bool pass = false;

	Stack<int> test_stack;

	try
	{
		test_stack.Peek();
	}
	catch (Exception& except)
	{
		pass = true;
	}

	cout << "Peek empty list test ";

	return pass;
}

bool test_Push_Pop_data()
{
	bool pass = true;
	int size = 10;
	Stack<int> test_stack;
	test_stack.setSize(size);
	for (int i = 0; i < NUM_INTS; ++i)
		test_stack.Push(TEST_DATA[i]);

	for (int i = NUM_INTS - 1; i > 0; --i)
	{
		if (test_stack.Pop() != TEST_DATA[i])
			pass = false;
	}

	cout << "Push Pop test ";

	return pass;
}

bool test_copy_ctor()
{
	bool pass = true;
	int size = 10;

	Stack<int> test_stack;
	test_stack.setSize(size);


	for (int i = 0; i < NUM_INTS; ++i)
		test_stack.Push(TEST_DATA[i]);


	Stack<int> cpy_test_stack(test_stack);

	for (int i = NUM_INTS - 1; i > 0; --i)
	{
		if (cpy_test_stack.Pop() != TEST_DATA[i])
			pass = false;
	}

	cout << "Copy ctor test ";

	return pass;
}

bool test_op_eql()
{
	bool pass = true;
	int size = 10;

	Stack<int> test_stack;
	test_stack.setSize(size);


	for (int i = 0; i < NUM_INTS; ++i)
		test_stack.Push(TEST_DATA[i]);


	Stack<int> cpy_test_stack;

	cpy_test_stack = test_stack;

	for (int i = NUM_INTS - 1; i > 0; --i)
	{
		if (cpy_test_stack.Pop() != TEST_DATA[i])
			pass = false;
	}

	cout << "Op eql test ";

	return pass;
}

bool test_is_empty()
{
	bool pass = true;
	int size = 10;

	Stack<int> test_stack;
	test_stack.setSize(size);

	for (int i = 0; i < NUM_INTS; ++i)
		test_stack.Push(TEST_DATA[i]);

	while (!test_stack.isEmpty())
		test_stack.Pop();

	pass = test_stack.isEmpty(); // True will pass test

	cout << "Is empty test ";

	return pass;
}

bool test_is_full()
{
	bool pass = true;
	int size = 5;
	int num = 0;

	Stack<int> test_stack;
	test_stack.setSize(size);


	while (!test_stack.isFull())
		test_stack.Push(TEST_DATA[num++]);

	pass = test_stack.isFull(); // True will pass test

	cout << "Is full test ";

	return pass;
}

bool test_Peek()
{
	bool pass = true;
	int size = 1;
	int num = 0;
	int Push_value = 15;
	Stack<int> test_stack;
	test_stack.setSize(size);
	test_stack.Push(Push_value);
	if (test_stack.Peek() != Push_value)
		pass = false;

	// If Peek returned true value, test to make sure that Peek didn't remove
	// the stack element (an exception would be called if Peek removed element).
	if (pass)
	{
		try
		{
			test_stack.Pop();
		}
		catch (Exception& except)
		{
			pass = false;
		}
	}


	cout << "Peek test ";

	return pass;
}

bool test_size_getter()
{
	bool pass = true;
	int size = 5;
	int num = 0;

	Stack<int> test_stack;
	test_stack.setSize(size);

	while (!test_stack.isFull() && pass)
	{
		test_stack.Push(TEST_DATA[num++]);

		if (test_stack.getSize() != num)
			pass = false;
	}

	cout << "Size getter test ";

	return pass;
}

bool test_Push_full_list_complex()
{
	bool pass = false;

	Stack<string> test_stack;

	try
	{
		test_stack.Push("test");
	}
	catch (Exception& except)
	{
		pass = true;
	}

	cout << "Push full list test complex ";

	return pass;
}

bool test_Pop_empty_list_complex()
{
	bool pass = false;

	Stack<string> test_stack;

	try
	{
		test_stack.Pop();
	}
	catch (Exception& except)
	{
		pass = true;
	}

	cout << "Pop empty list test complex ";

	return pass;
}

bool test_Peek_empty_list_complex()
{
	bool pass = false;

	Stack<string> test_stack;

	try
	{
		test_stack.Peek();
	}
	catch (Exception& except)
	{
		pass = true;
	}

	cout << "Peek empty list test complex ";

	return pass;
}

bool test_Push_Pop_data_complex()
{
	bool pass = true;
	int size = 10;

	Stack<string> test_stack;
	test_stack.setSize(size);

	for (int i = 0; i < size; ++i)
		test_stack.Push(STATES[i]);

	for (int i = size - 1; i > 0; --i)
	{
		if (test_stack.Pop() != STATES[i])
			pass = false;
	}

	cout << "Push Pop test complex ";

	return pass;
}

bool test_copy_ctor_complex()
{
	bool pass = true;
	int size = 10;

	Stack<string> test_stack;
	test_stack.setSize(size);

	for (int i = 0; i < size; ++i)
		test_stack.Push(STATES[i]);


	Stack<string> cpy_test_stack(test_stack);

	for (int i = size - 1; i > 0; --i)
	{
		if (cpy_test_stack.Pop() != STATES[i])
			pass = false;
	}

	cout << "Copy ctor test complex";

	return pass;
}

bool test_op_eql_complex()
{
	bool pass = true;
	int size = 10;

	Stack<string> test_stack;
	test_stack.setSize(size);


	for (int i = 0; i < size; ++i)
		test_stack.Push(STATES[i]);


	Stack<string> cpy_test_stack;

	cpy_test_stack = test_stack;

	for (int i = size - 1; i > 0; --i)
	{
		if (cpy_test_stack.Pop() != STATES[i])
			pass = false;
	}

	cout << "Op eql test complex";

	return pass;
}

bool test_is_empty_complex()
{
	bool pass = true;
	int size = 10;

	Stack<string> test_stack;
	test_stack.setSize(size);

	for (int i = 0; i < size; ++i)
		test_stack.Push(STATES[i]);

	while (!test_stack.isEmpty())
		test_stack.Pop();

	pass = test_stack.isEmpty(); // True will pass test

	cout << "Is empty test complex ";

	return pass;
}

bool test_is_full_complex()
{
	bool pass = true;
	int size = 5;
	int num = 0;

	Stack<string> test_stack;
	test_stack.setSize(size);


	while (!test_stack.isFull())
		test_stack.Push(STATES[num++]);

	pass = test_stack.isFull(); // True will pass test

	cout << "Is full test complex ";

	return pass;
}

bool test_Peek_complex()
{
	bool pass = true;
	int size = 1;
	int num = 0;
	string Push_value = "test";

	Stack<string> test_stack;
	test_stack.setSize(size);


	test_stack.Push(Push_value);

	if (test_stack.Peek() != Push_value)
		pass = false;

	// If Peek returned true value, test to make sure that Peek didn't remove
	// the stack element (an exception would be called if Peek removed element).
	if (pass)
	{
		try
		{
			test_stack.Pop();
		}
		catch (Exception& except)
		{
			pass = false;
		}
	}


	cout << "Peek test complex ";

	return pass;
}

bool test_size_getter_complex()
{
	bool pass = true;
	int size = 5;
	int num = 0;

	Stack<string> test_stack;
	test_stack.setSize(size);


	while (!test_stack.isFull() && pass)
	{
		test_stack.Push(STATES[num++]);

		if (test_stack.getSize() != num)
			pass = false;
	}

	cout << "Size getter test complex ";

	return pass;
}