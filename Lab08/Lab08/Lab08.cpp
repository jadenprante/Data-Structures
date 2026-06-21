/*************************************************************
* Author:			Jaden Prante
* Filename:			Lab06.cpp
* Date Created:		Jan 14th 2025
* Modifications:	NA
*
* 
* Lab/Assignment: Lab 8 – Linked List Based Queue 
*
* Overview:
* Linked List queu implementation
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
#include "Queue.h"  
// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };
const int NUM_NAMES = 15;
const int NUM_SIZE = 10;
const int NUM_EXTRACT = 4;
// Test Function Declarations
bool testIsEmptyOnNewQueue();
bool testEnqueueMakesQueueNonEmpty();
bool testGetNumElementsAfterEnqueue();
bool testDequeueSingleElement();
bool testFIFOOrder();
bool testPeekDoesNotDequeue();
bool testDequeueUntilEmpty();
bool testCopyCtor();
bool testCopyAssignment();
bool testMoveCtor();
bool testMoveAssignment();
bool testEnqueueAfterMove();
bool testDequeueEmptyQueueThrows();
bool testPeekEmptyQueueThrows();
bool testStringQueue();
bool testLargeQueue();
bool testClearQueue();
bool testMixedOperations();
bool testEnqueueAfterEmpty();
bool testDestructor();

// Array of test functions
FunctionPointer test_functions[] = { testIsEmptyOnNewQueue, testEnqueueMakesQueueNonEmpty, testGetNumElementsAfterEnqueue,
testDequeueSingleElement, testFIFOOrder, testPeekDoesNotDequeue, testDequeueUntilEmpty, testCopyCtor, testCopyAssignment, 
testMoveCtor, testMoveAssignment, testEnqueueAfterMove, testDequeueEmptyQueueThrows, testPeekEmptyQueueThrows, testStringQueue, 
testLargeQueue, testClearQueue, testMixedOperations, testEnqueueAfterEmpty, testDestructor
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
	return 0; cout << "Hello World!\n";
}

bool testIsEmptyOnNewQueue() {
    cout << "IsEmptyOnNewQueue test ";
    Queue<int> q;
    return q.isEmpty();
}

bool testEnqueueMakesQueueNonEmpty() {
    cout << "EnqueueMakesQueueNonEmpty test ";
    Queue<int> q;
    q.Enqueue(10);
    return !q.isEmpty();
}

bool testGetNumElementsAfterEnqueue() {
    cout << "GetNumElementsAfterEnqueue test ";
    Queue<int> q;
    q.Enqueue(10);
    q.Enqueue(20);
    return q.getNumElements() == 2;
}

bool testDequeueSingleElement() {
    cout << "DequeueSingleElement test ";
    Queue<int> q;
    q.Enqueue(5);
    return q.Dequeue() == 5 && q.isEmpty();
}

bool testFIFOOrder() {
    cout << "First in First out test ";
    Queue<int> q;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    return (q.Dequeue() == 1) && (q.Dequeue() == 2) && (q.Dequeue() == 3);
}

bool testPeekDoesNotDequeue() {
    cout << "PeekDoesNotDequeue test ";
    Queue<int> q;
    q.Enqueue(42);
    return q.Peek() == 42 && q.getNumElements() == 1;
}

bool testDequeueUntilEmpty() {
    cout << "DequeueUntilEmpty test ";
    Queue<int> q;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Dequeue();
    q.Dequeue();
    return q.isEmpty();
}

bool testCopyCtor() {
    cout << "Copy Constructor test ";
    Queue<int> q1;
    q1.Enqueue(10);
    q1.Enqueue(20);
    Queue<int> q2(q1);
    return (q2.Dequeue() == 10) && (q2.Dequeue() == 20) && q1.getNumElements() == 2;
}

bool testCopyAssignment() {
    cout << "Copy Assignment Operator test ";
    Queue<int> q1;
    q1.Enqueue(100);
    q1.Enqueue(200);

    Queue<int> q2;
    q2 = q1;

    return (q2.Dequeue() == 100) && (q2.Dequeue() == 200) && q1.getNumElements() == 2;
}

bool testMoveCtor() {
    cout << "Move Constructor test ";
    Queue<int> q1;
    q1.Enqueue(5);
    q1.Enqueue(10);

    Queue<int> q2(std::move(q1));
    return q2.getNumElements() == 2 && q1.isEmpty();
}

bool testMoveAssignment() {
    cout << "Move Assignment Operator test ";
    Queue<int> q1;
    q1.Enqueue(7);
    q1.Enqueue(14);
    Queue<int> q2;
    q2 = std::move(q1);
    return q2.getNumElements() == 2 && q1.isEmpty();
}

bool testEnqueueAfterMove() {
    cout << "EnqueueAfterMove test ";
    Queue<int> q1;
    q1.Enqueue(30);
    Queue<int> q2 = std::move(q1);
    q2.Enqueue(40);
    return q2.getNumElements() == 2;
}

bool testDequeueEmptyQueueThrows() {
    cout << "DequeueEmptyQueueThrows test ";
    try {
        Queue<int> q;
        q.Dequeue();
    }
    catch (const Exception&) {
        return true;
    }
    return false;
}

bool testPeekEmptyQueueThrows() {
    cout << "PeekEmptyQueueThrows test ";
    try {
        Queue<int> q;
        q.Peek();
    }
    catch (const Exception&) {
        return true;
    }
    return false;
}

bool testStringQueue() {
    cout << "StringQueue test ";
    Queue<std::string> q;
    q.Enqueue("hello");
    q.Enqueue("world");
    return q.Dequeue() == "hello" && q.Dequeue() == "world";
}

bool testLargeQueue() {
    cout << "LargeQueue test ";
    Queue<int> q;
    for (int i = 0; i < 1000; ++i)
        q.Enqueue(i);
    for (int i = 0; i < 1000; ++i)
        if (q.Dequeue() != i) 
            return false;
    return q.isEmpty();
}

bool testClearQueue() {
    cout << "ClearQueue test ";
    Queue<int> q;
    q.Enqueue(10);
    q.Enqueue(20);
    q.Dequeue();
    q.Dequeue();
    return q.isEmpty();
}

bool testMixedOperations() {
    cout << "MixedOperations test ";
    Queue<int> q;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Dequeue();
    q.Enqueue(3);
    return q.getNumElements() == 2 && q.Peek() == 2;
}

bool testEnqueueAfterEmpty() {
    cout << "EnqueueAfterEmpty test ";
    Queue<int> q;
    q.Enqueue(10);
    q.Dequeue();
    q.Enqueue(20);
    return q.Peek() == 20 && q.getNumElements() == 1;
}

bool testDestructor() {
    cout << "Destructor test ";
    Queue<int>* q = new Queue<int>();
    q->Enqueue(99);
    delete q;
    return true; 
}
