/*************************************************************
* Author:			Jaden Prante
* Filename:			Lab06.cpp
* Date Created:		Apr 21st 2025
* Modifications:	NA
*
* 
* Lab/Assignment: Lab 9 – Circular Queues
*
* Overview:
* This lab goes over queue with arrays 
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
#include "CircularQueue.h"  
// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };
const int NUM_NAMES = 15;
const int NUM_SIZE = 10;
const int NUM_EXTRACT = 4;
// Test function declaration
bool testEnqueueDequeue();
bool testQueueIsEmpty();
bool testQueueIsFull();
bool testPeek();
bool testWrapAround();
bool testCopyCtor();
bool testMoveCtor();
bool testCopyAssignment();
bool testMoveAssignment();
bool testQueueSize();
bool testDequeueFromEmpty();
bool testEnqueueToFull();
bool testMultipleEnqueueDequeue();
bool testHeadTailPositioning();
bool testCircularFunctionality();
bool testStressTest();
bool testBoundaryConditions();
bool testExceptionHandling();
bool testLargeDataHandling();
bool testPerformance();


// Array of test functions
FunctionPointer test_functions[] = { testEnqueueDequeue, testQueueIsEmpty, testQueueIsFull, testPeek,
testWrapAround, testCopyCtor, testMoveCtor, testCopyAssignment, testMoveAssignment, testQueueSize, 
testDequeueFromEmpty, testEnqueueToFull, testMultipleEnqueueDequeue, testHeadTailPositioning, testCircularFunctionality,
testStressTest, testBoundaryConditions, testExceptionHandling, testLargeDataHandling, testPerformance
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

bool testEnqueueDequeue() 
{
    cout << "Enqueue and Dequeue test ";
    CircularQueue<int> queue(5);
    queue.Enqueue(10);
    return queue.Dequeue() == 10;
}

bool testQueueIsEmpty() 
{
    cout << "Queue is empty test ";
    CircularQueue<int> queue(5);
    return queue.isEmpty();
}

bool testQueueIsFull() 
{
    cout << "Queue is full test ";
    CircularQueue<int> queue(3);
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);
    return queue.isFull();
}

bool testPeek() 
{
    cout << "Peek test ";
    CircularQueue<int> queue(5);
    queue.Enqueue(42);
    return queue.Peek() == 42;
}

bool testWrapAround() 
{
    cout << "Wrap Around test ";
    CircularQueue<int> queue(3);
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Dequeue();
    queue.Dequeue();
    queue.Enqueue(3);
    queue.Enqueue(4);
    return queue.Dequeue() == 3;
}

bool testCopyCtor() 
{
    cout << "Copy Constructor test ";
    CircularQueue<int> queue1(5);
    queue1.Enqueue(10);
    CircularQueue<int> queue2 = queue1;
    return queue2.Dequeue() == 10;
}

bool testMoveCtor() 
{
    cout << "Move Constructor test ";
    CircularQueue<int> queue1(5);
    queue1.Enqueue(20);
    CircularQueue<int> queue2 = std::move(queue1);
    return queue2.Dequeue() == 20;
}

bool testCopyAssignment() 
{
    cout << "Copy Assignment Operator test ";
    CircularQueue<int> queue1(5);
    queue1.Enqueue(30);
    CircularQueue<int> queue2(5);
    queue2 = queue1;
    return queue2.Dequeue() == 30;
}

bool testMoveAssignment() 
{
    cout << "Move Assignment Operator test ";
    CircularQueue<int> queue1(5);
    queue1.Enqueue(40);
    CircularQueue<int> queue2(5);
    queue2 = std::move(queue1);
    return queue2.Dequeue() == 40;
}

bool testQueueSize() 
{
    cout << "Queue Size test ";
    CircularQueue<int> queue(2);
    queue.Enqueue(1);
    queue.Enqueue(2);
    return queue.getSize() == 2;
}

bool testDequeueFromEmpty() 
{
    bool pass = false;
    cout << "Dequeue from empty test ";
    CircularQueue<int> queue(3);
    try {
        queue.Dequeue();
    }
    catch (Exception& except) {
        except.getMessage();
        pass = true;
    }
    return pass;
}

bool testEnqueueToFull() 
{
    bool pass = false;
    cout << "Enqueue from full test ";
    CircularQueue<int> queue(2);
    queue.Enqueue(1);
    queue.Enqueue(2);
    try {
        queue.Enqueue(3);
    }
    catch (Exception& except) {
        except.getMessage();
        pass = true;
    }
    return pass;
}

bool testMultipleEnqueueDequeue() 
{
    cout << "Multiple Enqueue and Dequeue test ";
    CircularQueue<int> queue(4);
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Dequeue();
    queue.Enqueue(3);
    return queue.Dequeue() == 2;
}

bool testHeadTailPositioning() 
{
    cout << "Head and Tail positioning test ";
    CircularQueue<int> queue(3);
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Dequeue();
    queue.Enqueue(3);
    queue.Dequeue();
    return queue.Dequeue() == 3;
}

bool testCircularFunctionality() 
{
    cout << "Circular Functionality test ";
    CircularQueue<int> queue(2);
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Dequeue();
    queue.Enqueue(3);
    return queue.isFull();
}

bool testStressTest() 
{
    cout << "Stress test ";
    CircularQueue<int> queue(1000);
    for (int i = 0; i < 1000; i++)
        queue.Enqueue(i);
    for (int i = 0; i < 1000; i++)
        if (queue.Dequeue() != i)
            return false;
    return true;
}

bool testBoundaryConditions() 
{
    cout << "Boundary Conditions test ";
    CircularQueue<int> queue(1);
    queue.Enqueue(99);
    return queue.isFull() && !queue.isEmpty();
}

bool testExceptionHandling() 
{
    bool pass = false;
    cout << "Exception Handling test ";
    CircularQueue<int> queue(2);
    queue.Enqueue(1);
    queue.Enqueue(2);
    try {
        queue.Enqueue(3);
    }
    catch (Exception& except) {
        except.getMessage();
        pass = true;
    }
    return pass;
}

bool testLargeDataHandling() 
{
    cout << "Large Data Handling test ";
    CircularQueue<string> queue(5);
    queue.Enqueue("Hello");
    queue.Enqueue("World");
    return queue.Dequeue() == "Hello" && queue.Dequeue() == "World";
}

bool testPerformance() {
    cout << "Overall Performance test ";
    CircularQueue<int> queue(100000);
    for (int i = 0; i < 100000; i++)
        queue.Enqueue(i);
    for (int i = 0; i < 100000; i++)
        if (queue.Dequeue() != i)
            return false;
    return true;
}
