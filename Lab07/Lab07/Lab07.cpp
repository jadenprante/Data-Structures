/*************************************************************
* Author:			Jaden Prante
* Filename:			Lab06.cpp
* Date Created:		Apr 19th 2025
* Modifications:	NA
*
* *\
* Lab/Assignment: Lab 7 – Stack Array Implementation
*
* Overview:
* Linked List stack implementation
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
#include "Stack.h"  
// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };
const int NUM_NAMES = 15;
const int NUM_SIZE = 10;
const int NUM_EXTRACT = 4;
// Test function declaration
bool testDefaultCtor();
bool testPushSingleElement();
bool testPushMultipleElements();
bool testPopSingleElement();
bool testPopMultipleElements();
bool testPopFromEmptyStack();
bool testPeek();
bool testPeekFromEmptyStack();
bool testCopyCtor();
bool testMoveCtor();
bool testCopyAssignment();
bool testMoveAssignment();
bool testIsEmptyTrue();
bool testIsEmptyFalse();
bool testLargeNumberOfElements();
bool testPopAllElements();
bool testPeekDoesNotRemoveElement();
bool testDifferentDataTypes();
bool testClearStack();
// Array of test functions
FunctionPointer test_functions[] = { testDefaultCtor, testPushSingleElement,
testPushMultipleElements, testPopSingleElement, testPopMultipleElements, testPopFromEmptyStack, testPeek, testPeekFromEmptyStack,
testCopyCtor, testMoveCtor, testCopyAssignment, testMoveAssignment, testIsEmptyTrue, testIsEmptyFalse, testLargeNumberOfElements, testPopAllElements,
testPeekDoesNotRemoveElement, testDifferentDataTypes, testClearStack
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

bool testDefaultCtor() {
    cout << "Default Constructor testing ";
    Stack<int> stack;
    return stack.isEmpty();
}

bool testPushSingleElement() {
    cout << "Pushing Single Element testing ";
    Stack<int> stack;
    stack.Push(5);
    return stack.getNumElements() == 1 && stack.Peek() == 5;
}

bool testPushMultipleElements() {
    cout << "Pushing Multiple Elements testing ";
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    return stack.getNumElements() == 3 && stack.Peek() == 3;
}

bool testPopSingleElement() {
    cout << "Popping Single Element testing ";
    Stack<int> stack;
    stack.Push(5);
    int popped = stack.Pop();
    return stack.isEmpty() && popped == 5;
}

bool testPopMultipleElements() {
    cout << "Popping Multiple Elements testing ";
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    stack.Pop();
    return stack.getNumElements() == 2 && stack.Peek() == 2;
}

bool testPopFromEmptyStack() {
    cout << "Popping from empty stack testing ";
    Stack<int> stack;
    try {
        stack.Pop();
    }
    catch (Exception&) {
        return true; // Exception caught
    }
    return false; // No exception thrown
}

bool testPeek() {
    cout << "Peek testing ";
    Stack<int> stack;
    stack.Push(5);
    return stack.Peek() == 5;
}

bool testPeekFromEmptyStack() {
    cout << "Peeking from empty stack testing ";
    Stack<int> stack;
    try {
        stack.Peek();
    }
    catch (const Exception&) {
        return true; // Exception caught
    }
    return false; // No exception thrown
}

bool testCopyCtor() {
    cout << "Copy Constructor Testing ";
    Stack<int> stack1;
    stack1.Push(1);
    stack1.Push(2);
    Stack<int> stack2(stack1);
    return stack2.getNumElements() == 2 && stack2.Peek() == 2;
}

bool testMoveCtor() {
    cout << "Move Constructor Testing ";
    Stack<int> stack1;
    stack1.Push(1);
    stack1.Push(2);
    Stack<int> stack2(std::move(stack1));
    return stack2.getNumElements() == 2 && stack2.Peek() == 2 && stack1.isEmpty();
}

bool testCopyAssignment() {
    cout << "Copy Assignment Operator Testing ";
    Stack<int> stack1;
    stack1.Push(1);
    stack1.Push(2);
    Stack<int> stack2;
    stack2 = stack1;
    return stack2.getNumElements() == 2 && stack2.Peek() == 2;
}

bool testMoveAssignment() {
    cout << "Move Assignment Operator Testing ";
    Stack<int> stack1;
    stack1.Push(1);
    stack1.Push(2);
    Stack<int> stack2;
    stack2 = std::move(stack1);
    return stack2.getNumElements() == 2 && stack2.Peek() == 2 && stack1.isEmpty();
}

bool testIsEmptyTrue() {
    cout << "IsEmptyTrue testing ";
    Stack<int> stack;
    return stack.isEmpty();
}

bool testIsEmptyFalse() {
    cout << "IsEmptyFalse testing ";
    Stack<int> stack;
    stack.Push(1);
    return !stack.isEmpty();
}

bool testLargeNumberOfElements() {
    cout << "Large number of elements testing ";
    Stack<int> stack;
    for (int i = 0; i < 1000; ++i) {
        stack.Push(i);
    }
    return stack.getNumElements() == 1000 && stack.Peek() == 999;
}

bool testPopAllElements() {
    cout << "Popping all elements testing ";
    Stack<int> stack;
    for (int i = 0; i < 10; ++i) {
        stack.Push(i);
    }
    for (int i = 0; i < 10; ++i) {
        stack.Pop();
    }
    return stack.isEmpty();
}

bool testPeekDoesNotRemoveElement() {
    cout << "Peek not removing element testing ";
    Stack<int> stack;
    stack.Push(5);
    stack.Peek();
    return stack.getNumElements() == 1;
}

bool testDifferentDataTypes() {
    cout << "Different data type testing ";
    Stack<std::string> stack;
    stack.Push("Hello");
    stack.Push("World");
    return stack.getNumElements() == 2 && stack.Peek() == "World";
}

bool testClearStack() {
    cout << "Cleariong stack testing ";
    Stack<int> stack;
    for (int i = 0; i < 5; ++i) {
        stack.Push(i);
    }
    while (!stack.isEmpty()) {
        stack.Pop();
    }
    return stack.isEmpty();
}
